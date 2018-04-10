//===----------------------------- version.h --------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2018 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file version.h
/// \brief Declarations of Simple DirectMedia Layer version utility functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_VERSION_H
#define ODE_SDL_VERSION_H

struct SDL_version;

namespace ode::sdl
{
  ///
  /// \brief Gets an object of type \c SDL_version which represents the version
  /// of the Simple DirectMedia Layer against which the program was compiled.
  ///
  /// \return An object of type \c SDL_version.
  ///
  SDL_version compiled_version();

  ///
  /// \brief Gets an object of type \c SDL_version which represents the version
  /// of the Simple DirectMedia Layer against which the program is currently linked.
  ///
  /// \return An object of type \c SDL_version.
  ///
  SDL_version linked_version();

} // namespace ode::sdl

#endif // !ODE_SDL_VERSION_H