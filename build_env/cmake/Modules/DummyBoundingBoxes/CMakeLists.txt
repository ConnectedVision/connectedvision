cmake_minimum_required(VERSION 2.8.12)

project(DummyBoundingBoxes)

set(ConnectedVisionCppRoot ../../../..)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()

set(DummyBoundingBoxes_DataClasses_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_output_Detections_boundingBox.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_output_Detections_basePoint.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_output_ObjectData.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_output_ObjectData_detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_params.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_params_boundingBoxStart.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Class_DummyBoundingBoxes_params_boundingBoxEnd.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/DummyBoundingBoxes_ModuleDescription.h
)

set(DummyBoundingBoxes_DataClasses_Sources
)


set(DummyBoundingBoxes_DataClasses_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_input_Trigger_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_output_Detections_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_output_Detections_boundingBox_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_Detections_boundingBox.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_output_Detections_basePoint_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_Detections_basePoint.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_output_ObjectData_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_ObjectData.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_output_ObjectData_detections_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections_boundingBox.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_params_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_params.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_params_boundingBoxStart_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_params_boundingBoxStart.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Class_DummyBoundingBoxes_params_boundingBoxEnd_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_params_boundingBoxEnd.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_ModuleDescription.h
)

set(DummyBoundingBoxes_DataClasses_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_input_Trigger.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_Detections.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_Detections_boundingBox.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_Detections_basePoint.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_ObjectData.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections_boundingBox.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_params.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_params_boundingBoxStart.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Stub_DummyBoundingBoxes_params_boundingBoxEnd.cpp
)


set(DummyBoundingBoxes_InputPins_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/InputPin_DummyBoundingBoxes_input_Trigger.h
)

set(DummyBoundingBoxes_InputPins_Sources
)


set(DummyBoundingBoxes_InputPins_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/InputPin_DummyBoundingBoxes_input_Trigger_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/InputPin_Stub_DummyBoundingBoxes_input_Trigger.h
)

set(DummyBoundingBoxes_InputPins_Stubs_Sources
)


set(DummyBoundingBoxes_Stores_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_DummyBoundingBoxes_input_Trigger_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_DummyBoundingBoxes_output_Detections_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_DummyBoundingBoxes_output_Detections_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_Stub_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_DummyBoundingBoxes_output_Detections_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_DummyBoundingBoxes_output_ObjectData_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_DummyBoundingBoxes_output_ObjectData_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData.h
)

set(DummyBoundingBoxes_Stores_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_Stub_DummyBoundingBoxes_output_Detections.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_Detections.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData.cpp
)


set(DummyBoundingBoxes_Stores_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_SQLite_DummyBoundingBoxes_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_Manager_SQLite_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_SQLite_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_Manager_Ringbuffer_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_SQLite_DummyBoundingBoxes_output_ObjectData.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/Store_Manager_Ringbuffer_DummyBoundingBoxes_output_ObjectData.h
)

set(DummyBoundingBoxes_Stores_Sources
)


set(DummyBoundingBoxes_OutputPins_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/OutputPin_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/OutputPin_DummyBoundingBoxes_output_ObjectData.h
)

set(DummyBoundingBoxes_OutputPins_Sources
)


set(DummyBoundingBoxes_OutputPins_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/OutputPin_DummyBoundingBoxes_output_Detections_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/OutputPin_Stub_DummyBoundingBoxes_output_Detections.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/OutputPin_DummyBoundingBoxes_output_ObjectData_Default.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/stubs/OutputPin_Stub_DummyBoundingBoxes_output_ObjectData.h
)

set(DummyBoundingBoxes_OutputPins_Stubs_Sources
)


set(DummyBoundingBoxes_Module_Headers
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/DummyBoundingBoxesModule.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/DummyBoundingBoxesWorker.h
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/DummyBoundingBoxesModuleFactory.h
)

set(DummyBoundingBoxes_Module_Sources
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/DummyBoundingBoxesModule.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/DummyBoundingBoxesWorker.cpp
	${ConnectedVisionCppRoot}/modules/DummyBoundingBoxes/src/DummyBoundingBoxesModuleFactory.cpp
)



include_directories(
	${ConnectedVisionCppRoot}/core/include/
	${ConnectedVisionCppRoot}/core/src/
)


set(HEADERS
	${DummyBoundingBoxes_DataClasses_Headers}
	${DummyBoundingBoxes_DataClasses_Stubs_Headers}
	${DummyBoundingBoxes_InputPins_Headers}
	${DummyBoundingBoxes_InputPins_Stubs_Headers}
	${DummyBoundingBoxes_Stores_Stubs_Headers}
	${DummyBoundingBoxes_Stores_Headers}
	${DummyBoundingBoxes_OutputPins_Headers}
	${DummyBoundingBoxes_OutputPins_Stubs_Headers}
	${DummyBoundingBoxes_Module_Headers}
)

set(SOURCES
	${DummyBoundingBoxes_DataClasses_Sources}
	${DummyBoundingBoxes_DataClasses_Stubs_Sources}
	${DummyBoundingBoxes_InputPins_Sources}
	${DummyBoundingBoxes_InputPins_Stubs_Sources}
	${DummyBoundingBoxes_Stores_Stubs_Sources}
	${DummyBoundingBoxes_Stores_Sources}
	${DummyBoundingBoxes_OutputPins_Sources}
	${DummyBoundingBoxes_OutputPins_Stubs_Sources}
	${DummyBoundingBoxes_Module_Sources}
)


source_group(DataClasses FILES
	${DummyBoundingBoxes_DataClasses_Headers}
	${DummyBoundingBoxes_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${DummyBoundingBoxes_DataClasses_Stubs_Headers}
	${DummyBoundingBoxes_DataClasses_Stubs_Sources}
)
source_group(InputPins FILES
	${DummyBoundingBoxes_InputPins_Headers}
	${DummyBoundingBoxes_InputPins_Sources}
)
source_group(InputPins\\Stubs FILES
	${DummyBoundingBoxes_InputPins_Stubs_Headers}
	${DummyBoundingBoxes_InputPins_Stubs_Sources}
)
source_group(Stores\\Stubs FILES
	${DummyBoundingBoxes_Stores_Stubs_Headers}
	${DummyBoundingBoxes_Stores_Stubs_Sources}
)
source_group(Stores FILES
	${DummyBoundingBoxes_Stores_Headers}
	${DummyBoundingBoxes_Stores_Sources}
)
source_group(OutputPins FILES
	${DummyBoundingBoxes_OutputPins_Headers}
	${DummyBoundingBoxes_OutputPins_Sources}
)
source_group(OutputPins\\Stubs FILES
	${DummyBoundingBoxes_OutputPins_Stubs_Headers}
	${DummyBoundingBoxes_OutputPins_Stubs_Sources}
)
source_group(Module FILES
	${DummyBoundingBoxes_Module_Headers}
	${DummyBoundingBoxes_Module_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(FILES
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}Module.h"
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}ModuleFactory.h"
	DESTINATION "include/Modules/${PROJECT_NAME}"
)