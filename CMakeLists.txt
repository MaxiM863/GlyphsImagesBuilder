cmake_minimum_required(VERSION 3.14)
project(MyLibrary VERSION 1.0 LANGUAGES CXX)

add_library(MyLibrary src/mylib.cpp)

# Export targets for installation
install(TARGETS MyLibrary
    EXPORT MyLibraryTargets
    DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)

# Create a Config file for find_package()
install(EXPORT MyLibraryTargets
    FILE MyLibraryTargets.cmake
    NAMESPACE MyLibrary::
    DESTINATION lib/cmake/MyLibrary
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)


install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfigVersion.cmake"
    DESTINATION lib/cmake/MyLibrary
)
