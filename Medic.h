//
// Created by avi on 13/06/2021.
//
#include "Character.h"

#ifndef GAME_MEDIC_H
#define GAME_MEDIC_H
namespace mtm {
    class Medic : public Character {
    private:
        static const int RELOAD_AMMO = 5;
        static const int MOVING_RANGE = 5;
        static const int AMMO_PER_ATTACK = 1;
    public:
        Medic(Team team, int health, int currentAmmo, int range, int power);

        ~Medic() override = default;

        /// @param src_coordinate
        /// @param dst_coordinate
        /// @throw OutOfRange if the point to attack is out of its attack range.
        /// @throw IllegalTarget if the attack is on them (it'll come before OutOfAmmo because there is no ammo check on characters from the attacker team).
        /// @return vector with one coordinate - the one they need to attack.
        std::vector<GridPoint>
        getAttackCoordinates(const GridPoint &src_coordinate, const GridPoint &dst_coordinate) override;

        /// @param victim
        /// @param distance_from_attacked_point that's here just to make sure we attack the requested point.
        /// @throw OutOfAmmo if the victim is from the other team, and the attacker doesn't have enough ammo to attack.
        /// if the victim is from the same team as the attacker they are healed, otherwise they are damaged.
        /// @return true if it was an attack and not a heal action.
        bool attack(std::shared_ptr<Character> victim, int distance_from_attacked_point) override;

        std::string &addToString(std::string &str) override;

        /// @return a pointer to a clone of the character.
        std::shared_ptr<Character> clone() const override;
    };
}

#endif //GAME_MEDIC_H
