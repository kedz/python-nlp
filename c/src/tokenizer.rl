#include "tokenizer.h"
#include "stdio.h"
#include <string.h>


%%{

    machine tok;
    alphtype unsigned char;

    include WChar "unicode.rl";


    SGML = "<" (
          ("!"| "?") [A-Za-z\-] [^>\r\n]*
        | [A-Za-z] [A-Za-z0-9_:.\-]*
          ([ ]+ (
              [A-Za-z][A-Za-z0-9_:.\-]*
            |
              [A-Za-z][A-Za-z0-9_:.\-]*[ ]*"="[ ]*
              (   "'" (!"'")* "'" 
                | "\"" (!'"')* "\"" 
                | [A-Za-z][A-Za-z0-9_:.\-]*
              )
          ))* 
          [ ]* "/"? | "/"[A-Za-z][A-Za-z0-9_:.\-]*
        )[ ]*">";


    SPMDASH = 
            "&" (/MD/i | /mdash/i | /ndash/i) ";"
        | 0xC2 0x96 
        | 0xC2 0x97
        | 0xE2 0x80 0x93..0x95;
    
    SPAMP = "&amp;";
    SPPUNC = "&" (
        "HT"|"TL"|"UR"|"LR"|"QC"|"QL"|"QR"|"odq"|"cdq"| 
        "#" udigit+
        ) ";" ;
    SPLET = "&" [aeiouAEIOU] ("acute"|"grave"|"uml") ";";
    SPACE = " " 
        | "\t" 
        | 0xC2 0xA0
        | 0xE2 0x80 0x80..0x8A
        | 0xE3 0x80 0x80 ;

    SPACES = SPACE+;

    NEWLINE = "\r"
        | "\r" ? "\n" 
        | 0xE2 0x80 0xA8
        | 0xE2 0x80 0xA9
        | 0x0B
        | 0x0C 
        | 0xC2 0x85;

    SPACENL = SPACE | NEWLINE ;

    SPACENLS = SPACENL+ ;

    #TODO: Need to break out UPPER for SENTEND
    #
    #

    DIGIT = udigit | 0xDF 0x80..0x89 ;

    DATE = DIGIT {1,2} [\-\/] DIGIT {1,2} [\-\/] DIGIT {2,4};

    NUM = DIGIT+ 
        | DIGIT* ( ("."|":"|","|0xC2 0xAD|0xD9 0xAB|0xD9 0xAC) DIGIT+ )+;

    NUMBER = [\-\+]? NUM;

    SUBSUPNUM = 
        (   
              0xE2 0x81 0xBA 
            | 0xE2 0x81 0xBB
            | 0xE2 0x82 0x8A
            | 0xE2 0x82 0x8B
        )? 
        (
            (   
                  0xE2 0x81 0xB0
                | 0xC2 0xB9
                | 0xC2 0xB2
                | 0xC2 0xB3
                | 0xE2 0x81 0xB4..0xB9
            )+ | (0xE2 0x82 0x80..0x89)+
        );

    FRAC = ( DIGIT{1,4} ("-"|" "| 0xC2 0xA0) )?
           DIGIT{1,4} ('\\'? "/" | 0xE2 0x81 0x84) DIGIT{1,4} ;

    FRACSTB3 = ( DIGIT{1,4} "-" )? DIGIT{1,4} ("\\"?"/"| 0xE2 0x81 0x84)
                DIGIT{1,4} ;
    FRAC2 =   0xC2 0xBC # u+00BC
            | 0xC2 0xBD # u+00BD
            | 0xC2 0xBE # u+00BE
            | 0xE2 0x85 0x93..0x9E # u+2153 .. u+215E
            ;

    DOLSIGN = ([A-Z]*"$"|"#");
    DOLSIGN2 =    0xC2 0xA2 # u+00A2 
                | 0xC2 0xA3 # u+00A3 
                | 0xC2 0xA4 # u+00A4 
                | 0xC2 0xA5 # u+00A5 
                | 0xC2 0x80 # u+0080 
                | 0xE2 0x82 0xA0 # u+20A0 
                | 0xE2 0x82 0xAC # u+20AC 
                | 0xD8 0x8B # u+060B 
                | 0xE0 0xB8 0xBF # u+0E3F 
                | 0xE2 0x82 0xA4 # u+20A4 
                | 0xEF 0xBF 0xA0 # u+FFE0 
                | 0xEF 0xBF 0xA1 # u+FFE1 
                | 0xEF 0xBF 0xA5 # u+FFE5 
                | 0xEF 0xBF 0xA6 # u+FFE6 
                ;

    LETTER = ualpha | SPLET  # TODO Make sure this matches stanford
        | 0xC2 0xAD # u+00AD
        | 0xC8 0xB7..0xBF # u+0237 .. u+024F
        | 0xC9 0x80..0xBF
        | 0xCB 0x82..0x85 # u+02C2 .. u+02C5
        | 0xCB 0x92..0x9F # u+02D2 .. u+02DF
        | 0xCB 0xA5..0xBF # u+02E5 .. u+02FF
        | 0xCC 0x80..0xBF # u+0300 .. u+036F
        | 0xCD 0x80..0xAF
        | 0xCD 0xB0..0xBD # u+0370 .. u+037D
        | 0xCE 0x84 # u+0384
        | 0xCE 0x85 # u+0385
        | 0xCF 0x8F # u+03CF 
        | 0xCF 0xB6 # u+03F6 
        | 0xCF 0xBC..0xBF # u+03FC .. u+03FF
        | 0xD2 0x83..0x87 # u+0483 .. u+0487
        | 0xD3 0x8F # u+04CF 
        | 0xD3 0xB6..0xBF # u+04F6 .. u+04FF 
        | 0xD4 0x90..0xA5 # u+0510 .. u+0525
        | 0xD5 0x9A..0x9F # u+055A .. u+055F
        | 0xD6 0x91..0xBD # u+0591 .. u+05BD 
        | 0xD6 0xBF # u+05BF 
        | 0xD7 0x81 # u+05C1 
        | 0xD7 0x82 # u+05C2 
        | 0xD7 0x84 # u+05C4 
        | 0xD7 0x85 # u+05C5 
        | 0xD7 0x87 # u+05C7 
        | 0xD8 0x95..0x9A # u+0615 .. u+061A 
        | 0xD8 0xBB..0xBF # u+063B .. u+063F 
        | 0xD9 0x8B..0x9E # u+064B .. u+065E 
        | 0xD9 0xB0 # u+0670 
        | 0xDB 0x96..0xAF # u+06D6 .. u+06EF 
        | 0xDB 0xBA..0xBF # u+06FA .. u+06FF 
        | 0xDC 0x8F # u+070F 
        | 0xDC 0x91 # u+0711 
        | 0xDC 0xB0..0xBF # u+0730 .. u+074F
        | 0xDD 0x80..0x8F
        | 0xDD 0x90..0xBF # u+0750 .. u+077F
        | 0xDE 0xA6..0xB1 # u+07A6 .. u+07B1 
        | 0xDF 0x8A..0xB5 # u+07CA .. u+07F5 
        | 0xDF 0xBA # u+07FA 
        | 0xE0 0xA4 0x80..0x83 # u+0900 .. u+0903 
        | 0xE0 0xA4 0xBC # u+093C 
        | 0xE0 0xA4 0xBE # u+093E .. u+094E
        | 0xE0 0xA4 0xBF
        | 0xE0 0xA5 0x80..0x8E
        | 0xE0 0xA5 0x91..0x95 # u+0951 .. u+0955 
        | 0xE0 0xA5 0xA2..0xA3 # u+0962 .. u+0963 
        | 0xE0 0xA6 0x81..0x83 # u+0981 .. u+0983 
        | 0xE0 0xA6 0xBC..0xBF # u+09BC .. u+09C4
        | 0xE0 0xA7 0x80..0x84
        | 0xE0 0xA7 0x87 # u+09C7 
        | 0xE0 0xA7 0x88 # u+09C8 
        | 0xE0 0xA7 0x8B..0x8D # u+09CB .. u+09CD 
        | 0xE0 0xA7 0x97 # u+09D7
        | 0xE0 0xA7 0xA2 # u+09E2 
        | 0xE0 0xA7 0xA3 # u+09E3 
        | 0xE0 0xA8 0x81..0x83 # u+0A01 .. u+0A03
        | 0xE0 0xA8 0xBC # u+0A3C 
        | 0xE0 0xA8 0xBE # u+0A3E .. u+0A4F
        | 0xE0 0xA8 0xBF 
        | 0xE0 0xA9 0x80..0x8F
        | 0xE0 0xAA 0x81..0x83 # u+0A81 .. u+0A83
        | 0xE0 0xAA 0xBC..0xBF # u+0ABC .. u+0ACF 
        | 0xE0 0xAB 0x80..0x8F
        | 0xE0 0xAE 0x82 # u+0B82 
        | 0xE0 0xAE 0xBE # u+0BBE .. u+0BC2
        | 0xE0 0xAE 0xBF 
        | 0xE0 0xAF 0x80..0x82
        | 0xE0 0xAF 0x86..0x88 # u+0BC6 .. u+0BC8 
        | 0xE0 0xAF 0x8A..0x8D # u+0BCA .. u+0BCD 
        | 0xE0 0xB0 0x81..0x83 # u+0C01 .. u+0C03
        | 0xE0 0xB0 0xBE # u+0C3E .. u+0C56 
        | 0xE0 0xB0 0xBF 
        | 0xE0 0xB1 0x80..0x96
        | 0xE0 0xB4 0xBE # u+0D3E .. u+0D44 
        | 0xE0 0xB4 0xBF 
        | 0xE0 0xB5 0x80..0x84
        | 0xE0 0xB5 0x86..0x88 # u+0D46 .. u+0D48 
        | 0xE0 0xB8 0xB0..0xBA # u+0E30 .. u+0E3A 
        | 0xE0 0xB9 0x87..0x8E # u+0E47 .. u+0E4E 
        | 0xE0 0xBA 0xB1..0xBC # u+0EB1 .. u+0EBC 
        | 0xE0 0xBB 0x88..0x8D # u+0EC8 .. u+0ECD 
        ;

    WORD = LETTER (LETTER | DIGIT)*([.!?]LETTER(LETTER | DIGIT)*)*;
   
    FILENAME_EXT = /bat/i  | /bmp/i  | /c/i    | /class/i | /cgi/i | /cpp/i 
        | /dll/i | /doc/i  | /docx/i | /exe/i  | /gif/i   | /gz/i  | /h/i 
        | /htm/i | /html/i | /jar/i  | /java/i | /jpeg/i  | /jpg/i | /mov/i 
        | /mp3/i | /pdf/i  | /php/i  | /pl/i   | /png/i   | /ppt/i | /ps/i 
        | /py/i  | /sql/i  | /tar/i  | /txt/i  | /wav/i   | /x/i   | /xml/i 
        | /zip/i ;
    FILENAME = (LETTER|DIGIT)+("."(LETTER|DIGIT)+)*("."FILENAME_EXT);
    # TODO test filename also maybe do UPPPER 

    APOS = "'" | 0xC2 0x92 | 0xE2 0x80 0x99 | "&apos;" ;
    APOSETCETERA = APOS | "`" | 0xC2 0x91 | 0xE2 0x80 0x98 | 0xE2 0x80 0x9B;
    HYPHEN = "-" | "_" | 0xD6 0x8A | 0xE2 0x80 0x90 | 0xE2 0x80 0x91 ;

    ACRO2 =   [A-Za-z] ( "." [A-Za-z] )+ 
            | (/Canada|Sino|Korean|EU|Japan|non/i) "-U.S" 
            | "U.S.-" ( "U.K" | "U.S.S.R" ) ;

    
    THING = ( [dDoOlL] APOSETCETERA (ualnum) )?
            ( ualnum )+
            ( HYPHEN ( [dDoOlL] APOSETCETERA ualnum )? ualnum+ )*;
    THINGA = [A-Z]+ ( ("+" | "&" | SPAMP ) [A-Z]+ )+ ;
    THING3 = [A-Za-z0-9]+ ("-" [A-Za-z]+ ){0,2} 
        ( "\\"? "/" [A-Za-z0-9]+ ("-" [A-Za-z]+ ){0,2} ){1,2} ;

    HTHING = [A-Za-z0-9] ( [A-Za-z0-9.,] | 0xC2 0xAD )*
             ( 
                "-" (([A-Za-z0-9] | 0xC2 0xAD )+ | ACRO2 ".")
             )+ ;
    REDAUX = APOS ( [msdMSD] | /re/i | /ve/i | /ll/i );

    SWORD = ( [A-Za-z] | 0xC2 0xAD )* [A-MO-Za-mo-z] ( 0xC2 0xAD )* ;
    SREDAUX = "n" APOSETCETERA "t" ;

    APOWORD = APOS "n" APOS? 
            | [lLdDjJ] APOS 
            | /Dunkin/i APOS
            | /somethin/i APOS
            | /ol/i APOS
            | APOS /em/i 
            | [A-HJ-XZn] APOSETCETERA ualpha{2} ualpha*
            | APOS[2-9]"0"[Ss]
            | APOS /til/i [Ll]?
            | ualpha ualpha* [aeiouyAEIOUY] APOSETCETERA [aeiouA-Z] ualpha*
            | APOS /cause/i
            | /cont'd/i "."?
            | "cont'd"
            | /'twas/i
            | /nor'easter/i
            | /c'mon/i
            | /e'er/i
            | /s'mores/i
            | /ev'ry/i
            | /li'l/i
            | /nat'l/i
            | [Oo] APOSETCETERA [Oo]
            ;

    APOWORD2 = [Yy] APOS;

    FULLURL = /http/i [Ss]?":\/\/" 
        [^ \t\n\f\r\<>|"(){}]+ 
        [^ \t\n\f\r"<>|.!?(){},\-] ;
    LIKELYURL = (
            (/www/i "."  ([^ \t\n\f\r"<>|.!?(){},]+ 
                ".")+ [a-zA-Z]{2,4})
        |
            (([^ \t\n\f\r"`'<>|.!?(){},\-_$]+ 
                ".")+ (/com/i|/net/i|/org/i|/edu/i))
        )("/"[^ \t\n\f\r"<>|()]+ 
             [^ \t\n\f\r"<>|.!?(){},\-])?;
#/* &lt;,< should match &gt;,>, but that's too complicated */
#
#    EMAIL = ("&lt;"|"<")?[a-zA-Z0-9]
#        !(([\t\n\f\r"<>|(){}]|0xC2 0xA0)*)
#        "@"
#            ((!(([ \t\n\f\r"<>|(){}.]|0xC2 0xA0)+)) 
#            ".")*
#
 #       !(([ \t\n\f\r\"<>|(){}.]|0xC2 0xA0)+)
 #       ("&gt;"|">")?;
#[^ \t\n\f\r"<>|()\u00A0{}]*



#/* Technically, names should be capped at 15 characters.  However, then
#   you get into weirdness with what happens to the rest of the characters. */
    TWITTER_NAME = "@"[a-zA-Z_][a-zA-Z_0-9]*;
    TWITTER_CATEGORY = "#"LETTER+;
    TWITTER = TWITTER_NAME|TWITTER_CATEGORY;

    ABMONTH = /Jan/i|/Feb/i|/Mar/i|/Apr/i|/Jun/i|/Jul/i|/Aug/i
        |/Sep/i|/Sept/i|/Oct/i|/Nov/i|/Dec/i;
    ABDAYS = /Mon/i|/Tue/i|/Tues/i|/Wed/i|/Thu/i|/Thurs/i|/Fri/i;
    ABSTATE = /Ala/i | /Ariz/i   | [A]/z/i     | [A]/rk/i | /Calif/i  | /Colo/i
        | /Conn/i    | /Ct/i     | /Dak/i      | [D]/el/i | /Fla/i    | /Ga/i
        | [I]/ll/i   | /Ind/i    | /Kan/i[Ss]? | /Ky/i    | [L]/a/i  
        | [M]/ass/i  | /Md/i     | /Mich/i     | /Minn/i  | [M]/iss/i | /Mo/i
        | /Mont/i    | /Neb/i    | /Nev/i      | /Okla/i  | [O]/re/i  
        | [P]/a/i    | /Penn/i   | /Tenn/i     | [T]/ex/i | /Va/i     | /Vt/i
        | [W]/ash/i  | /Wis/i [Cc]? | /Wyo/i ;
    ABCOMP = /Inc/i | /Co/i [Ss]? | /Corp/i    | [Pp]{1,2}[Tt][ye][Ss]? 
        | /Ltd/i    | /Plc/i      | /Rt/i      | /Bancorp/i | /Bhd/i | /Assn/i
        | /Univ/i   | /Intl/i     | /Sys/i ;
    ABNUM = /tel/i | /est/i | /ext/i | /sq/i ;
    ABPTIT = /Jr/i | /Sr/i | /Bros/i | (/Ed/i | /Ph/i) "." [Dd] 
        | /Blvd/i | /Rd/i | /Esq/i;

    ABBREV1 = (ABMONTH | ABDAYS | ABSTATE | ABCOMP | ABNUM | ABPTIT | /etc/i
        | /al/i | /seq/i | /Bldg/i) ".";


    ACRO = [A-Za-z]("."[A-Za-z])* 
        | (/Canada/i | /Sino/i | /Korean/i | /EU/i | /Japan/i| /non/i)
          "-" [Uu]"."[Ss] 
        | [Uu] "." [Ss] ".-" ([Uu]"."[Kk] | [Uu]"."[Ss]"."[Ss]"."[Rr]);

    ABTITLE = /Mr/i | /Mrs/i | /Ms/i | [M]/iss/i | /Dr/i[Ss]? | /Prof/i[Ss]?
        | /Sen/i [Ss]? | /Rep/i [Ss]? | /Atty/i [Ss]? | /Lt/i | /Col/i 
        | /Gen/i | /Messrs/i | /Gov/i [Ss]? | /Adm/i | /Rev/i | /Maj/i 
        | /Sgt/i | /Cpl/i | /Pvt/i | /Capt/i | /St/i [Ee]? | /Ave/i | /Pres/i
        | /Lieut/i | /Hon/i | /Brig/i | [Cc][Oo]?/mdr/i | /Pfc/i | /Spc/i
        | /Supt/i [Ss]? | /Det/i | /Mt/i | /Ft/i | /Adj/i | /Adv/i | /Asst/i 
        | /Assoc/i | /Ens/i | /Insp/i | /Mlle/i | /Mme/i | /Msgr/i | /Sfc/i
        ;
    ABCOMP2 = /Invt/i | /Elec/i | /Natl/i | [Mm][ft][Gg] | /Dept/i ;

    ABBREV4 = ABTITLE | /vs/i | [v] | /Alex/i | /Wm/i | /Jos/i | /Cie/i 
        | [Aa] "." [Kk] "." [Aa] | /cf/i | /TREAS/i | /Ph/i | ACRO | ABCOMP2;
    ABBREV2 = ABBREV4 ".";
    ACRONYM = ACRO".";

 
    PUNC = [?!]+ |
        [.¡¿]  ; # TODO add these ! \u037E\u0589\u061F\u06D4\u0700-\u0702\u07FA\u3002]

    ABBREV3 = (
              /ca/i
            | /fig/i [sS]?
            | /prop/i
            | /no/i [sS]? 
            | /art/i
            | /bldg/i
            | /pp/i
            | /op/i
        ) ".";

    PHONE = (
                  "("[0-9]{2,3}")" (" "| 0xC2 0xA0)? 
                | ("+""+"?)? ([0-9]{2,4}( "-" | " " | 0xC2 0xA0))?[0-9]{2,4}
                  ("-" | " "| 0xC2 0xA0)
            ) [0-9]{3,4} ("-" | " "| 0xC2 0xA0)? [0-9]{3,5}
            | (("+""+"?)?[0-9]{2,4}".")?[0-9]{2,4}"."[0-9]{3,4}"."[0-9]{3,5};

    FAKEDUCKFEET = "<<" | ">>" ;
    LESSTHAN = "<"|"&lt;";
    GREATERTHAN = ">"|"&gt;";
    #HYPHEN = [-_\u058A\u2010\u2011] defined above
    HYPHENS = "-"+;
#    LDOTS = "."{3,5}
#        | ("." (" " | 0xC2 0xA0)){2,4} "."
       # | 0xC2 0x85 # u+0085 TODO: check if this is newline or hypen
#        | 0xE2 0x80 0x81 ; # u+2026

#    ATS = "@"+;
#    UNDS = "_"+;
#    ASTS = "*"+ | ("\\*"){1,3} ;
#    HASHES = "#"+;
#    FNMARKS = ATS|HASHES|UNDS;

    INSENTP = [,;:] | 0xE3 0x80 0x81; # u+3001
    QUOTES = APOS 
        | "''"
        | 
            ( 
                  "`"
                | 0xE2 0x80 0x98..0x9D # u+2018 .. u+201D
                | 0xC2 0x91..0x94 # u+0091 .. u+0094
                | 0xE2 0x80 0x9E # u+201E
                | 0xE2 0x80 0x9F #u+201F
                | 0xE2 0x80 0xB9 # u+2039
                | 0xE2 0x80 0xBA # u+203A
                | 0xC2 0xAB # u+00AB
                | 0xC2 0xBB # u+00BB
            ){1,2} ;

    DBLQUOT = "\""|"&quot;";
    #/* Cap'n for captain, c'est for french */
    TBSPEC = "-" (/RRB/i|/LRB/i|/RCB/i|/LCB/i|/RSB/i|/LSB/i)"-"
        | /C.D.s/i 
        | /pro-/i
        | /anti-/i 
        | [Ss] ("&" | "&amp;") [Pp]"-500"
        | [Ss] ("&"|"&amp;") /Ls/i
        | /Cap/i APOS [Nn]
        | [Cc] APOS /est/i;
    TBSPEC2 = APOS [0-9][0-9];
    BANGWORDS = ("E"|/Yahoo/i|/Jeopardy/i) "!";
 
    all_word = SPMDASH|
          SPAMP
        | SPPUNC
        | SPLET
        | DIGIT
        | DATE
        | NUM
        | NUMBER
        | SUBSUPNUM

        | FRAC | FRACSTB3 | FRAC2 | DOLSIGN | DOLSIGN2

        | WORD 
        | FILENAME
        | REDAUX
        | INSENTP | PUNC | DBLQUOT |TBSPEC | TBSPEC2 | BANGWORDS | QUOTES 
        | PHONE | ABBREV3;
       # | FNMARKS | ASTS |HYPHEN | HYPHENS | FAKEDUCKFEET 
       # | GREATERTHAN | LESSTHAN;


 
    SMILEY = [<>]? [:;=] [\-o\*']? [\(\)DPdpO\\{@\|\[\]]  ;  
#ASIANSMILEY = [\^x=~<>]\.\[\^x=~<>]|[\-\^x=~<>']_[\-\^x=~<>']|\([\-\^x=~<>'][_.]?[\-\^x=~<>']\)|\([\^x=~<>']-[\^x=~<>'`]\)



    MISCSYMBOL = 
          [+%&~\^\|\\]         
        | 0xC2 0xA6
        | 0xC2 0xA7 
        | 0xC2 0xA8
        | 0xC2 0xA9
        | 0xC2 0xAC
        | 0xC2 0xAE
        | 0xC2 0xAF
        | 0xC2 0xB0..0xB3 # u+00B0 .. u+00B3
        | 0xC2 0xB4..0xBA # u+00B4 .. u+00BA
        | 0xC3 0x97 # u+00D7
        | 0xC3 0xB7 # u+00F7
        | 0xCE 0x87 # u+0387
        | 0xD6 0xBE # u+05BE
        | 0xD7 0x80 # u+05C0
        | 0xD7 0x83 # u+05C3
        | 0xD7 0x86 # u+05C6
        | 0xD7 0xB3 # u+05F3
        | 0xD7 0xB4 # u+05F4
        | 0xD8 0x80..0x83 # u+0600 .. u+0603
        | 0xD8 0x86..0x8A # u+0606 .. u+060A
        | 0xD8 0x8C # u+060C 
        | 0xD8 0x94 # u+0614
        | 0xD8 0x9B # u+061B
        | 0xD8 0x9E # u+061E
        | 0xD9 0xAA # u+066A
        | 0xD9 0xAD # u+066D
        | 0xDC 0x83..0x8D # u+0703 .. u+070D
        | 0xDF 0xB6 # u+07F6
        | 0xDF 0xB7 # u+07F7
        | 0xDF 0xB8 # u+07F8
        | 0xE0 0xA5 0xA4 # u+0964
        | 0xE0 0xA5 0xA5 # u+0965
        | 0xE0 0xB9 0x8F # u+0E4F
        | 0xE1 0xBE 0xBD # u+1FBD
        | 0xE2 0x80 0x96 # u+2016
        | 0xE2 0x80 0x97 # u+2017
        | 0xE2 0x80 0xA0..0xA3 # u+2020 .. u+2023
        | 0xE2 0x80 0xB0..0xB8 # u+2030 .. u+2038 
        | 0xE2 0x80 0xBB # u+203B 
        | 0xE2 0x81 0x83 # u+2043 
        | 0xE2 0x80 0xBE..0xFF # u+203E .. u+2042
        | 0xE2 0x81 0x00..0x82
        | 0xE2 0x81 0x84 # u+2044 
        | 0xE2 0x81 0xBA..0xBF # u+207A .. u+207F
        | 0xE2 0x82 0x8A..0x8E # u+208A .. u+208E 
        | 0xE2 0x84 0x80..0xFF # u+2100 .. u+214F
        | 0xE2 0x85 0x00..0x8F
        | 0xE2 0x86 0x90..0xBF # u+2190 .. u+21FF
        | 0xE2 0x87 0x80..0xBF
        | 0xE2 0x88 0x80..0xBF # u+2200 .. u+2bFF
        | 0xE2 0x89 0x80..0xBF
        | 0xE2 (0x89..0xAE ) 0x00..0xBF
        | 0xE2 0xAF 0x00..0xBF
        | 0xE3 0x80 0x92 # u+3012
        | 0xE3 0x83 0xBB # u+30FB
        | 0xEF 0xBC 0x81..0x8F # u+FF01 .. u+FF0F
        | 0xEF 0xBC 0x9A..0xA0 # u+FF1A .. FF20
    | 0xEF 0xBC 0xBB..0xFF   # u+FF3B .. u+FF40
    | 0xEF 0xBD 0x00..0x80   
    | 0xEF 0xBD 0x9B..0xA5 ; # u+FF5B .. u+FF65

action NextToken {
    if (span_pos == BUFSIZE) {
        __token_list *next_slab = NL_allocate_mem_size(mgr, sizeof(__token_list));
        next_slab->next = NULL;  
        next_slab->tokens = NL_allocate_mem_size(mgr, sizeof(NL_span *) * BUFSIZE);
        tail->next = next_slab;
        tail = tail->next;
        num_lists++;
        span_pos = 0;
        tokens = next_slab->tokens;
    }
    tokens[span_pos++] = NL_new_span(ts, te - ts, mgr);
}
#
#action NormalizedAmpNext {
#    if (span_pos == max_span_pos) {
#        max_span_pos = max_span_pos * 2;
#        tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#        if (tokens == NULL) {
#            return;
#        }
#        //printf("%d spans allocated\n", max_span_pos);
#    }
#    tokens[span_pos] = NLPC_new_span(ts, te);
#    if (config->normalizeAmpersandEntity) {
#        NL_add_label(
#            tokens[span_pos], (unsigned char*)"NORM", (unsigned char *) "&");
#    } 
#    span_pos++;
#}
#
#action NormalizedLRBNext {
#    if (span_pos == max_span_pos) {
#        max_span_pos = max_span_pos * 2;
#        tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#        if (tokens == NULL) {
#            return;
#        }
#        //printf("%d spans allocated\n", max_span_pos);
#    }
#    tokens[span_pos] = NLPC_new_span(ts, te);
#    if (config->normalizeParentheses) {
#        NL_add_label(
#            tokens[span_pos], (unsigned char*)"NORM", (unsigned char *) "-LRB-");
#    } 
#    span_pos++;
#}
#
#action NormalizedRRBNext {
#    if (span_pos == max_span_pos) {
#        max_span_pos = max_span_pos * 2;
#        tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#        if (tokens == NULL) {
#            return;
#        }
#        //printf("%d spans allocated\n", max_span_pos);
#    }
#    tokens[span_pos] = NLPC_new_span(ts, te);
#    if (config->normalizeParentheses) {
#        NL_add_label(
#            tokens[span_pos], (unsigned char*)"NORM", (unsigned char *) "-RRB-");
#    } 
#    span_pos++;
#}
#
#
#action MarkIntermediate1 {
#    //printf("marking1!\n");
#    ti1 = fpc;    
#}
#
#action NextIntermediate1 {
#    if (span_pos == max_span_pos) {
#        max_span_pos = max_span_pos * 2;
#        tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#        //printf("%d spans allocated\n", max_span_pos);
#    }
#    tokens[span_pos++] = NLPC_new_span(ts, ti1);
#    ts = ti1;
#    fpc = ti1 - 1;
#    te = '\0';
#}
#
#action MarkIntermediate2 {
#    //printf("marking2!\n");
#    ti2 = fpc;    
#}
#
#action NextIntermediate2 {
#    if (span_pos == max_span_pos) {
#        max_span_pos = max_span_pos * 2;
#        tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#        //printf("%d spans allocated\n", max_span_pos);
#    }
#    tokens[span_pos++] = NLPC_new_span(ts, ti2);
#    ts = ti2;
#    fpc = ti2 - 1;
#    te = '\0';
#}
#
#
#action NextTwoTokens {
#    if (span_pos == max_span_pos) {
#        max_span_pos = max_span_pos * 2;
#        tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#        //printf("%d spans allocated\n", max_span_pos);
#    }
#    tokens[span_pos++] = NLPC_new_span(ts, ti);
#
#    if (span_pos == max_span_pos) {
#        max_span_pos = max_span_pos * 2;
#        tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#        //printf("%d spans allocated\n", max_span_pos);
#    }
#    tokens[span_pos++] = NLPC_new_span(ti, te);
#
#}
#
#action SplitAssimilation3 {
#
#    if (config->splitAssimilations) {
#        if (span_pos == max_span_pos) {
#            max_span_pos = max_span_pos * 2;
#            tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#            //printf("%d spans allocated\n", max_span_pos);
#        }
#
#        tokens[span_pos++] = NLPC_new_span(ts, ts + 3);
#        if (span_pos == max_span_pos) {
#            max_span_pos = max_span_pos * 2;
#            tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#            //printf("%d spans allocated\n", max_span_pos);
#        }
#
#        tokens[span_pos++] = NLPC_new_span(ts + 3, te);
#        
#    } else {
#        if (span_pos == max_span_pos) {
#            max_span_pos = max_span_pos * 2;
#            tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#            //printf("%d spans allocated\n", max_span_pos);
#        }
#
#        tokens[span_pos++] = NLPC_new_span(ts, te);
#    }
#
#}
#
#action SplitAssimilation2 {
#
#    if (config->splitAssimilations) {
#        if (span_pos == max_span_pos) {
#            max_span_pos = max_span_pos * 2;
#            tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#            //printf("%d spans allocated\n", max_span_pos);
#        }
#
#        tokens[span_pos++] = NLPC_new_span(ts, ts + 2);
#        if (span_pos == max_span_pos) {
#            max_span_pos = max_span_pos * 2;
#            tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#            //printf("%d spans allocated\n", max_span_pos);
#        }
#
#        tokens[span_pos++] = NLPC_new_span(ts + 2, te);
#        
#    } else {
#        if (span_pos == max_span_pos) {
#            max_span_pos = max_span_pos * 2;
#            tokens = realloc(tokens, sizeof(NLPC_span *) * max_span_pos);
#            //printf("%d spans allocated\n", max_span_pos);
#        }
#
#        tokens[span_pos++] = NLPC_new_span(ts, te);
#    }
#
#}

    main := |*
        [cC]"++" => NextToken;
        ([cC] | [fF] ) "#" => NextToken;

#        (/cannot/i | /gonna/i | /gotta/i 
#            | /lemme/i | /gimme/i | /wanna/i)  => SplitAssimilation3;
#
#        (/'twas/i 
#            | /'tis/i) => SplitAssimilation2;                   
#
        SGML => NextToken;
#        "cont'd" => NextToken; # needed to break a weird tie between word 
#                               # and apoword
#
#        SPMDASH => NextToken;
#        SPAMP =>  NormalizedAmpNext; #  NextToken; # missing transform
#
#        WORD %MarkIntermediate2 REDAUX => NextIntermediate2;
#        SWORD %MarkIntermediate1 SREDAUX => NextIntermediate1;
#
        WORD => NextToken;
#
#        APOWORD => NextToken;
#        APOWORD2 %MarkIntermediate2 ualpha => NextIntermediate2;
#
#        TWITTER => NextToken;
#        REDAUX %MarkIntermediate2 [^A-Za-z] => NextIntermediate2;
#        SREDAUX %MarkIntermediate1 [^A-Za-z] => NextIntermediate1;
#
#        DATE => NextToken;
#
#        NUMBER => NextToken;
#        SUBSUPNUM => NextToken;
#
#        FRAC => NextToken;
#        FRAC2 => NextToken;
#
#        TBSPEC => NextToken;
#        BANGWORDS => NextToken;
#
#        THING3 => NextToken;
#
#        DOLSIGN => NextToken;
#        DOLSIGN2 => NextToken;
#
#
#        ABBREV3 %MarkIntermediate1 SPACENL? udigit => NextIntermediate1;
#        (/pt/i [eyEY] | /co/i)"." 
#            %MarkIntermediate1 SPACE (/ltd/i|/lim/i) => NextIntermediate1; 
#
#        #ABBREV1 /SENTEND 
#        ABBREV1 %MarkIntermediate2 any any => NextIntermediate2;        
#        ABBREV1 => NextToken;
#        ABBREV2 => NextToken;
#
#        ABBREV4 %MarkIntermediate2 SPACE => NextIntermediate2;
#
#        ACRO %MarkIntermediate2 SPACENL => NextIntermediate2;
#
#        TBSPEC2 %MarkIntermediate2 SPACENL => NextIntermediate2;
#
#        FILENAME %MarkIntermediate2 (SPACENL|[.?!,]) => NextIntermediate2;
#        WORD "." %MarkIntermediate2 INSENTP => NextIntermediate2;
#        PHONE => NextToken;
#        
#        DBLQUOT => NextToken;
#        
#
#        GREATERTHAN => NextToken;
#        LESSTHAN => NextToken;
#
#
#
#
#
#        "{" => NextToken;
#        "}" => NextToken;
#        "[" => NextToken;
#        "]" => NextToken;
#        "(" => NormalizedLRBNext;
#        ")" => NormalizedRRBNext;
#
#        HYPHENS => NextToken;
#        #LDOTS => NextToken;
#        #FNMARKS => NextToken;         
#        #ASTS => NextToken;
#
#        INSENTP => NextToken;
#        [?!]+ => NextToken;
#
        "." => NextToken; # add other sentence final punc and add a test.
#
#        "="+ => NextToken;
#
#        "/" => NextToken;
#
#        REDAUX => NextToken;
#        SREDAUX => NextToken;
#
#
##        WORD => NextToken;
##        FILENAME => NextToken;
#        #test THINGs ?
##        APOWORD2 => NextToken;
##        FULLURL => NextToken;
##        LIKELYURL => NextToken;
##        TWITTER => NextToken;
##        ABBREV1 => NextToken;
##        ABBREV2 => NextToken;
##        ACRONYM => NextToken;
# #       EMAIL => NextToken;
#     #   all_word => NextToken;
#
##        MISCSYMBOL => NextToken;
##        SMILEY => NextToken;
#        #LDOTS => NextToken;
        SPACES;
        SPACENLS;
        0xEF 0xBB 0xBF => {printf("I found a byte order mark!\n");};
        any; # => { printf("the uncola: 0x%02X\n", (unsigned int)  *ts); };
    *|;

#main := |*
#    [^ \n]+ => NextToken; 
#    any;
#    *|;
}%%

%% write data nofinal;

#define BUFSIZE 4


NL_span **NL_tokenize_buf(unsigned char *buf, size_t buf_len, 
        size_t *num_tokens, NL_PTBTokConfig *cfg, NL_v_memmgr *mgr) {

    __token_list *head = NL_allocate_mem_size(mgr, sizeof(__token_list));
    __token_list *tail = head;
    size_t num_lists = 1;

    NL_span **tokens = NL_allocate_mem_size(mgr, sizeof(NL_span *) * BUFSIZE);
    head->tokens = tokens;

    int span_pos = 0;
    int max_span_pos = BUFSIZE;

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *ti1 = 0;
    unsigned char *ti2 = 0;
    unsigned char *p = buf;  
    unsigned char *pe = p + buf_len; 
    unsigned char *eof = pe;
    %% write init;

    %% write exec;

    *num_tokens = BUFSIZE * (num_lists - 1) + span_pos;
    NL_span **out_tokens = NL_allocate_mem_size(
        mgr, sizeof(NL_span *) * (*num_tokens));
    NL_span **current_out = out_tokens;
    
    __token_list *next;

    for (;head; head=next) {
        if (head->next == NULL) {
            memcpy(current_out, head->tokens, span_pos * sizeof(NL_span*));
        } else {
            memcpy(current_out, head->tokens, BUFSIZE * sizeof(NL_span*));
            current_out = &current_out[BUFSIZE] ;
        }

        NL_deallocate_v_mem(mgr, head->tokens);
        next = head->next;
        NL_deallocate_v_mem(mgr, head);

    }


    return out_tokens;

}
