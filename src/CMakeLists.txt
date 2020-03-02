# source file lists

set(SOURCES
  main.cpp
)

message("/src SOURCES => ${SOURCES}")

add_subdirectory(common)
add_subdirectory(network)

add_executable(${PROJECT_NAME}
  ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  common
  network
)