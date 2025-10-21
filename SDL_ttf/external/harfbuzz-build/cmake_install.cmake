# Install script for directory: C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/GameCPP")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/ucrt64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/harfbuzz" TYPE FILE FILES
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-aat-layout.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-aat.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-blob.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-buffer.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-common.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-cplusplus.hh"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-deprecated.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-draw.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-face.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-font.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-map.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-color.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-deprecated.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-font.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-layout.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-math.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-meta.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-metrics.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-name.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-shape.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot-var.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ot.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-paint.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-set.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-shape-plan.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-shape.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-style.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-unicode.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-version.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-ft.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-gdi.h"
    "C:/Code/CPP/vendored/SDL_ttf/external/harfbuzz/src/hb-uniscribe.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Code/CPP/build/vendored/SDL_ttf/external/harfbuzz-build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
