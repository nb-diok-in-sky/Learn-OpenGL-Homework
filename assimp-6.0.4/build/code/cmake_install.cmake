# Install script for directory: D:/LearnOpenGL/assimp-6.0.4/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Assimp")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp6.0.4-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/LearnOpenGL/assimp-6.0.4/build/lib/Debug/assimp-vc143-mtd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/LearnOpenGL/assimp-6.0.4/build/lib/Release/assimp-vc143-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/LearnOpenGL/assimp-6.0.4/build/lib/MinSizeRel/assimp-vc143-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/LearnOpenGL/assimp-6.0.4/build/lib/RelWithDebInfo/assimp-vc143-mt.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp6.0.4" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/LearnOpenGL/assimp-6.0.4/build/bin/Debug/assimp-vc143-mtd.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/LearnOpenGL/assimp-6.0.4/build/bin/Release/assimp-vc143-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/LearnOpenGL/assimp-6.0.4/build/bin/MinSizeRel/assimp-vc143-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/LearnOpenGL/assimp-6.0.4/build/bin/RelWithDebInfo/assimp-vc143-mt.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/anim.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/aabb.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/ai_assert.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/camera.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/color4.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/color4.inl"
    "D:/LearnOpenGL/assimp-6.0.4/build/code/../include/assimp/config.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/ColladaMetaData.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/commonMetaData.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/defs.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/cfileio.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/light.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/material.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/material.inl"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/matrix3x3.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/matrix3x3.inl"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/matrix4x4.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/matrix4x4.inl"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/mesh.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/ObjMaterial.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/pbrmaterial.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/GltfMaterial.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/postprocess.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/quaternion.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/quaternion.inl"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/scene.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/metadata.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/texture.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/types.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/vector2.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/vector2.inl"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/vector3.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/vector3.inl"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/version.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/cimport.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/AssertHandler.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/importerdesc.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Importer.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/DefaultLogger.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/ProgressHandler.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/IOStream.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/IOSystem.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Logger.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/LogStream.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/NullLogger.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/cexport.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Exporter.hpp"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/DefaultIOStream.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/DefaultIOSystem.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/ZipArchiveIOSystem.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/SceneCombiner.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/fast_atof.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/qnan.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/BaseImporter.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Hash.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/MemoryIOWrapper.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/ParsingUtils.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/StreamReader.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/StreamWriter.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/StringComparison.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/StringUtils.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/SGSpatialSort.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/GenericProperty.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/SpatialSort.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/SkeletonMeshBuilder.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/SmallVector.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/SmoothingGroups.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/SmoothingGroups.inl"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/StandardShapes.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/RemoveComments.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Subdivision.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Vertex.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/LineSplitter.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/TinyFormatter.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Profiler.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/LogAux.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Bitmap.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/XMLTools.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/IOStreamBuffer.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/CreateAnimMesh.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/XmlParser.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/BlobIOSystem.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/MathFunctions.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Exceptional.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/ByteSwapper.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Compiler/pushpack1.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Compiler/poppack1.h"
    "D:/LearnOpenGL/assimp-6.0.4/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/LearnOpenGL/assimp-6.0.4/build/bin/Debug/assimp-vc143-mtd.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/LearnOpenGL/assimp-6.0.4/build/bin/Release/assimp-vc143-mt.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/LearnOpenGL/assimp-6.0.4/build/bin/MinSizeRel/assimp-vc143-mt.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/LearnOpenGL/assimp-6.0.4/build/bin/RelWithDebInfo/assimp-vc143-mt.pdb")
  endif()
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/LearnOpenGL/assimp-6.0.4/build/code/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
