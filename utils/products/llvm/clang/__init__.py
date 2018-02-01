#===----------------------------- __init__.py ----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


from . import build

from .build import clang_bin_path, clang_cxx_bin_path, set_up


__all__ = ["build", "clang_bin_path", "clang_cxx_bin_path", "set_up"]
