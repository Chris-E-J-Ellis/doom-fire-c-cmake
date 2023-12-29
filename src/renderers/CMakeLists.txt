set(SDL2_DIR ${LIBS_DIR}/SDL2/cmake)

find_package(SDL2 REQUIRED)

target_sources(doom_fire_c_experiment
        PRIVATE
        fire-renderer-sdl.c
        fire-renderer-sdl.h
        fire-renderer-text.c
        fire-renderer-text.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2)