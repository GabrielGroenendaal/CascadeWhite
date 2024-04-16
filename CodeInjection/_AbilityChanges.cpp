#include "swan-master/codeinjection.h"
#include "NitoKernel/include/kPrint.h"

extern "C"
{

    unsigned int *HandlerOvercoatPowders(int a1, ServerFlow *a2, unsigned int *a3)
    {
        char *v7; // r0
        int moveId;
        unsigned int *result;
        moveId = BattleEventVar_GetValue(VAR_MOVEID);

        if (moveId == 79 || moveId == 147 || moveId == 76 || moveId == 77 || moveId == 139)
        {
            result = (unsigned int *)BattleEventVar_RewriteValue(VAR_NOEFFECTFLAG, 1);
            if (result)
            {
                BattleHandler_PushRun(a2, 2, (int)a3);
                v7 = BattleHandler_PushWork(a2, 4, (int)a3);
                BattleHandler_StrSetup((unsigned __int16 *)v7 + 2, 2u, 210);
                BattleHandler_AddArg((u16 *)(v7 + 4), (int)a3);
                BattleHandler_PopWork(a2, (unsigned int *)v7);
                return BattleHandler_PushRun(a2, 3, (int)a3);
            }
        }
        return result;
    }

    // void THUMB_BRANCH_HandlerSnowCloak(int a1, int a2, int a3)
    // {
    //     int attackingMon;
    //     BattleMon *PokeParam;

    //     if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && Handler_GetWeather((a2)) == 3) // hail
    //     {
    //         attackingMon = BattleEventVar_GetValue(VAR_ATTACKING_MON);
    //         PokeParam = Handler_GetPokeParam((ServerFlow*)a2, attackingMon);
    //         k::Printf("\n\nWe're inside the Snow Cloak Handler Function\na1 = %d\na2 = %d\na3 = %d\nAttackingMon = %d\nPokeParam = %d\nHeld Item = %d\n\n",
    //             a1, a2, a3, attackingMon, PokeParam, PokeParam->HeldItem);
    //         if (PokeParam->HeldItem != 293){
    //             BattleEventVar_MulValue(VAR_RATIO, 3277);
    //         }
    //     }
    // }

    // void THUMB_BRANCH_HandlerSandVeil(int a1, int a2, int a3)
    // {
    //     int attackingMon;
    //     BattleMon *PokeParam;

    //     if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) &&  Handler_GetWeather((a2)) == 4)// hail
    //     {
    //         attackingMon = BattleEventVar_GetValue(VAR_ATTACKING_MON);
    //         PokeParam = Handler_GetPokeParam((ServerFlow*)a2, attackingMon);
    //         k::Printf("\n\nWe're inside the Sand Veil Handler Function\na1 = %d\na2 = %d\na3 = %d\nAttackingMon = %d\nPokeParam = %d\nHeld Item = %d\n\n",
    //             a1, a2, a3, attackingMon, PokeParam, PokeParam->HeldItem);
    //         if (PokeParam->HeldItem != 293){
    //             BattleEventVar_MulValue(VAR_RATIO, 3277);
    //         }
    //     }
    // }

    bool checksIfWildBattle(ServerFlow *a1)
    {
        // k::Printf("\nBtlType is %d\n", a1->mainModule->btlSetup->BtlType);
        return a1->mainModule->btlSetup->BtlType == 0;
    }

    // For Unnerve
    // a1 is the position of the pokemon with unnerve
    // a2 is the ServerFlow
    // a3 is the type of skip i think
    // a6 is supposedly the side of
    bool THUMB_BRANCH_SAFESTACK_HandlerUnnerveSkipCheck(int a1, int a2, int a3, int a4, u16 a5, unsigned __int8 a6)
    {
        int MainModule; // r0
        bool result; // r0

        result = 0;
        if (a3 == 5)
        {
            MainModule = HandlerGetMainModule(a1);
            //k::Printf("\n a1 is %d\na2 is %d\na3 is %d\na4 is %d\na5 is %d\na6 is %d\nMainModule is %d\n", a1, a2, a3, a4, (int)a5, a6, MainModule);
            if (!MainModule_IsAllyMonID(MainModule, a6))
            {
                if (PML_ItemIsBerry(a5) || 
                    a5 == 290 ||
                    (a5 >= 545 && a5 <= 564) ||
                    a5 == 292 ||
                    a5 == 291 || 
                    a5 == 274 ||
                    a5 == 542 ||
                    a5 == 294 || 
                    a5 == 543 || 
                    a5 == 275 || 
                    a5 == 219 || 
                    a5 == 214 ||
                    a5 == 271 ||
                    a5 == 541) {
                          return 1; // if (PML_ItemIsBerry(a5))
                    }
            }
        }
        return result;
    }


    void THUMB_BRANCH_HandlerRegenerator(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;      // r6
        unsigned int v6;           // r4
        unsigned int v7;           // r0
        HandlerParam_ChangeHP *v8; // r0
        int Value;                 // [sp+0h] [bp-18h]

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetPokeParam(a2, (int)a3);
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


    // For Fluffy
    int HandlerFluffy(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r0
        int isFire;
        int ratio;

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVEID);

            isFire = (PML_MoveGetType(Value) == TYPE_FIRE) ? 2 : 1;
            ratio = (getMoveFlag(Value, FLAG_CONTACT)) ? 2048 : 4096;

            // k::Printf("\n\n isFire is %d\nratio is %d\nisFire times Ratio is %d\n\n", isFire, ratio, isFire * ratio);

            return BattleEventVar_MulValue(VAR_RATIO, isFire * ratio);
        }
        return result;
    }

    // Weak Armor
    void THUMB_BRANCH_HandlerWeakArmor(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;             // r7
        int v6;                           // r6
        HandlerParam_ChangeStatStage *v7; // r0
        HandlerParam_ChangeStatStage *v8; // r0

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVECATEGORY) == 1 && !BattleEventVar_GetValue(VAR_SUBSTITUTE))
        {
            PokeParam = Handler_GetPokeParam(a2, (int)a3);
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
    // void THUMB_BRANCH_HandlerPickpocket(int a1, ServerFlow *a2, unsigned int a3)
    // {
    //     return;
    // }

    // For Tough Claws
    void THUMB_BRANCH_HandlerCuteCharm(int a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;           // r0
        int v6;                           // r6
        BattleMon *PokeParam;             // r7
        HandlerParam_ChangeStatStage *v8; // r4

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE))
        {
            Value = BattleEventVar_GetValue(VAR_MOVEID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_ATTACKING_MON);
                PokeParam = Handler_GetPokeParam(a2, v6);
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

    // Tough Claws
    int HandlerToughClaws(int a1, int a2, int a3)
    {
        int result; // r0
        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            int MoveID = BattleEventVar_GetValue(VAR_MOVEID);
            if (getMoveFlag(MoveID, FLAG_CONTACT))
            {
                return BattleEventVar_MulValue(VAR_MOVEPOWERRATIO, 5324);
            }
        }
        return result;
    }

    // Heatproof
    int THUMB_BRANCH_HandlerHeatproofPower(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVETYPE);
            if (result == 9)
            {
                return BattleEventVar_MulValue(VAR_MOVEPOWERRATIO, 1024);
            }
        }
        return result;
    }

    int THUMB_BRANCH_HandlerIceBody(int a1, ServerFlow *a2, int a3)
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
                PokeParam = Handler_GetPokeParam(a2, a3);
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v8->header.flags |= 0x800000u;
                v8->pokeID = a3;
                v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, 0x8u);
                BattleHandler_PopWork(a2, v8);
                return BattleEventVar_RewriteValue(VAR_MOVEFAILFLAG, 1);
            }
        }
        else
        {
            result = BattleEventVar_GetValue(VAR_MON_ID);
            if (a3 == result)
            {
                PokeParam = Handler_GetPokeParam(a2, a3);
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v8->header.flags |= 0x800000u;
                v8->pokeID = a3;
                v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, 0x10u);
                BattleHandler_PopWork(a2, v8);
                return BattleEventVar_RewriteValue(VAR_MOVEFAILFLAG, 1);
            }
        }
        return result;
    }

    //
    void HandlerPreBurnOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            // k::Printf("\nWe are in, lets see if this works");
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_BURN;
            v6->sickCont = MakeBasicStatus(CONDITION_BURN);
            v6->fAlmost = 0;
            v6->pokeID = (unsigned __int8)a3;
            BattleHandler_StrSetup((u16 *)&v6->exStr, 1u, 201);
            BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
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
            BattleHandler_StrSetup((u16 *)&v6->exStr, 2u, 202);
            BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
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
            result = BattleEventVar_GetValue(VAR_CONDITIONID);
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
        int result; // r0
        // int PokeType;
        // int v6;               // r6
        // BattleMon *PokeParam; // r7

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result && BattleEventVar_GetValue(VAR_MOVETYPE) == TYPE_POISON)
        {
            // v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_DEFENDING_MON);
            // PokeParam = Handler_GetPokeParam(a2, v6);
            // PokeType = BattleMon_GetPokeType(PokeParam);
            // result = GetTypeEffectivenesssVsMonAltered(TYPE_POISON, PokeType);
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 4);
        }
        return result;
    }

    typedef struct
    {
        int triggerValue;
        ABILITY_HANDLER_FUNC function;
    } ABILITY_TRIGGERTABLE;

    ABILITY_TRIGGERTABLE AbilityTriggerTable[] =
        {
            // {0x2D, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders},
            // {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat},

            {0x47, (ABILITY_HANDLER_FUNC)HandlerFriendGuard}, // 0
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 1
            {0x3B, (ABILITY_HANDLER_FUNC)HandlerPlusMinus},   // 2
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 3
            {0x76, (ABILITY_HANDLER_FUNC)HandlerHealer},      // 4
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 5

            {0x38, (ABILITY_HANDLER_FUNC)HandlerToughClaws}, // 6

            {0x13, (ABILITY_HANDLER_FUNC)HandlerSlushRush},        // 7
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 8

            {0x3B, (ABILITY_HANDLER_FUNC)HandlerThickFat},         // 9
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 10

            {0x3B, (ABILITY_HANDLER_FUNC)HandlerGuts},        // 11
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI}, // 12

            {0x13, (ABILITY_HANDLER_FUNC)HandlerQuickFeet},     // 13
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI}, // 14

            {0x38, (ABILITY_HANDLER_FUNC)HandlerFlareBoost},  // 15
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI}, // 16

            {0x6B, (ABILITY_HANDLER_FUNC)HandlerPoisonHeal},    // 17
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI}, // 18

            {0x38, (ABILITY_HANDLER_FUNC)HandlerToxicBoost},       // 19
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},    // 20
            {0x6B, (ABILITY_HANDLER_FUNC)HandlerToxicBoostStatus}, // 21

            {0x47, (ABILITY_HANDLER_FUNC)HandlerFluffy}, // 22

            {0x2D, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders}, // 23
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat},        // 24

            {0x3E, (ABILITY_HANDLER_FUNC)HandlerCorrosion},

            {0x3C, (ABILITY_HANDLER_FUNC)HandlerMarvelScale}, // 15
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI},

            {0x7F, (ABILITY_HANDLER_FUNC)HandlerRainDish},
            {0x65, (ABILITY_HANDLER_FUNC)HandlerWaterVeil},
            {0x67, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon},
            {0x8A, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},
            {0x55, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},
            {2, (ABILITY_HANDLER_FUNC)HandlerWaterVeilActionEnd},

    };

    int *THUMB_BRANCH_EventAddFriendGuard(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[0].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPlus(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[2].triggerValue;
    }

    int *THUMB_BRANCH_EventAddHealer(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[4].triggerValue;
    }

    int *THUMB_BRANCH_EventAddLightMetal(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[6].triggerValue;
    }

    int *THUMB_BRANCH_EventAddHeavyMetal(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[7].triggerValue;
    }

    int *THUMB_BRANCH_EventAddThickFat(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[9].triggerValue;
    }

    int *THUMB_BRANCH_EventAddGuts(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[11].triggerValue;
    }

    int *THUMB_BRANCH_EventAddQuickFeet(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[13].triggerValue;
    }

    int *THUMB_BRANCH_EventAddFlareBoost(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[15].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPoisonHeal(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[17].triggerValue;
    }

    int *THUMB_BRANCH_EventAddToxicBoost(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&AbilityTriggerTable[19].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPickup(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[22].triggerValue;
    }

    int *THUMB_BRANCH_EventAddOvercoat(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[23].triggerValue;
    }

    int *THUMB_BRANCH_EventAddLimber(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[25].triggerValue;
    }

    int *THUMB_BRANCH_EventAddMarvelScale(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[26].triggerValue;
    }

    int *THUMB_BRANCH_EventAddRainDish(unsigned int *a1)
    {
        *a1 = 6;
        return (int *)&AbilityTriggerTable[28].triggerValue;
    }

    // int GetTypeEffectivenessVsMonAltered(Types a1, int a2)
    // {
    //     int TypeEffectiveness; // r4
    //     int v6;                // r0
    //     unsigned __int8 v7;    // [sp+0h] [bp-18h] BYREF
    //     unsigned __int8 v8;    // [sp+1h] [bp-17h] BYREF

    //     sub_21CE58C(a2, &v8, &v7);
    //     if (PokeTypePair_IsMonotype(a2))
    //     {
    //         return GetTypeEffectivenessAltered(a1, v8);
    //     }
    //     TypeEffectiveness = GetTypeEffectivenessAltered(a1, v8);
    //     v6 = GetTypeEffectivenessAltered(a1, v7);
    //     return GetTypeEffectivenessMultiplier(TypeEffectiveness, v6);
    // }

    // int GetTypeEffectivenessAltered(Types a1, int a2)
    // {
    //     TypeEffectiveness result;
    //     int typeChart[18][18];
    //     unsigned int v3;

    //     if (a1 == 18 || a2 == 18)
    //     {
    //         result = EFFECTIVENESS_1;
    //         return result;
    //     }

    //     if (a1 == TYPE_ICE)
    //     {
    //         v3 = FreezeDryTypeChart[a1][a2];
    //     }
    //     else if (a1 == TYPE_FIGHTING)
    //     {
    //         v3 = SkyUppercutTypeChart[a1][a2];
    //     }
    //     else if (a1 == TYPE_POISON)
    //     {
    //         v3 = CorrosionTypeChart[a1][a2];
    //     }

    //     switch (v3)
    //     {
    //     case 0:
    //         result = EFFECTIVENESS_IMMUNE;
    //         break;
    //     case 2:
    //         result = EFFECTIVENESS_1_2;
    //         break;
    //     case 4:
    //         result = EFFECTIVENESS_1;
    //         break;
    //     case 8:
    //         result = EFFECTIVENESS_2;
    //         break;
    //     default:
    //         result = EFFECTIVENESS_1;
    //     }
    //     return result;
    // }

    void THUMB_BRANCH_HandlerSkullBash(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup((u16 *)&v5->str, 2u, 556);
            BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
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
            BattleHandler_StrSetup((u16 *)&v5->str, 2u, 863);
            BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
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

    // int HandlerBodyPress(int a1, int a2, int a3) {

    // }
    // int HandlerNewTeleport()
    // {
    //     HandlerParam_AddPosEffect *v5;     // r6
    //     HandlerParam_SetConditionFlag *v6; // r0
    //     HandlerParam_Switch *v7;           // r0

    //     if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && Handler_GetFightEnableBenchPokeNum(a2, a3))
    //     {
    //         if (Handler_CheckReservedMemberChangeAction(a2))
    //         {
    //             v5 = BattleHandler_PushWork(a2, EFFECT_ADDPOSEFFECT, a3);
    //             v5->effect = 4;
    //             v5->pos = Handler_PokeIDToPokePos(a2, a3);
    //             *(v5 + 3) = a3;
    //             *(&v5[1] + 12) = 1;
    //             BattleHandler_PopWork(a2, v5);
    //             v6 = BattleHandler_PushWork(a2, EFFECT_SETCONDITIONFLAG, a3);
    //             v6->pokeID = a3;
    //             v6->flag = CONDITIONFLAG_BATONPASS;
    //             v6->header.flags |= 0x1000000u;
    //             BattleHandler_PopWork(a2, v6);
    //             v7 = BattleHandler_PushWork(a2, EFFECT_SWITCH, a3);
    //             v7->pokeID = a3;
    //             v7->fIntrDisable = 1;
    //             v7->header.flags |= 0x1000000u;
    //             BattleHandler_PopWork(a2, v7);
    //         }
    //     }
    // }

    // int HandlerPartingShot()
    // {
    // }

    typedef struct
    {
        int triggerValue;
        MOVE_HANDLER_FUNC function;
    } MOVE_TRIGGERTABLE;

    MOVE_TRIGGERTABLE MoveTriggerTable[] =
        {
            {0x96, (MOVE_HANDLER_FUNC)HandlerMeteorBeam},
            {0x3E, (MOVE_HANDLER_FUNC)NewHandlerSkyUppercut}, // BattleEvent_CheckTypeEffectiveness
            {0x3E, (MOVE_HANDLER_FUNC)HandlerFreezeDry},
            //{0x39, (MOVE_HANDLER_FUNC)HandlerBodyPress}
            };

    // Meteor Beam
    int *THUMB_BRANCH_EventAddFreezeShock(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[0].triggerValue;
    }

    // Parting Shot
    // int *THUMB_BRANCH_EventAddLockOn(unsigned int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[1].triggerValue;
    // }

    // // Teleport
    // int *THUMB_BRANCH_EventAddTeleport(unsigned int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[2].triggerValue;
    // }

    int *THUMB_BRANCH_EventAddSkyUppercut(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[1].triggerValue;
    }

    int *THUMB_BRANCH_EventAddMiracleEye(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[2].triggerValue;
    }

    // int *THUMB_BRANCH_EventAddSwallow(unsigned int *a1){
    //     *a1 = 1;
    //     return (int *)&MoveTriggerTable[3].triggerValue;
    // }
}