#pragma once

enum class EntityState
{
    // All
    NONE,
    WALK,
    HURT,
    DEAD,

    // Samurai
    
    SAMURAI_ATTACK1,
    SAMURAI_ATTACK2,
    SAMURAI_ATTACK3,

    // Samurai_Archer

    SAMURAI_ARCHER_ATTACK1,
    SAMURAI_ARCHER_ATTACK2,
    SAMURAI_ARCHER_ATTACK3,
    SAMURAI_ARCHER_SHOT,

    // Samurai_Commander

    SAMURAI_COMMANDER_ATTACK1,
    SAMURAI_COMMANDER_ATTACK2,
    SAMURAI_COMMANDER_ATTACK3,

    // SMALL_DDRAGON

    SMALL_DDRAGON_ATTACK,

    // DRAGON

    DRAGON_ATTACK,
};

namespace SamuraiState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK1 = EntityState::SAMURAI_ATTACK1;
    constexpr EntityState ATTACK2 = EntityState::SAMURAI_ATTACK2;
    constexpr EntityState ATTACK3 = EntityState::SAMURAI_ATTACK3;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
}

namespace SamuraiArcherState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK1 = EntityState::SAMURAI_ARCHER_ATTACK1;
    constexpr EntityState ATTACK2 = EntityState::SAMURAI_ARCHER_ATTACK2;
    constexpr EntityState ATTACK3 = EntityState::SAMURAI_ARCHER_ATTACK3;
    constexpr EntityState SHOT = EntityState::SAMURAI_ARCHER_SHOT;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
}

namespace SamuraiCommanderState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK1 = EntityState::SAMURAI_COMMANDER_ATTACK1;
    constexpr EntityState ATTACK2 = EntityState::SAMURAI_ARCHER_ATTACK2;
    constexpr EntityState ATTACK3 = EntityState::SAMURAI_ARCHER_ATTACK3;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
}

namespace SmallDragon
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::SMALL_DDRAGON_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
}

namespace Dragon
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::DRAGON_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
}