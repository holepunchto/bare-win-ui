cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)
find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-prelude REQUIRED PATHS node_modules/cmake-prelude)

project(bare_win_ui C CXX)

fetch_package("github:holepunchto/bare@1.38.0")
fetch_package("github:holepunchto/libpath#a68d099")

include(cmake/windows-app-sdk.cmake)

add_bare_module(
  bare_win_ui
  SOURCES
    binding.cc
  LINK
    WindowsAppSDK
)

target_include_directories(
  ${bare_win_ui}
  PRIVATE
    node_modules/bare-winrt-registry/lib
)

target_compile_options(
  ${bare_win_ui}
  PRIVATE
    /GR-
)

target_precompile_headers(
  ${bare_win_ui}
  PRIVATE
    lib/windows-app-sdk.h
)

file(READ "package.json" pkg)

string(JSON version GET "${pkg}" version)

file(READ "lib/runtime.manifest" manifest)

string(CONFIGURE "${manifest}" manifest)

file(GENERATE OUTPUT "runtime.manifest" CONTENT "${manifest}" NEWLINE_STYLE WIN32)

bare_target(target)

add_executable_target(
  bare_runtime
  SOURCES
    lib/runtime.cc
    "${CMAKE_CURRENT_BINARY_DIR}/runtime.manifest"
  LINK
    $<LINK_LIBRARY:WHOLE_ARCHIVE,bare::static>
    bare::exports
    rlimit::static
    path::static
    WindowsAppSDK
  DESTINATION ${target}
  OUTPUT_DIRECTORY bin
  EXPORT OFF
)

set_target_properties(
  bare_runtime_executable
  PROPERTIES
  OUTPUT_NAME bare
)

target_compile_features(
  bare_runtime_executable
  PRIVATE
    cxx_std_20
)

target_compile_options(
  bare_runtime_executable
  PRIVATE
    /GR-
)

target_precompile_headers(bare_runtime_executable REUSE_FROM ${bare_win_ui})

add_dependencies(bare_runtime_executable WindowsAppSDK_Resources)

target_link_options(
  bare_runtime_executable
  PRIVATE
    /subsystem:windows
    /entry:mainCRTStartup
)

install(
  FILES
    $<TARGET_FILE:WebView2_Core>
    $<TARGET_FILE:Win2D_Canvas>
    $<TARGET_FILE:WindowsAppSDK_Bootstrap>
    ${WindowsAppSDK_Resources_FILE}
  DESTINATION ${target}/bare
)
