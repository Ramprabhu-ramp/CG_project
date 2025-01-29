cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

# Explicitly list the test source code and headers. The Catch header-only unit
# test framework is stored in with the test source.
set(Imagequality_Dalys_TEST_SRC
    test_cmake_demo.cpp
)
set(Imagequality_Dalys_TEST_HEADER
    catch.hpp
)

PREPEND(Imagequality_Dalys_TEST_SRC)

# Make an executable target that depends on the test source code we specified
# above.
add_executable(TestImagequality_Dalys ${Imagequality_Dalys_TEST_SRC} ${Imagequality_Dalys_TEST_HEADER})

# Enable testing via CTest
enable_testing()
# Add our test as runnable via CTest
add_test(NAME TestImagequality_Dalys  COMMAND TestImagequality_Dalys)

# Link our unit tests against the library we compiled
target_link_libraries(TestImagequality_Dalys Imagequality_Dalys)
