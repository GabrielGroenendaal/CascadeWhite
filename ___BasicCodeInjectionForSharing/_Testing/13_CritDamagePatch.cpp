#include "../swan-master/swantypes.h"
#include "../kPrint.h"

#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long
extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

bool IsEqual(int a1, int a2)
{
    char *c1 = (char *)&a1;
    char *c2 = (char *)&a2;

    for (u16 i = 0; i < 4; ++i)
    {
        if (c1[i] != c2[i])
            return false;
    }
    return true;
}

unsigned short int &LOWORD(unsigned int &x)
{
    return *(reinterpret_cast<unsigned short int *>(&x) + 0);
}

// extern "C" int THUMB_BRANCH_PlayerSave_GetBlockSize()
// {
//   return 168;
// };

extern "C" int THUMB_BRANCH_sub_200AE9C(int *a1)
{
    int a5 = 0x3C;
    return *(a1 + 596);
}

extern "C"
{

    struct SWAN_ALIGNED(4) m_record
    {
        u32 Turn;
        __int16 MoveID;
        u8 PokeID;
        u8 fEffective;
    };
    enum BattleStyle
#ifdef __cplusplus
        : u32
#endif
    {
        BTL_STYLE_SINGLE = 0,
        BTL_STYLE_DOUBLE = 1,
        BTL_STYLE_TRIPLE = 2,
        BTL_STYLE_ROTATION = 3
    };

    struct MoveRecord
    {
        u32 ptr;
        m_record record[120];
    };

    struct FaintRecordUnit
    {
        u8 count;
        u8 fExpChecked[24];
        u8 faintedMonIDs[24];
    };

    struct FaintRecord
    {
        FaintRecordUnit turnRecord[4];
    };

    enum BattleResult
    {
        BTL_RESULT_DEFEAT = 0x0,
        BTL_RESULT_VICTORY = 0x1,
        BTL_RESULT_DRAW = 0x2,
        BTL_RESULT_FLEE = 0x3,
        BTL_RESULT_FLEE_FOE = 0x4,
        BTL_RESULT_CAPTURE = 0x5,
        BTL_RESULT_6 = 0x6,
    };

    struct EscapeInfo
    {
        u32 count;
        u8 clientID[4];
    };

    struct SWAN_ALIGNED(4) PokeSet
    {
        void *mons[6];
        u16 damage[6];
        u16 substituteDamage[6];
        u8 damageType[6];
        u16 sortWork[6];
        u8 count;
        u8 countMax;
        u8 getIdx;
        u8 targetPosCount;
    };

    struct PosPokeState
    {
        u8 enabled;
        u8 clientID;
        u8 monID;
    };

    struct PosPoke
    {
        PosPokeState positions[6];
        u8 lastPos[24];
    };

    struct SWAN_ALIGNED(4) HandlerParam_StrParams
    {
        u16 strID;
        __int16 flags;
        int type;
        int args[8];
    };

    struct SWAN_ALIGNED(2) CalcExpWork
    {
        u32 level;
        u8 isBoosted;
        u8 hp;
        u8 atk;
        u8 def;
        u8 spatk;
        u8 spdef;
        u8 spe;
    };

    struct EffectivenessCounter
    {
        u16 NoEffectHits;
        u16 SuperEffectiveHits;
        u16 NotVeryEffectiveHits;
        u16 OpponentNoEffectHits;
        u16 OpponentSuperEffectiveHits;
        u16 OpponentNotVeryEffectiveHits;
    };

    struct EffectivenessRecorder
    {
        int effectiveness[24];
    };
    struct SWAN_ALIGNED(2) BattleFieldStatus
    {
        u32 BattleBGID;
        unsigned int BattlePedestalID;
        unsigned char BtlWeather;
        u8 Season;
        u16 ZoneID;
        u8 Hour;
        u8 Minute;
        char field_E;
        char field_F;
    };
    struct SWAN_ALIGNED(2) StrBuf
    {
        u16 CharCapacity;
        u16 CharCount;
        u32 Magic;
        __int16 String[];
    };

    struct TrainerBattleSetup
    {
        _DWORD TrID;
        _DWORD TrClass;
        _DWORD TrAIBits;
        u16 TrItems[4];
        StrBuf *TrainerName;
        __int16 field_18[4];
        __int16 field_20[4];
    };
    struct SWAN_ALIGNED(4) BtlSetup
    {
        u32 btlType;
        u32 BtlStyle;
        BattleFieldStatus m_FieldStatus;
        u16 BattleBGMID;
        __int16 WinBGMID;
        int field_1C;
        char commMode;
        char field_21;
        u8 BtlSetupType;
        char field_23;
        void *Parties[4];
        int m_PlayerInfo;
        int field_38;
        int field_3C;
        int field_40;
        u8 field_44[4];
        TrainerBattleSetup *TrainerSetups[4];
        int field_58;
        int field_5C;
        int field_60;
        int field_64;
        int field_68;
        int field_6C;
        void *gameData;
        void *m_TrainerData;
        int *m_ItemWork;
        int field_7C;
        int m_Dex;
        int m_RecordData;
        int field_88;
        int field_8C;
        int field_90;
        char field_94;
        char field_95;
        char field_96;
        char field_97;
        char BadgeCount;
        char field_99;
        char field_9A;
        char field_9B;
        int field_9C;
        __int16 field_A0;
        __int16 field_A2;
        int EarnedMoney;
        BattleResult battleResult;
        char CapturedPkmIdx;
        char field_AD;
        __int16 field_AE;
        void *field_B0;
        int field_B4;
        int field_B8;
        int field_BC;
        int field_C0;
        int field_C4;
        int field_C8;
        int field_CC;
        u16 HPSum;
        u8 CurrentTurn;
        u8 SwitchCount;
        u8 NoEffectHits;
        u8 SuperEffectiveHits;
        u8 NotVeryEffectiveHits;
        u8 OpponentNoEffectHits;
        u8 OpponentNotVeryEffectiveHits;
        u8 BattlesWon;
        u8 OpponentFainted;
        u8 AllyFainted;
        u8 UniqueMovesUsed;
        char field_DD;
        char field_DE;
        u8 field_DF;
        int field_E0;
        int field_E4;
        int field_E8;
        int field_EC;
        int field_F0;
        int field_F4;
        int field_F8;
        int field_FC;
        int field_100[4];
        char field_110;
        int field_114;
        int field_118;
        int field_11C;
        int field_120;
        int field_124;
        char field_128;
        u8 field_129;
        int field_12C;
        int field_130;
        int field_134;
        __int16 field_138;
        __int16 field_13A;
        u8 KeySystemLevelAdjust;
        char field_13D;
        char field_13E;
        char field_13F;
        int field_140;
        int field_144;
        int field_148;
    };

    struct TrainerParam
    {
        int pTrainerInfo;
        int Name;
        __int16 Class;
        __int16 ID;
        int AIFlags;
        u16 Items[4];
        int field_18;
        int field_1C;
        int field_20;
        int field_24;
    };

    struct SWAN_ALIGNED(32) MainModule
    {
        BtlSetup *btlSetup;
        int *BtlvCore;
        void *server;
        int *clients[4];
        TrainerParam trainerParam[4];
        int playerInfo;
        u8 field_C4[4];
        char pokeconClient[232];
        char pokeconServer[232];
        void *srcParty[4];
        void *srcPartyForServer[4];
        void *tempParty;
        void *battleField;
        void *TempPartyPkm;
        int field_2C4;
        int field_2C8;
        int field_2CC;
        int field_2D0;
        int field_2D4;
        unsigned char gap2D8[260];
        int field_3DC;
        int chatotChatterBlk[4];
        int randomSeed;
        int field_3F4;
        int field_3F8;
        int field_3FC;
        int field_400;
        int field_404;
        int field_408;
        int field_40C;
        int field_410;
        int field_414;
        int field_418;
        int field_41C;
        __int16 field_420;
        SWAN_PACKED SWAN_ALIGNED(1) int field_422;
        char field_426;
        char field_427;
        unsigned __int8 field_428[6];
        char field_42E;
        char field_42F;
        int winMoney;
        int bonusMoney;
        int loseMoney;
        int field_43C;
        __int16 field_440;
        __int16 CmdLimitTime;
        int serverResult;
        EscapeInfo escapeInfo;
        int subproc;
        int field_454;
        int field_458;
        int field_45C;
        int subseq;
        int field_464;
        u16 heapID;
        char field_46A;
        char field_46B;
        char playerClientID;
        char field_46D;
        char field_46E;
        char field_46F;
        char field_470;
        char field_471;
        char CurrentTrainer;
        char field_473;
        int pokestarScriptPtr;
        int pokestarScriptHeapPtr;
        int field_47C;
    };

    union SWAN_ALIGNED(4) ConditionData
    {
        u32 raw;
        void *permanent;
        void *poke;
        void *poketurn;
        void *turn;
    };

    struct StatStageParam
    {
        u8 AttackStage;
        u8 DefenseStage;
        u8 SpAttackStage;
        u8 SpDefenseStage;
        u8 SpeedStage;
        u8 AccuracyStage;
        u8 EvasionStage;
    };

    enum PokeType
    {
        TYPE_NORMAL = 0x0,
        TYPE_FIGHT = 0x1,
        TYPE_FLY = 0x2,
        TYPE_POIS = 0x3,
        TYPE_GROUND = 0x4,
        TYPE_ROCK = 0x5,
        TYPE_BUG = 0x6,
        TYPE_GHOST = 0x7,
        TYPE_STEEL = 0x8,
        TYPE_FIRE = 0x9,
        TYPE_WATER = 0xA,
        TYPE_GRASS = 0xB,
        TYPE_ELEC = 0xC,
        TYPE_PSY = 0xD,
        TYPE_ICE = 0xE,
        TYPE_DRAGON = 0xF,
        TYPE_DARK = 0x10,
        TYPE_FAIRY = 0x11,
        TYPE_NULL = 0x12,
    };

    struct SWAN_ALIGNED(2) MoveCore
    {
        u16 MoveID;
        u8 CurrentPP;
        u8 MaxPP;
        u8 PPUpCount;
        char UsedFlag;
    };

    struct MoveSet
    {
        MoveCore truth;
        MoveCore surface;
        u8 fLinked;
    };
    struct MoveDamageRec
    {
        u16 moveID;
        u16 damage;
        u8 damageType;
        u8 moveType;
        u8 pokeID;
        u8 pokePos;
    };

    struct MailData
    {
        u32 TID;
        _BYTE TrainerGender;
        _BYTE Region;
        _BYTE GameVersion;
        _BYTE byte7;
        char StringContent[16];
        __int16 field_18;
        __int16 field_1A;
        __int16 field_1C;
        _WORD word1E;
        int field_20;
        int field_24;
        int field_28;
        int field_2C;
        int field_30;
        int field_34;
    };
    struct PkmBufferChunk
    {
        char RawData[32];
    };

    struct PkmBuffer
    {
        PkmBufferChunk Chunks[4];
    };

    struct SWAN_ALIGNED(4) BoxPkm
    {
        u32 pid;
        u16 SanityFlags;
        u16 checksum;
        PkmBuffer ContentBuffer;
    };

    struct PartyPkm
    {
        BoxPkm Base;
        u32 StatusCond;
        u8 Level;
        u8 field_8D;
        u16 NowHP;
        u16 MaxHP;
        u16 ATK;
        u16 DEF;
        u16 SPE;
        u16 SPA;
        u16 SPD;
        MailData Mail;
        u32 field_D4;
        u32 field_D8;
    };

    struct SWAN_ALIGNED(4) BattleMon
    {
        PartyPkm *partySrc;
        PartyPkm *disguiseSrc;
        int Experience;
        __int16 Species;
        __int16 MaxHP;
        __int16 CurrentHP;
        __int16 HeldItem;
        __int16 UsedItem;
        __int16 Ability;
        char Level;
        char ID;
        char BaseAttack;
        char flags;
        ConditionData *Conditions[36];
        u8 MoveConditionCounter[36];
        char ConfrontRecCount;
        u8 ConfrontRec[24];
        _BYTE gapE9[5];
        __int16 Attack;
        __int16 Defense;
        __int16 SpecialAttack;
        __int16 SpecialDefense;
        __int16 Speed;
        char Type1;
        char Type2;
        char Sex;
        char field_FB;
        StatStageParam StatStageParam;
        char field_103;
        MoveSet Moves[4];
        __int16 CurrentAbility;
        __int16 Weight;
        char MoveCount;
        char Form;
        char CritStage;
        char UsedMoveCount;
        char PrevMoveType;
        char field_145;
        __int16 TurnCount;
        __int16 AppearedTurn;
        __int16 PreviousMove;
        __int16 PreviousMoveID;
        __int16 ConsecutiveMoveCounter;
        __int16 field_150;
        char prevTargetPos;
        u8 TurnFlag[2];
        u8 ConditionFlag[2];
        u8 Counters[5];
        MoveDamageRec DamageRec[3][6];
        unsigned __int8 DamageRecCount[3];
        char DamageRecTurn;
        char DamageRecPtr;
        char field_1F1;
        __int16 SubstituteHP;
        __int16 comboMoveID;
        char comboPokeID;
        char field_1F7;
    };

    enum BattleEventVar
    {
        VAR_NULL = 0x0,
        VAR_1 = 0x1,
        VAR_MON_ID = 0x2,
        VAR_ATTACKING_MON = 0x3,
        VAR_DEFENDING_MON = 0x4,
        VAR_TARGET_COUNT = 0x5,
        VAR_TARGET_MON_ID = 0x6,
        VAR_7 = 0x7,
        VAR_8 = 0x8,
        VAR_9 = 0x9,
        VAR_A = 0xA,
        VAR_B = 0xB,
        VAR_ACTION = 0xC,
        VAR_POKE_POS = 0xD,
        VAR_ORIGINAL_TARGET = 0xE,
        VAR_PREVIOUS_ABILITY = 0xF,
        VAR_NEXT_ABILITY = 0x10,
        VAR_PRIORITY = 0x11,
        VAR_MOVE_ID = 0x12,
        VAR_MOVE_ID_2 = 0x13,
        VAR_ORIGINAL_MOVE = 0x14,
        VAR_POKE_TYPE = 0x15,
        VAR_MOVE_TYPE = 0x16,
        VAR_MOVE_INDEX = 0x17,
        VAR_MOVE_PRIORITY = 0x18,
        VAR_STAT_STAGE_CHANGE_COUNT = 0x19,
        VAR_MOVE_CATEGORY = 0x1A,
        VAR_TARGET_TYPE = 0x1B,
        VAR_USER_TYPE = 0x1C,
        VAR_CONDITION_ID = 0x1D,
        VAR_CONDITION_ADDRESS = 0x1E,
        VAR_MOVE_EFFECT = 0x1F,
        VAR_VOLUME = 0x20,
        VAR_SEMI_INVULN_TYPE = 0x21,
        VAR_FAIL_CAUSE = 0x22,
        VAR_23 = 0x23,
        VAR_EFFECT_TURN_COUNT = 0x24,
        VAR_DEFAULT_EFFECT_CHANCE = 0x25,
        VAR_EFFECT_CHANCE = 0x26,
        VAR_ACCURACY_STAGE = 0x27,
        VAR_EVASION_STAGE = 0x28,
        VAR_MAX_HIT_COUNT = 0x29,
        VAR_HIT_COUNT = 0x2A,
        VAR_ACCURACY = 0x2B,
        VAR_CRIT_STAGE = 0x2C,
        VAR_ITEM = 0x2D,
        VAR_ITEM_REACTION = 0x2E,
        VAR_SPEED = 0x2F,
        VAR_MOVE_POWER = 0x30,
        VAR_MOVE_POWER_RATIO = 0x31,
        VAR_DAMAGE = 0x32,
        VAR_POWER = 0x33,
        VAR_GUARD = 0x34,
        VAR_RATIO = 0x35,
        VAR_36 = 0x36,
        VAR_FIXED_DAMAGE = 0x37,
        VAR_TYPE_EFFECTIVENESS = 0x38,
        VAR_WEATHER = 0x39,
        VAR_ENDURE = 0x3A,
        VAR_SWAP_POKE_ID = 0x3B,
        VAR_BATTLE_MON_STAT = 0x3C,
        VAR_BATTLE_MON_STAT_SWAP_FLAG = 0x3D,
        VAR_ENABLE_MODE = 0x3E,
        VAR_WORK_ADDRESS = 0x3F,
        VAR_NO_EFFECT_FLAG = 0x40,
        VAR_MOVE_FAIL_FLAG = 0x41,
        VAR_AVOID_FLAG = 0x42,
        VAR_43 = 0x43,
        VAR_TYPE_MATCH_FLAG = 0x44,
        VAR_CRITICAL_FLAG = 0x45,
        VAR_SUBSTITUTE_FLAG = 0x46,
        VAR_SHIELD_DUST_FLAG = 0x47,
        VAR_SHEER_FORCE_FLAG = 0x48,
        VAR_49 = 0x49,
        VAR_TRICK_ROOM_FLAG = 0x4A,
        VAR_IGNORE_TYPE_EFFECTIVENESS = 0x4B,
        VAR_SET_TYPE_EFFECTIVENESS = 0x4C,
        VAR_DELAY_ATTACK_FLAG = 0x4D,
        VAR_MAGIC_COAT_FLAG = 0x4E,
        VAR_MESSAGE_FLAG = 0x4F,
        VAR_GENERAL_USE_FLAG = 0x51,
        VAR_SIDE = 0x52,
        VAR_SIDE_EFFECT = 0x53,
    };

    enum FlowResult
    {
        RESULT_TURN_STARTING = 0x0,
        RESULT_SWITCH = 0x1,
        RESULT_MON_FAINTED = 0x2,
        RESULT_EXP_GAINED = 0x3,
        RESULT_TEAM_FAINTED = 0x4,
        RESULT_ESCAPE = 0x5,
        RESULT_CAPTURE = 0x6,
    };

    enum ActionIgnoreReason
    {
        REASON_NONE = 0x0,
        REASON_OTHER_MOVE = 0x1,
        REASON_FALL_ASLEEP = 0x2,
        REASON_CONFUSION = 0x3,
        REASON_OVERLEVELED = 0x4,
        REASON_ASLEEP = 0x5,
    };

    enum MoveTarget : unsigned __int8
    {
        TARGET_OTHER_SELECT = 0x0,
        TARGET_ALLY_USER_SELECT = 0x1,
        TARGET_ALLY_SELECT = 0x2,
        TARGET_ENEMY_SELECT = 0x3,
        TARGET_OTHER_ALL = 0x4,
        TARGET_ENEMY_ALL = 0x5,
        TARGET_ALLY_ALL = 0x6,
        TARGET_USER = 0x7,
        TARGET_ALL = 0x8,
        TARGET_ENEMY_RANDOM = 0x9,
        TARGET_FIELD = 0xA,
        TARGET_SIDE_ENEMY = 0xB,
        TARGET_SIDE_ALLY = 0xC,
        TARGET_UNKNOWN = 0xD,
        TARGET_LONG_RANGE = 0xE,
    };

    struct ClientIDRecord
    {
        u8 count;
        u8 clientID[4];
    };

    enum BattleEventType
    {
        EVENT_NULL = 0x0,
        EVENT_ACTION_PROCESSING_START = 0x1,
        EVENT_ACTION_PROCESSING_END = 0x2,
        EVENT_MOVE_SEQUENCE_START = 0x3,
        EVENT_MOVE_SEQUENCE_END = 0x4,
        EVENT_BYPASS_SUBSTITUTE = 0x5,
        EVENT_CHECK_DELAYED_MOVE = 0x6,
        EVENT_DECIDE_DELAYED_MOVE = 0x7,
        EVENT_MOVE_SEQUENCE_STEAL = 0x8,
        EVENT_MOVE_SEQUENCE_REFLECT = 0x9,
        EVENT_A = 0xA,
        EVENT_SKIP_RUN_CALC = 0xB,
        EVENT_PREVENT_RUN = 0xC,
        EVENT_RUN_EXIT_MESSAGE = 0xD,
        EVENT_CHECK_SLEEP = 0xE,
        EVENT_CHECK_SPECIAL_PRIORITY = 0xF,
        EVENT_GET_MOVE_PRIORITY = 0x11,
        EVENT_CHECK_FLOATING = 0x12,
        EVENT_CALC_SPEED = 0x13,
        EVENT_14 = 0x14,
        EVENT_BEFORE_ATTACKS = 0x15,
        EVENT_MOVE_REQUEST_FOR_ACTION_ORDER = 0x16,
        EVENT_MOVE_REQUEST_CHECK_FAIL = 0x17,
        EVENT_MOVE_REQUEST_PARAM = 0x18,
        EVENT_MOVE_REQUEST_MESSAGE = 0x19,
        EVENT_CHECK_MOVE_STEAL = 0x1A,
        EVENT_FLOATING_IMMUNE_TO_MOVE = 0x1B,
        EVENT_SKIP_AVOID_CHECK = 0x1C,
        EVENT_CHECK_MOVE_FAIL = 0x1D,
        EVENT_MOVE_EXECUTE_CHECK1 = 0x1E,
        EVENT_MOVE_EXECUTE_CHECK2 = 0x1F,
        EVENT_MOVE_EXECUTE_CHECK3 = 0x20,
        EVENT_MOVE_EXECUTE_FAIL = 0x21,
        EVENT_CHOOSE_MOVE = 0x22,
        EVENT_BREAK_OPPONENT_GUARD = 0x23,
        EVENT_MOVE_EXECUTE_START = 0x24,
        EVENT_MOVE_EXECUTE_EFFECTIVE = 0x25,
        EVENT_MOVE_EXECUTE_NOEFFECT = 0x26,
        EVENT_MOVE_EXECUTE_END = 0x27,
        EVENT_MOVE_PARAM = 0x28,
        EVENT_DECIDE_TARGET = 0x29,
        EVENT_REDIRECT_TARGET = 0x2A,
        EVENT_REDIRECT_TARGETEND = 0x2B,
        EVENT_NOEFFECT_CHECK = 0x2C,
        EVENT_ABILITY_CHECK_NO_EFFECT = 0x2D,
        EVENT_CHECK_PROTECT_BREAK = 0x2E,
        EVENT_AVOID_MOVE = 0x2F,
        EVENT_CHECK_DAMAGE_TO_RECOVER = 0x30,
        EVENT_APPLY_DAMAGE_TO_RECOVER = 0x31,
        EVENT_BYPASS_ACCURACY_CHECK = 0x32,
        EVENT_MOVE_ACCURACY_STAGE = 0x33,
        EVENT_MOVE_ACCURACY = 0x34,
        EVENT_MOVE_HIT_COUNT = 0x35,
        EVENT_CRITICAL_CHECK = 0x36,
        EVENT_MOVE_BASE_POWER = 0x37,
        EVENT_MOVE_POWER = 0x38,
        EVENT_BEFORE_ATTACKER_POWER = 0x39,
        EVENT_BEFORE_DEFENDER_GUARD = 0x3A,
        EVENT_ATTACKER_POWER = 0x3B,
        EVENT_DEFENDER_GUARD = 0x3C,
        EVENT_CHECK_TYPE_EFFECTIVENESS_ENABLE = 0x3D,
        EVENT_CHECK_TYPE_EFFECTIVENESS = 0x3E,
        EVENT_REWRITE_TYPE_EFFECTIVENESS = 0x3F,
        EVENT_TYPE_MATCH_CHECK = 0x40,
        EVENT_SAME_TYPE_ATTACK_BONUS = 0x41,
        EVENT_ATTACKER_TYPE = 0x42,
        EVENT_DEFENDER_TYPE = 0x43,
        EVENT_AFTER_DAMAGE_REACTION = 0x44,
        EVENT_DETERMINE_MOVE_DAMAGE = 0x45,
        EVENT_MOVE_DAMAGE_PROCESSING_1 = 0x46,
        EVENT_MOVE_DAMAGE_PROCESSING_2 = 0x47,
        EVENT_MOVE_DAMAGE_PROCESSING_END = 0x48,
        EVENT_MOVE_DAMAGE_PROCESSING_FINAL = 0x49,
        EVENT_PREVIOUS_MOVE_REACTION = 0x4A,
        EVENT_MOVE_DAMAGE_REACTION_1 = 0x4B,
        EVENT_MOVE_DAMAGE_REACTION_2 = 0x4C,
        EVENT_MOVE_DAMAGE_SIDE_AFTER = 0x4D,
        EVENT_DECREMENT_PP = 0x4E,
        EVENT_DECREMENT_PP_DONE = 0x4F,
        EVENT_CALC_RECOIL = 0x50,
        EVENT_ADD_STAT_STAGE_CHANGE_TARGET = 0x51,
        EVENT_ADD_STAT_STAGE_CHANGE_USER = 0x52,
        EVENT_SWITCH_OUT_INTERRUPT = 0x53,
        EVENT_SWITCH_OUT_END = 0x54,
        EVENT_SWITCH_IN = 0x55,
        EVENT_SWITCH_IN_PREVIOUS = 0x56,
        EVENT_AFTER_LAST_SWITCHIN = 0x57,
        EVENT_CHECK_ACTIVATION = 0x58,
        EVENT_GET_STAT_STAGE_CHANGE_VALUE = 0x59,
        EVENT_STAT_STAGE_CHANGE = 0x5A,
        EVENT_STAT_STAGE_CHANGE_LAST_CHECK = 0x5B,
        EVENT_STAT_STAGE_CHANGE_FAIL = 0x5C,
        EVENT_STAT_STAGE_CHANGE_APPLIED = 0x5D,
        EVENT_MOVE_STAT_STAGE_CHANGE_APPLIED = 0x5E,
        EVENT_MOVE_CONDITION_TURN_COUNT = 0x5F,
        EVENT_MOVE_CONDITION_SPECIAL = 0x60,
        EVENT_MOVE_CONDITION_MESSAGE = 0x61,
        EVENT_MOVE_CONDITION_PARAM = 0x62,
        EVENT_ADD_CONDITION_TYPE = 0x63,
        EVENT_ADD_CONDITION = 0x64,
        EVENT_ADD_CONDITION_CHECK_FAIL = 0x65,
        EVENT_ADD_CONDITION_APPLIED = 0x66,
        EVENT_ADD_CONDITION_FAIL = 0x67,
        EVENT_ADD_BASIC_STATUS = 0x68,
        EVENT_MOVE_CONDITION_APPLIED = 0x69,
        EVENT_ABILITY_NULLIFIED = 0x6A,
        EVENT_CONDITION_DAMAGE = 0x6B,
        EVENT_MOVE_FLINCH_CHANCE = 0x6C,
        EVENT_FLINCH_CHECK = 0x6D,
        EVENT_FLINCH_FAIL = 0x6E,
        EVENT_FLINCH_APPLIED = 0x6F,
        EVENT_OHKO_CHECK = 0x70,
        EVENT_OHKO_PREVENT = 0x71,
        EVENT_USE_ITEM = 0x72,
        EVENT_USE_ITEM_TEMP = 0x73,
        EVENT_ENDURE_CHECK = 0x74,
        EVENT_ENDURE = 0x75,
        EVENT_TURN_CHECK_BEGIN = 0x76,
        EVENT_TURN_CHECK_END = 0x77,
        EVENT_TURN_CHECK_DONE = 0x78,
        EVENT_NOTIFY_AIR_LOCK = 0x79,
        EVENT_WEATHER_CHECK = 0x7A,
        EVENT_WEIGHT_RATIO = 0x7B,
        EVENT_MOVE_WEATHER_TURN_COUNT = 0x7C,
        EVENT_WEATHER_CHANGE = 0x7D,
        EVENT_AFTER_WEATHER_CHANGE = 0x7E,
        EVENT_WEATHER_REACTION = 0x7F,
        EVENT_ENABLE_SIMPLE_DAMAGE = 0x80,
        EVENT_DAMAGE_PROCESSING_START = 0x81,
        EVENT_DAMAGE_PROCESSING_END_PREVIOUSHIT = 0x82,
        EVENT_DAMAGE_PROCESSING_END_HIT_REAL = 0x83,
        EVENT_DAMAGE_PROCESSING_END_HIT_1 = 0x84,
        EVENT_DAMAGE_PROCESSING_END_HIT_2 = 0x85,
        EVENT_DAMAGE_PROCESSING_END_HIT_3 = 0x86,
        EVENT_DAMAGE_PROCESSING_END_HIT_4 = 0x87,
        EVENT_DAMAGE_PROCESSING_END = 0x88,
        EVENT_BEFORE_ABILITY_CHANGE = 0x89,
        EVENT_AFTER_ABILITY_CHANGE = 0x8A,
        EVENT_CHECK_FORCE_SWITCH = 0x8B,
        EVENT_CALC_DRAIN = 0x8C,
        EVENT_CALC_DRAIN_END = 0x8D,
        EVENT_RECOVER_HP = 0x8F,
        EVENT_AFTER_ITEM_EQUIP = 0x90,
        EVENT_CHECK_ITEM_REACTION = 0x91,
        EVENT_ITEM_CONSUMED = 0x92,
        EVENT_CHECK_CHARGE_UP_FAIL = 0x93,
        EVENT_CHECK_CHARGE_UP_SKIP = 0x94,
        EVENT_CHARGE_UP_START = 0x95,
        EVENT_CHARGE_UP_START_DONE = 0x96,
        EVENT_CHARGE_UP_SKIP = 0x97,
        EVENT_CHARGE_UP_END = 0x98,
        EVENT_CHECK_HIDING = 0x99,
        EVENT_HELD_ITEM_CHECK = 0x9A,
        EVENT_HELD_ITEM_FAIL = 0x9B,
        EVENT_HELD_ITEM_DECIDE = 0x9C,
        EVENT_ITEM_REWRITE_DONE = 0x9D,
        EVENT_CALL_FIELD_EFFECT = 0x9E,
        EVENT_CHECK_SIDE_EFFECT_PARAM = 0x9F,
        EVENT_UNCATEGORIZED_MOVE = 0xA0,
        EVENT_UNCATEGORIZED_MOVE_NO_TARGET = 0xA1,
        EVENT_COMBINED_MOVE_CHECK = 0xA2,
        EVENT_NOTIFY_FAINTED = 0xA3,
        EVENT_AFTER_SHIFT = 0xA4,
    };

    struct MoveAnimCtrl
    {
        unsigned __int16 moveID;
        unsigned __int8 attackerPos;
        unsigned __int8 targetPos;
        unsigned __int8 effectIndex;
        unsigned __int8 flags;
        unsigned __int16 subEff;
    };

    struct MoveParam
    {
        unsigned __int16 MoveID;
        unsigned __int16 OriginalMoveID;
        unsigned __int16 userType;
        unsigned __int8 moveType;
        char damageType;
        int category;
        MoveTarget targetType;
        int flags;
    };

    struct SWAN_PACKED SWAN_ALIGNED(1) calc_damage_record
    {
        u16 damage;
        unsigned __int16 targetID : 5;
        unsigned __int16 effectiveness : 3;
        unsigned __int16 unk : 1;
        unsigned __int16 isEndureActive : 1;
        unsigned __int16 unk2 : 3;
        unsigned __int16 isCritical : 1;
        unsigned __int16 isFixedDamage : 1;
        unsigned __int16 isSubstituteActive : 1;
    };

    struct HitCheckParam
    {
        char countMax;
        char count;
        char fCheckEveryTime;
        char fMultiHitMove;
        char fPutAnimCmd;
        char MultiHitEffectiveness;
    };
    struct CalcDamageRecord
    {
        u8 real_hit_count;
        u8 substitute_hit_count;
        u8 total_hit_count;
        u8 pad;
        calc_damage_record record[6];
    };

    struct MoveStealParam
    {
        char stealCount;
        char stealMonID[6];
        char targetPos[6];
        char targetMonID[6];
    };

    struct SWAN_ALIGNED(4) PokeSetStackUnit
    {
        PokeSet TargetOriginal;
        PokeSet Target;
        PokeSet Ally;
        PokeSet Enemy;
        PokeSet Damaged;
        PokeSet StealTarget;
        PokeSet psetTemp;
        MoveAnimCtrl moveAnimCtrl;
        MoveParam moveParam;
        MoveParam MoveParamOriginal;
        HitCheckParam hitCheck;
        MoveStealParam moveStealParam;
        MoveStealParam magicCoatParam;
        CalcDamageRecord calcDamageAlly;
        CalcDamageRecord calcDamageEnemy;
        char defaultTargetPos;
        char field_28D;
        char field_28E;
        char field_28F;
    };

    struct LevelUpInfo
    {
        u8 level;
        u16 hp;
        u16 atk;
        u16 def;
        u16 spa;
        u16 spd;
        u16 spe;
    };

    struct HEManager
    {
        u32 state;
        u8 workBuffer[500];
    };

    struct EventWorkStack
    {
        u8 work[512];
        u16 size[16];
        u32 sp;
    };

    enum TurnFlag
#ifdef __cplusplus
        : u32
#endif
    {

        TURNFLAG_ACTIONSTART = 0x0,
        TURNFLAG_ACTIONDONE = 0x1,
        TURNFLAG_DAMAGED = 0x2,
        TURNFLAG_MOVEPROCDONE = 0x3,
        TURNFLAG_FLINCH = 0x4,
        // TURNFLAG_FOCUSPUNCHREADY = 0x5,
        TURNFLAG_MOVEFAILED = 0x5,
        // TURNFLAG_FOCUSPUNCHFAIL = 0x6,
        TURNFLAG_MOVEFAILEDLASTTURN = 0x6,
        TURNFLAG_PROTECT = 0x7,
        TURNFLAG_ITEMCONSUMED = 0x8,
        TURNFLAG_CANTUSEITEM = 0x9,
        TURNFLAG_COMBOMOVEREADY = 0xA,
        TURNFLAG_HIDEMOVEOFF = 0xB,
        TURNFLAG_MOVED = 0xC,
        TURNFLAG_TURNCHECKCONDITIONPASSED = 0xD,
        TURNFLAG_ACCURACYUP = 0xE,
        TURNFLAG_USINGFLING = 0xF,
    };
    struct BattleAction_Default
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 param : 28;
    };
    struct BattleAction_Attack
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 targetPos : 3;
        unsigned __int32 moveID : 19;
        unsigned __int32 moveInfoFlag : 1;
        unsigned __int32 pad : 5;
    };
    struct BattleAction_Item
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 targetIdx : 3;
        unsigned __int32 itemID : 20;
        unsigned __int32 moveIdx : 5;
    };
    struct BattleAction_Switch
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 battlePos : 3;
        unsigned __int32 partyIndex : 3;
        unsigned __int32 unkFlag : 1;
        unsigned __int32 pad : 21;
    };
    struct BattleAction_Run
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 escape : 28;
    };
    struct BattleAction_Rotate
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 rotation : 3;
        unsigned __int32 pad : 3;
        unsigned __int32 unkFlag : 1;
        unsigned __int32 pad2 : 21;
    };
    struct BattleAction_Shift
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 shift : 28;
    };

    union BattleActionParam
    {
        u32 raw;
        BattleAction_Default Default;
        BattleAction_Attack Attack;
        BattleAction_Item Item;
        BattleAction_Switch Switch;
        BattleAction_Run Run;
        BattleAction_Shift Shift;
        BattleAction_Rotate Rotate;
    };

    struct ActionOrderWork
    {
        BattleMon *BattleMon;
        BattleActionParam *Action;
        int orderData;
        char clientID;
        char fDone;
        char InterruptActive;
        char field_F;
    };
    struct SWAN_ALIGNED(8) ServerFlow
    {
        void *server;
        MainModule *mainModule;
        void *pokeCon;
        void *serverCommandQueue;
        int turnCount;
        FlowResult flowResult;
        int heapHandle;
        MoveRecord moveRecord;
        FaintRecord faintRecord;
        void *evolutionDataPtr;
        MoveAnimCtrl *moveAnimCtrl;
        MoveStealParam *moveStealParam;
        MoveStealParam *magicCoatParam;
        HitCheckParam *hitCheckParam;
        EscapeInfo escapeInfo;
        LevelUpInfo levelUpInfo;
        ClientIDRecord clientIDRecord;
        int rotationHandlerWork[24][7];
        int SimulationCounter;
        int StatStageChangeCount;
        char cmdBuildStep;
        char actOrderStep;
        char turnCheckStep;
        char defaultTargetPos;
        __int16 heapID;
        char actionOrderIndex;
        char actionOrderEndIndex;
        _BYTE ballTargetPos;
        char revivedPokeCount;
        char escapeAttempts;
        char moveAnimIndex;
        char SwitchOutInterruptingMonCount;
        char thruDeadMsgPokeID;
        char flags;
        u8 SwitchOutInterruptingMonIDs[6];
        u8 RevivedMonIDs[24];
        char FaintedMonFlag[24];
        char WasInBattleFlag[24];
        char ClientSwitchCount[4];
        ActionOrderWork actionOrderWork[6];
        ActionOrderWork TempActionOrderWork;
        PokeSet *PokeSetTargetOriginal;
        PokeSet *PokeSetTarget;
        PokeSet *PokeSetAlly;
        PokeSet *PokeSetEnemy;
        PokeSet *PokeSetDamaged;
        PokeSet *PokeSetStealTarget;
        PokeSet *PokeSetTemp;
        CalcDamageRecord *CalcDamageAlly;
        CalcDamageRecord *CalcDamageEnemy;
        PokeSetStackUnit PokeSetStack[7];
        int PokeSetStackPtr;
        PokeSet PokeSetSwitchInProc;
        MoveParam *moveParam;
        MoveParam *moveParamOriginal;
        PosPoke posPoke;
        HandlerParam_StrParams StrParam;
        CalcExpWork calcExpWork[6];
        EventWorkStack eventWorkStack;
        HEManager heManager;
        MoveDamageRec moveDamageRec;
        __int16 PrevUsedMove;
        ActionIgnoreReason actionIgnoreReason;
        EffectivenessCounter effectivenessCounter;
        EffectivenessRecorder effectivenessRecorder;
        u8 flowFlags[4];
        u8 TempWork[320];
        int PokestarResult;
    };
    struct EventWorkSave
    {
        u16 Works[431];
        u8 FlagBytes[383];
        u8 CanRespawnHiddenItems;
    };

    enum BattleMonValue
    {
        VALUE_NULL = 0x0,
        VALUE_ATTACK_STAGE = 0x1,
        VALUE_DEFENSE_STAGE = 0x2,
        VALUE_SPECIAL_ATTACK_STAGE = 0x3,
        VALUE_SPECIAL_DEFENSE_STAGE = 0x4,
        VALUE_SPEED_STAGE = 0x5,
        VALUE_ACCURACY_STAGE = 0x6,
        VALUE_EVASION_STAGE = 0x7,
        VALUE_ATTACK_STAT = 0x8,
        VALUE_DEFENSE_STAT = 0x9,
        VALUE_SPECIAL_ATTACK_STAT = 0xA,
        VALUE_SPECIAL_DEFENSE_STAT = 0xB,
        VALUE_SPEED_STAT = 0xC,
        VALUE_CURRENT_HP = 0xD,
        VALUE_MAX_HP = 0xE,
        VALUE_LEVEL = 0xF,
        VALUE_ABILITY = 0x10,
        VALUE_EFFECTIVE_ABILITY = 0x11,
        VALUE_SEX = 0x12,
        VALUE_FORM = 0x13,
        VALUE_EXPERIENCE = 0x14,
        VALUE_BASE_ATTACK = 0x15,
    };
    enum MoveCondition
    {
        CONDITION_NONE = 0x0,
        CONDITION_PARALYSIS = 0x1,
        CONDITION_SLEEP = 0x2,
        CONDITION_FREEZE = 0x3,
        CONDITION_BURN = 0x4,
        CONDITION_POISON = 0x5,
        CONDITION_CONFUSION = 0x6,
        CONDITION_ATTRACT = 0x7,
        CONDITION_BIND = 0x8,
        CONDITION_NIGHTMARE = 0x9,
        CONDITION_CURSE = 0xA,
        CONDITION_TAUNT = 0xB,
        CONDITION_TORMENT = 0xC,
        CONDITION_DISABLE = 0xD,
        CONDITION_YAWN = 0xE,
        CONDITION_HEAL_BLOCK = 0xF,
        CONDITION_GASTRO_ACID = 0x10,
        CONDITION_FORESIGHT = 0x11,
        CONDITION_LEECH_SEED = 0x12,
        CONDITION_EMBARGO = 0x13,
        CONDITION_PERISH_SONG = 0x14,
        CONDITION_INGRAIN = 0x15,
        CONDITION_BLOCK = 0x16,
        CONDITION_ENCORE = 0x17,
        CONDITION_ROOST = 0x18,
        CONDITION_MOVE_LOCK = 0x19,
        CONDITION_CHARGE_LOCK = 0x1A,
        CONDITION_CHOICE_LOCK = 0x1B,
        CONDITION_MUST_HIT = 0x1C,
        CONDITION_LOCK_ON = 0x1D,
        CONDITION_FLOATING = 0x1E,
        CONDITION_KNOCKED_DOWN = 0x1F,
        CONDITION_TELEKINESIS = 0x20,
        CONDITION_SKY_DROP = 0x21,
        CONDITION_ACCURACY_UP = 0x22,
        CONDITION_AQUA_RING = 0x23,
        CONDITION_24 = 0x24,
    };

    extern u32 PML_MoveGetCategory(int wazaId);
    extern void BattleEventVar_Push();
    extern u32 BattleEventVar_SetConstValue(BattleEventVar a1, int a2);
    extern int BattleMon_GetID(BattleMon *a1);
    extern u32 BattleEventVar_SetValue(BattleEventVar a1, int a2);
    extern void BattleEvent_CallHandlers(ServerFlow *a1, BattleEventType a2);
    extern int BattleEventVar_GetValue(BattleEventVar a1);
    extern int ServerEvent_GetMovePower(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4);
    extern int ServerEvent_GetTargetDefenses(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4, int a5);
    extern int ServerEvent_GetAttackPower(
        ServerFlow *a1,
        BattleMon *AttackingMon,
        BattleMon *DefendingMon,
        MoveParam *a4,
        int criticalFlag);
    extern int BattleMon_GetValue(BattleMon *a1, BattleMonValue a2);
    extern unsigned int CalcBaseDamage(int power, int attack, int level, unsigned int defense);
    extern unsigned int fixed_round(int a1, int a2);
    extern int ServerEvent_GetWeather(ServerFlow *a1);
    extern int WeatherPowerMod(int a1, int a2);
    extern int MainModule_GetDebugFlag();
    extern bool ServerFlow_IsNotPokestarBattle(ServerFlow *a1);
    extern int BattleRandom(unsigned int a1);
    extern int ServerEvent_SameTypeAttackBonus(ServerFlow *a1, BattleMon *a2, PokeType a3);
    extern unsigned int TypeEffectivenessPowerMod(unsigned int result, unsigned int a2);
    extern MoveCondition BattleMon_GetStatus(BattleMon *a1);
    extern unsigned int BattleEventVar_SetMulValue(BattleEventVar a1, int a2, int a3, int a4);
    extern void BattleEventVar_Pop();
    extern EventWorkSave *GameData_GetEventWork(void *gameData);
    extern u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);
    extern int BattleMon_GetPreviousMove(BattleMon *a1);
    extern bool BattleMon_GetTurnFlag(BattleMon *a1, TurnFlag a2);

    u32 GetCritSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16415);

        // // k::Printf("Current crit setting is %d\n", *lvl_cap_ptr);

        return *lvl_cap_ptr;
    }

    int VANILLA_CRIT_CHANCES[5] = {0x10, 8, 4, 3, 2};
    int MODERN_CRIT_CHANCES[5] = {0x18, 8, 2, 0, 0};

    bool THUMB_BRANCH_RollCritical(int a1)
    {
        if (GetCritSetting() == 0)
        {
            return BattleRandom(VANILLA_CRIT_CHANCES[a1]) == 0;
        }
        else
        {
            return BattleRandom(MODERN_CRIT_CHANCES[a1]) == 0;
        }
    }

    bool personalRollCritical(int a1)
    {
        if (GetCritSetting() == 0)
        {
            return BattleRandom(VANILLA_CRIT_CHANCES[a1]) == 0;
        }
        else
        {
            return BattleRandom(MODERN_CRIT_CHANCES[a1]) == 0;
        }
    }

    int THUMB_BRANCH_SAFESTACK_ServerEvent_CalcDamage(
        ServerFlow *a1,
        BattleMon *AttackingMon,
        BattleMon *DefendingMon,
        MoveParam *MoveParam,
        int TypeEffectiveness,
        int targetDmgRatio,
        int criticalFlag,
        int BattleDebugMode,
        _WORD *destDamage)
    {
        int ID;                // r0
        int v13;               // r0
        int defense;           // r7
        unsigned __int8 level; // r0
        int v16;               // r0
        unsigned int fxDamage; // r7
        int Weather;           // r0
        int weatherDmgRatio;   // r1
        int damageRoll;        // r0
        PokeType moveType;     // r2
        int v22;               // r0
        int v23;               // r4
        int v24;               // r4
        int v25;               // r0
        unsigned int Value;    // [sp+8h] [bp-28h]
        int v29;               // [sp+Ch] [bp-24h]
        int Category;          // [sp+10h] [bp-20h]
        int power;             // [sp+14h] [bp-1Ch]
        int attack;            // [sp+18h] [bp-18h]

        Category = PML_MoveGetCategory(MoveParam->MoveID);
        v29 = 0;
        BattleEventVar_Push();
        BattleEventVar_SetConstValue(VAR_TYPE_EFFECTIVENESS, TypeEffectiveness);
        ID = BattleMon_GetID(AttackingMon);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
        v13 = BattleMon_GetID(DefendingMon);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v13);
        BattleEventVar_SetConstValue(VAR_CRITICAL_FLAG, criticalFlag);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, MoveParam->moveType);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, MoveParam->MoveID);
        BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, Category);
        BattleEventVar_SetValue(VAR_FIXED_DAMAGE, 0);
        BattleEvent_CallHandlers(a1, EVENT_MOVE_DAMAGE_PROCESSING_1);
        Value = BattleEventVar_GetValue(VAR_FIXED_DAMAGE);
        if (Value)
        {
            v29 = 1;
        }
        else
        {
            power = ServerEvent_GetMovePower(a1, AttackingMon, DefendingMon, MoveParam);
            attack = ServerEvent_GetAttackPower(a1, AttackingMon, DefendingMon, MoveParam, criticalFlag);
            defense = ServerEvent_GetTargetDefenses(a1, AttackingMon, DefendingMon, MoveParam, criticalFlag);
            level = BattleMon_GetValue(AttackingMon, VALUE_LEVEL);
            v16 = CalcBaseDamage(power, attack, level, defense);
            fxDamage = v16;
            if (targetDmgRatio != 4096)
            {
                fxDamage = fixed_round(v16, targetDmgRatio);
            }

            Weather = ServerEvent_GetWeather(a1);
            weatherDmgRatio = WeatherPowerMod(Weather, MoveParam->moveType);
            if (weatherDmgRatio != 4096)
            {
                fxDamage = fixed_round(fxDamage, weatherDmgRatio);
            }

            if (criticalFlag)
            {

                if (GetCritSetting() == 1 && MoveParam->MoveID != 480 && MoveParam->MoveID != 524 && MoveParam->MoveID != 6 && MoveParam->MoveID != 190 && MoveParam->MoveID != 346)
                {
                    fxDamage = fxDamage * 3;
                    fxDamage = fxDamage >> 2;
                }
                else
                {
                    fxDamage *= 2;
                }
            }

            if (!MainModule_GetDebugFlag() && ServerFlow_IsNotPokestarBattle(a1))
            {
                if (BattleDebugMode)
                {
                    damageRoll = 85;
                }
                else
                {
                    damageRoll = (100 - BattleRandom(16u));
                }

                fxDamage = damageRoll * fxDamage / 100;
            }

            moveType = (PokeType)MoveParam->moveType;
            if (moveType != TYPE_NULL)
            {

                v22 = ServerEvent_SameTypeAttackBonus(a1, AttackingMon, moveType);
                fxDamage = fixed_round(fxDamage, v22);
            }

            v23 = TypeEffectivenessPowerMod(fxDamage, TypeEffectiveness);

            if (Category == 1 && BattleMon_GetStatus(AttackingMon) == CONDITION_BURN && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != 62)
            {

                v23 = 50 * v23 / 100u;
            }

            // Check for Overheat and Sheer Cold
            if (Category == 2 && (BattleMon_GetPreviousMove(AttackingMon) == 329 || BattleMon_GetPreviousMove(AttackingMon) == 437 || BattleMon_GetPreviousMove(AttackingMon) == 315 || BattleMon_GetPreviousMove(AttackingMon) == 434) && !BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                v23 = 50 * v23 / 100u;
                // k::Printf("\nBecause of Overheat, the new power of this move is %d\n\n", v23);
            }

            if (!v23)
            {
                v23 = 1;
            }

            BattleEventVar_SetMulValue(VAR_RATIO, 4096, 41, 0x20000);
            BattleEventVar_SetValue(VAR_DAMAGE, v23);
            BattleEvent_CallHandlers(a1, EVENT_MOVE_DAMAGE_PROCESSING_2);

            v24 = BattleEventVar_GetValue(VAR_RATIO);
            v25 = BattleEventVar_GetValue(VAR_DAMAGE);

            LOWORD(Value) = fixed_round(v25, v24);
        }

        BattleEvent_CallHandlers(a1, EVENT_MOVE_DAMAGE_PROCESSING_END);
        BattleEventVar_Pop();

        *destDamage = Value;
        return v29;
    }
    enum MoveField
    {
        MVDATA_TYPE = 0x0,
        MVDATA_QUALITY = 0x1,
        MVDATA_CATEGORY = 0x2,
        MVDATA_POWER = 0x3,
        MVDATA_ACCURACY = 0x4,
        MVDATA_BASEPP = 0x5,
        MVDATA_PRIORITY = 0x6,
        MVDATA_CRIT_STAGE = 0x7,
        MVDATA_HIT_MAX = 0x8,
        MVDATA_HIT_MIN = 0x9,
        MVDATA_FLINCH_RATE = 0xA,
        MVDATA_INFLICT_STATUS = 0xB,
        MVDATA_INFLICT_CHANCE = 0xC,
        MVDATA_INFLICT_DURATION = 0xD,
        MVDATA_TURN_MIN = 0xE,
        MVDATA_TURN_MAX = 0xF,
        MVDATA_STAT1 = 0x10,
        MVDATA_STAT2 = 0x11,
        MVDATA_STAT3 = 0x12,
        MVDATA_STAT1_STAGE = 0x13,
        MVDATA_STAT2_STAGE = 0x14,
        MVDATA_STAT3_STAGE = 0x15,
        MVDATA_STAT1_CHANCE = 0x16,
        MVDATA_STAT2_CHANCE = 0x17,
        MVDATA_STAT3_CHANCE = 0x18,
        MVDATA_RECOIL = 0x19,
        MVDATA_HEAL = 0x1A,
        MVDATA_TARGET = 0x1B,
        MVDATA_WAZASEQ_ID = 0x1C,
        MVDATA_UNUSED = 0x1D,
        MVDATA_RECOIL_NEG = 0x1E,
        MVDATA_HEAL_NEG = 0x1F,
    };
    enum ConditionFlag
    {
        CONDITIONFLAG_ACTION_DONE = 0x0,
        CONDITIONFLAG_NO_SWITCH = 0x1,
        CONDITIONFLAG_CHARGE = 0x2,
        CONDITIONFLAG_FLY = 0x3,
        CONDITIONFLAG_DIVE = 0x4,
        CONDITIONFLAG_DIG = 0x5,
        CONDITIONFLAG_SHADOW_FORCE = 0x6,
        CONDITIONFLAG_DEFENSE_CURL = 0x7,
        CONDITIONFLAG_MINIMIZE = 0x8,
        CONDITIONFLAG_FOCUS_ENERGY = 0x9,
        CONDITIONFLAG_POWER_TRICK = 0xA,
        CONDITIONFLAG_MICLE_BERRY = 0xB,
        CONDITIONFLAG_NO_ACTION = 0xC,
        CONDITIONFLAG_FLASH_FIRE = 0xD,
        CONDITIONFLAG_BATON_PASS = 0xE,
        CONDITIONFLAG_NULL = 0xF,
    };

    extern u32 PML_MoveGetParam(int wazaId, MoveField dataId);
    extern int BattleMon_GetCritStage(BattleMon *a1);
    extern u32 BattleEventVar_SetRewriteOnceValue(BattleEventVar a1, int a2);
    extern bool PML_MoveIsAlwaysCrit(int wazaId);
    extern bool BattleMon_GetConditionFlag(BattleMon *a1, ConditionFlag a2);

    bool THUMB_BRANCH_ServerEvent_CheckCritical(ServerFlow *a1, BattleMon *a2, BattleMon *a3, int a4)
    {
        __int16 Param; // r4
        int v8;        // r4
        int ID;        // r0
        int v10;       // r0
        bool v11;      // r4
        int Value;     // r0

        Param = PML_MoveGetParam(a4, MVDATA_CRIT_STAGE);
        v8 = (Param + BattleMon_GetCritStage(a2));
        BattleEventVar_Push();
        ID = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, ID);
        v10 = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, v10);
        BattleEventVar_SetValue(VAR_CRIT_STAGE, v8);
        v11 = 0;
        BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
        BattleEvent_CallHandlers(a1, EVENT_CRITICAL_CHECK);
        if (!BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG))
        {
            if (PML_MoveIsAlwaysCrit(a4))
            {
                v11 = 1;
            }
            else
            {
                Value = BattleEventVar_GetValue(VAR_CRIT_STAGE);
                if (Value > 4)
                {
                    // LOBYTE(Value) = 4;
                    Value = (Value & 0xFF) | 4;
                }
                v11 = personalRollCritical(Value);
            }
            if (MainModule_GetDebugFlag())
            {
                v11 = 1;
            }
        }
        BattleEventVar_Pop();

        if (BattleMon_GetConditionFlag(a3, CONDITIONFLAG_DEFENSE_CURL))
        {
            v11 = 0;
        }

        return v11;
    }

    extern void MoveEvent_ForceRemoveItemFromBattleMon(BattleMon *a1, int a2);
    extern int MoveEvent_AddItem(BattleMon *a1, int a2, int a3);

    int THUMB_BRANCH_ServerEvent_InterruptSwitch(ServerFlow *a1, BattleMon *a2)
    {
        unsigned int v3;      // r4
        unsigned int v4;      // r7
        BattleMon *BattleMon; // r0
        int v6;               // r6
        int Value;            // r0
        unsigned int v8;      // r4
        int ID;               // r0
        int moveID;
        // ServerFlow *v10;                  // r6
        int v11; // r1
        // ServerFlow *v14;                  // [sp+4h] [bp-44h]
        ActionOrderWork *ActionOrderWork; // [sp+8h] [bp-40h]
        char *p_actionOrderIndex;         // [sp+20h] [bp-28h]

        v3 = 0;
        if (a1->actionOrderIndex)
        {
            ActionOrderWork = a1->actionOrderWork;
            p_actionOrderIndex = &a1->actionOrderIndex;
            do
            {
                v4 = v3;
                BattleMon = a1->actionOrderWork[v4].BattleMon;

                // k::Printf("\nThis is a quick test to see if we are successfully catching a Battlemon\nv3 is %d, v4 is %d\nThis battlemon's id is %d, its species is %d, and its attack stat is %d\n",
                //          v3, v4, BattleMon_GetID(BattleMon), BattleMon->Species, BattleMon->Attack);

                if (BattleMon != a2 && !a1->actionOrderWork[v4].fDone)
                {
                    v6 = (((u32)ActionOrderWork[v4].Action) & 0xF) == 1 ? (((u32)ActionOrderWork[v4].Action) >> 7) : 0;

                    if (v6 == 228)
                    {
                        moveID = v6;
                        Value = BattleMon_GetValue(BattleMon, VALUE_SPEED_STAT);
                        if (MoveEvent_AddItem(a1->actionOrderWork[v4].BattleMon, moveID, Value))
                        {
                            a1->actionOrderWork[v4].InterruptActive = 1;
                        }
                    }
                    else if (v6 == 467 || v6 == 291 || v6 == 19 || v6 == 91 || v6 == 340)
                    {

                        if ((BattleMon_GetConditionFlag(a1->actionOrderWork[v4].BattleMon, CONDITIONFLAG_SHADOW_FORCE) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v4].BattleMon, CONDITIONFLAG_DIG) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v4].BattleMon, CONDITIONFLAG_DIVE) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v4].BattleMon, CONDITIONFLAG_FLY)) ||
                            a1->actionOrderWork[v8].BattleMon->HeldItem == 271)
                        {
                            moveID = v6;
                            Value = BattleMon_GetValue(BattleMon, VALUE_SPEED_STAT);

                            if (MoveEvent_AddItem(a1->actionOrderWork[v4].BattleMon, moveID, Value))
                            {
                                a1->actionOrderWork[v4].InterruptActive = 1;
                            }
                        }
                    }
                }
                ++v3;
            } while (v3 < *p_actionOrderIndex);
        }
        v8 = 0;
        a1->SwitchOutInterruptingMonCount = 0;
        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_TARGET_MON_ID, ID);
        BattleEvent_CallHandlers(a1, EVENT_SWITCH_OUT_INTERRUPT);
        BattleEventVar_Pop();
        if (a1->actionOrderIndex)
        {
            do
            {

                if (a1->actionOrderWork[v8].InterruptActive)
                {
                    if ((((u32)a1->actionOrderWork[v8].Action) & 0xF) == 1)
                    {
                        v11 = (((u32)a1->actionOrderWork[v8].Action) >> 7);
                    }
                    else
                    {
                        v11 = 0;
                    }

                    if (v11 == 228)
                    {
                        MoveEvent_ForceRemoveItemFromBattleMon(a1->actionOrderWork[v8].BattleMon, v11);
                    }

                    else if (v11 == 467 || v11 == 291 || v11 == 19 || v11 == 91 || v11 == 340)
                    {

                        if ((BattleMon_GetConditionFlag(a1->actionOrderWork[v8].BattleMon, CONDITIONFLAG_SHADOW_FORCE) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v8].BattleMon, CONDITIONFLAG_DIG) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v8].BattleMon, CONDITIONFLAG_DIVE) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v8].BattleMon, CONDITIONFLAG_FLY)) ||
                            a1->actionOrderWork[v8].BattleMon->HeldItem == 271)
                        {

                            MoveEvent_ForceRemoveItemFromBattleMon(a1->actionOrderWork[v8].BattleMon, v11);
                        }
                    }
                    a1->actionOrderWork[v8].InterruptActive = 0;
                }
                ++v8;
            } while (v8 < a1->actionOrderIndex);
        }
        return a1->SwitchOutInterruptingMonCount;
    }
    enum PkmField
    {
        PF_PID = 0x0,
        PF_Species = 0x5,
        PF_Item = 0x6,
        PF_IdSet = 0x7,
        PF_Experience = 0x8,
        PF_Happiness = 0x9,
        PF_Ability = 0xA,
        PF_Markings = 0xB,
        PF_Region = 0xC,
        PF_EvHP = 0xD,
        PF_EvATK = 0xE,
        PF_EvDEF = 0xF,
        PF_EvSPE = 0x10,
        PF_EvSPA = 0x11,
        PF_EvSPD = 0x12,
        PF_ContestCool = 0x13,
        PF_ContestBeauty = 0x14,
        PF_ContestCute = 0x15,
        PF_ContestSmart = 0x16,
        PF_ContestTough = 0x17,
        PF_ContestSheen = 0x18,
        PF_RibbonChampionSinnoh = 0x19,
        PF_RibbonAbility = 0x1A,
        PF_RibbonAbilityGreat = 0x1B,
        PF_RibbonAbilityDouble = 0x1C,
        PF_RibbonAbilityMulti = 0x1D,
        PF_RibbonAbilityPair = 0x1E,
        PF_RibbonAbilityWorld = 0x1F,
        PF_RibbonAlert = 0x20,
        PF_RibbonShock = 0x21,
        PF_RibbonDowncast = 0x22,
        PF_RibbonCareless = 0x23,
        PF_RibbonRelax = 0x24,
        PF_RibbonSnooze = 0x25,
        PF_RibbonSmile = 0x26,
        PF_RibbonGorgeous = 0x27,
        PF_RibbonRoyal = 0x28,
        PF_RibbonGorgeousRoyal = 0x29,
        PF_RibbonFootprint = 0x2A,
        PF_RibbonRecord = 0x2B,
        PF_RibbonEvent = 0x2C,
        PF_RibbonLegend = 0x2D,
        PF_RibbonChampionWorld = 0x2E,
        PF_RibbonBirthday = 0x2F,
        PF_RibbonSpecial = 0x30,
        PF_RibbonSouvenir = 0x31,
        PF_RibbonWishing = 0x32,
        PF_RibbonClassic = 0x33,
        PF_RibbonPremier = 0x34,
        PF_Ribbon0x35 = 0x35,
        PF_Move1 = 0x36,
        PF_Move2 = 0x37,
        PF_Move3 = 0x38,
        PF_Move4 = 0x39,
        PF_Move1PP = 0x3A,
        PF_Move2PP = 0x3B,
        PF_Move3PP = 0x3C,
        PF_Move4PP = 0x3D,
        PF_Move1PPUp = 0x3E,
        PF_Move2PPUp = 0x3F,
        PF_Move3PPUp = 0x40,
        PF_Move4PPUp = 0x41,
        PF_Move1PPMax = 0x42,
        PF_Move2PPMax = 0x43,
        PF_Move3PPMax = 0x44,
        PF_Move4PPMax = 0x45,
        PF_IvHP = 0x46,
        PF_IvATK = 0x47,
        PF_IvDEF = 0x48,
        PF_IvSPE = 0x49,
        PF_IvSPA = 0x4A,
        PF_IvSPD = 0x4B,
        PF_IsEgg = 0x4C,
        PF_RibbonG3Cool = 0x4D,
        PF_RibbonG3CoolSuper = 0x4E,
        PF_RibbonG3CoolHyper = 0x4F,
        PF_RibbonG3CoolMaster = 0x50,
        PF_RibbonG3Beauty = 0x51,
        PF_RibbonG3BeautySuper = 0x52,
        PF_RibbonG3BeautyHyper = 0x53,
        PF_RibbonG3BeautyMaster = 0x54,
        PF_RibbonG3Cute = 0x55,
        PF_RibbonG3CuteSuper = 0x56,
        PF_RibbonG3CuteHyper = 0x57,
        PF_RibbonG3CuteMaster = 0x58,
        PF_RibbonG3Smart = 0x59,
        PF_RibbonG3SmartSuper = 0x5A,
        PF_RibbonG3SmartHyper = 0x5B,
        PF_RibbonG3SmartMaster = 0x5C,
        PF_RibbonG3Tough = 0x5D,
        PF_RibbonG3ToughSuper = 0x5E,
        PF_RibbonG3ToughHyper = 0x5F,
        PF_RibbonG3ToughMaster = 0x60,
        PF_RibbonChampionHoenn = 0x61,
        PF_RibbonWinning = 0x62,
        PF_RibbonVictory = 0x63,
        PF_RibbonArtist = 0x64,
        PF_RibbonEffort = 0x65,
        PF_RibbonChampionBattle = 0x66,
        PF_RibbonChampionRegional = 0x67,
        PF_RibbonChampionNational = 0x68,
        PF_RibbonCountry = 0x69,
        PF_RibbonNational = 0x6A,
        PF_RibbonEarth = 0x6B,
        PF_RibbonWorld = 0x6C,
        PF_FatefulEncounter = 0x6D,
        PF_Sex = 0x6E,
        PF_Forme = 0x6F,
        PF_Nature = 0x70,
        PF_IsHiddenAbility = 0x71,
        PF_NicknameStrBuf = 0x73,
        PF_NicknameRaw = 0x74,
        PF_HasNickname = 0x75,
        PF_MetGameVersion = 0x77,
        PF_RibbonG4Cool = 0x78,
        PF_RibbonG4CoolGreat = 0x79,
        PF_RibbonG4CoolUltra = 0x7A,
        PF_RibbonG4CoolMaster = 0x7B,
        PF_RibbonG4Beauty = 0x7C,
        PF_RibbonG4BeautyGreat = 0x7D,
        PF_RibbonG4BeautyUltra = 0x7E,
        PF_RibbonG4BeautyMaster = 0x7F,
        PF_RibbonG4Cute = 0x80,
        PF_RibbonG4CuteGreat = 0x81,
        PF_RibbonG4CuteUltra = 0x82,
        PF_RibbonG4CuteMaster = 0x83,
        PF_RibbonG4Smart = 0x84,
        PF_RibbonG4SmartGreat = 0x85,
        PF_RibbonG4SmartUltra = 0x86,
        PF_RibbonG4SmartMaster = 0x87,
        PF_RibbonG4Tough = 0x88,
        PF_RibbonG4ToughGreat = 0x89,
        PF_RibbonG4ToughUltra = 0x8A,
        PF_RibbonG4ToughMaster = 0x8B,
        PF_Ribbon0x8C = 0x8C,
        PF_OTNameStrBuf = 0x8D,
        PF_OTNameRaw = 0x8E,
        PF_HatchDateYear = 0x8F,
        PF_HatchDateMonth = 0x90,
        PF_HatchDateDay = 0x91,
        PF_MetYear = 0x92,
        PF_MetMonth = 0x93,
        PF_MetDay = 0x94,
        PF_HatchLocation = 0x95,
        PF_MetLocation = 0x96,
        PF_Pokerus = 0x97,
        PF_Pokeball = 0x98,
        PF_MetLevel = 0x99,
        PF_TrGender = 0x9A,
        PF_GroundTile = 0x9B,
        PF_StatusCond = 0x9D,
        PF_Level = 0x9E,
        PF_NowHP = 0xA0,
        PF_MaxHP = 0xA1,
        PF_ATK = 0xA2,
        PF_DEF = 0xA3,
        PF_SPE = 0xA4,
        PF_SPA = 0xA5,
        PF_SPD = 0xA6,
        PF_Mail = 0xA7,
        PF_IsSpeciesValid = 0xA9,
        PF_LegalSpecies = 0xAB,
        PF_IVsAll = 0xAC,
        PF_IsNotNidoran = 0xAD,
        PF_Type1 = 0xAE,
        PF_Type2 = 0xAF,
        PF_NicknameStrBufKeepFlags = 0xB0,
        PF_NicknameRawKeepFlags = 0xB1,
        PF_NPokemon = 0xB2,
        PF_PokestarFame = 0xB3,
    };
    enum PersonalField
    {
        Personal_HP = 0x0,
        Personal_ATK = 0x1,
        Personal_DEF = 0x2,
        Personal_SPE = 0x3,
        Personal_SPA = 0x4,
        Personal_SPD = 0x5,
        Personal_Type1 = 0x6,
        Personal_Type2 = 0x7,
        Personal_CaptureRate = 0x8,
        Personal_BaseEXP = 0x9,
        Personal_EvHP = 0xA,
        Personal_EvATK = 0xB,
        Personal_EvDEF = 0xC,
        Personal_EvSPE = 0xD,
        Personal_EvSPA = 0xE,
        Personal_EvSPD = 0xF,
        Personal_Telekinesis = 0x10,
        Personal_WildItem50 = 0x11,
        Personal_WildItem5 = 0x12,
        Personal_WildItem1 = 0x13,
        Personal_GenderProb = 0x14,
        Personal_EggHappiness = 0x15,
        Personal_BaseHappiness = 0x16,
        Personal_GrowthRate = 0x17,
        Personal_EggGroup1 = 0x18,
        Personal_EggGroup2 = 0x19,
        Personal_Abil1 = 0x1A,
        Personal_Abil2 = 0x1B,
        Personal_AbilH = 0x1C,
        Personal_EscapeRate = 0x1D,
        Personal_FormeDataOffs = 0x1E,
        Personal_FormeSpritesOffset = 0x1F,
        Personal_FormeCount = 0x20,
        Personal_Color = 0x21,
        Personal_SpriteFlip = 0x22,
        Personal_SpriteForme = 0x23,
        Personal_EvoStage = 0x24,
        Personal_Height = 0x25,
        Personal_Weight = 0x26,
        Personal_TMHM1 = 0x27,
        Personal_TMHM2 = 0x28,
        Personal_TMHM3 = 0x29,
        Personal_TMHM4 = 0x2A,
        Personal_TypeTutor = 0x2B,
        Personal_SpecialTutor1 = 0x2C,
        Personal_SpecialTutor2 = 0x2D,
        Personal_SpecialTutor3 = 0x2E,
        Personal_SpecialTutor4 = 0x2F,
    };
    extern u32 PokeParty_GetParam(PartyPkm *pPkm, PkmField field, void *extra);
    extern void PokeParty_SetParam(PartyPkm *pPkm, PkmField field, u32 data);
    extern void PokeParty_SetHiddenAbil(PartyPkm *pPkm, u16 species, u16 forme);
    extern u32 PML_PersonalGetParamSingle(u16 species, u16 form, PersonalField field);
    extern void PokeParty_SetNature(PartyPkm *pkm, u8 nature);

    void THUMB_BRANCH_TrainerUtil_SetupPkm(u16 trId, PartyPkm *pkm, u16 forme, u8 genderAndAbil)
    {
        u32 v5;           // r7
        int v6;           // r4
        PersonalField v7; // r6
        u32 ParamSingle;  // r0
        u8 v9;            // r1
        u32 data;         // [sp+0h] [bp-20h]
        u16 species;      // [sp+8h] [bp-18h]
        u32 movePP;
        data = forme;
        v5 = 255;
        v6 = 0;
        species = PokeParty_GetParam(pkm, PF_Species, 0);
        
        do
        {
            if (PokeParty_GetParam(pkm, (PkmField)(v6 + 54), 0) == 218)
            {
                v5 = 0;
            }
            // Checks if the move has 5 or less PP, if it does, sets the PP to 5
            movePP = PokeParty_GetParam(pkm, (PkmField)(v6 + 58), 0);
            if (movePP < 5)
            {
                PokeParty_SetParam(pkm, (PkmField)(v6 + 58), 5);
            }
            else
            {
                movePP += ((movePP / 5) * 3);
                PokeParty_SetParam(pkm, (PkmField)(v6 + 58), movePP);
            }
            ++v6;
        } while (v6 < 4);

        PokeParty_SetParam(pkm, PF_Happiness, v5);
        PokeParty_SetParam(pkm, PF_Forme, data);
        if ((genderAndAbil & 0xF0) == 48)
        {
            PokeParty_SetHiddenAbil(pkm, species, data);
        }
        else if ((genderAndAbil & 0xF0) != 0)
        {
            v7 = Personal_Abil1;
            if (PML_PersonalGetParamSingle(species, data, Personal_Abil2) && (genderAndAbil & 0xF0) == 32)
            {
                v7 = Personal_Abil2;
            }
            ParamSingle = PML_PersonalGetParamSingle(species, data, v7);
            PokeParty_SetParam(pkm, PF_Ability, ParamSingle);
        }
        PokeParty_GetParam(pkm, PF_PID, 0);
        PokeParty_SetNature(pkm, v9);
    }
}