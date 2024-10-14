#include "codeinjection_new.h"
#include "kPrint.h"

extern "C"
{

    bool THUMB_BRANCH_SAFESTACK_BattleMon_CheckIfMoveCondition(BattleMon *a1, MoveCondition a2)
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

    void THUMB_BRANCH_SAFESTACK_HandlerLightBall(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            result = BattleMon_GetSpecies(PokeParam);
            if (result == 25 || result == 133)
            {
                BattleEventVar_MulValue(VAR_RATIO, 0x2000);
            }
        }
    }

    bool checkIfWildBattle(ServerFlow *a1)
    {
        return a1->mainModule->btlSetup->btlType == 0;
    }

    void HandlerStaticOrb(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_PARALYSIS;
            v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            v6->fAlmost = 0;
            v6->pokeID = (int)a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup(&v6->exStr, 2u, 273);
            BattleHandler_AddArg(&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerStaticOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
            v6->sickID = CONDITION_PARALYSIS;
            v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            v6->fAlmost = 0;
            v6->pokeID = a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup(&v6->exStr, 2u, 273);
            BattleHandler_AddArg(&v6->exStr, a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerFlameOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {

            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_BURN;
            v6->sickCont = MakeBasicStatus(CONDITION_BURN);
            v6->fAlmost = 0;
            v6->pokeID = a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup(&v6->exStr, 2u, 258);
            BattleHandler_AddArg(&v6->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg(&v6->exStr, SubID);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerToxicOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
            v6->sickID = CONDITION_POISON;
            v6->sickCont = Condition_MakeBadlyPoisoned();
            v6->fAlmost = 0;
            v6->pokeID = a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup(&v6->exStr, 2u, 240);
            BattleHandler_AddArg(&v6->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg(&v6->exStr, SubID);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerMysteriousDevice(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 1u, 1) || BattleMon_IsStatChangeValid(PokeParam, 3u, 1) || BattleMon_IsStatChangeValid(PokeParam, 6u, -1))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerMysteriousDeviceUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        int SubID;                    // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ACCURACY;
            v6->rankVolume = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerColressDevice(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 1u, 1) || BattleMon_IsStatChangeValid(PokeParam, 3u, 1))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerColressDeviceUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        int SubID;                    // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerStressTester(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Damage *v1;
        int ItemParam;
        int SubID;
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);

            k::Printf("\n\nThe pokemon's sex is %d\n\n", PokeParam->Sex);
            v1 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, a3);
            v1->pokeID = a3;
            v1->damage = BattleMon_GetValue(PokeParam, VALUE_CURRENT_HP) - 1;
            BattleHandler_StrSetup(&v1->exStr, 2u, 1038);
            BattleHandler_AddArg(&v1->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg(&v1->exStr, SubID);
            BattleHandler_PopWork(a2, v1);
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
                // BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&v7->str, 2u, 210);
                BattleHandler_AddArg(&v7->str, (int)a3);
                BattleHandler_PopWork(a2, v7);
                // BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
            }
        }
    }

    void HandlerAssaultVest(int a1, int a2, int a3)
    {

        int result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            if (BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 2)
            {
                BattleEventVar_MulValue(VAR_RATIO, 6144);
            }
        }
    }

    int HandlerRoseliBerry(int a1, ServerFlow *a2, int a3, _DWORD *a4)
    {
        return CommonResistBerry(a1, a2, a3, a4, TYPE_FAIRY, 0);
    }

    void HandlerFairyGemPower(int a1, ServerFlow *a2, int a3, _DWORD *a4)
    {
        CommonGemDecide(a1, a2, a3, a4, TYPE_FAIRY);
    }

    void HandlerFairyGemDecide(int a1, ServerFlow *a2, int a3, _DWORD *a4)
    {
        CommonGemPower(a1, a2, a3, a4, TYPE_FAIRY);
    }

    void HandlerPixiePlate(BattleEventItem *a1, int a2, int a3)
    {
        CommonTypeBoostingItem(a1, a2, a3, TYPE_FAIRY);
    }

    void HandlerFairyDust(BattleEventItem *a1, int a2, int a3)
    {
        CommonTypeBoostingItem(a1, a2, a3, TYPE_FAIRY);
    }

    void HandlerWeaknessPolicy(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS) > 3)
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 1u, 2) || BattleMon_IsStatChangeValid(PokeParam, 3u, 2))
            {
                ItemEvent_PushRun(a1, a2, (int)a3);
            }
        }
    }

    void HandlerWeaknessPolicyUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        int SubID;                    // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 2;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 2;
            BattleHandler_PopWork(a2, v6);
        }
    }

    int HandlerLuckyCharm(BattleEventItem *a1, ServerFlow *a2, int a3, unsigned int *a4)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_CRITICAL_FLAG))
        {
            BattleEventVar_MulValue(VAR_RATIO, 2048);
            *a4 = 1;
            return 1;
        }
        return 0;
    }

    void HandlerLuckyCharmUse(BattleEventItem *a1, ServerFlow *a2, int a3, unsigned int **a4)
    {
        HandlerParam_ConsumeItem *v7;
        int SubID;
        if (*a4)
        {
            if (HandlerCommon_CheckTargetMonID(a3))
            {
                v7 = (HandlerParam_ConsumeItem *)(a2, EFFECT_CONSUMEITEM, a3);
                BattleHandler_StrSetup(&v7->exStr, 2u, 219);
                BattleHandler_AddArg(&v7->exStr, (int)a3);
                SubID = BattleEventItem_GetSubID(a1);
                BattleHandler_AddArg(&v7->exStr, SubID);
                BattleHandler_PopWork(a2, v7);
            }
        }
    }

    void HandlerThroatSpraySoundMoveCheck(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            int moveID = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(moveID, FLAG_SOUND))
            {
                BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
                if (BattleMon_IsStatChangeValid(currentMon, STATSTAGE_SPECIAL_ATTACK, 1))
                {
                    ItemEvent_PushRun(battleEventItem, serverFlow, pokemonSlot);
                }
            }
        }
    }

    void HandlerThroatSprayUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_ChangeStatStage *spAttackBoost;
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            spAttackBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, pokemonSlot);
            spAttackBoost->poke_cnt = 1;
            spAttackBoost->pokeID[0] = pokemonSlot;
            spAttackBoost->rankType = STATSTAGE_SPECIAL_ATTACK;
            spAttackBoost->rankVolume = 1;
            BattleHandler_PopWork(a2, spAttackBoost);
        }
    }

    void HandlerBlunderPolicyCheckMiss(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        k::Printf("\nWe are inside the Blunder Policy Handler\n");
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            k::Printf("\nWe are inside the first loop of logic in the Blunder Policy Handler\n");

            BattleMon *battleMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
            if (BattleMon_IsStatChangeValid(battleMon, STATSTAGE_SPEED, 2))
            {
                ItemEvent_PushRun(battleEventItem, serverFlow, pokemonSlot);
            }
        }
    }

    void HandlerBlunderPolicyUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_ChangeStatStage *speedBoost;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            speedBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, pokemonSlot);
            speedBoost->poke_cnt = 1;
            speedBoost->pokeID[0] = pokemonSlot;
            speedBoost->rankType = STATSTAGE_SPEED;
            speedBoost->rankVolume = 2;
            BattleHandler_PopWork(a2, speedBoost);
        }
    }

    // KEE BERRY
    void HandlerKeeBerryDamageReaction(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1)
        {
            BattleMon *defendingMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

            // if (IsModifyItemMove((MoveID)BattleEventVar_GetValue(VAR_MOVE_ID), BattleMon_GetHeldItem(defendingMon))) // CHECK ITEM IS NOT KNOCKED OFF OR CHANGED
            //     return;

            if (BattleMon_IsStatChangeValid(defendingMon, STATSTAGE_DEFENSE, 1))
            {
                ItemEvent_PushRun(battleEventItem, serverFlow, pokemonSlot);
            }
        }
    }
    void HandlerKeeBerryUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_ChangeStatStage *defenseBoost;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            defenseBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, pokemonSlot);
            defenseBoost->poke_cnt = 1;
            defenseBoost->pokeID[0] = (u8)pokemonSlot;
            defenseBoost->rankType = STATSTAGE_DEFENSE;
            defenseBoost->rankVolume = 1;
            BattleHandler_PopWork(a2, defenseBoost);
        }
    }

    // MARANGA BERRY
    void HandlerMarangaBerryDamageReaction(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 2)
        {
            BattleMon *defendingMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

            // if (IsModifyItemMove((MoveID)BattleEventVar_GetValue(VAR_MOVE_ID), BattleMon_GetHeldItem(defendingMon))) // CHECK ITEM IS NOT KNOCKED OFF OR CHANGED
            //     return;

            if (BattleMon_IsStatChangeValid(defendingMon, STATSTAGE_SPECIAL_DEFENSE, 1))
            {
                ItemEvent_PushRun(battleEventItem, serverFlow, pokemonSlot);
            }
        }
    }
    void HandlerMarangaBerryUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_ChangeStatStage *spDefenseBoost;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            spDefenseBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, pokemonSlot);
            spDefenseBoost->poke_cnt = 1;
            spDefenseBoost->pokeID[0] = (u8)pokemonSlot;
            spDefenseBoost->rankType = STATSTAGE_SPECIAL_DEFENSE;
            spDefenseBoost->rankVolume = 1;
            BattleHandler_PopWork(a2, spDefenseBoost);
        }
    }


    typedef struct
    {
        BattleEventType triggerValue;
        ITEM_HANDLER_FUNC function;
    } ITEM_TRIGGERTABLE;


    ITEM_TRIGGERTABLE MarangaBerryHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ITEM_HANDLER_FUNC)HandlerMarangaBerryDamageReaction},
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerMarangaBerryUse},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerMarangaBerryUse},
    };

    ITEM_TRIGGERTABLE *EventAddMarangaBerry(int *a1)
    {
        *a1 = ARRAY_COUNT(MarangaBerryHandlers);
        return MarangaBerryHandlers;
    }

   ITEM_TRIGGERTABLE KeeBerryHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ITEM_HANDLER_FUNC)HandlerKeeBerryDamageReaction},
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerKeeBerryUse},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerKeeBerryUse},
    };

    ITEM_TRIGGERTABLE *EventAddKeeBerry(int *a1)
    {
        *a1 = ARRAY_COUNT(KeeBerryHandlers);
        return KeeBerryHandlers;
    }

    //
    // ASSAULT VEST
    //
    ITEM_TRIGGERTABLE AssaultVestHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ITEM_HANDLER_FUNC)HandlerAssaultVest}, // 10
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerBracer(_DWORD *a1)
    {
        *a1 = 1;
        return AssaultVestHandlers;
    };

    //
    // WEAKNESS POLICY
    //
    ITEM_TRIGGERTABLE WeaknessPolicyHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicy}, // 0
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicyUse},            // 1
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerLens(_DWORD *a1)
    {
        *a1 = 2;
        return WeaknessPolicyHandlers;
    };

    //
    // FAIRY DUST
    //
    ITEM_TRIGGERTABLE FairyDustHandlers[] = {
        {EVENT_MOVE_POWER, (ITEM_HANDLER_FUNC)HandlerFairyDust}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddAdamantOrb(_DWORD *a1)
    {
        *a1 = 1;
        return FairyDustHandlers;
    }

    //
    // PIXIE PLATE
    //
    ITEM_TRIGGERTABLE PixiePlateHandlers[] = {
        {EVENT_MOVE_POWER, (ITEM_HANDLER_FUNC)HandlerPixiePlate},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddLustrousOrb(_DWORD *a1)
    {
        *a1 = 1;
        return PixiePlateHandlers;
    }

    //
    // FAIRY GEM
    //
    ITEM_TRIGGERTABLE FairyGemHandlers[] = {
        {EVENT_DAMAGE_PROCESSING_START, (ITEM_HANDLER_FUNC)HandlerFairyGemPower},
        {EVENT_MOVE_POWER, (ITEM_HANDLER_FUNC)HandlerFairyGemDecide},
        {EVENT_DAMAGE_PROCESSING_END, (ITEM_HANDLER_FUNC)HandlerGemEnd},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerBelt(_DWORD *a1)
    {
        *a1 = 3;
        return FairyGemHandlers;
    }

    //
    // ROSELI BERRY
    //
    ITEM_TRIGGERTABLE RoseliBerryHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ITEM_HANDLER_FUNC)HandlerRoseliBerry},
        {EVENT_AFTER_DAMAGE_REACTION, (ITEM_HANDLER_FUNC)HandlerCommonResistBerryDamageAfter},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddLansatBerry(_DWORD *a1)
    {
        *a1 = 2;
        return RoseliBerryHandlers;
    }

    //
    // FLAME ORB
    //
    ITEM_TRIGGERTABLE FlameOrbHandlers[] = {
        {EVENT_TURN_CHECK_END, (ITEM_HANDLER_FUNC)HandlerFlameOrb},
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerFlameOrbWild},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerFlameOrbUseTemp},
        {EVENT_SKIP_RUN_CALC, (ITEM_HANDLER_FUNC)HandlerSmokeBall},
        {EVENT_RUN_EXIT_MESSAGE, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddFlameOrb(_DWORD *a1)
    {
        *a1 = 5;
        return FlameOrbHandlers;
    }

    //
    // TOXIC ORB
    //
    ITEM_TRIGGERTABLE ToxicOrbHandlers[] = {
        {EVENT_TURN_CHECK_END, (ITEM_HANDLER_FUNC)HandlerToxicOrb},
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerToxicOrbWild},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerToxicOrbUseTemp},
        {EVENT_SKIP_RUN_CALC, (ITEM_HANDLER_FUNC)HandlerSmokeBall},
        {EVENT_RUN_EXIT_MESSAGE, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddToxicOrb(_DWORD *a1)
    {
        *a1 = 5;
        return ToxicOrbHandlers;
    }

    //
    // STRESS TESTER
    //
    ITEM_TRIGGERTABLE StressTesterHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerStressTester},
        {EVENT_SKIP_RUN_CALC, (ITEM_HANDLER_FUNC)HandlerSmokeBall},
        {EVENT_RUN_EXIT_MESSAGE, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddMetalPowder(_DWORD *a1)
    {
        *a1 = 3;
        return StressTesterHandlers;
    }

    //
    // STATIC ORB
    //
    ITEM_TRIGGERTABLE StaticOrbHandlers[] = {
        {EVENT_TURN_CHECK_END, (ITEM_HANDLER_FUNC)HandlerStaticOrb},
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerStaticOrbWild},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerLightBallUseTemp},
        {EVENT_SKIP_RUN_CALC, (ITEM_HANDLER_FUNC)HandlerSmokeBall},
        {EVENT_RUN_EXIT_MESSAGE, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddAmuletCoin(_DWORD *a1)
    {
        *a1 = 5;
        return StaticOrbHandlers;
    }

    //
    // MYSTERIOUS DEVICE / COLRESS PROTOTYPE
    //
    ITEM_TRIGGERTABLE MysteriousDeviceHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerMysteriousDevice},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerMysteriousDeviceUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddQuickPowder(_DWORD *a1)
    {
        *a1 = 2;
        return MysteriousDeviceHandlers;
    }

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerWeight(_DWORD *a1)
    {
        *a1 = 2;
        return MysteriousDeviceHandlers;
    }

    //
    // COLRESS INVENTION
    //
    ITEM_TRIGGERTABLE ColressDeviceHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerColressDevice},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerColressDeviceUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerBand(_DWORD *a1)
    {
        *a1 = 2;
        return ColressDeviceHandlers;
    }

    //
    // LUCKY CHARM
    //
    ITEM_TRIGGERTABLE LuckyCharmHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ITEM_HANDLER_FUNC)HandlerLuckyCharm},                // 26
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerLuckyCharmUse},                             // 27
        {EVENT_AFTER_DAMAGE_REACTION, (ITEM_HANDLER_FUNC)HandlerCommonResistBerryDamageAfter}, // 28
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddRingTarget(_DWORD *a1)
    {
        *a1 = 3;
        return LuckyCharmHandlers;
    }

    //
    // THROAT SPRAY
    //
    ITEM_TRIGGERTABLE ThroatSprayHandlers[] = {
        {EVENT_MOVE_EXECUTE_END, (ITEM_HANDLER_FUNC)HandlerThroatSpraySoundMoveCheck}, // 35
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerThroatSprayUse},                    // 36
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddGriseousOrb(_DWORD *a1)
    {
        *a1 = 2;
        return ThroatSprayHandlers;
    }

    //
    // BLUNDER POLICY
    //
    ITEM_TRIGGERTABLE BlunderPolicyHandlers[] = {
        {EVENT_MOVE_EXECUTE_NOEFFECT, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyCheckMiss}, // 37
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyUse},                    // 38
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddLuckyPunch(_DWORD *a1)
    {
        *a1 = 2;
        return BlunderPolicyHandlers;
    }

    //
    // SAFETY GOGGLES
    //
    ITEM_TRIGGERTABLE SafetyGogglesHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ITEM_HANDLER_FUNC)HandlerOvercoatPowders},
        {EVENT_WEATHER_REACTION, (ITEM_HANDLER_FUNC)HandlerOvercoat},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerAnklet(_DWORD *a1)
    {
        *a1 = 2;
        return SafetyGogglesHandlers;
    }
}