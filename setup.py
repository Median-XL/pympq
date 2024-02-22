import os
import shutil
import struct
from pathlib import Path

from setuptools import Extension, setup

if os.name != 'nt':
    raise NotImplementedError("pympq only supports windows")


def get_version() -> str:
    version = os.environ.get("PYMPQ_DIST_VERSION")
    if not version:
        return "0.1.dev"
    return version


def get_arch() -> str:
    bits = struct.calcsize("P") * 8
    if bits == 64:
        return "x64"
    elif bits == 32:
        return "x86"
    else:
        raise ValueError("Can't determine architecture")


# hack'ish workaround to get StormLib.dll included next
# to the generated .pyd in our installed module
shutil.copyfile(f"stormlib\\{get_arch()}\\StormLib.dll", "pympq\\StormLib.dll")


pympq_ext = Extension(
    'pympq',
    sources = ['src\\pympq.cpp'],
    include_dirs=[f"stormlib\\{get_arch()}"],
    library_dirs=[f"stormlib\\{get_arch()}"],
    libraries=["StormLib", "StormLibRUD"],
    extra_compile_args=["/D_UNICODE", "/DUNICODE"],
)

setup(
    name='pympq',
    version=get_version(),
    author="Median XL",
    url="https://github.com/Median-XL/pympq",
    description='python implementation of the stormlib API',
    classifiers=[
        "Environment :: Win32 (MS Windows)",
        "Operating System :: Microsoft :: Windows",
        "Programming Language :: C++",
        "Programming Language :: Python :: Implementation :: CPython",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
    ],
    ext_package="pympq",
    ext_modules=[pympq_ext],
    include_package_data=True,
    packages = ["pympq"],
    package_dir={"pympq": "pympq"},
    package_data={
        "pympq": ["*.dll"],
    },
)
