cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME "tifftool")

project(${PROJECT_NAME})

message(STATUS ${PROJECT_SOURCE_DIR})



set(CMAKE_CXX_STANDARD 14)


#----------
# libtiff
#----------
find_package(TIFF REQUIRED)
if(TIFF_FOUND)
	message(STATUS "Tiff Found:" ${TIFF_INCLUDE_DIR}" "${TIFF_LIBRARIES})
	include_directories(${TIFF_INCLUDE_DIR})
endif(TIFF_FOUND)




#------------
#
#------------
add_executable(${PROJECT_NAME}
"src/tifftool.cpp"
)

add_executable("test"
"test/test.cpp"
)

target_link_libraries(${PROJECT_NAME} ${TIFF_LIBRARIES})
