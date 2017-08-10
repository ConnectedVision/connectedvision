cmake_minimum_required(VERSION 2.8.12)

project(Skeleton)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../../" CACHE PATH "default install path" FORCE)
endif()


set(Skeleton_DataClasses_Headers
	../../src/Class_Skeleton_input_Detections.h
	../../src/Class_Skeleton_input_Detections_boundingBox.h
	../../src/Class_Skeleton_output_Average.h
	../../src/Class_Skeleton_output_Average_color.h
	../../src/Class_Skeleton_params.h
	../../src/Skeleton_ModuleDescription.h
)

set(Skeleton_DataClasses_Sources
)


set(Skeleton_DataClasses_Stubs_Headers
	../../src/stubs/Class_Skeleton_input_Detections_Default.h
	../../src/stubs/Stub_Skeleton_input_Detections.h
	../../src/stubs/Class_Skeleton_input_Detections_boundingBox_Default.h
	../../src/stubs/Stub_Skeleton_input_Detections_boundingBox.h
	../../src/stubs/Class_Skeleton_output_Average_Default.h
	../../src/stubs/Stub_Skeleton_output_Average.h
	../../src/stubs/Class_Skeleton_output_Average_color_Default.h
	../../src/stubs/Stub_Skeleton_output_Average_color.h
	../../src/stubs/Class_Skeleton_params_Default.h
	../../src/stubs/Stub_Skeleton_params.h
	../../src/stubs/Stub_Skeleton_ModuleDescription.h
)

set(Skeleton_DataClasses_Stubs_Sources
	../../src/stubs/Stub_Skeleton_input_Detections.cpp
	../../src/stubs/Stub_Skeleton_input_Detections_boundingBox.cpp
	../../src/stubs/Stub_Skeleton_output_Average.cpp
	../../src/stubs/Stub_Skeleton_output_Average_color.cpp
	../../src/stubs/Stub_Skeleton_params.cpp
)


set(Skeleton_InputPins_Headers
	../../src/InputPin_Skeleton_input_Detections.h
)

set(Skeleton_InputPins_Sources
)


set(Skeleton_InputPins_Stubs_Headers
	../../src/stubs/InputPin_Skeleton_input_Detections_Default.h
	../../src/stubs/InputPin_Stub_Skeleton_input_Detections.h
)

set(Skeleton_InputPins_Stubs_Sources
)


set(Skeleton_Stores_Stubs_Headers
	../../src/stubs/Store_Manager_SQLite_Skeleton_input_Detections_Default.h
	../../src/stubs/Store_Manager_SQLite_Stub_Skeleton_input_Detections.h
	../../src/stubs/Store_SQLite_Skeleton_input_Detections_Default.h
	../../src/stubs/Store_SQLite_Stub_Skeleton_input_Detections.h
	../../src/stubs/Store_Manager_Ringbuffer_Skeleton_input_Detections_Default.h
	../../src/stubs/Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections.h
	../../src/stubs/Store_Manager_SQLite_Skeleton_output_Average_Default.h
	../../src/stubs/Store_Manager_SQLite_Stub_Skeleton_output_Average.h
	../../src/stubs/Store_SQLite_Skeleton_output_Average_Default.h
	../../src/stubs/Store_SQLite_Stub_Skeleton_output_Average.h
	../../src/stubs/Store_Manager_Ringbuffer_Skeleton_output_Average_Default.h
	../../src/stubs/Store_Manager_Ringbuffer_Stub_Skeleton_output_Average.h
)

set(Skeleton_Stores_Stubs_Sources
	../../src/stubs/Store_Manager_SQLite_Stub_Skeleton_input_Detections.cpp
	../../src/stubs/Store_SQLite_Stub_Skeleton_input_Detections.cpp
	../../src/stubs/Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections.cpp
	../../src/stubs/Store_Manager_SQLite_Stub_Skeleton_output_Average.cpp
	../../src/stubs/Store_SQLite_Stub_Skeleton_output_Average.cpp
	../../src/stubs/Store_Manager_Ringbuffer_Stub_Skeleton_output_Average.cpp
)


set(Skeleton_Stores_Headers
	../../src/Store_Manager_SQLite_Skeleton_input_Detections.h
	../../src/Store_SQLite_Skeleton_input_Detections.h
	../../src/Store_Manager_Ringbuffer_Skeleton_input_Detections.h
	../../src/Store_Manager_SQLite_Skeleton_output_Average.h
	../../src/Store_SQLite_Skeleton_output_Average.h
	../../src/Store_Manager_Ringbuffer_Skeleton_output_Average.h
)

set(Skeleton_Stores_Sources
)


set(Skeleton_OutputPins_Headers
	../../src/OutputPin_Skeleton_output_Average.h
)

set(Skeleton_OutputPins_Sources
)


set(Skeleton_OutputPins_Stubs_Headers
	../../src/stubs/OutputPin_Skeleton_output_Average_Default.h
	../../src/stubs/OutputPin_Stub_Skeleton_output_Average.h
)

set(Skeleton_OutputPins_Stubs_Sources
)


set(Skeleton_Swagger_Headers
)

set(Skeleton_Swagger_Sources
)


set(Skeleton_Module_Headers
	../../src/SkeletonModule.h
	../../src/SkeletonWorker.h
	../../src/SkeletonModuleFactory.h
)

set(Skeleton_Module_Sources
	../../src/SkeletonModule.cpp
	../../src/SkeletonWorker.cpp
	../../src/SkeletonModuleFactory.cpp
)



# if Connected Vision itself is not provided as a Conan package, then the include directories need to specified explicitly
if(EXISTS "$ENV{ConnectedVision}/core/include")
	include_directories(
		"$ENV{ConnectedVision}/core/include"
		"$ENV{ConnectedVision}/core/src"
	)
endif()


set(HEADERS
	${Skeleton_DataClasses_Headers}
	${Skeleton_DataClasses_Stubs_Headers}
	${Skeleton_InputPins_Headers}
	${Skeleton_InputPins_Stubs_Headers}
	${Skeleton_Stores_Stubs_Headers}
	${Skeleton_Stores_Headers}
	${Skeleton_OutputPins_Headers}
	${Skeleton_OutputPins_Stubs_Headers}
	${Skeleton_Swagger_Headers}
	${Skeleton_Module_Headers}
)

set(SOURCES
	${Skeleton_DataClasses_Sources}
	${Skeleton_DataClasses_Stubs_Sources}
	${Skeleton_InputPins_Sources}
	${Skeleton_InputPins_Stubs_Sources}
	${Skeleton_Stores_Stubs_Sources}
	${Skeleton_Stores_Sources}
	${Skeleton_OutputPins_Sources}
	${Skeleton_OutputPins_Stubs_Sources}
	${Skeleton_Swagger_Sources}
	${Skeleton_Module_Sources}
)


source_group(DataClasses FILES
	${Skeleton_DataClasses_Headers}
	${Skeleton_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${Skeleton_DataClasses_Stubs_Headers}
	${Skeleton_DataClasses_Stubs_Sources}
)
source_group(InputPins FILES
	${Skeleton_InputPins_Headers}
	${Skeleton_InputPins_Sources}
)
source_group(InputPins\\Stubs FILES
	${Skeleton_InputPins_Stubs_Headers}
	${Skeleton_InputPins_Stubs_Sources}
)
source_group(Stores\\Stubs FILES
	${Skeleton_Stores_Stubs_Headers}
	${Skeleton_Stores_Stubs_Sources}
)
source_group(Stores FILES
	${Skeleton_Stores_Headers}
	${Skeleton_Stores_Sources}
)
source_group(OutputPins FILES
	${Skeleton_OutputPins_Headers}
	${Skeleton_OutputPins_Sources}
)
source_group(OutputPins\\Stubs FILES
	${Skeleton_OutputPins_Stubs_Headers}
	${Skeleton_OutputPins_Stubs_Sources}
)
source_group(Swagger FILES
	${Skeleton_Swagger_Headers}
	${Skeleton_Swagger_Sources}
)
source_group(Module FILES
	${Skeleton_Module_Headers}
	${Skeleton_Module_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})