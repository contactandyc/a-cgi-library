cmake_minimum_required(VERSION 3.10)
project(acgilibrary VERSION 0.1.1)

# Options
option(DEBUG "Enable debugging" OFF)
option(ADDRESS_SANITIZER "Enable Address Sanitizer" OFF)

set(CMAKE_INSTALL_INCLUDEDIR include)
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_DOCDIR share/doc/acgilibrary)
set(CMAKE_C_STANDARD 99)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Find the required libraries
find_package(amemorylibrary REQUIRED)
find_package(themacrolibrary REQUIRED)
find_package(ajsonlibrary REQUIRED)

# Compiler options
if(ADDRESS_SANITIZER)
    add_compile_options(-fsanitize=address)
endif()

# Source files
set(SOURCE_FILES src/acgi.c)

# Debug library
add_library(acgilibrary_debug STATIC ${SOURCE_FILES})
target_include_directories(acgilibrary_debug PUBLIC ${themacrolibrary_INCLUDE_DIRS})
target_include_directories(acgilibrary_debug PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_definitions(acgilibrary_debug PUBLIC -D_AML_DEBUG_)
target_compile_options(acgilibrary_debug PRIVATE -g -O0)
set_target_properties(acgilibrary_debug PROPERTIES OUTPUT_NAME "acgilibrary_debug")
target_compile_options(acgilibrary_debug PRIVATE -g -O0)


# Release library
add_library(acgilibrary_static STATIC ${SOURCE_FILES})
target_include_directories(acgilibrary_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_include_directories(acgilibrary_static PUBLIC ${themacrolibrary_INCLUDE_DIRS})
target_compile_options(acgilibrary_static PRIVATE -O3)
set_target_properties(acgilibrary_static PROPERTIES OUTPUT_NAME "acgilibrary_static")
target_compile_options(acgilibrary_static PRIVATE -O3)

# Shared library
add_library(acgilibrary SHARED ${SOURCE_FILES})
target_include_directories(acgilibrary PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_include_directories(acgilibrary PUBLIC ${themacrolibrary_INCLUDE_DIRS})
target_compile_options(acgilibrary PRIVATE -O3)
set_target_properties(acgilibrary PROPERTIES OUTPUT_NAME "acgilibrary")
target_compile_options(acgilibrary PRIVATE -O3)

# Link libraries
target_link_libraries(acgilibrary_debug PUBLIC amemorylibrary ajsonlibrary)
target_link_libraries(acgilibrary_static PUBLIC amemorylibrary ajsonlibrary)
target_link_libraries(acgilibrary PUBLIC amemorylibrary ajsonlibrary)

# Installation of the library
install(TARGETS acgilibrary acgilibrary_static acgilibrary_debug
        EXPORT acgilibraryTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include)

# Export the targets
install(EXPORT acgilibraryTargets
        FILE acgilibraryTargets.cmake
        DESTINATION lib/cmake/acgilibrary)

# Create and install the config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "acgilibraryConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_file(acgilibraryConfig.cmake.in acgilibraryConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/acgilibraryConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/acgilibraryConfigVersion.cmake"
        DESTINATION lib/cmake/acgilibrary)

# Installation of other files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/a-cgi-library DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES README.md AUTHORS NEWS.md CHANGELOG.md LICENSE NOTICE DESTINATION ${CMAKE_INSTALL_DOCDIR})

# Uninstall command
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/bin/cmake_uninstall.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
               IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
