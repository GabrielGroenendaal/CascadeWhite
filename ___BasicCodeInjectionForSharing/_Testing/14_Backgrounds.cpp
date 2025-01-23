#include "../swan-master/swantypes.h"
#include "../kPrint.h"

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

int ZoneIDsNowWithLighting[] = {
    16
};

bool IsInArray(int value){
    for (int i = 0; i < 1; i++){
        if (ZoneIDsNowWithLighting[i] == value){
            return true;
        }
    };
    return false;
}

extern "C"
{
    enum HeapID : unsigned __int16 {HEAPID_SYSTEM = 0x0,HEAPID_USER = 0x1,HEAPID_GAMESYSTEM = 0x3,HEAPID_GAMEEVENT = 0x4,HEAPID_TRIAL_HOUSE = 0x5,HEAPID_SAVEDATA = 0x7,HEAPID_NET = 0x8,HEAPID_DEVICE_ALLOC = 0x9,HEAPID_STARTMENU = 0xB,HEAPID_DLP = 0xC,HEAPID_FIELDMAP = 0x15,HEAPID_TITLE = 0x16,HEAPID_POKELIST = 0x17,HEAPID_NAMEIN = 0x1E,HEAPID_IRC_BATTLE_MENU = 0x1F,HEAPID_TRAINER_CARD = 0x26,HEAPID_MUSICAL_EVENT = 0x2C,HEAPID_MUSICAL_DRESSUP = 0x2D,HEAPID_MUSICAL = 0x2E,HEAPID_DEBUG_GENDER_SELECT = 0x39,HEAPID_MICTEST = 0x49,HEAPID_FIELD_PARTICLE = 0x50,HEAPID_BATTLE_RETURN = 0x52,HEAPID_GAMESYNC = 0x67,HEAPID_DEMO3D = 0x6C,HEAPID_INTRO = 0x6F,HEAPID_FIELD_MENU = 0x70,HEAPID_BATTLE_LOAD = 0x76,HEAPID_CDEMO = 0x7F,HEAPID_SAVEDATA_DELETE = 0x81,HEAPID_FIELD_CLACT = 0x89,HEAPID_FIELD_WEATHER = 0x92,HEAPID_FIELD_PLACE_NAME = 0x93,HEAPID_FIELD_SCENEAREA = 0x96,HEAPID_HEAD_MASK = 0x7FFF,HEAPID_TAIL_BIT = 0x8000,};
    struct AreaData {u16 Buildings;u16 Textures;u8 SrtAnime;u8 PatAnime;u8 IsExterior;u8 Lights;u8 EdgeColorTableId;u8 BbdMdlColors;};
    typedef u16 GXColor;
    struct 	VecFx16	 {__int16 x;__int16 y;__int16 z;};
    struct 	FieldLightInfo	 {u16 DayPart;s16 MinutesOffs;u8 LightIsEnabled[4];GXColor LightColors[4];VecFx16 LightPositions[4];GXColor GXDiffuse;GXColor GXAmbient;GXColor GXSpecular;GXColor GXEmission;GXColor GXFogColor;GXColor ClearColor;};
    struct 	FieldLightData	 {FieldLightInfo Entries[16];};
    extern int sub_201991C(int a1);
    extern FieldLightData* Normalize060File(int arcId, u16 datId, u32 *pEntryCount, HeapID heapId);
    extern int GetZoneStaticLightDataIndex(u16 zoneId);
    extern b32 AreaData_HasSeasons(u16 areaID);
    extern u32 ZoneData_GetAreaID(int zoneId);
    extern AreaData* AreaData_Create(HeapID heapId, u16 areaId, u16 areaSeasonShift);
    extern int  AreaData_GetLightsID(AreaData *ad);
    extern void AreaData_Free(AreaData *ad);
    extern void sub_201998C(
        FieldLightData *lights,
        u32 lightEntryCount,
        int seconds,
        int areaIdSeasonShift,
        u16 *dest);
    extern void GFL_HeapFree(void *heap);

    void THUMB_BRANCH_sub_2019830(u16 zoneId, int hours, int minutes, int a4, int areaIdSeasonShift, u16 *a6, HeapID heapId)
    {
        int v8;                       // r7
        FieldLightData *v9;           // r4
        u16 v10;                      // r0
        int ZoneStaticLightDataIndex; // r0
        int zoneIdToUse;
        u16 v12;                      // r6
        u16 AreaID;                   // r0
        HeapID v14;                   // r4
        u16 v15;                      // r0
        AreaData *v16;                // r5
        u16 LightsID;                 // r0
        int v18;                      // [sp+4h] [bp-1Ch]
        u32 pEntryCount[6];           // [sp+8h] [bp-18h] BYREF

      
        zoneIdToUse = (IsInArray(zoneId)) ? 445 : zoneId;
        v8 = 60 * minutes;
        v9 = 0;
        v18 = 3600 * hours;
        if (a4)
        {
            v10 = sub_201991C(a4);
            v9 = Normalize060File(61, v10, pEntryCount, (HeapID)(heapId & 0x7FFF | 0x8000));
        }
        if (!v9)
        {
            ZoneStaticLightDataIndex = GetZoneStaticLightDataIndex(zoneId);
            if (ZoneStaticLightDataIndex != 0xFFFFFFF)
            {
                v9 = Normalize060File(81, ZoneStaticLightDataIndex, pEntryCount, (HeapID)(heapId & 0x7FFF | 0x8000));
            }
        }
        if (!v9)
        {
            v12 = 0;
            AreaID = ZoneData_GetAreaID(zoneId);
            if (AreaData_HasSeasons(AreaID))
            {
                v12 = areaIdSeasonShift;
            }
            v14 = (HeapID)(heapId & 0x7FFF | 0x8000);
            v15 = ZoneData_GetAreaID(zoneId);
            v16 = AreaData_Create(v14, v15, v12);
            LightsID = AreaData_GetLightsID(v16);
            v9 = Normalize060File(60, LightsID, pEntryCount, v14);
            AreaData_Free(v16);
        }
        sub_201998C(v9, pEntryCount[0], v8 + v18, areaIdSeasonShift, a6);
        GFL_HeapFree(v9);
    }
}