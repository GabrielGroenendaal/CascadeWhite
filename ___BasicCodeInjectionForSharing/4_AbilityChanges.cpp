#include "codeinjection_new.h"
#include "kPrint.h"

extern "C"
{

    bool PersonalCheckIfMoveCondition(BattleMon *a1, MoveCondition a2)
    {
        if (a1->HeldItem == 289 && a2 == CONDITION_TAUNT)
        {
            return true;
        }
        else if (a2 == CONDITION_BLOCK && ((a1->Conditions[CONDITION_CURSE] & 7) != 0))
        {
            return true;
        }
        else
        {
            return (a1->Conditions[a2] & 7) != 0;
        }
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
                a1 == 290 ||
                a1 == 43 ||
                (a1 >= 545 && a1 <= 564) ||
                a1 == 292 ||
                a1 == 291 ||
                a1 == 274 ||
                a1 == 542 ||
                a1 == 294 ||
                a1 == 543 ||
                a1 == 275 ||
                a1 == 219 ||
                a1 == 214 ||
                a1 == 271 ||
                a1 == 541);
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

    // // For Fluffy
    void HandlerFluffy(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r0
        int isFire;
        int ratio;

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);

            isFire = (PML_MoveGetType(Value) == TYPE_FIRE) ? 2 : 1;
            ratio = (getMoveFlag(Value, FLAG_CONTACT)) ? 2048 : 4096;

            // k::Printf("\n\n isFire is %d\nratio is %d\nisFire times Ratio is %d\n\n", isFire, ratio, isFire * ratio);

            BattleEventVar_MulValue(VAR_RATIO, isFire * ratio);
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
        BattleMon *attackingMon;  // r4
        unsigned __int8 Value; // r0
        BattleMon *defendingMon;         // r5
        int v8;                // r4
        int v9;                // r0

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon(a2, a3);
            defendingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_DEFENDING_MON));
            v8 = BattleMon_GetPokeType(attackingMon);
            v9 = BattleMon_GetPokeType(defendingMon);

            if (PokeTypePair_HasSharedType(v8, v9)){
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5448);
            }
            
        }
    }

     void RivalryDefense(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *attackingMon;  // r4
        unsigned __int8 Value; // r0
        BattleMon *defendingMon;         // r5
        int v8;                // r4
        int v9;                // r0

        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            defendingMon = Handler_GetBattleMon(a2, a3);
            attackingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
            v8 = BattleMon_GetPokeType(attackingMon);
            v9 = BattleMon_GetPokeType(defendingMon);

            if (PokeTypePair_HasSharedType(v8, v9)){
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2730);
            }
            
        }
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
        {EVENT_TURN_CHECK_BEGIN, (ABILITY_HANDLER_FUNC)HandlerHealer},           // 4
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

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRivalry(_DWORD *a1)
    {
        *a1 = 2;
        return RivalryHandlers;
    }

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
                if (BattleMon_GetTurnFlag(a2, TURNFLAG_FOCUSPUNCHFAIL))
                {
                    v7 = MOVEFAIL_FOCUSPUNCHFAIL;
                    goto LABEL_50;
                }
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
                    else if (Status == CONDITION_PARALYSIS && a2->Ability != 63 && RollEffectChance(0x19u))
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
}