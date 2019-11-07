/* Generated by CIL v. 1.3.7 */
/* print_CIL_Input is true */
#include <stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif


int KernelMode;
int Executive;
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
int safety;
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
  int KbFilter_PnP_irpSp__Control;
  int KbFilter_PnP_CIL___Tmp23;

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
        KbFilter_PnP_irpSp__Control = 224;
        KbFilter_PnP_status =
            IofCallDriver(KbFilter_PnP_devExt__TopOfStack, KbFilter_PnP_Irp);
        KbFilter_PnP_CIL___Tmp23 = KbFilter_PnP_status;
        if (KbFilter_PnP_CIL___Tmp23 >= 259) {
          if (KbFilter_PnP_CIL___Tmp23 <= 259) {
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
int main() {
  wcet = 0;
  int main_status;
  int main_irp;
  int main_pirp;
  int main_devobj;
  int main_tmp_ndt_1;

  {
    safety = 0;
    main_pirp = main_irp;
    _BLAST_init();
    stub_driver_init();
    klee_make_symbolic(&main_tmp_ndt_1, sizeof(int), "main_tmp_ndt_1");
    if (main_tmp_ndt_1 >= 3) {
      if (main_tmp_ndt_1 <= 3) {
        main_status = KbFilter_PnP(main_devobj, main_pirp);
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
  int IofCallDriver_tmp_ndt_2;
  int IofCallDriver_tmp_ndt_3;

  {
    if (compRegistered > 0) {
      IofCallDriver_compRetStatus =
          KbFilter_Complete(IofCallDriver_DeviceObject, IofCallDriver_Irp,
                            IofCallDriver_lcontext);
      stubMoreProcessingRequired();
    } else {
      if (compRegistered < 0) {
        IofCallDriver_compRetStatus =
            KbFilter_Complete(IofCallDriver_DeviceObject, IofCallDriver_Irp,
                              IofCallDriver_lcontext);
        stubMoreProcessingRequired();
      }
    }
    klee_make_symbolic(&IofCallDriver_tmp_ndt_2, sizeof(int),
                       "IofCallDriver_tmp_ndt_2");
    if (IofCallDriver_tmp_ndt_2 >= 0) {
      if (IofCallDriver_tmp_ndt_2 <= 0) {
        IofCallDriver_returnVal2 = 0;
      } else {
        goto _L;
      }
    } else {
    _L: /* CIL Label */
      klee_make_symbolic(&IofCallDriver_tmp_ndt_3, sizeof(int),
                         "IofCallDriver_tmp_ndt_3");
      if (IofCallDriver_tmp_ndt_3 >= 1) {
        if (IofCallDriver_tmp_ndt_3 <= 1) {
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
        goto _L___0;
      }
    } else {
    _L___0: /* CIL Label */
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
  int KeWaitForSingleObject_tmp_ndt_4;
  int retres;

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
    klee_make_symbolic(&KeWaitForSingleObject_tmp_ndt_4, sizeof(int),
                       "KeWaitForSingleObject_tmp_ndt_4");
    if (KeWaitForSingleObject_tmp_ndt_4 >= 0) {
      if (KeWaitForSingleObject_tmp_ndt_4 <= 0) {
        retres = 0;
      } else {
        retres = -1073741823;
      }
    } else {
      retres = -1073741823;
    }
    return (retres);
  }
}
int KbFilter_Complete(int KbFilter_Complete_DeviceObject,
                      int KbFilter_Complete_Irp,
                      int KbFilter_Complete_Context) {
  int retres;
  int KbFilter_Complete_event;

  {
    KbFilter_Complete_event = KbFilter_Complete_Context;
    KeSetEvent(KbFilter_Complete_event, 0, 0);
    retres = -1073741802;
    return (retres);
  }
}
