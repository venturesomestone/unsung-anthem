/// The declaration of the type of objects that contain information about one
/// command line option.
/// \file
/// \author Antti Kivi
/// \date 19 March 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_OPTION_H
#define ODE_CLI_OPTION_H

#include <cstddef>

#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

#include "ode/argv_t.h"
#include "ode/cli/option_type.h"

namespace ode::cli
{
  ///
  /// The string which is prefixed to the long names of the options.
  ///
#if _WIN32
  constexpr auto option_prefix = "/";
#else
  constexpr auto option_prefix = "--";
#endif // !_WIN32

  ///
  /// The string which is prefixed to the short names of the options.
  ///
#if _WIN32
  constexpr auto short_option_prefix = "/";
#else
  constexpr auto short_option_prefix = "-";
#endif // !_WIN32

  ///
  /// The string which is used to separate the option from its value if a space
  /// isn’t used to do so.
  ///
  /// The separator can only be used with the longer option names.
  ///
#if _WIN32
  constexpr auto value_separator = ":";
#else
  constexpr auto value_separator = "=";
#endif // !_WIN32

  ///
  /// The index of the element containing pointer to the parsed option in the
  /// tuple containing information about one parsed command line option.
  ///
  constexpr std::size_t parsed_option_index = 0;

  ///
  /// The index of the element containing the value of the parsed option in the
  /// tuple containing information about one parsed command line option.
  ///
  constexpr std::size_t parsed_value_index = 1;

  ///
  /// The index of the element containing the indices of the parsed option in
  /// the tuple containing information about one parsed command line option.
  ///
  constexpr std::size_t parsed_indices_index = 2;

  ///
  /// The type of objects which contain information about one command line
  /// option for the command line parser.
  ///
  class option final
  {
  public:
    ///
    /// The type of the command line option values.
    ///
    using value_t =
        std::variant<std::nullptr_t, bool, int, double, std::string>;

    ///
    /// The type of the objects returned when parsing a command line option.
    ///
    using parsed_value_t =
        std::tuple<const option*, std::optional<value_t>, std::vector<int>>;

    ///
    /// Constructs an object of the type \c option.
    ///
    option();

    ///
    /// Constructs an object of the type \c option.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param type an enumerable value representing type of the values which
    /// this command line option accepts.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const option_type type,
        const value_t& default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option.
    ///
    /// \param name the long name of the command line option.
    /// \param type an enumerable value representing type of the values which
    /// this command line option accepts.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const option_type type,
        const value_t& default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a Boolean
    /// value.
    ///
    /// The command line options accepting Boolean values don’t necessarily
    /// need any explicit value. A useful rule of thumb of their functionality
    /// is that when they’re specifed, the value is the opposite of the default
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const bool default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a Boolean
    /// value.
    ///
    /// The command line options accepting Boolean values don’t necessarily
    /// need any explicit value. A useful rule of thumb of their functionality
    /// is that when they’re specifed, the value is the opposite of the default
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(const std::string& name, const bool default_v, const bool r);

    ///
    /// Constructs an object of the type \c option which accepts an integer
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const int default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts an integer
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(const std::string& name, const int default_v, const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a double
    /// precision floating point value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const double default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a double
    /// precision floating point value.
    ///
    /// \param name the long name of the command line option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(const std::string& name, const double default_v, const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a string
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const std::string& default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a string
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(const std::string& name, const std::string& default_v, const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a string
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const char* default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a string
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(const std::string& name, const char* default_v, const bool r);

    ///
    /// Constructs an object of the type \c option by copying the given object
    /// of the type \c option.
    ///
    /// \param a an \c option from which the new one is constructed.
    ///
    option(const option& a) = default;

    ///
    /// Constructs an object of the type \c option by moving the given object
    /// of the type \c option.
    ///
    /// \param a an \c option from which the new one is constructed.
    ///
    option(option&& a) = default;

    ///
    /// Destructs an object of the type \c option.
    ///
    ~option() = default;

    ///
    /// Assigns the given object of the type \c option to this one by copying.
    ///
    /// \param a an \c option from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option& operator=(const option& a) = delete;

    ///
    /// Assigns the given object of the type \c option to this one by moving.
    ///
    /// \param a an \c option from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option& operator=(option&& a) = delete;

    ///
    /// Parses this option from the command line arguments.
    ///
    /// This function doesn’t do any checks regarding command line option
    /// requirements nor mutual exclusivity. It simply parses the value of the
    /// option.
    ///
    /// If the option is found but the value given to it is invalid, the first
    /// element in the return value is set to \c std::nullopt but the second
    /// element will still contain the parsed indices.
    ///
    /// \param argc the number of arguments passed in the execution.
    /// \param argv an array containing the arguments passed in the execution.
    /// \param all_options an object of the type \c std::vector containing a
    /// simple list of pointers to all of the possible options.
    /// \param parsed_indices an object of the type \c std::vector containing
    /// the values and indices of the command line arguments which are already
    /// parsed and, thus, should be skipped when parsing this option.
    /// \param prefix a string which is prefixed to the long names of the
    /// options.
    /// \param short_prefix a string which is prefixed to the long names of the
    /// options.
    /// \param alternative_prefix a string which is also accepted as a prefix
    /// for both long and short option.
    /// \param separator a string which is used to separate the option from its
    /// value if a space isn’t used to do so.
    /// \param use_alternative_name whether or not to use the alternative,
    /// camel case name of the option.
    /// \param allow_separator_for_short whether or not allow to use the
    /// separator to separate the short options from the values.
    /// \param allow_combining whether or not it’s allowed to specify multiple
    /// short, one-character options together.
    ///
    /// \return An object of the type \c std::pair, the first element of which
    /// is an object of the type \c std::optional which contains an object of
    /// the type \c value_t if the parsing is successful, and the second
    /// element of which is an object of the type \c std::vector containing the
    /// indices of the command line arguments that were parsed.
    ///
    parsed_value_t parse_option(
        const int argc,
        ode::argv_t argv[],
        const std::vector<option*> all_options,
        const std::vector<parsed_value_t>& parsed_indices,
        const std::string_view prefix,
        const std::string_view short_prefix,
        const std::string_view alternative_prefix,
        const std::string_view separator,
        const bool use_alternative_name,
        const bool allow_separator_for_short,
        const bool allow_combining) const;

    ///
    /// Parses this option from the command line arguments.
    ///
    /// This overload of the function should be preferred to the ‘full’ variant
    /// as it uses correct prefixes, separators, and name variants for the
    /// current platform.
    ///
    /// This function doesn’t do any checks regarding command line option
    /// requirements nor mutual exclusivity. It simply parses the value of the
    /// option.
    ///
    /// If the option is found but the value given to it is invalid, the first
    /// element in the return value is set to \c std::nullopt but the second
    /// element will still contain the parsed indices.
    ///
    /// \param argc the number of arguments passed in the execution.
    /// \param argv an array containing the arguments passed in the execution.
    /// \param all_options an object of the type \c std::vector containing a
    /// simple list of pointers to all of the possible options.
    /// \param parsed_indices an object of the type \c std::vector containing
    /// the values and indices of the command line arguments which are already
    /// parsed and, thus, should be skipped when parsing this option.
    ///
    /// \return An object of the type \c std::pair, the first element of which
    /// is an object of the type \c std::optional which contains an object of
    /// the type \c value_t if the parsing is successful, and the second
    /// element of which is an object of the type \c std::vector containing the
    /// indices of the command line arguments that were parsed.
    ///
    parsed_value_t parse_option(
        const int argc,
        ode::argv_t argv[],
        const std::vector<option*> all_options,
        const std::vector<parsed_value_t>& parsed_indices) const;

    ///
    /// Gives the long name of this command line option.
    ///
    /// TODO: Contemplate the possibility of making the name case-insensitive.
    ///
    /// \return An object of the type \c std::string.
    ///
    std::string name() const;

    ///
    /// Gives the alternative, camel case long name of this command line
    /// option.
    ///
    /// TODO: Contemplate the possibility of making the alternative name
    /// case-insensitive.
    ///
    /// \return An object of the type \c std::string.
    ///
    std::string alternative_name() const;

    ///
    /// Gives the short, one-character name of this command line option.
    ///
    /// \return An object of the type \c std::optional which contains an object
    /// of the type \c std::string if the option has a short, one-character
    /// name.
    ///
    std::optional<std::string> short_name() const;

    ///
    /// Gives an enumerable value representing the type of the values this
    /// command line option accepts.
    ///
    /// \return A value of the enumerable type \c option_type.
    ///
    option_type type() const;

    ///
    /// Gives the default value of the command line option.
    ///
    /// \return An object of the type \c value_t.
    ///
    value_t default_value() const;

    ///
    /// Gives a Boolean value telling whether or not this command line option is
    /// required.
    ///
    /// An option group may ignore the value of this Boolean if the group is
    /// for example mutually exclusive.
    ///
    /// \return A value of the type \c bool.
    ///
    bool required() const;

  private:
    friend bool operator==(const option& lhs, const option& rhs) noexcept;

    ///
    /// The long name of the command line option.
    ///
    const std::string n;

    ///
    /// The alternative, Windows-only long name of the command line option.
    ///
    const std::string alt_n;

    ///
    /// The short, one-character name of the command line option.
    ///
    const std::optional<std::string> short_n;

    ///
    /// The enumerable value representing the type of the values this command
    /// line option accepts.
    ///
    const option_type t;

    ///
    /// The default value of the command line option.
    ///
    const value_t default_v;

    ///
    /// Whether or not this option is required.
    ///
    /// An option group may ignore the value of this Boolean if the group is
    /// for example mutually exclusive.
    ///
    const bool req;
  };

  ///
  /// Compares two objects of the type \c option.
  ///
  /// \param lhs the left-hand side object of the operator.
  /// \param rhs the right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  bool operator==(const option& lhs, const option& rhs) noexcept;

  ///
  /// Compares two objects of the type \c option.
  ///
  /// \param lhs the left-hand side object of the operator.
  /// \param rhs the right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are not equal,
  /// otherwise \c false.
  ///
  bool operator!=(const option& lhs, const option& rhs) noexcept;

  ///
  /// Inserts the formatted data of an object of the type \c option to the
  /// given \c std::ostream.
  ///
  /// \param os the stream to which the data is inserted.
  /// \param a the object, the data of which is inserted.
  ///
  /// \return A reference of the \c std::ostream.
  ///
  std::ostream& operator<<(std::ostream& os, const option& a);

} // namespace ode::cli

#endif // !ODE_CLI_OPTION_H
