#ifndef ZTGK_UNIT_H
#define ZTGK_UNIT_H
#include "ECS/Grid/Grid.h"
#include "ECS/Entity.h"
#include "ECS/Unit/Equipment/UnitEquipment.h"
#include "ECS/Unit/Mining/IMineable.h"
#include "ECS/Utils/AstarPathfinding.h"
#include "ECS/Unit/UnitAI/StateMachine/StateManager.h"
#include "ECS/Unit/Equipment/Modifiers.h"
#include "ECS/Unit/Mining/PickupubleItem.h"
#include "ECS/Utils/RNG.h"

class UnitSystem;

struct UnitStats {
    float max_hp{};
    float hp{};

    float move_spd{20};
    float move_spd_when_beaten{move_spd/2.0f};
    float mine_spd{};
    float atk_spd{1};

    Modifiers added{};
};

enum UnitType{
    UNIT_SPONGE,
    UNIT_BUG,
    UNIT_SHROOM
};

class Unit : public Component {
public:
    static const UnitStats ALLY_BASE;
    static const UnitStats ENEMY_BASE_BUG;
    static const UnitStats ENEMY_BASE_SHROOM;

    bool isSelected = false;

    Vector2Int gridPosition;
    glm::vec3 worldPosition;
    float rotation = 0;
    float currentRotation = 0;

    State* currentState;
    AstarPathfinding pathfinding;
    Grid* grid;

    UnitEquipment equipment;
    std::string icon_path;

    //target flags
    bool hasMovementTarget = false;
    bool hasCombatTarget = false;
    bool hasMiningTarget = false;
    bool hasPickupTarget = false;
    bool isTargetInRange = false;

    //targets
    Vector2Int movementTarget = Vector2Int(0, 0);
    Unit* combatTarget = nullptr;
    PickupubleItem * pickupTarget = nullptr;

    std::vector<IMineable*> miningTargets = {};
    IMineable* currentMiningTarget = nullptr;

    Unit(std::string name, Grid *grid, Vector2Int gridPosition, UnitStats stats, bool isAlly);
    ~Unit();

    bool IsAlly() const;

    void EquipItem(Item item, short slot);
    void UnequipItem(short slot);
    void UpdateStats();

    UnitStats GetBaseStats();

    void showImGuiDetailsImpl(Camera *camera) override;
    void UpdateImpl() override;

    bool isAlly;
    UnitStats stats;

    Unit* GetClosestEnemyInWeaponRange();
    std::vector<Unit*> GetPathableEnemiesInSight();
    Unit* GetClosestPathableEnemyInSight();
    Unit* GetClosestEnemyInSight();

    Vector2Int GetDirtiestTileAround();

    bool canFindPathToTarget(Vector2Int target);
    std::vector<IMineable> miningPath;

    void Pickup(PickupubleItem* item);

    // serializer
    // only use this with serializer!
    Unit() : equipment(this) {};
    // completes the serialization started by the new entity func
    void serializer_init(Grid * pGrid);
    // partially sets up the required components, always call serializer_init after this, before returning to the main loop!!
    static Entity * serializer_newUnitEntity(Scene * scene, const std::string & name);


    IMineable* findClosestMineable(const std::vector<IMineable>& MineablesToExclude = {});

    bool ForcedMovementState = false;
    Vector2Int forcedMovementTarget = Vector2Int(0, 0);
    void DIEXD();

    bool canPathToAttackTarget(Unit* target = nullptr);
    bool canPathToMiningTarget();


    bool isAlive = true;
    bool isBeingHealedByWashingMachine = false;

    bool playinIdleAnimation = false;

    Vector2Int getClosestWashingMachineTile();

    void tryToSendEmote(ztgk::game::EMOTES emote, float time = 2);

    ztgk::game::EMOTES mostRecentEmote;

    Speaker* speaker;

    UnitType unitType;

    float animationcooldown = 0;

    bool checkIfMaybeOtherUnitHasThisIMineableComponentAsThierCurrentMiningTargetAndReturnBooleanSayingTrueIfItHasAndFalseIfItDoesNot();

    bool lastUsedRightAttack = true;

    glm::vec3 calculateFlingDirection(Vector2Int killerPos);
    glm::vec3 flingDirection;

    //bool to decide if the unit is dead -> cannot kill right in Update because UnitSystem update crashes if we remove a unit from the list while iterating over it
    bool Omae_wa_mou_shindeiru = false;

private:
    Vector2Int previousGridPosition;
    void onFirstUpdate();
    bool firstUpdate = true;
    float deathTimer = 3;

};


#endif //ZTGK_UNIT_H
