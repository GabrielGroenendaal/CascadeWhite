#include "codeinjection_new.h"
#include "kPrint.h"

extern "C"
{

    void THUMB_BRANCH_copyTrainerName(wchar_t *pDest, wchar_t *pSrc)
    {
        wcharsncpy(pSrc, pDest, 8);
    }

    // void THUMB_BRANCH_ARM9_02008B74(wchar_t *pDest, wchar_t *pSrc){
    //     wcharsncpy(pSrc, pDest, 8);
    // }

    bool PersonalCheckIfMoveCondition(BattleMon *a1, MoveCondition a2)
    {
        if (a2 == CONDITION_BLOCK && ((a1->Conditions[CONDITION_CURSE] & 7) != 0))
        {
            return true;
        }
        else
        {
            return (a1->Conditions[a2] & 7) != 0;
        }
    }

    bool isInArray(int value, int type)
    {
        if (type == 0)
        {
            for (int i = 0; i < 22; i++)
            {
                if (BulletproofMoves[i] == value)
                {
                    return true;
                }
            }
            return false;
        }
        else if (type == 1)
        {
            for (int i = 0; i < 17; i++)
            {
                if (WindMoves[i] == value)
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    bool overrideContact(BattleMon *a1, MoveID a2)
    {
        if (BattleMon_GetHeldItem(a1) == IT0293_SAFETY_GOGGLES || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
            return true;
        if (BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL089_IRON_FIST && getMoveFlag(a2, FLAG_PUNCH))
            return true;
        return false;
    }

    void HandlerOvercoatPowders(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v7; // r0
        int moveId;
        int result;
        moveId = BattleEventVar_GetValue(VAR_MOVE_ID);

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && (moveId == 78 || moveId == 79 || moveId == 147 || moveId == 76 || moveId == 476 || moveId == 77 || moveId == 139))
        {
            result = BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
            if (result)
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&v7->str, 2u, 210);
                BattleHandler_AddArg(&v7->str, (int)a3);
                BattleHandler_PopWork(a2, v7);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
            }
        }
    }

    bool checksIfWildBattle(ServerFlow *a1)
    {
        // k::Printf("\nBtlType is %d\n", a1->mainModule->btlSetup->BtlType);
        return a1->mainModule->btlSetup->btlType == 0;
    }

    bool checkIfConsumableItem(int a1)
    {
        return (PML_ItemIsBerry(a1) ||
                a1 == IT0290_FAIRY_GEM ||
                a1 == IT0043_BERRY_JUICE ||
                (a1 >= IT0545_ABSORB_BULB && a1 <= IT0564_NORMAL_GEM) ||
                a1 == IT0292_CLRS_BOOSTER ||
                a1 == IT0254_PROTO_ARMOR ||
                a1 == IT0286_CLRS_ARMOR ||
                a1 == IT0291_WEAKNESS_POLICY ||
                a1 == IT0274_MYSTERY_DEVICE ||
                a1 == IT0542_RED_CARD ||
                a1 == IT0294_PROTO_BOOSTER ||
                a1 == IT0543_RING_TARGET ||
                a1 == IT0275_FOCUS_SASH ||
                a1 == IT0219_MENTAL_HERB ||
                a1 == IT0214_WHITE_HERB ||
                a1 == IT0271_POWER_HERB ||
                a1 == IT0315_PROTO_ACCELERATOR ||
                a1 == IT0314_CLRS_INVENTION ||
                a1 == IT0318_CLRS_ACCELERATOR ||
                a1 == IT0541_AIR_BALLOON);
    }

    // // For Unnerve
    // // a1 is the position of the pokemon with unnerve
    // // a2 is the ServerFlow
    // // a3 is the type of skip i think
    // // a6 is supposedly the side of
    bool THUMB_BRANCH_SAFESTACK_HandlerUnnerveSkipCheck(BattleEventItem *a1, int a2, int a3, int a4, u16 a5, unsigned __int8 a6)
    {
        int PokeID;  // r0
        bool result; // r0

        result = 0;
        if (a3 == 5)
        {
            PokeID = BattleEventItem_GetPokeID(a1);
            if (!MainModule_IsAllyMonID(PokeID, a6))
            {
                if (checkIfConsumableItem(a5))
                {
                    return 1;
                }
            }
        }
        return result;
    }

    void THUMB_BRANCH_SAFESTACK_HandlerRegenerator(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;      // r6
        unsigned int v6;           // r4
        unsigned int v7;           // r0
        HandlerParam_ChangeHP *v8; // r0
        int Value;                 // [sp+0h] [bp-18h]

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            if (!BattleMon_IsFainted(PokeParam) && !BattleMon_IsFullHP(PokeParam))
            {
                v6 = DivideMaxHPZeroCheck(PokeParam, 4u);
                Value = BattleMon_GetValue(PokeParam, VALUE_MAX_HP);
                v7 = Value - BattleMon_GetValue(PokeParam, VALUE_CURRENT_HP);
                if (v6 > v7)
                {
                    v6 = v7;
                }
                v8 = (HandlerParam_ChangeHP *)BattleHandler_PushWork(a2, EFFECT_CHANGEHP, (int)a3);
                v8->pokeID[0] = (int)a3;
                v8->volume[0] = v6;
                v8->poke_cnt = 1;
                v8->fEffectDisable = 1;
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    void THUMB_BRANCH_HandlerIronFist(int a1, int a2, int a3)
    {
        int result;             // r0
        unsigned __int16 Value; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            result = getMoveFlag(Value, FLAG_PUNCH);
            if (result)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5325);
            }
        }
    }

    void THUMB_BRANCH_HandlerAftermath(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *aftermathMon;  // r0
        unsigned __int16 Value;   // r0
        int v7;                   // r6
        BattleMon *explodedMon;   // r7
        HandlerParam_Damage *v9;  // r4
        __int16 ExistAdjacentPos; // [sp+0h] [bp-18h]
        u8 adjacentPos[5];
        int v6;
        int i;

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            aftermathMon = Handler_GetBattleMon(a2, (int)a3);
            if (BattleMon_IsFainted(aftermathMon))
            {

                HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a2, EFFECT_ADD_ANIMATION, (int)a3);
                addAnimation->header.flags |= 0x800000u;
                addAnimation->animNo = MOVE153_EXPLOSION;
                addAnimation->pos_from = Handler_PokeIDToPokePos(a2, (int)a3);
                addAnimation->pos_to = 6;
                BattleHandler_PopWork(a2, addAnimation);

                ExistAdjacentPos = Handler_GetExistFrontPokePos(a2, (int)a3);
                v6 = Handler_ExpandPokeID(a2, ExistAdjacentPos | 0x200, adjacentPos);

                for (i = 0; i < v6; i++)
                {
                    explodedMon = Handler_GetPokeParam(a2, adjacentPos[i]);
                    v9 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, (int)a3);
                    v9->pokeID = v7;
                    v9->damage = DivideMaxHPZeroCheck(explodedMon, 3u);
                    v9->flags = v9->flags & 0xFE | 1;
                    BattleHandler_StrSetup(&v9->exStr, 2u, 402);
                    BattleHandler_AddArg(&v9->exStr, v7);
                    BattleHandler_PopWork(a2, v9);
                }
            }
        }
    }

    void THUMB_BRANCH_HandlerRockyHelmet(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;  // r0
        HandlerParam_Damage *v7; // r4
        BattleMon *attackingMon;
        BattleMon *BattleMon;      // r6
        unsigned __int8 ItemParam; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                attackingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
                if (overrideContact(attackingMon, (MoveID)Value))
                    return;

                v7 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, (int)a3);
                v7->pokeID = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleMon = Handler_GetBattleMon(a2, v7->pokeID);
                ItemParam = CommonGetItemParam(a1, ITSTAT_USE_PARAM);
                v7->damage = DivideMaxHPZeroCheck(BattleMon, ItemParam);
                BattleHandler_StrSetup(&v7->exStr, 2u, 424);
                BattleHandler_AddArg(&v7->exStr, v7->pokeID);
                BattleHandler_PopWork(a2, v7);
            }
        }
    }

    // // For Fluffy
    void HandlerFluffy(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        int Value;  // r0
        int isFire;
        int ratio;
        BattleMon *attackingMon;

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);

            isFire = (PML_MoveGetType(Value) == TYPE_FIRE) ? 2 : 1;

            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                attackingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
                if (overrideContact(attackingMon, (MoveID)Value))
                {
                    ratio = 4096;
                }
                else
                {
                    ratio = 2048;
                }
            }

            // k::Printf("\n\n isFire is %d\nratio is %d\nisFire times Ratio is %d\n\n", isFire, ratio, isFire * ratio);

            BattleEventVar_MulValue(VAR_RATIO, isFire * ratio);
        }
    }

    void HandlerIceScales(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result && PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) == 2)
        {
            // k::Printf("\n\n isFire is %d\nratio is %d\nisFire times Ratio is %d\n\n", isFire, ratio, isFire * ratio);

            BattleEventVar_MulValue(VAR_RATIO, 2048);
        }
    }

    void HandlerPickupNew(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *BattleMon; // r6
        int UsedItem;
        HandlerParam_SetItem *v8; // r0

        // k::Printf("\nWe are inside the first loop of logic\n");
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            // k::Printf("\nWe are inside the second loop of logic\n");

            BattleMon = Handler_GetBattleMon(a2, a3);
            UsedItem = BattleMon_GetUsedItem(BattleMon);

            if (UsedItem && BattleMon_GetHeldItem(BattleMon) == 0)
            {
                // k::Printf("\nWe are inside the third loop of logic\n");
                v8 = (HandlerParam_SetItem *)BattleHandler_PushWork(a2, EFFECT_SET_HELD_ITEM, a3);
                v8->header.flags |= 0x800000u;
                v8->itemID = UsedItem;
                v8->pokeID = a3;
                v8->fClearConsume = 0;
                BattleHandler_StrSetup(&v8->exStr, 2u, 1162);
                BattleHandler_AddArg(&v8->exStr, a3);
                BattleHandler_AddArg(&v8->exStr, UsedItem);
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    // // Weak Armor
    void THUMB_BRANCH_HandlerWeakArmor(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;             // r7
        int v6;                           // r6
        HandlerParam_ChangeStatStage *v7; // r0
        HandlerParam_ChangeStatStage *v8; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1 && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            v6 = 0;
            if (BattleMon_IsStatChangeValid(PokeParam, 2u, -1) || BattleMon_IsStatChangeValid(PokeParam, 5u, 2))
            {
                v6 = 1;
            }
            if (v6)
            {
                if (!BattleMon_IsFainted(PokeParam))
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v7->poke_cnt = 1;
                    v7->pokeID[0] = (unsigned int)a3;
                    v7->fMoveAnimation = 1;
                    v7->rankType = STATSTAGE_DEFENSE;
                    v7->rankVolume = -1;
                    BattleHandler_PopWork(a2, v7);
                    v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v8->poke_cnt = 1;
                    v8->pokeID[0] = (unsigned int)a3;
                    v8->fMoveAnimation = 1;
                    v8->rankType = STATSTAGE_SPEED;
                    v8->rankVolume = 2;
                    BattleHandler_PopWork(a2, v8);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
    }

    void THUMB_BRANCH_CommonContactStatusAbility(
        ServerFlow *a1,
        unsigned int *a2,
        MoveCondition a3,
        ConditionData a4,
        unsigned __int8 a5)
    {
        unsigned __int16 Value; // r0
        BattleMon *attackingMon;
        HandlerParam_AddCondition *v9; // r5

        if ((int)a2 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT) && !AbilityEvent_RollEffectChance((int)a1, a5))
            {
                attackingMon = Handler_GetBattleMon(a1, BattleEventVar_GetValue(VAR_ATTACKING_MON));

                if (overrideContact(attackingMon, (MoveID)Value))
                    return;

                v9 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a1, EFFECT_ADDCONDITION, (int)a2);
                v9->header.flags |= 0x800000u;
                v9->sickID = a3;
                v9->sickCont = a4;
                v9->fAlmost = 0;
                v9->pokeID = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleHandler_PopWork(a1, v9);
            }
        }
    }

    void THUMB_BRANCH_HandlerMummy(int a1, ServerFlow *a2, unsigned int a3)
    {
        unsigned __int16 Value;         // r0
        unsigned int v6;                // r6
        BattleMon *BattleMon;           // r0
        HandlerParam_ChangeAbility *v8; // r4

        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && !Handler_CheckMatchup((int)a2))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleMon = Handler_GetBattleMon(a2, v6);

                if (overrideContact(BattleMon, (MoveID)Value))
                    return;

                if (BattleMon_GetValue(BattleMon, VALUE_ABILITY) != 152)
                {
                    v8 = (HandlerParam_ChangeAbility *)BattleHandler_PushWork(a2, EFFECT_CHANGEABILITY, a3);
                    v8->abilityID = 152;
                    v8->pokeID = v6;
                    BattleHandler_StrSetup(&v8->exStr, 2u, 463);
                    BattleHandler_AddArg(&v8->exStr, v8->pokeID);
                    if (!MainModule_IsAllyMonID(a3, v6))
                    {
                        v8->header.flags |= 0x800000u;
                    }
                    BattleHandler_PopWork(a2, v8);
                }
            }
        }
    }

    void THUMB_BRANCH_HandlerRoughSkin(int a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;  // r0
        int v6;                  // r6
        BattleMon *BattleMon;    // r7
        HandlerParam_Damage *v8; // r4

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleMon = Handler_GetBattleMon(a2, v6);

                if (overrideContact(BattleMon, (MoveID)Value))
                    return;

                if (!BattleMon_IsFainted(BattleMon))
                {
                    v8 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, (int)a3);
                    v8->header.flags |= 0x800000u;
                    v8->pokeID = v6;
                    v8->damage = DivideMaxHPZeroCheck(BattleMon, 8u);
                    BattleHandler_StrSetup(&v8->exStr, 2u, 430);
                    BattleHandler_AddArg(&v8->exStr, v6);
                    BattleHandler_PopWork(a2, v8);
                }
            }
        }
    }

    void HandlerForewarnMessage(int a1, ServerFlow *a2, unsigned int a3)
    {
        BattleMon *PokeParam;     // r7
        int v6;                   // r6
        HandlerParam_Message *v1; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);

            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
            v1 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v1->str, 2u, 1228);
            BattleHandler_AddArg(&v1->str, a3);
            BattleHandler_PopWork(a2, v1);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
        }
    }

    // For Gooey
    void THUMB_BRANCH_HandlerCuteCharm(int a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;           // r0
        int v6;                           // r6
        BattleMon *PokeParam;             // r7
        HandlerParam_ChangeStatStage *v8; // r4

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {

                v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_ATTACKING_MON);
                PokeParam = Handler_GetBattleMon(a2, v6);

                if (overrideContact(PokeParam, (MoveID)Value))
                    return;

                if (!BattleMon_IsFainted(PokeParam))
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v8->poke_cnt = 1;
                    v8->pokeID[0] = (unsigned int)v6;
                    v8->fMoveAnimation = 1;
                    v8->rankType = STATSTAGE_SPEED;
                    v8->rankVolume = -1;
                    BattleHandler_PopWork(a2, v8);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
        return;
    }

    // Slush Rush
    void HandlerSlushRush(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && Handler_GetWeather(a2) == 3) // hail
        {
            BattleEventVar_MulValue(VAR_RATIO, 0x2000);
        }
    }

    void HandlerSlushRushPower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_ICE)
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
        }
    }

    void HandlerSandForceResist(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_ROCK)
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
        }
    }

    void HandlerSwiftSwimResist(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_WATER)
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
        }
    }

    // Tough Claws
    void HandlerToughClaws(int a1, int a2, int a3)
    {
        int result; // r0
        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            int MoveID = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(MoveID, FLAG_CONTACT))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
            }
        }
    }

    void HandlerAmplifier(int a1, int a2, int a3)
    {
        int result; // r0
        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            int MoveID = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(MoveID, FLAG_SOUND))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
            }
        }
    }

    // Heatproof
    void THUMB_BRANCH_HandlerHeatproofPower(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVE_TYPE);
            if (result == 9)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 1024);
            }
        }
    }

    int THUMB_BRANCH_SAFESTACK_HandlerIceBody(int a1, ServerFlow *a2, int a3)
    {
        int result;                 // r0
        BattleMon *PokeParam;       // r7
        HandlerParam_RecoverHP *v8; // r5

        result = BattleEventVar_GetValue(VAR_WEATHER);
        if (result == 3)
        {
            result = BattleEventVar_GetValue(VAR_MON_ID);
            if (a3 == result)
            {
                PokeParam = Handler_GetBattleMon(a2, a3);
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v8->header.flags |= 0x800000u;
                v8->pokeID = a3;
                v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, 0x8u);
                BattleHandler_PopWork(a2, v8);
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
        else
        {
            result = BattleEventVar_GetValue(VAR_MON_ID);
            if (a3 == result)
            {
                PokeParam = Handler_GetBattleMon(a2, a3);
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v8->header.flags |= 0x800000u;
                v8->pokeID = a3;
                v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, 0x10u);
                BattleHandler_PopWork(a2, v8);
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
        return result;
    }

    //
    void HandlerPreBurnOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        BattleMon *PokeParam; // r7

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            // k::Printf("\nWe are in, lets see if this works");
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_HasType(PokeParam, TYPE_FIRE))
            {
                v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v6->sickID = CONDITION_POISON;
                v6->sickCont = MakeBasicStatus(CONDITION_POISON);
                v6->fAlmost = 0;
                v6->pokeID = (unsigned __int8)a3;
                BattleHandler_StrSetup(&v6->exStr, 1u, 202);
                BattleHandler_AddArg(&v6->exStr, (int)a3);
                BattleHandler_PopWork(a2, v6);
            }
            else
            {
                v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v6->sickID = CONDITION_BURN;
                v6->sickCont = MakeBasicStatus(CONDITION_BURN);
                v6->fAlmost = 0;
                v6->pokeID = (unsigned __int8)a3;
                BattleHandler_StrSetup(&v6->exStr, 1u, 201);
                BattleHandler_AddArg(&v6->exStr, (int)a3);
                BattleHandler_PopWork(a2, v6);
            }
        }
    }

    void HandlerPrePoisonOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {

            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_POISON;
            v6->sickCont = MakeBasicStatus(CONDITION_POISON);
            v6->fAlmost = 0;
            v6->pokeID = (unsigned __int8)a3;
            BattleHandler_StrSetup(&v6->exStr, 1u, 202);
            BattleHandler_AddArg(&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerPreParalysisOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {

            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_PARALYSIS;
            v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            v6->fAlmost = 0;
            v6->pokeID = (unsigned __int8)a3;
            BattleHandler_StrSetup(&v6->exStr, 1u, 203);
            BattleHandler_AddArg(&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerPreStatusMarvelScaleOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        BattleMon *poke;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            poke = Handler_GetBattleMon(a2, a3);
            if (poke->Sex == 0)
            {
                v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v6->sickID = CONDITION_POISON;
                v6->sickCont = MakeBasicStatus(CONDITION_POISON);
                v6->fAlmost = 0;
                v6->pokeID = (unsigned __int8)a3;
                BattleHandler_StrSetup(&v6->exStr, 1u, 202);
                BattleHandler_AddArg(&v6->exStr, (int)a3);
                BattleHandler_PopWork(a2, v6);
            }
            else
            {
                v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v6->sickID = CONDITION_PARALYSIS;
                v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
                v6->fAlmost = 0;
                v6->pokeID = (unsigned __int8)a3;
                BattleHandler_StrSetup(&v6->exStr, 1u, 203);
                BattleHandler_AddArg(&v6->exStr, (int)a3);
                BattleHandler_PopWork(a2, v6);
            }
        }
    }

    int checkHigher(int a1, int a2)
    {
        if (a1 < a2)
        {
            return a2;
        }
        return a1;
    }

    int HandlerToxicBoostStatus(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r0
        int v6;     // r0

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_CONDITION_ID);
            if (result == 4)
            {
                Value = BattleEventVar_GetValue(VAR_DAMAGE);
                v6 = checkHigher(Value / 2, 1);
                return BattleEventVar_RewriteValue(VAR_DAMAGE, v6);
            }
        }
        return result;
    }

    int HandlerCorrosion(int a1, ServerFlow *a2, int a3)
    {
        int result;

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_POISON)
        {
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 4);
        }
        return result;
    }

    void HandlerDrySkinDamage(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVE_TYPE);
            if (result == 9)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
            }
        }
    }

    void HandlerToxicBoostDamage(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVE_TYPE);
            if (result == TYPE_POISON)
            {
                BattleEventVar_MulValue(VAR_RATIO, 2048);
            }
        }
    }

    void HandlerDistracting(int a1, ServerFlow *a2, int a3)
    {
        u8 *TempWork;                     // r4
        unsigned int v6;                  // r5
        HandlerParam_ChangeStatStage *v7; // r1
        unsigned int v8;                  // r3
        char v9;                          // r2
        char *v10;                        // r0
        __int16 ExistFrontPokePos;        // [sp+0h] [bp-18h]

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
            TempWork = Handler_GetTempWork(a2);
            v6 = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, TempWork);
            if (v6)
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
                v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                v7->rankType = STATSTAGE_EVASION;
                v7->rankVolume = -1;
                v7->fMoveAnimation = 1;
                v8 = 0;
                for (v7->poke_cnt = v6; v8 < v6; v10[16] = v9)
                {
                    v9 = TempWork[v8];
                    v10 = (char *)v7 + v8++;
                }
                BattleHandler_PopWork(a2, v7);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
        }
    }

    void THUMB_BRANCH_HandlerIntimidate(int a1, ServerFlow *a2, int a3)
    {
        u8 *TempWork;                     // r4
        unsigned int NumTargets;          // r5
        HandlerParam_ChangeStatStage *v7; // r1
        unsigned int v8;                  // r3
        unsigned int v88;
        u8 v9;                     // r2
        char *v10;                 // r0
        __int16 ExistFrontPokePos; // [sp+0h] [bp-18h]

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
            TempWork = Handler_GetTempWork(a2);
            NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, TempWork);
            if (NumTargets)
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);

                v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                v7->header.flags |= 0x08000000;
                v7->rankType = STATSTAGE_ATTACK;
                v7->rankVolume = -1;
                v7->fMoveAnimation = 1;
                v8 = 0;
                for (v7->poke_cnt = NumTargets; v8 < NumTargets; v10[16] = v9)
                {
                    v9 = TempWork[v8];
                    v10 = (char *)(v7 + v8++);
                }
                BattleHandler_PopWork(a2, v7);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
        }
    }
    // int __fastcall HandlerSynchronoise(int a1, ServerFlow *a2, int a3)
    // {
    //     int result;            // r0
    //     unsigned __int8 Value; // r0
    //     BattleMon *BattleMon;  // r6
    //     BattleMon *v8;         // r0
    //     int PokeType;          // r4
    //     int v10;               // r0

    //     result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
    //     if (a3 == result)
    //     {
    //         Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
    //         BattleMon = Handler_GetBattleMon(a2, Value);
    //         v8 = Handler_GetBattleMon(a2, a3);
    //         PokeType = BattleMon_GetPokeType(v8);
    //         v10 = BattleMon_GetPokeType(BattleMon);
    //         result = PokeTypePair_HasSharedType(PokeType, v10);
    //         if (!result)
    //         {
    //             return BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    //         }
    //     }
    //     return result;
    // }

    void RivalryOffense(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *attackingMon; // r4
        unsigned __int8 Value;   // r0
        BattleMon *defendingMon; // r5
        int v8;                  // r4
        int v9;                  // r0

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon(a2, a3);
            defendingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_DEFENDING_MON));
            v8 = BattleMon_GetPokeType(attackingMon);
            v9 = BattleMon_GetPokeType(defendingMon);

            if (PokeTypePair_HasSharedType(v8, v9))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5448);
            }
        }
    }

    void RivalryDefense(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *attackingMon; // r4
        unsigned __int8 Value;   // r0
        BattleMon *defendingMon; // r5
        int v8;                  // r4
        int v9;                  // r0

        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            defendingMon = Handler_GetBattleMon(a2, a3);
            attackingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
            v8 = BattleMon_GetPokeType(attackingMon);
            v9 = BattleMon_GetPokeType(defendingMon);

            if (PokeTypePair_HasSharedType(v8, v9))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2730);
            }
        }
    }

    void HandlerWellBakedBody(int a1, ServerFlow *a2, int a3)
    {
        if (CommonDamageRecoverCheck(a2, a3, TYPE_FIRE))
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_DEFENSE, 2);
        }
    }

    void HandlerNewLightningRod(int a1, ServerFlow *a2, int a3)
    {
        if (CommonDamageRecoverCheck(a2, a3, TYPE_ELECTRIC))
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_SPECIAL_ATTACK, 1);
        }
    }

    void HandlerNewStormDrain(int a1, ServerFlow *a2, int a3)
    {
        if (CommonDamageRecoverCheck(a2, a3, TYPE_WATER))
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_SPECIAL_ATTACK, 1);
        }
    }

    void HandlerForewarnNew(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_CRITICAL_FLAG))
        {
            BattleEventVar_MulValue(VAR_RATIO, 3072);
        }
    }

    // void HandlerNewHealer(ServerFlow *a1, int a2, int a3)
    // {
    //     BattleMon *BattleMon;       // r7
    //     HandlerParam_RecoverHP *v6; // r5

    //     if (a3 == BattleEventVar_GetValue(VAR_MON_ID) || MainModule_IsAllyMonID(a3, BattleEventVar_GetValue(VAR_MON_ID)))
    //     {

    //         BattleMon = Handler_GetBattleMon(a1, a2);
    //         v6 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a1, EFFECT_RECOVERHP, a2);
    //         if (BattleEventVar_GetValue(VAR_DISPLAYED) != 2)
    //         {
    //             v6->header.flags |= 0x800000u;
    //             BattleEventVar_SetConstValue(VAR_DISPLAYED, 2);
    //         }
    //         v6->pokeID = BattleEventVar_GetValue(VAR_MON_ID);
    //         v6->recoverHP = DivideMaxHPZeroCheck(BattleMon, 0x10u);
    //         BattleHandler_PopWork(a1, v6);
    //         BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    //     }
    // };

    int HandlerNewHealer(int a1, ServerFlow *a2, unsigned int a3, int a4)
    {

        int NumTargets;             // r0
        __int16 v7;                 // r0
        unsigned int currentTarget; // r4
        int currentTargetPosition;  // r1
        BattleMon *BattleMon;       // r0
        HandlerParam_RecoverHP *v6; // r5
        u8 v13[5];                  // [sp+4h] [bp-1Ch] BYREF
        int v14;                    // [sp+8h] [bp-18h]

        NumTargets = BattleEventVar_GetValue(VAR_MON_ID);
        v14 = a4;
        if (a3 == NumTargets)
        {
            BattleMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_MON_ID));
            if (!BattleMon_IsFullHP(BattleMon))
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
                v6 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, currentTargetPosition);
                v6->pokeID = currentTargetPosition;
                v6->recoverHP = DivideMaxHPZeroCheck(BattleMon, 0x10u);
                BattleHandler_PopWork(a2, v6);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
            v7 = Handler_PokeIDToPokePos(a2, a3);
            NumTargets = Handler_ExpandPokeID(a2, v7 | 0x700, v13);
            for (currentTarget = 0; currentTarget < NumTargets; currentTarget++)
            {
                currentTargetPosition = v13[currentTarget];
                BattleMon = Handler_GetBattleMon(a2, currentTargetPosition);
                if (!BattleMon_IsFullHP(BattleMon))
                {
                    v6 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, currentTargetPosition);
                    v6->pokeID = currentTargetPosition;
                    v6->recoverHP = DivideMaxHPZeroCheck(BattleMon, 0x10u);
                    BattleHandler_PopWork(a2, v6);
                }
            }
        }
        return NumTargets;
    }

    typedef struct
    {
        BattleEventType triggerValue;
        ABILITY_HANDLER_FUNC function;
    } ABILITY_TRIGGERTABLE;

    ABILITY_TRIGGERTABLE FriendGuardHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerFriendGuard}, // 0
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}};

    ABILITY_TRIGGERTABLE PlusMinusHandlers[] = {
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerPlusMinus},          // 2
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}, // 3
    };

    ABILITY_TRIGGERTABLE HealerHandlers[] = {
        {EVENT_TURN_CHECK_BEGIN, (ABILITY_HANDLER_FUNC)HandlerNewHealer},        // 4
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}, // 5
    };

    ABILITY_TRIGGERTABLE ToughClawsHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerToughClaws}, // 6
    };

    ABILITY_TRIGGERTABLE SlushRushHandlers[] = {
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSlushRush},              // 7
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 8
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSlushRushPower},
        {EVENT_ADD_CONDITION_CHECK_FAIL, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorStatus},
        {EVENT_ADD_CONDITION_FAIL, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon},
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorCureStatus},
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorCureStatus},
        {EVENT_ACTION_PROCESSING_END, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorActionEnd},
    };

    ABILITY_TRIGGERTABLE ThickFatHandlers[] = {
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerThickFat},           // 9
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 10
    };

    ABILITY_TRIGGERTABLE GutsHandlers[] = {
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerGuts},   // 11
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI}, // 12

    };

    ABILITY_TRIGGERTABLE QuickFeetHandlers[] = {

        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerQuickFeet},    // 13
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI}, // 14
    };

    ABILITY_TRIGGERTABLE FlareBoostHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerFlareBoost}, // 15
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI}, // 16
    };

    ABILITY_TRIGGERTABLE PoisonHealHandlers[] = {
        {EVENT_CONDITION_DAMAGE, (ABILITY_HANDLER_FUNC)HandlerPoisonHeal}, // 17
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},     // 18
    };

    ABILITY_TRIGGERTABLE ToxicBoostHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerToxicBoost},             // 42
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},           // 43
        {EVENT_CONDITION_DAMAGE, (ABILITY_HANDLER_FUNC)HandlerToxicBoostStatus}, // 44
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerToxicBoostDamage}};

    ABILITY_TRIGGERTABLE FluffyHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerFluffy},   // 22
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 23
    };

    ABILITY_TRIGGERTABLE OvercoatHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders}, // 24
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerOvercoat},               // 25
    };

    ABILITY_TRIGGERTABLE CorrosionHandlers[] = {
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerCorrosion}, // 26
    };

    ABILITY_TRIGGERTABLE MarvelScaleHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ABILITY_HANDLER_FUNC)HandlerMarvelScale},         // 27
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreStatusMarvelScaleOnAI}, // 28
    };

    ABILITY_TRIGGERTABLE RainDishHandlers[] = {
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerRainDish},                // 29
        {EVENT_ADD_CONDITION_CHECK_FAIL, (ABILITY_HANDLER_FUNC)HandlerWaterVeil},       // 30
        {EVENT_ADD_CONDITION_FAIL, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon}, // 31
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus}, // 32
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},            // 33
        {EVENT_ACTION_PROCESSING_END, (ABILITY_HANDLER_FUNC)HandlerWaterVeilActionEnd}, // 34
    };

    ABILITY_TRIGGERTABLE StrongBodyHandlers[] = {
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerClearBodyCheck}, // 35
        {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerClearBodyGuard},       // 36
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerOvercoat},                   // 37

    };

    ABILITY_TRIGGERTABLE DrySkinHandlers[] = {
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerDrySkinWeather},      // 38
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerDrySkinDamage},             // 39
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerDrySkinCheck}, // 40
    };

    ABILITY_TRIGGERTABLE PickupHandlers[] = {
        {EVENT_SWITCH_OUT_END, (ABILITY_HANDLER_FUNC)HandlerPickupNew}, // 41
    };

    ABILITY_TRIGGERTABLE SwiftSwimHandlers[] = {
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSwiftSwim},
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSwiftSwimResist} // 41
    };

    ABILITY_TRIGGERTABLE SandRushHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSandForce},
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSandVeilWeather}, // 41
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSandForceResist}};

    ABILITY_TRIGGERTABLE SandForceHandlers[] = {
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSandRush},              // 41
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSandVeilWeather}, // 41
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSandForceResist}};

    ABILITY_TRIGGERTABLE RivalryHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)RivalryOffense},               // 41
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)RivalryDefense}, // 41
    };

    ABILITY_TRIGGERTABLE DistractingHandlers[] = {
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerDistracting},            // 41
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerDistracting}, // 41
    };

    ABILITY_TRIGGERTABLE IceScalesHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerIceScales}, // 22
    };

    ABILITY_TRIGGERTABLE WellBakedBodyHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerWellBakedBody}, // 22
    };

    ABILITY_TRIGGERTABLE AmplifierHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerSoundproof}, // 22
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerAmplifier}};

    ABILITY_TRIGGERTABLE ForewarnHandlers[] = {
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerForewarnMessage}, // 22
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerForewarnMessage},
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerForewarnNew},
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}};

    ABILITY_TRIGGERTABLE LightningRodHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerNewLightningRod}, // 22
    };

    ABILITY_TRIGGERTABLE StormDrainHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerNewStormDrain}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLightningRod(_DWORD *a1)
    {
        *a1 = 1;
        return LightningRodHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddStormDrain(_DWORD *a1)
    {
        *a1 = 1;
        return StormDrainHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddForewarn(_DWORD *a1)
    {
        *a1 = 4;
        return ForewarnHandlers;
    }

    // Well Baked Body
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSuctionCups(_DWORD *a1)
    {
        *a1 = 1;
        return WellBakedBodyHandlers;
    }

    // Amplifier
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSoundproof(_DWORD *a1)
    {
        *a1 = 1;
        return AmplifierHandlers;
    }

    // Ice Scales
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRunAway(_DWORD *a1)
    {
        *a1 = 1;
        return IceScalesHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRivalry(_DWORD *a1)
    {
        *a1 = 2;
        return RivalryHandlers;
    }

    // Distracting
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddKlutz(_DWORD *a1)
    {
        *a1 = 2;
        return DistractingHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddFriendGuard(_DWORD *a1)
    {
        *a1 = 2;
        return FriendGuardHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPlus(_DWORD *a1)
    {
        *a1 = 2;
        return PlusMinusHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddHealer(_DWORD *a1)
    {
        *a1 = 2;
        return HealerHandlers;
    }

    // CORROSION
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLightMetal(_DWORD *a1)
    {
        *a1 = 1;
        return ToughClawsHandlers;
    }

    // SLUSH RUSH
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddHeavyMetal(_DWORD *a1)
    {
        *a1 = 8;
        return SlushRushHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddThickFat(_DWORD *a1)
    {
        *a1 = 2;
        return ThickFatHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddGuts(_DWORD *a1)
    {
        *a1 = 2;
        return GutsHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddQuickFeet(_DWORD *a1)
    {
        *a1 = 2;
        return QuickFeetHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddFlareBoost(_DWORD *a1)
    {
        *a1 = 2;
        return FlareBoostHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPoisonHeal(_DWORD *a1)
    {
        *a1 = 2;
        return PoisonHealHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddToxicBoost(_DWORD *a1)
    {
        *a1 = 4;
        return ToxicBoostHandlers;
    }

    // FLUFFY
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddImmunity(_DWORD *a1)
    {
        *a1 = 2;
        return FluffyHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddOvercoat(_DWORD *a1)
    {
        *a1 = 2;
        return OvercoatHandlers;
    }

    // CORROSION
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLimber(_DWORD *a1)
    {
        *a1 = 1;
        return CorrosionHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddMarvelScale(_DWORD *a1)
    {
        *a1 = 2;
        return MarvelScaleHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRainDish(_DWORD *a1)
    {
        *a1 = 6;
        return RainDishHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddClearBody(_DWORD *a1)
    {
        *a1 = 3;
        return StrongBodyHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddDrySkin(_DWORD *a1)
    {
        *a1 = 3;
        return DrySkinHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPickup(_DWORD *a1)
    {
        *a1 = 1;
        return PickupHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSwiftSwim(_DWORD *a1)
    {
        *a1 = 2;
        return SwiftSwimHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSandForce(_DWORD *a1)
    {
        *a1 = 3;
        return SandForceHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSandRush(_DWORD *a1)
    {
        *a1 = 3;
        return SandRushHandlers;
    }

    void HandlerIntimidateCheck(int a1, int a2, int a3, int *a4)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_INTIMFLAG) == 1)
            {

                if (BattleEventVar_GetValue(VAR_VOLUME) < 0)
                {

                    *a4 = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
                }
            }
        }
    }

    void HandlerIntimidateGuard(int a1, ServerFlow *a2, int a3, int *a4)
    {
        CommonStatDropGuardMessage(a2, a3, a4, 1240);
    }

    void HandlerRattledIntimidate(int a1, ServerFlow *a2, int a3)
    {
        int Value;                         // r0
        HandlerParam_ChangeStatStage *v13; // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {

            if (BattleEventVar_GetValue(VAR_INTIMFLAG) == 1)
            {
                v13 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                v13->header.flags |= 0x800000u;
                v13->rankType = STATSTAGE_SPEED;
                v13->rankVolume = 1;
                v13->fMoveAnimation = 1;
                v13->poke_cnt = 1;
                v13->pokeID[0] = a3;
                BattleHandler_PopWork(a2, v13);
            }
        }
    }

    void THUMB_BRANCH_CommonStatDropGuardCheck(int a1, int a2, int *a3, int a4)
    {
        if (a2 == BattleEventVar_GetValue(VAR_MON_ID) && (a2 != BattleEventVar_GetValue(VAR_ATTACKING_MON) || BattleEventVar_GetValue(VAR_HOSTILEFLAG) == 1) && (a4 == 8 || a4 == BattleEventVar_GetValue(VAR_MOVE_EFFECT)) && BattleEventVar_GetValue(VAR_VOLUME) < 0)
        {
            // k::Printf("\nBlocked\n");
            // k::Printf("Clear Body Handler: The INTIM flag is %d\nAnd the Hostile flag is %d\n", BattleEventVar_GetValue(VAR_INTIMFLAG), BattleEventVar_GetValue(VAR_HOSTILEFLAG));
            *a3 = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        }
    };

    void THUMB_BRANCH_HandlerDefiant(int a1, ServerFlow *a2, unsigned int a3)
    {
        unsigned __int8 Value;             // r0
        HandlerParam_ChangeStatStage *v13; // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            Value = BattleEventVar_GetValue(VAR_ATTACKING_MON);
            // k::Printf("Defiant Handler: The INTIM flag is %d\nAnd the Hostile flag is %d\n", BattleEventVar_GetValue(VAR_INTIMFLAG), BattleEventVar_GetValue(VAR_HOSTILEFLAG));
            if ((BattleEventVar_GetValue(VAR_INTIMFLAG) == 1 || BattleEventVar_GetValue(VAR_HOSTILEFLAG) == 1 || !MainModule_IsAllyMonID(a3, Value)) && BattleEventVar_GetValue(VAR_VOLUME) < 0)
            {
                v13 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                v13->header.flags |= 0x800000u;
                v13->rankType = STATSTAGE_ATTACK;
                v13->rankVolume = 2;
                v13->fMoveAnimation = 1;
                v13->poke_cnt = 1;
                v13->pokeID[0] = a3;
                BattleHandler_PopWork(a2, v13);
            }
        }
    }

    ABILITY_TRIGGERTABLE ScrappyHandlers[] = {
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerScrappy}, // 22
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerIntimidateCheck},
        {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerIntimidateGuard}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddScrappy(_DWORD *a1)
    {
        *a1 = 3;
        return ScrappyHandlers;
    }

    ABILITY_TRIGGERTABLE RattledHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ABILITY_HANDLER_FUNC)HandlerRattled}, // 22
        {EVENT_STAT_STAGE_CHANGE_APPLIED, (ABILITY_HANDLER_FUNC)HandlerRattledIntimidate}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRattled(_DWORD *a1)
    {
        *a1 = 2;
        return RattledHandlers;
    }

    int HandlerInnerFocusAttack(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_POKE_TYPE);
            if (result == TYPE_DARK)
            {
                return BattleEventVar_RewriteValue(VAR_NO_TYPE_EFFECTIVENESS, 1);
            }
        }
        return result;
    }

    ABILITY_TRIGGERTABLE InnerFocusHandlers[] = {
        {EVENT_FLINCH_CHECK, (ABILITY_HANDLER_FUNC)HandlerInnerFocus}, // 22
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerIntimidateCheck},
        {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerIntimidateGuard},
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerInnerFocusAttack}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddInnerFocus(_DWORD *a1)
    {
        *a1 = 4;
        return InnerFocusHandlers;
    }

    void HandlerAngerPointPower(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *mon;
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            mon = Handler_GetBattleMon(a2, a3);
            if (BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 6144);
            }
        }
    }

    void HandlerAngerPointSpeed(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *mon;
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            mon = Handler_GetBattleMon(a2, a3);
            if (BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                BattleEventVar_MulValue(VAR_RATIO, 6144);
            }
        }
    }

    void HandlerAngerPointMessage(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *mon;
        HandlerParam_Message *v1;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            mon = Handler_GetBattleMon(a2, a3);
            if (BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILED))
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                v1 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&v1->str, 2u, 1243);
                BattleHandler_AddArg(&v1->str, a3);
                BattleHandler_PopWork(a2, v1);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
            }
        }
    }

    ABILITY_TRIGGERTABLE AngerPointHandlers[] = {
        {EVENT_MOVE_EXECUTE_END, (ABILITY_HANDLER_FUNC)HandlerAngerPointMessage},  // 22
        {EVENT_MOVE_EXECUTE_FAIL, (ABILITY_HANDLER_FUNC)HandlerAngerPointMessage}, // 22
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerAngerPointPower},
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerAngerPointSpeed},

    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddAngerPoint(_DWORD *a1)
    {
        *a1 = 4;
        return AngerPointHandlers;
    }

    void HandlerThunderArmor(int a1, ServerFlow *a2, int a3)
    {
        if (CommonDamageRecoverCheck(a2, a3, TYPE_ELECTRIC))
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
        }
    }

    ABILITY_TRIGGERTABLE ThunderArmorHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerThunderArmor}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddInsomnia(_DWORD *a1)
    {
        *a1 = 1;
        return ThunderArmorHandlers;
    }

    void HandlerBulletproof(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Message *v9;
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (isInArray(BattleEventVar_GetValue(VAR_MOVE_ID), 0))
            {
                BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);

                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
                v9 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&v9->str, 2u, 1246);
                BattleHandler_AddArg(&v9->str, a3);
                BattleHandler_PopWork(a2, v9);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
        }
    }

    ABILITY_TRIGGERTABLE BulletproofHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerBulletproof}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddDamp(_DWORD *a1)
    {
        *a1 = 1;
        return BulletproofHandlers;
    }

    void HandlerWindRiderTailwind(int a1, ServerFlow *a2, int a3)
    {
        // HandlerParam_Message *v9;
        if ((BattleEventVar_GetValue(VAR_MON_ID) == a3 || MainModule_IsAllyMonID(a3, BattleEventVar_GetValue(VAR_MON_ID))) && BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE366_TAILWIND)
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
        }
        // if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
        // {
        //     if (isInArray(BattleEventVar_GetValue(VAR_MOVE_ID), 1))
        //     {
        //         BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
        //         CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
        //     }
        // }
    }

    void HandlerWindRider(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Message *v9;
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (isInArray(BattleEventVar_GetValue(VAR_MOVE_ID), 1))
            {
                BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
                CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
            }
        }
    }
    ABILITY_TRIGGERTABLE WindRiderHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerWindRider}, // 22
        {EVENT_MOVE_EXECUTE_END, (ABILITY_HANDLER_FUNC)HandlerWindRiderTailwind}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddKeenEye(_DWORD *a1)
    {
        *a1 = 2;
        return WindRiderHandlers;
    }

    //
    // Pixilate
    //
    void HandlerPixilateType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
            {
                BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_FAIRY);
            }
        }
    }
    void HandlerAtePower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (PML_MoveGetType(BattleEventVar_GetValue(VAR_MOVE_ID)) == TYPE_NORMAL) // physical
            {
                BattleEventVar_MulValue(VAR_RATIO, 4915); // 20% boost
            }
        }
    }

    ABILITY_TRIGGERTABLE PixilateHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerPixilateType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddAnticipation(_DWORD *a1)
    {
        *a1 = 2;
        return PixilateHandlers;
    }

    //
    // Aerilate
    //
    void HandlerAerilateType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
            {
                BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_FLYING);
            }
        }
    }

    ABILITY_TRIGGERTABLE AerilateHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerAerilateType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddStickyHold(_DWORD *a1)
    {
        *a1 = 2;
        return AerilateHandlers;
    }
    //
    // Refrigerate
    //
    void HandlerRefrigerateType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
            {
                BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_ICE);
            }
        }
    }
    ABILITY_TRIGGERTABLE RefrigerateHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerRefrigerateType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddEarlyBird(_DWORD *a1)
    {
        *a1 = 2;
        return RefrigerateHandlers;
    }

    //
    // Galvanize
    //
    void HandlerGalvanizeType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
            {
                BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_ELECTRIC);
            }
        }
    }
    ABILITY_TRIGGERTABLE GalvanizeHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerGalvanizeType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddOblivious(_DWORD *a1)
    {
        *a1 = 2;
        return GalvanizeHandlers;
    }

    void HandlerNormalizePower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (PML_MoveGetType(BattleEventVar_GetValue(VAR_MOVE_ID)) == TYPE_NORMAL) // physical
            {
                BattleEventVar_MulValue(VAR_RATIO, 5325); // 20% boost
            }
        }
    }

    ABILITY_TRIGGERTABLE NormalizeHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerNormalize},             // 22
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerScrappy}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerNormalizePower}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddNormalize(_DWORD *a1)
    {
        *a1 = 3;
        return NormalizeHandlers;
    }

    void THUMB_BRANCH_HandleTrace(int a1, ServerFlow *a2, unsigned int tracePokemonID, _DWORD *a4)
    {
        int tracePokemonSlot; // r5
        unsigned int Value;
        __int16 ExistFrontPokePos; // r0
        int opposingPokeSlot;      // r0
        int oppposingPokeID;       // r0
        u8 v9;                     // r7
        unsigned int i;
        unsigned int pokeCount;
        int traceAbilityId;
        int traceAbilityPokemonId;
        u8 opposingPokePos[5];
        BattleMon *traceVictim;          // r5
        BattleMon *traceUser;            // r0
        HandlerParam_ChangeAbility *v19; // r5
        _DWORD *v26;

        Value = BattleEventVar_GetValue(VAR_MON_ID);

        if (tracePokemonID == Value)
        {
            traceAbilityId = 0;
            traceAbilityPokemonId = 0;
            tracePokemonSlot = Handler_PokeIDToPokePos(a2, tracePokemonID);
            opposingPokeSlot = sub_219C508(Handler_GetBattleStyle(a2), tracePokemonSlot);
            oppposingPokeID = Handler_PokePosToPokeID(a2, opposingPokeSlot);
            v9 = oppposingPokeID;
            traceVictim = Handler_GetBattleMon(a2, oppposingPokeID);
            traceUser = Handler_GetBattleMon(a2, tracePokemonID);
            traceAbilityId = BattleMon_GetValue(traceVictim, VALUE_ABILITY);

            if (j_j_IsTraceFailAbility(traceAbilityId))
            {
                ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, (int)tracePokemonID);
                pokeCount = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, opposingPokePos);

                for (i = 0; i < pokeCount; (i + 1))
                {
                    if (opposingPokePos[i] != oppposingPokeID)
                    {
                        traceVictim = Handler_GetBattleMon(a2, opposingPokePos[i]);
                        traceAbilityId = BattleMon_GetValue(traceVictim, VALUE_ABILITY);
                        if (!j_j_IsTraceFailAbility(traceAbilityId))
                        {
                            traceAbilityPokemonId = BattleMon_GetID(traceVictim);
                            i = pokeCount;
                        }
                    }
                }
                if (!traceAbilityPokemonId)
                {
                    *a4 = 1;
                }
            }
            else
            {
                traceAbilityPokemonId = BattleMon_GetID(traceVictim);
            }
        }
        else if (!MainModule_IsAllyMonID(Value, tracePokemonID) && *a4 == 1)
        {
            traceAbilityId = 0;
            traceAbilityPokemonId = 0;
            tracePokemonSlot = Handler_PokeIDToPokePos(a2, Value);
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, (int)tracePokemonID);
            if (tracePokemonSlot != 6 && (Handler_GetBattleStyle(a2) != BTL_STYLE_TRIPLE || IsPosInRangeTripleBattle(ExistFrontPokePos, tracePokemonSlot)))
            {
                traceVictim = Handler_GetBattleMon(a2, Value);
                traceAbilityId = BattleMon_GetValue(traceVictim, VALUE_ABILITY);
                if (!j_j_IsTraceFailAbility(traceAbilityId))
                {
                    traceAbilityPokemonId = BattleMon_GetID(traceVictim);
                }
            }
        }

        if (traceAbilityPokemonId && traceAbilityId)
        {
            if ((int)tracePokemonID != 31)
            {
                v19 = (HandlerParam_ChangeAbility *)BattleHandler_PushWork(a2, EFFECT_CHANGEABILITY, (int)tracePokemonID);
                v19->pokeID = (int)tracePokemonID;
                v19->abilityID = traceAbilityId;
                v19->fSkipSwitchInEvent = 1;
                v19->header.flags |= 0x800000u;
                BattleHandler_StrSetup(&v19->exStr, 2u, 381);
                BattleHandler_AddArg(&v19->exStr, traceAbilityPokemonId);
                BattleHandler_AddArg(&v19->exStr, v19->abilityID);
                BattleHandler_PopWork(a2, v19);
            }
        }
    }

    int THUMB_BRANCH_SAFESTACK_HandlerShadowTag(int a1, ServerFlow *a2, unsigned int a3, int a4)
    {
        unsigned __int8 Value;     // r0
        int result;                // r0
        __int16 ExistFrontPokePos; // r0
        unsigned int NumTargets;   // r6
        unsigned int v10;          // r4
        BattleMon *BattleMon;      // r0
        u8 v12[5];                 // [sp+0h] [bp-18h] BYREF

        *v12 = a4;
        Value = BattleEventVar_GetValue(VAR_MON_ID);
        result = MainModule_IsAllyMonID(Value, a3);
        if (!result)
        {
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
            NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, v12);
            v10 = 0;
            if (NumTargets)
            {
                while (v10 < NumTargets)
                {
                    BattleMon = Handler_GetBattleMon(a2, v12[v10]);
                    if (BattleMon_GetValue(BattleMon, VALUE_EFFECTIVE_ABILITY) == ABIL023_SHADOW_TAG || BattleMon_HasType(BattleMon, TYPE_NORMAL) || BattleMon_HasType(BattleMon, TYPE_GHOST))
                    {
                        return result;
                    }
                    v10++;
                }
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
            else
            {
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
        return result;
    }

    void HandlerJustifiedDefense(int a1, int a2, int a3)
    {
        int Value; // r0

        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_TYPE);
            if (Value == TYPE_DARK)
            {
                BattleEventVar_MulValue(VAR_RATIO, 2048);
            }
        }
    }

    ABILITY_TRIGGERTABLE JustifiedHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ABILITY_HANDLER_FUNC)HandlerJustified}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerJustifiedDefense},  // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddJustified(_DWORD *a1)
    {
        *a1 = 2;
        return JustifiedHandlers;
    }

    int THUMB_BRANCH_SAFESTACK_ServerControl_MoveExecuteCheck1(ServerFlow *a1, BattleMon *a2, int a3, int a4)
    {
        MoveFailCause v7;                      // r6
        ActionIgnoreReason actionIgnoreReason; // r0
        int v9;                                // r1
        ConditionData MoveConditionData;       // r0
        int PreviousMove;                      // r0
        int ID;                                // r0
        int v15;                               // [sp+Ch] [bp-24h]
        MoveCondition Status;                  // [sp+10h] [bp-20h]

        v15 = 0;
        ServerControl_CheckMoveExeSleepCure(a1, a2);
        Status = BattleMon_GetStatus(a2);
        if (Status != CONDITION_SLEEP || (v7 = MOVEFAIL_SLEEP, ServerEvent_MoveExecuteFail(a1, a2, a3, 2)))
        {
            v15 = ServerControl_CheckMoveExeFreezeThaw(a1, a2, a3);
            Status = BattleMon_GetStatus(a2);
            if (Status == CONDITION_FREEZE && !v15)
            {
                v7 = MOVEFAIL_FREEZE;
                goto LABEL_50;
            }
            actionIgnoreReason = a1->actionIgnoreReason;
            if (actionIgnoreReason == REASON_OVERLEVELED)
            {
                v7 = MOVEFAIL_IGNORE;
                goto LABEL_50;
            }
            if (actionIgnoreReason == REASON_FALL_ASLEEP)
            {
                v7 = MOVEFAIL_IGNORE_FALL_ASLEEP;
                goto LABEL_50;
            }
            if (!a4)
            {
                v9 = Move_SearchIndex(a2, a3);
                if (v9 != 4 && !Move_GetPP(a2, v9))
                {
                    v7 = MOVEFAIL_PPZERO;
                    goto LABEL_50;
                }
            }
            v7 = (MoveFailCause)ServerEvent_CheckMoveExecute(a1, a2, a3, EVENT_MOVE_EXECUTE_CHECK1);
            if (v7 == MOVEFAIL_NULL)
            {
                // if (BattleMon_GetTurnFlag(a2, TURNFLAG_FOCUSPUNCHFAIL))
                // {
                //     v7 = MOVEFAIL_FOCUSPUNCHFAIL;
                //     goto LABEL_50;
                // }
                if (BattleMon_GetTurnFlag(a2, TURNFLAG_FLINCH))
                {
                    v7 = MOVEFAIL_FLINCH;
                    goto LABEL_50;
                }
                if (PersonalCheckIfMoveCondition(a2, CONDITION_DISABLEMOVE) && a3 != 165)
                {
                    MoveConditionData = BattleMon_GetMoveCondition(a2, CONDITION_DISABLEMOVE);
                    if (a3 == Condition_GetParam(MoveConditionData))
                    {
                        v7 = MOVEFAIL_DISABLE;
                        goto LABEL_50;
                    }
                }
                if (PersonalCheckIfMoveCondition(a2, CONDITION_HEALBLOCK) && getMoveFlag(a3, FLAG_HEALING))
                {
                    v7 = MOVEFAIL_HEALBLOCK;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_GRAVITY) && getMoveFlag(a3, FLAG_GROUNDED_BY_GRAVITY))
                {
                    v7 = MOVEFAIL_GRAVITY;
                    goto LABEL_50;
                }
                if (a3 == 165)
                {
                    goto LABEL_60;
                }
                if (PersonalCheckIfMoveCondition(a2, CONDITION_ENCORE) && (PreviousMove = BattleMon_GetPreviousMove(a2), PreviousMove != 165) && PreviousMove != a3 || PersonalCheckIfMoveCondition(a2, CONDITION_MOVELOCK) && a3 != BattleMon_GetPreviousMoveID(a2))
                {
                    v7 = MOVEFAIL_MOVELOCK;
                    goto LABEL_50;
                }
                if (PersonalCheckIfMoveCondition(a2, CONDITION_TAUNT) && !PML_MoveIsDamaging(a3))
                {
                    v7 = MOVEFAIL_TAUNT;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_IMPRISON) && BattleField_CheckImprison(a1->pokeCon, a2, a3))
                {
                    v7 = MOVEFAIL_IMPRISON;
                }
                else
                {
                LABEL_60:
                    if (ServerControl_CheckConfusionHit(a1, a2))
                    {
                        v7 = MOVEFAIL_CONFUSION;
                    }
                    else if (Status == CONDITION_PARALYSIS && BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) != 63 && RollEffectChance(0x19u))
                    {
                        v7 = MOVEFAIL_PARALYSIS;
                    }
                    else if (ServerControl_CheckAttract(a1, a2))
                    {
                        v7 = MOVEFAIL_ATTRACT;
                    }
                }
            }
        }
    LABEL_50:
        if (v7)
        {
            ServerControl_MoveExecuteFail(a1, a2, a3, v7);
            return 1;
        }
        else
        {
            if (Status == CONDITION_SLEEP)
            {
                ServerDisplay_MoveExecuteFailMessage(a1, (int)a2, a3, 2u);
                ServerDisplay_AddEffectAtPosition(a1, a2, 598);
            }
            else if (v15)
            {
                if (Status == CONDITION_FREEZE)
                {
                    ServerDisplay_CureStatus(a1, a2, 3, 0);
                    ID = BattleMon_GetID(a2);
                    ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 303, ID, a3, -65536);
                }
            }
            return 0;
        }
    }

    // int MyPosPoke_GetPokeExistPos(PosPoke *a1, int a2)
    // {
    //     unsigned int i;   // r4
    //     PosPokeState *v3; // r3

    //     for (i = 0; i < 6; ++i)
    //     {
    //         v3 = &a1->state[i];
    //         k::Printf("\nExistPokeID = %d", v3->existPokeID);
    //         if (v3->fEnable && a2 == v3->existPokeID)
    //         {
    //             return i;
    //         }
    //     }
    //     return 6;
    // }

    // bool MyPosPoke_IsExist(PosPoke *a1, int a2)
    // {
    //     return MyPosPoke_GetPokeExistPos(a1, a2) != 6;
    // }

    // int THUMB_BRANCH_SAFESTACK_BattleHandler_ChangeStatStage(ServerFlow *a1, HandlerParam_ChangeStatStage *a2, unsigned __int16 a3)
    // {
    //     int v5;               // r6
    //     BattleMon *v6;        // r7
    //     unsigned int i;       // r6
    //     BattleMon *v8;        // r7
    //     int v11;              // [sp+1Ch] [bp-24h]
    //     int v12;              // [sp+20h] [bp-20h]
    //     BattleMon *BattleMon; // [sp+24h] [bp-1Ch]

    //     BattleMon = PokeCon_GetBattleMon(a1->pokeCon, a2->header.flags << 19 >> 27);
    //     v12 = 0;
    //     v11 = 0;
    //     v5 = 0;
    //     k::Printf("\nCheck #1");
    //     if (a2->poke_cnt)
    //     {
    //         while (1)
    //         {
    //             if (j_j_PosPoke_IsExist_4(&a1->posPoke, a2->pokeID[v5]))
    //             {
    //                 v6 = PokeCon_GetBattleMon(a1->pokeCon, a2->pokeID[v5]);
    //                 if (!BattleMon_IsFainted(v6) && BattleMon_IsStatChangeValid(v6, a2->rankType, a2->rankVolume))
    //                 {
    //                     break;
    //                 }
    //             }
    //             if (++v5 >= a2->poke_cnt)
    //             {
    //                 goto LABEL_7;
    //             }
    //         }
    //         v12 = 1;
    //     }
    //     k::Printf("\nCheck #2");
    // LABEL_7:
    //     if (v12 && (a2->header.flags & 0x800000) != 0)
    //     {
    //         ServerDisplay_AbilityPopupAdd(a1, BattleMon);
    //     }
    //     if (a2->header.flags & 0x04000000 != 0)
    //     {
    //         BattleEventVar_SetConstValue(VAR_INTIMFLAG, 2);
    //     }
    //     if (a2->header.flags & 0x08000000 != 0)
    //     {
    //         BattleEventVar_SetConstValue(VAR_HOSTILEFLAG, 2);
    //     }
    //     k::Printf("\nCheck #3");
    //     for (i = 0; i < a2->poke_cnt; ++i)
    //     {
    //         k::Printf("\nCheck #4");
    //         k::Printf("\nWhat is the information we have access to?\nID is %d\nBattlemon species is %d\nOutput of function is %d\n",
    //         a2->pokeID[i],
    //         BattleMon_GetSpecies(Handler_GetBattleMon(a1, a2->pokeID[i])),
    //         MyPosPoke_GetPokeExistPos(&a1->posPoke, a2->pokeID[i])
    //         );
    //         if (j_j_PosPoke_IsExist_4(&a1->posPoke, a2->pokeID[i]))
    //         {
    //             k::Printf("\nCheck #5");
    //             v8 = PokeCon_GetBattleMon(a1->pokeCon, a2->pokeID[i]);
    //             if (!BattleMon_IsFainted(v8))
    //             {
    //                 k::Printf("\nCheck #6");
    //                 if (ServerControl_StatStageChangeCore(
    //                         a1,
    //                         a2->header.flags << 19 >> 27,
    //                         v8,
    //                         a2->rankType,
    //                         a2->rankVolume,
    //                         0x1Fu,
    //                         a3,
    //                         a2->pad,
    //                         a2->fMoveAnimation,
    //                         a2->pad2 == 0))
    //                 {
    //                     k::Printf("\nCheck #7");
    //                     BattleHandler_SetString(a1, &a2->exStr);
    //                     v11 = 1;
    //                 }
    //             }
    //         }
    //     }
    //     k::Printf("\nCheck #8");
    //     if (v12 && (a2->header.flags & 0x800000) != 0)
    //     {
    //         ServerDisplay_AbilityPopupRemove(a1, BattleMon);
    //     }
    //     return v11;
    // }

    void THUMB_BRANCH_BattleMon_TurnCheck(BattleMon *a1)
    {
        bool didMoveFail = BattleMon_GetTurnFlag(a1, TURNFLAG_MOVEFAILED);
        sys_memset(a1->TurnFlag, 0, 2u);
        if (a1->TurnCount < 9999u)
        {
            ++a1->TurnCount;
        }
        if (didMoveFail)
        {
            TurnFlag_Set(a1, TURNFLAG_MOVEFAILEDLASTTURN);
        }
        MoveDamageRec_ClearTurn(a1);
    }

    // void THUMB_BRANCH_ServerControl_MoveUseNotEffective(ServerFlow *a1, int a2, int a3)
    // {
    //     int v6; // r7

    //     // Added logic for effects that trigger on move failures to proc whenever any
    //     // individual target is unaffected.
    //     BattleMon *mon;
    //     mon = Handler_GetBattleMon(a1, a2);
    //     TurnFlag_Set(mon, TURNFLAG_MOVEFAILED);

    //     v6 = HEManager_PushState(&a1->HEManager);
    //     ServerEvent_MoveUseEnd_Common(a1, a2, a3, EVENT_MOVE_EXECUTE_NOEFFECT);
    //     HEManager_PopState(&a1->HEManager, v6);
    // }

    void THUMB_BRANCH_ServerEvent_CheckMoveExecuteFail(ServerFlow *a1, BattleMon *a2, int a3, int a4)
    {
        int ID; // r0
        TurnFlag_Set(a2, TURNFLAG_MOVEFAILED);

        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_MON_ID, ID);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, a3);
        BattleEventVar_SetConstValue(VAR_FAIL_CAUSE, a4);
        BattleEvent_CallHandlers(a1, EVENT_MOVE_EXECUTE_FAIL);
        BattleEventVar_Pop();
    }

    void THUMB_BRANCH_ServerFlow_CheckNoEffect_TypeEffectiveness(
        ServerFlow *a1,
        MoveParam *a2,
        BattleMon *attacker,
        PokeSet *targets,
        EffectivenessRecorder *effrec)
    {
        BattleMon *i;     // r5
        int v8;           // r7
        int ID;           // r0
        int v10;          // r0
        unsigned int v11; // r5

        EffectivenessRecorder_Init(effrec);
        j_j_PokeSet_SeekStart_7(targets);
        for (i = j_PokeSet_SeekNext_29(targets); i; i = j_PokeSet_SeekNext_28(targets))
        {
            v8 = ServerEvent_CheckMoveDamageEffectiveness(a1, attacker, i, a2, 1);
            ID = BattleMon_GetID(i);
            EffectivenessRecorder_Add(effrec, ID, v8);
            if (!v8)
            {
                // TurnFlag Added Here
                if (!MainModule_IsAllyMonID(i->ID, attacker->ID))
                {
                    TurnFlag_Set(attacker, TURNFLAG_MOVEFAILED);
                }

                j_PokeSet_Remove_8(targets, i);
                EffectivenessCounter_CountUp(&a1->effectivenessCounter, a1, attacker, i, 0);
                v10 = BattleMon_GetID(attacker);
                v11 = j_MainModule_PokeIDToClientID(v10);
                if (v11 == MainModule_GetPlayerClientID(a1->mainModule))
                {
                    RecordData_Increment(a1->mainModule, 75);
                }
            }
        }
    };

    void THUMB_BRANCH_ServerFlow_CheckNoEffect_Avoid(ServerFlow *a1, unsigned __int16 *a2, BattleMon *a3, PokeSet *a4)
    {
        BattleMon *i; // r4

        if (j_PokeSet_GetCountMax_4(a4) != 1 || j_PokeSet_Get_8(a4, 0) != a3)
        {
            j_PokeSet_SeekStart_20(a4);
            for (i = j_PokeSet_SeekNext_41(a4); i; i = j_PokeSet_SeekNext_40(a4))
            {
                if (!ServerEvent_SkipAvoidCheck(a1, a3, i, a2) && !ServerEvent_CheckHit(a1, a3, i, a2))
                {
                    if (!MainModule_IsAllyMonID(i->ID, a3->ID))
                    {
                        TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                    }

                    j_PokeSet_Remove_10(a4, i);
                    ServerDisplay_MoveAvoid(a1, i);
                }
            }
        }
    };

    void THUMB_BRANCH_ServerFlow_CheckNoEffect_Hiding(ServerFlow *a1, unsigned __int16 *a2, BattleMon *a3, PokeSet *a4)
    {
        BattleMon *i; // r4

        j_j_PokeSet_SeekStart_19(a4);
        for (i = j_j_PokeSet_SeekNext_38(a4); i; i = j_j_PokeSet_SeekNext_39(a4))
        {
            if (!ServerControl_IsGuaranteedHit(a1, a3, i))
            {
                if (ServerEvent_CheckHiding(a1, a3, i))
                {
                    if (!MainModule_IsAllyMonID(i->ID, a3->ID))
                    {
                        TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                    }
                    j_j_PokeSet_Remove_9(a4, i);
                    ServerDisplay_MoveAvoid(a1, i);
                }
            }
        }
    };

    void THUMB_BRANCH_flowsub_CheckNoEffect_Protect(ServerFlow *a1, unsigned __int16 *a2, BattleMon *a3, PokeSet *a4, int a5)
    {
        BattleMon *i; // r7
        BattleMon *j; // r7
        BattleMon *k; // r7
        int ID;       // r0
        BattleMon *m; // r7

        j_PokeSet_SeekStart_10(a4);
        for (i = j_PokeSet_SeekNext_18(a4); i; i = j_PokeSet_SeekNext_19(a4))
        {
            if (!ServerControl_IsGuaranteedHit(a1, a3, i) && ServerControl_CheckNoEffectCore(a1, a2, (int)a3, i, a5, 43))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(i->ID, a3->ID))
                {
                    TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                }
                j_PokeSet_Remove_0(a4, i);
            }
        }
        j_PokeSet_SeekStart_11(a4);
        for (j = j_PokeSet_SeekNext_20(a4); j; j = j_PokeSet_SeekNext_21(a4))
        {
            if (ServerControl_CheckNoEffectCore(a1, a2, (int)a3, j, a5, 44))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(i->ID, a3->ID))
                {
                    TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                }
                j_PokeSet_Remove_1(a4, j);
            }
        }
        if (getMoveFlag(*a2, FLAG_BLOCKED_BY_PROTECT))
        {
            j_PokeSet_SeekStart_12(a4);
            for (k = j_PokeSet_SeekNext_22(a4); k; k = j_PokeSet_SeekNext_23(a4))
            {
                if (BattleMon_GetTurnFlag(k, TURNFLAG_PROTECT) && !ServerEvent_CheckProtectBreak(a1, a3))
                {
                    // Add TurnFlag modification for the Attacking Pokemon here
                    if (!MainModule_IsAllyMonID(i->ID, a3->ID))
                    {
                        TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                    }
                    j_PokeSet_Remove_2(a4, k);
                    ID = BattleMon_GetID(k);
                    ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 523, ID, -65536);

                    if (BattleMon_GetPreviousMoveID(k) == MOVE376_SPIKY_SHIELD && getMoveFlag(*a2, FLAG_CONTACT))
                    {
                        if (!overrideContact(k, (MoveID)*a2))
                        {
                            HandlerParam_Damage *v7 = (HandlerParam_Damage *)BattleHandler_PushWork(a1, EFFECT_DAMAGE, a3->ID);
                            v7->pokeID = a3->ID;
                            v7->damage = DivideMaxHPZeroCheck(a3, 8u);
                            BattleHandler_StrSetup(&v7->exStr, 2u, 1189);
                            BattleHandler_AddArg(&v7->exStr, v7->pokeID);
                            BattleHandler_PopWork(a1, v7);
                        }
                    }

                    if (BattleMon_GetPreviousMoveID(k) == MOVE462_SILK_TRAP && getMoveFlag(*a2, FLAG_CONTACT))
                    {
                        if (!overrideContact(k, (MoveID)*a2))
                        {
                            HandlerParam_ChangeStatStage *v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a1, EFFECT_CHANGESTATSTAGE, a3->ID);
                            v8->pokeID[0] = a3->ID;
                            v8->poke_cnt = 1;
                            v8->fMoveAnimation = 1;
                            v8->rankType = STATSTAGE_SPEED;
                            v8->rankVolume = -1;
                            BattleHandler_StrSetup(&v8->exStr, 2u, 1264);
                            BattleHandler_AddArg(&v8->exStr, v8->pokeID[0]);
                            BattleHandler_PopWork(a1, v8);
                        }
                    }
                }
            }
        }

        j_PokeSet_SeekStart_13(a4);
        for (m = j_PokeSet_SeekNext_24(a4); m; m = j_PokeSet_SeekNext_25(a4))
        {
            if (ServerControl_CheckNoEffectCore(a1, a2, (int)a3, m, a5, 45))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(i->ID, a3->ID))
                {
                    TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                }
                j_PokeSet_Remove_3(a4, m);
            }
        }
    }
}