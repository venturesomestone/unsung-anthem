//===---------------------------- scheduler.h -------------------*- C++ -*-===//
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
/// \file scheduler.h
/// \brief The declaration of the scheduler which executes the updates of the
/// application on each frame.
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_SCHEDULER_H
#define ODE_FRAMEWORK_SCHEDULER_H

#include "ode/engine_framework.h"
#include "ode/framework/state.h"

namespace ode
{
  ///
  /// \brief Runs the next frame of the application and constructs the state
  /// from it.
  ///
  /// TODO
  ///
  template <typename A>
  state update_state(const state& previous, engine_framework<A>& engine)
  {
    return {};
  }

} // namespace ode

#endif // !ODE_FRAMEWORK_SCHEDULER_H