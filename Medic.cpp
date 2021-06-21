
#include "Medic.h"
#include <cassert>

namespace mtm {
    Medic::Medic(Team team, int health, int currentAmmo, int range, int power) :
            Character(team, health, currentAmmo, Medic::RELOAD_AMMO, range, power, Medic::MOVING_RANGE,
                      Medic::AMMO_PER_ATTACK) {}

    std::string &Medic::addToString(std::string &str) {
        return getTeam() == POWERLIFTERS ? str += "M" : str += "m";
    }

    std::vector<GridPoint>
    Medic::getAttackCoordinates(const GridPoint &src_coordinate, const GridPoint &dst_coordinate) {
        if (GridPoint::distance(src_coordinate, dst_coordinate) > getRange()) {
            throw OutOfRange();
        }
        if (GridPoint::distance(src_coordinate, dst_coordinate) == 0) {
            throw IllegalTarget();
        }
        return std::vector<GridPoint>(1, dst_coordinate);
    }

    bool Medic::attack(std::shared_ptr<Character> victim, int distance_from_attacked_point) {
        assert(distance_from_attacked_point == 0);
        if (victim == nullptr) {
            throw IllegalTarget();
        }
        if (victim->getTeam() == getTeam()) {
            victim->increaseHealth(getPower());
            return false;
        }
        if (getCurrentAmmo() < getAmmoPerAttack()) {
            throw OutOfAmmo();
        }
        victim->reduceHealth(getPower());
        return true;
    }

    std::shared_ptr<Character> Medic::clone() const {
        return std::shared_ptr<Character>(new Medic(getTeam(), getHealth(), getCurrentAmmo(), getRange(), getPower()));
    }
}


