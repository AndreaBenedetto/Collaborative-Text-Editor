cmake_minimum_required(VERSION 3.14)
project(Client)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

qt5_add_resources(QRC IconsClient.qrc)

list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::PrintSupport
        )
list(REMOVE_DUPLICATES LIBRARIES)

add_executable(Client ${QRC} main.cpp Client.cpp Client.h User.cpp User.h LoginWindow.cpp LoginWindow.h RegistrationWindow.cpp RegistrationWindow.h CancellationWindow.cpp CancellationWindow.h FileChoiceWindow.cpp FileChoiceWindow.h OtherFunctions.cpp OtherFunctions.h SettingsWindow.cpp SettingsWindow.h Editor.cpp Editor.h Symbol.cpp Symbol.h MyTextEdit.cpp MyTextEdit.h UserInfo.cpp UserInfo.h ChooseFileNameWindow.cpp ChooseFileNameWindow.h OpenFileWindow.cpp OpenFileWindow.h URIWindow.cpp URIWindow.h)
target_link_libraries(Client ${LIBRARIES})