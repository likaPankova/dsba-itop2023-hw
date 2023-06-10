cmake_minimum_required(VERSION 3.5)

project(ex_modelview VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#set(TS_FILES ex_modelview/trans_ru.ts)


set(PROJECT_SOURCES
        ex_modelview/main.cpp
        ex_modelview/mainwindow.cpp
        ex_modelview/mainwindow.h
        ex_modelview/mainwindow.ui
        ex_modelview/tablemodel.cpp
        ex_modelview/tablemodel.h
        ex_modelview/addrowdialog.h
        ex_modelview/addrowdialog.cpp
        ex_modelview/addrowdialog.ui
        ex_modelview/proxymodel.h
        ex_modelview/proxymodel.cpp
        ex_modelview/about.h
        ex_modelview/about.cpp
        ex_modelview/about.ui
        ex_modelview/about.ui
        #${TS_FILES}
)



set(MACOSX_BUNDLE_ICON_FILE icon.ico)
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/ex_modelview/public/icon.ico")
set_source_files_properties(${app_icon_macos} PROPERTIES
      MACOSX_PACKAGE_LOCATION "Resources")


      qt_add_executable(ex_modelview
          MACOSX_BUNDLE
          MANUAL_FINALIZATION
          ${app_icon_macos}
          ${PROJECT_SOURCES}
      )




#find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

#qt6_add_translations(ex_modelview
#    TS_FILES trans_ru.ts
#    QM_FILES_OUTPUT_VARIABLE qm_files)
#install(FILES ${qm_files} DESTINATION .)



# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ex_modelview APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation


# And the following tells CMake where to find and install the file itself.


target_link_libraries(ex_modelview PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ex_modelview PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ex_modelview)
endif()
