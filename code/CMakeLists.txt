cmake_minimum_required(VERSION 3.5)

project(PCO_Barbier)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core Gui Widgets Test REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE FORMS "src/*.ui")

add_executable(pco_barbier ${SOURCES} ${HEADERS} ${FORMS})

target_link_libraries(pco_barbier PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test)
target_link_libraries(pco_barbier PRIVATE -lpcosynchro)


file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets/)
