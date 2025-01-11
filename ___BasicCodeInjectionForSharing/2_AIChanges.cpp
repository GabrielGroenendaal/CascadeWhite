#include "codeinjection_new.h"
#include "kPrint.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

extern "C"
{

    u16 THUMB_BRANCH_getTrainerID(u16 *pTrainerInfo)
    {
        return *(pTrainerInfo + 4);
    };

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

    u32 GetCritSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16415);

        // k::Printf("Current crit setting is %d\n", *lvl_cap_ptr);

        return *lvl_cap_ptr;
    }

    int GetCritRatio(int sniper)
    {
        if (GetCritSetting() == 0)
        {
            if (sniper == 1)
            {
                return 12288;
            }
            else
            {
                return 8192;
            }
        }
        else
        {
            if (sniper == 1)
            {
                return 9216;
            }
            else
            {
                return 6144;
            }
        }
    }

    int GetCritRatioSwitch()
    {
        if (GetCritSetting() == 0)
        {
            return 2;
        }
        else
        {
            return 1.5;
        }
    }

    int GetTypeEffectivenessAlteredSacredSword(int a1, int a2)
    {
        TypeEffectiveness result;
        int v3;

        if (a1 == TYPE_NONE || a2 == TYPE_NONE)
        {
            result = EFFECTIVENESS_1;
            return result;
        }

        if (a1 == TYPE_FIGHTING)
        {
            v3 = SacredSwordTypeChart[a1][a2];
            // //k::printf("\nFreezeDryChart entered\nv3 = %d\na1 = %d\na2 = %d\n\n", v3, a1, a2);
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

    int GetTypeEffectivenessAltered(int a1, int a2)
    {
        TypeEffectiveness result;
        int v3;
        PlayerState *playerState;
        int zoneId;
        playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        zoneId = PlayerState_GetZoneID(playerState);

        if (a1 == TYPE_NONE || a2 == TYPE_NONE)
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
            if (a2 == TYPE_FLYING)
            {
                v3 = SkyUppercutTypeChart[a1][a2];
            }
            if (zoneId == 121)
            {
                v3 = opelucidTypeChart[a1][a2];
            }
            else
            {
                v3 = SkyUppercutTypeChart[a1][a2];
            }
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

    int GetTypeEffectivenessVsMonAlteredSacredSword(int a1, int a2)
    {
        int TypeEffectiveness; // r4
        int v6;                // r0
        int v7;
        int v8;
        v8 = PokeTypePair_GetType1(a2);
        v7 = PokeTypePair_GetType2(a2);

        if (PokeTypePair_IsMonotype(a2))
        {
            return GetTypeEffectivenessAlteredSacredSword(a1, v8);
        }
        TypeEffectiveness = GetTypeEffectivenessAlteredSacredSword(a1, v8);
        v6 = GetTypeEffectivenessAlteredSacredSword(a1, v7);
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
        // if (a1->HeldItem == 289 && a2 == CONDITION_TAUNT)
        // {
        //     return true;
        // }
        if (a2 == CONDITION_BLOCK && ((a1->Conditions[CONDITION_CURSE] & 7) != 0))
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
                    // k::Printf("\nDid we get in here?\n");
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
        if (MoveID == MOVE175_FLAIL || MoveID == MOVE179_REVERSAL)
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
        if (MoveID == MOVE323_WATER_SPOUT || MoveID == MOVE284_ERUPTION)
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
        if (MoveID == MOVE486_ELECTRO_BALL)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) > Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // Gyro Ball
        if (MoveID == MOVE360_GYRO_BALL)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) < Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // //k::printf("\n ServerFlow: %d\nAttackingMon: %d\nDefendingMon: %d\nCheckRatio for Move %d \n", a1, AttackingMon, DefendingMon, MoveID);
        // Venoshock
        // //k::print("\nCheck #1");
        if (MoveID == MOVE474_VENOSHOCK)
        {
            if (PersonalCheckIfMoveCondition(DefendingMon, CONDITION_POISON))
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #2");
        //  Solarbeam and Solar Blade
        if (MoveID == MOVE076_SOLAR_BEAM || MoveID == MOVE554_SOLAR_BLADE)
        {
            if (ServerEvent_GetWeather(a1) != WEATHER_SUN && AttackingMon->HeldItem != IT0271_POWER_HERB && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL034_CHLOROPHYLL && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL094_SOLAR_POWER && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL122_FLOWER_GIFT)
            {
                return 0;
            }
        }
        // //k::print("\nCheck #3");
        //  Skull Bash and Meteor Beam and Sky Attack
        if (MoveID == MOVE130_SKULL_BASH || MoveID == MOVE553_METEOR_BEAM || MoveID == MOVE143_SKY_ATTACK)
        {
            if (AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return 0;
            }
        }

        // Stomp'n Tantrum, Uproar, Temper Flare
        if (MoveID == MOVE253_UPROAR || MoveID == MOVE046_STOMPING_TANTRUM || MoveID == MOVE218_TEMPER_FLARE || MoveID == MOVE220_SEETHING_COLD || MoveID == MOVE037_THRASH)
        {
            if (BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 8192;
            }
        }

        // Electro Shot
        if (MoveID == MOVE193_ELECTRO_SHOT)
        {
            if (ServerEvent_GetWeather(a1) != 2 && AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return 0;
            }
        }

        if (MoveID == MOVE282_KNOCK_OFF)
        {
            if (HandlerCommon_CheckIfCanStealPokeItem(a1, AttackingMon->ID, DefendingMon->ID) && DefendingMon->HeldItem)
            {
                return 8192;
            }
        }

        // //k::print("\nCheck #4");
        //  Hex, Beat Up, Infernal Parade, Barb Barrage
        if (MoveID == MOVE169_INFERNAL_PARADE || MoveID == MOVE212_BARB_BARRAGE || MoveID == MOVE251_BEAT_UP || MoveID == MOVE506_HEX || MoveID == MOVE244_BITTER_MALICE)
        {
            if (BattleMon_GetStatus(DefendingMon))
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #5");
        //  Acrobatics
        if (MoveID == MOVE512_ACROBATICS)
        {
            if (!AttackingMon->HeldItem || AttackingMon->HeldItem == IT0556_FLYING_GEM)
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #6");
        //  All 2 hit moves
        if (MoveID == MOVE003_DOUBLE_SLAP || MoveID == MOVE022_VINE_WHIPS || MoveID == MOVE458_DOUBLE_HIT || MoveID == MOVE024_DOUBLE_KICK || MoveID == MOVE011_DUAL_WINGBEAT || MoveID == MOVE041_TWINEEDLE || MoveID == MOVE155_BONEMERANG || MoveID == MOVE544_GEAR_GRIND || MoveID == MOVE530_DUAL_CHOP)
        {
            return 8192;
        }
        // //k::print("\nCheck #7");
        //  All 3 hit moves
        if (MoveID == MOVE167_TRIPLE_KICK || MoveID == MOVE471_TRIPLE_DIVE || MoveID == MOVE470_TRIPLE_AXEL)
        {
            return 12288;
        }
        // //k::print("\nCheck #8");
        //  Brine
        if (MoveID == MOVE362_BRINE)
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
        if (MoveID == MOVE514_RETALIATE)
        {
            if (checkRetaliate(a1, AttackingMon->ID, 1u))
            {
                // //k::printf("\nWe have triggered this effect for retaliate with turn AI\n");
                return 8192;
            }
        }

        // First Impression
        if (MoveID == MOVE373_1ST_IMPRESSION)
        {
            if (BattleMon_GetConditionFlag(AttackingMon, CONDITIONFLAG_ACTIONDONE))
            {
                return 0;
            }
        }

        // //k::print("\nCheck #9");
        //  Facade
        if (MoveID == MOVE263_FACADE)
        {
            if (BattleMon_GetStatus(AttackingMon))
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #10");
        //  Wake Up Slap and Dream Eater
        if (MoveID == MOVE358_WAKE_UP_SLAP || MoveID == MOVE138_DREAM_EATER)
        {
            if (PersonalCheckIfMoveCondition(DefendingMon, CONDITION_SLEEP))
            {
                return 8192;
            }
        }
        // //k::print("\nCheck #11");
        //  autocrit moves
        // if (MoveID == MOVE006_PAY_DAY || MoveID == MOVE524_FROST_BREATH || MoveID == MOVE346_WICKED_BLOW || MoveID == MOVE190_OCTAZOOKA || MoveID == MOVE480_STORM_THROW)
        // {
        //     if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL075_SHELL_ARMOR || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL004_BATTLE_ARMOR)
        //     {
        //         return 4096;
        //     }
        //     if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL097_SNIPER)
        //     {
        //         return 12288;
        //     }
        //     else
        //     {
        //         return 8192;
        //     }
        // }
        // //k::print("\nCheck #12");
        //  All multihit moves
        if (MoveID == MOVE004_COMET_PUNCH || MoveID == MOVE031_RAZOR_WINDS || MoveID == MOVE042_PIN_MISSILE ||
            MoveID == MOVE131_SPIKE_CANNON || MoveID == MOVE140_BARRAGE || MoveID == MOVE154_FURY_SWIPES || MoveID == MOVE198_BONE_RUSH ||
            MoveID == MOVE292_ARM_THRUST || MoveID == MOVE331_BULLET_SEED || MoveID == MOVE333_ICICLE_SPEAR || MoveID == MOVE350_ROCK_BLAST ||
            MoveID == MOVE541_TAIL_SLAP || MoveID == MOVE378_SCALE_SHOT)
        {
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL092_SKILL_LINK)
            {
                return 20480;
            }
            else if (AttackingMon->HeldItem == IT0317_LOADED_DICE)
            {
                return 16384;
            }
            else
            {
                return 8192;
            }
        }
        // Hyper Beam
        if (MoveID == MOVE063_HYPER_BEAM)
        {
            if (BattleMon_GetPreviousMove(AttackingMon) == MOVE063_HYPER_BEAM && !BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 0;
            }
        }

        // Giga Impact
        if (MoveID == MOVE416_GIGA_IMPACT)
        {
            if (BattleMon_GetPreviousMove(AttackingMon) == MOVE416_GIGA_IMPACT && !BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 0;
            }
        }

        // Stomping Tantrum / Uproar / Seething Chill / Thrash / Temper Flare
        if (MoveID == MOVE046_STOMPING_TANTRUM || MoveID == MOVE253_UPROAR || MoveID == MOVE218_TEMPER_FLARE || MoveID == MOVE220_SEETHING_COLD || MoveID == MOVE037_THRASH)
        {
            if (BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 8192;
            }
        }

        // //k::print("\nCheck #13");
        if (MoveID == MOVE311_WEATHER_BALL)
        {
            if (ServerEvent_GetWeather(a1) > 0)
            {
                return 8192;
            }
        }
        // Payback, Revenge, and Avalanche
        if (MoveID == MOVE371_PAYBACK || MoveID == MOVE279_REVENGE || MoveID == MOVE419_AVALANCHE)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) < Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // Spit Up
        if (MoveID == MOVE255_SPIT_UP)
        {
            if (!PML_ItemIsBerry(AttackingMon->HeldItem))
            {
                return 0;
            }
        }

        if (MoveID == MOVE282_KNOCK_OFF)
        {
            if (BattleMon_GetHeldItem(DefendingMon) && !HandlerCommon_CheckIfCanStealPokeItem(a1, AttackingMon->ID, DefendingMon->ID))
            {
                return 6144;
            }
        }

        if (MoveID == MOVE478_POWER_TRIP || MoveID == MOVE500_STORED_POWER)
        {
            int total;
            int temp;
            total = 0;
            for (int i = 0; i < 7; ++i)
            {
                temp = BattleMon_GetValue(AttackingMon, BattleMonValues[i]) - 6;
                if (temp > 0)
                {
                    total += temp;
                }
            }

            if (total)
            {
                return 4096 + (2048 * total);
            }
        }

        return 4096;
    }

    // SOURCE OF THE CRASH IS THIS FUNCTION //

    int THUMB_BRANCH_SAFESTACK_Handler_SimulationDamage(ServerFlow *a1, int a2, int a3, int a4, bool isSimulation, bool something)
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
        int critFlag;
        int v17;

        int a4check;

        AttackingMon = PokeCon_GetBattleMon(a1->pokeCon, a2);
        DefendingMon = PokeCon_GetBattleMon(a1->pokeCon, a3);

        if (!a4)
        {
            return 0;
        }

        // Checks for Static Damage Moves
        if (a4 == MOVE101_NIGHT_SHADE && !BattleMon_HasType(DefendingMon, TYPE_NORMAL))
        {
            return AttackingMon->Level;
        }
        else if (a4 == MOVE069_SEISMIC_TOSS && (!BattleMon_HasType(DefendingMon, TYPE_GHOST) || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL113_SCRAPPY))
        {
            return AttackingMon->Level;
        }
        else if (a4 == MOVE149_PSYWAVE && !BattleMon_HasType(DefendingMon, TYPE_DARK))
        {
            return AttackingMon->Level;
        }
        else if (a4 == MOVE162_SUPER_FANG && (!BattleMon_HasType(DefendingMon, TYPE_GHOST) || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL113_SCRAPPY))
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
            if (a4 == MOVE383_COPYCAT && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL158_PRANKSTER)
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
            else if (a4 == MOVE267_NATURE_POWER)
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

        if (a4check == MOVE165_STRUGGLE)
        {
            ((MoveParam *)moveParam)->moveType = 17;
        }
        if (a4check == MOVE311_WEATHER_BALL)
        {
            v17 = ServerEvent_GetWeather(a1);
            if (v17 == 1)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE053_FLAMETHROWER);
                ((MoveParam *)moveParam)->moveType = TYPE_FIRE;
            }
            else if (v17 == 2)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE057_SURF);
                ((MoveParam *)moveParam)->moveType = TYPE_WATER;
            }
            else if (v17 == 3)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE058_ICE_BEAM);
                ((MoveParam *)moveParam)->moveType = TYPE_ICE;
            }
            else if (v17 == 4)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE408_POWER_GEM);
                ((MoveParam *)moveParam)->moveType = TYPE_ROCK;
            }
        }

        if (a4check == MOVE363_NATURAL_GIFT)
        {
            if (PML_ItemIsBerry(BattleMon_GetHeldItem(AttackingMon)))
            {
                Types Type = (Types)ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_TYPE);
                if (IsEqual(Type, TYPE_FIGHTING))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE280_BRICK_BREAK);
                }
                else if (IsEqual(Type, TYPE_FLYING))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE332_AERIAL_ACE);
                }
                else if (IsEqual(Type, TYPE_FAIRY))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE066_PLAY_ROUGH);
                }
                else if (IsEqual(Type, TYPE_FIRE))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE053_FLAMETHROWER);
                }
                else if (IsEqual(Type, TYPE_WATER))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE057_SURF);
                }
                else if (IsEqual(Type, TYPE_ELECTRIC))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE085_THUNDERBOLT);
                }
                else if (IsEqual(Type, TYPE_ROCK))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE408_POWER_GEM);
                }
                else if (IsEqual(Type, TYPE_GROUND))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE089_EARTHQUAKE);
                }
                else if (IsEqual(Type, TYPE_STEEL))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE360_GYRO_BALL);
                }
                else if (IsEqual(Type, TYPE_DRAGON))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE337_DRAGON_CLAW);
                }
                else if (IsEqual(Type, TYPE_ICE))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE058_ICE_BEAM);
                }
                else if (IsEqual(Type, TYPE_BUG))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE404_X_SCISSOR);
                }
                else if (IsEqual(Type, TYPE_POISON))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE440_CROSS_POISON);
                }
                else if (IsEqual(Type, TYPE_PSYCHIC))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE060_PSYBEAM);
                }
                else if (IsEqual(Type, TYPE_GHOST))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE421_SHADOW_CLAW);
                }
                else if (IsEqual(Type, TYPE_DARK))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE282_KNOCK_OFF);
                }
                else if (IsEqual(Type, TYPE_GRASS))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE202_GIGA_DRAIN);
                }
                ((MoveParam *)moveParam)->moveType = ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_TYPE);

                if (90 == ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_POWER))
                {
                    ratio = 4608;
                }
                if (100 == ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_POWER))
                {
                    ratio = 5120;
                }
            }
        }
        if (a4check == MOVE546_TECHNO_BLAST)
        {
            if (AttackingMon->HeldItem == IT0119_CHILL_DRIVE)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE058_ICE_BEAM);
                ((MoveParam *)moveParam)->moveType = TYPE_ICE;
            }
            if (AttackingMon->HeldItem == IT0116_DOUSE_DRIVE)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE056_HYDRO_PUMP);
                ((MoveParam *)moveParam)->moveType = TYPE_WATER;
            }
            if (AttackingMon->HeldItem == IT0118_BURN_DRIVE)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE083_FIRE_SPIN);
                ((MoveParam *)moveParam)->moveType = TYPE_FIRE;
            }
            if (AttackingMon->HeldItem == IT0117_SHOCK_DRIVE)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE085_THUNDERBOLT);
                ((MoveParam *)moveParam)->moveType = TYPE_ELECTRIC;
            }
        }
        if (a4check == MOVE327_SKY_UPPERCUT || a4check == MOVE357_FREEZE_DRY)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAltered(((MoveParam *)moveParam)->moveType, BattleMon_GetPokeType(DefendingMon));
        }

        if (a4check == MOVE533_SACRED_SWORD)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAlteredSacredSword(((MoveParam *)moveParam)->moveType, BattleMon_GetPokeType(DefendingMon));
        }
        if (((MoveParam *)moveParam)->moveType == TYPE_FIRE && BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL021_WELL_BAKED_BODY)
        {
            ratio = 0;
        }
        if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL015_THUNDER_ARMOR || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL031_LIGHTNING_ROD) && ((MoveParam *)moveParam)->moveType == TYPE_ELECTRIC)
        {
            ratio = 0;
        }
        if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL114_STORM_DRAIN || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL087_DRY_SKIN) && ((MoveParam *)moveParam)->moveType == TYPE_WATER)
        {
            ratio = 0;
        }
        if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL006_BULLETPROOF && isInArray(a4check, 0))
        {
            ratio = 0;
        }
        if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL051_WIND_RIDER && isInArray(a4check, 1))
        {
            ratio = 0;
        }

        if (a4check == MOVE006_PAY_DAY || a4check == MOVE524_FROST_BREATH || a4check == MOVE346_WICKED_BLOW || a4check == MOVE190_OCTAZOOKA || a4check == MOVE480_STORM_THROW || a4check == MOVE163_SLASH)
        {
            critFlag = 1;
        }
        else
        {
            critFlag = 0;
        }

        ServerEvent_CalcDamage(
            a1,
            AttackingMon,
            DefendingMon,
            (MoveParam *)moveParam,
            TypeEffectiveness,
            ratio,
            critFlag,
            v15 == 0,
            &v12);
        --a1->SimulationCounter;

        if (a4check == MOVE228_PURSUIT && (v12 * 2) >= DefendingMon->CurrentHP)
        {
            if (RandomInRange(1, 100) >= 75)
            {
                v12 *= 2;
            }
        }

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
        if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL101_TECHNICIAN)
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
        if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL104_MOLD_BREAKER && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL164_TERAVOLT && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL163_TURBOBLAZE)
        {
            // Heatproof
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL085_HEATPROOF && Type == TYPE_FIRE)
            {
                value *= .25;
            }
            // Thick Fat
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL047_THICK_FAT && (Type == TYPE_FIRE || Type == TYPE_ICE))
            {
                value *= .5;
            }
            // Dry Skin
            if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL087_DRY_SKIN || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL017_FLUFFY) && Type == TYPE_FIRE)
            {
                value *= 2;
            }
            // Toxic Boost
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL137_TOXIC_BOOST && Type == TYPE_POISON)
            {
                value *= .5;
            }
            // Filter and Solid Rock
            // if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL111_FILTER || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL116_SOLID_ROCK) && TypeEffectivenessVsMon > 3)
            // {
            //      value *= .75;
            // }

            if ((BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL110_TENACITY) && TypeEffectivenessVsMon < 3)
            {
                value *= 2;
            }
            // Swift Swim
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL033_SWIFT_SWIM && Type == TYPE_WATER)
            {
                value *= .5;
            }
            // Slush Rush
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL134_SLUSH_RUSH && Type == TYPE_ICE)
            {
                value *= .5;
            }
            // Sand Force and Sand Rush
            if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL146_SAND_RUSH || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL159_SAND_FORCE) && Type == TYPE_ROCK)
            {
                value *= .5;
            }

            // Justified
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL154_JUSTIFIED && Type == TYPE_DARK)
            {
                value *= .5;
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

        if (MoveID == MOVE474_VENOSHOCK)
        {
            if (PersonalCheckIfMoveCondition(DefendingMon, CONDITION_POISON))
            {
                return value * 2;
            }
        }

        // Meteor Beam, Skull Bash, Sky Attack
        else if (MoveID == MOVE130_SKULL_BASH || MoveID == MOVE553_METEOR_BEAM || MoveID == MOVE143_SKY_ATTACK)
        {
            if (AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return value / 2;
            }
        }

        // Reversal and Flail
        // Set base power to 20
        else if (MoveID == MOVE175_FLAIL || MoveID == MOVE179_REVERSAL)
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
        else if (MoveID == MOVE323_WATER_SPOUT || MoveID == MOVE284_ERUPTION)
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
        else if (MoveID == MOVE486_ELECTRO_BALL)
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
        else if (MoveID == MOVE360_GYRO_BALL)
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

        // KNOCK OFF
        // else if (MoveID == MOVE282_KNOCK_OFF)
        // {
        //     if (HandlerCommon_CheckIfCanStealPokeItem(server, AttackingMon->ID, DefendingMon->ID) && DefendingMon->HeldItem)
        //     {
        //         return value * 1.5;
        //     }
        // }

        // Electro Shot
        else if (MoveID == MOVE193_ELECTRO_SHOT)
        {
            if (BattleField_GetWeather() != 2 && AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return value / 2;
            }
        }

        // Solarbeam and Solar Blade
        else if (MoveID == MOVE076_SOLAR_BEAM || MoveID == MOVE554_SOLAR_BLADE)
        {
            if (BattleField_GetWeather() != 1 && AttackingMon->HeldItem != IT0271_POWER_HERB && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL034_CHLOROPHYLL && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL094_SOLAR_POWER && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL122_FLOWER_GIFT)
            {
                return value / 2;
            }
        }
        else if (MoveID == MOVE506_HEX || MoveID == MOVE212_BARB_BARRAGE || MoveID == MOVE251_BEAT_UP || MoveID == MOVE244_BITTER_MALICE || MoveID == MOVE169_INFERNAL_PARADE)
        {
            if (BattleMon_GetStatus(DefendingMon))
            {
                return value * 2;
            }
        }
        // Acrobatics
        else if (MoveID == MOVE512_ACROBATICS)
        {
            if (!AttackingMon->HeldItem || AttackingMon->HeldItem == IT0556_FLYING_GEM)
            {
                return value * 2;
            }
        }
        else if (MoveID == MOVE003_DOUBLE_SLAP || MoveID == MOVE022_VINE_WHIPS || MoveID == MOVE458_DOUBLE_HIT || MoveID == MOVE024_DOUBLE_KICK || MoveID == MOVE011_DUAL_WINGBEAT || MoveID == MOVE041_TWINEEDLE || MoveID == MOVE155_BONEMERANG || MoveID == MOVE544_GEAR_GRIND || MoveID == MOVE530_DUAL_CHOP)
        {
            return value * 2;
        }
        // //k::print("\nCheck #7");
        //  All 3 hit moves
        else if (MoveID == MOVE167_TRIPLE_KICK || MoveID == MOVE471_TRIPLE_DIVE || MoveID == MOVE470_TRIPLE_AXEL)
        {
            return value * 3;
        }
        // Wake Up Slap and Dream Eater
        else if (MoveID == MOVE358_WAKE_UP_SLAP || MoveID == MOVE138_DREAM_EATER)
        {
            if (PersonalCheckIfMoveCondition(DefendingMon, CONDITION_SLEEP))
            {
                return value * 2;
            }
        }

        else if (MoveID == MOVE514_RETALIATE)
        {
            if (checkRetaliate(server, AttackingMon->ID, 0))
            {
                // //k::printf("\nWe have triggered this effect for retaliate with switch AI\n");
                return value * 2;
            }
        }
        // autocrit moves
        else if (MoveID == MOVE006_PAY_DAY || MoveID == MOVE163_SLASH || MoveID == MOVE480_STORM_THROW || MoveID == MOVE524_FROST_BREATH || MoveID == MOVE190_OCTAZOOKA || MoveID == MOVE346_WICKED_BLOW)
        {
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL075_SHELL_ARMOR || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL004_BATTLE_ARMOR)
            {
                return value;
            }
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL097_SNIPER)
            {
                return value * 2 * 1.5;
            }
            else
            {
                return value * 2;
            }
        }
        else if (MoveID == MOVE004_COMET_PUNCH || MoveID == MOVE031_RAZOR_WINDS || MoveID == MOVE042_PIN_MISSILE ||
                 MoveID == MOVE131_SPIKE_CANNON || MoveID == MOVE140_BARRAGE || MoveID == MOVE154_FURY_SWIPES || MoveID == MOVE198_BONE_RUSH ||
                 MoveID == MOVE292_ARM_THRUST || MoveID == MOVE331_BULLET_SEED || MoveID == MOVE333_ICICLE_SPEAR || MoveID == MOVE350_ROCK_BLAST ||
                 MoveID == MOVE541_TAIL_SLAP || MoveID == MOVE378_SCALE_SHOT)
        {
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL092_SKILL_LINK)
            {
                return value * 5;
            }
            else if (AttackingMon->HeldItem == IT0317_LOADED_DICE)
            {
                return value * 4;
            }
            else
            {
                return value * 2;
            }
        }
        else if (MoveID == MOVE373_1ST_IMPRESSION)
        {
            if (BattleMon_GetConditionFlag(AttackingMon, CONDITIONFLAG_ACTIONDONE))
            {
                return value * 0;
            }
        }

        else if (MoveID == MOVE371_PAYBACK || MoveID == MOVE419_AVALANCHE || MoveID == MOVE279_REVENGE)
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) < Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value * 2;
            }
        }

        else if (MoveID == MOVE282_KNOCK_OFF)
        {
            if (BattleMon_GetHeldItem(DefendingMon) && !HandlerCommon_CheckIfCanStealPokeItem(server, AttackingMon->ID, DefendingMon->ID))
            {
                return value * 1.5;
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

        ability = BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY);

        if (Type == TYPE_WATER && (ability == ABIL114_STORM_DRAIN || ability == ABIL011_WATER_ABSORB || ability == ABIL087_DRY_SKIN))
        {
            return true;
        }
        if (Type == TYPE_GROUND && (ability == ABIL026_LEVITATE))
        {
            return true;
        }
        if (Type == TYPE_ELECTRIC && (ability == ABIL010_VOLT_ABSORB || ability == ABIL015_THUNDER_ARMOR || ability == ABIL078_MOTOR_DRIVE || ability == ABIL031_LIGHTNING_ROD))
        {
            return true;
        }
        if (Type == TYPE_GRASS && (ability == ABIL157_SAP_SIPPER))
        {
            return true;
        }
        if (Type == TYPE_FIRE && ((ability == ABIL018_FLASH_FIRE) || ability == ABIL021_WELL_BAKED_BODY))
        {
            return true;
        }
        if (ability == ABIL043_AMPLIFIER && getMoveFlag(MoveID, FLAG_SOUND))
        {
            return true;
        }
        if (ability == ABIL006_BULLETPROOF && isInArray(MoveID, 0))
        {
            return true;
        }
        if (ability == ABIL051_WIND_RIDER && isInArray(MoveID, 1))
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
                            if (PML_MoveIsDamaging(ID) && ID != MOVE120_SELF_DESTRUCT && ID != MOVE153_EXPLOSION)
                            {
                                Type = PML_MoveGetType(ID);
                                BasePower = PML_MoveGetBasePower(ID);
                                // k:Printf("\nBase Power from %d is %d\n", ID, BasePower);

                                // Weather Ball Checks
                                if (ID == MOVE311_WEATHER_BALL)
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
                                if (ID == MOVE267_NATURE_POWER)
                                {
                                    int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(a1->mainModule->server));

                                    // //k::printf("\n\nThe Battle Terrain is %d\n\n", BattleTerrain);

                                    if (BattleTerrain == 5u)
                                    {
                                        ID = 402;
                                    }
                                    else if (BattleTerrain == 11u)
                                    {
                                        ID = 89;
                                    }
                                    else if (BattleTerrain == 0xCu)
                                    {
                                        ID = 56;
                                    }
                                    else if (BattleTerrain == 7u)
                                    {
                                        ID = 59;
                                    }
                                    else if (BattleTerrain == 9u)
                                    {
                                        ID = 426;
                                    }
                                    else if (BattleTerrain == 0xAu)
                                    {
                                        ID = 157;
                                    }
                                    else if (BattleTerrain == 0xDu)
                                    {
                                        ID = 58;
                                    }
                                    else
                                    {
                                        ID = 161;
                                    }
                                }

                                if (ID == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(MonData)))
                                {
                                    Type = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_TYPE);
                                    BasePower = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_POWER);
                                }

                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_ELECTRIC;
                                    BasePower *= 1.2;
                                }
                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_ICE;
                                    BasePower *= 1.2;
                                }
                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL060_AERILATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_FLYING;
                                    BasePower *= 1.2;
                                }
                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL107_PIXILATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_FAIRY;
                                    BasePower *= 1.2;
                                }
                                // //k::printf("\nBase Power from %d is %d, and the Type is %d\n", ID, BasePower, Type);

                                // if (BasePower < 0xA)
                                // {
                                //     BasePower = 60;
                                // }
                                if (ID == MOVE327_SKY_UPPERCUT || ID == MOVE357_FREEZE_DRY || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL007_CORROSION)
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    // //k::printf("\n 2. TypeEffectivenessVsMon is: %d for Move %d \n", TypeEffectivenessVsMon, a4);
                                }
                                else if (ID == MOVE533_SACRED_SWORD)
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAlteredSacredSword(Type, PokeType);
                                }
                                else
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);
                                }

                                if (!(BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL104_MOLD_BREAKER || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL163_TURBOBLAZE || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL164_TERAVOLT) && CheckIfImmuneAbility(Type, ID, a4))
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
        int temp;
        int Type; // [sp+4h] [bp-24h]

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
        if (wazaId == MOVE267_NATURE_POWER)
        {
            int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(a1->mainModule->server));

            // //k::printf("\n\nThe Battle Terrain is %d\n\n", BattleTerrain);

            if (BattleTerrain == 5u)
            {
                wazaId = 402;
            }
            else if (BattleTerrain == 11u)
            {
                wazaId = 89;
            }
            else if (BattleTerrain == 0xCu)
            {
                wazaId = 56;
            }
            else if (BattleTerrain == 7u)
            {
                wazaId = 59;
            }
            else if (BattleTerrain == 9u)
            {
                wazaId = 426;
            }
            else if (BattleTerrain == 0xAu)
            {
                wazaId = 157;
            }
            else if (BattleTerrain == 0xDu)
            {
                wazaId = 58;
            }
            else
            {
                wazaId = 161;
            }
        }

        if (wazaId == MOVE383_COPYCAT && BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL158_PRANKSTER)
        {
            int actualMove = Handler_GetPrevUsedMove(BattleServer_GetServerFlow(a1->mainModule->server));
            if (actualMove && !j_j_IsNotAllowedCopycatMove(actualMove))
            {
                wazaId = actualMove;
            }
        }
        IsDamaging = PML_MoveIsDamaging(Param);
        Type = PML_MoveGetType(wazaId);
        PokeType = BattleMon_GetPokeType(a3);

        if (wazaId == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(a2)))
        {
            Type = ItemGetParam(BattleMon_GetHeldItem(a2), ITSTAT_NATURAL_GIFT_TYPE);
        }

        if (BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL107_PIXILATE && Type == TYPE_NORMAL)
        {
            Type = TYPE_FAIRY;
        }
        if (BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
        {
            Type = TYPE_ICE;
        }
        if (BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
        {
            Type = TYPE_ELECTRIC;
        }
        if (BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL060_AERILATE && Type == TYPE_NORMAL)
        {
            Type = TYPE_FLYING;
        }
        if (BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL096_NORMALIZE)
        {
            Type = TYPE_NORMAL;
        }

        if (wazaId == MOVE327_SKY_UPPERCUT || wazaId == MOVE357_FREEZE_DRY || BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL007_CORROSION)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAltered(Type, PokeType);
            // //k::printf("\n 2. TypeEffectivenessVsMon is: %d for Move %d \n", TypeEffectiveness, wazaId);
        }
        else if (wazaId == MOVE533_SACRED_SWORD || BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL039_INNER_FOCUS || BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL096_NORMALIZE || BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL113_SCRAPPY)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAlteredSacredSword(Type, PokeType);
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
            if (BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL110_TENACITY)
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

    // int CompareCategory(void *a1, TrainerAIEnv *a2)
    // {
    //     int TargetsPreviousMoveID;
    //     int AttackersCurrentMoveID;

    //     TargetsPreviousMoveID = BattleMon_GetPreviousMoveID(a2->defender);
    //     AttackersCurrentMoveID = a2->moveID;
    //     if (TargetsPreviousMoveID)
    //     {
    //         a2->param = AIGetMoveParam(a2, TargetsPreviousMoveID, MVDATA_CATEGORY);
    //     }
    //     else
    //     {
    //         a2->param = 0;
    //     }
    // }

    int CheckTargetMoves(BattleMon *a1)
    {
        int MoveCount;
        int LoopMoveID;
        int LoopMoveCategory;
        int LoopMoveCategoryCheck;
        int i;

        MoveCount = BattleMon_GetMoveCount(a1);
        LoopMoveCategoryCheck = 0;
        do
        {
            LoopMoveID = Move_GetID(a1, i);
            LoopMoveCategory = PML_MoveGetParam(LoopMoveID, MVDATA_CATEGORY);
            if (!LoopMoveCategoryCheck && !PML_MoveIsDamaging(LoopMoveID) && Move_GetPP(a1, i))
            {
                LoopMoveCategoryCheck = LoopMoveCategory;
            }

            if (LoopMoveCategory != LoopMoveCategoryCheck)
            {

                if (BattleMon_GetValue(a1, VALUE_ATTACK_STAT) >= BattleMon_GetValue(a1, VALUE_SPECIAL_ATTACK_STAT))
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
            i++;
        } while (i < MoveCount);
        return LoopMoveCategoryCheck;
    }

    int THUMB_BRANCH_AI094_GetPreviousMoveCategory(void *a1, TrainerAIEnv *a2)
    {
        int PreviousMoveID; // r1
        int LoopMoveID;
        int LoopMoveCategory;
        u32 LoopMoveCategoryCheck;

        PreviousMoveID = BattleMon_GetPreviousMoveID(a2->defender);
        if (PreviousMoveID && !PML_MoveIsDamaging(PreviousMoveID))
        {
            a2->param = AIGetMoveParam(a2, PreviousMoveID, MVDATA_CATEGORY);
        }
        else
        {
            a2->param = CheckTargetMoves(a2->defender);
        }

        return a2->result;
    }

    // This function iterates through each of the defender Pokemon's moves to see if any of them are a OHKO
    // or a 2HKO if the defender is faster.
    // It is invoked when determining whether or not to use a set up move

    // int THUMB_BRANCH_AI072_Nop(void *a1, TrainerAIEnv *a2)
    // {

    //     int i = 0;
    //     int MoveCount = BattleMon_GetMoveCount(a2->defender);
    //     int currentHp = BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);

    //     do
    //     {
    //         int damage = Handler_SimulationDamage(a2->serverFlow,
    //                                               BattleMon_GetID(a2->defender),
    //                                               BattleMon_GetID(a2->attacker),
    //                                               Move_GetID(a2->defender, i));

    //         // If the target is faster the the Pokemon using the set up move, doubles the damage
    //         // now checking for a 2HKO
    //         if (Handler_CalculateSpeed(a2->serverFlow, a2->defender, 1) > Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
    //         {
    //             damage *= 2;
    //         }

    //         // If currentHP is less than or equal to damage, performs the jump
    //         if (AIConditionalJump(a1, 6, currentHp, damage))
    //         {
    //             break;
    //         }

    //         // Else, incremenets and checks the next move.
    //         i++;
    //     } while (i < MoveCount);

    //     return a2->result;
    // }

    int THUMB_BRANCH_AI072_Nop(void *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        u8 opposingPokePos[5];
        unsigned int k;

        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);

        for (k = 0; k < pokeCount; (k + 1))
        {
            int i = 0;
            int MoveCount = BattleMon_GetMoveCount(a2->defender);
            int currentHp = BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);

            do
            {
                int damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(a2->defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(a2->defender, i));

                // If the target is faster the the Pokemon using the set up move, doubles the damage
                // now checking for a 2HKO
                if (Handler_CalculateSpeed(a2->serverFlow, a2->defender, 1) > Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
                {
                    damage *= 2;
                }

                // If currentHP is less than or equal to damage, performs the jump
                if (AIConditionalJump(a1, 6, currentHp, damage))
                {
                    k = pokeCount;
                    break;
                }

                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        return a2->result;
    }

    // Checks Damage Threshold for negligible damage
    // USED FOR SET UP
    int THUMB_BRANCH_A1060_Nop(void *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        u8 opposingPokePos[5];
        unsigned int k;

        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);

        for (k = 0; k < pokeCount; (k + 1))
        {
            int i = 0;
            int MoveCount = BattleMon_GetMoveCount(a2->defender);
            // int currentHp = BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);
            int currentHp = DivideMaxHPZeroCheck(a2->attacker, 4u);
            do
            {
                int damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(a2->defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(a2->defender, i));

                // If the target is faster the the Pokemon using the set up move, doubles the damage
                // now checking for a 2HKO
                if (Handler_CalculateSpeed(a2->serverFlow, a2->defender, 1) > Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
                {
                    damage *= 2;
                }

                // If currentHP is less than or equal to damage, performs the jump
                if (AIConditionalJump(a1, 6, currentHp, damage))
                {
                    k = pokeCount;
                    break;
                }

                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        return a2->result;
    }

    // USED FOR DEBUFFING MOVES
    int THUMB_BRANCH_A1062_Nop(void *a1, TrainerAIEnv *a2)
    {
        int i = 0;
        int MoveCount = BattleMon_GetMoveCount(a2->defender);
        int currentHp = DivideMaxHPZeroCheck(a2->attacker, 4u);
        // BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);

        do
        {
            int damage = Handler_SimulationDamage(a2->serverFlow,
                                                  BattleMon_GetID(a2->defender),
                                                  BattleMon_GetID(a2->attacker),
                                                  Move_GetID(a2->defender, i));

            // If the target is faster the the Pokemon using the set up move, doubles the damage
            // now checking for a 2HKO
            if (Handler_CalculateSpeed(a2->serverFlow, a2->defender, 1) > Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
            {
                damage *= 2;
            }

            // If currentHP is less than or equal to damage, performs the jump
            if (AIConditionalJump(a1, 6, currentHp, damage))
            {
                break;
            }

            // Else, incremenets and checks the next move.
            i++;
        } while (i < MoveCount);

        return a2->result;
    }

    int THUMB_BRANCH_A1063_Nop(void *a1, TrainerAIEnv *a2)
    {
        return a2->result;
    }
}
