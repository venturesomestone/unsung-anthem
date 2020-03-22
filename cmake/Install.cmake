# Copyright (c) 2019–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

# TODO Resolve how to handle the Ode binaries installation
# function(ODE_INSTALLATION)
#   install(TARGETS ${ODE_NAME} ${ODE_NAME}${ODE_DYNAMIC_MARK}
#       RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_BIN_DIR_NAME}
#       PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_INCLUDE_DIR_NAME}
#       PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_INCLUDE_DIR_NAME}
#       LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME}
#       ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME})
# endfunction()

# TODO Resolve how to handle the Ode binaries installation
# function(ODE_TEST_INSTALLATION)
#   install(TARGETS ${ODE_TEST_NAME}
#       RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_BIN_DIR_NAME})
# endfunction()

function(ANTHEM_INSTALLATION)
  install(TARGETS ${ANTHEM_NAME} RUNTIME DESTINATION bin)
endfunction()

# function(ANTHEM_LIB_INSTALLATION)
#   install(TARGETS ${ANTHEM_LIB_NAME} ${ANTHEM_LIB_NAME}${ODE_DYNAMIC_MARK}
#       RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_BIN_DIR_NAME}
#       PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_INCLUDE_DIR_NAME}
#       PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_INCLUDE_DIR_NAME}
#       LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME}
#       ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME})
# endfunction()

function(ANTHEM_TEST_INSTALLATION)
  install(TARGETS ${ANTHEM_TEST_NAME} RUNTIME DESTINATION bin)
endfunction()

function(ODE_SCRIPT_INSTALLATION)
  # TODO Reserved for a world with newer CMake versions
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/ode
  #     TYPE LIB
  #     FILES_MATCHING PATTERN "*.lua")
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/ode
      DESTINATION lib
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ODE_TEST_SCRIPT_INSTALLATION)
  ode_script_installation()
  # TODO Reserved for a world with newer CMake versions
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/ode
  #     TYPE LIB
  #     FILES_MATCHING PATTERN "*.lua")
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/ode
      DESTINATION lib
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ANTHEM_SCRIPT_INSTALLATION)
  ode_script_installation()
  # TODO Reserved for a world with newer CMake versions
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/anthem
  #     TYPE LIB
  #     FILES_MATCHING PATTERN "*.lua")
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/anthem
      DESTINATION lib
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ANTHEM_LIB_SCRIPT_INSTALLATION)
  ode_script_installation()
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/lib/anthem
  #     DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_SCRIPT_DIR_NAME}
  #     FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ANTHEM_TEST_SCRIPT_INSTALLATION)
  ode_test_script_installation()
  # TODO Reserved for a world with newer CMake versions
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/anthem
  #     TYPE LIB
  #     FILES_MATCHING PATTERN "*.lua")
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/anthem
      DESTINATION lib
      FILES_MATCHING PATTERN "*.lua")
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/anthem
  #     DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_TEST_SCRIPT_DIR_NAME}
  #     FILES_MATCHING PATTERN "*.lua")
endfunction()

function(CREATE_INSTALL_TARGETS)
  if(NOT ODE_ENABLE_GCOV)
    anthem_installation()
  endif()
  anthem_script_installation()
  if(NOT ODE_ENABLE_GCOV)
    # anthem_lib_installation()
  endif()
  # anthem_lib_script_installation()
  if(ODE_BUILD_TEST)
    if(NOT ODE_ENABLE_GCOV)
      anthem_test_installation()
    endif()
    anthem_test_script_installation()
  endif()
endfunction()
