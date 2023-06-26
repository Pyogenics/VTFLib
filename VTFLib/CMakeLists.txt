cmake_minimum_required(VERSION 3.12)
project(vtflib)

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME}
	PRIVATE
	Error.cpp
	FileReader.cpp
	FileWriter.cpp
	Float16.cpp
	MemoryReader.cpp
	MemoryWriter.cpp
	Proc.cpp
	ProcReader.cpp
	ProcWriter.cpp
	VMTFile.cpp
	VMTGroupNode.cpp
	VMTIntegerNode.cpp
	VMTNode.cpp
	VMTSingleNode.cpp
	VMTStringNode.cpp
	VMTValueNode.cpp
	VMTWrapper.cpp
	VTFFile.cpp
	VTFLib.cpp
	VTFMathlib.cpp
	VTFWrapper.cpp	
)
target_include_directories(${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/lib
)
#XXX: Add windows support here
target_compile_definitions(${PROJECT_NAME}
	PRIVATE
	NDEBUG
	VTFLIB_EXPORTS
)
target_compile_options(${PROJECT_NAME}
	PRIVATE
	-fvisibility=hidden #XXX: remove this on non GCC builds
	-fpermissive #XXX: this is for some real strange stuff in Proc.cpp
)
