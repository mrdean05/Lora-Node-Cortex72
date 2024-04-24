cmake_minimum_required(VERSION 3.16.3)

project(pi_lorawan_hello_otaa)

# rest of your project
add_executable(pi_lorawan_hello_otaa
    main.c
)

add_subdirectory("/home/pp/scripts/pplv1-lorawan" "/home/pp/scripts/pplv1-lorawan/build")

target_link_libraries(pi_lorawan_hello_otaa pi_lorawan)

