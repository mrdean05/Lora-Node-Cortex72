cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_PROJECT_NAME a72_lorawan_hello_otaa)

project(${CMAKE_PROJECT_NAME})

# rest of your project
add_executable(${CMAKE_PROJECT_NAME}
    main.c
)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../../Lora-Node-Cortex72" "${CMAKE_CURRENT_LIST_DIR}/../../Lora-Node-Cortex72/build")


target_link_libraries(${CMAKE_PROJECT_NAME} pi_lorawan)

