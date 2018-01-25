//===-------------------------- logger.h ------------------------*- C++ -*-===//
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
/// \file logger.h
/// \brief Declarations of main logging functions.
/// \author Antti Kivi
/// \date 14 December 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_LOGGER_H
#define ANTHEM_LOGGER_H

#include "anthem/logging.h"

///
/// \def ANTHEM_TRACE(...)
/// \brief Preprocessor macro which is used for trace-level logging.
///
#define ANTHEM_TRACE(...) ::anthem::logging::trace(__VA_ARGS__)

///
/// \def ANTHEM_DEBUG(...)
/// \brief Preprocessor macro which is used for debug-level logging.
///
#define ANTHEM_DEBUG(...) ::anthem::logging::debug(__VA_ARGS__)

///
/// \def ANTHEM_INFO(...)
/// \brief Preprocessor macro which is used for info-level logging.
///
#define ANTHEM_INFO(...) ::anthem::logging::info(__VA_ARGS__)

///
/// \def ANTHEM_WARN(...)
/// \brief Preprocessor macro which is used for warning-level logging.
///
#define ANTHEM_WARN(...) ::anthem::logging::warn(__VA_ARGS__)

///
/// \def ANTHEM_ERROR(...)
/// \brief Preprocessor macro which is used for error-level logging.
///
#define ANTHEM_ERROR(...) ::anthem::logging::error(__VA_ARGS__)

///
/// \def ANTHEM_CRITICAL(...)
/// \brief Preprocessor macro which is used for critical-level logging.
///
#define ANTHEM_CRITICAL(...) ::anthem::logging::critical(__VA_ARGS__)

namespace anthem
{
  ///
  /// \brief The main logger of the game.
  ///
  extern logger_t logger;
  
  // Logging methods which use the global logger.
  namespace logging
  {
    ///
    /// \brief Writes a trace-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void trace(const char* fmt, const Args&... args)
    {
      trace(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes a trace-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <class T> inline void trace(const T& msg)
    {
      trace(logger, msg);
    }
    
    ///
    /// \brief Writes a debug-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void debug(const char* fmt, const Args&... args)
    {
      debug(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes a debug-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <class T> inline void debug(const T& msg)
    {
      debug(logger, msg);
    }
    
    ///
    /// \brief Writes an info-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void info(const char* fmt, const Args&... args)
    {
      info(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes an info-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <class T> inline void info(const T& msg)
    {
      info(logger, msg);
    }
    
    ///
    /// \brief Writes a warning-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void warn(const char* fmt, const Args&... args)
    {
      warn(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes a warning-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <class T> inline void warn(const T& msg)
    {
      warn(logger, msg);
    }
    
    ///
    /// \brief Writes an error-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void error(const char* fmt, const Args&... args)
    {
      error(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes an error-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <class T> inline void error(const T& msg)
    {
      error(logger, msg);
    }
    
    ///
    /// \brief Writes a critical-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void critical(const char* fmt, const Args&... args)
    {
      critical(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes a critical-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <class T>
    inline void critical(const T& msg)
    {
      critical(logger, msg);
    }
    
  } // namespace logging
} // namespace anthem

#endif // !ANTHEM_LOGGER_H
