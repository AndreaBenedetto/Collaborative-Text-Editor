cmake_minimum_required(VERSION 3.14)
project(Server)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Qt5Sql REQUIRED)

qt5_add_resources(QRC IconsServer.qrc)

list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        sqlite3
        Qt5::Sql
        )
list(REMOVE_DUPLICATES LIBRARIES)

add_executable(Server ${QRC} main.cpp Server.cpp Server.h User.cpp User.h DataBaseOperations.cpp DataBaseOperations.h Symbol.cpp Symbol.h)
target_link_libraries(Server ${LIBRARIES})