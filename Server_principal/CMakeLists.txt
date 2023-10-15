cmake_minimum_required(VERSION 3.0)

project(MeuProjeto)

# Configurar as variáveis
set(SRCDIR src)
set(INCDIR inc)
set(OBJDIR out)

if (WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lws2_32")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWIN32")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm")
endif()

# Encontrar arquivos de origem
file(GLOB SRCS ${SRCDIR}/*.c)

# Criar um executável
add_executable(server ${SRCS})

# Definir diretórios de saída
set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Inclui a pasta de headers
target_include_directories(server PRIVATE ${INCDIR})
