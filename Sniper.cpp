//
// Created by avi on 13/06/2021.
//
#include <cassert>
#include "Sniper.h"

namespace mtm {
    Sniper::Sniper(Team team, int health, int currentAmmo, int range, int power) : Character(team, health, currentAmmo,
                                                                                             Sniper::RELOAD_AMMO,
                                                                                             range, power,
                                                                                             Sniper::MOVING_RANGE,
                                                                                             Sniper::AMMO_PER_ATTACK) {
        attack_counter = 0;
    }

    std::vector<GridPoint>
    Sniper::getAttackCoordinates(const GridPoint &src_coordinate, const GridPoint &dst_coordinate) {
        int distance = GridPoint::distance(src_coordinate, dst_coordinate);
        int range = getRange();
        if (distance > range || distance < ceil(double(range) / 2)) {
            throw OutOfRange();
        }
        if (getCurrentAmmo() < getAmmoPerAttack()) {
            throw OutOfAmmo();
        }
        if (distance == 0) {
            throw IllegalTarget();
        }
        return std::vector<GridPoint>(1, dst_coordinate);
    }

    bool Sniper::attack(std::shared_ptr<Character> victim, int distance_from_attacked_point) {
        assert(distance_from_attacked_point == 0);
        if (victim == nullptr || victim->getTeam() == getTeam()) {
            throw IllegalTarget();
        }
        int attack_by;
        int power = getPower();
        attack_counter++;
        attack_by = attack_counter % STRONG_ATTACK ? power : power * 2;
        victim->reduceHealth(attack_by);
        return true;
    }

    std::string &Sniper::addToString(std::string &str) {
        return getTeam() == POWERLIFTERS ? str += "N" : str += "n";
    }

    std::shared_ptr<Character> Sniper::clone() const {
        std::shared_ptr<Character> c(
                new Sniper(getTeam(), getHealth(), getCurrentAmmo(), getRange(), getPower()));
        std::dynamic_pointer_cast<Sniper>(c)->attack_counter = attack_counter;
        return c;
    }
}

