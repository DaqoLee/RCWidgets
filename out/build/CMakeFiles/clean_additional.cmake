# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\RCWidgets_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\RCWidgets_autogen.dir\\ParseCache.txt"
  "RCWidgets_autogen"
  )
endif()
