//
// Created by avi on 13/06/2021.
//

#ifndef GAME_SOLDIER_H
#define GAME_SOLDIER_H

#include "Character.h"

namespace mtm {
    class Soldier : public Character {
    private:
        static const int RELOAD_AMMO = 3;
        static const int MOVING_RANGE = 3;
        static const int AMMO_PER_ATTACK = 1;

    public:

        Soldier(Team team, int health, int currentAmmo, int range, int power);

        /// @param src_coordinate
        /// @param dst_coordinate
        /// @throw OutOfRange if the point to attack is out of its attacker's attack range.
        /// @throw OutOfAmmo if the attacker doesn't have enough ammo to attack.
        /// @throw IllegalTarget if the attacker tries to attack a coordinate that is not in his row or column.
        /// @return vector with coordinates - the ones in the attack area.
        std::vector<GridPoint>
        getAttackCoordinates(const GridPoint &src_coordinate, const GridPoint &dst_coordinate) override;

        /// @param victim
        /// @param distance_from_attacked_point
        /// if the attack is on a teammate, or an empty space nothing happens, otherwise the victim is damaged in relation to where he stands.
        /// @return true anyway because there is no limit on what he can attack.
        bool attack(std::shared_ptr<Character> victim, int distance_from_attacked_point) override;

        std::string &addToString(std::string &str) override;

        /// @return a pointer to a clone of the character.
        std::shared_ptr<Character> clone() const override;
    };
}

#endif //GAME_SOLDIER_H
