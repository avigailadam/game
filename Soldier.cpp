//
// Created by avi on 13/06/2021.
//

#include "Soldier.h"

namespace mtm {
    Soldier::Soldier(Team team, int health, int currentAmmo, int range, int power) :
            Character(team, health, currentAmmo, Soldier::RELOAD_AMMO, range, power, Soldier::MOVING_RANGE,
                      Soldier::AMMO_PER_ATTACK) {}

    std::string &Soldier::addToString(std::string &str) {
        return getTeam() == POWERLIFTERS ? str += "S" : str += "s";
    }

    std::vector<GridPoint>
    Soldier::getAttackCoordinates(const GridPoint &src_coordinate, const GridPoint &dst_coordinate) {
        std::vector<GridPoint> vector;
        int distance = GridPoint::distance(src_coordinate, dst_coordinate);
        int range = getRange();
        if (distance > range) {
            throw OutOfRange();
        }
        if (getCurrentAmmo() < getAmmoPerAttack()) {
            throw OutOfAmmo();
        }
        if ((src_coordinate.row != dst_coordinate.row) && (src_coordinate.col != dst_coordinate.col)) {
            throw IllegalTarget();
        }
        int max_dist = ceil(double(range) / 3);
        for (int i = dst_coordinate.row - max_dist; i <= dst_coordinate.row + max_dist; ++i) {
            for (int j = dst_coordinate.col - max_dist; j <= dst_coordinate.col + max_dist; ++j) {
                GridPoint curr_point(i, j);
                int dist = GridPoint::distance(curr_point, dst_coordinate);
                if (dist > max_dist) {
                    continue;
                }
                vector.push_back(curr_point);
            }
        }
        return vector;
    }

    bool Soldier::attack(std::shared_ptr<Character> victim, int distance_from_attacked_point) {
        if (victim == nullptr || getTeam() == victim->getTeam()) {
            return true;
        }
        double coefficient = distance_from_attacked_point == 0 ? 1.0 : 0.5;
        victim->reduceHealth(ceil(getPower() * coefficient));
        return true;
    }

    std::shared_ptr<Character> Soldier::clone() const {
        return std::shared_ptr<Character>(
                new Soldier(getTeam(), getHealth(), getCurrentAmmo(), getRange(), getPower()));
    }
}



