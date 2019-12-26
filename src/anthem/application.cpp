//===-------------------------- application.cpp -----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file application.cpp
/// \brief The definition of the application type.
/// \author Antti Kivi
/// \date 10 June 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "anthem/application.h"

#include <stdexcept>

#include "ode/systems/graphics/graphics_system.h"

#include "anthem/systems/input/input_system.h"
#include "anthem/systems/scenes/world/world_configuration.h"

namespace anthem
{
  ode::system_t application::make_system(const ode::system_type type)
  {
    if (ode::system_type::graphics == type)
    {
      return ode::graphics_system{};
    }
    else if (ode::system_type::input == type)
    {
      return input_system{};
    }

    throw std::runtime_error{"The system type is invalid"};
  }

  std::vector<ode::system_t> application::make_other_systems()
  {
    return {};
  }

  ode::scene_configuration_t application::first_scene() const
  {
    return ode::scene_configuration_t{world_configuration{"test"}};
  }
} // namespace anthem