cmake_minimum_required(VERSION 3.17)
project(game)

set(CMAKE_CXX_STANDARD 11)

set(LIBRARIES
        gtest
        pthread)
add_executable(game main.cpp game_test.cpp character_test.cpp Character.h Soldier.h Soldier.cpp Medic.h Medic.cpp Sniper.h
                Sniper.cpp Game.cpp Game.h Exceptions.h Exceptions.cpp Auxiliaries.cpp Auxiliaries.h)
target_link_libraries(game ${LIBRARIES})