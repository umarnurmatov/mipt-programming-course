set(TARGET_NAME onegin)

file(GLOB_RECURSE SOURCES src/*.c)

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX)

add_executable(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC include)

target_link_libraries(${TARGET_NAME} PRIVATE cutils)

target_compile_definitions(${TARGET_NAME} PRIVATE WORKING_DIR="${PROJECT_SOURCE_DIR}")
