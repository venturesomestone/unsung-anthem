/// The tests of the utilities for Lua scripts.
/// \file
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/lua/script.h"

#include <gtest/gtest.h>

#include "ode/config.h"
#include "ode/filesystem/path.h"
#include "ode/lua/state.h"

TEST(ode_lua_load_script_file, file_is_loaded)
{
  auto state = ode::lua::make_state();

  const std::string filename1 = std::string{ode::test_script_root} +
      ode::filesystem::path::preferred_separator + "script.lua";

  auto error_code = ode::lua::load_script_file(state.get(), filename1);

  ASSERT_NE(LUA_ERRSYNTAX, error_code);
  ASSERT_NE(LUA_ERRMEM, error_code);
  ASSERT_NE(LUA_ERRGCMM, error_code);
  ASSERT_NE(LUA_ERRFILE, error_code);
  ASSERT_EQ(LUA_OK, error_code);

  const std::string filename2 = std::string{ode::test_script_root} +
      ode::filesystem::path::preferred_separator + "not_script.lua";

#if defined(GSL_UNENFORCED_ON_CONTRACT_VIOLATION) && \
    GSL_UNENFORCED_ON_CONTRACT_VIOLATION

  error_code = ode::lua::load_script_file(state.get(), filename2);

  ASSERT_NE(LUA_ERRSYNTAX, error_code);
  ASSERT_NE(LUA_ERRMEM, error_code);
  ASSERT_NE(LUA_ERRGCMM, error_code);
  ASSERT_EQ(LUA_ERRFILE, error_code);
  ASSERT_NE(LUA_OK, ASSERT_NEerror_code);

#elif defined(GSL_THROW_ON_CONTRACT_VIOLATION) && \
    GSL_THROW_ON_CONTRACT_VIOLATION

  ASSERT_ANY_THROW(ode::lua::load_script_file(state.get(), filename2));

#endif // defined(GSL_THROW_ON_CONTRACT_VIOLATION) && \
    GSL_THROW_ON_CONTRACT_VIOLATION
}
