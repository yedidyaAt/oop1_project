cmake_minimum_required(VERSION 3.26)
project(oop1_ex04)


set(MY_AUTHORS "Uri_Tauber")

include(cmake/CompilerSettings.cmake)

add_executable(${CMAKE_PROJECT_NAME})

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
if(NOT MSVC)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
endif()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(resources)

include(cmake/Zip.cmake)

option(SFML_STATIC_LIBRARIES "Link SFML statically" OFF)

if(WIN32)
    set(SFML_LOCATION "C:/SFML/SFML-3.0.0")
    set(SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")
endif()

# --- Linux: Do nothing — CMake will automatically search system paths

# Now find SFML 3
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
    SFML::Graphics
    SFML::Window
    SFML::System
)

include(cmake/SFML.cmake)
