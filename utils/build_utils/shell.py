# ===--------------------------- shell.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing shell helpers.
"""

from __future__ import print_function

import os
import pipes
import platform
import shutil
import subprocess
import sys
import tarfile
import zipfile

from contextlib import contextmanager

from . import diagnostics


DEVNULL = getattr(subprocess, "DEVNULL", subprocess.PIPE)

DRY_RUN = False


def _quote(arg):
    return pipes.quote(str(arg))


def quote_command(args):
    """
    quote_command(args) -> str

    Quote the command for passing to a shell.
    """
    return " ".join([_quote(a) for a in args])


def _coerce_dry_run(dry_run_override):
    if dry_run_override is None:
        return DRY_RUN
    else:
        return dry_run_override


def _echo_command(dry_run, command, env=None, prompt="+ "):
    output = []
    if env is not None:
        output += ["env"] + [_quote("%s=%s" % (k, v))
                             for (k, v) in sorted(env.items())]
    output += [_quote(arg) for arg in command]
    file = sys.stderr
    if dry_run:
        file = sys.stdout
    print(prompt + " ".join(output), file=file)
    file.flush()


def call(command, stderr=None, env=None, dry_run=None, echo=True):
    """
    call(command, ...) -> str

    Execute the given command.

    This function will raise an exception on any command failure.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        _echo_command(dry_run, command, env=env)
    if dry_run:
        return
    _env = None
    if env is not None:
        _env = dict(os.environ)
        _env.update(env)
    try:
        subprocess.check_call(command, env=_env, stderr=stderr)
    except subprocess.CalledProcessError as e:
        diagnostics.fatal(
            "command terminated with a non-zero exit status "
            + str(e.returncode)
            + ", aborting")
    except OSError as e:
        diagnostics.fatal(
            "could not execute '"
            + quote_command(command)
            + "': "
            + e.strerror)


def capture(
        command,
        stderr=None,
        env=None,
        dry_run=None,
        echo=True,
        optional=False,
        allow_non_zero_exit=False):
    """
    capture(command, ...) -> str

    Execute the given command and return the standard output.

    This function will raise an exception on any command failure.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        _echo_command(dry_run, command, env=env)
    if dry_run:
        return
    _env = None
    if env is not None:
        _env = dict(os.environ)
        _env.update(env)
    try:
        out = subprocess.check_output(command, env=_env, stderr=stderr)
        # Coerce to `str` hack. not py3 `byte`, not py2 `unicode`.
        return str(out.decode())
    except subprocess.CalledProcessError as e:
        if allow_non_zero_exit:
            return e.output
        if optional:
            return None
        diagnostics.fatal(
            "command terminated with a non-zero exit status "
            + str(e.returncode)
            + ", aborting")
    except OSError as e:
        if optional:
            return None
        diagnostics.fatal(
            "could not execute '"
            + quote_command(command)
            + "': "
            + e.strerror)


@contextmanager
def pushd(path, dry_run=None, echo=True):
    dry_run = _coerce_dry_run(dry_run)
    old_dir = os.getcwd()
    if dry_run or echo:
        _echo_command(dry_run, ["pushd", path])
    if not dry_run:
        os.chdir(path)
    yield
    if dry_run or echo:
        _echo_command(dry_run, ["popd"])
    if not dry_run:
        os.chdir(old_dir)


def makedirs(path, dry_run=None, echo=True):
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        _echo_command(dry_run, ["mkdir", "-p", path])
    if dry_run:
        return
    if not os.path.isdir(path):
        os.makedirs(path)


def rmtree(path, dry_run=None, echo=True):
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        _echo_command(dry_run, ["rm", "-rf", path])
    if dry_run:
        return
    if os.path.exists(path):
        shutil.rmtree(path)


def copytree(src, dest, dry_run=None, echo=True):
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        _echo_command(dry_run, ["cp", "-r", src, dest])
    if dry_run:
        return
    shutil.copytree(src, dest)


def copy(src, dest, dry_run=None, echo=True):
    """
    Copy a file.

    path -- path to the file.
    dest -- the destination directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        _echo_command(dry_run, ["cp", src, dest])
    if dry_run:
        return
    shutil.copy(src, dest)


def move(src, dest, dry_run=None, echo=True):
    """
    Move a directory recursively.

    src -- path to the directory.
    dest -- the destination directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        _echo_command(dry_run, ["mv", "-f", src, dest])
    if dry_run:
        return
    shutil.move(src, dest)


def tar(path, dest=None, dry_run=None, echo=True):
    """
    Extract an archive.

    path -- path to the archive.
    dest -- the destination directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        if dest:
            _echo_command(dry_run, ["tar", "-xf", path, "-C", dest])
        else:
            _echo_command(dry_run, ["tar", "-xf", path])
    if dry_run:
        return
    if path.endswith(".zip"):
        with zipfile.ZipFile(path, "r") as archive:
            if dest:
                archive.extractall(dest)
            else:
                archive.extractall()
    else:
        if path.endswith(".tar") or path.endswith(".tar.gz"):
            with tarfile.open(path) as archive:
                if dest:
                    archive.extractall(dest)
                else:
                    archive.extractall()
        else:
            if sys.version_info.major == 2:
                # TODO Use different command for Windows.
                with pushd(os.path.dirname(path)):
                    if dest:
                        call(
                            ["tar", "-xf", os.path.split(path)[1], "-C", dest])
                    else:
                        call(["tar", "-xf", os.path.split(path)[1]])
            else:
                with tarfile.open(path) as archive:
                    if dest:
                        archive.extractall(dest)
                    else:
                        archive.extractall()


def curl(url, dest, env=None, dry_run=None, echo=True):
    """
    Download a file.

    url -- the URL from which the file is downloaded.
    dest -- the file where the file is downloaded.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    call(
        ["curl", "-o", dest, "--create-dirs", url],
        env=env,
        dry_run=dry_run,
        echo=echo)


def call_without_sleeping(command, env=None, dry_run=False, echo=False):
    """
    Execute a command during which system sleep is disabled.
    By default, this ignores the state of the 'shell.dry_run' flag.
    """

    # Disable system sleep, if possible.
    if platform.system() == "Darwin":
        # Don't mutate the caller's copy of the arguments.
        command = ["caffeinate"] + list(command)

    call(command, env=env, dry_run=dry_run, echo=echo)
