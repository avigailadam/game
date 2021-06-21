//
// Created by avi on 13/06/2021.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H


#include "Character.h"
#include <vector>
#include <memory>
#include <ostream>

namespace mtm {

    enum CompareTeamResult {
        SAME, DIFFERENT, EMPTY
    };
    typedef int units_t;

    class Game {
    private:
        int height;
        int width;
        std::vector<std::vector<std::shared_ptr<mtm::Character>>> board;


        /// @param place coordinates on the game board
        /// @return pointer to the character on that place or null if empty
        std::shared_ptr<Character> getCharacterAt(const GridPoint &place) const;

        /// @param point
        /// @return whether a position is within the game board.
        bool isOutOfBounds(const GridPoint &point) const;

    public:

        /// @param height
        /// @param width
        /// @throw IllegalArgument if height or width are not a positive number.
        Game(int height, int width);

        ~Game() = default;

        /// copy's the game board and clone the characters in it.
        /// @param other
        Game(const Game &other);

        ///
        /// @param other
        /// @return reference for the copied game
        Game &operator=(const Game &other);

        /// @param coordinates
        /// @param character
        /// @throw IllegalCell if the coordinated are not in the game board.
        /// @throw CellOccupied if there is already a character on that place on the board.
        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);

        /// @param type
        /// @param team
        /// @param health
        /// @param ammo
        /// @param range
        /// @param power
        /// @throw IllegalArgument if any value is negative or health is zero.
        /// @return pointer for the new character.
        static std::shared_ptr<Character>
        makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power);

        /// @param src_coordinates the character's starting point.
        /// @param dst_coordinates the character's destination.
        /// @throw IllegalCell id if the starting point or destination is not in the game board.
        /// @throw CellEmpty if there is no character in the starting point.
        /// @throw MoveTooFar if the destination point is out of the character's moving range.
        /// @throw CellOccupied if there is already a character in the destination point.
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        /// @param src_coordinates the attacker's position.
        /// @param dst_coordinates the attack destination.
        /// @throw IllegalCell if the attacker's position, or the attacking point are not in the game board.
        /// @throw CellIsEmpty if there is no character in the attacker's position.
        /// @throw OutOfRange if the destination is not within the attacker's attacking range.
        /// @throw OutOfAmmo if the attacker doesn't have enough ammo left to attack.
        /// @throw Illegal target if the destination is not a legal destination for the character.
        /// if the character on the attacker position can attack the target on the destination by its criteria then it does its own attack way.
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        /// @param coordinates the character's place on board.
        /// the function adds the reload amount of the character to its current ammo.
        void reload(const GridPoint &coordinates);

        /// @param os
        /// @param game
        /// this operator overloading enables to print a game board.
        friend std::ostream &operator<<(std::ostream &os, Game &game);

        /// @param winningTeam a pointer that would be updated with the winning team or null is there is no winning team.
        /// @return whether the game is over or not.
        bool isOver(Team *winningTeam = NULL) const;
    };
}


#endif //GAME_GAME_H
