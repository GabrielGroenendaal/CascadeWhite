#ifndef __POKE_PARAM_H
#define __POKE_PARAM_H

#include "swantypes.h"

ENUM_DECLARE(PkmField)

enum PkmField
#ifdef __cplusplus
: u32
#endif
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
SWAN_CPPTYPE_EX(pml, PokeParam, PkmField)

#endif //__POKE_PARAM_H
// Tchaikovsky code generator
