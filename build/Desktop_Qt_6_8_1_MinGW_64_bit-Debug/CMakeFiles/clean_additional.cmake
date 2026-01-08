# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "app\\AegisSecurity_autogen"
  "app\\CMakeFiles\\AegisSecurity_autogen.dir\\AutogenUsed.txt"
  "app\\CMakeFiles\\AegisSecurity_autogen.dir\\ParseCache.txt"
  "database\\AegisData_autogen"
  "database\\CMakeFiles\\AegisData_autogen.dir\\AutogenUsed.txt"
  "database\\CMakeFiles\\AegisData_autogen.dir\\ParseCache.txt"
  "libs\\ui\\AegisUI_autogen"
  "libs\\ui\\CMakeFiles\\AegisUI_autogen.dir\\AutogenUsed.txt"
  "libs\\ui\\CMakeFiles\\AegisUI_autogen.dir\\ParseCache.txt"
  )
endif()
