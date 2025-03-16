find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(unit_tests
    buffer_test.cpp
    freespace_test.cpp
)

target_link_libraries(unit_tests PRIVATE ${GTEST_BOTH_LIBRARIES} sut )

