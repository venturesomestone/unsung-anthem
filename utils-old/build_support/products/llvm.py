#===--------------------------- llvm.py ----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the LLVM product helpers.
"""


import json
import os
import platform

from . import clang, libcxxabi, libcxx

from .product import binary_exists, build_call, check_source

from .. import diagnostics, shell, workspace

from ..httpstream import stream_file

from ..variables import ANTHEM_SOURCE_ROOT, VERSIONS_FILE


def skip_checkout(build_data, versions):
    """
    Check whether or not LLVM should be skipped in the checkout.

    build_data -- the build data.
    versions -- the version info dictionary of the checkout.
    """
    diagnostics.note(
        "{} checkout check is done in the checkout process".format(
            build_data.products.llvm.repr))
    return False


def skip_download(build_data, key):
    """
    Check whether or not the LLVM download should be skipped.

    build_data -- the build data.
    key -- the name of the subproduct.
    """
    if os.path.isfile(VERSIONS_FILE):
        with open(VERSIONS_FILE) as json_file:
            versions = json.load(json_file)
    else:
        versions = {}

    if "llvm" in versions:
        version_node = versions["llvm"]
        if key in version_node:
            if version_node[key] == build_data.products.llvm.version:
                diagnostics.debug(
                    "{} should not be re-downloaded, skipping".format(key))
                return True
    return False


def inject_version_info(build_data, versions):
    """
    Add the LLVM version info to the checkout version info.

    build_data -- the build data.
    versions -- the version info dictionary of the checkout.
    """
    product = build_data.products.llvm
    args = build_data.args
    version = product.version
    if args.build_libcxx:
        version_info = {
            "llvm": version, "clang": 0, "libcxx": version,
            "libcxxabi": version
        }
    elif args.build_llvm:
        version_info = {
            "llvm": version, "clang": version, "libcxx": version,
            "libcxxabi": version
        }
    versions["llvm"] = version_info


def remove_old_checkout(build_data, key):
    """
    Remove the old checkout of the given LLVM subproduct.

    build_data -- the build data.
    key -- the name of the subproduct.
    """
    product = build_data.products.llvm
    version = product.version
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", version, key))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))


def remove_libcxx_bad_symlink():
    """
    Remove the bad symlink in libc++.
    """
    # FIXME: This is bad, this is hardcoded.
    shell.rm(os.path.join(
        ANTHEM_SOURCE_ROOT, "llvm", "temp", "libcxx", "test", "std",
        "experimental", "filesystem", "Inputs", "static_test_env",
        "bad_symlink"))


def remove_libcxx_release_bad_symlink(subdir):
    """
    Remove the bad symlink in libc++.

    subdir -- the name of the libc++ subdir in the release archive.
    """
    # FIXME: This is bad, this is hardcoded.
    shell.rm(os.path.join(
        ANTHEM_SOURCE_ROOT, "llvm", "temp", "libcxx", subdir, "test", "std",
        "experimental", "filesystem", "Inputs", "static_test_env",
        "bad_symlink"))


def git_dependency(build_data, key):
    """
    Download the given LLVM subproduct by using git.

    build_data -- the build data.
    key -- the name of the subproduct.
    """
    product = build_data.products.llvm
    version = product.version
    remove_old_checkout(build_data=build_data, key=key)

    with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp")):
        shell.call([
            build_data.toolchain.git,
            "clone",
            product.git_format.format(key=key)])

    # FIXME: This is bad, this is hardcoded.
    if key == "libcxx":
        remove_libcxx_bad_symlink()

    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key),
        os.path.join(ANTHEM_SOURCE_ROOT, "llvm", version, key))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))


def move_release_files(build_data, key, subdir):
    """
    Move the LLVM subproduct files to the correct location after the download.

    build_data -- the build data.
    key -- the name of the subproduct.
    """
    product = build_data.products.llvm
    version = product.version
    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key, subdir),
        os.path.join(ANTHEM_SOURCE_ROOT, "llvm", version, key))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))


def release_dependency(build_data, key):
    """
    Download the given LLVM subproduct.

    build_data -- the build data.
    key -- the name of the subproduct.
    """
    product = build_data.products.llvm
    version = product.version
    remove_old_checkout(build_data=build_data, key=key)
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))
    url = product.release_format.format(
        protocol=build_data.connection_protocol, version=version,
        key=product.subproducts[key]
    )
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "llvm", "temp", key, "{}.tar.xz".format(key)
    )

    stream_file(build_data=build_data, url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))
    subdir = "{}-{}.src".format(key, version)
    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir))
    # FIXME: This is bad, this is hardcoded.
    if key == "libcxx":
        remove_libcxx_release_bad_symlink(subdir=subdir)
    shell.rm(destination)
    move_release_files(build_data=build_data, key=key, subdir=subdir)


def single_dependency(build_data, key):
    """
    Download the given LLVM subproduct.

    build_data -- the build data.
    key -- the name of the subproduct.
    """
    diagnostics.debug("Downloading LLVM subproject {}".format(key))
    version = build_data.products.llvm.version
    if version.startswith("6.0"):
        git_dependency(build_data=build_data, key=key)
    else:
        release_dependency(build_data=build_data, key=key)


def get_llvm_binary(build_data):
    """
    Download the pre-built LLVM binary.

    build_data -- the build data.
    """
    product = build_data.products.llvm
    version = product.version
    key = "llvm"
    remove_old_checkout(build_data=build_data, key="llvm")
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", "llvm"))
    sys = platform.system()
    if sys == "Linux":
        machine = "x86_64-ubuntu16.04"
    else:
        machine = "x86_64-apple-darwin"
    url = product.binary_format.format(
        protocol=build_data.connection_protocol, version=version,
        platform=machine
    )
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "llvm", "temp", key, "{}.tar.xz".format(key)
    )

    stream_file(build_data=build_data, url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))
    subdir = "clang+llvm-{version}-{platform}".format(
        version=version,
        platform=machine)
    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir))
    shell.rm(destination)
    move_release_files(build_data=build_data, key=key, subdir=subdir)


def get_dependency(build_data):
    """
    Download the LLVM subproducts.

    build_data -- the build data.
    """
    args = build_data.args
    product = build_data.products.llvm
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))
    if args.build_libcxx:
        llvm_deps = ["llvm", "libcxx", "libcxxabi"]
    elif args.build_llvm:
        llvm_deps = list(product.subproducts.keys())

    if args.source_llvm or args.build_libcxx:
        for dep in llvm_deps:
            if not skip_download(build_data=build_data, key=dep):
                single_dependency(build_data=build_data, key=dep)
    elif args.build_llvm:
        get_llvm_binary(build_data=build_data)

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))


def do_build(build_data):
    """
    Do the build of LLVM with Clang and libc++.

    build_data -- the build data.
    """
    args = build_data.args
    product = build_data.products.llvm
    if build_data.args.build_llvm:
        bin_path = clang.clang_bin_path(build_data=build_data)
    elif build_data.args.build_libcxx:
        bin_path = libcxx.libcxx_bin_path(build_data=build_data)
    build_dir = workspace.build_dir(
        build_data=build_data, product=product, subproduct="llvm"
    )
    if binary_exists(
            build_data=build_data, product=product, path=bin_path,
            subproduct="llvm"):
        return
    libcxx.set_up(build_data=build_data)
    libcxxabi.set_up(build_data=build_data)
    if build_data.args.build_llvm:
        clang.set_up(build_data=build_data)
    shell.makedirs(build_dir)

    cmake_args = []

    if args.llvm_assertions:
        cmake_args += ["-DLLVM_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_args += ["-DLLVM_ENABLE_ASSERTIONS=OFF"]

    if args.libcxx_assertions:
        cmake_args += ["-DLIBCXX_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_args += ["-DLIBCXX_ENABLE_ASSERTIONS=OFF"]

    if build_data.args.build_libcxx:
        build_call(
            build_data=build_data, product=product, subproduct="llvm",
            cmake_args=cmake_args, build_targets="cxx",
            install_targets=["install-cxx", "install-cxxabi"]
        )
    else:
        build_call(
            build_data=build_data, product=product, subproduct="llvm",
            cmake_args=cmake_args
        )


def set_up(build_data):
    """
    Set LLVM up for the build.

    build_data -- the build data.
    """
    product = build_data.products.llvm
    check_source(product=product, subproduct="llvm")
    do_build(build_data=build_data)
    if build_data.args.build_llvm:
        build_data.toolchain.cc = clang.clang_bin_path(build_data=build_data)
        build_data.toolchain.cxx = clang.clang_cxx_bin_path(
            build_data=build_data
        )
        build_data.args.main_tool = "llvm"


def set_toolchain(build_data):
    """
    Set Clang to the toolchain.

    build_data -- the build data.
    """
    if build_data.args.build_llvm:
        build_data.toolchain.cc = clang.clang_bin_path(build_data=build_data)
        build_data.toolchain.cxx = clang.clang_cxx_bin_path(
            build_data=build_data)
        diagnostics.debug(
            "Set {} to the toolchain from a custom location: {}".format(
                build_data.products.llvm.repr, build_data.toolchain.llvm))