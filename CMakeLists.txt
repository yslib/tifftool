cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME "tifftool")

project(${PROJECT_NAME})



set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR "D:\\opencv\\build")


# OpenMP
FIND_PACKAGE(OpenMP)
if(OPENMP_FOUND)
message("OPENMP FOUND")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()




#----------
# libtiff
#----------
find_package(TIFF REQUIRED)
if(TIFF_FOUND)
	message(STATUS "Tiff Found:" ${TIFF_INCLUDE_DIRS}" "${TIFF_LIBRARIES})
	include_directories(${TIFF_INCLUDE_DIR})
endif(TIFF_FOUND)


find_package(OpenCV REQUIRED)
if(OPENCV_FOUND)
   message(STATUS "OpenCV Found:" ${OpenCV_INCLUDE_DIRS}" "${OpenCV_LIBS})
   include_directories(${OpenCV_INCLUDE_DIRS})
endif(OPENCV_FOUND)

aux_source_directory("src" SRC_FILE)



#------------
#
#------------
link_directories(${PROJECT_NAME} "D:\\opencv\\build\\x64\\vc15\\bin")
add_executable(${PROJECT_NAME} ${SRC_FILE})

add_executable("test" "test/test.cpp")

target_link_libraries(${PROJECT_NAME} ${TIFF_LIBRARIES} ${OpenCV_LIBS})
