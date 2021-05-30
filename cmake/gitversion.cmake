# Export following variables:
# ${GIT_BRANCH} actual git branch
# ${GIT_COMMIT_HASH} actual git commit hash
# ${GIT_VERSION} actual git version
# ${GIT_VERSION_MAJOR} actual git version major number
# ${GIT_VERSION_MINOR} actual git version minor number
# ${GIT_VERSION_PATCH_LEVEL} actual git version patch number
#


function(get_repository_version)
  # Set the current git branch name into the GIT_BRANCH variable
  execute_process(
    COMMAND ${PYTHON} "${SCRIPTS_PATH}/gitversion.py" -b
    "${CMAKE_SOURCE_DIR}"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(GIT_BRANCH ${GIT_BRANCH} PARENT_SCOPE)

  # Get the latest abbreviated commit hash of the working branch
  execute_process(
    COMMAND ${PYTHON} "${SCRIPTS_PATH}/gitversion.py" -s
    "${CMAKE_SOURCE_DIR}"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(GIT_COMMIT_HASH ${GIT_COMMIT_HASH} PARENT_SCOPE)

  # Get the tag name as version indicator.
  execute_process(
    COMMAND ${PYTHON} "${SCRIPTS_PATH}/gitversion.py" -a
    "${CMAKE_SOURCE_DIR}"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(GIT_VERSION ${GIT_VERSION} PARENT_SCOPE)

  execute_process(
    COMMAND ${PYTHON} "${SCRIPTS_PATH}/gitversion.py" -M
    "${CMAKE_SOURCE_DIR}"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION_MAJOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(GIT_VERSION_MAJOR ${GIT_VERSION_MAJOR} PARENT_SCOPE)

  execute_process(
    COMMAND ${PYTHON} "${SCRIPTS_PATH}/gitversion.py" -m
    "${CMAKE_SOURCE_DIR}"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION_MINOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(GIT_VERSION_MINOR ${GIT_VERSION_MINOR} PARENT_SCOPE)

  execute_process(
    COMMAND ${PYTHON} "${SCRIPTS_PATH}/gitversion.py" -P
    "${CMAKE_SOURCE_DIR}"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION_PATCH_LEVEL
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(GIT_VERSION_PATCH_LEVEL ${GIT_VERSION_PATCH_LEVEL} PARENT_SCOPE)

  if(NOT GIT_VERSION)
    message(FATAL_ERROR "COULD NOT DETERMINE GIT VERSION")
  endif()

endfunction()
