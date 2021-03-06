#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int wcet;
void tracerx_check() {
  printf("Timing of Path:%d\n", wcet);
  klee_assert(wcet < 5001);
}
int main() {
  wcet = 0;

  unsigned Cur_Vertical_Sep;
  unsigned High_Confidence;
  unsigned Two_of_Three_Reports_Valid;
  unsigned Own_Tracked_Alt;
  unsigned Own_Tracked_Alt_Rate;
  unsigned Other_Tracked_Alt;
  unsigned Alt_Layer_Value;
  unsigned Positive_RA_Alt_Thresh__0;
  unsigned Positive_RA_Alt_Thresh__1;
  unsigned Positive_RA_Alt_Thresh__2;
  unsigned Positive_RA_Alt_Thresh__3;
  unsigned Up_Separation;
  unsigned Down_Separation;
  unsigned Other_RAC;
  unsigned Other_Capability;
  unsigned Climb_Inhibit;

  klee_make_symbolic(&Cur_Vertical_Sep, sizeof(unsigned), "Cur_Vertical_Sep");
  klee_make_symbolic(&High_Confidence, sizeof(unsigned), "High_Confidence");
  klee_make_symbolic(&Two_of_Three_Reports_Valid, sizeof(unsigned),
                     "Two_of_Three_Reports_Valid");
  klee_make_symbolic(&Own_Tracked_Alt, sizeof(unsigned), "Own_Tracked_Alt");
  klee_make_symbolic(&Own_Tracked_Alt_Rate, sizeof(unsigned),
                     "Own_Tracked_Alt_Rate");
  klee_make_symbolic(&Other_Tracked_Alt, sizeof(unsigned), "Other_Tracked_Alt");
  klee_make_symbolic(&Alt_Layer_Value, sizeof(unsigned), "Alt_Layer_Value");
  klee_make_symbolic(&Positive_RA_Alt_Thresh__0, sizeof(unsigned),
                     "Positive_RA_Alt_Thresh__0");
  klee_make_symbolic(&Positive_RA_Alt_Thresh__1, sizeof(unsigned),
                     "Positive_RA_Alt_Thresh__1");
  klee_make_symbolic(&Positive_RA_Alt_Thresh__2, sizeof(unsigned),
                     "Positive_RA_Alt_Thresh__2");
  klee_make_symbolic(&Positive_RA_Alt_Thresh__3, sizeof(unsigned),
                     "Positive_RA_Alt_Thresh__3");
  klee_make_symbolic(&Up_Separation, sizeof(unsigned), "Up_Separation");
  klee_make_symbolic(&Down_Separation, sizeof(unsigned), "Down_Separation");
  klee_make_symbolic(&Other_RAC, sizeof(unsigned), "Other_RAC");
  klee_make_symbolic(&Other_Capability, sizeof(unsigned), "Other_Capability");
  klee_make_symbolic(&Climb_Inhibit, sizeof(unsigned), "Climb_Inhibit");

  unsigned enabled, tcas_equipped, intent_not_known;
  unsigned need_upward_RA, need_downward_RA;
  unsigned alt_sep;
  unsigned alim;
  // New variables added ....
  unsigned temp1, temp2, temp3, temp4;
  unsigned result_Non_Crossing_Biased_Climb;
  unsigned result_Non_Crossing_Biased_Descend;
  klee_make_symbolic(&enabled, sizeof(unsigned), "enabled");
  klee_make_symbolic(&tcas_equipped, sizeof(unsigned), "tcas_equipped");
  klee_make_symbolic(&intent_not_known, sizeof(unsigned), "intent_not_known");
  klee_make_symbolic(&need_upward_RA, sizeof(unsigned), "need_upward_RA");
  klee_make_symbolic(&need_downward_RA, sizeof(unsigned), "need_downward_RA");
  klee_make_symbolic(&alt_sep, sizeof(unsigned), "alt_sep");
  klee_make_symbolic(&alim, sizeof(unsigned), "alim");
  klee_make_symbolic(&temp1, sizeof(unsigned), "temp1");
  klee_make_symbolic(&temp2, sizeof(unsigned), "temp2");
  klee_make_symbolic(&temp3, sizeof(unsigned), "temp3");
  klee_make_symbolic(&temp4, sizeof(unsigned), "temp4");
  klee_make_symbolic(&result_Non_Crossing_Biased_Climb, sizeof(unsigned),
                     "result_Non_Crossing_Biased_Climb");
  klee_make_symbolic(&result_Non_Crossing_Biased_Descend, sizeof(unsigned),
                     "result_Non_Crossing_Biased_Descend");

  // -- initialize();
  Positive_RA_Alt_Thresh__0 = 400;
  Positive_RA_Alt_Thresh__1 = 500;
  Positive_RA_Alt_Thresh__2 = 640;
  Positive_RA_Alt_Thresh__3 = 740;
  wcet += 4;
  // -- alt_sep_test();

  enabled = 0;
  tcas_equipped = 0;
  intent_not_known = 0;
  need_upward_RA = 0;
  need_downward_RA = 0;
  wcet += 4;

  // -- -- alim = ALIM();
  if (Alt_Layer_Value == 0) {
    alim = Positive_RA_Alt_Thresh__0;
    wcet += 1;
  }
  if (Alt_Layer_Value == 1) {
    alim = Positive_RA_Alt_Thresh__1;
    wcet += 1;
  }
  if (Alt_Layer_Value == 2) {
    alim = Positive_RA_Alt_Thresh__2;
    wcet += 1;
  }
  alim = Positive_RA_Alt_Thresh__3;
  wcet += 1;

  if ((High_Confidence != 0) && (Own_Tracked_Alt_Rate <= 600) &&
      (Cur_Vertical_Sep > 600)) {
    enabled = 1;
    wcet += 1;
  }

  if (Other_Capability == 0) {
    tcas_equipped = 1;
    wcet += 1;
  }
  if ((Two_of_Three_Reports_Valid != 0) && Other_RAC == 0) {
    intent_not_known = 1;
    wcet += 1;
  }
  alt_sep = 0;
  wcet += 1;

  if ((enabled != 0) && (((tcas_equipped != 0) && (intent_not_known != 0)) ||
                         !(tcas_equipped != 0))) {
    //////////////////////////////////////////////////////////////////////////////
    { // ENTERING Non_Crossing_Biased_Climb();
      unsigned upward_preferred_1;
      unsigned alim_Non_Crossing_Biased_Climb;
      unsigned temp11, temp12, temp13;

      klee_make_symbolic(&upward_preferred_1, sizeof(unsigned),
                         "upward_preferred_1");
      klee_make_symbolic(&alim_Non_Crossing_Biased_Climb, sizeof(unsigned),
                         "alim_Non_Crossing_Biased_Climb");
      klee_make_symbolic(&temp11, sizeof(unsigned), "temp11");
      klee_make_symbolic(&temp12, sizeof(unsigned), "temp12");
      klee_make_symbolic(&temp13, sizeof(unsigned), "temp13");

      upward_preferred_1 = 0;
      result_Non_Crossing_Biased_Climb = 0;
      wcet += 2;
      // alim = ALIM() ;
      if (Alt_Layer_Value == 0) {
        alim_Non_Crossing_Biased_Climb = Positive_RA_Alt_Thresh__0;
        wcet += 1;
      }
      if (Alt_Layer_Value == 1) {
        alim_Non_Crossing_Biased_Climb = Positive_RA_Alt_Thresh__1;
        wcet += 1;
      }
      if (Alt_Layer_Value == 2) {
        alim_Non_Crossing_Biased_Climb = Positive_RA_Alt_Thresh__2;
        wcet += 1;
      }
      alim_Non_Crossing_Biased_Climb = Positive_RA_Alt_Thresh__3;
      wcet += 1;

      // temp11 = Inhibit_Biased_Climb();
      if (Climb_Inhibit == 1) {
        temp11 = Up_Separation + 100;
        wcet += 1;
      } else {
        temp11 = Up_Separation;
        wcet += 1;
      }

      if (temp11 > Down_Separation) {
        upward_preferred_1 = 1;
        wcet += 1;
      }

      if (upward_preferred_1 == 1) {
        // temp12 = Own_Below_Threat();
        if (Own_Tracked_Alt < Other_Tracked_Alt) {
          temp12 = 1;
          wcet += 1;
        } else {
          temp12 = 0;
          wcet += 1;
        }
        if (!(temp12 != 0) ||
            ((temp12 != 0) &&
             (!(Down_Separation >= alim_Non_Crossing_Biased_Climb)))) {
          result_Non_Crossing_Biased_Climb = 1;
          wcet += 1;
        }
      } else {
        // temp13= Own_Above_Threat();
        if (Other_Tracked_Alt < Own_Tracked_Alt) {
          temp13 = 1;
          wcet += 1;
        } else {
          temp13 = 0;
          wcet += 1;
        }
        if ((temp13 != 0) && (Cur_Vertical_Sep >= 300) &&
            (Up_Separation >= alim_Non_Crossing_Biased_Climb)) {
          result_Non_Crossing_Biased_Climb = 1;
          wcet += 1;
        }
      }
    } // LEAVING_NON_CROSSING_BIASED_CLIMB:
    //////////////////////////////////////////////////////////////////////////////
    temp1 = result_Non_Crossing_Biased_Climb;
    wcet += 1;
    //  temp2 = Own_Below_Threat();
    if (Own_Tracked_Alt < Other_Tracked_Alt) {
      temp2 = 1;
      wcet += 1;
    } else {
      temp2 = 0;
      wcet += 1;
    }

    if ((temp1 != 0) && (temp2 != 0)) {
      need_upward_RA = 1;
      wcet += 1;
    }

    //////////////////////////////////////////////////////////////////////////////
    // temp3 = Non_Crossing_Biased_Descend();
    //////////////////////////////////////////////////////////////////////////////
    {
      // ENTERING Non_Crossing_Biased_Descend()
      unsigned upward_preferred_2;
      unsigned alim_Non_Crossing_Biased_Descend;
      unsigned temp21, temp22, temp23;
      klee_make_symbolic(&upward_preferred_2, sizeof(unsigned),
                         "upward_preferred_2");
      klee_make_symbolic(&alim_Non_Crossing_Biased_Descend, sizeof(unsigned),
                         "alim_Non_Crossing_Biased_Descend");
      klee_make_symbolic(&temp21, sizeof(unsigned), "temp21");
      klee_make_symbolic(&temp22, sizeof(unsigned), "temp22");
      klee_make_symbolic(&temp23, sizeof(unsigned), "temp23");

      upward_preferred_2 = 0;
      result_Non_Crossing_Biased_Descend = 0;
      wcet += 2;

      // alim_Non_Crossing_Biased_Descend=ALIM() ;
      if (Alt_Layer_Value == 0) {
        alim_Non_Crossing_Biased_Descend = Positive_RA_Alt_Thresh__0;
        wcet += 1;
      }
      if (Alt_Layer_Value == 1) {
        alim_Non_Crossing_Biased_Descend = Positive_RA_Alt_Thresh__1;
        wcet += 1;
      }
      if (Alt_Layer_Value == 2) {
        alim_Non_Crossing_Biased_Descend = Positive_RA_Alt_Thresh__2;
        wcet += 1;
      }
      alim_Non_Crossing_Biased_Descend = Positive_RA_Alt_Thresh__3;
      wcet += 1;

      // temp21 = Inhibit_Biased_Climb();
      if (Climb_Inhibit == 1) {
        temp21 = Up_Separation + 100;
        wcet += 1;
      } else {
        temp21 = Up_Separation;
        wcet += 1;
      }

      if (temp21 > Down_Separation) {
        upward_preferred_2 = 1;
        wcet += 1;
      }
      if (upward_preferred_2 == 1) {
        // temp22 = Own_Below_Threat();
        if (Own_Tracked_Alt < Other_Tracked_Alt) {
          temp22 = 1;
          wcet += 1;
        } else {
          temp22 = 0;
          wcet += 1;
        }

        if ((temp22 != 0) && (Cur_Vertical_Sep >= 300) &&
            (Down_Separation >= alim_Non_Crossing_Biased_Descend)) {
          result_Non_Crossing_Biased_Descend = 1;
          wcet += 1;
        }
      } else {
        // temp23 = Own_Above_Threat();
        if (Other_Tracked_Alt < Own_Tracked_Alt) {
          temp23 = 1;
          wcet += 1;
        } else {
          temp23 = 0;
          wcet += 1;
        }

        if (!(temp23 != 0) ||
            ((temp23 != 0) &&
             (Up_Separation >= alim_Non_Crossing_Biased_Descend))) {
          result_Non_Crossing_Biased_Descend = 1;
          wcet += 1;
        }
      }

    } // ENTERING Non_Crossing_Biased_Descend()
    //////////////////////////////////////////////////////////////////////////////
    temp3 = result_Non_Crossing_Biased_Descend;
    wcet += 1;
    // temp4 = Own_Above_Threat();
    if (Other_Tracked_Alt < Own_Tracked_Alt) {
      temp4 = 1;
      wcet += 1;
    } else {
      temp4 = 0;
      wcet += 1;
    }
    if ((temp3 != 0) && (temp4 != 0)) {
      need_downward_RA = 1;
      wcet += 1;
    }
    if ((need_upward_RA != 0) && (need_downward_RA != 0)) {
      alt_sep = 0;
      wcet += 1;
    } else if ((need_upward_RA != 0)) {
      alt_sep = 1;
      wcet += 1;
    } else if ((need_downward_RA != 0)) {
      // BLAST/ARMC
      // if( Up_Separation >= alim && Down_Separation < alim )
      //     ERROR: goto ERROR;
      // TRACER
      //_DECOMPILE_ABORT( Up_Separation >= alim && Down_Separation < alim );
      alt_sep = 2;
      wcet += 1;
    } else {
      alt_sep = 0;
      wcet += 1;
    }
  }
  tracerx_check();
  return 0;
}
