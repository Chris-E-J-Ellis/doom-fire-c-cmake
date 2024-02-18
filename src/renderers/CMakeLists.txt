if (PDC_LIB)
    target_sources(${PROJECT_NAME}_curses
            PRIVATE
            fire-renderer-curses.c
            fire-renderer-curses.h
    )
endif ()

if (SDL2_FOUND)
    target_sources(doom_fire_c_experiment_sdl
            PRIVATE
            fire-renderer-sdl.c
            fire-renderer-sdl.h
    )
endif ()

target_sources(${PROJECT_NAME}_text
        PRIVATE
        fire-renderer-text.c
        fire-renderer-text.h
)
