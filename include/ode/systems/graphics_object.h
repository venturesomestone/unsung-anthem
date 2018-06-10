//===------------------------- graphics_object.h ----------------*- C++ -*-===//
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
/// \file graphics_object.h
/// \brief The declaration of the type of the graphics system objects.
/// \author Antti Kivi
/// \date 8 May 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_GRAPHICS_OBJECT_H
#define ODE_SYSTEMS_GRAPHICS_OBJECT_H

#include "ode/systems/object.h"
#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// \class graphics_object
  /// \brief The type of the graphics system objects.
  ///
  class graphics_object final : public object
  {
  public:
    ///
    /// \brief The system type of this object.
    ///
    static constexpr system_type type = system_type::graphics;

    ///
    /// \brief Constructs an object of the type \c graphics_object.
    ///
    graphics_object() = default;

    ///
    /// \brief Constructs an object of the type \c graphics_object by copying
    /// the given object of the type \c graphics_object.
    ///
    /// \param a a \c graphics_object from which the new one is constructed.
    ///
    graphics_object(const graphics_object& a) = default;

    ///
    /// \brief Constructs an object of the type \c graphics_object by moving
    /// the given object of the type \c graphics_object.
    ///
    /// \param a a \c graphics_object from which the new one is constructed.
    ///
    graphics_object(graphics_object&& a) = default;

    ///
    /// \brief Destructs an object of the type \c graphics_object.
    ///
    ~graphics_object() = default;

    ///
    /// \brief Assigns the given object of the type \c graphics_object to this
    /// one by copying.
    ///
    /// \param a a \c graphics_object from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_object& operator=(const graphics_object& a) = default;

    ///
    /// \brief Assigns the given object of the type \c graphics_object to this
    /// one by moving.
    ///
    /// \param a a \c graphics_object from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_object& operator=(graphics_object&& a) = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_GRAPHICS_OBJECT_H