find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} WIN32 main.c)

target_sources(${PROJECT_NAME} PRIVATE

    ${PROJECT_DATA_DIR}/glMines.rc

    game/border.c
    game/counter.c
    game/field.c
    game/game.c
    game/input.c
    game/resources.c
    game/smile.c
    game/window.c

    graphics/renderer.c
    graphics/shader.c
    graphics/texture.c

    math/matrix4.c
    math/transform.c

    glad.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_DL_LIBS}
    ${MATH_LIB}
    OpenGL::GL
    glfw
)

add_custom_command(TARGET ${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_DATA_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)

install(TARGETS ${PROJECT_NAME} RUNTIME)
install(DIRECTORY ${PROJECT_DATA_DIR} DESTINATION "bin")
install(FILES $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        DESTINATION "bin")