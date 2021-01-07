from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir

import sys

ext_modules = [
    Pybind11Extension("python_example",
                      ["bindings.cc"],
                      # Example: passing in the version to the compiled code
                      #define_macros = [('VERSION_INFO', __version__)],
                      #cxx_std=17
    ),
]

setup(
    name="concavehull",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext}
)
