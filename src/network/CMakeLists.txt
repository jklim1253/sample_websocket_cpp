# source file list
set(SOURCES
  network.cpp
)

message("/src/network SOURCES => ${SOURCES}")

add_definitions(-DOW_NETWORK_EXPORTS)

set(MODULE_NAME network)

add_library(${MODULE_NAME}
  SHARED
    ${SOURCES}
)

target_include_directories(${MODULE_NAME}
  PUBLIC
    ${VCPKG_INCLUDE_DIR}
)

target_link_directories(${MODULE_NAME}
  PUBLIC 
    ${VCPKG_LIBRARY_DEBUG_DIR}
)

target_link_libraries(${MODULE_NAME}
  common
  boost_random-vc140-mt-gd
  libssl
  libcrypto
)
