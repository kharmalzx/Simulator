# Install script for directory: D:/vs projects/Simulator/include/QXlsx

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Simulator")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/vs projects/Simulator/lib/Debug/QXlsxQt6.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/vs projects/Simulator/lib/Release/QXlsxQt6.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/vs projects/Simulator/lib/MinSizeRel/QXlsxQt6.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/vs projects/Simulator/lib/RelWithDebInfo/QXlsxQt6.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QXlsxQt6" TYPE FILE FILES
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxabstractooxmlfile.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxabstractsheet.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxabstractsheet_p.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxcellformula.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxcell.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxcelllocation.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxcellrange.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxcellreference.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxchart.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxchartsheet.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxconditionalformatting.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxdatavalidation.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxdatetype.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxdocument.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxformat.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxglobal.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxrichstring.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxworkbook.h"
    "D:/vs projects/Simulator/include/QXlsx/header/xlsxworksheet.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake"
         "D:/vs projects/Simulator/include/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/vs projects/Simulator/include/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/vs projects/Simulator/include/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/vs projects/Simulator/include/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/vs projects/Simulator/include/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/vs projects/Simulator/include/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES
    "D:/vs projects/Simulator/include/QXlsx/QXlsxQt6Config.cmake"
    "D:/vs projects/Simulator/include/QXlsx/QXlsxQt6ConfigVersion.cmake"
    )
endif()

