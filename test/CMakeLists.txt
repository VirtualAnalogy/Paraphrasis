file(GLOB PluginParametersTest_SOURCES *.cpp)
set(TinyThread_SOURCES ${CMAKE_SOURCE_DIR}/include/tinythread/source/tinythread.cpp)
add_executable(pluginparameterstest ${PluginParametersTest_SOURCES} ${TinyThread_SOURCES})
target_link_libraries(pluginparameterstest pthread)
