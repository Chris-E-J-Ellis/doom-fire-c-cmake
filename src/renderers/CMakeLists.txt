if (BUILD_PDCURSES)

target_include_directories(${PROJECT_NAME} PRIVATE
        ../../libs/PDCurses
)

find_library(PDC_LIB pdcurses REQUIRED HINTS ${LIBS_DIR}/PDCurses)
find_path(PDC_INCLUDES curses.h PATHS ${LIBS_DIR}/PDCurses)
find_file(PDC_DLL pdcurses.dll PATHS ${LIBS_DIR}/PDCurses)

set(CURSES_SOURCES
        fire-renderer-curses.c
        fire-renderer-curses.h
)

# Copy pdcurses dll separately because CMake...
add_custom_target(PDC_DLL_COPY
        ALL
        COMMAND ${CMAKE_COMMAND} -E copy "${PDC_DLL}" "${CMAKE_BINARY_DIR}"
        COMMENT "Copy dll file to ${CMAKE_BINARY_DIR} directory" VERBATIM)

elseif (BUILD_SDL)

set(SDL2_DIR ${LIBS_DIR}/SDL2/cmake)
set(SDL2_NO_MWINDOWS TRUE) # Disable -mwindows link option
set(SDL_LIB SDL2::SDL2)

find_package(SDL2 REQUIRED)

set(SDL_SOURCES
        fire-renderer-sdl.c
        fire-renderer-sdl.h
)

endif ()

target_sources(doom_fire_c_experiment
        PRIVATE
        fire-renderer-text.c
        fire-renderer-text.h
        ${SDL_SOURCES}
        ${CURSES_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL_LIB}
        ${PDC_LIB}
)
