cmake_minimum_required(VERSION 3.10)
project(ProducerConsumer)

# Enable most warning messages from the compiler
add_compile_options(-Wall)

# Specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_EXTENSIONS FALSE)

# Add the source directory
add_subdirectory(src)

# Specify the executable target
add_executable(producer_consumer src/main.c)
target_link_libraries(producer_consumer PRIVATE utils)
