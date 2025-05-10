cmake_minimum_required(VERSION 3.10.0)
project(Balls VERSION 0.1.0 LANGUAGES C)

add_executable(Balls ball.c list.c main.c mylib.c)

target_link_libraries(Balls PRIVATE m glut GLU GL)