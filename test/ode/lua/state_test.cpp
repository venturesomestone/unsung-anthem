/// The tests of the Lua state.
/// \file
/// \author Antti Kivi
/// \date 7 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/lua/state.h"

#include "gsl/util"

#include <gtest/gtest.h>

#include "ode/config.h"
#include "ode/filesystem/path.h"
#include "ode/lua/lua_config.h"

TEST(ode_lua_make_state, created)
{
  auto state = ode::lua::make_state();

  ASSERT_NE(state, nullptr);

  state.reset(nullptr);

  ASSERT_EQ(state, nullptr);
}

TEST(ode_lua_clean, cleaned)
{
  lua_State* state = luaL_newstate();

  luaL_openlibs(state);

  const std::string filename = std::string{ode::test_script_root} +
      ode::filesystem::path::preferred_separator + "state.lua";

  const auto load_error = luaL_loadfile(state, filename.c_str());

  lua_pcall(state, 0, 0, 0);

  const std::string var = "test.level.another";

  gsl::index index = 0;
  std::string current = "";

  for (auto c : var)
  {
    if ('.' == c)
    {
      if (0 == index)
      {
        lua_getglobal(state, current.c_str());
      }
      else
      {
        lua_getfield(state, ode::lua::stack_top, current.c_str());
      }

      current = "";
      index += 1;
    }
    else
    {
      current += c;
    }
  }

  lua_getfield(state, ode::lua::stack_top, current.c_str());

  const auto top1 = lua_gettop(state);

  ASSERT_EQ(top1, ++index);

  ode::lua::clean(state);

  const auto top2 = lua_gettop(state);

  ASSERT_EQ(top2, 0);

  lua_close(state);

  state = nullptr;
}
