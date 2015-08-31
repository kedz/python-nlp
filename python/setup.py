from setuptools import setup, Extension
import os

def find_nlp_sources():
    cwd = os.path.dirname(os.path.realpath(__file__))
    c_src = os.path.join(
        os.path.split(cwd)[0],
        "c", "src")
    if not os.path.exists(c_src):
        raise Exception("Could not find c sources.")

    sources = [os.path.join(c_src, f) 
               for f in os.listdir(c_src) if f.endswith(".c")]
    return sources, c_src

def build_extension():

    try:
        from Cython.Build import cythonize
        use_cython = True
        ext = ".pyx"
    except ImportError, e:
        use_cython = False
        ext = ".c"

    sources_nlp, include_nlp = find_nlp_sources()

#    libraries = ["fnlp"]#['oolm', 'dstruct', 'misc', 'z', 'gomp']
#
#    _mem_mgr = Extension(
#        "nlp._mem_mgr",
#        sources=[os.path.join('nlp', '_mem_mgr{}'.format(ext)),],
#        libraries=libraries,
#        extra_compile_args=["-I/home/kedz/projects2015/fnlp/fnlp-c/include", "-O4"],
#        extra_link_args=["-L/home/kedz/projects2015/fnlp/fnlp-c/lib"],
#        language="c")
# 
#
#    config = Extension(
#        "nlp.config",
#        sources=[os.path.join('nlp', 'config{}'.format(ext)),],
#        libraries=libraries,
#        extra_compile_args=["-I/home/kedz/projects2015/fnlp/fnlp-c/include", "-O4"],
#        extra_link_args=["-L/home/kedz/projects2015/fnlp/fnlp-c/lib"],
#        language="c")
#       
    libnlp = Extension(
        "nlp.libnlp",
        sources=[os.path.join("nlp", "libnlp{}".format(ext)),
            #"nlp/libnlp.pxd"
            ] + sources_nlp,
        include_dirs=["."],
        extra_compile_args=["-I{}".format(include_nlp), "-O9", "-std=c11" ],
        extra_link_args=["-O9"],
        language="c")
#
    ez = Extension(
        "nlp.ez",
        sources=[os.path.join('nlp', 'ez{}'.format(ext)), 
            "nlp/libnlp.pyx",
            #"nlp/libnlp.pxd"
            ] + sources_nlp,
        include_dirs=["."],
        extra_compile_args=["-I{}".format(include_nlp), "-O9", "-std=c11" ],
        extra_link_args=["-O9"],
        language="c")
#

    if use_cython is True:
        return cythonize([libnlp, ez])
    else:
        return [libnlp, ez]


    if use_cython is True:
        return cythonize([_mem_mgr, config, ez])
    else:
        return [_mem_mgr, config, ez]

setup(
    name="nlp",
    version="0.0.1",
    author="Chris Kedzie",
    author_email="kedzie@cs.columbia.edu",
    description="A package for fast NLP algorithms.",
#    license="",
#    keywords="",
#    url="",
    packages=['nlp'],
#    long_description="",
#    classifiers=[],
    ext_modules=build_extension(),
)
