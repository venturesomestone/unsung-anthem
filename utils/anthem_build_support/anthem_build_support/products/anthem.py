# anthem_build_support/products/anthem.py ------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Unsung Anthem build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import (diagnostics, shell)
from ..call import (call_without_sleeping,
                    call_ninja,
                    call_ninja_install,
                    call_make,
                    call_make_install)
from ..variables import ANTHEM_REPO_NAME


class Anthem(product.Product):
    def do_build(self):
        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build Unsung Anthem from.
            call_without_sleeping([self.toolchain.cmake,
                                   self.source_dir,
                                   '-G',
                                   self.args.cmake_generator,
                                   '-DANTHEM_INSTALL_PREFIX='
                                   + self.workspace.install_root])

            # Build.
            if self.args.cmake_generator == 'Ninja':
                call_ninja()
                call_ninja_install()
            elif self.args.cmake_generator == 'Unix Makefiles':
                call_make()
                call_make_install()


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir(ANTHEM_REPO_NAME)):
        diagnostics.fatal('cannot find source directory for Unsung Anthem '
                          '(tried %s)'
                          % (workspace.source_dir(ANTHEM_REPO_NAME)))

    anthem_build = Anthem(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.source_dir(ANTHEM_REPO_NAME),
                          build_dir=workspace.build_dir(args.host_target,
                                                        'anthem'))

    anthem_build.do_build()
