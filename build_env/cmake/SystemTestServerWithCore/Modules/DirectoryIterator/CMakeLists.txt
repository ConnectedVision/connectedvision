cmake_minimum_required(VERSION 2.8.12)

project(DirectoryIterator)

set(ConnectedVisionCppRoot ../../../../../)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()


set(DirectoryIterator_DataClasses_Headers
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/Class_DirectoryIterator_output_FileMetadata.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/Class_DirectoryIterator_params.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/DirectoryIterator_ModuleDescription.h
)

set(DirectoryIterator_DataClasses_Sources
)


set(DirectoryIterator_DataClasses_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Class_DirectoryIterator_output_FileMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Stub_DirectoryIterator_output_FileMetadata.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Class_DirectoryIterator_params_Default.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Stub_DirectoryIterator_params.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Stub_DirectoryIterator_ModuleDescription.h
)

set(DirectoryIterator_DataClasses_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Stub_DirectoryIterator_output_FileMetadata.cpp
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Stub_DirectoryIterator_params.cpp
)


set(DirectoryIterator_Stores_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/sql/DirectoryIterator_output_FileMetadata.sql
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_Manager_SQLite_DirectoryIterator_output_FileMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_SQLite_DirectoryIterator_output_FileMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_SQLite_Stub_DirectoryIterator_output_FileMetadata.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_Manager_Ringbuffer_DirectoryIterator_output_FileMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata.h
)

set(DirectoryIterator_Stores_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata.cpp
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_SQLite_Stub_DirectoryIterator_output_FileMetadata.cpp
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata.cpp
)


set(DirectoryIterator_Stores_Headers
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/Store_Manager_SQLite_DirectoryIterator_output_FileMetadata.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/Store_SQLite_DirectoryIterator_output_FileMetadata.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/Store_Manager_Ringbuffer_DirectoryIterator_output_FileMetadata.h
)

set(DirectoryIterator_Stores_Sources
)


set(DirectoryIterator_OutputPins_Headers
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/OutputPin_DirectoryIterator_output_FileMetadata.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/OutputPin_DirectoryIterator_output_BinaryData.h
)

set(DirectoryIterator_OutputPins_Sources
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/OutputPin_DirectoryIterator_output_BinaryData.cpp
)


set(DirectoryIterator_OutputPins_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/OutputPin_DirectoryIterator_output_FileMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/stubs/OutputPin_Stub_DirectoryIterator_output_FileMetadata.h
)

set(DirectoryIterator_OutputPins_Stubs_Sources
)


set(DirectoryIterator_Module_Headers
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/DirectoryIteratorModule.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/DirectoryIteratorWorker.h
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/DirectoryIteratorModuleFactory.h
)

set(DirectoryIterator_Module_Sources
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/DirectoryIteratorModule.cpp
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/DirectoryIteratorWorker.cpp
	${ConnectedVisionCppRoot}/modules/DirectoryIterator/src/DirectoryIteratorModuleFactory.cpp
)



include_directories(
	${ConnectedVisionCppRoot}/core/include/
	${ConnectedVisionCppRoot}/core/src/
)


set(HEADERS
	${DirectoryIterator_DataClasses_Headers}
	${DirectoryIterator_DataClasses_Stubs_Headers}
	${DirectoryIterator_Stores_Stubs_Headers}
	${DirectoryIterator_Stores_Headers}
	${DirectoryIterator_OutputPins_Headers}
	${DirectoryIterator_OutputPins_Stubs_Headers}
	${DirectoryIterator_Module_Headers}
)

set(SOURCES
	${DirectoryIterator_DataClasses_Sources}
	${DirectoryIterator_DataClasses_Stubs_Sources}
	${DirectoryIterator_Stores_Stubs_Sources}
	${DirectoryIterator_Stores_Sources}
	${DirectoryIterator_OutputPins_Sources}
	${DirectoryIterator_OutputPins_Stubs_Sources}
	${DirectoryIterator_Module_Sources}
)


source_group(DataClasses FILES
	${DirectoryIterator_DataClasses_Headers}
	${DirectoryIterator_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${DirectoryIterator_DataClasses_Stubs_Headers}
	${DirectoryIterator_DataClasses_Stubs_Sources}
)
source_group(Stores\\Stubs FILES
	${DirectoryIterator_Stores_Stubs_Headers}
	${DirectoryIterator_Stores_Stubs_Sources}
)
source_group(Stores FILES
	${DirectoryIterator_Stores_Headers}
	${DirectoryIterator_Stores_Sources}
)
source_group(OutputPins FILES
	${DirectoryIterator_OutputPins_Headers}
	${DirectoryIterator_OutputPins_Sources}
)
source_group(OutputPins\\Stubs FILES
	${DirectoryIterator_OutputPins_Stubs_Headers}
	${DirectoryIterator_OutputPins_Stubs_Sources}
)
source_group(Module FILES
	${DirectoryIterator_Module_Headers}
	${DirectoryIterator_Module_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(FILES
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}Module.h"
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}ModuleFactory.h"
	DESTINATION "include/Modules/${PROJECT_NAME}"
)