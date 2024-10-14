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

    bool checkForPaybackBoost(ServerFlow *a1, BattleMon *AttackingMon, BattleMon *DefendingMon)
    {
        int *ActionOrderAttackingMon;
        int *ActionOrderDefendingMon;

        if (BattleMon_GetTurnFlag(DefendingMon, TURNFLAG_ACTIONDONE))
        {
            return true;
        }
        // return false;

        // k::Printf("\n\nDid we get this far?\n", ActionOrderAttackingMon);
        ActionOrderAttackingMon = ActionOrder_SearchByMonID(a1, AttackingMon->ID);
        ActionOrderDefendingMon = ActionOrder_SearchByMonID(a1, DefendingMon->ID);
        // k::Printf("The action order for the attacking mon is %d\n", ActionOrderAttackingMon);
        // k::Printf("The action order for the defending mon is %d\n\n", ActionOrderDefendingMon);
        if (ActionOrderAttackingMon > ActionOrderDefendingMon)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int THUMB_BRANCH_HandlerPayback(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        int result2;
        unsigned __int8 Value;   // r0
        BattleMon *DefendingMon; // r0
        BattleMon *AttackingMon;
        bool paybackBoost;

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            DefendingMon = Handler_GetBattleMon(a2, Value);
            AttackingMon = Handler_GetBattleMon(a2, result);

            paybackBoost = checkForPaybackBoost(a2, AttackingMon, DefendingMon);

            if (paybackBoost)
            {
                k::Printf("\n\nWe got the payback boost babyyyyy!\n\n");
                return HandlerCommon_MultiplyBasePower(2);
            }
        }
        return result;
    }

    void THUMB_BRANCH_HandlerSkullBash(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 556);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_DEFENSE;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerMeteorBeam(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 863);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    // // void HandlerSkyAttack
    void HandlerSkyAttack(int a1, ServerFlow *a2, unsigned int *a3)
    {
        // k::Printf("\nAre we inside?\n");
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 550);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    int HandlerElectroShotRain(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            result = Handler_GetWeather(a2);
            if (result == 2)
            {
                return BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
            }
        }
        return result;
    }

    // // void HandlerElectroShot
    void HandlerElectroShotCharge(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 866);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    // // void HandlerIngrain

    int NewHandlerSkyUppercut(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        // int PokeType;
        // int v6;               // r6
        // BattleMon *PokeParam; // r7
        // int resultdata;

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            // v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_DEFENDING_MON);
            // PokeParam = Handler_GetPokeParam(a2, v6);
            // PokeType = BattleMon_GetPokeType(PokeParam);
            // // k::Printf("\n4. Result is Type Effectiveness is %d\n", result);
            // result = GetTypeEffectivenesssVsMonAltered(TYPE_FIGHTING, PokeType);
            // k::Printf("\nFinal Type Effectiveness is %d\n\n", result);
            // BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, result);
            // result = BattleEventVar_RewriteValue(VAR_TYPEEFFECTIVENESS, result);
            // k::Printf("\nReturn value is %d\n\n", result);
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 3);
        }
        return result;
    }

    int HandlerFreezeDry(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        int PokeType;
        int v6;               // r6
        BattleMon *PokeParam; // r7

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            // v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_DEFENDING_MON);
            // PokeParam = Handler_GetPokeParam(a2, v6);
            // PokeType = BattleMon_GetPokeType(PokeParam);
            // result = GetTypeEffectivenesssVsMonAltered(TYPE_ICE, PokeType);
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 2);
        }
        return result;
    }

    int HandlerSwallowCheckFail(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0
        int HeldItem;         // r0

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            HeldItem = BattleMon_GetHeldItem(PokeParam);
            if (!HeldItem)
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            }
            if (!PML_ItemIsBerry(HeldItem))
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            }
            if (!Handler_CheckItemUsable(a2, a3))
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            }
        }
        return result;
    }

    int HandlerSwallowHeal(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0
        int Count;            // r0
        int v8;               // r1

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);

            if (PML_ItemIsBerry(PokeParam->HeldItem))
            {
                return BattleEventVar_RewriteValue(VAR_RATIO, 3072);
            }
            // return BattleEventVar_RewriteValue(VAR_RATIO, 1024);
        }
        return result;
    }

    MoveID NEW_PROTECT_COUNTER_MOVES[6] = {
        MOVE203_ENDURE, MOVE182_PROTECT, MOVE197_DETECT, MOVE469_WIDE_GUARD, MOVE501_QUICK_GUARD, MOVE376_TRUMP_CARD};

    void THUMB_BRANCH_HandlerProtectStart(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *BattleMon;        // r0
        int PreviousMoveID;          // r0
        int v7;                      // r3
        HandlerParam_SetCounter *v8; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon = Handler_GetBattleMon(a2, (int)a3);
            PreviousMoveID = BattleMon_GetPreviousMoveID(BattleMon);
            v7 = 0;
            while (PreviousMoveID != NEW_PROTECT_COUNTER_MOVES[v7])
            {
                if (++v7 >= 6)
                {
                    v8 = (HandlerParam_SetCounter *)BattleHandler_PushWork(a2, EFFECT_COUNTER, (int)a3);
                    v8->pokeID = (int)a3;
                    v8->counterID = COUNTER_PROTECT;
                    v8->value = 0;
                    BattleHandler_PopWork(a2, v8);
                    return;
                }
            }
        }
    }

    int THUMB_BRANCH_HandlerElectroBall(int a1, ServerFlow *a2, int a3)
    {
        int result;            // r0
        BattleMon *PokeParam;  // r5
        unsigned __int8 Value; // r0
        BattleMon *v8;         // r6
        int v9;                // r5
        int v10;               // r0
        int v11;               // r1

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            v8 = Handler_GetBattleMon(a2, Value);
            v9 = Handler_CalculateSpeed(a2, PokeParam, 0);
            v10 = Handler_CalculateSpeed(a2, v8, 0);
            if (v9 > v10)
            {
                v11 = 110;
            }
            else
            {
                v11 = 55;
            }
            return BattleEventVar_RewriteValue(VAR_MOVE_POWER, v11);
        }
        return result;
    }

    int THUMB_BRANCH_HandlerGyroBall(int a1, ServerFlow *a2, int a3)
    {
        int result;            // r0
        BattleMon *PokeParam;  // r5
        unsigned __int8 Value; // r0
        BattleMon *v8;         // r6
        int v9;                // r5
        int v10;               // r0
        int v11;               // r1

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            v8 = Handler_GetBattleMon(a2, Value);
            v9 = Handler_CalculateSpeed(a2, PokeParam, 0);
            v10 = Handler_CalculateSpeed(a2, v8, 0);
            if (v9 < v10)
            {
                v11 = 110;
            }
            else
            {
                v11 = 55;
            }
            return BattleEventVar_RewriteValue(VAR_MOVE_POWER, v11);
        }
        return result;
    }

    int THUMB_BRANCH_HandlerSleepTalk(int r0_0, ServerFlow *r1_0, int a3, int *a4)
    {
        int result;             // r0
        unsigned int v6;        // r5
        unsigned int i;         // r6
        int ID;                 // r4
        unsigned int v9;        // r1
        int v10;                // r5
        int v11;                // r4
        unsigned int MoveCount; // [sp+8h] [bp-20h]
        BattleMon *PokeParam;   // [sp+Ch] [bp-1Ch]

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(r1_0, a3);
            // result = BattleMon_CheckIfMoveCondition(PokeParam, CONDITION_SLEEP);
            // if (result)
            // {
            MoveCount = BattleMon_GetMoveCount(PokeParam);
            v6 = 0;
            for (i = 0; v6 < MoveCount; v6 = (v6 + 1))
            {
                ID = Move_GetID(PokeParam, v6);
                if (!j_j_IsSleepTalkUncallableMove(ID) && ID != 156 && !getMoveFlag(ID, FLAG_REQUIRES_CHARGE))
                {
                    v9 = i;
                    i = (i + 1);
                    a4[v9] = ID;
                }
            }
            if (i)
            {
                v10 = *(a4 + ((4 * BattleRandom(i)) & 0x3FF));
                v11 = Handler_ReqMoveTargetAuto(r1_0, a3, v10);
                BattleEventVar_RewriteValue(VAR_MOVE_ID, v10);
                return BattleEventVar_RewriteValue(VAR_POKE_POS, v11);
            }
            else
            {
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
            //}
        }
        return result;
    }

    void HandlerSwallowEnd(int a1, ServerFlow *a2, int a3, int *a4)
    {
        BattleMon *PokeParam;     // r0
        HandlerParam_Header *v8;  // r0
        HandlerParam_Message *v7; // r4
        HandlerParam_ActivateItem *v9;

        u16 HeldItem;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && !*a4)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            HeldItem = BattleMon_GetHeldItem(PokeParam);

            if (PML_ItemIsBerry(HeldItem))
            {
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&v7->str, 2u, 1159);
                BattleHandler_AddArg(&v7->str, a3);
                BattleHandler_AddArg(&v7->str, HeldItem);
                BattleHandler_PopWork(a2, v7);

                v9 = (HandlerParam_ActivateItem *)BattleHandler_PushWork(a2, EFFECT_ACTIVATEITEM, a3);
                v9->header.flags |= 0x1000000u;
                v9->itemID = (int)HeldItem;
                v9->pokeID = a3;
                BattleHandler_PopWork(a2, v9);

                v8 = (HandlerParam_Header *)BattleHandler_PushWork(a2, EFFECT_CONSUMEITEM, a3);
                v8[1].flags = 1;
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    void HandlerTeleportEffect(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Message *v5; // r5
        HandlerParam_Switch *v7;  // r0

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && Handler_GetFightEnableBenchPokeNum(a2, a3))
        {
            if (Handler_CheckReservedMemberChangeAction(a2))
            {
                v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&v5->str, 2u, 767);
                BattleHandler_AddArg(&v5->str, a3);
                BattleHandler_PopWork(a2, v5);
                v7 = (HandlerParam_Switch *)BattleHandler_PushWork(a2, EFFECT_SWITCH, a3);
                v7->pokeID = a3;
                v7->fIntrDisable = 1;
                BattleHandler_PopWork(a2, v7);
            }
        }
    }

    void HandlerSolarBeamPowerNew(int a1, int a2, int a3)
    {
        BattleMon *attackingMon;
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon((ServerFlow *)a2, a3);

            if (attackingMon->Ability != 34 && attackingMon->Ability != 94 && attackingMon->Ability != 122 && (Handler_GetWeather(a2) - 2) <= 2u)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
            }
        }
    }

    int HandlerSolarBeamSunCheckNew(int a1, int a2, int a3)
    {
        int result; // r0
        BattleMon *attackingMon;

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon((ServerFlow *)a2, a3);

            if (Handler_GetWeather(a2) == 1 || attackingMon->Ability == 34 || attackingMon->Ability == 94 || attackingMon->Ability == 122)
            {
                return BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
            }
        }
        return result;
    }

    int HandlerGrowthNew(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r1
        BattleMon *attackingMon;

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon((ServerFlow *)a2, a3);
            result = Handler_GetWeather(a2);
            if (result == 1 || attackingMon->Ability == 34 || attackingMon->Ability == 94 || attackingMon->Ability == 122)
            {
                Value = BattleEventVar_GetValue(VAR_VOLUME);
                if (Value == 1)
                {
                    Value = 2;
                }
                return BattleEventVar_RewriteValue(VAR_VOLUME, Value);
            }
        }
        return result;
    }

    int HandlerSynthesis(int a1, int a2, int a3)
    {
        int result;           // r0
        unsigned int Weather; // r0
        int v7;               // r1
        BattleMon *attackingMon;

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            attackingMon = Handler_GetBattleMon((ServerFlow *)a2, a3);
            Weather = Handler_GetWeather(a2);

            if (Weather == 1 || attackingMon->Ability == 34 || attackingMon->Ability == 94 || attackingMon->Ability == 122)
            {
                v7 = 2732;
            }
            else if (Weather == 2 || Weather == 3 || Weather == 4)
            {
                v7 = 1024;
            }
            else
            {
                v7 = 2048;
            }
            return BattleEventVar_RewriteValue(VAR_RATIO, v7);
        }
        return result;
    }

    void HandlerStickyWeb(int a1, ServerFlow *a2, unsigned int a3, int a4)
    {
        ConditionData Permanent;    // r4
        bool SideFromOpposingMonID; // r0

        SideFromOpposingMonID = GetSideFromOpposingMonID(a3);
        CommonCreateSideEffect(a1, a2, a3, a4, SideFromOpposingMonID, 14, 1, 209);
    }

    typedef struct
    {
        BattleEventType triggerValue;
        MOVE_HANDLER_FUNC function;
    } MOVE_TRIGGERTABLE;

    MOVE_TRIGGERTABLE MeteorBeamHandlers[] = {
        {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerMeteorBeam},
    };

    MOVE_TRIGGERTABLE SkyUppercutHandlers[] = {
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (MOVE_HANDLER_FUNC)NewHandlerSkyUppercut}};

    MOVE_TRIGGERTABLE FreezeDryHandlers[] = {
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (MOVE_HANDLER_FUNC)HandlerFreezeDry},
    };

    MOVE_TRIGGERTABLE ElectroShotHandlers[] = {
        {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerElectroShotRain},
        {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerElectroShotCharge},
    };

    MOVE_TRIGGERTABLE SkyAttackHandlers[] = {
        {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerSkyAttack},
    };

    MOVE_TRIGGERTABLE SwallowHandlers[] = {
        {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
        {EVENT_RECOVER_HP, (MOVE_HANDLER_FUNC)HandlerSwallowHeal},
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
    };

    MOVE_TRIGGERTABLE StockpileHandlers[] = {
        {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
    };

    MOVE_TRIGGERTABLE SpitUpHandlers[] = {
        {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
    };

    MOVE_TRIGGERTABLE TeleportHandlers[] = {
        {EVENT_UNCATEGORIZED_MOVE, (MOVE_HANDLER_FUNC)HandlerTeleportEffect},
    };

    MOVE_TRIGGERTABLE PartingShotHandlers[] = {
        {EVENT_DAMAGE_PROCESSING_END_HIT_3, (MOVE_HANDLER_FUNC)HandlerUturn},
    };

    MOVE_TRIGGERTABLE SolarBeamHandlers[] = {
        {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerSolarBeamSunCheckNew},
        {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerSolarBeamCharge},
        {EVENT_MOVE_POWER, (MOVE_HANDLER_FUNC)HandlerSolarBeamPowerNew}};

    MOVE_TRIGGERTABLE SynthesisHandlers[] = {
        {EVENT_RECOVER_HP, (MOVE_HANDLER_FUNC)HandlerSynthesis},
    };

    MOVE_TRIGGERTABLE GrowthHandlers[] = {
        {EVENT_GET_STAT_STAGE_CHANGE_VALUE, (MOVE_HANDLER_FUNC)HandlerGrowthNew},
    };

    MOVE_TRIGGERTABLE StickyWebHandlers[] = {
        {EVENT_UNCATEGORIZED_MOVE_NO_TARGET, (MOVE_HANDLER_FUNC)HandlerStickyWeb},
    };

    MOVE_TRIGGERTABLE SpikyShieldHandlers[] = {
        {EVENT_MOVE_SEQUENCE_START, (MOVE_HANDLER_FUNC)HandlerProtectStart},
        {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerProtectCheckFail},
        {EVENT_MOVE_EXECUTE_FAIL, (MOVE_HANDLER_FUNC)HandlerProtectResetCounter},
        {EVENT_UNCATEGORIZED_MOVE, (MOVE_HANDLER_FUNC)HandlerProtect},

    };

    // Spiky Shield
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddTrumpCard(_DWORD *a1)
    {
        *a1 = 4;
        return SpikyShieldHandlers;
    }


    // Sticky Web
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddMagnitude(_DWORD *a1)
    {
        *a1 = 1;
        return StickyWebHandlers;
    }
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSolarBeam(_DWORD *a1)
    {
        *a1 = 3;
        return SolarBeamHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSynthesis(_DWORD *a1)
    {
        *a1 = 1;
        return SynthesisHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddGrowth(_DWORD *a1)
    {
        *a1 = 1;
        return GrowthHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddFreezeShock(_DWORD *a1)
    {
        *a1 = 1;
        return MeteorBeamHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSkyUppercut(_DWORD *a1)
    {
        *a1 = 1;
        return SkyUppercutHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddMiracleEye(_DWORD *a1)
    {
        *a1 = 1;
        return FreezeDryHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddForesight(_DWORD *a1)
    {
        *a1 = 2;
        return ElectroShotHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSwallow(_DWORD *a1)
    {
        *a1 = 3;
        return SwallowHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSpitup(_DWORD *a1)
    {
        *a1 = 3;
        return SpitUpHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddStockpile(_DWORD *a1)
    {
        *a1 = 3;
        return StockpileHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSkyAttack(_DWORD *a1)
    {
        *a1 = 1;
        return SkyAttackHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddTeleport(_DWORD *a1)
    {
        *a1 = 1;
        return TeleportHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddLockOn(_DWORD *a1)
    {
        *a1 = 1;
        return PartingShotHandlers;
    }

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
                j_PokeSet_Remove_0(a4, i);
            }
        }
        j_PokeSet_SeekStart_11(a4);
        for (j = j_PokeSet_SeekNext_20(a4); j; j = j_PokeSet_SeekNext_21(a4))
        {
            if (ServerControl_CheckNoEffectCore(a1, a2, (int)a3, j, a5, 44))
            {
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
                    j_PokeSet_Remove_2(a4, k);
                    ID = BattleMon_GetID(k);
                    ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 523, ID, -65536);

                    if (BattleMon_GetPreviousMoveID(k) == MOVE376_TRUMP_CARD && getMoveFlag(*a2, FLAG_CONTACT))
                    {
                        HandlerParam_Damage* v7 = (HandlerParam_Damage *) BattleHandler_PushWork(a1, EFFECT_DAMAGE, a3->ID);
                        v7->pokeID = a3->ID;
                        v7->damage = DivideMaxHPZeroCheck(a3, 8u);
                        BattleHandler_StrSetup(&v7->exStr, 2u, 1189);
                        BattleHandler_AddArg(&v7->exStr, v7->pokeID);
                        BattleHandler_PopWork(a1, v7);
                    }
                }
            }
        }

        j_PokeSet_SeekStart_13(a4);
        for (m = j_PokeSet_SeekNext_24(a4); m; m = j_PokeSet_SeekNext_25(a4))
        {
            if (ServerControl_CheckNoEffectCore(a1, a2, (int)a3, m, a5, 45))
            {

                j_PokeSet_Remove_3(a4, m);
            }
        }
    }

    // MOVE_TRIGGERTABLE MoveTriggerTable[] =
    //     {
    //         {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerMeteorBeam},
    //         {EVENT_CHECK_TYPE_EFFECTIVENESS, (MOVE_HANDLER_FUNC)NewHandlerSkyUppercut}, // BattleEvent_CheckTypeEffectiveness
    //         {EVENT_CHECK_TYPE_EFFECTIVENESS, (MOVE_HANDLER_FUNC)HandlerFreezeDry},
    //         {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerElectroShotRain},
    //         {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerElectroShotCharge},
    //         {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerSkyAttack},

    //         {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
    //         {EVENT_RECOVER_HP, (MOVE_HANDLER_FUNC)HandlerSwallowHeal},
    //         {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},

    //         {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
    //         {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
    //         {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},

    //         {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerSkyAttack},

    //         {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
    //         {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
    //         {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},

    //         {EVENT_UNCATEGORIZED_MOVE, (MOVE_HANDLER_FUNC)HandlerTeleportEffect},
    //         //{0x78, (MOVE_HANDLER_FUNC)HandlerUturn},
    //         {EVENT_DAMAGE_PROCESSING_END_HIT_3, (MOVE_HANDLER_FUNC)HandlerUturn},
    //         //{0x27, (MOVE_HANDLER_FUNC)HandlerUturn}

    // };

    // // Meteor Beam
    // int *THUMB_BRANCH_EventAddFreezeShock(unsigned int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[0].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddSkyUppercut(unsigned int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[1].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddMiracleEye(unsigned int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[2].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddForesight(unsigned int *a1)
    // {
    //     *a1 = 2;
    //     return (int *)&MoveTriggerTable[3].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddSwallow(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable[6].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddSpitUp(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable[13].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddSkyAttack(unsigned int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[12].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddStockpile(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable[13].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddTeleport(unsigned int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[16].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddLockOn(unsigned int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[17].triggerValue;
    // }

    // void EndOfCharge()
    // {
    // }

    // int checkState(BattleMon *PokeParam)
    // {
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_SHADOWFORCE))
    //     {
    //         return 1;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_FLY))
    //     {
    //         return 2;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_DIG))
    //     {
    //         return 3;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_DIVE))
    //     {
    //         return 4;
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }

    // int checkScript(int a1)
    // {
    //     if (a1 == 1)
    //     {
    //         return 1168;
    //     }
    //     if (a1 == 2)
    //     {
    //         return 1171;
    //     }
    //     if (a1 == 3)
    //     {
    //         return 1165;
    //     }
    //     if (a1 == 4)
    //     {
    //         return 1177;
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }

    // int HandlerPursuitStartCharge(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     int result;         // r0
    //     unsigned int Value; // r6
    //     int v8[6];          // [sp+0h] [bp-18h] BYREF
    //     int moveID;
    //     int state;
    //     BattleMon *PokeParam;
    //     HandlerParam_Message *v5; // r6

    //     PokeParam = Handler_GetPokeParam(a2, a3);
    //     k::Printf("\nLayer One: We are inside the function did we get this far?\n");
    //     if (checkState(PokeParam))
    //     {
    //         v8[1] = a4;
    //         result = Handler_GetThisTurnAction(a2, a3, v8);
    //         k::Printf("\nLayer Two: We are inside the function did we get this far?\n");
    //         if (result)
    //         {
    //             Value = BattleEventVar_GetValue(VAR_TARGETMONID);
    //             result = MainModule_IsAllyMonID(Value, a3);
    //             if (!result)
    //             {
    //                 k::Printf("\nLayer Three: We are inside the function did we get this far?\n");
    //                 Handler_PokeIDToPokePos(a2, Value);
    //                 Handler_PokeIDToPokePos(a2, a3);
    //                 result = Handler_IsTargetInRange(a2, a3, Value, 0);
    //                 if (!result)
    //                 {
    //                     k::Printf("\nWe are inside the function did we get this far?\n");
    //                     v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //                     BattleHandler_StrSetup(&v5->str, 2u, checkScript(checkState(PokeParam)));
    //                     BattleHandler_AddArg(&v5->str, (int)a3);
    //                     BattleHandler_PopWork(a2, v5);

    //                     return Handler_AddSwitchOutInterrupt((int)&a2, a3);
    //                 }
    //             }
    //         }
    //     }
    //     return result;
    // }

    // void SwitchOutInterruptDig(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1165);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptShadowForce(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1168);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptFly(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1171);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptBounce(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1174);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptDive(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup(&v5->str, 2u, 1177);
    //         BattleHandler_AddArg(&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // MOVE_TRIGGERTABLE MoveTriggerTable2[] =
    //     {
    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerDig},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerShadowForce},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},
    //         {0x2E, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
    //         {0x81, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
    //         {0x84, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerFly},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerBounce},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerDive},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    // };

    // int *THUMB_BRANCH_EventAddDig(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[0].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddShadowForce(unsigned int *a1)
    // {
    //     *a1 = 6;
    //     return (int *)&MoveTriggerTable2[3].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddFly(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[9].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddBounce(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[12].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddDive(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[15].triggerValue;
    // }
}