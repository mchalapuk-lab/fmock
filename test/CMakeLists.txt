include_directories (${SRC_DIR}/include)
link_directories (${SRC_DIR}/test)
add_executable (${PROJECT_NAME}-tests
  tests.cpp
  throw.cpp
)
target_link_libraries (${PROJECT_NAME}-tests gmock pthread)

