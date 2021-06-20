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

        // TODO document
        ///
        /// @param src_coordinate
        /// @param dst_coordinate
        /// @return
        std::vector<GridPoint>
        getAttackCoordinates(const GridPoint &src_coordinate, const GridPoint &dst_coordinate) override;

        void attack(Character &victim, int distance_from_attacked_point, bool reduce) override;
        // TODO document
        ///
        /// @param victim
        /// @param distance_from_attacked_point
        /// @param reduce

        std::string &addToString(std::string &str) override;

        std::shared_ptr<Character> clone() const override;
    };
}

#endif //GAME_MEDIC_H
