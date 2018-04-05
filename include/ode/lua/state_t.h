//===----------------------------- state_t.h --------------------*- C++ -*-===//
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
/// \file state_t.h
/// \brief Declarations of Lua state types.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_STATE_T_H
#define ODE_LUA_STATE_T_H

#include <memory>

#include "gsl/view"

#include <lua.hpp>

namespace ode::lua
{
  ///
  /// \brief Type of Lua state objects.
  ///
  using state_t = std::unique_ptr<lua_State, decltype(&lua_close)>;

  ///
  /// \brief Pointer type which is used as parameter for passing a raw Lua
  /// state.
  ///
  using state_ptr_t = gsl::not_null<lua_State*>;

} // namespace ode::lua

#endif // !ODE_LUA_STATE_T_H