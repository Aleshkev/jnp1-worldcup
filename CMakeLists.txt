cmake_minimum_required(VERSION 3.16)
project(jnp1_worldcup)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wfatal-errors -Wall -Wextra -Wpedantic -O2"
        )

include_directories(.)

add_executable(jnp1_worldcup

        src/player.h
        src/field.h
        src/fields.h
        src/board.h
        src/defaultScoreboard.h
        src/worldcup.h
        src/worldcup_example.cc
        src/common.h)

add_custom_target(format
        COMMAND /usr/bin/clang-format
        -i
        organism.h
        )
