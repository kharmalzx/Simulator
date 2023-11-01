cmake_minimum_required(VERSION 3.4)
project(Simulator)
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_PREFIX_PATH "D:/QT/6.5.2/msvc2019_64/lib/cmake")

find_package(Qt6 COMPONENTS Widgets Core Gui StateMachine Quick Scxml REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Set the build output location to a common directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


file(GLOB SOURCE_FILE ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEAD_FILE ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB UI_FILE ${PROJECT_SOURCE_DIR} /*.ui)


add_subdirectory(include/QXlsx)

add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${HEAD_FILE})

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets Qt6::StateMachine Qt6::Quick Qt6::Scxml QXlsx::QXlsx)


#将生成的moc文件放到根目录下
#file(GLOB MOC_FILES "${PROJECT_SOURCE_DIR}/x64/Debug/moc/*.cpp")
#foreach(MOC_FILE ${MOC_FILES})
#    file(COPY ${MOC_FILE} DESTINATION ${PROJECT_SOURCE_DIR})
#endforeach()