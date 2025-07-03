
cmake_minimum_required(VERSION 3.10)


project(trabalho-ecommerce LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)


aux_source_directory(src SRC_FILES)


add_executable(ecommerce_app 
    src/main.cpp
    src/produto.cpp
    src/vendedores.cpp   # <--- GARANTA QUE ESTE ARQUIVO ESTÁ AQUI
    src/compradores.cpp
    src/notaFiscal.cpp
)


message(STATUS "CMake configuration successful for 'ecommerce_app'")