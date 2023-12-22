set(SDL2_DIR ${LIBS_DIR}/SDL2/cmake)

find_package(SDL2 REQUIRED)

set(SOURCES main.c
        fire-engine.c
        fire-engine.h
        fire-renderer.h
        fire-renderer-sdl.c
        fire-renderer-sdl.h
        fire-palette.c
        fire-palette.h)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2)

# Copy required dlls
add_custom_command(TARGET doom_fire_c_experiment POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:doom_fire_c_experiment> $<TARGET_RUNTIME_DLLS:doom_fire_c_experiment>
        COMMAND_EXPAND_LISTS
)
