

find_package(OpenCV REQUIRED)

target_link_libraries(
    ${OpenCV_LIBS}
)

target_include_directories(${OpenCV_INCLUDE_DIRS})