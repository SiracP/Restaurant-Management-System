# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Restaurant_Management_System_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Restaurant_Management_System_autogen.dir\\ParseCache.txt"
  "Restaurant_Management_System_autogen"
  )
endif()
