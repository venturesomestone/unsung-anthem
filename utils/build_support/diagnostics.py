#===------------------------- diagnostics.py ------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing diagnostic logging functions.
"""

from __future__ import print_function

import sys


ENDC = "\033[0m"
BOLD = "\033[1m"
UNDERLINE = "\033[4m"

RED = "\033[31m"
GREEN = "\033[32m"
ORANGE = "\033[33m"
BLUE = "\033[34m"
PURPLE = "\033[35m"

FAIL = "\033[91m"
OK_GREEN = "\033[92m"
WARNING = "\033[93m"
OK_BLUE = "\033[94m"
HEADER = "\033[95m"


def printer(level, colour=None, do_print=True, print_script=False,
            show_type=False):
    """
    Decorator for printing a diagnostic notification to the standard output.

    level -- the level of the message.
    colour -- the colour of the message.
    do_print -- whether or not the message is printed.
    print_script -- whether or not the script file should be printed.
    show_type -- whether or not to print the type of the command before it.
    """
    def _printer_decorator(func):
        def _wrapper(message):
            executable = sys.argv[0] + ": " if print_script else ""
            message_type = "{}: ".format(level) if show_type else ""

            if colour is not None:
                full_message = "{}{}{}{}{}".format(executable, colour,
                                                   message_type, func(message),
                                                   ENDC)
            else:
                full_message = "{}{}{}".format(executable, message_type,
                                               func(message))

            if do_print:
                print(full_message)

            sys.stdout.flush()

            return full_message

        return _wrapper

    return _printer_decorator


@printer(level="debug")
def debug(message):
    """
    Print a debug diagnostic notification to the standard output.

    message -- the message to be printed.
    """
    return message


@printer(level="debug", colour=OK_GREEN)
def debug_ok(message):
    """
    Print a debug diagnostic notification to the standard output.

    message -- the message to be printed.
    """
    return message


@printer(level="note", colour=OK_BLUE)
def fine(message):
    """
    Print a diagnostic notification to the standard output notifying some step
    is complete.

    message -- the message to be printed.
    """
    return message


@printer(level="note", colour=HEADER + BOLD)
def head(message):
    """
    Print a header diagnostic notification to the standard output.

    message -- the message to be printed.
    """
    return message


@printer(level="note")
def note(message):
    """
    Print a diagnostic notification to the standard output.

    message -- the message to be printed.
    """
    return message


@printer(level="warning", colour=WARNING)
def warn(message):
    """
    Print a warning notification to the standard output.

    message -- the message to be printed.
    """
    return message


def warning(message):
    """
    Print a warning notification to the standard output.

    message -- the message to be printed.
    """
    warn(message=message)


def fatal(message):
    """
    Raise a fatal error.

    message -- the message to be printed.
    """

    @printer(level="fatal error", colour=BOLD + FAIL, do_print=False)
    def _impl(message):
        return message

    raise SystemExit(_impl(message))