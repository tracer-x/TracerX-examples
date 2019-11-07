/* Generated by CIL v. 1.3.7 */
/* print_CIL_Input is true */
#include <stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int safety;
int KernelMode;
int Executive;
int DevicePowerState;
int s;
int UNLOADED;
int NP;
int DC;
int SKIP1;
int SKIP2;
int MPR1;
int MPR3;
int IPC;
int pended;
int compFptr;
int compRegistered;
int lowerDriverReturn;
int setEventCalled;
int customIrp;
int myStatus;
int wcet;

void stub_driver_init(void) {

  {
    s = NP;
    klee_make_symbolic(&pended, sizeof(int), "pended");
    klee_make_symbolic(&compFptr, sizeof(int), "compFptr");
    klee_make_symbolic(&compRegistered, sizeof(int), "compRegistered");
    klee_make_symbolic(&lowerDriverReturn, sizeof(int), "lowerDriverReturn");
    klee_make_symbolic(&setEventCalled, sizeof(int), "setEventCalled");
    klee_make_symbolic(&customIrp, sizeof(int), "customIrp");
  }
}
void _BLAST_init(void) {

  {
    klee_make_symbolic(&UNLOADED, sizeof(int), "UNLOADED");
    klee_make_symbolic(&NP, sizeof(int), "NP");
    klee_make_symbolic(&DC, sizeof(int), "DC");
    klee_make_symbolic(&SKIP1, sizeof(int), "SKIP1");
    klee_make_symbolic(&SKIP2, sizeof(int), "SKIP2");
    klee_make_symbolic(&MPR1, sizeof(int), "MPR1");
    klee_make_symbolic(&MPR3, sizeof(int), "MPR3");
    klee_make_symbolic(&IPC, sizeof(int), "IPC");
    s = UNLOADED;
    klee_make_symbolic(&pended, sizeof(int), "pended");
    klee_make_symbolic(&compRegistered, sizeof(int), "compRegistered");
    klee_make_symbolic(&lowerDriverReturn, sizeof(int), "lowerDriverReturn");
    klee_make_symbolic(&setEventCalled, sizeof(int), "setEventCalled");
    klee_make_symbolic(&customIrp, sizeof(int), "customIrp");
  }
}
void IofCompleteRequest(int IofCompleteRequest_Irp,
                        int IofCompleteRequest_PriorityBoost);
int IofCallDriver(int IofCallDriver_DeviceObject, int IofCallDriver_Irp);
int KeWaitForSingleObject(int KeWaitForSingleObject_Object,
                          int KeWaitForSingleObject_WaitReason,
                          int KeWaitForSingleObject_WaitMode,
                          int KeWaitForSingleObject_Alertable,
                          int KeWaitForSingleObject_Timeout);
int KbFilter_PnP(int KbFilter_PnP_DeviceObject, int KbFilter_PnP_Irp) {
  int KbFilter_PnP_devExt;
  int KbFilter_PnP_irpStack;
  int KbFilter_PnP_status;
  int KbFilter_PnP_event;
  int KbFilter_PnP_DeviceObject__DeviceExtension;
  int KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation;
  int KbFilter_PnP_irpStack__MinorFunction;
  int KbFilter_PnP_devExt__TopOfStack;
  int KbFilter_PnP_devExt__Started;
  int KbFilter_PnP_devExt__Removed;
  int KbFilter_PnP_devExt__SurpriseRemoved;
  int KbFilter_PnP_Irp__IoStatus__Status;
  int KbFilter_PnP_Irp__IoStatus__Information;
  int KbFilter_PnP_Irp__CurrentLocation;
  int KbFilter_PnP_irpSp;
  int KbFilter_PnP_nextIrpSp;
  int KbFilter_PnP_nextIrpSp__Control;
  int KbFilter_PnP_irpSp___0;
  int KbFilter_PnP_irpSp__Context;
  int KbFilter_PnP_irpSp__Control;
  long KbFilter_PnP_CIL___Tmp23;

  {
    KbFilter_PnP_status = 0;
    KbFilter_PnP_devExt = KbFilter_PnP_DeviceObject__DeviceExtension;
    KbFilter_PnP_irpStack =
        KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation;
    if (KbFilter_PnP_irpStack__MinorFunction >= 0) {
      if (KbFilter_PnP_irpStack__MinorFunction <= 0) {
        KbFilter_PnP_irpSp =
            KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation;
        KbFilter_PnP_nextIrpSp =
            KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation - 1;
        KbFilter_PnP_nextIrpSp__Control = 0;
        safety = safety + (s - NP);
        safety = safety + (compRegistered - 0);
        compRegistered = 1;
        KbFilter_PnP_irpSp___0 =
            KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation - 1;
        KbFilter_PnP_irpSp__Context = KbFilter_PnP_event;
        KbFilter_PnP_irpSp__Control = 224;
        KbFilter_PnP_status =
            IofCallDriver(KbFilter_PnP_devExt__TopOfStack, KbFilter_PnP_Irp);
        KbFilter_PnP_CIL___Tmp23 = (long)KbFilter_PnP_status;
        if (KbFilter_PnP_CIL___Tmp23 >= 259L) {
          if (KbFilter_PnP_CIL___Tmp23 <= 259L) {
            KeWaitForSingleObject(KbFilter_PnP_event, Executive, KernelMode, 0,
                                  0);
          }
        }
        if (KbFilter_PnP_status >= 0) {
          if (myStatus >= 0) {
            KbFilter_PnP_devExt__Started = 1;
            KbFilter_PnP_devExt__Removed = 0;
            KbFilter_PnP_devExt__SurpriseRemoved = 0;
          }
        }
        KbFilter_PnP_Irp__IoStatus__Status = KbFilter_PnP_status;
        myStatus = KbFilter_PnP_status;
        KbFilter_PnP_Irp__IoStatus__Information = 0;
        IofCompleteRequest(KbFilter_PnP_Irp, 0);
      } else {
        goto _L___0;
      }
    } else {
    _L___0: /* CIL Label */
      if (KbFilter_PnP_irpStack__MinorFunction >= 23) {
        if (KbFilter_PnP_irpStack__MinorFunction <= 23) {
          KbFilter_PnP_devExt__SurpriseRemoved = 1;
          safety = safety + (s - NP);
          s = SKIP1;
          KbFilter_PnP_Irp__CurrentLocation =
              KbFilter_PnP_Irp__CurrentLocation + 1;
          KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation =
              KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation + 1;
          KbFilter_PnP_status =
              IofCallDriver(KbFilter_PnP_devExt__TopOfStack, KbFilter_PnP_Irp);
        } else {
          goto _L;
        }
      } else {
      _L: /* CIL Label */
        if (KbFilter_PnP_irpStack__MinorFunction >= 2) {
          if (KbFilter_PnP_irpStack__MinorFunction <= 2) {
            KbFilter_PnP_devExt__Removed = 1;
            safety = safety + (s - NP);
            s = SKIP1;
            KbFilter_PnP_Irp__CurrentLocation =
                KbFilter_PnP_Irp__CurrentLocation + 1;
            KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation =
                KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation + 1;
            IofCallDriver(KbFilter_PnP_devExt__TopOfStack, KbFilter_PnP_Irp);
            KbFilter_PnP_status = 0;
          } else {
            safety = safety + (s - NP);
            s = SKIP1;
            KbFilter_PnP_Irp__CurrentLocation =
                KbFilter_PnP_Irp__CurrentLocation + 1;
            KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation =
                KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation + 1;
            KbFilter_PnP_status = IofCallDriver(KbFilter_PnP_devExt__TopOfStack,
                                                KbFilter_PnP_Irp);
          }
        } else {
          safety = safety + (s - NP);
          s = SKIP1;
          KbFilter_PnP_Irp__CurrentLocation =
              KbFilter_PnP_Irp__CurrentLocation + 1;
          KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation =
              KbFilter_PnP_Irp__Tail__Overlay__CurrentStackLocation + 1;
          KbFilter_PnP_status =
              IofCallDriver(KbFilter_PnP_devExt__TopOfStack, KbFilter_PnP_Irp);
        }
      }
    }
    return (KbFilter_PnP_status);
  }
}
int KbFilter_CreateClose(int KbFilter_CreateClose_DeviceObject,
                         int KbFilter_CreateClose_Irp);
int KbFilter_Power(int KbFilter_Power_DeviceObject, int KbFilter_Power_Irp);
int KbFilter_InternIoCtl(int KbFilter_InternIoCtl_DeviceObject,
                         int KbFilter_InternIoCtl_Irp);
int main() {
  wcet = 0;
  int main_status;
  int main_irp;
  int main_pirp;
  int main_irp_choice;
  int main_devobj;
  int main_tmp_ndt_1;
  int main_tmp_ndt_2;
  int main_tmp_ndt_3;
  int main_tmp_ndt_4;
  int main_tmp_ndt_5;

  {
    safety = 0;
    main_pirp = main_irp;
    _BLAST_init();
    myStatus = 0;
    if (main_irp_choice >= 0) {
      if (main_irp_choice <= 0) {
        myStatus = -1073741637;
      }
    }
    stub_driver_init();
    klee_make_symbolic(&main_tmp_ndt_1, sizeof(int), "main_tmp_ndt_1");
    if (main_tmp_ndt_1 >= 0) {
      if (main_tmp_ndt_1 <= 0) {
        main_status = KbFilter_CreateClose(main_devobj, main_pirp);
      } else {
        goto _L___2;
      }
    } else {
    _L___2: /* CIL Label */
      klee_make_symbolic(&main_tmp_ndt_2, sizeof(int), "main_tmp_ndt_2");
      if (main_tmp_ndt_2 >= 1) {
        if (main_tmp_ndt_2 <= 1) {
          main_status = KbFilter_CreateClose(main_devobj, main_pirp);
        } else {
          goto _L___1;
        }
      } else {
      _L___1: /* CIL Label */
        klee_make_symbolic(&main_tmp_ndt_3, sizeof(int), "main_tmp_ndt_3");
        if (main_tmp_ndt_3 >= 3) {
          if (main_tmp_ndt_3 <= 3) {
            main_status = KbFilter_PnP(main_devobj, main_pirp);
          } else {
            goto _L___0;
          }
        } else {
        _L___0: /* CIL Label */
          klee_make_symbolic(&main_tmp_ndt_4, sizeof(int), "main_tmp_ndt_4");
          if (main_tmp_ndt_4 >= 4) {
            if (main_tmp_ndt_4 <= 4) {
              main_status = KbFilter_Power(main_devobj, main_pirp);
            } else {
              goto _L;
            }
          } else {
          _L: /* CIL Label */
            klee_make_symbolic(&main_tmp_ndt_5, sizeof(int), "main_tmp_ndt_5");
            if (main_tmp_ndt_5 >= 8) {
              if (main_tmp_ndt_5 <= 8) {
                main_status = KbFilter_InternIoCtl(main_devobj, main_pirp);
              }
            }
          }
        }
      }
    }
    tracerx_check();
    return 0;
  }
}
void stubMoreProcessingRequired(void) {

  {
    safety = safety + (s - NP);
    s = MPR1;
  }
}
int KbFilter_Complete(int KbFilter_Complete_DeviceObject,
                      int KbFilter_Complete_Irp, int KbFilter_Complete_Context);
int IofCallDriver(int IofCallDriver_DeviceObject, int IofCallDriver_Irp) {
  int IofCallDriver_returnVal2;
  int IofCallDriver_compRetStatus;
  int IofCallDriver_lcontext;
  long long IofCallDriver_CIL___Tmp7;
  int IofCallDriver_tmp_ndt_6;
  int IofCallDriver_tmp_ndt_7;

  {
    if (compRegistered > 0) {
      goto _L;
    } else {
      if (compRegistered < 0) {
      _L: /* CIL Label */
        IofCallDriver_compRetStatus =
            KbFilter_Complete(IofCallDriver_DeviceObject, IofCallDriver_Irp,
                              IofCallDriver_lcontext);
        IofCallDriver_CIL___Tmp7 = (long long)IofCallDriver_compRetStatus;
        if (IofCallDriver_CIL___Tmp7 >= -1073741802LL) {
          if (IofCallDriver_CIL___Tmp7 <= -1073741802LL) {
            stubMoreProcessingRequired();
          }
        }
      }
    }
    klee_make_symbolic(&IofCallDriver_tmp_ndt_6, sizeof(int),
                       "IofCallDriver_tmp_ndt_6");
    if (IofCallDriver_tmp_ndt_6 >= 0) {
      if (IofCallDriver_tmp_ndt_6 <= 0) {
        IofCallDriver_returnVal2 = 0;
      } else {
        goto _L___0;
      }
    } else {
    _L___0: /* CIL Label */
      klee_make_symbolic(&IofCallDriver_tmp_ndt_7, sizeof(int),
                         "IofCallDriver_tmp_ndt_7");
      if (IofCallDriver_tmp_ndt_7 >= 1) {
        if (IofCallDriver_tmp_ndt_7 <= 1) {
          IofCallDriver_returnVal2 = -1073741823;
        } else {
          IofCallDriver_returnVal2 = 259;
        }
      } else {
        IofCallDriver_returnVal2 = 259;
      }
    }
    if (s >= NP) {
      if (s <= NP) {
        s = IPC;
        lowerDriverReturn = IofCallDriver_returnVal2;
      } else {
        goto _L___1;
      }
    } else {
    _L___1: /* CIL Label */
      if (s >= MPR1) {
        if (s <= MPR1) {
          if (IofCallDriver_returnVal2 >= 259) {
            if (IofCallDriver_returnVal2 <= 259) {
              s = MPR3;
              lowerDriverReturn = IofCallDriver_returnVal2;
            } else {
              s = NP;
              lowerDriverReturn = IofCallDriver_returnVal2;
            }
          } else {
            s = NP;
            lowerDriverReturn = IofCallDriver_returnVal2;
          }
        } else {
          safety = safety + (s - SKIP1);
          s = SKIP2;
          lowerDriverReturn = IofCallDriver_returnVal2;
        }
      } else {
        safety = safety + (s - SKIP1);
        s = SKIP2;
        lowerDriverReturn = IofCallDriver_returnVal2;
      }
    }
    return (IofCallDriver_returnVal2);
  }
}
void IofCompleteRequest(int IofCompleteRequest_Irp,
                        int IofCompleteRequest_PriorityBoost) {

  {
    safety = safety + (s - NP);
    s = DC;
  }
}
int KeSetEvent(int KeSetEvent_Event, int KeSetEvent_Increment,
               int KeSetEvent_Wait) {
  int KeSetEvent_l;

  {
    setEventCalled = 1;
    return (KeSetEvent_l);
  }
}
int KeWaitForSingleObject(int KeWaitForSingleObject_Object,
                          int KeWaitForSingleObject_WaitReason,
                          int KeWaitForSingleObject_WaitMode,
                          int KeWaitForSingleObject_Alertable,
                          int KeWaitForSingleObject_Timeout) {
  int KeWaitForSingleObject_tmp_ndt_8;
  int retres7;

  {
    if (s >= MPR3) {
      if (s <= MPR3) {
        if (setEventCalled >= 1) {
          if (setEventCalled <= 1) {
            s = NP;
            setEventCalled = 0;
          } else {
            goto _L;
          }
        } else {
        _L: /* CIL Label */
          if (customIrp >= 1) {
            if (customIrp <= 1) {
              s = NP;
              customIrp = 0;
            }
          }
        }
      } else {
        goto _L___0;
      }
    } else {
    _L___0: /* CIL Label */
      if (customIrp >= 1) {
        if (customIrp <= 1) {
          s = NP;
          customIrp = 0;
        }
      }
    }
    klee_make_symbolic(&KeWaitForSingleObject_tmp_ndt_8, sizeof(int),
                       "KeWaitForSingleObject_tmp_ndt_8");
    if (KeWaitForSingleObject_tmp_ndt_8 >= 0) {
      if (KeWaitForSingleObject_tmp_ndt_8 <= 0) {
        retres7 = 0;
      } else {
        retres7 = -1073741823;
      }
    } else {
      retres7 = -1073741823;
    }
    return (retres7);
  }
}
int KbFilter_Complete(int KbFilter_Complete_DeviceObject,
                      int KbFilter_Complete_Irp,
                      int KbFilter_Complete_Context) {
  int KbFilter_Complete_event;
  int retres5;

  {
    KbFilter_Complete_event = KbFilter_Complete_Context;
    KeSetEvent(KbFilter_Complete_event, 0, 0);
    retres5 = -1073741802;
    return (retres5);
  }
}
int KbFilter_DispatchPassThrough(int KbFilter_DispatchPassThrough_DeviceObject,
                                 int KbFilter_DispatchPassThrough_Irp);
int KbFilter_CreateClose(int KbFilter_CreateClose_DeviceObject,
                         int KbFilter_CreateClose_Irp) {
  int KbFilter_CreateClose_irpStack__MajorFunction;
  int KbFilter_CreateClose_devExt__UpperConnectData__ClassService;
  int KbFilter_CreateClose_Irp__IoStatus__Status;
  int KbFilter_CreateClose_status;
  int KbFilter_CreateClose_tmp;

  {
    KbFilter_CreateClose_status = myStatus;
    if (KbFilter_CreateClose_irpStack__MajorFunction >= 0) {
      if (KbFilter_CreateClose_irpStack__MajorFunction <= 0) {
        if (KbFilter_CreateClose_devExt__UpperConnectData__ClassService >= 0) {
          if (KbFilter_CreateClose_devExt__UpperConnectData__ClassService <=
              0) {
            KbFilter_CreateClose_status = -1073741436;
          }
        }
      }
    }
    KbFilter_CreateClose_Irp__IoStatus__Status = KbFilter_CreateClose_status;
    myStatus = KbFilter_CreateClose_status;
    KbFilter_CreateClose_tmp = KbFilter_DispatchPassThrough(
        KbFilter_CreateClose_DeviceObject, KbFilter_CreateClose_Irp);
    return (KbFilter_CreateClose_tmp);
  }
}
int KbFilter_DispatchPassThrough(int KbFilter_DispatchPassThrough_DeviceObject,
                                 int KbFilter_DispatchPassThrough_Irp) {
  int KbFilter_DispatchPassThrough_Irp__Tail__Overlay__CurrentStackLocation;
  int KbFilter_DispatchPassThrough_Irp__CurrentLocation;
  int KbFilter_DispatchPassThrough_DeviceObject__DeviceExtension__TopOfStack;
  int KbFilter_DispatchPassThrough_irpStack;
  int KbFilter_DispatchPassThrough_tmp;

  {
    KbFilter_DispatchPassThrough_irpStack =
        KbFilter_DispatchPassThrough_Irp__Tail__Overlay__CurrentStackLocation;
    safety = safety + (s - NP);
    s = SKIP1;
    KbFilter_DispatchPassThrough_Irp__CurrentLocation =
        KbFilter_DispatchPassThrough_Irp__CurrentLocation + 1;
    KbFilter_DispatchPassThrough_Irp__Tail__Overlay__CurrentStackLocation =
        KbFilter_DispatchPassThrough_Irp__Tail__Overlay__CurrentStackLocation +
        1;
    KbFilter_DispatchPassThrough_tmp = IofCallDriver(
        KbFilter_DispatchPassThrough_DeviceObject__DeviceExtension__TopOfStack,
        KbFilter_DispatchPassThrough_Irp);
    return (KbFilter_DispatchPassThrough_tmp);
  }
}
int PoCallDriver(int PoCallDriver_DeviceObject, int PoCallDriver_Irp);
int KbFilter_Power(int KbFilter_Power_DeviceObject, int KbFilter_Power_Irp) {
  int KbFilter_Power_irpStack__MinorFunction;
  int KbFilter_Power_devExt__DeviceState;
  int KbFilter_Power_powerState__DeviceState;
  int KbFilter_Power_Irp__CurrentLocation;
  int KbFilter_Power_Irp__Tail__Overlay__CurrentStackLocation;
  int KbFilter_Power_devExt__TopOfStack;
  int KbFilter_Power_powerType;
  int KbFilter_Power_tmp;

  {
    if (KbFilter_Power_irpStack__MinorFunction >= 2) {
      if (KbFilter_Power_irpStack__MinorFunction <= 2) {
        if (KbFilter_Power_powerType >= DevicePowerState) {
          if (KbFilter_Power_powerType <= DevicePowerState) {
            KbFilter_Power_devExt__DeviceState =
                KbFilter_Power_powerState__DeviceState;
          }
        }
      }
    }
    safety = safety + (s - NP);
    s = SKIP1;
    KbFilter_Power_Irp__CurrentLocation =
        KbFilter_Power_Irp__CurrentLocation + 1;
    KbFilter_Power_Irp__Tail__Overlay__CurrentStackLocation =
        KbFilter_Power_Irp__Tail__Overlay__CurrentStackLocation + 1;
    KbFilter_Power_tmp =
        PoCallDriver(KbFilter_Power_devExt__TopOfStack, KbFilter_Power_Irp);
    return (KbFilter_Power_tmp);
  }
}
int PoCallDriver(int PoCallDriver_DeviceObject, int PoCallDriver_Irp) {
  int PoCallDriver_compRetStatus;
  int PoCallDriver_returnVal;
  int PoCallDriver_lcontext;
  long PoCallDriver_CIL___Tmp7;
  long PoCallDriver_CIL___Tmp8;
  int PoCallDriver_tmp_ndt_9;
  int PoCallDriver_tmp_ndt_10;

  {
    if (compRegistered > 0) {
      goto _L;
    } else {
      if (compRegistered < 0) {
      _L: /* CIL Label */
        PoCallDriver_compRetStatus = KbFilter_Complete(
            PoCallDriver_DeviceObject, PoCallDriver_Irp, PoCallDriver_lcontext);
        PoCallDriver_CIL___Tmp7 = (long)PoCallDriver_compRetStatus;
        if (PoCallDriver_CIL___Tmp7 >= -1073741802L) {
          if (PoCallDriver_CIL___Tmp7 <= -1073741802L) {
            stubMoreProcessingRequired();
          }
        }
      }
    }
    klee_make_symbolic(&PoCallDriver_tmp_ndt_9, sizeof(int),
                       "PoCallDriver_tmp_ndt_9");
    if (PoCallDriver_tmp_ndt_9 >= 0) {
      if (PoCallDriver_tmp_ndt_9 <= 0) {
        PoCallDriver_returnVal = 0;
      } else {
        goto _L___0;
      }
    } else {
    _L___0: /* CIL Label */
      klee_make_symbolic(&PoCallDriver_tmp_ndt_10, sizeof(int),
                         "PoCallDriver_tmp_ndt_10");
      if (PoCallDriver_tmp_ndt_10 >= 1) {
        if (PoCallDriver_tmp_ndt_10 <= 1) {
          PoCallDriver_returnVal = -1073741823;
        } else {
          PoCallDriver_returnVal = 259;
        }
      } else {
        PoCallDriver_returnVal = 259;
      }
    }
    if (s >= NP) {
      if (s <= NP) {
        s = IPC;
        lowerDriverReturn = PoCallDriver_returnVal;
      } else {
        goto _L___1;
      }
    } else {
    _L___1: /* CIL Label */
      if (s >= MPR1) {
        if (s <= MPR1) {
          PoCallDriver_CIL___Tmp8 = (long)PoCallDriver_returnVal;
          if (PoCallDriver_CIL___Tmp8 >= 259L) {
            if (PoCallDriver_CIL___Tmp8 <= 259L) {
              s = MPR3;
              lowerDriverReturn = PoCallDriver_returnVal;
            } else {
              s = NP;
              lowerDriverReturn = PoCallDriver_returnVal;
            }
          } else {
            s = NP;
            lowerDriverReturn = PoCallDriver_returnVal;
          }
        } else {
          safety = safety + (s - SKIP1);
          s = SKIP2;
          lowerDriverReturn = PoCallDriver_returnVal;
        }
      } else {
        safety = safety + (s - SKIP1);
        s = SKIP2;
        lowerDriverReturn = PoCallDriver_returnVal;
      }
    }
    return (PoCallDriver_returnVal);
  }
}
int KbFilter_InternIoCtl(int KbFilter_InternIoCtl_DeviceObject,
                         int KbFilter_InternIoCtl_Irp) {
  int KbFilter_InternIoCtl_Irp__IoStatus__Information;
  int KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__IoControlCode;
  int KbFilter_InternIoCtl_devExt__UpperConnectData__ClassService;
  int KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__InputBufferLength;
  int KbFilter_InternIoCtl_sizeof__CONNECT_DATA;
  int KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__Type3InputBuffer;
  int KbFilter_InternIoCtl_sizeof__INTERNAL_I8042_HOOK_KEYBOARD;
  int KbFilter_InternIoCtl_Irp__IoStatus__Status;
  int KbFilter_InternIoCtl_hookKeyboard;
  int KbFilter_InternIoCtl_connectData;
  int KbFilter_InternIoCtl_status;
  int KbFilter_InternIoCtl_tmp;
  int KbFilter_InternIoCtl_CIL___Tmp20;
  int KbFilter_InternIoCtl_CIL___Tmp24;
  int KbFilter_InternIoCtl_CIL___Tmp28;
  int retres26;
  int TRACER_returning;
  int TRACER_breaking;

  {
    TRACER_returning = 0;
    TRACER_breaking = 0;
    KbFilter_InternIoCtl_status = 0;
    KbFilter_InternIoCtl_Irp__IoStatus__Information = 0;
    if (KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__IoControlCode >=
        KbFilter_InternIoCtl_CIL___Tmp20) {
      if (KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__IoControlCode <=
          KbFilter_InternIoCtl_CIL___Tmp20) {
        if (KbFilter_InternIoCtl_devExt__UpperConnectData__ClassService > 0) {
          KbFilter_InternIoCtl_status = -1073741757;
          TRACER_breaking = 1;
        } else {
          if (KbFilter_InternIoCtl_devExt__UpperConnectData__ClassService < 0) {
            KbFilter_InternIoCtl_status = -1073741757;
            TRACER_breaking = 1;
          } else {
            if (KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__InputBufferLength <
                KbFilter_InternIoCtl_sizeof__CONNECT_DATA) {
              KbFilter_InternIoCtl_status = -1073741811;
              TRACER_breaking = 1;
            }
          }
        }
        if (TRACER_breaking <= 0) {
          KbFilter_InternIoCtl_connectData =
              KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__Type3InputBuffer;
        }
      } else {
        goto _L___0;
      }
    } else {
    _L___0: /* CIL Label */
      if (KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__IoControlCode >=
          KbFilter_InternIoCtl_CIL___Tmp24) {
        if (KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__IoControlCode <=
            KbFilter_InternIoCtl_CIL___Tmp24) {
          KbFilter_InternIoCtl_status = -1073741822;
        } else {
          goto _L;
        }
      } else {
      _L: /* CIL Label */
        if (KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__IoControlCode >=
            KbFilter_InternIoCtl_CIL___Tmp28) {
          if (KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__IoControlCode <=
              KbFilter_InternIoCtl_CIL___Tmp28) {
            if (KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__InputBufferLength <
                KbFilter_InternIoCtl_sizeof__INTERNAL_I8042_HOOK_KEYBOARD) {
              KbFilter_InternIoCtl_status = -1073741811;
            } else {
              KbFilter_InternIoCtl_hookKeyboard =
                  KbFilter_InternIoCtl_irpStack__Parameters__DeviceIoControl__Type3InputBuffer;
              KbFilter_InternIoCtl_status = 0;
            }
          }
        }
      }
    }
    if (KbFilter_InternIoCtl_status < 0) {
      KbFilter_InternIoCtl_Irp__IoStatus__Status = KbFilter_InternIoCtl_status;
      myStatus = KbFilter_InternIoCtl_status;
      IofCompleteRequest(KbFilter_InternIoCtl_Irp, 0);
      retres26 = KbFilter_InternIoCtl_status;
      TRACER_returning = 1;
    } else {
      KbFilter_InternIoCtl_tmp = KbFilter_DispatchPassThrough(
          KbFilter_InternIoCtl_DeviceObject, KbFilter_InternIoCtl_Irp);
      retres26 = KbFilter_InternIoCtl_tmp;
    }
    return (retres26);
  }
}
