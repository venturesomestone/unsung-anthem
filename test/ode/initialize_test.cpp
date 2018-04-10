//===------------------------ initialize_test.cpp ---------------*- C++ -*-===//
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
/// \file initialize_test.cpp
/// \brief Tests of definitions of initialization functions of Obliging Ode.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/initialize.h"

#include <gtest/gtest.h>

TEST(ode_initalize, sdl)
{
  // Use a separate scope to ensure that SDL is quit.
  {
    ASSERT_NO_THROW(ode::initialize_sdl());
  }
}