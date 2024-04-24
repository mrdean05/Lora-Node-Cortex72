cmake_minimum_required(VERSION 3.16.3)

project(pi_lorawan)

set(LORAMAC_NODE_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/LoRaMac-node)


add_library(pi_loramac_node INTERFACE)

target_sources(pi_loramac_node INTERFACE
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/CayenneLpp.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandlerMsgDisplay.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/NvmDataMgmt.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandler/LmHandler.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandler/packages/FragDecoder.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandler/packages/LmhpClockSync.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandler/packages/LmhpCompliance.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandler/packages/LmhpFragmentation.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandler/packages/LmhpRemoteMcastSetup.c
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/NvmDataMgmt.c

    ${LORAMAC_NODE_PATH}/src/boards/mcu/utilities.c

    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/NvmDataMgmt.c

    ${LORAMAC_NODE_PATH}/src/mac/region/Region.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionAS923.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionAU915.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionBaseUS.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionCN470.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionCN470A20.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionCN470A26.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionCN470B20.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionCN470B26.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionCN779.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionCommon.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionEU433.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionEU868.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionIN865.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionKR920.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionRU864.c
    ${LORAMAC_NODE_PATH}/src/mac/region/RegionUS915.c
    ${LORAMAC_NODE_PATH}/src/mac/LoRaMac.c
    ${LORAMAC_NODE_PATH}/src/mac/LoRaMacAdr.c
    ${LORAMAC_NODE_PATH}/src/mac/LoRaMacClassB.c
    ${LORAMAC_NODE_PATH}/src/mac/LoRaMacCommands.c
    ${LORAMAC_NODE_PATH}/src/mac/LoRaMacConfirmQueue.c
    ${LORAMAC_NODE_PATH}/src/mac/LoRaMacCrypto.c
    ${LORAMAC_NODE_PATH}/src/mac/LoRaMacParser.c
    ${LORAMAC_NODE_PATH}/src/mac/LoRaMacSerializer.c

    ${LORAMAC_NODE_PATH}/src/peripherals/soft-se/aes.c
    ${LORAMAC_NODE_PATH}/src/peripherals/soft-se/cmac.c
    ${LORAMAC_NODE_PATH}/src/peripherals/soft-se/soft-se-hal.c
    ${LORAMAC_NODE_PATH}/src/peripherals/soft-se/soft-se.c

    ${LORAMAC_NODE_PATH}/src/radio/sx126x/sx126x.c

    ${LORAMAC_NODE_PATH}/src/system/delay.c
     ${LORAMAC_NODE_PATH}/src/system/gpio.c
    ${LORAMAC_NODE_PATH}/src/system/nvmm.c
    ${LORAMAC_NODE_PATH}/src/system/systime.c
    ${LORAMAC_NODE_PATH}/src/system/timer.c

    ${CMAKE_CURRENT_LIST_DIR}/src/boards/board.c
    ${CMAKE_CURRENT_LIST_DIR}/src/boards/delay-board.c
    ${CMAKE_CURRENT_LIST_DIR}/src/boards/ioexpander.c
    ${CMAKE_CURRENT_LIST_DIR}/src/boards/gpio-board.c
    ${CMAKE_CURRENT_LIST_DIR}/src/boards/radio-board.c
    ${CMAKE_CURRENT_LIST_DIR}/src/boards/rtc-board.c
    ${CMAKE_CURRENT_LIST_DIR}/src/boards/spi-board.c
    ${CMAKE_CURRENT_LIST_DIR}/src/boards/sx126x-board.c
    ${CMAKE_CURRENT_LIST_DIR}/src/boards/eeprom-board.c
)

target_include_directories(pi_loramac_node INTERFACE
    ${LORAMAC_NODE_PATH}/src
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandler
    ${LORAMAC_NODE_PATH}/src/apps/LoRaMac/common/LmHandler/packages
    ${LORAMAC_NODE_PATH}/src/boards
    ${LORAMAC_NODE_PATH}/src/mac
    ${LORAMAC_NODE_PATH}/src/mac/region
    ${LORAMAC_NODE_PATH}/src/peripherals/soft-se
    ${LORAMAC_NODE_PATH}/src/radio
    ${LORAMAC_NODE_PATH}/src/radio/sx126x
    ${LORAMAC_NODE_PATH}/src/system
)

target_link_libraries(pi_loramac_node INTERFACE)

target_compile_definitions(pi_loramac_node INTERFACE -DSOFT_SE)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_EU868)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_US915)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_CN779)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_EU433)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_AU915)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_AS923)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_CN470)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_KR920)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_IN865)
target_compile_definitions(pi_loramac_node INTERFACE -DREGION_RU864)
target_compile_definitions(pi_loramac_node INTERFACE -DACTIVE_REGION=LORAMAC_REGION_US915)

add_library(pi_lorawan INTERFACE)

target_sources(pi_lorawan INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/lorawan.c
)

target_include_directories(pi_lorawan INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/include
)

# link pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


target_link_libraries(pi_lorawan INTERFACE pi_loramac_node Threads::Threads m)
