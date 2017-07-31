//===--- util_test.cpp ------------------------------------------*- C++ -*-===//
//
//                           Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file util_test.cpp
/// \brief Tests of the implementations of Guideline Support Library utility
/// types.
/// \author Antti Kivi
/// \date 31 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "gsl/util"

#include "anthem/__config.h"

TEST_CASE("the Callable of a final_action is invoked at the end of the scope",
          "[gsl::final_action]") {

  int i = 0;

  auto f = [&]() {
    ++i;
  };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    gsl::final_action<decltype(f)> a{f};
  }

  REQUIRE_FALSE(0 == i);
  REQUIRE(1 == i);
}

TEST_CASE("the Callable is not invoked twice if final_action is moved",
          "[gsl::final_action]") {

  int i = 0;

  auto f = [&]() {
    ++i;
  };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    gsl::final_action<decltype(f)> a{f};
    gsl::final_action<decltype(f)> b{std::move(a)};
  }

  REQUIRE_FALSE(0 == i);
  REQUIRE(1 == i);
  REQUIRE_FALSE(2 == i);
}

TEST_CASE("finally creates final_action which invokes the Callable correctly",
          "[gsl::finally]") {

  int i = 0;

  auto f = [&]() {
    ++i;
  };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    auto a = gsl::finally<decltype(f)>(f);
  }

  REQUIRE_FALSE(0 == i);
  REQUIRE(1 == i);
}

TEST_CASE("narrow_cast casts as expected", "[gsl::narrow_cast]") {

  int i = 0;
  auto j = gsl::narrow_cast<unsigned int>(i);

  #if HAS_CXX17_TYPE_TRAITS

    constexpr bool a = std::is_same_v<decltype(j), unsigned int>;
    constexpr bool b = std::is_same_v<decltype(j), int>;

  #elif HAS_EXPERIMENTAL_TYPE_TRAITS

    constexpr bool a = std::experimental::is_same_v<decltype(j), unsigned int>;
    constexpr bool b = std::experimental::is_same_v<decltype(j), int>;

  #else

    constexpr bool a = std::is_same<decltype(j), unsigned int>::value;
    constexpr bool b = std::is_same<decltype(j), int>::value;

  #endif // !(HAS_CXX17_TYPE_TRAITS && HAS_EXPERIMENTAL_TYPE_TRAITS)

  REQUIRE(a);
  REQUIRE_FALSE(b);
}
