//===------------------------------ state.h ---------------------*- C++ -*-===//
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
/// \file state.h
/// \brief Declarations of Lua state utilities
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_STATE_H
#define ODE_LUA_STATE_H

#include "ode/lua/state_t.h"

namespace ode::lua
{
  ///
  /// \brief Initializes a new Lua state.
  ///
  /// \return Pointer to the new \c lua_State.
  ///
  state_t make_state() noexcept;

  ///
  /// \brief Resets the given Lua state.
  ///
  /// \param state Lua state to reset.
  ///
  void clean(const state_ptr_t state) noexcept;

} // namespace ode::lua

#endif // !ODE_LUA_STATE_H
