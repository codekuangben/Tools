set (PROJECT_NAME Sokit)
project(${PROJECT_NAME})

cmake_minimum_required(VERSION 2.8.10)
#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
#cmake_policy(SET CMP0003 NEW)

if (DEFINED ENV{QTDIR})
    set(CMAKE_PREFIX_PATH $ENV{QTDIR} ${CMAKE_PREFIX_PATH})
else ()
    message (FATAL_ERROR "ERROR: Environment variable QTDIR is not set. Please locate your Qt folder MY_QT5_DIR.")
endif ()

#set (CMAKE_MODULE_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64")
set (CMAKE_PREFIX_PATH "F:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

# CMake policy introduced in relation to Qt 5.1
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
	cmake_policy(SET CMP0020 OLD)
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

if(NOT Qt5Widgets_FOUND)
    message(SEND_ERROR "Failed to find Qt 5.0.0 or greater.")
else(NOT Qt5Widgets_FOUND)
    set(CMAKE_PACKAGE_QTGUI TRUE)

    file(GLOB UI_FILES *.ui)

    set(SRCS_FILES
		./baseform.cpp
		./baseform.h
		./clientform.cpp
		./clientform.h
		./clientskt.cpp
		./clientskt.h
		./helpform.cpp
		./helpform.h
		./logger.cpp
		./logger.h
		./main.cpp
		./main.h
		./notepadform.cpp
		./notepadform.h
		./resource.h
		./serverform.cpp
		./serverform.h
		./serverskt.cpp
		./serverskt.h
		./setting.cpp
		./setting.h
		./toolkit.cpp
		./toolkit.h
		./transferform.cpp
		./transferform.h
		./transferskt.cpp
		./transferskt.h
    )

	#these files need build moc files
    SET(MOC_FILES
		./main.h
        ./baseform.h
		./clientform.h
		./clientskt.h
		./helpform.h
		./logger.h
		./notepadform.h
		./serverform.h
		./serverskt.h
		./transferform.h
		./transferskt.h
    )
	
	SET(QRC_FILES ./icons.qrc)

	qt5_wrap_cpp(MOC_SRCS ${MOC_FILES})
    qt5_wrap_ui(UI_SRCS ${UI_FILES})
	qt5_add_resources(QRC_SRCS ${QRC_FILES})

    source_group("Moc Files" FILES ${MOC_SRCS})
    source_group("Ui Files" FILES ${UI_SRCS} ${UI_FILES})
	source_group("Qrc Files" FILES ${QRC_SRCS} ${QRC_FILES})
	
	file(GLOB RC_FILES ./*.rc)
	source_group("Rc Files" FILES ${RC_FILES})
	
    source_group("Base" FILES ${SRCS_FILES})

	# Create debug libraries with _d postfix
	set(CMAKE_DEBUG_POSTFIX "_d")

    # if we don't include this CMake will not include ui headers properly:
    #include_directories(${CMAKE_CURRENT_BINARY_DIR})
	# Find includes in corresponding build directories
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
	# Instruct CMake to run moc automatically when needed.
	#set(CMAKE_AUTOMOC ON)

    include_directories(.)
	#include_directories(${QT_BINARY_DIR}/../include)
	
	#link_directories(${QT_BINARY_DIR}/../lib)
	
    set(ALLSRCS ${SRCS_FILES} ${MOC_SRCS} ${UI_SRCS} ${QRC_SRCS} ${RC_FILES})

    ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALLSRCS})

    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")
	
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})
	
endif(NOT Qt5Widgets_FOUND)