#===------------------------ script_options.py ----------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the script options.
"""


import multiprocessing
import os

from . import arguments

from .targets import host_target

from .variables import SCRIPT_DIR


def script_options(parser):
    parser.add_argument(
        "-n", "--dry-run",
        help="print the commands that would be executed, but do not execute "
             "them",
        action="store_true",
        default=False)

    return parser

def ci_options(parser):
    ci_group = parser.add_argument_group(title="Continuous integration")
    ci_group.add_argument(
        "--ci",
        help="build in a CI environment",
        action="store_true")
    ci_group.add_argument(
        "--travis",
        help="[deprecated] build in a Travis CI environment",
        action="store_true")
    ci_group.add_argument(
        "--circleci",
        help="[deprecated] build in a CircleCI environment",
        action="store_true")
    ci_group.add_argument(
        "--appveyor",
        help="[deprecated] build in an AppVeyor CI environment",
        action="store_true")

    return parser

def target_options(parser):
    targets_group = parser.add_argument_group(
        title="[not implemented] Host and cross-compilation targets")
    targets_group.add_argument(
        "--host-target",
        help="The host target. LLVM, Clang, and Unsung Anthem will be built "
             "for this target. The built LLVM and Clang will be used to "
             "compile Unsung Anthem for the cross-compilation targets.",
        default=host_target().name)
    targets_group.add_argument(
        "--cross-compile-hosts",
        help="A space separated list of targets to cross-compile Unsung "
             "Anthem tools for. Can be used multiple times.",
        action=arguments.ACTION.concat,
        type=arguments.TYPE.shell_split,
        default=[])

    return parser

def projects_options(parser):
    projects_group = parser.add_argument_group(
        title="Options to select projects")
    projects_group.add_argument(
        "-l", "--llvm",
        help="build LLVM and use the built LLVM",
        action="store_true",
        dest="build_llvm")
    projects_group.add_argument(
        "-g", "--gcc",
        help="build GNU Compiler Collection and use the built compiler",
        action="store_true",
        dest="build_gcc")
    projects_group.add_argument(
        "--libc++",
        help="build libc++ and use the built library to build the project",
        action="store_true",
        dest="build_libcxx")
    projects_group.add_argument(
        "--libcxx",
        help="build libc++ and use the built library to build the project",
        action="store_true",
        dest="build_libcxx")
    projects_group.add_argument(
        "--sdl",
        help="build and use SDL (default GLFW)",
        action="store_true")
    projects_group.add_argument(
        "--glfw",
        help="build and use GLFW",
        action="store_true")
    projects_group.add_argument(
        "--build-cmake",
        help="build CMake",
        action="store_true")
    projects_group.add_argument(
        "--build-ninja",
        help="build the Ninja tool",
        action=arguments.ACTION.optional_bool)
    projects_group.add_argument(
        "--build-docs",
        help="build the Unsung Anthem documentation",
        action="store_true",
        dest="build_docs")
    projects_group.add_argument(
        "--build-test",
        help="build the Unsung Anthem tests",
        action="store_true",
        dest="build_test")
    projects_group.add_argument(
        "--build-test-optimized",
        help="build the Unsung Anthem tests with optimization",
        action="store_true",
        dest="build_test_optimized")

    return parser

def build_action_options(parser):
    build_actions_group = parser.add_mutually_exclusive_group(required=False)
    build_actions_group.add_argument(
        "--install",
        help="only install the project dependencies",
        action="store_true",
        dest="install_only")
    build_actions_group.add_argument(
        "--build",
        help="build the project without installing the dependencies",
        action="store_true",
        dest="build_only")
    build_actions_group.add_argument(
        "--run-test",
        help="run the tests without installing the dependencies or building "
             "the project",
        action="store_true",
        dest="test_only")
    build_actions_group.add_argument(
        "--docs-only",
        help="build only the documentation",
        action="store_true",
        dest="docs_only")

    return parser

def extra_action_options(parser):
    extra_actions_group = parser.add_argument_group(
        title="Extra actions to perform before or in addition to building")
    extra_actions_group.add_argument(
        "-c", "--clean",
        help="do a clean build",
        action="store_true")
    extra_actions_group.add_argument(
        "--gcov",
        help="use gcov and lcov to generate code coverage information",
        action="store_true",
        dest="enable_gcov")

    return parser

def cxx_options(parser):
    parser.add_argument(
        "--stdlib",
        help="build using the specified C++ standard library implementation",
        metavar="STDLIB",
        dest="stdlib")

    cpp_version_group = parser.add_mutually_exclusive_group(required=False)
    cpp_version_group.add_argument(
        "--std",
        help="build using the specified C++ standard version",
        default="c++14",
        metavar="STANDARD",
        dest="std")
    cpp_version_group.add_argument(
        "--c++latest",
        help="build using the latest features of the C++ standard version and"
             "its drafts (default is C++14)",
        action="store_const",
        const="c++latest",
        dest="std")
    cpp_version_group.add_argument(
        "--c++2a",
        help="build using the next C++ standard draft (default is C++14)",
        action="store_const",
        const="c++2a",
        dest="std")
    cpp_version_group.add_argument(
        "--c++17",
        help="build using the C++17 standard version (default is C++14)",
        action="store_const",
        const="c++17",
        dest="std")
    cpp_version_group.add_argument(
        "--c++14",
        help="build using the C++14 standard version (default)",
        action="store_const",
        const="c++14",
        dest="std")

    return parser

def build_variant_options(parser):
    build_variant_group = parser.add_mutually_exclusive_group(required=False)
    build_variant_group.add_argument(
        "-d", "--debug",
        help="build the Debug variant of everything (default)",
        action="store_const",
        const="Debug",
        dest="build_variant")
    build_variant_group.add_argument(
        "-r", "--release-debuginfo",
        help="build the RelWithDebInfo variant of everything (default is "
             "Debug)",
        action="store_const",
        const="RelWithDebInfo",
        dest="build_variant")
    build_variant_group.add_argument(
        "-R", "--release",
        help="build the Release variant of everything (default is Debug)",
        action="store_const",
        const="Release",
        dest="build_variant")

    build_variant_override_group = parser.add_argument_group(
        title="Override build variant for a specific project")
    build_variant_override_group.add_argument(
        "--debug-llvm",
        help="build the Debug variant of LLVM",
        action="store_const",
        const="Debug",
        dest="llvm_build_variant")
    build_variant_override_group.add_argument(
        "--debug-libcxx",
        help="build the Debug variant of libc++. This has an effect only if "
             "LLVM is not built",
        action="store_const",
        const="Debug",
        dest="libcxx_build_variant")
    build_variant_override_group.add_argument(
        "--debug-anthem",
        help="build the Debug variant of Unsung Anthem",
        action="store_const",
        const="Debug",
        dest="anthem_build_variant")
    build_variant_override_group.add_argument(
        "--debug-sdl",
        help="build the Debug variant of SDL",
        action="store_const",
        const="Debug",
        dest="sdl_build_variant")
    build_variant_override_group.add_argument(
        "--debug-glfw",
        help="build the Debug variant of GLFW",
        action="store_const",
        const="Debug",
        dest="glfw_build_variant")

    return parser

def assertion_options(parser):
    assertions_group = parser.add_mutually_exclusive_group(required=False)
    assertions_group.add_argument(
        "--assertions",
        help="enable assertions in all projects",
        action="store_const",
        const=True,
        dest="assertions")
    assertions_group.add_argument(
        "--no-assertions",
        help="disable assertions in all projects",
        action="store_const",
        const=False,
        dest="assertions")

    assertions_override_group = parser.add_argument_group(
        title="Control assertions in a specific project")
    assertions_override_group.add_argument(
        "--llvm-assertions",
        help="enable assertions in LLVM",
        action="store_const",
        const=True,
        dest="llvm_assertions")
    assertions_override_group.add_argument(
        "--no-llvm-assertions",
        help="disable assertions in LLVM",
        action="store_const",
        const=False,
        dest="llvm_assertions")
    assertions_override_group.add_argument(
        "--libcxx-assertions",
        help="enable assertions in libc++",
        action="store_const",
        const=True,
        dest="libcxx_assertions")
    assertions_override_group.add_argument(
        "--no-libcxx-assertions",
        help="disable assertions in libc++",
        action="store_const",
        const=False,
        dest="libcxx_assertions")
    assertions_override_group.add_argument(
        "--anthem-assertions",
        help="enable assertions in Unsung Anthem",
        action="store_const",
        const=True,
        dest="anthem_assertions")
    assertions_override_group.add_argument(
        "--no-anthem-assertions",
        help="disable assertions in Unsung Anthem",
        action="store_const",
        const=False,
        dest="anthem_assertions")

    return parser

def cmake_options(parser):
    # FIXME This should perhaps be one option using choices=[...]
    cmake_generator_group = parser.add_argument_group(
        title="Select the CMake generator")
    cmake_generator_group.add_argument(
        "-G",
        help="CMake's generator (default is Ninja)",
        choices=["Ninja",
                 "Xcode",
                 "Unix Makefiles",
                 "Visual Studio 14 2015",
                 "Visual Studio 15 2017",
                 "Eclipse CDT4 - Ninja"],
        dest="cmake_generator")
    cmake_generator_group.add_argument(
        "-x", "--xcode",
        help="use CMake's Xcode generator (default is Ninja)",
        action="store_const",
        const="Xcode",
        dest="cmake_generator")
    cmake_generator_group.add_argument(
        "-m", "--make",
        help="use CMake's Makefile generator (default is Ninja)",
        action="store_const",
        const="Unix Makefiles",
        dest="cmake_generator")
    cmake_generator_group.add_argument(
        "--visual-studio-14",
        help="use CMake's Visual Studio 2015 generator (default is Ninja)",
        action="store_const",
        const="Visual Studio 14 2015",
        dest="cmake_generator")
    cmake_generator_group.add_argument(
        "--visual-studio-2015",
        help="use CMake's Visual Studio 2015 generator (default is Ninja)",
        action="store_const",
        const="Visual Studio 14 2015",
        dest="cmake_generator")
    cmake_generator_group.add_argument(
        "--visual-studio-15",
        help="use CMake's Visual Studio 2017 generator (default is Ninja)",
        action="store_const",
        const="Visual Studio 15 2017",
        dest="cmake_generator")
    cmake_generator_group.add_argument(
        "--visual-studio-2017",
        help="use CMake's Visual Studio 2017 generator (default is Ninja)",
        action="store_const",
        const="Visual Studio 15 2017",
        dest="cmake_generator")
    cmake_generator_group.add_argument(
        "-e", "--eclipse",
        help="use CMake's Eclipse generator (default is Ninja)",
        action="store_const",
        const="Eclipse CDT4 - Ninja",
        dest="cmake_generator")

    parser.add_argument(
        "--extra-cmake-options",
        help="Pass through extra options to CMake in the form of comma "
             "separated options '-DCMAKE_VAR1=YES,-DCMAKE_VAR2=/tmp'. Can be "
             "called multiple times to add multiple such options.",
        action=arguments.ACTION.concat,
        type=arguments.TYPE.shell_split,
        default=[])

    return parser

def test_options(parser):
    run_tests_group = parser.add_argument_group(
        title="Run tests")

    # NOTE We cannot merge -t and --test, because nargs="?" makes '-ti' to be
    # treated as '-t=i'.
    run_tests_group.add_argument(
        "-t",
        help="test Unsung Anthem after building (implies --build-test)",
        action="store_const",
        const=True,
        dest="test")
    run_tests_group.add_argument(
        "--test",
        help="test Unsung Anthem after building (implies --build-test)",
        action=arguments.ACTION.optional_bool)
    run_tests_group.add_argument(
        "-o",
        help="run the test suite in optimized mode too (implies --test and "
             "--build-test-optimized)",
        action="store_const",
        const=True,
        dest="test_optimized")
    run_tests_group.add_argument(
        "--test-optimized",
        help="run the test suite in optimized mode too (implies --test and "
             "--build-test-optimized)",
        action=arguments.ACTION.optional_bool)

    return parser

def build_options(parser):
    run_build_group = parser.add_argument_group(title="Run build")
    run_build_group.add_argument(
        "-S", "--skip-build",
        help="generate build directory only without building",
        action="store_true")

    run_build_group.add_argument(
        "--clion",
        help="install the dependencies and generate the CMake command for "
             "setting up an CLion environment",
        action="store_true")

    run_build_group.add_argument(
        "--skip-build-anthem",
        help="skip building Unsung Anthem",
        action=arguments.ACTION.optional_bool)

    return parser

def checkout_options(parser):
    checkout_group = parser.add_argument_group(title="Update checkout")
    checkout_group.add_argument(
        "--skip-repository",
        metavar="DIRECTORY",
        default=[],
        help="skip the specified repository. To skip a specific LLVM project, "
             "add the prefix llvm- to the name of the project.",
        dest="skip_repository_list",
        action="append")

    return parser

def version_options(parser):
    version_group = parser.add_argument_group(
        title="Dependency and project version information")
    version_group.add_argument(
        "--anthem-version",
        metavar="MAJOR.MINOR.PATCH",
        default="default",
        help="the Unsung Anthem version")
    version_group.add_argument(
        "--llvm-version",
        metavar="MAJOR.MINOR.PATCH",
        default="default",
        help="the LLVM version")
    version_group.add_argument(
        "--gcc-version",
        metavar="MAJOR.MINOR.PATCH",
        default="default",
        help="the GNU Compiler Collection version")
    version_group.add_argument(
        "--cmake-major-version",
        metavar="MAJOR",
        default="default",
        help="the CMake major version")
    version_group.add_argument(
        "--cmake-minor-version",
        metavar="MINOR",
        default="default",
        help="the CMake minor version")
    version_group.add_argument(
        "--cmake-patch-version",
        metavar="PATCH",
        default="default",
        help="the CMake patch version")
    version_group.add_argument(
        "--cmake-minor-patch-version",
        metavar="MINOR_PATCH",
        default="default",
        help="the CMake minor patch version")
    version_group.add_argument(
        "--cmake-version",
        metavar="MAJOR.MINOR.PATCH(.MINOR_PATCH)",
        default="default",
        help="the CMake version. Overrides the major, minor, patch, and minor "
             "patch settings if set")
    version_group.add_argument(
        "--ninja-version",
        metavar="MAJOR.MINOR.PATCH",
        default="default",
        help="the Ninja version")
    version_group.add_argument(
        "--catch-version",
        metavar="MAJOR.MINOR.PATCH",
        default="default",
        help="the Catch version")
    version_group.add_argument(
        "--sdl-version",
        metavar="MAJOR.MINOR.PATCH",
        default="default",
        help="the SDL version")
    version_group.add_argument(
        "--glfw-version",
        metavar="MAJOR.MINOR.PATCH",
        default="default",
        help="the GLFW version")
    version_group.add_argument(
        "--spdlog-version",
        metavar="MAJOR.MINOR.PATCH",
        default="default",
        help="the spdlog version")
    version_group.add_argument(
        "--cat-version",
        metavar="MAJOR.MINOR",
        default="default",
        help="the cat library version")

    return parser

def system_options(parser):
    parser.add_argument(
        "--build-config",
        default=os.path.join(SCRIPT_DIR, "anthem-config.json"),
        metavar='PATH',
        help="the build configuration file to use")

    parser.add_argument(
        "--build-subdir",
        help="name of the directory under $ANTHEM_BUILD_ROOT where the build "
             "products will be placed",
        metavar="PATH")
    parser.add_argument(
        "--shared-build-subdir",
        help="name of the directory under $ANTHEM_BUILD_ROOT where the shared "
             "build products will be placed. Has an effect only if the shared "
             "tools are not disabled",
        metavar="PATH")
    parser.add_argument(
        "--install-prefix",
        help="The installation prefix. This is where built Unsung Anthem "
             "products (like bin, lib, and include) will be installed.",
        metavar="PATH")

    parser.add_argument(
        "-j", "--jobs",
        help="the number of parallel build jobs to use",
        type=int,
        dest="build_jobs",
        default=multiprocessing.cpu_count())

    parser.add_argument(
        "--darwin-xcrun-toolchain",
        help="the name of the toolchain to use on Darwin",
        default="default")
    parser.add_argument(
        "--cmake",
        help="the path to a CMake executable that will be used to build "
             "Unsung Anthem",
        type=arguments.TYPE.executable,
        metavar="PATH")
    parser.add_argument(
        "--git",
        help="the path to a git executable that will be used to clone "
             "possible git projects",
        type=arguments.TYPE.executable,
        metavar="PATH")

    parser.add_argument(
        "--host-cc",
        help="the absolute path to CC, the C compiler for the host platform. "
             "Default is auto detected",
        type=arguments.TYPE.executable,
        metavar="PATH")
    parser.add_argument(
        "--host-cxx",
        help="the absolute path to CXX, the C++ compiler for the host "
             "platform. Default is auto detected",
        type=arguments.TYPE.executable,
        metavar="PATH")
    parser.add_argument(
        "--msbuild",
        help="the absolute path to MSBuild, the Microsoft Visual Studio "
             "compiler for the host platform. Default is auto detected",
        type=arguments.TYPE.executable,
        metavar="PATH")
    parser.add_argument(
        "--main-tool",
        help="the name of the main tool to be looked by the script. The "
             "default is llvm",
        metavar="NAME",
        default="llvm")
    parser.add_argument(
        "--main-tool-version",
        help="the version of the main tool which will be used in the lookup "
             "of the tool",
        metavar="VERSION",
        default="default")
    parser.add_argument(
        "--disable-shared-builds",
        help="disallow sharing dependencies between Unsung Anthem versions if "
             "the versions of the dependencies are the same",
        action="store_true")

    parser.add_argument(
        "--darwin-deployment-version",
        help="minimum deployment target version for macOS",
        metavar="MAJOR.MINOR",
        default="10.9")

    return parser

def msbuild_options(parser):
    msbuild_group = parser.add_argument_group(title="MSBuild options")
    msbuild_group.add_argument(
        "--msbuild-logger",
        help="the absolute path to MSBuild logger",
        metavar="PATH")

    return parser

def program_options(parser):
    parser.add_argument(
        "--executable-name",
        help="the name of the Unsung Anthem executable",
        metavar="NAME")
    parser.add_argument(
        "--test-executable-name",
        help="the name of the Unsung Anthem test executable",
        metavar="NAME")

    return parser

def miscellaneous_options(parser):
    parser.add_argument(
        "--build-args",
        help="arguments to the build tool. This would be prepended to the "
             "default argument that is '-j8' when CMake generator is "
             "\"Ninja\".",
        type=arguments.TYPE.shell_split,
        default=[])

    return parser