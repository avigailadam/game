//
// Created by avi on 13/06/2021.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include "Auxiliaries.h"
#include "Exceptions.h"
#include <cmath>
#include <memory>
#include <vector>


namespace mtm {
    class Character {
    private:
        Team team;
        int health;
        int current_ammo;
        int reload_ammo;
        int range;
        int power;
        int moving_range;
        int ammo_per_attack;

    protected:
        /// @param team The team the character belongs to.
        /// @param health The current health
        /// @param currentAmmo
        /// @param reloadAmmo Ammo reloaded on reload
        /// @param attackRange
        /// @param attackDamageBase
        /// @param movingRange
        /// @param ammoPerAttack
        Character(Team team, int health, int currentAmmo, int reloadAmmo, int attackRange, int attackDamageBase,
                  int movingRange, int ammoPerAttack) : team(team), health(health), current_ammo(currentAmmo),
                                                        reload_ammo(reloadAmmo), range(attackRange), power(attackDamageBase),
                                                        moving_range(movingRange),
                                                        ammo_per_attack(ammoPerAttack) {}

    public:
        /// @return A clone of the current character, including all of its current state.
        virtual std::shared_ptr<Character> clone() const = 0;

        /// @param characterPosition
        /// @param positionToAttack
        /// @return All coordinates (potentially around) the positionToAttack. This enables support for area attacks
        virtual std::vector<GridPoint>
        getAttackCoordinates(const GridPoint &characterPosition, const GridPoint &positionToAttack) = 0;

        // TODO document
        ///
        /// @param victim
        /// @param distance_from_attacked_point
        /// @param reduce
        virtual void attack(Character &victim, int distance_from_attacked_point, bool reduce) = 0;

        virtual ~Character()= default;

        void reduceHealth(int amount) {
            health -= amount;
        }

        void increaseHealth(int amount) {
            health += amount;
        }

        /// Reduces ammo by the character's ammo per attack.
        void reduceAmmo() {
            current_ammo -= ammo_per_attack;
        }

        void reload() {
            current_ammo += reload_ammo;
        }

        int getAmmoPerAttack() const {
            return ammo_per_attack;
        }

        Team getTeam() const {
            return team;
        }

        int getHealth() const {
            return health;
        }

        int getCurrentAmmo() const {
            return current_ammo;
        }

        int getRange() const {
            return range;
        }

        int getPower() const {
            return power;
        }

        int getMovingRange() const {
            return moving_range;
        }

        // TODO document
        ///
        /// @param str
        /// @return
        virtual std::string &addToString(std::string &str) = 0;
    };
}

#endif //GAME_CHARACTER_H
