//===----------------------- world_configuration.h --------------*- C++ -*-===//
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
/// \file world_configuration.h
/// \brief The declaration of the type of the scene configurations for the
/// basic gameplay scenes.
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_SYSTEMS_SCENES_WORLD_CONFIGURATION_H
#define ANTHEM_SYSTEMS_SCENES_WORLD_CONFIGURATION_H

#include "ode/systems/scene_configuration.h"

namespace anthem
{
  ///
  /// \class world_configuration
  /// \brief The type of the objects which hold the configurations of the basic
  /// gameplay scenes.
  ///
  class world_configuration : public ode::scene_configuration
  {
  public:
    ///
    /// \brief Constructs an object of the type \c world_configuration.
    ///
    world_configuration() = default;

    ///
    /// \brief Constructs an object of the type \c world_configuration by
    /// copying the given object of the type \c world_configuration.
    ///
    /// \param a a \c world_configuration from which the new one is
    /// constructed.
    ///
    world_configuration(const world_configuration& a) = default;

    ///
    /// \brief Constructs an object of the type \c world_configuration by
    /// moving the given object of the type \c world_configuration.
    ///
    /// \param a a \c world_configuration from which the new one is
    /// constructed.
    ///
    world_configuration(world_configuration&& a) = default;

    ///
    /// \brief Destructs an object of the type \c world_configuration.
    ///
    ~world_configuration() = default;

    ///
    /// \brief Assigns the given object of the type \c world_configuration to
    /// this one by copying.
    ///
    /// \param a a \c world_configuration from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    world_configuration& operator=(const world_configuration& a) = default;

    ///
    /// \brief Assigns the given object of the type \c world_configuration to
    /// this one by moving.
    ///
    /// \param a a \c world_configuration from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    world_configuration& operator=(world_configuration&& a) = default;
  };

} // namespace anthem

#endif // !ANTHEM_SYSTEMS_SCENES_WORLD_CONFIGURATION_H
