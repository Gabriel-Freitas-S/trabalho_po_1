cmake_minimum_required(VERSION 3.28)
project(trabalho_po_1 C)

set(CMAKE_C_STANDARD 17)

# Configurações de compilação otimizadas
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -DNDEBUG")

# Diretórios de include
include_directories(include)

# Coleta todos os arquivos fonte da pasta src
file(GLOB SOURCES
    "src/*.c"
    "main.c"
)

# Cria o executável principal
add_executable(trabalho_po_1 ${SOURCES})

# Link com bibliotecas matemáticas
target_link_libraries(trabalho_po_1 m)

# Configurações específicas por compilador
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(trabalho_po_1 PRIVATE -Wformat=2 -Wundef -Wshadow)
endif()

# Cria diretórios necessários em tempo de build
add_custom_command(TARGET trabalho_po_1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/output
    COMMENT "Criando estrutura de diretórios"
)
