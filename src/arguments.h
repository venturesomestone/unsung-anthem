//===------------------------- arguments.h ----------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file arguments.h
/// \brief The declarations of the utilities related to parsing command line
/// arguments.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_ARGUMENTS_H
#define ANTHEM_ARGUMENTS_H

#include <type_traits>

#include "anthem/logging.h"
#include "anthem/types.h"

namespace anthem {

  ///
  /// \struct arguments
  /// \brief Type of objects which hold parsed information of command line
  /// arguments.
  ///
  struct arguments final {
    ///
    /// \brief Constructs an object of class \c arguments with no data.
    ///
    arguments() noexcept = default;

    ///
    /// \brief Constructs an object of class \c arguments.
    ///
    /// \param window_width value of the starting width of the window.
    /// \param window_height value of the starting height of the window.
    ///
    constexpr arguments(const pixel_count window_width,
                        const pixel_count window_height) noexcept
    : window_width{window_width}, window_height{window_height} {

    }

    ///
    /// \brief Constructs an object of class \c arguments which has the same
    /// values as the original object \c a.
    ///
    /// \param a object from which values are copied into the constructed
    /// object.
    ///
    constexpr arguments(const arguments& a) noexcept = default;

    ///
    /// \brief Constructs an object of class \c arguments and moves the values
    /// of \c a to the constructed object.
    ///
    /// \param a object from which values are moved into the constructed object.
    ///
    constexpr arguments(arguments&& a) noexcept = default;

    ///
    /// \brief Destructs an object of class \c arguments.
    ///
    ~arguments() noexcept = default;

    ///
    /// \brief Copies the values of \c a and replaces the values of \c *this by
    /// them.
    ///
    /// \param a object of class \c arguments from which the values are copied.
    ///
    /// \return Reference to \c *this.
    ///
    constexpr arguments& operator=(const arguments& a) noexcept = delete;

    ///
    /// \brief Moves the values of \c a and replaces the values of \c *this by
    /// them.
    ///
    /// \param a object of class \c arguments from which the values are moved.
    ///
    /// \return Reference to \c *this.
    ///
    constexpr arguments& operator=(arguments&& a) noexcept = delete;

    ///
    /// \brief The starting width of the window.
    ///
    const pixel_count window_width{0};

    ///
    /// \brief The starting height of the window.
    ///
    const pixel_count window_height{0};
  };

  ///
  /// \brief Compares the two objects of class \c arguments.
  ///
  /// \param lhs left-hand side object of the operator.
  /// \param rhs right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  constexpr const bool operator==(const arguments& lhs,
                                  const arguments& rhs) noexcept {

    return lhs.window_width == rhs.window_width &&
           lhs.window_height == rhs.window_height;
  }

  ///
  /// \brief Compares the two objects of class \c arguments.
  ///
  /// \param lhs left-hand side object of the operator.
  /// \param rhs right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are not equal,
  /// otherwise \c false.
  ///
  constexpr const bool operator!=(const arguments& lhs,
                                  const arguments& rhs) noexcept {

    return lhs.window_width == rhs.window_width &&
           lhs.window_height == rhs.window_height;
  }

  ///
  /// \brief Returns an object of class \c arguments which contains the values
  /// set when executing the program from the command line.
  ///
  /// \param logger the main logger.
  /// \param argc the number of arguments passed in the execution.
  /// \param argv array containing the arguments passed in the execution.
  ///
  /// \return An object of class \c arguments.
  ///
  const arguments parse_arguments(const logging::logger_t& logger,
                                  const int argc, const char* argv[]) noexcept;

} // namespace anthem

#endif // !ANTHEM_ARGUMENTS_H
