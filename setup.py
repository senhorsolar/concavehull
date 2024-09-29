from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension("concavehull",
                      ["src/bindings.cc"],
                      cxx_std=20
    ),
]

setup(
    name="concavehull",
    ext_modules=ext_modules,    
    cmdclass={"build_ext": build_ext}
)
