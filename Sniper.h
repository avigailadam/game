//
// Created by avi on 13/06/2021.
//

#ifndef GAME_SNIPER_H
#define GAME_SNIPER_H

#include "Character.h"

namespace mtm {

    class Sniper : public Character {
    private:
        static const int RELOAD_AMMO = 2;
        static const int MOVING_RANGE = 4;
        static const int AMMO_PER_ATTACK = 1;
        static const int STRONG_ATTACK = 3;
        int attack_counter;


    public:

        /// initialize attack_counter to 0.
        /// @param team
        /// @param health
        /// @param currentAmmo
        /// @param range
        /// @param power
        Sniper(Team team, int health, int currentAmmo, int range, int power);
        ~Sniper() override = default;

        /// @param src_coordinate
        /// @param dst_coordinate
        /// @throw OutOfRange if the point to attack is out of its attacker's attack range.
        /// @throw OutOfAmmo if the attacker doesn't have enough ammo to attack.
        /// @throw IllegalTarget if the attacker tries to attack itself.
        /// @return vector with one coordinate - the one they need to attack.
        std::vector<GridPoint>
        getAttackCoordinates(const GridPoint &src_coordinate, const GridPoint &dst_coordinate) override;

        /// @param victim
        /// @param distance_from_attacked_point
        /// @throw IllegalTarget if the attacker tries to attack an empty spot or a teammate.
        /// the attacker attack if he can by its power and in every third attack by its power*2.
        /// @return true if the attack happened properly.
        bool attack(std::shared_ptr<Character> victim, int distance_from_attacked_point) override;

        std::string &addToString(std::string &str) override;

        /// @return a pointer to a clone of the character.
        std::shared_ptr<Character> clone() const override;
    };
}
#endif //GAME_SNIPER_H
