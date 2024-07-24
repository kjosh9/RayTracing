include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  core_tests
  test_parsing.cpp
  test_plane.cpp
)

target_link_libraries(core_tests
  PRIVATE
  GTest::gtest_main
  nlohmann_json::nlohmann_json    
  core
)

include(GoogleTest)
gtest_discover_tests(core_tests)

add_custom_target( valgrind
  COMMAND valgrind --leak-check=full --error-exitcode=1 $<TARGET_FILE:core_tests>
  DEPENDS core_tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running tests with Valgrind"
)