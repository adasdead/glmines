cmake_minimum_required(VERSION 3.23)
project(Minesweeper VERSION 1.0 LANGUAGES C)

set(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Minesweeper

    src/game/border.c
    src/game/counter.c
    src/game/field.c
    src/game/game.c
    src/game/input.c
    src/game/resources.c
    src/game/smile.c
    src/game/window.c

    src/graphics/renderer.c
    src/graphics/shader.c
    src/graphics/texture.c

    src/math/matrix4.c
    src/math/transform.c
    src/math/vector3.c

    src/glad.c
    src/main.c
)

set_target_properties(Minesweeper PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_custom_command(TARGET Minesweeper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_BINARY_DIR}/bin
)

target_include_directories(Minesweeper
    PRIVATE
        src/
)

target_link_libraries(Minesweeper
    PRIVATE
        ${CMAKE_DL_LIBS}
        OpenGL::GL
        glfw
)