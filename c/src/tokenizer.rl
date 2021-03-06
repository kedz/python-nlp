#include "tokenizer.h"
#include "stdio.h"
#include <string.h>
#include "tokenizer_utils.h"

%%{

    machine tok;
    alphtype unsigned char;

    include WChar "unicode.rl";

    action AlertSoftHyphen {
        alert_soft_hyphen++;
    }

    SGML = "<" (
          ("!"| "?") [A-Za-z\-] [^>\r\n]*
        | [A-Za-z] [A-Za-z0-9_:.\-]*
          ([ ]+ (
              [A-Za-z][A-Za-z0-9_:.\-]*
            |
              [A-Za-z][A-Za-z0-9_:.\-]*[ ]*"="[ ]*
              (   "'" [^']* "'" 
                | "\"" [^"]* "\"" 
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

    ALL_SPACES =      SPACES 
                    | 0xE2 0x80 0x8B  # U+200B zero width space
                    | 0xE2 0x80 0x8E  # U+200E left-to-right mark
                    | 0xE2 0x80 0x8F  # U+200F right-to-left mark
                    | 0xEF 0xBB 0xBF  # U+FEFF zero width no-break space
                    ;

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
    SENTEND = SPACENL (SPACENL | upper | SGML);
    #

    DIGIT = udigit | 0xDF 0x80..0x89 ;

    DATE = DIGIT {1,2} [\-\/] DIGIT {1,2} [\-\/] DIGIT {2,4};

    NUM = DIGIT+ 
        | DIGIT* ( ("."|":"|","|0xC2 0xAD %AlertSoftHyphen |0xD9 0xAB|0xD9 0xAC) DIGIT+ )+;

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

    DOLSIGN2_NORM =   0xC2 0x80 # u+0080 
                    | 0xC2 0xA4 # u+00A4 
                    | 0xE2 0x82 0xA0 # u+20A0 
                    | 0xE2 0x82 0xAC # u+20AC 
                    ;
    DOLSIGN2_CENTS = 0xC2 0xA2 ; # u+00A2 
    DOLSIGN2_POUNDS = 0xC2 0xA3 ; # u+00A3

    DOLSIGN2 =    0xC2 0xA5 # u+00A5 
                | 0xD8 0x8B # u+060B 
                | 0xE0 0xB8 0xBF # u+0E3F 
                | 0xE2 0x82 0xA4 # u+20A4 
                | 0xEF 0xBF 0xA0 # u+FFE0 
                | 0xEF 0xBF 0xA1 # u+FFE1 
                | 0xEF 0xBF 0xA5 # u+FFE5 
                | 0xEF 0xBF 0xA6 # u+FFE6 
                ;

    LETTER = ualpha | SPLET  # TODO Make sure this matches stanford
        | 0xC2 0xAD %AlertSoftHyphen # u+00AD
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
    THINGA = [A-Z]+ ( ("+" | "&" | SPAMP %{ num_amps++; } ) [A-Z]+ )+ ;
    THING3 = [A-Za-z0-9]+ ("-" [A-Za-z]+ ){0,2} 
        ( "\\"? "/" [A-Za-z0-9]+ ("-" [A-Za-z]+ ){0,2} ){1,2} ;

    HTHING = [A-Za-z0-9] ( [A-Za-z0-9.,] | 0xC2 0xAD %AlertSoftHyphen )*
             ( 
                "-" (([A-Za-z0-9] | 0xC2 0xAD %AlertSoftHyphen)+ | ACRO2 ".")
             )+ ;
    REDAUX = APOS ( [msdMSD] | /re/i | /ve/i | /ll/i );

    SWORD = ( [A-Za-z] | 0xC2 0xAD )* [A-MO-Za-mo-z] ( 0xC2 0xAD )* ;
    SREDAUX = [Nn] APOSETCETERA [Tt] ;

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
#o
 
#EMAIL = (&lt;|<)?[a-zA-Z0-9][^ \t\n\f\r\"<>|()\u00A0{}]*@([^ \t\n\f\r\"<>|(){}.\u00A0]+\.)*([^ \t\n\f\r\"<>|(){}.\u00A0]+)(&gt;|>)?


   EMAIL = ("&lt;"|"<")? [a-zA-Z0-9] [^ \t\n\f\r"<>|(){}]* 
        '@'
        ([^ \t\n\f\r"<>|(){}.]+ '.')*
        ([^ \t\n\f\r"<>|(){}.]+) ('&gt;'|'>')?
        ;
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


    SENT_END_PUNC = "." | [?!]+ ;
    PUNC =    "¡"
            | "¿"  
            | 0xCD 0xBE # U+037E
            | 0xD6 0x89 # U+0589
            | 0xD8 0x9F # U+061F
            | 0xDB 0x94 # U+06D4
            | 0xDC 0x80 # U+0700-U+0702
            | 0xDC 0x81
            | 0xDC 0x82
            | 0xDF 0xBA # U+07FA
            | 0xE3 0x80 0x82 # U+3002
            ;

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
    LDOTS = "."{3,5}
        | ("." (" " | 0xC2 0xA0)){2,4} "."
        | 0xE2 0x80 0xA6 ; # u+2026
       # | 0xC2 0x85 # u+0085 I disagree with corenlp that this should be here

    ATS = "@"+;
    UNDS = "_"+;
    HASHES = "#"+;
    FNMARKS = ATS|HASHES|UNDS;
    ASTS = "*"+ | ("\\*"){1,3} ;

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

    DBLQUOT = "\""|"&quot;"; #THIS IS HOW STANFORD DOES IT
    #/* Cap'n for captain, c'est for french */
    TBSPEC = "-" (/RRB/i|/LRB/i|/RCB/i|/LCB/i|/RSB/i|/LSB/i)"-"
        | /C.D.s/i 
        | /pro-/i
        | /anti-/i 
        | [Ss] "&" [Pp]"-500"
        | [Ss] "&" /Ls/i
        | /Cap/i APOS [Nn]
        | [Cc] APOS /est/i;

    TBSPEC_SampP = [Ss] "&amp;" [Pp] "-500";
    TBSPEC_SampLs = [Ss] "&amp;" /Ls/i;

    TBSPEC2 = APOS [0-9][0-9];
    BANGWORDS = ("E"|/Yahoo/i|/Jeopardy/i) "!";
    BANGMAGAZINES = /ok/i "!";
 
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


 
    SMILEY = [<>]? [:;=] [\-o\*']? 
        ("(" | ")" | "D" | "d" |"P" | "p" | "O" | "\\" | "{" 
             | "@" | "|" |"["| "]" ); #  [()DPdpO\\{@|\[\]]  ;  
#ASIANSMILEY = [\^x=~<>]\.\[\^x=~<>]|[\-\^x=~<>']_[\-\^x=~<>']|\([\-\^x=~<>'][_.]?[\-\^x=~<>']\)|\([\^x=~<>']-[\^x=~<>'`]\)
    ASIANSMILEY = [\^x=~<>]"."[\^x=~<>] 
                | [\-\^x=~<>']"_"[\-\^x=~<>']
                | "("[\-\^x=~<>'][_.]?[\-\^x=~<>']")"
                | "("[\^x=~<>']"-"[\^x=~<>'`]")";


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
    NEXT_TOKEN    
}

action NextTokenSentEnd {
    NL_add_bspan(mgr, ann, ts, te - ts, NULL, NL_SENT_END_FLAG);
}


action SplitAssimilation3 {
    if (split_assimilations == 1) {
        SPLIT_ASSIM(3)
    } else {
        NEXT_TOKEN
    }
}

action SplitAssimilation2 {
    if (split_assimilations == 1) {
        SPLIT_ASSIM(2)
    } else {
        NEXT_TOKEN
    }
}
action NormalizePTB3MDash {
    if (normalize_ptb3_dashes == 1) {
        NL_add_bspan(mgr, ann, ts, te - ts, &ptb3dash, 0);
    } else {
        NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
    }
}

action NormalizeAmp {
    if (normalize_amp == 1) {
        NL_add_bspan(mgr, ann, ts, te - ts, &amp, 0);
    } else {
        NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
    }
}

action ConvertAmp {
    if (normalize_amp == 1 && num_amps > 0) {
        size_t size = te - ts - 4 * num_amps;
        NL_string *norm = NL_new_string(mgr, size);
        NL_normalize_ampersand(ts, te - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);
        num_amps = 0;
    } else {
        NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
    }
}

action MarkIntermediate1 {
    ti1 = fpc;    
}

action MarkIntermediate2 {
    ti2 = fpc;    
}

action NextIntermediate1 {
    
    if (alert_soft_hyphen > 0) {                                            
        size_t size = ti1 - ts - alert_soft_hyphen * 2;             
        if (size > 1) {                                               
            NL_string *norm = NL_new_string(mgr, size);
            NL_copy_no_softhyphen(ts, ti1 - ts, norm->bytes);                  
            NL_add_bspan(mgr, ann, ts, ti1 - ts, (void *) norm, NL_OWN_DATA); 
        } else {                                                            
            NL_string *norm = NL_new_string(mgr, 1);
            norm->bytes[0] = '-';
            NL_add_bspan(mgr, ann, ts, ti1 - ts, (void *) norm, NL_OWN_DATA); 
        }                                                                   
    } else {
        NL_add_bspan(mgr, ann, ts, ti1 - ts, NULL, 0); 
    }

    alert_soft_hyphen = 0;
    ts = ti1;                                            
    fpc = ti1 - 1;                                       
    te = '\0';                                           
}

action NextIntermediate2 {

    if (alert_soft_hyphen > 0) {                                            
        size_t size = ti2 - ts - alert_soft_hyphen * 2;             
        if (size > 1) {                                               
            NL_string *norm = NL_new_string(mgr, size);
            NL_copy_no_softhyphen(ts, ti2 - ts, norm->bytes);                  
            NL_add_bspan(mgr, ann, ts, ti2 - ts, (void *) norm, NL_OWN_DATA); 
        } else {                                                            
            NL_string *norm = NL_new_string(mgr, 1);
            norm->bytes[0] = '-';
            NL_add_bspan(mgr, ann, ts, ti2 - ts, (void *) norm, NL_OWN_DATA); 
        }                                                                   
    } else {
        NL_add_bspan(mgr, ann, ts, ti2 - ts, NULL, 0); 
    }

    alert_soft_hyphen = 0;
    ts = ti2;                                            
    fpc = ti2 - 1;                                       
    te = '\0';                                           
}

action NextIntermediateHandleProbablyLeftQuotes1 {

    if (normalize_quotes == QUOTES_LATEX) {
        size_t size NL_get_size_latex_quotes(ts, ti1 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_latex_quotes_probably_left(ts, ti1 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti1 - ts, norm, NL_OWN_DATA); 
    } else if (normalize_quotes == QUOTES_UNICODE) {
        size_t size = NL_get_size_unicode_quotes(ts, ti1 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_unicode_quotes_probably_left(ts, ti1 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti1 - ts, norm, NL_OWN_DATA); 
    } else if (normalize_quotes == QUOTES_ASCII) {
        size_t size = NL_get_size_ascii_quotes(ts, ti1 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_ascii_quotes(ts, ti1 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti1 - ts, norm, NL_OWN_DATA); 
    } else {
        NL_add_bspan(mgr, ann, ts, ti1 - ts, NULL, 0); 
    }
    alert_soft_hyphen = 0;
    ts = ti1;                                            
    fpc = ti1 - 1;                                       
    te = '\0';                                           
}

action NextIntermediateHandleProbablyRightQuotes1 {


    if (normalize_quotes == QUOTES_LATEX) {
        size_t size = NL_get_size_latex_quotes(ts, ti1 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_latex_quotes_probably_right(ts, ti1 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti1 - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else if (normalize_quotes == QUOTES_UNICODE) {
        size_t size = NL_get_size_unicode_quotes(ts, ti1 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_unicode_quotes_probably_right(ts, ti1 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti1 - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else if (normalize_quotes == QUOTES_ASCII) {
        size_t size = NL_get_size_ascii_quotes(ts, ti1 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_ascii_quotes(ts, ti1 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti1 - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else {
        NL_add_bspan(mgr, ann, ts, ti1 - ts, NULL, NL_SENT_INC); 
    }
    alert_soft_hyphen = 0;
    ts = ti1;                                            
    fpc = ti1 - 1;                                       
    te = '\0';                                           
}


action NextIntermediateHandleProbablyLeftQuotes2 {


    if (normalize_quotes == QUOTES_LATEX) {
        size_t size = NL_get_size_latex_quotes(ts, ti2 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_latex_quotes_probably_left(ts, ti2 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti2 - ts, norm, NL_OWN_DATA); 
    } else if (normalize_quotes == QUOTES_UNICODE) {
        size_t size = NL_get_size_unicode_quotes(ts, ti2 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_unicode_quotes_probably_left(ts, ti2 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti2 - ts, norm, NL_OWN_DATA); 
    } else if (normalize_quotes == QUOTES_ASCII) {
        size_t size = NL_get_size_ascii_quotes(ts, ti2 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_ascii_quotes(ts, ti2 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti2 - ts, norm, NL_OWN_DATA); 
    } else {
        NL_add_bspan(mgr, ann, ts, ti2 - ts, NULL, 0); 
    }
    alert_soft_hyphen = 0;
    ts = ti2;                                            
    fpc = ti2 - 1;                                       
    te = '\0';                                           
}

action NextIntermediateHandleProbablyRightQuotes2 {

    if (normalize_quotes == QUOTES_LATEX) {
        size_t size = NL_get_size_latex_quotes(ts, ti2 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_latex_quotes_probably_right(ts, ti2 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti2 - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else if (normalize_quotes == QUOTES_UNICODE) {
        size_t size = NL_get_size_unicode_quotes(ts, ti2 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_unicode_quotes_probably_right(ts, ti2 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti2 - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else if (normalize_quotes == QUOTES_ASCII) {
        size_t size = NL_get_size_ascii_quotes(ts, ti2 - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_ascii_quotes(ts, ti2 - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, ti2 - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else {
        NL_add_bspan(mgr, ann, ts, ti2 - ts, NULL, NL_SENT_INC); 
    }
    alert_soft_hyphen = 0; 
    ts = ti2;                                            
    fpc = ti2 - 1;                                       
    te = '\0';                                           
}


action HandleQuotesProbablyRight {

    if (normalize_quotes == QUOTES_LATEX) {
        size_t size = NL_get_size_latex_quotes(ts, te - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_latex_quotes_probably_right(ts, te - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, te - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else if (normalize_quotes == QUOTES_UNICODE) {
        size_t size = NL_get_size_unicode_quotes(ts, te - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_unicode_quotes_probably_right(ts, te - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, te - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else if (normalize_quotes == QUOTES_ASCII) {
        size_t size = NL_get_size_ascii_quotes(ts, te - ts);
        NL_string *norm = NL_new_string(mgr, size);
        NL_ascii_quotes(ts, te - ts, norm->bytes);
        NL_add_bspan(mgr, ann, ts, te - ts, norm, NL_OWN_DATA | NL_SENT_INC); 
    } else {
        NL_add_bspan(mgr, ann, ts, te - ts, NULL, NL_SENT_INC); 

    }

}

    action TokenizeNewline {
        if (tokenize_newlines == 1) {
            NL_add_bspan(mgr, ann, ts, te - ts, &newline_token, 0);
        }
    }

    action EscapeForwardSlashAsterisk {
        if (escape_forward_slash_asterisk == 1) {
            size_t size = NL_get_size_escaped_forward_slash_asterisk(
                ts, te - ts);
            NL_string *norm = NL_new_string(mgr, size);
            NL_escape_forward_slash_asterisk(ts, te - ts, norm->bytes);
            NL_add_bspan(mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);
        } else {
            NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
        }
    }

    action HandleEllipsis {
        if (normalize_ellipsis == ELLIPSIS_PTB3) {
            NL_add_bspan(mgr, ann, ts, te - ts, &ptb3_ellipsis_label, 0);
        } else if (normalize_ellipsis == ELLIPSIS_UNICODE) {
            NL_add_bspan(mgr, ann, ts, te - ts, &uni_ellipsis_label, 0);
        } else {
            NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
        }
    }

    action NormalizeLCBNext { 
        if (normalize_brackets == 1) {
            NL_add_bspan(mgr, ann, ts, te - ts, &lcb_label, 0);
        } else {
            NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
        }
    }

    action NormalizeRCBNext { 
        if (normalize_brackets == 1) {
            NL_add_bspan(mgr, ann, ts, te - ts, &rcb_label, NL_SENT_INC);
        } else {
            NL_add_bspan(mgr, ann, ts, te - ts, NULL, NL_SENT_INC);
        }
    }

    action NormalizeLSBNext { 
        if (normalize_brackets == 1) {
            NL_add_bspan(mgr, ann, ts, te - ts, &lsb_label, 0);
        } else {
            NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
        }
    }

    action NormalizeRSBNext { 
        if (normalize_brackets == 1) {
            NL_add_bspan(mgr, ann, ts, te - ts, &rsb_label, NL_SENT_INC);
        } else {
            NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
        }
    }

    action NormalizeLRBNext { 
        if (normalize_brackets == 1) {
            NL_add_bspan(mgr, ann, ts, te - ts, &lrb_label, 0);
        } else {
            NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
        }
    }

    action NormalizeRRBNext { 
        if (normalize_brackets == 1) {
            NL_add_bspan(mgr, ann, ts, te - ts, &rrb_label, NL_SENT_INC);
        } else {
            NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
        }
    }

    main := |*
        [cC]"++" => NextToken;
        ([cC] | [fF] ) "#" => NextToken;

        (/cannot/i | /gonna/i | /gotta/i 
            | /lemme/i | /gimme/i | /wanna/i)  => SplitAssimilation3;

        (/'twas/i 
            | /'tis/i) => SplitAssimilation2;                   

        SGML => {
            if (normalize_spaces == 1) {
                size_t size = NL_get_size_normalized_spaces(
                    ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_normalize_spaces(ts, te - ts, norm->bytes);
                NL_add_bspan(mgr, ann, ts, te - ts, 
                    (void *) norm, NL_OWN_DATA);
            } else {
                NEXT_TOKEN
            }
        };

        # needed to break a weird tie between word and apoword
        "cont'd" => HandleQuotesProbablyRight; 

        SPMDASH => NormalizePTB3MDash;
        SPAMP =>  NormalizeAmp; 
        SPPUNC => NextToken;
        WORD %MarkIntermediate2 REDAUX => NextIntermediate2;
        SWORD %MarkIntermediate1 SREDAUX => NextIntermediate1;
        WORD => NextToken;

        APOWORD => HandleQuotesProbablyRight;
        APOWORD2 %MarkIntermediate2 ualpha => NextIntermediate2;

 #       FULLURL => NextToken; # TODO add escaping for these
 #       LIKELYURL => NextToken;
  #      EMAIL => NextToken; # TODO: can't get this to work

        TWITTER => NextToken;
        REDAUX %MarkIntermediate2 [^A-Za-z] => 
            NextIntermediateHandleProbablyRightQuotes2;
        SREDAUX %MarkIntermediate1 [^A-Za-z] => 
            NextIntermediateHandleProbablyRightQuotes1;

        DATE => NextToken; #TODO escape slashes
        NUMBER => NextToken;
        SUBSUPNUM => NextToken;

        FRAC => {
            if (normalize_spaces == 1 && escape_forward_slash_asterisk == 1) {
                size_t size = NL_get_size_normalized_spaces_slashes(
                    ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_normalize_parens_slashes(ts, te - ts, norm->bytes);
                NL_add_bspan(mgr, ann, ts, te - ts, norm, NL_OWN_DATA);
            } else if (normalize_spaces == 1) {
                size_t size = NL_get_size_normalized_spaces(
                    ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_normalize_spaces(ts, te - ts, norm->bytes);
                NL_add_bspan(mgr, ann, ts, te - ts, norm, NL_OWN_DATA);
            } else if (escape_forward_slash_asterisk == 1) {
                size_t size = 
                    NL_get_size_escaped_forward_slash_asterisk(ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_escape_forward_slash_asterisk(ts, te - ts, norm->bytes);
                NL_add_bspan(mgr, ann, ts, te - ts, norm, NL_OWN_DATA);
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }

        };

        ### FRAC2 patterns ###
        0xC2 0xBC => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &one_fourth_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts, 
                        &one_fourth_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xC2 0xBD => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &one_half_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts, 
                        &one_half_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xC2 0xBE => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &three_fourths_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts, 
                        &three_fourths_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x93 => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &one_third_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts, 
                        &one_third_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x94 => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &two_thirds_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts,
                        &two_thirds_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x95 => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &one_fifth_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts,
                        &one_fifth_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x96 => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &two_fifths_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts,
                        &two_fifths_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x97 => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &three_fifths_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts,
                    &three_fifths_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x98 => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &four_fifths_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts, &four_fifths_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x99 => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &one_sixth_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts,
                        &one_sixth_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x9A => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &five_sixths_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts,
                        &five_sixths_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x9B => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &one_eighth_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts, &one_eighth_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x9C => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &three_eighths_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts,
                        &three_eighths_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x9D => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &five_eighths_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts,
                        &five_eighths_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        0xE2 0x85 0x9E => {
            if (normalize_fractions == 1) {
                if (escape_forward_slash_asterisk == 0) {
                    NL_add_bspan(mgr, ann, ts, te - ts, &seven_eighths_label, 0);
                } else {
                    NL_add_bspan(mgr, ann, ts, te - ts, 
                        &seven_eighths_esc_label, 0);
                }
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        TBSPEC => NextToken;
        TBSPEC_SampP => {
            NL_string *norm = NL_new_string(mgr, 7);
            norm->bytes[0] = *ts;
            norm->bytes[1] = '&';
            norm->bytes[2] = *(ts +6);                                       
            norm->bytes[3] = '-';
            norm->bytes[4] = '5';
            norm->bytes[5] = '0';
            norm->bytes[6] = '0';
            NL_add_bspan(mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);
        };

        TBSPEC_SampLs => {
            NL_string *norm = NL_new_string(mgr, 4);
            norm->bytes[0] = *ts;
            norm->bytes[1] = '&';
            norm->bytes[2] = *(ts +6);                                       
            norm->bytes[3] = *(ts +7);            
            NL_add_bspan(mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);
        };

        BANGWORDS => NextToken;
        BANGMAGAZINES %MarkIntermediate1 SPACENL /magazine/i =>
            NextIntermediate1;
        THING3 => EscapeForwardSlashAsterisk;
        DOLSIGN => NextToken;
        DOLSIGN2 => NextToken;
        DOLSIGN2_CENTS => {
            if (normalize_currency == 1) {
                NL_add_bspan(mgr, ann, ts, te -ts, &cents_label, 0);
            } else {
                NL_add_bspan(mgr, ann, ts, te -ts, NULL, 0);
            }
        };

        DOLSIGN2_POUNDS => {
            if (normalize_currency == 1) {
                NL_add_bspan(mgr, ann, ts, te -ts, &pounds_label, 0);
            } else {
                NL_add_bspan(mgr, ann, ts, te -ts, NULL, 0);
            }
        };

        DOLSIGN2_NORM => {
            if (normalize_currency == 1) {
                NL_add_bspan(mgr, ann, ts, te -ts, &dollar_label, 0);
            } else {
                NL_add_bspan(mgr, ann, ts, te -ts, NULL, 0);
            }
        };

        PHONE => {
            
            if (normalize_spaces == 1 && normalize_parentheses == 1) {
                size_t size = NL_get_size_normalized_spaces_parens(
                    ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_normalize_parens_spaces(ts, te - ts, norm->bytes);
                NL_add_bspan(
                    mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);
            } else if (normalize_spaces == 1) {
                size_t size = NL_get_size_normalized_spaces(
                    ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_normalize_spaces(ts, te - ts, norm->bytes);
                NL_add_bspan(
                    mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);
            } else if (normalize_parentheses == 1) {
                size_t size = NL_get_size_normalized_parentheses(
                    ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_normalize_parentheses(ts, te - ts, norm->bytes);
                NL_add_bspan(
                    mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

    ACRONYM %MarkIntermediate1 SPACENLS (
          [A] /bout/i | [A] /ccording/i | [A] /dditionally/i | [A] /fter/i
        | [A] /n/i | [A] | [A] /s/i | [A] /t/i | [B] /ut/i | [D] /id/i
        | [D] /uring/i | [E] /arlier/i | [H] /e/i | [H] /er/i | [H] /ere/i
        | [H] /ow/i | [H] /owever/i | [I] /f/i | [I] /n/i | [I] /t/i
        | [L] /ast/i | [M] /any/i | [M] /ore/i | [M] /r/i "." | [M] /s/i "."
        | [N] /ow/i | [O] /nce/i | [O] /ne/i | [O] /ther/i | [O] /ur/i
        | [S] /he/i | [S] /ince/i | [S] /o/i | [S] /ome/i | [S] /uch/i
        | [T] /hat/i | [T] /he/i | [T] /heir/i | [T] /hen/i | [T] /here/i
        | [T] /hese/i | [T] /hey/i | [T] /his/i | [W] /e/i | [W] /hen/i
        | [W] /hile/i | [W] /hat/i | [Y] /et/i | [Y] /ou/i
        | SGML) SPACENL => {
            if (ti1 - ts == 2) { // e.g. "I."
 
                te = ti1 - 1;
                NEXT_TOKEN

                ts = ti1 - 1;
                fpc = ti1 - 2;
                te = '\0';

            } else if (strict_ptb3 && memcmp(ts, "U.S.", 4) != 0) {
                te = ti1 - 1;
                NEXT_TOKEN
                ts = ti1 - 1;
                fpc = ti1 - 2;
                te = '\0';


            } else { // Return next word WITH period and return period for 
                     // next token.
               
                te = ti1;
                NEXT_TOKEN
                ts = ti1 - 1;
                fpc = ti1 - 2;
                te = '\0';

            }
        };


        ABBREV3 %MarkIntermediate2 SPACENL ? udigit => NextIntermediate2;

        (/pt/i [eyEY]|/co/i)"." %MarkIntermediate2 
            SPACE ( /ltd/i | /lim/i ) => NextIntermediate2;

        ABBREV1 %MarkIntermediate1 SENTEND => {
            if (strict_ptb3 && memcmp(ts, "U.S.", 4) != 0) {
                te = ti1 - 1;
                NEXT_TOKEN
                ts = ti1 - 1;
                fpc = ti1 - 2;
                te = '\0';


            } else { // Return next word WITH period and return period for 
                     // next token.
               
                te = ti1;
                NEXT_TOKEN
                ts = ti1 - 1;
                fpc = ti1 - 2;
                te = '\0';

            }


        };
        
        ABBREV1 %MarkIntermediate1 any any => NextIntermediate1;

        ABBREV1  => {
            if (strict_ptb3 && memcmp(ts, "U.S.", 4) != 0) {
                te = te - 1;
                NEXT_TOKEN
                ts = te;
                fpc = te - 1;
                te = '\0';


            } else { // Return next word WITH period and return period for 
                     // next token.
               
                NEXT_TOKEN
                ts = te - 1;
                fpc = te - 2;
                te = '\0';

            }


        };

        ABBREV2 => NextToken; 

        ABBREV4 %MarkIntermediate2 SPACE => NextIntermediate2;
        ACRO %MarkIntermediate2 SPACENL => NextIntermediate2;
        TBSPEC2 %MarkIntermediate2 SPACENL => NextIntermediate2;
        FILENAME %MarkIntermediate2 (SPACENL|[.?!,]) => NextIntermediate2;

        WORD"." %MarkIntermediate2 INSENTP => NextIntermediate2;

        (DBLQUOT | [`]{1,2}) %MarkIntermediate2 [A-Za-z0-9$] => 
            NextIntermediateHandleProbablyLeftQuotes2;
        #    NextToken;
        
        DBLQUOT => HandleQuotesProbablyRight;
       
        LESSTHAN => {
            NL_add_bspan(mgr, ann, ts, te - ts, &lessthan_label, 0);
        };
        GREATERTHAN => {
            NL_add_bspan(mgr, ann, ts, te - ts, &greaterthan_label, 0);
        };

        SMILEY %MarkIntermediate2 [^A-Za-z0-9] => {
            te = ti2;
            if (normalize_parentheses == 1) {
                size_t size = NL_get_size_normalized_parentheses(
                    ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_normalize_parentheses(ts, te - ts, norm->bytes);
                NL_add_bspan(
                    mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);

            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }   
            ts = te;
            fpc = te - 1;
            te = '\0';

        };
        ASIANSMILEY => {
            if (normalize_parentheses == 1) {
                size_t size = NL_get_size_normalized_parentheses(
                    ts, te - ts);
                NL_string *norm = NL_new_string(mgr, size);
                NL_normalize_parentheses(ts, te - ts, norm->bytes);
                NL_add_bspan(
                    mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };

        "{" => NormalizeLCBNext;
        "}" => NormalizeRCBNext;
        "[" => NormalizeLSBNext;
        "]" => NormalizeRSBNext;
        "(" => NormalizeLRBNext;
        ")" => NormalizeRRBNext;

        HYPHENS => {
            size_t num_hyphens = te - ts;
            if (normalize_ptb3_dashes 
                    && 3 <= num_hyphens && num_hyphens <= 4) {
                NL_add_bspan(mgr, ann, ts, te - ts, &ptb3dash, 0);
            } else {
                NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);
            }
        };
        LDOTS => HandleEllipsis;

        FNMARKS => NextToken;
        ASTS => EscapeForwardSlashAsterisk;

        INSENTP => NextToken;
        SENT_END_PUNC => NextTokenSentEnd;
        PUNC => NextToken;
        "="+ => NextToken;
        "\\/" => NextToken;
        "/" => EscapeForwardSlashAsterisk; 

        HTHING "." %MarkIntermediate1 INSENTP => NextIntermediate1;
        HTHING => NextToken;

        
        THING "." %MarkIntermediate2 INSENTP => NextIntermediate2;
        THING => NextToken;        

        THINGA => ConvertAmp;

        REDAUX => HandleQuotesProbablyRight;
        SREDAUX => HandleQuotesProbablyRight;

        # This pattern is meant to be a negative case of the next.
        "'" %MarkIntermediate2 [A-Za-z] 0xC2 0xA0 =>
             NextIntermediateHandleProbablyRightQuotes2;

        "'" %MarkIntermediate2 [A-Za-z][^ \t\n\r] =>
             NextIntermediateHandleProbablyLeftQuotes2;
 

        QUOTES => HandleQuotesProbablyRight; ## TODO: TEST THIS I THINK I 
                                             ## FUCKED UP THE CP1252 PARTS

        FAKEDUCKFEET => NextToken;

        MISCSYMBOL => NextToken;

        0xC2 0x95 => {
            NL_add_bspan(mgr, ann, ts, te - ts, &uni_bullet, 0);     
        };
        0xC2 0x99 => {
            NL_add_bspan(mgr, ann, ts, te - ts, &uni_tm, 0);     
        };

        ALL_SPACES;
        '\0' => {
            fwrite("Warning: tokenizer found null character.\n", 
                   1, 41, stderr);
        };

        NEWLINE => TokenizeNewline;

        #SPACENLS;

        /&nbsp;/i ; # In CORENLP this is needed for invertible mode but we are
                    # always invertible.

        0xEF 0xBB 0xBF => {printf("I found a byte order mark!\n");};
        any; # => { printf("the uncola: 0x%02X\n", (unsigned int)  *ts); };
    *|;

}%%

%% write data nofinal;


#define NEXT_TOKEN                                                            \
    if (alert_soft_hyphen > 0) {                                              \
        size_t size = te - ts - alert_soft_hyphen * 2;                        \
        if (size > 1) {                                                       \
            NL_string *norm = NL_new_string(mgr, size);                       \
            NL_copy_no_softhyphen(ts, te - ts, norm->bytes);                  \
            NL_add_bspan(                                                     \
                mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);           \
        } else {                                                              \
            NL_string *norm = NL_new_string(mgr, 1);                          \
            norm->bytes[0] = '-';                                             \
            NL_add_bspan(                                                     \
                mgr, ann, ts, te - ts, (void *) norm, NL_OWN_DATA);           \
        }                                                                     \
        alert_soft_hyphen = 0;                                                \
    } else {                                                                  \
        NL_add_bspan(mgr, ann, ts, te - ts, NULL, 0);                         \
    }                                                                         \


#define SPLIT_ASSIM(PREFIX)                                                   \
    NL_add_bspan(mgr, ann, ts, PREFIX, NULL, 0);                              \
    NL_add_bspan(mgr, ann, ts + PREFIX, te - PREFIX - ts, NULL, 0);           \


static NL_string ptb3dash = {(unsigned char *) "--", 2, 0};
static NL_string amp = {(unsigned char *) "&", 1, 0};
static NL_string newline_token = {(unsigned char *) "*NL*", 4, 0};
static NL_string uni_bullet = {(unsigned char *) "\xE2\x80\xA2", 3, 0};
static NL_string uni_tm = {(unsigned char *) "\xE2\x84\xA2", 3, 0};
static NL_string cents_label = {(unsigned char *) "cents", 5, 0};
static NL_string pounds_label = {(unsigned char *) "#", 1, 0};
static NL_string dollar_label = {(unsigned char *) "\\$", 2, 0};
static NL_string ptb3_ellipsis_label = {(unsigned char *) "...", 3, 0};
static NL_string uni_ellipsis_label = {
    (unsigned char *) "\xE2\x80\xA6", 3, 0};

static NL_string lrb_label = {(unsigned char *) "-LRB-", 5, 0};
static NL_string rrb_label = {(unsigned char *) "-RRB-", 5, 0};
static NL_string lsb_label = {(unsigned char *) "-LSB-", 5, 0};
static NL_string rsb_label = {(unsigned char *) "-RSB-", 5, 0};
static NL_string lcb_label = {(unsigned char *) "-LCB-", 5, 0};
static NL_string rcb_label = {(unsigned char *) "-RCB-", 5, 0};

static NL_string lessthan_label = {(unsigned char *) "<", 1, 0};
static NL_string greaterthan_label = {(unsigned char *) ">", 1, 0};
static NL_string one_fourth_label = {(unsigned char *) "1/4", 3};
static NL_string one_fourth_esc_label = {(unsigned char *) "1\\/4", 4};
static NL_string one_half_label = {(unsigned char *) "1/2", 3};
static NL_string one_half_esc_label = {(unsigned char *) "1\\/2", 4};
static NL_string three_fourths_label = {(unsigned char *) "3/4", 3};
static NL_string three_fourths_esc_label = {(unsigned char *) "3\\/4", 4};
static NL_string one_third_label = {(unsigned char *) "1/3", 3};
static NL_string one_third_esc_label = {(unsigned char *) "1\\/3", 4};
static NL_string two_thirds_label = {(unsigned char *) "2/3", 3};
static NL_string two_thirds_esc_label = {(unsigned char *) "2\\/3", 4};
static NL_string one_fifth_label = {(unsigned char *) "1/5", 3};
static NL_string one_fifth_esc_label = {(unsigned char *) "1\\/5", 4};
static NL_string two_fifths_label = {(unsigned char *) "2/5", 3};
static NL_string two_fifths_esc_label = {(unsigned char *) "2\\/5", 4};
static NL_string three_fifths_label = {(unsigned char *) "3/5", 3};
static NL_string three_fifths_esc_label = {(unsigned char *) "3\\/5", 4};
static NL_string four_fifths_label = {(unsigned char *) "4/5", 3};
static NL_string four_fifths_esc_label = {(unsigned char *) "4\\/5", 4};
static NL_string one_sixth_label = {(unsigned char *) "1/6", 3};
static NL_string one_sixth_esc_label = {(unsigned char *) "1\\/6", 4};
static NL_string five_sixths_label = {(unsigned char *) "5/6", 3};
static NL_string five_sixths_esc_label = {(unsigned char *) "5\\/6", 4};
static NL_string one_eighth_label = {(unsigned char *) "1/8", 3};
static NL_string one_eighth_esc_label = {(unsigned char *) "1\\/8", 4};
static NL_string three_eighths_label = {(unsigned char *) "3/8", 3};
static NL_string three_eighths_esc_label = {(unsigned char *) "3\\/8", 4};
static NL_string five_eighths_label = {(unsigned char *) "5/8", 3};
static NL_string five_eighths_esc_label = {(unsigned char *) "5\\/8", 4};
static NL_string seven_eighths_label = {(unsigned char *) "7/8", 3};
static NL_string seven_eighths_esc_label = {(unsigned char *) "7\\/8", 4};


NL_annotations *NL_tokenize_buf(NL_buffer *buffer, NL_PTBTokConfig *cfg, 
        NL_v_memmgr *mgr) {

    size_t tmp = buffer->size; // I don't understand what is happening here.
    NL_annotations *ann = NL_new_bspan_annotations(mgr);
    buffer->size = tmp;
    int alert_soft_hyphen = 0;
    size_t num_amps = 0;
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *ti1 = 0;
    unsigned char *ti2 = 0;
    unsigned char *p = buffer->bytes;  
    unsigned char *pe = p + buffer->size; 
    unsigned char *eof = pe;

    int split_assimilations = 1;
    if (cfg != NULL) {
        split_assimilations = cfg->split_assimilations;
    }

    int normalize_ptb3_dashes = 1;
    if (cfg != NULL) {
        normalize_ptb3_dashes = cfg->normalize_dashes;
    }

    int normalize_amp = 1;
    if (cfg != NULL) {
        normalize_amp = cfg->normalize_amp;
    }

    NL_normalize_quotes normalize_quotes = QUOTES_LATEX;
    if (cfg != NULL) {
        normalize_quotes = cfg->normalize_quotes;
    }

    int tokenize_newlines = 0;
    if (cfg != NULL) {
        tokenize_newlines = cfg->tokenize_newlines;
    }

    int normalize_currency = 0;
    if (cfg != NULL) {
        normalize_currency = cfg->normalize_currency;
    }

    int escape_forward_slash_asterisk = 0;
    if (cfg != NULL) {
        escape_forward_slash_asterisk = cfg->escape_forward_slash_asterisk;
    }

    NL_normalize_ellipsis normalize_ellipsis = ELLIPSIS_PTB3;
    if (cfg != NULL) {
        normalize_ellipsis = cfg->normalize_ellipsis;
    }

    int normalize_parentheses = 1;
    if (cfg != NULL) {
        normalize_parentheses = cfg->normalize_parentheses;
    }

    int normalize_brackets = 1;
    if (cfg != NULL) {
        normalize_brackets = cfg->normalize_brackets;
    }

    int strict_ptb3 = 0;
    if (cfg != NULL) {
        strict_ptb3 = cfg->strict_ptb3;
    }

    int normalize_spaces = 1;
    if (cfg != NULL) {
        normalize_spaces = cfg->normalize_spaces;
    }

    int normalize_fractions = 0;
    if (cfg != NULL) {
        normalize_fractions = cfg->normalize_fractions;
    }

    %% write init;

    %% write exec;

    return ann; 

}

NL_PTBTokConfig *NL_new_PTB_tokenizer_config(NL_v_memmgr *mgr) {

    NL_PTBTokConfig *cfg = NL_allocate_mem_size(mgr, sizeof(NL_PTBTokConfig));
    if (cfg != NULL) {
        cfg->split_assimilations = 1;
        cfg->normalize_dashes = 1;
        cfg->normalize_amp = 1;
        cfg->normalize_quotes = QUOTES_LATEX;
        cfg->tokenize_newlines = 0;
        cfg->normalize_currency = 0;
        cfg->escape_forward_slash_asterisk = 0;
        cfg->normalize_ellipsis = ELLIPSIS_PTB3;
        cfg->normalize_parentheses = 1;
        cfg->normalize_brackets = 1;
        cfg->strict_ptb3 = 0;
        cfg->normalize_spaces = 1;
        cfg->normalize_fractions = 0;
    }
    return cfg;
}
