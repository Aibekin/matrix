cmake_minimum_required(VERSION 3.10)
project(Matrix LANGUAGES C CXX)

file(GLOB_RECURSE MATRIX_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp include/**/*.h include/**/*.hpp)
add_library(Matrix SHARED ${MATRIX_SOURCES})

target_include_directories(Matrix PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(Matrix::Matrix ALIAS Matrix)

include(GNUInstallDirs)

install(TARGETS Matrix
    EXPORT MatrixTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT MatrixTargets
    FILE MatrixTargets.cmake
    NAMESPACE Matrix::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Matrix
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MatrixConfigVersion.cmake
    VERSION 1.0
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/MatrixConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MatrixConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Matrix
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MatrixConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MatrixConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Matrix
)