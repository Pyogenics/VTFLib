cmake_minimum_required(VERSION 3.12)
project(VTFCmd)

add_executable(VTFCmd)
target_sources(${PROJECT_NAME}
	PRIVATE
	vtfcmd.c
	enumerations.c
)
target_include_directories(${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/external/DevIL/DevIL/include
)
target_link_libraries(${PROJECT_NAME}
	PRIVATE
	WIN32POSIXAbstraction
	vtflib
)
