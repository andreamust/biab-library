# Band-in-a-Box Converter Library

A [pybind11](https://github.com/pybind/pybind11) module built with a
CMake-based build system for converting Band-in-a-Box files.

The C++ source code has been provided by [Andrew Choi](https://sixthhappiness.github.io/articles/chart-translate/index.html), to whom all credits must be given.

## Prerequisites

- A compiler with C++11 support
- Pip 10+ or CMake >= 3.4 (or 3.8+ on Windows, which was the first version to support VS 2015)
- Ninja or Pip 10+

## Installation

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/pybind/biab_library.git
pip install ./biab_library  # Note that this command must be run in the root directory
```

With the `setup.py` file included in this example, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.

## Run the Python Code

```python
import baib_converter
biab_converter.biab("path_to_the_biab_file")
```

Which will led to an output of this shape:

```
Beat = 0 Duration = 8 chord = Ab
Beat = 8 Duration = 8 chord = Ab7
Beat = 16 Duration = 8 chord = Gb7b9
Beat = 24 Duration = 8 chord = Ab7
Beat = 32 Duration = 2 chord = Ab
Beat = 34 Duration = 2 chord = Db
Beat = 36 Duration = 2 chord = Bb7
Beat = 38 Duration = 2 chord = Eb7b9
Beat = 40 Duration = 4 chord = Ab
Beat = 44 Duration = 4 chord = Db7b9
Beat = 48 Duration = 8 chord = Ab
Beat = 56 Duration = 8 chord = Ab7
Beat = 64 Duration = 8 chord = Gb7b9
Beat = 72 Duration = 8 chord = Ab7
Beat = 80 Duration = 2 chord = Ab
Beat = 82 Duration = 2 chord = Db
Beat = 84 Duration = 2 chord = Bb7
Beat = 86 Duration = 2 chord = Eb7b9
Beat = 88 Duration = 4 chord = Ab
Beat = 92 Duration = 4 chord = Db7b9
Beat = 96 Duration = 4 chord = Ab

Name = Adam's Apple - Wayne Shorter
Meter = 4/4
Key = Ab
Tempo = 100
```
