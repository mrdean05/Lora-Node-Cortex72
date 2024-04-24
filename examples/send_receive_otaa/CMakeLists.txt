cmake_minimum_required(VERSION 3.16.3)

project(a72_lorawan_hello_otaa)

# rest of your project
add_executable(a72_lorawan_hello_otaa
    main.c
)

add_subdirectory("${pwd}/../../Lora-Node-Cortex72" "${pwd}/../../Lora-Node-Cortex72build")


target_link_libraries(a72_lorawan_hello_otaa pi_lorawan)

