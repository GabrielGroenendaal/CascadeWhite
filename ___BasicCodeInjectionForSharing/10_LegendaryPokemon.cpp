#include "codeinjection_new.h"
#include "kPrint.h"

extern "C"
{

    // void THUMB_BRANCH_TrainerUtil_LoadParty(int trId, PokeParty *party, HeapID heapId)
    // {
    //     HeapID v3;          // r4
    //     u32 PkmRawSize;     // r0
    //     PartyPkm *v5;       // r4
    //     u32 v6;             // r0
    //     unsigned int Flags; // r0
    //     int v8;             // r5
    //     int v9;             // r2
    //     int v10;            // r3
    //     __int64 v11;        // r0
    //     __int64 v12;        // kr08_8
    //     int v13;            // r0
    //     char *v14;          // r6
    //     int v15;            // r5
    //     int v16;            // r2
    //     __int64 v17;        // r0
    //     int v18;            // r0
    //     int v19;            // r5
    //     int v20;            // r5
    //     int v21;            // r2
    //     int v22;            // r3
    //     __int64 v23;        // r0
    //     __int64 v24;        // kr10_8
    //     int v25;            // r0
    //     char *v26;          // r6
    //     int v27;            // r5
    //     int v28;            // r2
    //     __int64 v29;        // r0
    //     int v30;            // r0
    //     int v31;            // r5
    //     char *v32;          // r7
    //     int v36;            // [sp+24h] [bp-74h]
    //     int v37;            // [sp+28h] [bp-70h]
    //     int v38;            // [sp+2Ch] [bp-6Ch]
    //     char *v39;          // [sp+30h] [bp-68h]
    //     char *v40;          // [sp+34h] [bp-64h]
    //     MonsNo v41;         // [sp+38h] [bp-60h]
    //     int v42;            // [sp+3Ch] [bp-5Ch]
    //     int v43;            // [sp+40h] [bp-58h]
    //     MonsNo v44;         // [sp+44h] [bp-54h]
    //     int v45;            // [sp+48h] [bp-50h]
    //     int v46;            // [sp+4Ch] [bp-4Ch]
    //     MonsNo v47;         // [sp+50h] [bp-48h]
    //     int v48;            // [sp+54h] [bp-44h]
    //     int v49;            // [sp+58h] [bp-40h]
    //     MonsNo species;     // [sp+5Ch] [bp-3Ch]
    //     int level;          // [sp+60h] [bp-38h]
    //     int v52;            // [sp+64h] [bp-34h]
    //     char *dest;         // [sp+68h] [bp-30h]
    //     int v54;            // [sp+6Ch] [bp-2Ch]
    //     TrainerData *heap;  // [sp+70h] [bp-28h]
    //     u32 v56[7];         // [sp+7Ch] [bp-1Ch] BYREF

    //     PokeParty_InitCore(party, 6);
    //     v3 = heapId & 0x7FFF | 0x8000;
    //     heap = (TrainerData *)GFL_HeapAllocate(v3, 0x14u, 0, "tr_tool.c", 0x23Du);
    //     dest = (char *)GFL_HeapAllocate(v3, 0x6Cu, 0, "tr_tool.c", 0x23Eu);
    //     PkmRawSize = PokeParty_GetPkmRawSize();
    //     v5 = (PartyPkm *)GFL_HeapAllocate(v3, PkmRawSize, 0, "tr_tool.c", 0x23Fu);
    //     TrainerData_ReadTrainerData(trId, heap);
    //     TrainerData_ReadParty(trId, dest);
    //     if (TrainerClass_GetSex(heap->Class) == 1)
    //     {
    //         v6 = 120;
    //     }
    //     else
    //     {
    //         v6 = 136;
    //     }
    //     v56[0] = v6;
    //     Flags = heap->Flags;
    //     if (Flags <= 3)
    //     {

    //         if (IsEqual(Flags, 0))
    //         {
    //             v54 = 0;
    //             if (heap->PokemonCount)
    //             {
    //                 do
    //                 {
    //                     v40 = &dest[8 * v54];
    //                     TrainerUtil_CalcBasePID(*(v40 + 2), *(v40 + 3), v40[1], v56, heapId);
    //                     level = *(v40 + 1);
    //                     v8 = 0;
    //                     v52 = *v40;
    //                     species = (MonsNo) * (v40 + 2);
    //                     v9 = trId + species + v52 + level;
    //                     v10 = v9;
    //                     //HIDWORD(v11) = 0;
    //                     v11 = (v11 & 0x00000000ffffffff);
    //                     if (heap->Class)
    //                     {
    //                         do
    //                         {
    //                             //LODWORD(v11) = v10;
    //                             v11 = (v11 & 0xffffffff00000000) | v10;
    //                             v12 = 0x5D588B656C078965LL * v11 + 2531011;
    //                             //HIDWORD(v11) = HIDWORD(v12);
    //                             v11 = (v11 & 0x00000000ffffffff) | (v12 & 0xffffffff00000000);
    //                             v10 = v12;
    //                             ++v8;
    //                             //v9 = HIWORD(HIDWORD(v12));
    //                             v9 = (v12 & 0xffff000000000000);
    //                         } while (v8 < heap->Class);
    //                     }
    //                     v13 = 31 * v52 / 255;
    //                     PokeParty_CreatePkm(
    //                         v5,
    //                         species,
    //                         level,
    //                         0,
    //                         -1,
    //                         (32 * (v13 & 0x1F)) | v13 & 0x1F | ((v13 & 0x1F) << 10) | ((v13 & 0x1F) << 15) | ((v13 & 0x1F) << 20) | ((v13 & 0x1F) << 25),
    //                         (v9 << 8) + v56[0],
    //                         0);

    //                     if (trId == 491)
    //                     {
    //                         PokeParty_SetParam(v5, PF_Pokeball, IT0494_LURE_BALL);
    //                     }
    //                     TrainerUtil_SetupPkm(trId, v5, *(v40 + 3), v40[1]);
    //                     PokeParty_AddPkm(party, v5);
    //                     ++v54;
    //                 } while (v54 < heap->PokemonCount);
    //             }
    //         }
    //         else if (IsEqual(Flags, 1))
    //         {
    //             v36 = 0;
    //             if (heap->PokemonCount)
    //             {
    //                 do
    //                 {
    //                     v14 = &dest[16 * v36];
    //                     TrainerUtil_CalcBasePID(*(v14 + 2), *(v14 + 3), v14[1], v56, heapId);
    //                     v48 = *(v14 + 1);
    //                     v15 = 0;
    //                     v49 = *v14;
    //                     v47 = (MonsNo) * (v14 + 2);
    //                     v16 = trId + v47 + v49 + v48;
    //                     v17 = v16;
    //                     if (heap->Class)
    //                     {
    //                         do
    //                         {
    //                             v17 = 0x5D588B656C078965LL * v17 + 2531011;
    //                             ++v15;
    //                             //v16 = HIWORD(HIDWORD(v17));
    //                             v16 = (v17 & 0xffff000000000000);
    //                         } while (v15 < heap->Class);
    //                     }
    //                     v18 = 31 * v49 / 255;
    //                     v19 = 0;
    //                     PokeParty_CreatePkm(
    //                         v5,
    //                         v47,
    //                         v48,
    //                         0,
    //                         -1,
    //                         (32 * (v18 & 0x1F)) | v18 & 0x1F | ((v18 & 0x1F) << 10) | ((v18 & 0x1F) << 15) | ((v18 & 0x1F) << 20) | ((v18 & 0x1F) << 25),
    //                         (v16 << 8) + v56[0],
    //                         0);
    //                     do
    //                     {
    //                         PokeParty_SetMove(v5, (MoveID) * &v14[2 * v19 + 8], v19);
    //                         ++v19;
    //                     } while (v19 < 4);
    //                     if (trId == 491)
    //                     {
    //                         PokeParty_SetParam(v5, PF_Pokeball, IT0494_LURE_BALL);
    //                     }
    //                     TrainerUtil_SetupPkm(trId, v5, *&dest[16 * v36 + 6], dest[16 * v36 + 1]);
    //                     PokeParty_AddPkm(party, v5);
    //                     ++v36;
    //                 } while (v36 < heap->PokemonCount);
    //             }
    //         }
    //         else if (IsEqual(Flags, 2))
    //         {
    //             v37 = 0;
    //             if (heap->PokemonCount)
    //             {
    //                 do
    //                 {
    //                     v39 = &dest[10 * v37];
    //                     TrainerUtil_CalcBasePID(*(v39 + 2), *(v39 + 3), v39[1], v56, heapId);
    //                     v45 = *(v39 + 1);
    //                     v20 = 0;
    //                     v46 = *v39;
    //                     v44 = (MonsNo) * (v39 + 2);
    //                     v21 = trId + v44 + v46 + v45;
    //                     v22 = v21;
    //                     //HIDWORD(v23) = 0;
    //                     v23 = (v23 & 0x00000000ffffffff);
    //                     if (heap->Class)
    //                     {
    //                         do
    //                         {
    //                             //LODWORD(v23) = v22;
    //                             v23 = (v23 & 0xffffffff00000000) | v22;
    //                             v24 = 0x5D588B656C078965LL * v23 + 2531011;
    //                             //HIDWORD(v23) = HIDWORD(v24);
    //                             v23 = (v23 & 0x00000000ffffffff) | (v24 & 0xffffffff00000000);
    //                             v22 = v24;
    //                             ++v20;
    //                             //v21 = HIWORD(HIDWORD(v24));
    //                             v21 = (v24 & 0xffff000000000000);
    //                         } while (v20 < heap->Class);
    //                     }
    //                     v25 = 31 * v46 / 255;
    //                     PokeParty_CreatePkm(
    //                         v5,
    //                         v44,
    //                         v45,
    //                         0,
    //                         -1,
    //                         (32 * (v25 & 0x1F)) | v25 & 0x1F | ((v25 & 0x1F) << 10) | ((v25 & 0x1F) << 15) | ((v25 & 0x1F) << 20) | ((v25 & 0x1F) << 25),
    //                         (v21 << 8) + v56[0],
    //                         0);
    //                     PokeParty_SetParam(v5, PF_Item, *(v39 + 4));
    //                     if (trId == 491)
    //                     {
    //                         PokeParty_SetParam(v5, PF_Pokeball, IT0494_LURE_BALL);
    //                     }
    //                     TrainerUtil_SetupPkm(trId, v5, *(v39 + 3), v39[1]);
    //                     PokeParty_AddPkm(party, v5);
    //                     ++v37;
    //                 } while (v37 < heap->PokemonCount);
    //             }
    //         }
    //         else if (IsEqual(Flags, 3))
    //         {
    //             v38 = 0;
    //             if (heap->PokemonCount)
    //             {
    //                 do
    //                 {
    //                     v26 = &dest[18 * v38];
    //                     TrainerUtil_CalcBasePID(*(v26 + 2), *(v26 + 3), v26[1], v56, heapId);
    //                     v42 = *(v26 + 1);
    //                     v27 = 0;
    //                     v43 = *v26;
    //                     v41 = (MonsNo) * (v26 + 2);
    //                     v28 = trId + v41 + v43 + v42;
    //                     v29 = v28;
    //                     if (heap->Class)
    //                     {
    //                         do
    //                         {
    //                             v29 = 0x5D588B656C078965LL * v29 + 2531011;
    //                             ++v27;
    //                             //v28 = HIWORD(HIDWORD(v29));
    //                             v28 = (v29 & 0xffff000000000000);
    //                         } while (v27 < heap->Class);
    //                     }
    //                     v30 = 31 * v43 / 255;
    //                     v31 = 0;
    //                     PokeParty_CreatePkm(
    //                         v5,
    //                         v41,
    //                         v42,
    //                         0,
    //                         -1,
    //                         (32 * (v30 & 0x1F)) | v30 & 0x1F | ((v30 & 0x1F) << 10) | ((v30 & 0x1F) << 15) | ((v30 & 0x1F) << 20) | ((v30 & 0x1F) << 25),
    //                         (v28 << 8) + v56[0],
    //                         0);
    //                     v32 = &dest[18 * v38];
    //                     PokeParty_SetParam(v5, PF_Item, *(v32 + 4));
    //                     do
    //                     {
    //                         PokeParty_SetMove(v5, (MoveID) * &v26[2 * v31 + 10], v31);
    //                         ++v31;
    //                     } while (v31 < 4);
    //                     TrainerUtil_SetupPkm(trId, v5, *(v32 + 3), v32[1]);
    //                     PokeParty_AddPkm(party, v5);
    //                     ++v38;
    //                 } while (v38 < heap->PokemonCount);
    //             }
    //         }
    //         else
    //         {
    //         }
    //         // switch (*(&jpt_2030984 + Flags))
    //         // {
    //         // case 0:
    //         //     v54 = 0;
    //         //     if (heap->PokemonCount)
    //         //     {
    //         //         do
    //         //         {
    //         //             v40 = &dest[8 * v54];
    //         //             TrainerUtil_CalcBasePID(*(v40 + 2), *(v40 + 3), v40[1], v56, heapId);
    //         //             level = *(v40 + 1);
    //         //             v8 = 0;
    //         //             v52 = *v40;
    //         //             species = *(v40 + 2);
    //         //             v9 = trId + species + v52 + level;
    //         //             v10 = v9;
    //         //             HIDWORD(v11) = 0;
    //         //             if (heap->Class)
    //         //             {
    //         //                 do
    //         //                 {
    //         //                     LODWORD(v11) = v10;
    //         //                     v12 = 0x5D588B656C078965LL * v11 + 2531011;
    //         //                     HIDWORD(v11) = HIDWORD(v12);
    //         //                     v10 = v12;
    //         //                     ++v8;
    //         //                     v9 = HIWORD(HIDWORD(v12));
    //         //                 } while (v8 < heap->Class);
    //         //             }
    //         //             v13 = 31 * v52 / 255;
    //         //             PokeParty_CreatePkm(
    //         //                 v5,
    //         //                 species,
    //         //                 level,
    //         //                 0,
    //         //                 -1,
    //         //                 (32 * (v13 & 0x1F)) | v13 & 0x1F | ((v13 & 0x1F) << 10) | ((v13 & 0x1F) << 15) | ((v13 & 0x1F) << 20) | ((v13 & 0x1F) << 25),
    //         //                 (v9 << 8) + v56[0],
    //         //                 0);
    //         //             TrainerUtil_SetupPkm(trId, v5, *(v40 + 3), v40[1]);
    //         //             PokeParty_AddPkm(party, v5);
    //         //             ++v54;
    //         //         } while (v54 < heap->PokemonCount);
    //         //     }
    //         //     break;
    //         // case 1:
    //         //     v36 = 0;
    //         //     if (heap->PokemonCount)
    //         //     {
    //         //         do
    //         //         {
    //         //             v14 = &dest[16 * v36];
    //         //             TrainerUtil_CalcBasePID(*(v14 + 2), *(v14 + 3), v14[1], v56, heapId);
    //         //             v48 = *(v14 + 1);
    //         //             v15 = 0;
    //         //             v49 = *v14;
    //         //             v47 = *(v14 + 2);
    //         //             v16 = trId + v47 + v49 + v48;
    //         //             v17 = v16;
    //         //             if (heap->Class)
    //         //             {
    //         //                 do
    //         //                 {
    //         //                     v17 = 0x5D588B656C078965LL * v17 + 2531011;
    //         //                     ++v15;
    //         //                     v16 = HIWORD(HIDWORD(v17));
    //         //                 } while (v15 < heap->Class);
    //         //             }
    //         //             v18 = 31 * v49 / 255;
    //         //             v19 = 0;
    //         //             PokeParty_CreatePkm(
    //         //                 v5,
    //         //                 v47,
    //         //                 v48,
    //         //                 0,
    //         //                 -1,
    //         //                 (32 * (v18 & 0x1F)) | v18 & 0x1F | ((v18 & 0x1F) << 10) | ((v18 & 0x1F) << 15) | ((v18 & 0x1F) << 20) | ((v18 & 0x1F) << 25),
    //         //                 (v16 << 8) + v56[0],
    //         //                 0);
    //         //             do
    //         //             {
    //         //                 PokeParty_SetMove(v5, *&v14[2 * v19 + 8], v19);
    //         //                 ++v19;
    //         //             } while (v19 < 4);
    //         //             TrainerUtil_SetupPkm(trId, v5, *&dest[16 * v36 + 6], dest[16 * v36 + 1]);
    //         //             PokeParty_AddPkm(party, v5);
    //         //             ++v36;
    //         //         } while (v36 < heap->PokemonCount);
    //         //     }
    //         //     break;
    //         // case 2:
    //         //     v37 = 0;
    //         //     if (heap->PokemonCount)
    //         //     {
    //         //         do
    //         //         {
    //         //             v39 = &dest[10 * v37];
    //         //             TrainerUtil_CalcBasePID(*(v39 + 2), *(v39 + 3), v39[1], v56, heapId);
    //         //             v45 = *(v39 + 1);
    //         //             v20 = 0;
    //         //             v46 = *v39;
    //         //             v44 = *(v39 + 2);
    //         //             v21 = trId + v44 + v46 + v45;
    //         //             v22 = v21;
    //         //             HIDWORD(v23) = 0;
    //         //             if (heap->Class)
    //         //             {
    //         //                 do
    //         //                 {
    //         //                     LODWORD(v23) = v22;
    //         //                     v24 = 0x5D588B656C078965LL * v23 + 2531011;
    //         //                     HIDWORD(v23) = HIDWORD(v24);
    //         //                     v22 = v24;
    //         //                     ++v20;
    //         //                     v21 = HIWORD(HIDWORD(v24));
    //         //                 } while (v20 < heap->Class);
    //         //             }
    //         //             v25 = 31 * v46 / 255;
    //         //             PokeParty_CreatePkm(
    //         //                 v5,
    //         //                 v44,
    //         //                 v45,
    //         //                 0,
    //         //                 -1,
    //         //                 (32 * (v25 & 0x1F)) | v25 & 0x1F | ((v25 & 0x1F) << 10) | ((v25 & 0x1F) << 15) | ((v25 & 0x1F) << 20) | ((v25 & 0x1F) << 25),
    //         //                 (v21 << 8) + v56[0],
    //         //                 0);
    //         //             PokeParty_SetParam(v5, PF_Item, *(v39 + 4));
    //         //             TrainerUtil_SetupPkm(trId, v5, *(v39 + 3), v39[1]);
    //         //             PokeParty_AddPkm(party, v5);
    //         //             ++v37;
    //         //         } while (v37 < heap->PokemonCount);
    //         //     }
    //         //     break;
    //         // case 3:
    //         //     v38 = 0;
    //         //     if (heap->PokemonCount)
    //         //     {
    //         //         do
    //         //         {
    //         //             v26 = &dest[18 * v38];
    //         //             TrainerUtil_CalcBasePID(*(v26 + 2), *(v26 + 3), v26[1], v56, heapId);
    //         //             v42 = *(v26 + 1);
    //         //             v27 = 0;
    //         //             v43 = *v26;
    //         //             v41 = *(v26 + 2);
    //         //             v28 = trId + v41 + v43 + v42;
    //         //             v29 = v28;
    //         //             if (heap->Class)
    //         //             {
    //         //                 do
    //         //                 {
    //         //                     v29 = 0x5D588B656C078965LL * v29 + 2531011;
    //         //                     ++v27;
    //         //                     v28 = HIWORD(HIDWORD(v29));
    //         //                 } while (v27 < heap->Class);
    //         //             }
    //         //             v30 = 31 * v43 / 255;
    //         //             v31 = 0;
    //         //             PokeParty_CreatePkm(
    //         //                 v5,
    //         //                 v41,
    //         //                 v42,
    //         //                 0,
    //         //                 -1,
    //         //                 (32 * (v30 & 0x1F)) | v30 & 0x1F | ((v30 & 0x1F) << 10) | ((v30 & 0x1F) << 15) | ((v30 & 0x1F) << 20) | ((v30 & 0x1F) << 25),
    //         //                 (v28 << 8) + v56[0],
    //         //                 0);
    //         //             v32 = &dest[18 * v38];
    //         //             PokeParty_SetParam(v5, PF_Item, *(v32 + 4));
    //         //             do
    //         //             {
    //         //                 PokeParty_SetMove(v5, *&v26[2 * v31 + 10], v31);
    //         //                 ++v31;
    //         //             } while (v31 < 4);
    //         //             TrainerUtil_SetupPkm(trId, v5, *(v32 + 3), v32[1]);
    //         //             PokeParty_AddPkm(party, v5);
    //         //             ++v38;
    //         //         } while (v38 < heap->PokemonCount);
    //         //     }
    //         //     break;
    //         // default:
    //         //     break;
    //         // }
    //     }
    //     GFL_HeapFree(heap);
    //     GFL_HeapFree(dest);
    //     GFL_HeapFree(v5);
    // }

    int THUMB_BRANCH_SAFESTACK_ServerCommand_SwitchIn_0(BtlClientWk *a1, int *a2, _DWORD *a3)
    {
        int v5;                   // r4
        int v6;                   // r7
        int v7;                   // r0
        BattleMon *ClientMonData; // r0
        int ID;                   // r7
        __int16 MemberPutStrID;   // r0
        int ClientPokePos;        // r0

        v5 = *a3;
        v6 = a3[1];
        v7 = *a2;
        k::Printf("\n\nCheck 1: Function Start");
        if (!*a2)
        {
            k::Printf("\nCheck 2");

            if (!a3[3])
            {
                k::Printf("\nCheck 3");
                goto LABEL_14;
            }
            k::Printf("\nCheck 4");
            ClientMonData = PokeCon_GetClientMonData(a1->pokeCon, *a3, a3[1]);
            ID = BattleMon_GetID(ClientMonData);
            if (IsOpponentClientID(a1->mainModule, a1->myID, v5))
            {
                if (TrainerParam_HasTrainerInfo(a1->mainModule, v5))
                {
                    // Cobalion
                    k::Printf("\nCheck 5");
                    if (IsEqual(a1->mainModule->trainerParam[v5].ID, 491))
                    {
                        k::Printf("\nCheck 6");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 214);
                        Btlv_StringParam_AddArg(&a1->strParam, v5);
                        Btlv_StringParam_AddArg(&a1->strParam, ID);
                        sub_21D022C((BtlvCore *)a1->btlvCore, &a1->strParam);
                        goto LABEL_14;
                    }
                    // Virizion
                    else if (IsEqual(a1->mainModule->trainerParam[v5].ID, 507))
                    {
                        k::Printf("\nCheck 7");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 217);
                        Btlv_StringParam_AddArg(&a1->strParam, v5);
                        Btlv_StringParam_AddArg(&a1->strParam, ID);
                        sub_21D022C((BtlvCore *)a1->btlvCore, &a1->strParam);
                        goto LABEL_14;
                    }
                    // Terrakion
                    else if (IsEqual(a1->mainModule->trainerParam[v5].ID, 508))
                    {
                        k::Printf("\nCheck 8");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 220);
                        Btlv_StringParam_AddArg(&a1->strParam, v5);
                        Btlv_StringParam_AddArg(&a1->strParam, ID);
                        sub_21D022C((BtlvCore *)a1->btlvCore, &a1->strParam);
                        goto LABEL_14;
                    }
                    // Keldeo
                    else if (IsEqual(a1->mainModule->trainerParam[v5].ID, 509))
                    {
                        k::Printf("\nCheck 9");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 223);
                        Btlv_StringParam_AddArg(&a1->strParam, v5);
                        Btlv_StringParam_AddArg(&a1->strParam, ID);
                        sub_21D022C((BtlvCore *)a1->btlvCore, &a1->strParam);
                        goto LABEL_14;
                    }
                    else
                    {
                        k::Printf("\nCheck 10");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 14);
                        Btlv_StringParam_AddArg(&a1->strParam, v5);
                        goto LABEL_13;
                    }
                }
            }
            else if (a1->myID == v5)
            {
                k::Printf("\nCheck 11");
                MemberPutStrID = GetMemberPutStrID(a1);
                Btlv_StringParam_Setup(&a1->strParam, 1, MemberPutStrID);
            LABEL_13:
                Btlv_StringParam_AddArg(&a1->strParam, ID);
                sub_21D022C((BtlvCore *)a1->btlvCore, &a1->strParam);
                goto LABEL_14;
            }
            Btlv_StringParam_Setup(&a1->strParam, 1, 17);
            Btlv_StringParam_AddArg(&a1->strParam, v5);
            goto LABEL_13;
        }
        if (v7 == 1)
        {
            k::Printf("\nCheck 12");

            if (!BattleViewCmd_WaitMessage((BtlvCore *)a1->btlvCore))
            {
                return 0;
            }
            k::Printf("\nCheck 13");
            ClientPokePos = MainModule_GetClientPokePos(a1->mainModule, v5, v6);
            sub_21D0088((BtlvCore *)a1->btlvCore, ClientPokePos, v5, v6);
        LABEL_14:
            ++*a2;
            return 0;
        }
        k::Printf("\nCheck 14, v7 = %d, function = %d", v7, sub_21D00C4((BtlvCore *)a1->btlvCore));
        if (v7 != 2 || !sub_21D00C4((BtlvCore *)a1->btlvCore))
        {

            
            return 0;
        }
        k::Printf("\nCheck 15. v7 = %d, function = %d", v7, sub_21D00C4((BtlvCore *)a1->btlvCore));
        sub_21B1F24(a1);

        if (v5 == GetPlayerClientID(a1->mainModule))

        {
            k::Printf("\nCheck 16\n\n");
            sub_21B9730(a1, &a1->field_1C4, a1->actPokeParty);
        }
        return 1;
    }

    // int THUMB_BRANCH_ServerCommand_SwitchIn_0(BtlClientWk *a1, int *a2, _DWORD *a3)
    // {
    //     int v5;                   // r4
    //     int v6;                   // r7
    //     int v7;                   // r0
    //     BattleMon *ClientMonData; // r0
    //     int ID;                   // r7
    //     __int16 MemberPutStrID;   // r0
    //     int ClientPokePos;        // r0

    //     v5 = *a3;
    //     v6 = a3[1];
    //     v7 = *a2;
    //     if (!*a2)
    //     {
    //         if (!a3[3])
    //         {
    //             goto LABEL_14;
    //         }
    //         ClientMonData = PokeCon_GetClientMonData(a1->pokeCon, *a3, a3[1]);
    //         ID = BattleMon_GetID(ClientMonData);
    //         if (IsOpponentClientID(a1->mainModule, a1->myID, v5))
    //         {
    //             if (TrainerParam_HasTrainerInfo(a1->mainModule, v5))
    //             {
    //                 Btlv_StringParam_Setup(&a1->strParam, 1, 14);
    //                 Btlv_StringParam_AddArg(&a1->strParam, v5);
    //                 goto LABEL_13;
    //             }
    //         }
    //         else if (a1->myID == v5)
    //         {
    //             MemberPutStrID = GetMemberPutStrID(a1);
    //             Btlv_StringParam_Setup(&a1->strParam, 1, MemberPutStrID);
    //         LABEL_13:
    //             Btlv_StringParam_AddArg(&a1->strParam, ID);
    //             sub_21D022C((BtlvCore *)a1->btlvCore, &a1->strParam);
    //             goto LABEL_14;
    //         }
    //         Btlv_StringParam_Setup(&a1->strParam, 1, 17);
    //         Btlv_StringParam_AddArg(&a1->strParam, v5);
    //         goto LABEL_13;
    //     }
    //     if (v7 == 1)
    //     {
    //         if (!BattleViewCmd_WaitMessage((BtlvCore *)a1->btlvCore))
    //         {
    //             return 0;
    //         }
    //         ClientPokePos = MainModule_GetClientPokePos(a1->mainModule, v5, v6);
    //         sub_21D0088((BtlvCore *)a1->btlvCore, ClientPokePos, v5, v6);
    //     LABEL_14:
    //         ++*a2;
    //         return 0;
    //     }
    //     if (v7 != 2 || !sub_21D00C4((BtlvCore *)a1->btlvCore))
    //     {
    //         return 0;
    //     }
    //     sub_21B1F24(a1);
    //     if (v5 == GetPlayerClientID(a1->mainModule))
    //     {
    //         sub_21B9730(a1, &a1->field_1C4, a1->actPokeParty);
    //     }
    //     return 1;
    // }
    // int THUMB_BRANCH_ServerCommand_SwitchOutMessage(BtlClientWk *a1, int *a2, int *a3)
    // {
    //     int v4;                 // r1
    //     __int16 SwitchOutStrID; // r0
    //     int v9[6];              // [sp+0h] [bp-18h] BYREF

    //     v4 = *a2;
    //     if (v4)
    //     {
    //         if (v4 == 1 && BattleViewCmd_WaitMessage(a1->BtlvCore))
    //         {
    //             return 1;
    //         }
    //     }
    //     else
    //     {
    //         SwitchOutStrID = GetSwitchOutStrID(a1, *a3, v9);
    //         Btlv_StringParam_Setup(&a1->strParam, 1, SwitchOutStrID);
    //         if (v9[0])
    //         {
    //             Btlv_StringParam_AddArg(&a1->strParam, *a3);
    //         }
    //         Btlv_StringParam_AddArg(&a1->strParam, a3[1]);
    //         sub_21D022C(a1->BtlvCore, &a1->strParam);
    //         ++*a2;
    //     }
    //     return 0;
    // }

    int THUMB_BRANCH_GetSwitchOutStrID(BtlClientWk *a1, int a2, _DWORD *a3)
    {
        unsigned int v4; // r0
        v4 = 0x43;
        if (a2 == a1->myID)
        {
            *a3 = 0;
            if (BtlSetup_GetBattleStyle(a1->mainModule) || MainModule_GetCommMode(a1->mainModule))
            {
                return 26;
            }
            else
            {
                v4 = sub_21B1F40(a1);
                if (v4 < 0x4B)
                {
                    if (v4 <= 0x32)
                    {
                        if (v4 <= 0x19)
                        {
                            if (v4)
                            {
                                return 26;
                            }
                            else
                            {
                                return 25;
                            }
                        }
                        else
                        {
                            return 27;
                        }
                    }
                    else
                    {
                        return 28;
                    }
                }
                else
                {
                    return 29;
                }
            }
        }
        else
        {
            *a3 = 1;
            if (TrainerParam_HasTrainerInfo(a1->mainModule, a2))
            {
                return 30;
            }
            else if (a1->mainModule->trainerParam[a2].ID == 491)
            {
                return 226;
            }
            else if (a1->mainModule->trainerParam[a2].ID == 507)
            {
                return 226;
            }
            else if (a1->mainModule->trainerParam[a2].ID == 508)
            {
                return 226;
            }
            else if (a1->mainModule->trainerParam[a2].ID == 509)
            {
                return 226;
            }
            else
            {
                return 31;
            }
        }
    }

    int THUMB_BRANCH_BattleHandler_Faint(ServerFlow *a1, HandlerParam_Faint *a2)
    {
        BattleMon *BattleMon; // r6
        HandlerParam_StrParams *check;

        int trainerId;

        if (!j_j_PosPoke_IsExist_7(&a1->posPoke, a2->pokeID))
        {
            return 0;
        }
        BattleMon = PokeCon_GetBattleMon(a1->pokeCon, a2->pokeID);
        if (BattleMon_IsFainted(BattleMon) && !a2->flags)
        {
            return 0;
        }

        check = &a2->exStr;
        trainerId = a1->mainModule->trainerParam[1].ID;

        if (trainerId == 491 && BattleMon->ID >= 6)
        {
            if (BattleMon->Species == PK638_COBALION || BattleMon->Species == PK112_RHYDON)
            {
                check->ID = 1167;
            }
            else
            {
                check->ID = 1170;
            }
        }
        else if (trainerId == 507 && BattleMon->ID >= 6)
        {
            if (BattleMon->Species == PK640_VIRIZION)
            {
                check->ID = 1173;
            }
            else
            {
                check->ID = 230;
            }
        }
        else if (trainerId == 508 && BattleMon->ID >= 6)
        {
            if (BattleMon->Species == PK639_TERRAKION)
            {
                check->ID = 1179;
            }
            else
            {
                check->ID = 232;
            }
        }
        else if (trainerId == 509 && BattleMon->ID >= 6)
        {
            if (BattleMon->Species == PK647_KELDEO)
            {
                check->ID = 1185;
            }
            else
            {
                check->ID = 234;
            }
        }
        else
        {
        }

        BattleHandler_SetString(a1, check);
        ServerControl_FaintPokemon(a1, BattleMon);
        return 1;
    }
}