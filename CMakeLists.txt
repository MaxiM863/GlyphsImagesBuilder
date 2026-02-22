cmake_minimum_required(VERSION 3.14)
project(mylib VERSION 1.0 LANGUAGES CXX)

add_library(mylib src/mylib.cpp)

# Specify include directories for consumers
# PUBLIC: used when building and when linking from another project
target_include_directories(mylib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # When building
        $<INSTALL_INTERFACE:include>                            # When installed
)

# Optionally set C++ standard
target_compile_features(mylib PUBLIC cxx_std_17)

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