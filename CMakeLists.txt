cmake_minimum_required(VERSION 3.0.0)
project(compiler VERSION 0.1.0)

include(CTest)
enable_testing()


#For gdb debug use.
add_definitions("-Wall -g")
#add_compile_options("-lpython3.8")

#Build under linux platform.
FILE(GLOB SC_FILES "*.cpp" "*.h")
#MESSAGE("build linux solution...")
find_package(OpenSSL REQUIRED)
find_package(Threads)
set(DEP_LIBS
    OpenSSL::Crypto OpenSSL::SSL pthread  
)

#executable.
add_executable(${PROJECT_NAME} ${SC_FILES})

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

#openssl config.
target_include_directories(${PROJECT_NAME} PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${DEP_LIBS} ${Python3_LIBRARIES} dl)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
