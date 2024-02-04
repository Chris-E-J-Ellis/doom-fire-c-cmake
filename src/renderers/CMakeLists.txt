set(SDL2_DIR ${LIBS_DIR}/SDL2/cmake)

set(SDL2_NO_MWINDOWS TRUE) # Disable -mwindows link option
find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
        ../../libs/PDCurses
)

find_library(PDC_LIB pdcurses REQUIRED HINTS ${LIBS_DIR}/PDCurses)
find_path(PDC_INCLUDES curses.h PATHS ${LIBS_DIR}/PDCurses)
find_file(PDC_DLL pdcurses.dll PATHS ${LIBS_DIR}/PDCurses)

target_sources(doom_fire_c_experiment
        PRIVATE
        fire-renderer-curses.c
        fire-renderer-curses.h
        fire-renderer-sdl.c
        fire-renderer-sdl.h
        fire-renderer-text.c
        fire-renderer-text.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        ${PDC_LIB}
)

# Copy pdcurses dll separately because CMake...
add_custom_target(PDC_DLL_COPY
        ALL
        COMMAND ${CMAKE_COMMAND} -E copy "${PDC_DLL}" "${CMAKE_BINARY_DIR}"
        COMMENT "Copy dll file to ${CMAKE_BINARY_DIR} directory" VERBATIM)
