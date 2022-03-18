cmake_minimum_required(VERSION 3.10)

project(parprog_problems VERSION 1.0 LANGUAGES CXX)

set(COMP_FLAGS "-pthread -l -Wall -Werror -Wfloat-equal
                -Wsign-conversion -Warray-bounds -Wdiv-by-zero
                -Wdouble-promotion -g3 -o0")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_definitions(${COMP_FLAGS})

add_executable(th1   threads01.cpp)
add_executable(th2   threads02.cpp)
add_executable(th3   threads03.cpp)
add_executable(th4   threads04.cpp)
add_executable(th401 threads0401.cpp)
add_executable(cth   cond_task.cpp)

target_link_libraries(th1   Threads::Threads)
target_link_libraries(th2   Threads::Threads)
target_link_libraries(th3   Threads::Threads)
target_link_libraries(th4   Threads::Threads)
target_link_libraries(th401 Threads::Threads)
target_link_libraries(cth   Threads::Threads)
