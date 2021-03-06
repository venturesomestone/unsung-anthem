/// The definition of the initialization utility function for Simple
/// DirectMedia Layer.
/// \file
/// \author Antti Kivi
/// \date 6 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/sdl/initialize_sdl.h"

#include <stdexcept>
#include <string>

#include "ode/logger.h"
#include "ode/sdl/sdl_version.h"

namespace ode::sdl
{
  void initialize()
  {
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
      ODE_ERROR("The Simple DirectMedia Layer initialization failed");
      const std::string error = std::string{SDL_GetError()};
      throw std::runtime_error{
          std::string{"The Simple DirectMedia Layer initialization failed, '"} +
          error + "'"};
    }

    ODE_DEBUG("Simple DirectMedia Layer is initialized");

    auto compiled = compiled_version();
    auto linked = linked_version();

    ODE_DEBUG(
        "The program is compiled againts Simple DirectMedia Layer {}.{}.{}",
        compiled.major,
        compiled.minor,
        compiled.patch);
    ODE_DEBUG(
        "The program is linked againts Simple DirectMedia Layer {}.{}.{}",
        linked.major,
        linked.minor,
        linked.patch);
  }
} // namespace ode::sdl
