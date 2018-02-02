//===---------------------------- logging.cpp -------------------*- C++ -*-===//
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
/// \file logging.cpp
/// \brief Definitions of the logging-related utility functions.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/logging.h"

namespace ode
{
  logger_t create_logger(
      const std::string& name,
      const std::string& pattern,
      const spdlog::level::level_enum level)
  {
    auto logger = spdlog::stdout_logger_mt(name);

    if (pattern != "NONE")
    {
      logger->set_pattern(pattern);
    }

    logger->set_level(level);

    return logger;
  }
} // namespace ode
