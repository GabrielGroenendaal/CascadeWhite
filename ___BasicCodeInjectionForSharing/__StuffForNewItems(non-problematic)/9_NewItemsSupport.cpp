#include "newitems_support.h"
#include "../settings.h"
#include "kPrint.h"
extern "C"
{

#if TOGGLE_TMS
    void THUMB_BRANCH_sub_21AD5A0(void *a1, int a2, int a3)
    {
        ShopUIWork *v4;          // r5
        int result;              // r0
        unsigned int BlockWidth; // r6
        GFLBitmap *Bitmap;       // r0
        u32 Width;               // r7
        GFLBitmap *v9;           // r0
        unsigned int v10;        // r6
        GFLBitmap *v11;          // r0
        u32 v12;                 // r7
        GFLBitmap *v13;          // r0

        v4 = sub_2026548(a1);
        result = -2;
        if (a2 != -2)
        {
            if (BagSave_CheckAmount(v4->Bag, v4->ItemInfo[a2].TagID, 1) && !PML_ItemIsTMHM(v4->ItemInfo[a2].TagID))
            {
                BlockWidth = GFL_FontGetBlockWidth(v4->NoneDispStr, v4->m_Font, 0);
                Bitmap = BmpWin_GetBitmap((BmpWin *)v4->dword194);
                Width = GFL_BitmapGetWidth(Bitmap);
                v9 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
                sub_21AD4CC(v4->dword1D8, v9, Width - BlockWidth, a3, v4->NoneDispStr, v4->m_Font, 12704);
            }
            else
            {
                WordSetNumber(v4->WordSet, 1, v4->ItemInfo[a2].Price, 5u, 1u, 1);
                GFL_WordSetFormatStrbuf(v4->WordSet, v4->StrBuff, v4->BalanceDispStr);
                v10 = GFL_FontGetBlockWidth(v4->StrBuff, v4->m_Font, 0);
                v11 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
                v12 = GFL_BitmapGetWidth(v11);
                v13 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
                sub_21AD4CC(v4->dword1D8, v13, v12 - v10, a3, v4->StrBuff, v4->m_Font, 12704);
            }
        }
    }
#endif

    int THUMB_BRANCH_SAFESTACK_TransformVsPokePartyBySeason(GameData *gameData, PokeParty *party, Season s)
    {
       // void *Pokedex; // r7
        int result;    // r0
        // int v6;        // r4
        // PartyPkm *Pkm; // r5
        // u32 Param;     // r6
        // u32 v9;        // r0
        // int v11;       // [sp+4h] [bp-34h]
        // int v12;       // [sp+8h] [bp-30h]
        // int i;         // [sp+14h] [bp-24h]
        // int forme;
        // Pokedex = GameData_GetPokedex(gameData);
        // v12 = 0;
        // v11 = 0;
        // if ((unsigned int)s <= SEASON_WINTER)
        // {
        //     if (s == SEASON_SPRING)
        //     {
        //         forme = 0;
        //     }
        //     else if (s == SEASON_SUMMER)
        //     {
        //         forme = 1;
        //     }
        //     else if (s == SEASON_AUTUMN)
        //     {
        //         forme = 2;
        //     }
        //     else if (s == SEASON_WINTER)
        //     {
        //         forme = 3;
        //     }
        //     else
        //     {
        //         forme = 0;
        //     }
        //     //__asm { ADD     PC, R0 }
        // }
        // result = PokeParty_GetPkmCount(party);
        // v6 = 0;
        // for (i = result; v6 < i; ++v6)
        // {
        //     Pkm = PokeParty_GetPkm(party, v6);
        //     Param = PokeParty_GetParam(Pkm, PF_Species, 0);
        //     v9 = PokeParty_GetParam(Pkm, PF_Forme, 0);
        //     if (Param == 585 && v9)
        //     {
        //         k::Printf("\n\nWe are in the function to transform Deerling into spring forme, maybe?\n\n");
        //         // PokeParty_ChangeForme(Pkm, forme);
        //         if (!v12)
        //         {
        //             PokeDex_RegistPkm(Pokedex, Pkm);
        //             v12 = 1;
        //         }
        //     }
        //     else if (Param == 586)
        //     {
        //         if (v9)
        //         {
        //             // PokeParty_ChangeForme(Pkm, forme);
        //             if (!v11)
        //             {
        //                 PokeDex_RegistPkm(Pokedex, Pkm);
        //                 v11 = 1;
        //             }
        //         }
        //     }
        //     result = i;
        // }
        return result;
    }

    int THUMB_BRANCH_FieldEncount_CreateWildPkm(PartyPkm *pPkm, EncountManager *mgr, WildPokemonParam *pkmData)
    {
        u32 pid;                  // r7
        u32 baseShinyRerollCount; // r6
        BagSaveData *Bag;         // r0
        u32 v8;                   // r0
        u32 rareRerollIndex;      // r6
        u32 HeldItem;             // r2
        u32 TrainerGender;        // r0
        wchar_t *PlayerName;      // r0
        int result;               // r0
        u16* pTrainerInfo;
        u32 rareRerollCount;      // [sp+14h] [bp-1Ch]
        PersonalData *personal;   // [sp+18h] [bp-18h]
        u32 random;


        pTrainerInfo = GetGameDataPlayerInfo(mgr->gameData);
        personal = PML_PersonalLoad(pkmData->Species, pkmData->Forme, HEAPID_GAMEEVENT);
        baseShinyRerollCount = 1;
        Bag = GameData_GetBag(mgr->gameData);
        if (BagSave_CheckAmount(Bag, 632, 1))
        {
            baseShinyRerollCount = 3;
        }
        v8 = PassPower_ApplyLuckyShiny(baseShinyRerollCount);
        rareRerollIndex = 0;
        for (rareRerollCount = v8; rareRerollIndex < rareRerollCount; ++rareRerollIndex)
        {
            pid = FieldEncount_GenPID(mgr, personal, pkmData);
            if (PML_UtilPIDIsRare(mgr->PTID, pid))
            {
                break;
            }
        }
        PokeParty_CreatePkm(pPkm, (MonsNo)pkmData->Species, pkmData->Level, mgr->PTID, ABIL_0, 0xFFFFFFFF, pid, 0);
        PokeParty_ChangeForme(pPkm, pkmData->Forme);

        if (pkmData->Species == 585)
        {
            random = GFL_RandomLCAlt(100u);

            if (random <= 25u)
            {
                PokeParty_ChangeForme(pPkm, 0);
            }
            else if (random > 25u && random <= 50u)
            {
                PokeParty_ChangeForme(pPkm, 1);
            }
            else if (random > 50u && random <= 75u)
            {
                PokeParty_ChangeForme(pPkm, 2);
            }
            else if (random > 75u && random <= 100u)
            {
                PokeParty_ChangeForme(pPkm, 3);
            }
            else
            {
                PokeParty_ChangeForme(pPkm, 0);
            }
        }

        PokeParty_SetDefaultMoves(pPkm);
        if (pkmData->HiddenAbility)
        {
            PokeParty_SetHiddenAbil(pPkm, pkmData->Species, pkmData->Forme);
        }
        HeldItem = pkmData->HeldItem;
        if (HeldItem <= 0x27E)
        {
            if (pkmData->HeldItem)
            {
                PokeParty_SetParam(pPkm, PF_Item, HeldItem);
            }
            else
            {
                FieldEncount_SetRandomHeldItem(
                    pPkm,
                    personal,
                    (unsigned int)(mgr->Flags << 22) >> 31,
                    mgr->EncType == ENCTYPE_LAND_DOUBLE);
            }
        }
        TrainerGender = getTrainerGender(pTrainerInfo);
        PokeParty_SetParam(pPkm, PF_TrGender, TrainerGender);
        PlayerName = GetPlayerName((int)pTrainerInfo);
        PokeParty_SetParam(pPkm, PF_OTNameRaw, (u32)PlayerName);
        if ((mgr->Flags & 0x400) != 0)
        {
            PokeParty_SetParam(pPkm, PF_Nature, mgr->PPkNature);
        }
        PokeParty_RecalcStats(pPkm);
        PML_PersonalFree(personal);
        return result;
    }
}