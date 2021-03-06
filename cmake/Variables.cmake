# Copyright (c) 2017–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(PRINT_STATUS NAME TITLE)
  message(STATUS "The ${TITLE} (${NAME}) is set to ${${NAME}}")
endfunction()

function(PRINT_STATUS_PLURAL NAME TITLE)
  message(STATUS "The ${TITLE} (${NAME}) are set to ${${NAME}}")
endfunction()

function(PRINT_STATUS_IF_DEFINED NAME TITLE)
  if(DEFINED ${NAME})
    print_status(${NAME} ${TITLE})
  endif()
endfunction()

function(ASSERT_VARIABLE NAME TITLE POSSIBLE_VALUES)
  if(NOT DEFINED ${NAME})
    message(FATAL_ERROR
        "The ${TITLE} (${NAME}) is not set – the possible values are \
${POSSIBLE_VALUES}")
  else()
    print_status(${NAME} ${TITLE})
  endif()
endfunction()

function(ASSERT_VARIABLE NAME TITLE)
  if(NOT DEFINED ${NAME})
    message(FATAL_ERROR "The ${TITLE} (${NAME}) is not set")
  else()
    print_status(${NAME} ${TITLE})
  endif()
endfunction()

function(ASSERT_ONLY_OTHER NAME1 NAME2 TITLE1 TITLE2)
  if(NOT DEFINED ${NAME1} AND NOT DEFINED ${NAME2})
    message(FATAL_ERROR
        "The neither ${TITLE1} nor ${TITLE2} (${NAME1} and ${NAME2}) is not \
set")
  elseif(${NAME1} AND ${NAME2})
    message(FATAL_ERROR
        "The both ${TITLE1} and ${TITLE2} (${NAME1} and ${NAME2}) are used")
  elseif(NOT ${NAME1} AND NOT ${NAME2})
    message(FATAL_ERROR
        "The neither ${TITLE1} nor ${TITLE2} (${NAME1} and ${NAME2}) is used")
  endif()
endfunction()

function(DEFAULT_VALUE NAME VALUE TITLE)
  if(NOT DEFINED ${NAME})
    message(STATUS
        "${TITLE} (${NAME}) is not set and will be defaulted to ${VALUE}")
    set(${NAME} ${VALUE} PARENT_SCOPE)
  else()
    print_status(${NAME} ${TITLE})
  endif()
endfunction()
