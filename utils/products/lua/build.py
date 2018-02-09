#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Lua build.
"""


import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def _create_cxx_header():
    cxx_header = os.path.join(data.build.local_root, "include", "lua.hpp")
    if not os.path.exists(cxx_header):
        with open(cxx_header, "w+") as outfile:
            outfile.write("// lua.hpp\n")
            outfile.write("// Lua header files for C++\n")
            outfile.write(
                "// <<extern \"C\">> not supplied automatically because Lua "
                "also compiles as C++\n"
            )
            outfile.write("\n")
            outfile.write("extern \"C\" {\n")
            outfile.write("#include \"lua.h\"\n")
            outfile.write("#include \"lualib.h\"\n")
            outfile.write("#include \"lauxlib.h\"\n")
            outfile.write("}\n")
            outfile.write("")


def _build_into_source():
    """
    Add the Lua source files into the external sources of the product.
    """
    product = data.build.products.lua
    dest = os.path.join(data.build.local_root, "src")
    if os.path.isdir(dest):
        for filename in os.listdir(dest):
            if not filename == "glad.c":
                shell.rm(os.path.join(dest, filename))
    else:
        shell.makedirs(dest)
    header_dest = os.path.join(data.build.local_root, "include")
    if os.path.isdir(header_dest):
        for filename in os.listdir(header_dest):
            if "lua" in filename and ".h" in filename:
                shell.rm(os.path.join(header_dest, filename))
    else:
        shell.makedirs(header_dest)
    source_dir = workspace.source_dir(product=product)
    for filename in os.listdir(os.path.join(source_dir, "src")):
        if filename.endswith(".c"):
            shell.copy(
                os.path.join(source_dir, "src", filename),
                os.path.join(dest, filename)
            )
        elif filename.endswith(".h"):
            shell.copy(
                os.path.join(source_dir, "src", filename),
                os.path.join(header_dest, filename)
            )
    _create_cxx_header()


def _build():
    """
    Do the build of Lua.
    """
    product = data.build.products.lua
    bin_path = os.path.join(data.build.local_root, "lib", "liblua.a")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(product)
    source_dir = workspace.source_dir(product=product)
    shell.makedirs(build_dir)
    shell.copytree(source_dir, build_dir)
    with shell.pushd(build_dir):
        if platform.system() == "Darwin":
            common.build.make(target="macosx")
        elif platform.system() == "Linux":
            common.build.make(target="linux")
        common.build.make(
            target="install",
            extra_args="INSTALL_TOP={}".format(data.build.local_root)
        )


def do_build():
    """
    Build Lua.
    """
    product = data.build.products.lua
    common.build.check_source(product)
    if data.build.lua_in_source:
        _build_into_source()
    else:
        _build()


def should_build():
    """
    Check whether this product should be built.
    """
    return True