cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project(ostreamable VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

add_library(${PROJECT_NAME} SHARED
  ostreamable.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER ../include/ostreamable.h)

target_include_directories(${PROJECT_NAME} PRIVATE ../include) 

install(TARGETS ${PROJECT_NAME} EXPORT OstreamableConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(EXPORT OstreamableConfig DESTINATION share/Ostreamable/cmake)

export(TARGETS ${PROJECT_NAME} FILE OstreamableConfig.cmake)

