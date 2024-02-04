set(SOURCES main.c
        fire-engine.c
        fire-engine.h
        fire-renderer.h
        fire-palette.c
        fire-palette.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        renderers)

add_subdirectory(renderers)

# Copy required dlls
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS)

# Copy pdcurses dll separately because CMake...
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${PDC_DLL}" "${CMAKE_BINARY_DIR}"
        COMMENT "Copy dll file to ${CMAKE_BINARY_DIR} directory" VERBATIM)
