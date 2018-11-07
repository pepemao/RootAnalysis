project(HSCP_DataFormats LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR}/../include )


ROOT_GENERATE_DICTIONARY(G__HSCPEvent HSCPEvent.h LINKDEF ${PROJECT_SOURCE_DIR}/../include/LinkDef.h)

add_library(DataFormatsHSCP SHARED HSCPEvent.cc EventProxyHSCP.cc PropertyEnum.cc G__HSCPEvent.cxx)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(DataFormats PUBLIC ${ROOTINCDIR}  ${CMAKE_SOURCE_DIR}/Core/include)
  
# Depend on a library that we defined in the top-level file
target_link_libraries(DataFormats)

install(TARGETS DataFormatsHSCP LIBRARY DESTINATION lib)

if(EXISTS libHSCPEvent_rdict.pcm)
  install(FILES libHSCPEvent_rdict.pcm libHSCPEvent.rootmap DESTINATION lib)
endif()

