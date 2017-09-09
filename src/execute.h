//===-------------------------- execute.h -----------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file execute.h
/// \brief The declaration of the main execution function of the game engine.
/// \author Antti Kivi
/// \date 29 June 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_EXECUTE_H
#define ANTHEM_EXECUTE_H

#include <memory>

namespace anthem {
  class game_state;
}

namespace anthem {

  ///
  /// \brief Returns the object of type \c game_state after executing the
  /// program with the given arguments.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv array containing the arguments passed in the execution.
  ///
  /// \return The object of type \c game_state.
  ///
  game_state execute(int argc, const char* argv[]);

} // namespace anthem

#endif // !ANTHEM_EXECUTE_H
