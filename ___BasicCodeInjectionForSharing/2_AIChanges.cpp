#include "codeinjection_new.h"
#include "kPrint.h"

extern "C"
{

    int GetTypeEffectivenessAltered(int a1, int a2)
    {
        TypeEffectiveness result;
        int v3;

        if (a1 == 18 || a2 == 18)
        {
            result = EFFECTIVENESS_1;
            return result;
        }

        if (a1 == TYPE_ICE)
        {
            v3 = FreezeDryTypeChart[a1][a2];
            // //k::printf("\nFreezeDryChart entered\nv3 = %d\na1 = %d\na2 = %d\n\n", v3, a1, a2);
        }
        else if (a1 == TYPE_FIGHTING)
        {
            v3 = SkyUppercutTypeChart[a1][a2];
            // //k::printf("\nSkyUppercutChart entered\nv3 = %d\na1 = %d\na2 = %d\n\n", v3, a1, a2);
        }
        else if (a1 == TYPE_POISON)
        {
            v3 = CorrosionTypeChart[a1][a2];
        }
        else
        {
            v3 = normalTypeChart[a1][a2];
        }

        switch (v3)
        {
        case 0:
            result = EFFECTIVENESS_IMMUNE;
            break;
        case 2:
            result = EFFECTIVENESS_1_2;
            break;
        case 4:
            result = EFFECTIVENESS_1;
            break;
        case 8:
            result = EFFECTIVENESS_2;
            break;
        default:
            return 0;
        }
        return result;
    }

    int GetTypeEffectivenessVsMonAltered(int a1, int a2)
    {
        int TypeEffectiveness; // r4
        int v6;                // r0
        int v7;
        int v8;
        v8 = PokeTypePair_GetType1(a2);
        v7 = PokeTypePair_GetType2(a2);

        if (PokeTypePair_IsMonotype(a2))
        {
            return GetTypeEffectivenessAltered(a1, v8);
        }
        TypeEffectiveness = GetTypeEffectivenessAltered(a1, v8);
        v6 = GetTypeEffectivenessAltered(a1, v7);
        return GetTypeEffectivenessMultiplier(TypeEffectiveness, v6);
    }

    TypeEffectiveness PersonalGetTypeEffectiveness(int a1, int a2)
    {
        TypeEffectiveness result;
        PlayerState *playerState;
        int typeChart[18][18];
        int zoneId;
        int v3;

        if (a1 == 18 || a2 == 18)
        {
            result = EFFECTIVENESS_1;
            return result;
        }

        playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        zoneId = PlayerState_GetZoneID(playerState);

        if (zoneId == 607 || zoneId == 195 || zoneId == 196 || zoneId == 197)
        {
            v3 = chargestoneTypeChart[a1][a2];
        }
        else if (zoneId == 339 || zoneId == 338 || zoneId == 340 || zoneId == 341 || zoneId == 462 || (zoneId >= 510 && zoneId <= 514) || (zoneId >= 569 && zoneId <= 572))
        {
            v3 = celestialTypeChart[a1][a2];
        }
        else if (zoneId == 121)
        {
            v3 = opelucidTypeChart[a1][a2];
        }
        else
        {
            v3 = normalTypeChart[a1][a2];
        }

        switch (v3)
        {
        case 0:
            result = EFFECTIVENESS_IMMUNE;
            break;
        case 2:
            result = EFFECTIVENESS_1_2;
            break;
        case 4:
            result = EFFECTIVENESS_1;
            break;
        case 8:
            result = EFFECTIVENESS_2;
            break;
        default:
            result = EFFECTIVENESS_1;
        }
        return result;
    }

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

    TypeEffectiveness THUMB_BRANCH_SAFESTACK_ServerEvent_CheckDamageEffectiveness(
        ServerFlow *a1,
        BattleMon *a2,
        BattleMon *a3,
        int a4,
        unsigned __int8 a5)
    {
        int ID;    // r0
        int v9;    // r0
        int Value; // r5
        int ActualType;
        int v11;                  // r4
        TypeEffectiveness result; // r0

        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
        v9 = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v9);
        BattleEventVar_SetConstValue(VAR_POKE_TYPE, a5);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a4);
        BattleEventVar_SetRewriteOnceValue(VAR_NO_TYPE_EFFECTIVENESS, 0);
        BattleEventVar_SetRewriteOnceValue(VAR_SET_TYPE_EFFECTIVENESS, 0);
        // j_j_BTL_SICKEVENT_CheckNotEffectByType(a1, a3);
        j_j_Condition_CheckUnaffectedByType(a1, a3);
        BattleEvent_CallHandlers(a1, EVENT_CHECK_TYPE_EFFECTIVENESS);
        Value = BattleEventVar_GetValue(VAR_NO_TYPE_EFFECTIVENESS);
        v11 = BattleEventVar_GetValue(VAR_SET_TYPE_EFFECTIVENESS);
        BattleEventVar_Pop();
        if (v11 >= 2)
        {
            // //k::printf("\nMon 1 Type 1 is %d\nMon 1 Type 2 is %d\nMon 2 Type 1 is %d\nMon 2 Type 2 is %d\na4 = %d", PokeTypePair_GetType1(BattleMon_GetPokeType(a2)), PokeTypePair_GetType2(BattleMon_GetPokeType(a2)), PokeTypePair_GetType1(BattleMon_GetPokeType(a3)), PokeTypePair_GetType2(BattleMon_GetPokeType(a3)), a4);
            // //k::printf("\n\nTypeEffectiveness is %d\na4 is %d\nActualType is %d\na5 as int is %d\nv11 is %d\n\n", GetTypeEffectivenessAltered(a4, ActualType), a4, ActualType, (int)a5, v11);
            return (TypeEffectiveness)GetTypeEffectivenessAltered(a4, a5);
        }
        else if (v11)
        {
            // //k::printf("\nWe're in here\n");
            return EFFECTIVENESS_1;
        }
        result = PersonalGetTypeEffectiveness(a4, a5);
        if (result == EFFECTIVENESS_IMMUNE)
        {
            if (Value)
            {
                return EFFECTIVENESS_1;
            }
        }
        return result;
    }

    bool checkRetaliate(ServerFlow *a2, int MonID, int turn)
    {
        FaintRecord *record;
        int turnCount;
        int faintedId;
        int loopCount;
        // record = Handler_GetActionRecord(a2);
        record = Handler_GetFaintRecord(a2);

        turnCount = j_j_FaintRecord_GetCount(record, turn);
        // turnCount = FaintRecord_GetCount(record, 1u);
        loopCount = 0;

        // k::Printf("\n\nRecord is %d\nturnCount is %d\nMonID is %d\n\n", record, turnCount, MonID);
        // // return true;
        if (turnCount)
        {
            while (loopCount <= turnCount)
            {
                faintedId = j_j_FaintRecord_GetPokeID(record, turn, loopCount);

                if (MainModule_IsAllyMonID(MonID, faintedId))
                {
                    k::Printf("\nDid we get in here?\n");
                    return true;
                }
                ++loopCount;
            }
        }
        return false;
    }

    int CheckRatio(ServerFlow *a1, BattleMon *AttackingMon, BattleMon *DefendingMon, int MoveID)
    {

        // Reversal and Flail
        // Set base power to 20
        if (MoveID == 175 || MoveID == 179)
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);
            if (Value == 409600)
            {
                return 4096;
            }
            else if (Value < 409600 && Value >= 281600)
            {
                return 8192;
            }
            else if (Value < 281600 && Value >= 145000)
            {
                return 16384;
            }
            else if (Value < 145000 && Value >= 85300)
            {
                return 32768;
            }
            else if (Value < 85300 && Value >= 42700)
            {
                return 40960;
            }
            else if (Value < 42700 && Value >= 17100)
            {
                return 61440;
            }
            else
            {
                return 81920;
            }
        }

        // Water Spout and Eruption
        if (MoveID == 323 || MoveID == 284)
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);

            if (Value == 409600)
            {
                return 4096;
            }
            else if (Value < 409600 && Value >= 384000)
            {
                return 3840;
            }
            else if (Value < 384000 && Value >= 358400)
            {
                return 3584;
            }
            else if (Value < 358400 && Value >= 332800)
            {
                return 3328;
            }
            else if (Value < 332800 && Value >= 307200)
            {
                return 3072;
            }
            else if (Value < 307200 && Value >= 281600)
            {
                return 2816;
            }
            else if (Value < 281600 && Value >= 256000)
            {
                return 2560;
            }
            else if (Value < 256000 && Value >= 230400)
            {
                return 2304;
            }
            else if (Value < 230400 && Value >= 204800)
            {
                return 2408;
            }
            else
            {
                return 0;
            }
        }

        // Electro Ball
        if (MoveID == 486)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) > Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // Gyro Ball
        if (MoveID == 360)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) < Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // //k::printf("\n ServerFlow: %d\nAttackingMon: %d\nDefendingMon: %d\nCheckRatio for Move %d \n", a1, AttackingMon, DefendingMon, MoveID);
        // Venoshock
        // //k::print("\nCheck #1");
        if (MoveID == 474)
        {
            if (PersonalCheckIfMoveCondition(DefendingMon, CONDITION_POISON))
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #2");
        //  Solarbeam and Solar Blade
        if (MoveID == 76 || MoveID == 554)
        {
            if (ServerEvent_GetWeather(a1) != 1 && AttackingMon->HeldItem != 271 && AttackingMon->Ability != 34 && AttackingMon->Ability != 94 && AttackingMon->Ability != 122)
            {
                return 0;
            }
        }
        // //k::print("\nCheck #3");
        //  Skull Bash and Meteor Beam and Sky Attack
        if (MoveID == 130 || MoveID == 553 || MoveID == 143)
        {
            if (AttackingMon->HeldItem != 271)
            {
                return 0;
            }
        }

        // Electro Shot
        if (MoveID == 193)
        {
            if (ServerEvent_GetWeather(a1) != 2 && AttackingMon->HeldItem != 271)
            {
                return 0;
            }
        }

        // //k::print("\nCheck #4");
        //  Hex, Beat Up, Infernal Parade, Barb Barrage
        if (MoveID == 169 || MoveID == 212 || MoveID == 251 || MoveID == 506 || MoveID == 244)
        {
            if (BattleMon_GetStatus(DefendingMon))
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #5");
        //  Acrobatics
        if (MoveID == 512)
        {
            if (!AttackingMon->HeldItem || AttackingMon->HeldItem == 556)
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #6");
        //  All 2 hit moves
        if (MoveID == 3 || MoveID == 24 || MoveID == 458 || MoveID == 11 || MoveID == 41 || MoveID == 155 || MoveID == 544 || MoveID == 530)
        {
            return 8192;
        }
        // //k::print("\nCheck #7");
        //  All 3 hit moves
        if (MoveID == 167)
        {
            return 12288;
        }
        // //k::print("\nCheck #8");
        //  Brine
        if (MoveID == 362)
        {

            if (BattleMon_GetHPRatio(DefendingMon) <= 204800)
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        if (MoveID == 514)
        {
            if (checkRetaliate(a1, AttackingMon->ID, 1u))
            {
                // //k::printf("\nWe have triggered this effect for retaliate with turn AI\n");
                return 8192;
            }
        }

        // First Impression
        if (MoveID == 373)
        {
            if (BattleMon_GetConditionFlag(AttackingMon, CONDITIONFLAG_ACTIONDONE))
            {
                return 0;
            }
        }

        // //k::print("\nCheck #9");
        //  Facade
        if (MoveID == 263)
        {
            if (BattleMon_GetStatus(AttackingMon))
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #10");
        //  Wake Up Slap and Dream Eater
        if (MoveID == 138 || MoveID == 358)
        {
            if (PersonalCheckIfMoveCondition(DefendingMon, CONDITION_SLEEP))
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #11");
        //  autocrit moves
        if (MoveID == 6 || MoveID == 190 || MoveID == 480 || MoveID == 524 || MoveID == 346)
        {
            if (DefendingMon->Ability == 4 || DefendingMon->Ability == 75)
            {
                return 4096;
            }
            if (AttackingMon->Ability == 97)
            {
                return 12288;
            }
            else
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #12");
        //  All multihit moves
        if (MoveID == 4 || MoveID == 31 || MoveID == 42 || MoveID == 131 || MoveID == 140 || MoveID == 154 || MoveID == 198 || MoveID == 292 || MoveID == 331 || MoveID == 333 || MoveID == 350 || MoveID == 541)
        {
            if (AttackingMon->Ability == 92)
            {
                return 20480;
            }
            // else if (AttackingMon->HeldItem == 543)
            // {
            //     return 16384;
            // }
            else
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #13");
        if (MoveID == 311)
        {
            if (ServerEvent_GetWeather(a1) > 0)
            {
                return 8192;
            }
        }
        // Payback, Revenge, and Avalanche
        if (MoveID == 279 || MoveID == 419 || MoveID == 371)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) < Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // Spit Up
        if (MoveID == 255)
        {
            if (!PML_ItemIsBerry(AttackingMon->HeldItem))
            {
                return 0;
            }
        }

        return 4096;
    }

    // SOURCE OF THE CRASH IS THIS FUNCTION //

    int THUMB_BRANCH_SAFESTACK_Handler_SimulationDamage(ServerFlow *a1, int a2, int a3, int a4)
    {
        int TypeEffectiveness;   // r6
        BattleMon *DefendingMon; // [sp+14h] [bp-34h]
        BattleMon *AttackingMon; // [sp+18h] [bp-30h]
        __int16 moveParam[20];
        unsigned __int16 v12; // [sp+1Ch] [bp-2Ch] BYREF
        int v14;              // [sp+48h] [bp+0h]
        int v15;              // [sp+4Ch] [bp+4h]
        int v16;
        unsigned int ratio;
        int v17;

        int a4check;

        AttackingMon = PokeCon_GetBattleMon(a1->pokeCon, a2);
        DefendingMon = PokeCon_GetBattleMon(a1->pokeCon, a3);

        if (!a4)
        {
            return 0;
        }

        // Checks for Static Damage Moves
        if (a4 == 101 && !BattleMon_HasType(DefendingMon, TYPE_NORMAL))
        {
            return AttackingMon->Level;
        }
        else if (a4 == 69 && (!BattleMon_HasType(DefendingMon, TYPE_GHOST) || AttackingMon->Ability != 113))
        {
            return AttackingMon->Level;
        }
        else if (a4 == 149 && !BattleMon_HasType(DefendingMon, TYPE_DARK))
        {
            return AttackingMon->Level;
        }
        else if (a4 == 162 && (!BattleMon_HasType(DefendingMon, TYPE_GHOST) || AttackingMon->Ability != 113))
        {
            int losthealth = DefendingMon->CurrentHP / 2u;
            if (!losthealth)
            {
                losthealth = 1;
            }
            return losthealth;
        }
        else
        {
            a4check = a4;
        }

        if (!PML_MoveIsDamaging(a4))
        {
            int actualMove;

            // Copycat
            if (a4 == 383)
            {
                actualMove = Handler_GetPrevUsedMove(a1);
                if (actualMove && !j_j_IsNotAllowedCopycatMove(actualMove))
                {
                    a4check = actualMove;
                }
                else
                {
                    return 0;
                }
            }
            // Nature Power
            else if (a4 == 267)
            {
                int BattleTerrain = Handler_GetBattleTerrain(a1);

                // //k::printf("\n\nThe Battle Terrain is %d\n\n", BattleTerrain);

                if (BattleTerrain == 5u)
                {
                    a4check = 402;
                }
                else if (BattleTerrain == 11u)
                {
                    a4check = 89;
                }
                else if (BattleTerrain == 0xCu)
                {
                    a4check = 56;
                }
                else if (BattleTerrain == 7u)
                {
                    a4check = 59;
                }
                else if (BattleTerrain == 9u)
                {
                    a4check = 426;
                }
                else if (BattleTerrain == 0xAu)
                {
                    a4check = 157;
                }
                else if (BattleTerrain == 0xDu)
                {
                    a4check = 58;
                }
                else
                {
                    a4check = 161;
                }
            }
            else
            {
                return 0;
            }
        }

        ++a1->SimulationCounter;

        if (BattleMon_IsIllusionEnabled(DefendingMon))
        {
            DefendingMon = MainModule_GetIllusionDisguise(a1->mainModule, (int)a1->pokeCon, (int)DefendingMon);
        }

        TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, a4check);
        ratio = CheckRatio(a1, AttackingMon, DefendingMon, a4check);
        ServerEvent_GetMoveParam(a1, a4check, (int)AttackingMon, (MoveParam *)moveParam);

        // k::printf("\n\nMoveParam's basic data for field 1 is %d", ((MoveParam *)moveParam)->MoveID);
        // k::printf("\nMoveParam's basic data for field 2 is %d", ((MoveParam *)moveParam)->OriginalMoveID);
        // k::printf("\nMoveParam's basic data for field 3 is %d", ((MoveParam *)moveParam)->userType);
        // k::printf("\nMoveParam's basic data for field 4 is %d", ((MoveParam *)moveParam)->moveType);
        // k::printf("\nMoveParam's basic data for field 5 is %d", ((MoveParam *)moveParam)->category);
        // k::printf("\nMoveParam's basic data for field 6 is %d", ((MoveParam *)moveParam)->targetType);
        // k::printf("\nMoveParam's basic data for field 7 is %d", ((MoveParam *)moveParam)->flags);

        if (a4check == 165)
        {
            ((MoveParam *)moveParam)->moveType = 17;
        }
        if (a4check == 311)
        {
            v17 = ServerEvent_GetWeather(a1);
            if (v17 == 1)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, 53);
                ((MoveParam *)moveParam)->moveType = TYPE_FIRE;
            }
            else if (v17 == 2)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, 57);
                ((MoveParam *)moveParam)->moveType = TYPE_WATER;
            }
            else if (v17 == 3)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, 59);
                ((MoveParam *)moveParam)->moveType = TYPE_ICE;
            }
            else if (v17 == 4)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, 408);
                ((MoveParam *)moveParam)->moveType = TYPE_ROCK;
            }
        }
        if (a4check == 327 || a4check == 357)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAltered(((MoveParam *)moveParam)->moveType, BattleMon_GetPokeType(DefendingMon));
        }

        ServerEvent_CalcDamage(
            a1,
            AttackingMon,
            DefendingMon,
            (MoveParam *)moveParam,
            TypeEffectiveness,
            ratio,
            0,
            v15 == 0,
            &v12);
        --a1->SimulationCounter;

        return v12;
    }

    int THUMB_BRANCH_SAFESTACK_GuessAbility(TrainerAIEnv *a1, int a2, int a3)
    {
        BattleMon *BattleMonFromBattlePos; // r6

        BattleMonFromBattlePos = GetBattleMonFromBattlePos(a1, a3);
        if (PersonalCheckIfMoveCondition(BattleMonFromBattlePos, CONDITION_GASTROACID))
        {
            return 0;
        }
        return BattleMon_GetValue(BattleMonFromBattlePos, VALUE_ABILITY);
    }

    int checkForTechnician(BattleMon *AttackingMon, int MoveID, unsigned int a3)
    {
        if (AttackingMon->Ability == 101)
        {
            if (PML_MoveGetBasePower(MoveID) <= 60)
            {
                return a3 * 1.5;
            }
        }
        return a3;
    }

    int checkForAbilityAndItemBPChanges(BattleMon *AttackingMon, BattleMon *DefendingMon, int Type, int TypeEffectivenessVsMon, unsigned int a4)
    {

        int value;
        value = a4;

        // Abilities
        if (AttackingMon->Ability != 104 && AttackingMon->Ability != 164 && AttackingMon->Ability != 163)
        {
            // Heatproof
            if (DefendingMon->Ability == 85 && Type == TYPE_FIRE)
            {
                return value * .25;
            }
            // Thick Fat
            if (DefendingMon->Ability == 47 && (Type == TYPE_FIRE || Type == TYPE_ICE))
            {
                return value * .5;
            }
            // Dry Skin
            if ((DefendingMon->Ability == 87 || DefendingMon->Ability == 17) && Type == TYPE_FIRE)
            {
                return value * 2;
            }
            // Toxic Boost
            if (DefendingMon->Ability == 137 && Type == TYPE_POISON)
            {
                return value * .5;
            }
            // Filter and Solid Rock
            if ((DefendingMon->Ability == 111 || DefendingMon->Ability == 116) && TypeEffectivenessVsMon > 3)
            {
                return value * .75;
            }
            // Swift Swim
            if (DefendingMon->Ability == 33 && Type == TYPE_WATER){
                return value * .5;
            }
            // Slush Rush
            if (DefendingMon->Ability == 134 && Type == TYPE_ICE){
                return value * .5;
            }
            // Sand Force and Sand Rush
            if ((DefendingMon->Ability == 146 || DefendingMon->Ability == 159) && Type == TYPE_ROCK){
                return value * .5;
            }

        }
        return value;
    }

    int checkForBPChanges(BattleMon *AttackingMon, BattleMon *DefendingMon, int MoveID, unsigned int a4, BtlClientWk *work)
    {
        unsigned int value;
        value = a4;
        ServerFlow *server;
        server = BattleServer_GetServerFlow(work->mainModule->server);

        if (MoveID == 474)
        {
            if (PersonalCheckIfMoveCondition(DefendingMon, CONDITION_POISON))
            {
                return value * 2;
            }
        }

        // Meteor Beam, Skull Bash, Sky Attack
        else if (MoveID == 130 || MoveID == 553 || MoveID == 143)
        {
            if (AttackingMon->HeldItem != 271)
            {
                return value / 2;
            }
        }

        // Reversal and Flail
        // Set base power to 20
        else if (MoveID == 175 || MoveID == 179)
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);

            if (Value == 409600)
            {
                return value;
            }
            else if (Value >= 281600)
            {
                return value * 2;
            }
            else if (Value < 281600 && Value >= 145000)
            {
                return value * 4;
            }
            else if (Value < 145000 && Value >= 85300)
            {
                return value * 8;
            }
            else if (Value < 85300 && Value >= 42700)
            {
                return value * 10;
            }
            else if (Value < 42700 && Value >= 17100)
            {
                return value * 15;
            }
            else
            {
                return value * 20;
            }
        }

        // Water Spout and Eruption
        else if (MoveID == 323 || MoveID == 284)
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);

            if (Value == 409600)
            {
                return value;
            }
            else if (Value < 409600 && Value >= 384000)
            {
                return value / 16 * 15;
            }
            else if (Value < 384000 && Value >= 358400)
            {
                return value / 8 * 7;
            }
            else if (Value < 358400 && Value >= 332800)
            {
                return value / 16 * 13;
            }
            else if (Value < 332800 && Value >= 307200)
            {
                return value / 8 * 6;
            }
            else if (Value < 307200 && Value >= 281600)
            {
                return value / 16 * 11;
            }
            else if (Value < 281600 && Value >= 256000)
            {
                return value / 8 * 5;
            }
            else if (Value < 256000 && Value >= 230400)
            {
                return value / 16 * 9;
            }
            else if (Value < 230400 && Value >= 204800)
            {
                return value / 2;
            }
            else
            {
                return 0;
            }
        }

        // Electro Ball
        else if (MoveID == 486)
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) > Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value * 2;
            }
            else
            {
                return value;
            }
        }

        // // Gyro Ball
        else if (MoveID == 360)
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) < Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value * 2;
            }
            else
            {
                return value;
            }
        }

        // Electro Shot
        else if (MoveID == 193)
        {
            if (BattleField_GetWeather() != 2 && AttackingMon->HeldItem != 271)
            {
                return value / 2;
            }
        }

        // Solarbeam and Solar Blade
        else if (MoveID == 76 || MoveID == 554)
        {
            if (BattleField_GetWeather() != 1 && AttackingMon->HeldItem != 271 && AttackingMon->Ability != 34 && AttackingMon->Ability != 94 && AttackingMon->Ability != 122)
            {
                return value / 2;
            }
        }
        else if (MoveID == 169 || MoveID == 212 || MoveID == 251 || MoveID == 506 || MoveID == 244)
        {
            if (BattleMon_GetStatus(DefendingMon))
            {
                return value * 2;
            }
        }
        // Acrobatics
        else if (MoveID == 512)
        {
            if (!AttackingMon->HeldItem || AttackingMon->HeldItem == 556)
            {
                return value * 2;
            }
        }
        // All 2 hit moves
        else if (MoveID == 3 || MoveID == 24 || MoveID == 458 || MoveID == 11 || MoveID == 41 || MoveID == 155 || MoveID == 544 || MoveID == 530)
        {
            return value * 2;
        }
        // All 3 hit moves
        else if (MoveID == 167)
        {
            return value * 3;
        }
        // Wake Up Slap and Dream Eater
        else if (MoveID == 138 || MoveID == 358)
        {
            if (PersonalCheckIfMoveCondition(DefendingMon, CONDITION_SLEEP))
            {
                return value * 2;
            }
        }

        if (MoveID == 514)
        {
            if (checkRetaliate(server, AttackingMon->ID, 0))
            {
                // //k::printf("\nWe have triggered this effect for retaliate with switch AI\n");
                return value * 2;
            }
        }
        // autocrit moves
        else if (MoveID == 6 || MoveID == 190 || MoveID == 480 || MoveID == 524 || MoveID == 346)
        {
            if (DefendingMon->Ability == 4 || DefendingMon->Ability == 75)
            {
                return value;
            }
            if (AttackingMon->Ability == 97)
            {
                return value * 3;
            }
            else
            {
                return value * 2;
            }
        }
        // All multihit moves
        else if (MoveID == 4 || MoveID == 31 || MoveID == 42 || MoveID == 131 || MoveID == 140 || MoveID == 154 || MoveID == 198 || MoveID == 292 || MoveID == 331 || MoveID == 333 || MoveID == 350 || MoveID == 541)
        {
            if (AttackingMon->Ability == 92)
            {
                return value * 5;
            }
            else if (AttackingMon->HeldItem == 543)
            {
                return value * 4;
            }
            else
            {
                return value * 2;
            }
        }
        else if (MoveID == 373)
        {
            if (BattleMon_GetConditionFlag(AttackingMon, CONDITIONFLAG_ACTIONDONE))
            {
                return value * 0;
            }
        }

        else if (MoveID == 279 || MoveID == 419 || MoveID == 371)
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) < Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value * 2;
            }
        }

        else
        {
            return value;
        }

        return value;
    }

    int checkForSTAB(BattleMon *a1, int a2, unsigned int a3)
    {
        if (BattleMon_HasType(a1, (Types)a2))
        {
            return a3 * 1.5;
        }
        else
        {
            return a3;
        }
    }

    bool CheckIfImmuneAbility(int Type, int MoveID, BattleMon *DefendingMon)
    {
        int ability;

        ability = DefendingMon->Ability;

        if (Type == TYPE_WATER && (ability == 114 || ability == 11 || ability == 87))
        {
            return true;
        }
        if (Type == TYPE_GROUND && (ability == 26))
        {
            return true;
        }
        if (Type == TYPE_ELECTRIC && (ability == 10 || ability == 31 || ability == 78))
        {
            return true;
        }
        if (Type == TYPE_GRASS && (ability == 157))
        {
            return true;
        }
        if (Type == TYPE_FIRE && (ability == 18))
        {
            return true;
        }
        if (ability == 43 && getMoveFlag(MoveID, FLAG_SOUND))
        {
            return true;
        }
        return false;
    }

    // a3 is the number of battle ready mons
    // a4 is the opposing pokemon
    unsigned int THUMB_BRANCH_SAFESTACK_PickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
    {
        unsigned int v5;                     // r5
        BattleMon *MonData;                  // r6
        int ID;                              // r4
        unsigned int BasePower;              // r4
        unsigned int TypeEffectivenessVsMon; // r0
        unsigned int v10;                    // r0
        unsigned int result;                 // r0
        unsigned int j;                      // r5
        unsigned int k;                      // r6
        unsigned int v14;                    // r1
        unsigned int v15;                    // r0
        unsigned int v18;
        u8 v16;                 // r1
        int Type;               // [sp+8h] [bp-38h]
        unsigned int MoveCount; // [sp+Ch] [bp-34h]
        unsigned int i;         // [sp+10h] [bp-30h]
        int PokeType;           // [sp+14h] [bp-2Ch]
        __int16 v23[6];         // [sp+1Ch] [bp-24h]
        BattleMon *v24;         // [sp+28h] [bp-18h]

        v24 = a4;
        PokeType = BattleMon_GetPokeType(a4);
        for (i = 0; i < a3; i = (i + 1))
        {
            v5 = 0;
            v23[i] = 0;
            MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
            if (!BattleMon_IsFainted(MonData))
            {
                MoveCount = BattleMon_GetMoveCount(MonData);
                if (MoveCount)
                {
                    do
                    {

                        if (Move_GetPP(MonData, v5))
                        {
                            ID = Move_GetID(MonData, v5);
                            if (PML_MoveIsDamaging(ID) && ID != 120 && ID != 153)
                            {
                                Type = PML_MoveGetType(ID);
                                BasePower = PML_MoveGetBasePower(ID);
                                // k:Printf("\nBase Power from %d is %d\n", ID, BasePower);

                                // Weather Ball Checks
                                if (ID == 311)
                                {
                                    v18 = BattleField_GetWeather();

                                    if (v18 != 0)
                                    {
                                        BasePower = 100;
                                    }
                                    if (v18 == 1)
                                    {
                                        Type = TYPE_FIRE;
                                    }
                                    else if (v18 == 2)
                                    {
                                        Type = TYPE_WATER;
                                    }
                                    else if (v18 == 3)
                                    {
                                        Type = TYPE_ICE;
                                    }
                                    else if (v18 == 4)
                                    {
                                        Type = TYPE_ROCK;
                                    }
                                }
                                // //k::printf("\nBase Power from %d is %d, and the Type is %d\n", ID, BasePower, Type);

                                // if (BasePower < 0xA)
                                // {
                                //     BasePower = 60;
                                // }
                                if (ID == 327 || ID == 357 || MonData->Ability == 7)
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    // //k::printf("\n 2. TypeEffectivenessVsMon is: %d for Move %d \n", TypeEffectivenessVsMon, a4);
                                }
                                else
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);
                                }

                                if (CheckIfImmuneAbility(Type, ID, a4))
                                {
                                    TypeEffectivenessVsMon = 0;
                                }

                                if (TypeEffectivenessVsMon <= 5)
                                {
                                    switch (TypeEffectivenessVsMon)
                                    {
                                    case 0:
                                        BasePower = 0;
                                        break;
                                    case 1:
                                        v10 = BasePower << 14;
                                        goto LABEL_11;
                                    case 2:
                                        v10 = BasePower << 15;
                                        goto LABEL_11;
                                    case 4:
                                        v10 = BasePower << 17;
                                        goto LABEL_11;
                                    case 5:
                                        v10 = BasePower << 18;
                                    LABEL_11:
                                        // //k::printf("\n Base Power of %d before any changes is %d\n", ID, v10);
                                        v10 = checkForBPChanges(MonData, v24, ID, v10, a1);
                                        // //k::printf("\n Base Power of %d after BP changes is %d\n", ID, v10);
                                        v10 = checkForTechnician(MonData, ID, v10);
                                        // //k::printf("\n Base Power of %d after Tech changes is %d\n", ID, v10);
                                        v10 = checkForSTAB(MonData, Type, v10);
                                        v10 = checkForAbilityAndItemBPChanges(MonData, v24, Type, TypeEffectivenessVsMon, v10);

                                        // //k::printf("\n Base Power of %d after STAB changes %d\n", ID, v10);
                                        BasePower = HIWORD(v10);
                                        // //k::printf("\n Base Power of %d after STAB and HIWORD changes %d\n", ID, BasePower);
                                        break;
                                    default:
                                        v10 = BasePower << 16;
                                        // //k::printf("\n Base Power of %d before any changes is %d\n", ID, v10);
                                        v10 = checkForBPChanges(MonData, v24, ID, v10, a1);
                                        // //k::printf("\n Base Power of %d after BP changes is %d\n", ID, v10);
                                        v10 = checkForTechnician(MonData, ID, v10);
                                        // //k::printf("\n Base Power of %d after Tech changes is %d\n", ID, v10);
                                        v10 = checkForSTAB(MonData, Type, v10);

                                        v10 = checkForAbilityAndItemBPChanges(MonData, v24, Type, TypeEffectivenessVsMon, v10);
                                        // //k::printf("\n Base Power of %d after STAB changes %d\n", ID, v10);
                                        BasePower = HIWORD(v10);
                                        // //k::printf("\n Base Power of %d after STAB and HIWORD changes %d\n", ID, BasePower);

                                        break;
                                    }
                                }
                                if (v23[i] < BasePower)
                                {
                                    // //k::printf("\n Base Power of %d is %d \n", ID, BasePower);
                                    v23[i] = BasePower;
                                }
                            }
                        }
                        v5 = (v5 + 1);
                    } while (v5 < MoveCount);
                }
            }
        }
        result = a3;
        for (j = 0; j < a3; result = a3)
        {
            for (k = (j + 1); k < a3; k = (k + 1))
            {
                v14 = v23[k];
                v15 = v23[j];
                if (v15 < v14)
                {
                    v23[j] = v14;
                    v23[k] = v15;
                    v16 = a2[j];
                    a2[j] = a2[k];
                    a2[k] = v16;
                }
            }
            j = (unsigned __int8)(j + 1);
        }
        return result;
    }

    bool THUMB_BRANCH_SAFESTACK_ShouldSwitchIfChoicedIntoIneffectiveMove(BtlClientWk *a1, BattleMon *a2, BattleMon *a3)
    {
        ConditionData MoveCondition; // r0
        int Param;                   // r0
        int TypeEffectiveness;
        bool IsDamaging; // r6
        int PokeType;    // r0
        __int64 v10;     // kr00_8
        bool result;     // r0
        __int64 v12;     // r0
        __int64 v13;     // kr08_8
        __int64 v14;     // kr10_8
        int wazaId;      // [sp+0h] [bp-28h]
        int Type;        // [sp+4h] [bp-24h]

        // //k::printf("\n Checking that we're inside the right function\n");
        if (!PersonalCheckIfMoveCondition(a2, CONDITION_CHOICELOCK) && !PersonalCheckIfMoveCondition(a2, CONDITION_ENCORE))
        {
            // //k::printf("\n We outtie\n");
            return 0;
        }

        if (PersonalCheckIfMoveCondition(a2, CONDITION_CHOICELOCK))
        {
            MoveCondition = BattleMon_GetMoveCondition(a2, CONDITION_CHOICELOCK);
            Param = Condition_GetParam(MoveCondition);
        }
        else if (PersonalCheckIfMoveCondition(a2, CONDITION_ENCORE))
        {
            MoveCondition = BattleMon_GetMoveCondition(a2, CONDITION_ENCORE);
            Param = Condition_GetParam(MoveCondition);
        }
        // //k::printf("\n Param = %d\n", Param);
        wazaId = Param;
        if (!Param)
        {
            return 0;
        }
        IsDamaging = PML_MoveIsDamaging(Param);
        Type = PML_MoveGetType(wazaId);
        PokeType = BattleMon_GetPokeType(a3);

        if (wazaId == 327 || wazaId == 357 || a2->Ability == 7)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAltered(Type, PokeType);
            // //k::printf("\n 2. TypeEffectivenessVsMon is: %d for Move %d \n", TypeEffectiveness, wazaId);
        }
        else
        {
            TypeEffectiveness = GetTypeEffectivenessVsMon(Type, PokeType);
        }

        if (!IsDamaging)
        {
            return 1;
        }
        // If the pokemon is immune via Type or Ability
        if (TypeEffectiveness == 0 || CheckIfImmuneAbility(Type, wazaId, a3))
        {
            // Will always switch if there's another pokemon that can deal some damage
            if (CheckIfMonToSwitchToWithSEMove(a1, a3, 1))
            {
                return 1;
            }
            return 0;
        }
        // If the move is 4x resisted
        else if (TypeEffectiveness == 1)
        {
            // Will switch so long as there's anotehr pokemon that can deal better damage
            if (CheckIfMonToSwitchToWithSEMove(a1, a3, 2))
            {
                return 1;
            }
            return 0;
        }
        // If the move is 2x resisted
        else if (TypeEffectiveness == 2)
        {
            // If the pokemon has tinted lens, it doesn't care about .5x resist
            if (a2->Ability == 110)
            {
                return 0;
            }
            // If another pokemon in the party has a super effective move, guaranteed switch
            if (CheckIfMonToSwitchToWithSEMove(a1, a3, 4))
            {
                return 1;
            }
            // If the best another pokemon in the party has is a neutral move, 50% chance to switch
            if (CheckIfMonToSwitchToWithSEMove(a1, a3, 3))
            {
                if (RandomInRange(1, 100) >= 25)
                {
                    return 1;
                }
            }
        }
        return 0;
    }
}
