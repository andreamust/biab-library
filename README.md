BIAB Library
==============


A [pybind11](https://github.com/pybind/pybind11) module built with a
CMake-based build system for converting Band-in-a-Box files.

The C++ source code has been provided by [Andrew Choi](https://sixthhappiness.github.io/articles/chart-translate/index.html), to whom all credits must be given.

Installation
------------

## Installation via pip

You can install the library using pip, by running the command:

```commandline
pip install biab-library
```
You can also find the PyPi documentation at [this link](https://pypi.org/project/biab-library/).

## Local installation

For installing the library locally, you can follow these steps:

 - clone this repository running `git clone https://github.com/andreamust/biab-library.git`
 - run `pip install ./biab-library`

Usage
-----------
The library implements three different methods for accessing the data stored in the Band-in-a-Box files. 

The methods are as follows:
* `biab_data`: given a Band-in-a-Box file path, it returns all the data stored in the file;
* `biab_meta`: given a Band-in-a-Box file path, it returns the file metadata;
* `biab_chords`: given a Band-in-a-Box file path, it returns all the chords contained in the file.



Tests
-----

TBD

Building the documentation
--------------------------

Documentation for the example project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

 - `cd python_example/docs`
 - `make html`

License
-------

pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.
