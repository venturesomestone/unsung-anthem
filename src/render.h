//===-------------------------- render.h ------------------------*- C++ -*-===//
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
/// \file render.h
/// \brief The declarations of the rendering-related functions.
/// \author Antti Kivi
/// \date 26 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_RENDER_H
#define ANTHEM_RENDER_H

namespace anthem
{
  struct game_state;
}

namespace anthem
{
  ///
  /// \brief Renders a game state.
  ///
  /// \param state the game state.
  ///
  void render_state(const game_state& state);

} // namespace anthem

#endif // !ANTHEM_RENDER_H
