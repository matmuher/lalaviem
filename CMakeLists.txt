project(GardenApp)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
  message(SEND_ERROR "Failed to find SDL")
  return()
endif()

find_package(LLVM REQUIRED)
if(NOT LLVM_FOUND)
  message(SEND_ERROR "Failed to find LLVM")
  return()
endif()

include_directories(${CMAKE_SOURCE_DIR}/src
                    ${LLVM_INCLUDE_DIR}
                    ${SDL2_INCLUDE_DIRS}
                    "/usr/lib/llvm-14/include"
                    )

add_compile_options(-Wall -fPIC)

set(PASS_LIB src/Pass_start.cpp)
add_library(Pass SHARED ${PASS_LIB})

add_compile_options(-fpass-plugin=./libPass.so) 

add_executable(GardenApp src/start.c src/sim.c src/app.c src/log.c)
target_link_libraries(GardenApp SDL2)
