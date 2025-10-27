#pragma once

enum class EntityState
{
    // All
    NONE,
    WALK,
    HURT,
    DEAD,
    IDLE,

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

    SMALL_DRAGON_ATTACK,
    SMALL_DRAGON_FIRE,

    // DRAGON

    DRAGON_ATTACK,
    DRAGON_FIRE,

    // Demon

    DEMON_ATTACK,

    // Jinn
    JINN_ATTACK,

    // Lizard
    LIZARD_ATTACK,

    // Medusa
    MEDUSA_ATTACK,

    // Orc1
    ORC1_ATTACK,

    // Orc2
    ORC2_ATTACK,

    // Orc3
    ORC3_ATTACK,
    // Castle
    DAMAGED,
    DESTROYED,
    CASTLE_ATTACK,
};

namespace SamuraiState
{
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState IDLE = EntityState::IDLE;
    constexpr EntityState ATTACK1 = EntityState::SAMURAI_ATTACK1;
    constexpr EntityState ATTACK2 = EntityState::SAMURAI_ATTACK2;
    constexpr EntityState ATTACK3 = EntityState::SAMURAI_ATTACK3;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
} // namespace SamuraiState

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
} // namespace SamuraiArcherState

namespace SamuraiCommanderState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK1 = EntityState::SAMURAI_COMMANDER_ATTACK1;
    constexpr EntityState ATTACK2 = EntityState::SAMURAI_COMMANDER_ATTACK2;
    constexpr EntityState ATTACK3 = EntityState::SAMURAI_COMMANDER_ATTACK3;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
    constexpr EntityState IDLE = EntityState::IDLE;
} // namespace SamuraiCommanderState

namespace SmallDragonState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::SMALL_DRAGON_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
    constexpr EntityState FIRE = EntityState::SMALL_DRAGON_FIRE;
} // namespace SmallDragonState

namespace DragonState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::DRAGON_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
    constexpr EntityState FIRE = EntityState::DRAGON_FIRE;
} // namespace DragonState

namespace DemonState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState IDLE = EntityState::IDLE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::DEMON_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
} // namespace DemonState

namespace JinnState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::JINN_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
} // namespace JinnState

namespace LizardState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::LIZARD_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
    constexpr EntityState IDLE = EntityState::IDLE;
} // namespace LizardState

namespace MedusaState
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::MEDUSA_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
} // namespace MedusaState

namespace Orc1State
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::ORC1_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
} // namespace Orc1State

namespace Orc2State
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::ORC2_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
} // namespace Orc2State

namespace Orc3State
{
    constexpr EntityState NONE = EntityState::NONE;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState ATTACK = EntityState::ORC3_ATTACK;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState DEAD = EntityState::DEAD;
} // namespace Orc3State

namespace CastleState
{
    constexpr EntityState IDLE = EntityState::IDLE;
    constexpr EntityState DAMAGED = EntityState::DAMAGED;
    constexpr EntityState DESTROYED = EntityState::DESTROYED;
    constexpr EntityState HURT = EntityState::HURT;
    constexpr EntityState ATTACK = EntityState::CASTLE_ATTACK;
    constexpr EntityState DEAD = EntityState::DEAD;
    constexpr EntityState WALK = EntityState::WALK;
    constexpr EntityState NONE = EntityState::NONE;
} // namespace CastleState