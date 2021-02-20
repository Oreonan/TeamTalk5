include (ttlib)
include (speex)
include (opus)
include (libvpx)
include (ogg)
include (opustools)

set (CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/MediaUtil.cpp)
set (CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/MediaUtil.h)

option (SPEEX "Build Speex codec classes" ON)

if (SPEEX)
  list (APPEND CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/SpeexEncoder.cpp)
  list (APPEND CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/SpeexDecoder.cpp)
  list (APPEND CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/SpeexEncoder.h)
  list (APPEND CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/SpeexDecoder.h)
  list (APPEND CODEC_COMPILE_FLAGS -DENABLE_SPEEX)
  list (APPEND CODEC_INCLUDE_DIR ${SPEEX_INCLUDE_DIR})
  list (APPEND CODEC_LINK_FLAGS ${SPEEX_LINK_FLAGS})
endif()

option (OPUS "Build OPUS codec classes" ON)
if (OPUS)
  list (APPEND CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/OpusEncoder.cpp)
  list (APPEND CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/OpusDecoder.cpp)
  list (APPEND CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/OpusEncoder.h)
  list (APPEND CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/OpusDecoder.h)
  list (APPEND CODEC_COMPILE_FLAGS -DENABLE_OPUS)
  list (APPEND CODEC_INCLUDE_DIR ${OPUS_INCLUDE_DIR})
  list (APPEND CODEC_LINK_FLAGS ${OPUS_LINK_FLAGS})
endif()

option (LIBVPX "Build libVPX codec classes" ON)
if (LIBVPX)
  list (APPEND CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/VpxEncoder.cpp)
  list (APPEND CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/VpxDecoder.cpp)
  list (APPEND CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/VpxEncoder.h)
  list (APPEND CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/VpxDecoder.h)
  list (APPEND CODEC_COMPILE_FLAGS -DENABLE_VPX)
  list (APPEND CODEC_INCLUDE_DIR ${LIBVPX_INCLUDE_DIR})
  list (APPEND CODEC_LINK_FLAGS ${LIBVPX_LINK_FLAGS})
endif()

option (OGG "Build libOgg classes" ON)
if (OGG)
  list (APPEND CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/OggFileIO.cpp)
  list (APPEND CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/OggFileIO.h)
  list (APPEND CODEC_COMPILE_FLAGS -DENABLE_OGG)
  list (APPEND CODEC_INCLUDE_DIR ${OGG_INCLUDE_DIR})
  list (APPEND CODEC_LINK_FLAGS ${OGG_LINK_FLAGS})
endif()

option (OPUSTOOLS "Build Opus-tools" ON)
if (OPUSTOOLS)
  list (APPEND CODEC_SOURCES ${TTLIBS_ROOT}/opus-tools/src/opus_header.c)
  list (APPEND CODEC_HEADERS ${TTLIBS_ROOT}/opus-tools/src/opus_header.h)
  list (APPEND CODEC_COMPILE_FLAGS -DENABLE_OPUSTOOLS)
  list (APPEND CODEC_INCLUDE_DIR ${OPUSTOOLS_INCLUDE_DIR})
endif()

if (LIBVPX)
  if (${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND ${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    list (APPEND CODEC_LINK_FLAGS "-Wl,-Bsymbolic")
  endif()
endif()

if (MSVC)
  option (LAMEMP3 "Build MP3 Lame classes" OFF)

  if (LAMEMP3)
    list (APPEND CODEC_COMPILE_FLAGS -DENABLE_MP3 )
    list (APPEND CODEC_INCLUDE_DIR ${TTLIBS_ROOT}/lame-3.97/Dll)
    list (APPEND CODEC_HEADERS ${TEAMTALKLIB_ROOT}/codec/LameMP3.h)
    list (APPEND CODEC_SOURCES ${TEAMTALKLIB_ROOT}/codec/LameMP3.cpp)
  endif()
  
endif()
