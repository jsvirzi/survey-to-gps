cmake_minimum_required(VERSION 3.27)
project(survey_to_gps C)

set(CMAKE_C_STANDARD 11)

add_executable(survey_to_gps
        plot-outline.c)

target_link_libraries(survey_to_gps m)
