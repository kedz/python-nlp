from setuptools import setup, Extension
import os

def build_extension():

    try:
        from Cython.Build import cythonize
        use_cython = True
        ext = ".pyx"
    except ImportError, e:
        use_cython = False
        ext = ".c"

    include_nlp = "../include/"
    lib_nlp = "../lib/"

    libnlp = Extension(
        "nlp.libnlp",
        sources=[
            os.path.join("nlp", "libnlp{}".format(ext)),
        ],
        include_dirs=[".", "{}".format(include_nlp)],
        library_dirs=[".", "{}".format(lib_nlp)],
        libraries = ["nlp"],
        extra_compile_args=["-O9", "-std=c11" ],
        extra_link_args=["-O9"],
        language="c")

    ez = Extension(
        "nlp.ez",
        sources=[
            os.path.join('nlp', 'ez{}'.format(ext)), 
            "nlp/libnlp{}".format(ext),
        ],
        libraries = ["nlp"],
        include_dirs=[".", "{}".format(include_nlp)],
        library_dirs=[".", "{}".format(lib_nlp)],
        extra_compile_args=["-O9", "-std=c11" ],
        extra_link_args=["-O9"],
        language="c")

    if use_cython is True:
        return cythonize([libnlp, ez], gdb_debug=True)
    else:
        return [libnlp, ez]

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
