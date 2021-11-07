# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(CalcCity)

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

set(SOURCES
  src/main.c
  src/core.c
  src/display.c
  src/menus.c
  src/calccity.c
)

set(ASSETS)

set(ASSETS_fx
  assets-fx/calccity.png
  assets-fx/large_tileset.png
  assets-fx/mini_tileset.png
  assets-fx/large_water.png
  assets-fx/alerts.png
  assets-fx/title.png
  assets-fx/fn_keys.png
  assets-fx/fn_1.png
  assets-fx/fn_2.png
)

set(ASSETS_cg)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(myaddin ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(myaddin PRIVATE -Wall -Wextra -Os)
target_link_libraries(myaddin Gint::Gint)

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET myaddin OUTPUT "CalcCity.g1a"
    NAME "CalcCity" ICON assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET myaddin OUTPUT "CalcCity.g3a"
    NAME "CalcCity" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
endif()
