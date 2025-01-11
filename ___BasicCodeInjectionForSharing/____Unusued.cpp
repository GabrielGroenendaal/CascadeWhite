


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
    //         return 1195;
    //     }
    //     if (a1 == 2)
    //     {
    //         return 1198;
    //     }
    //     if (a1 == 3)
    //     {
    //         return 1201;
    //     }
    //     if (a1 == 4)
    //     {
    //         return 1204;
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
    //         result = Handler_GetThisTurnAction(a2, a3, (unsigned int *)v8);
    //         k::Printf("\nLayer Two: We are inside the function did we get this far?\n");
    //         if (result)
    //         {
    //             Value = BattleEventVar_GetValue(VAR_TARGET_MON_ID);
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

    // int HandlerAmbushChargeCheck(int a1, ServerFlow *a2, int a3)
    // {
    //     int result; // r0
    //     BattleMon *PokeParam;
    //     result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
    //     PokeParam = Handler_GetPokeParam(a2, a3);
    //     if (a3 == result)
    //     {
    //         if (checkState(PokeParam))
    //         {
    //             return BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
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

    // MOVE_TRIGGERTABLE DigHandlers[] = {
    //     {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //     {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerDig},
    //     {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)EndOfCharge},
    //     {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerAmbushChargeCheck}};

    // MOVE_TRIGGERTABLE ShadowForceHandlers[] = {
    //     {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //     {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerShadowForce},
    //     {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)EndOfCharge},
    //     {EVENT_CHECK_PROTECT_BREAK, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
    //     {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
    //     {EVENT_DAMAGE_PROCESSING_END_HIT_1, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd},
    //     {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerAmbushChargeCheck}};

    // MOVE_TRIGGERTABLE FlyHandlers[] = {
    //     {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //     {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerFly},
    //     {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)EndOfCharge},
    //     {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerAmbushChargeCheck}

    // };

    // MOVE_TRIGGERTABLE BounceHandlers[] = {
    //     {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //     {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerBounce},
    //     {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)EndOfCharge},
    //     {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerAmbushChargeCheck}

    // };

    // MOVE_TRIGGERTABLE DiveHandlers[] = {
    //     {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //     {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerDive},
    //     {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)EndOfCharge},
    //     {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerAmbushChargeCheck}};

    // MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddDig(_DWORD *a1)
    // {
    //     *a1 = 4;
    //     return DigHandlers;
    // }

    // MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddShadowForce(_DWORD *a1)
    // {
    //     *a1 = 7;
    //     return ShadowForceHandlers;
    // }

    // MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddFly(_DWORD *a1)
    // {
    //     *a1 = 4;
    //     return FlyHandlers;
    // }

    // MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddBounce(_DWORD *a1)
    // {
    //     *a1 = 4;
    //     return BounceHandlers;
    // }

    // MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddDive(_DWORD *a1)
    // {
    //     *a1 = 4;
    //     return DiveHandlers;
    // }

    // int THUMB_BRANCH_ServerEvent_InterruptSwitch(ServerFlow *a1, BattleMon *a2)
    // {
    //     unsigned int v3;                  // r4
    //     unsigned int v4;                  // r7
    //     BattleMon *BattleMon;             // r0
    //     int v6;                           // r6
    //     int Value;                        // r0
    //     unsigned int v8;                  // r4
    //     int ID;                           // r0
    //     ServerFlow *v10;                  // r6
    //     int v11;                          // r1
    //     ServerFlow *v14;                  // [sp+4h] [bp-44h]
    //     ActionOrderWork *ActionOrderWork; // [sp+8h] [bp-40h]
    //     char *p_actionOrderIndex;         // [sp+20h] [bp-28h]

    //     v3 = 0;
    //     if (a1->numActOrder)
    //     {
    //         ActionOrderWork = a1->actionOrderWork;
    //         p_actionOrderIndex = &a1->numActOrder;
    //         do
    //         {
    //             v4 = v3;
    //             v14 = a1 + 16 * v3;
    //             BattleMon = v14->actionOrderWork[0].battleMon;
    //             if (BattleMon != a2 && !v14->actionOrderWork[0].fDone)
    //             {
    //                 v6 = (BattleAction_GetAction(ActionOrderWork[v4].Action)) == ACTION_ATTACK ? ((BattleAction_Fight *)ActionOrderWork[v4].Action)->moveID : 0;
    //                 if (v6 == MOVE228_PURSUIT || MOVE467_SHADOW_FORCE || MOVE019_FLY || MOVE340_BOUNCE || MOVE091_DIG || MOVE291_DIVE)
    //                 {
    //                     Value = BattleMon_GetValue(BattleMon, VALUE_SPEED_STAT);
    //                     if (MoveEvent_AddItem(a1->actionOrderWork[v4].battleMon, v6, Value))
    //                     {
    //                         v14->actionOrderWork[0].field_E = 1;
    //                     }
    //                 }
    //             }
    //             ++v3;
    //         } while (v3 < *p_actionOrderIndex);
    //     }
    //     v8 = 0;
    //     a1->field_788 = 0;
    //     BattleEventVar_Push();
    //     ID = BattleMon_GetID(a2);
    //     BattleEventVar_SetConstValue(VAR_TARGET_MON_ID, ID);
    //     BattleEvent_CallHandlers(a1, EVENT_SWITCH_OUT_INTERRUPT);
    //     BattleEventVar_Pop();
    //     if (a1->numActOrder)
    //     {
    //         do
    //         {
    //             v10 = (a1 + 16 * v8);
    //             if (v10->actionOrderWork[0].field_E)
    //             {
    //                 if (BattleAction_GetAction(ActionOrderWork[v4].Action) == ACTION_ATTACK)
    //                 {
    //                     v11 = ((BattleAction_Fight *)ActionOrderWork[v4].Action)->moveID;
    //                 }
    //                 else
    //                 {
    //                     v11 = 0;
    //                 }
    //                 if (v11 == MOVE228_PURSUIT || MOVE467_SHADOW_FORCE || MOVE019_FLY || MOVE340_BOUNCE || MOVE091_DIG || MOVE291_DIVE)
    //                 {
    //                     MoveEvent_ForceRemoveItemFromBattleMon(v10->actionOrderWork[0].battleMon, v11);
    //                 }
    //                 v10->actionOrderWork[0].field_E = 0;
    //             }
    //             ++v8;
    //         } while (v8 < a1->numActOrder);
    //     }
    //     return a1->field_788;
    // }

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