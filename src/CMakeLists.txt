set(SOURCES main.c
        fire-engine.c
        fire-engine.h
        fire-renderer.h
        fire-palette.c
        fire-palette.h)

# Common settings for targets
add_library(common INTERFACE)
target_compile_options(common INTERFACE -Werror -Wall -Wextra)

add_executable(${PROJECT_NAME}_text ${SOURCES})

# Curses target
find_library(PDC_LIB pdcurses HINTS ${LIBS_DIR}/PDCurses)
if (PDC_LIB)
    add_executable(${PROJECT_NAME}_curses ${SOURCES})
    target_compile_definitions(${PROJECT_NAME}_curses PRIVATE RENDERER_CURSES)

    target_include_directories(${PROJECT_NAME}_curses PRIVATE
            ${LIBS_DIR}/PDCurses
    )

    find_path(PDC_INCLUDES curses.h PATHS ${LIBS_DIR}/PDCurses)
    find_file(PDC_DLL pdcurses.dll PATHS ${LIBS_DIR}/PDCurses)

    # Copy pdcurses dll separately because CMake...
    add_custom_target(PDC_DLL_COPY
            ALL
            COMMAND ${CMAKE_COMMAND} -E copy "${PDC_DLL}" "${CMAKE_BINARY_DIR}"
            COMMENT "Copy dll file to ${CMAKE_BINARY_DIR} directory" VERBATIM)

    target_link_libraries(${PROJECT_NAME}_curses PRIVATE
            ${PDC_LIB}
    )
endif ()

#SDL Target
set(SDL2_DIR ${LIBS_DIR}/SDL2/cmake)
find_package(SDL2)
if (SDL2_FOUND)
    add_executable(${PROJECT_NAME}_sdl ${SOURCES})

    target_compile_definitions(${PROJECT_NAME}_sdl PRIVATE RENDERER_SDL)

    set(SDL2_NO_MWINDOWS TRUE) # Disable -mwindows link option

    target_link_libraries(${PROJECT_NAME}_sdl PRIVATE
            SDL2::SDL2
    )

endif ()

add_subdirectory(renderers)

get_directory_property(ALL_BUILDSYSTEM_TARGETS BUILDSYSTEM_TARGETS)
foreach (target ${ALL_BUILDSYSTEM_TARGETS})
    if (target MATCHES ${PROJECT_NAME})
        target_link_libraries(${target} PRIVATE common)

        target_include_directories(${target} PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}
                renderers)

        # Copy required dlls
        add_custom_command(TARGET ${target}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${target}> $<TARGET_RUNTIME_DLLS:${target}>
                COMMAND_EXPAND_LISTS)
    endif ()
endforeach ()
