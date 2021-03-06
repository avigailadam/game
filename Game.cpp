//
// Created by avi on 13/06/2021.
//
#include "Exceptions.h"
#include "Game.h"
#include "memory"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"
#include <ostream>

namespace mtm {

    Game::Game(int height, int width) : height(height), width(width) {
        if (height <= 0 || width <= 0) {
            throw IllegalArgument();
        }
        board = std::vector<std::vector<std::shared_ptr<Character>>>(height);
        for (int i = 0; i < height; ++i) {
            board[i] = std::vector<std::shared_ptr<Character>>(width, nullptr);
        }
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        if (isOutOfBounds(src_coordinates) || isOutOfBounds(dst_coordinates)) {
            throw IllegalCell();
        }
        if (getCharacterAt(src_coordinates) == nullptr) {
            throw CellEmpty();
        }
        std::shared_ptr<Character> attacker = getCharacterAt(src_coordinates);
        std::vector<GridPoint> targets = attacker->getAttackCoordinates(src_coordinates, dst_coordinates);
        bool costAmmo = false;
        for (const GridPoint &target : targets) {
            if (isOutOfBounds(target)) {
                continue;
            }
            std::shared_ptr<Character> victim = getCharacterAt(target);
            costAmmo |= attacker->attack(victim, GridPoint::distance(dst_coordinates, target));
            if (victim != nullptr && (victim->getHealth()) <= 0) {
                board[target.row][target.col] = nullptr;
            }
        }
        if (costAmmo) {
            attacker->reduceAmmo();
        }
    }

    bool Game::isOutOfBounds(const GridPoint &point) const {
        return point.row < 0 || point.col < 0 || point.row >= height || point.col >= width;
    }

    std::shared_ptr<Character> Game::getCharacterAt(const GridPoint &place) const {
        if (isOutOfBounds(place)) {
            throw IllegalCell();
        }
        return board[place.row][place.col];
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        std::shared_ptr<Character> character = getCharacterAt(src_coordinates);
        if (isOutOfBounds(src_coordinates) || isOutOfBounds(dst_coordinates)) {
            throw IllegalCell();
        }
        if (getCharacterAt(src_coordinates) == nullptr) {
            throw CellEmpty();
        }
        if (character->getMovingRange() < GridPoint::distance(src_coordinates, dst_coordinates)) {
            throw MoveTooFar();
        }
        if (getCharacterAt(dst_coordinates) != nullptr) {
            throw CellOccupied();
        }
        board[src_coordinates.row][src_coordinates.col] = nullptr;
        board[dst_coordinates.row][dst_coordinates.col] = character;
    }

    bool Game::isOver(Team *winningTeam) const {
        bool power_lifters_counter = false, crossfitters_counter = false;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::shared_ptr<Character> c = getCharacterAt(GridPoint(i, j));
                if (c == nullptr) {
                    continue;
                }
                *(c->getTeam() == POWERLIFTERS ? &power_lifters_counter : &crossfitters_counter) = true;
            }
            if (power_lifters_counter && crossfitters_counter) {
                return false;
            }
        }
        if (!power_lifters_counter && !crossfitters_counter) {
            return false;
        }
        if (winningTeam == nullptr) {
            return true;
        }
        *winningTeam = (power_lifters_counter ? POWERLIFTERS : CROSSFITTERS);
        return true;
    }

    std::shared_ptr<Character>
    Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power) {
        if (health < 1 || power < 0 || ammo < 0 || range < 0 || (team != POWERLIFTERS && team != CROSSFITTERS)) {
            throw IllegalArgument();
        }
        switch (type) {
            case SOLDIER:
                return std::shared_ptr<Character>(new Soldier(team, health, ammo, range, power));
            case SNIPER:
                return std::shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
            case MEDIC:
                return std::shared_ptr<Character>(new Medic(team, health, ammo, range, power));
            default:
                throw IllegalArgument();
        }
    }

    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {
        if (isOutOfBounds(coordinates)) {
            throw IllegalCell();
        }
        if (getCharacterAt(coordinates) != nullptr) {
            throw CellOccupied();
        }
        board[coordinates.row][coordinates.col] = character;
    }

    void Game::reload(const GridPoint &coordinates) {
        std::shared_ptr<Character> c = getCharacterAt(coordinates);
        if (c == nullptr) {
            throw CellEmpty();
        }
        c->reload();
    }

    std::ostream &operator<<(std::ostream &os, Game &game) {
        std::string str("");
        for (int row = 0; row < game.height; ++row) {
            for (int col = 0; col < game.width; col++) {
                if (game.board[row][col] == nullptr) {
                    str += " ";
                    continue;
                }
                game.board[row][col]->addToString(str);
            }
        }
        return printGameBoard(os, str.c_str(), str.c_str() + str.size(), game.width);
    }

    Game::Game(const Game &other) {
        board = other.board;
        width = other.width;
        height = other.height;
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; col++) {
                if (board[row][col] != nullptr) {
                    board[row][col] = other.board[row][col]->clone();
                }
            }
        }
    }

    Game &Game::operator=(const Game &other) {
        board = other.board;
        width = other.width;
        height = other.height;
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; col++) {
                if (board[row][col] != nullptr) {
                    board[row][col] = other.board[row][col]->clone();
                }
            }
        }
        return *this;
    }
}