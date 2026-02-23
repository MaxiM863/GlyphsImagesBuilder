cmake_minimum_required(VERSION 3.14)
project(mylib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(mylib INTERFACE include/GIB.hpp)

# Specify include directories for consumers
# PUBLIC: used when building and when linking from another project
target_include_directories(mylib
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # When building
        $<INSTALL_INTERFACE:include>                            # When installed
)

# Optionally set C++ standard
target_compile_features(mylib INTERFACE cxx_std_17)

# Install the library and headers
install(TARGETS mylib
    EXPORT mylibTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

# Export targets for find_package()
install(EXPORT mylibTargets
    FILE MyLibTargets.cmake
    NAMESPACE MyLib::
    DESTINATION lib/cmake/MyLib
)

# Create a Config file for find_package()
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MyLibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(MyLibConfig.cmake.in MyLibConfig.cmake @ONLY)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MyLibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MyLibConfigVersion.cmake"
    DESTINATION lib/cmake/MyLib
)

add_executable(Test Test/test.cpp)

target_link_libraries(Test PRIVATE mylib)