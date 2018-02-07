cmake_minimum_required(VERSION 2.8.12)

project(ConnectedVisionCore)

option(USE_INSTALL_SUBDIRECTORY_STRUCTURE "create a subdirectory structure for the install directory which consists of architecture and configuration type" OFF)

set(ConnectedVisionCppRoot ../../..)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()

get_filename_component(ConnectedVisionCppRootAbs "${ConnectedVisionCppRoot}" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
create_version_info_file("${ConnectedVisionCppRootAbs}" "${ConnectedVisionCppRootAbs}/core/src/VersionInfo/VersionInfoTemplate.h" "${ConnectedVisionCppRootAbs}/core/src/VersionInfo/VersionInfo.h")

set(ConnectedVisionIncludeHeaders
	${ConnectedVisionCppRoot}/core/include/general.h
	${ConnectedVisionCppRoot}/core/include/ConnectedVision.h
	${ConnectedVisionCppRoot}/core/include/ConnectedVision_Exceptions.h
	${ConnectedVisionCppRoot}/core/include/ConnectedVision_SmartPointer.h
	${ConnectedVisionCppRoot}/core/include/ConnectedVision_Thread.h
	${ConnectedVisionCppRoot}/core/include/IConnectedVisionModule.h
	${ConnectedVisionCppRoot}/core/include/IDataClassJSON.h
	${ConnectedVisionCppRoot}/core/include/IDataSource.h
	${ConnectedVisionCppRoot}/core/include/IHTTPAbstraction.h
	${ConnectedVisionCppRoot}/core/include/IModuleEnvironment.h
	${ConnectedVisionCppRoot}/core/include/IModuleSource.h
	${ConnectedVisionCppRoot}/core/include/IStore.h
	${ConnectedVisionCppRoot}/core/include/IStoreCV.h
	${ConnectedVisionCppRoot}/core/include/ILogging.h
	${ConnectedVisionCppRoot}/core/include/ConnectedVision.h
	${ConnectedVisionCppRoot}/core/include/ConnectedVision_Exceptions.h
	${ConnectedVisionCppRoot}/core/include/ConnectedVision_SmartPointer.h
	${ConnectedVisionCppRoot}/core/include/ConnectedVision_Thread.h
)

set(ConnectedVisionCoreErrorHandlingHeaders
	${ConnectedVisionCppRoot}/core/src/ErrorHandling/CallStack.h
	${ConnectedVisionCppRoot}/core/src/ErrorHandling/Exception_CallStack.h
)

set(ConnectedVisionCoreErrorHandlingSources
	${ConnectedVisionCppRoot}/core/src/ErrorHandling/CallStack_GCC.cpp
	${ConnectedVisionCppRoot}/core/src/ErrorHandling/CallStack_MSVC.cpp
	${ConnectedVisionCppRoot}/core/src/ErrorHandling/Exception_CallStack.cpp
)

set(ConnectedVisionStubHeaders
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_moduleStatus.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_status.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_status_stableResults.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_HostStatus.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription_params.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription_params_properties.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleStatus.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_PinDescription.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_PinDescription_properties.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_Manager_SQLite_Stub_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_Manager_SQLite_Stub_generic_status.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_SQLite_Stub_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_SQLite_Stub_generic_status.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_aliasID.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_callback.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_chain.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_chain_connections.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Class_generic_status_qualityOfService_Default.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_status_qualityOfService.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription_configFeatures.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription_moduleFeatures.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Class_generic_config_configFeatures_Default.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Class_ModuleDescription_configFeatures_Default.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Class_ModuleDescription_moduleFeatures_Default.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_configFeatures.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Class_generic_config_configFeatures_Default.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Class_generic_status_qualityOfService_Default.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Class_ModuleDescription_configFeatures_Default.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Class_ModuleDescription_moduleFeatures_Default.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_Manager_SQLite_Stub_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_Manager_SQLite_Stub_generic_status.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_SQLite_Stub_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_SQLite_Stub_generic_status.h
)

set(ConnectedVisionStubSources
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_moduleStatus.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_status.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_status_stableResults.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_HostStatus.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription_params.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription_params_properties.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleStatus.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_PinDescription.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_PinDescription_properties.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_SQLite_Stub_generic_config.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_SQLite_Stub_generic_status.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_aliasID.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_callback.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_chain.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_chain_connections.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription_moduleFeatures.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_config_configFeatures.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_ModuleDescription_configFeatures.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Stub_generic_status_qualityOfService.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_SQLite_Stub_generic_config.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/Store_SQLite_Stub_generic_status.cpp
)

set(ConnectedVisionCoreHeaders
	${ConnectedVisionCppRoot}/core/src/DBConnection.h
	${ConnectedVisionCppRoot}/core/src/helper.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_config_aliasID.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_config_callback.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_config_chain.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_config_chain_connections.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_config_configFeatures.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_moduleStatus.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_status.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_status_qualityOfService.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_status_stableResults.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_HostStatus.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_ModuleDescription.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_ModuleDescription_moduleFeatures.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_ModuleDescription_configFeatures.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_ModuleDescription_params.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_ModuleDescription_params_properties.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_ModuleStatus.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_PinDescription.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_PinDescription_properties.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_RawData.h
	${ConnectedVisionCppRoot}/core/src/CNamedResourcesPool.h
	${ConnectedVisionCppRoot}/core/src/ConnectedVisionInputPin.h
	${ConnectedVisionCppRoot}/core/src/ConnectedVisionOutputPin.h
	${ConnectedVisionCppRoot}/core/src/DataSource_Memory_BaseClass.h
	${ConnectedVisionCppRoot}/core/src/DataSource_REST_BaseClass.h
	${ConnectedVisionCppRoot}/core/src/ModuleSource_Memory_BaseClass.h
	${ConnectedVisionCppRoot}/core/src/ModuleSource_REST_BaseClass.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Store_Manager_Ringbuffer_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Store_Manager_Ringbuffer_generic_status.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Store_Manager_SQLite_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Store_Manager_SQLite_generic_status.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Store_SQLite_generic_config.h
	${ConnectedVisionCppRoot}/core/src/Module/Control/Store_SQLite_generic_status.h
)

set(ConnectedVisionCoreSources
	${ConnectedVisionCppRoot}/core/src/helper.cpp
	${ConnectedVisionCppRoot}/core/src/DBConnection.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_config.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_config_chain.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_generic_status.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Control/Class_RawData.cpp
	${ConnectedVisionCppRoot}/core/src/CNamedResourcesPool.cpp
	${ConnectedVisionCppRoot}/core/src/ConnectedVisionInputPinControl.cpp
	${ConnectedVisionCppRoot}/core/src/ConnectedVisionInputPinData.cpp
	${ConnectedVisionCppRoot}/core/src/ConnectedVisionOutputPin.cpp
	${ConnectedVisionCppRoot}/core/src/DataSource_Memory_BaseClass.cpp
	${ConnectedVisionCppRoot}/core/src/DataSource_Memory_BaseClass_specializations.cpp
	${ConnectedVisionCppRoot}/core/src/DataSource_REST_BaseClass.cpp
	${ConnectedVisionCppRoot}/core/src/ModuleSource_Memory_BaseClass.cpp
	${ConnectedVisionCppRoot}/core/src/ModuleSource_REST_BaseClass.cpp
)

set(ConnectedVisionCoreDataHandlingHeaders
	${ConnectedVisionCppRoot}/core/src/DataHandling/DataAllocator_Pool.h
	${ConnectedVisionCppRoot}/core/src/DataHandling/DataAllocator_Primitive.h
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Cache.h
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Manager_Basic.h
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Manager_Dynamic.h
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Manager_Pool.h
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Manager_Ringbuffer_Pool.h
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Ringbuffer.h
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_SQLite_BaseClass.h
)

set(ConnectedVisionCoreDataHandlingSources
	${ConnectedVisionCppRoot}/core/src/DataHandling/DataAllocator_Pool.cpp
	${ConnectedVisionCppRoot}/core/src/DataHandling/DataAllocator_Primitive.cpp
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Cache.cpp
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Manager_Basic.cpp
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Manager_Dynamic.cpp
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Manager_Pool.cpp
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_Ringbuffer.cpp
	${ConnectedVisionCppRoot}/core/src/DataHandling/Store_SQLite_BaseClass.cpp
)

set(ConnectedVisionCoreHTTPHeaders
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPServerPoco.h
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPClientPoco.h
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPTools.h
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPSServerPoco.h
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPSClientPoco.h
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPXClient.h
)

set(ConnectedVisionCoreHTTPSources
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPServerPoco.cpp
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPClientPoco.cpp
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPSServerPoco.cpp
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPSClientPoco.cpp
	${ConnectedVisionCppRoot}/core/src/HTTP/HTTPXClient.cpp
)

set(ConnectedVisionCoreModuleHeaders
	${ConnectedVisionCppRoot}/core/src/Module/WorkerController.h
	${ConnectedVisionCppRoot}/core/src/Module/Module_BaseClass.h
	${ConnectedVisionCppRoot}/core/src/Module/Worker_BaseClass.h
)

set(ConnectedVisionCoreModuleSources
	${ConnectedVisionCppRoot}/core/src/Module/WorkerController.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Module_BaseClass.cpp
	${ConnectedVisionCppRoot}/core/src/Module/Worker_BaseClass.cpp
)

set(ConnectedVisionCoreModuleDispatcherHeaders
	${ConnectedVisionCppRoot}/core/src/ModuleDispatcher/ModuleDispatcher.h
)

set(ConnectedVisionCoreModuleDispatcherSources
	${ConnectedVisionCppRoot}/core/src/ModuleDispatcher/ModuleDispatcher.cpp
)

set(ConnectedVisionCoreInputPinsHeaders
	${ConnectedVisionCppRoot}/core/src/Module/InputPins/InputPin_PNG.h
	${ConnectedVisionCppRoot}/core/src/Module/InputPins/InputPin_RAWYUV420.h
)

set(ConnectedVisionCoreInputPinsSources)

set(ConnectedVisionCoreOutputPinsHeaders
	${ConnectedVisionCppRoot}/core/src/Module/OutputPins/OutputPin_Generic.h
	${ConnectedVisionCppRoot}/core/src/Module/OutputPins/OutputPin_JSON.h
	${ConnectedVisionCppRoot}/core/src/Module/OutputPins/OutputPin_PNG.h
)

set(ConnectedVisionCoreOutputPinsSources
	${ConnectedVisionCppRoot}/core/src/Module/OutputPins/OutputPin_Generic.cpp
	${ConnectedVisionCppRoot}/core/src/Module/OutputPins/OutputPin_JSON.cpp
	${ConnectedVisionCppRoot}/core/src/Module/OutputPins/OutputPin_PNG.cpp
)


include_directories(
	${ConnectedVisionCppRoot}/core/include
	${ConnectedVisionCppRoot}/core/src
)

set(HEADERS
	${ConnectedVisionIncludeHeaders}
	${ConnectedVisionCoreErrorHandlingHeaders}
	${ConnectedVisionStubHeaders}
	${ConnectedVisionCoreHeaders}
	${ConnectedVisionCoreDataHandlingHeaders}
	${ConnectedVisionCoreHTTPHeaders}
	${ConnectedVisionCoreModuleHeaders}
	${ConnectedVisionCoreModuleDispatcherHeaders}
	${ConnectedVisionCoreInputPinsHeaders}
	${ConnectedVisionCoreOutputPinsHeaders}
)

set(SOURCES
	${ConnectedVisionCoreErrorHandlingSources}
	${ConnectedVisionStubSources}
	${ConnectedVisionCoreSources}
	${ConnectedVisionCoreDataHandlingSources}
	${ConnectedVisionCoreHTTPSources}
	${ConnectedVisionCoreModuleSources}
	${ConnectedVisionCoreModuleDispatcherSources}
	${ConnectedVisionCoreInputPinsSources}
	${ConnectedVisionCoreOutputPinsSources}
)


source_group(Source\ Files\\ErrorHandling FILES
	${ConnectedVisionCoreErrorHandlingHeaders}
	${ConnectedVisionCoreErrorHandlingSources}
)

source_group(Source\ Files\\Stubs FILES
	${ConnectedVisionStubHeaders}
	${ConnectedVisionStubSources}
)

source_group(Source\ Files FILES
	${ConnectedVisionCoreHeaders}
	${ConnectedVisionCoreSources}
)

source_group(Source\ Files\\DataHandling FILES
	${ConnectedVisionCoreDataHandlingHeaders}
	${ConnectedVisionCoreDataHandlingSources}
)

source_group(Source\ Files\\HTTP FILES
	${ConnectedVisionCoreHTTPHeaders}
	${ConnectedVisionCoreHTTPSources}
)

source_group(Source\ Files\\Module FILES
	${ConnectedVisionCoreModuleHeaders}
	${ConnectedVisionCoreModuleSources}
)

source_group(Source\ Files\\ModuleDispatcher FILES
	${ConnectedVisionCoreModuleDispatcherHeaders}
	${ConnectedVisionCoreModuleDispatcherSources}
)

source_group(Source\ Files\\InputPins FILES
	${ConnectedVisionCoreInputPinsHeaders}
	${ConnectedVisionCoreInputPinsSources}
)

source_group(Source\ Files\\OutputPins FILES
	${ConnectedVisionCoreOutputPinsHeaders}
	${ConnectedVisionCoreOutputPinsSources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(DIRECTORY
	"${ConnectedVisionCppRoot}/core/include/"
	DESTINATION "include"
	FILES_MATCHING PATTERN "*.h"
)

file(GLOB files "${ConnectedVisionCppRoot}/core/src/*.h")
install(FILES
	${files}
	"${ConnectedVisionCppRoot}/core/src/CNamedResourcesPool.cpp"
	"${ConnectedVisionCppRoot}/core/src/ConnectedVisionInputPinData.cpp"
	"${ConnectedVisionCppRoot}/core/src/ConnectedVisionOutputPin.cpp"
	"${ConnectedVisionCppRoot}/core/src/DataSource_Memory_BaseClass.cpp"
	"${ConnectedVisionCppRoot}/core/src/DataSource_REST_BaseClass.cpp"
	DESTINATION "include"
)

file(GLOB files "${ConnectedVisionCppRoot}/core/src/ErrorHandling/*.h")
install(FILES ${files} DESTINATION "include/ErrorHandling")

install(DIRECTORY
	"${ConnectedVisionCppRoot}/core/src/DataHandling/"
	DESTINATION "include/DataHandling"
)

file(GLOB files "${ConnectedVisionCppRoot}/core/src/HTTP/*.h")
install(FILES ${files} DESTINATION "include/HTTP")

file(GLOB files "${ConnectedVisionCppRoot}/core/src/Module/*.h")
install(FILES ${files} DESTINATION "include/Module")

file(GLOB files "${ConnectedVisionCppRoot}/core/src/Module/Control/*.h")
install(FILES ${files} DESTINATION "include/Module/Control")

file(GLOB files "${ConnectedVisionCppRoot}/core/src/Module/Control/stubs/*.h")
install(FILES ${files} DESTINATION "include/Module/Control/stubs")

file(GLOB files "${ConnectedVisionCppRoot}/core/src/ModuleDispatcher/*.h")
install(FILES ${files} DESTINATION "include/ModuleDispatcher")

install(DIRECTORY
	"${ConnectedVisionCppRoot}/core/src/Module/InputPins/"
	DESTINATION "include/Module/InputPins"
	FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY
	"${ConnectedVisionCppRoot}/core/src/Module/OutputPins/"
	DESTINATION "include/Module/OutputPins"
)

install(FILES
	"${ConnectedVisionCppRoot}/core/src/VersionInfo/VersionInfo.h"
	DESTINATION "include/VersionInfo"
)