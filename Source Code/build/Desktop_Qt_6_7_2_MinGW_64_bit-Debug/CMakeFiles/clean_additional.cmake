# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\compiler_design_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\compiler_design_autogen.dir\\ParseCache.txt"
  "compiler_design_autogen"
  )
endif()
