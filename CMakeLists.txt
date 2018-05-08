cmake_minimum_required(VERSION 3.11)
project(OpenCL-Loader LANGUAGES C)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(API_INCLUDE_DIR "src/include")
set(LIB_SRC_DIR "src/microhttpd")

file(GLOB API_HEADERS "${API_INCLUDE_DIR}/*.h" "${API_INCLUDE_DIR}/*.hpp")
file(GLOB LIB_SRC "${CMAKE_BINARY_DIR}/opencl_loader/${OPENCL_VERSION}/src/*.c")

include_directories(
 ${PROJECT_NAME}
 PRIVATE
 ${API_INCLUDE_ROOT}
)

add_library(${PROJECT_NAME} STATIC ${LIB_SRC} ${API_HEADERS} ${GEN_SRC})

source_group("Generator" FILES ${GEN_SRC})
source_group("${CL_SUBDIR}" FILES ${API_HEADERS})

if(BUILD_TEST)
  add_executable(${PROJECT_NAME}-test EXCLUDE_FROM_ALL ${CMAKE_SOURCE_DIR}/test/test.c)
  target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
endif()

install(FILES $<TARGET_FILE:${PROJECT_NAME}> DESTINATION lib)
install(DIRECTORY ${API_INCLUDE_DIR}/ DESTINATION include/${CL_SUBDIR})
