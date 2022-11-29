cmake_minimum_required(VERSION 3.6)

project(OpenGL)

file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB         SRCS    "${PROJECT_SOURCE_DIR}/src/*.c*")
file(GLOB         LIBS    "${PROJECT_SOURCE_DIR}/libs/*.lib")

add_executable(${PROJECT_NAME} WIN32 ${HEADERS} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
)

target_link_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/libs/
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})

if(MSVC)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS /SUBSYSTEM:CONSOLE)
endif(MSVC)