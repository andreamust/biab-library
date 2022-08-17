# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

__version__ = "0.4.1"

# The main interface is through Pybind11Extension.
# * You can add cxx_std=11/14/17, and then build_ext can be removed.
# * You can set include_pybind11=false to add the include directory yourself,
#   say from a submodule.
#
# Note:
#   Sort input source files if you glob sources to ensure bit-for-bit
#   reproducible builds (https://github.com/pybind/python_example/pull/53)

ext_modules = [
    Pybind11Extension("biab",
                      ["src/main.cpp"],
                      # Example: passing in the version to the compiled code
                      define_macros=[('VERSION_INFO', __version__)],
                      ),
]

setup(
    name="biab-library",
    version=__version__,
    author="Andrea Poltronieri",
    author_email="andrea.poltronieri21@gmail.com",
    url="https://github.com/andreamust/biab",
    description="A converter for band-in-a-box files",
    long_description="A tool for exploring and processing Band-in-a-Box files",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.6",
)
