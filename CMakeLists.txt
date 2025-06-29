cmake_minimum_required(VERSION 3.10)
project(trabalho_ecommerce)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(ecommerce
    src/main.cpp
    src/Produto.cpp
    src/Vendas.cpp
)
