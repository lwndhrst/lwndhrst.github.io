set(TARGET_NAME boids)

add_executable(${TARGET_NAME})

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.c)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS *.h)
target_sources(${TARGET_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${TARGET_NAME})

set_property(TARGET ${TARGET_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>)

if ("${PLATFORM}" STREQUAL "Web")
    add_custom_command(
        TARGET ${TARGET_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
    )
    #DEPENDS ${TARGET_NAME}
else()
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
    )
    #DEPENDS ${TARGET_NAME}
endif()

# set(raylib_VERBOSE 1)
target_link_libraries(${TARGET_NAME} raylib)
target_include_directories(${TARGET_NAME} PRIVATE ${raygui_SOURCE_DIR}/src)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an example.html file
    # set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${TARGET_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file $<TARGET_FILE_DIR:${TARGET_NAME}>/assets)

    # Fix generated compile_commands.json to also include Emscripten flags
    execute_process(COMMAND emcc --cflags OUTPUT_VARIABLE EM_CFLAGS)
    set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS "${EM_CFLAGS}")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${TARGET_NAME} "-framework IOKit")
    target_link_libraries(${TARGET_NAME} "-framework Cocoa")
    target_link_libraries(${TARGET_NAME} "-framework OpenGL")
endif()
