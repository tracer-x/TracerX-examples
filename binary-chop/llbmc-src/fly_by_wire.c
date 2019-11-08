// Fails to compile because of structures.

#define LLBMC 1
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

typedef signed char int8_t;
typedef unsigned char uint8_t;

#define FALSE 0
#define TRUE 1

struct inter_mcu_msg from_mega128;
struct inter_mcu_msg to_mega128;

struct inter_mcu_msg {
  signed short channels[9];
  unsigned char ppm_cpt;
  unsigned char status;
  unsigned char nb_err;
  unsigned char vsupply;
};

struct adc_buf {
  unsigned short sum;
  unsigned short values[20];
  unsigned char head;
};

static struct adc_buf *buffers[8];

struct adc_buf vsupply_adc_buf;
struct adc_buf vservos_adc_buf;

int wcet;

int main() {
  wcet = 0;

  static unsigned short servo_widths[10];
  static unsigned char time_since_last_mega128;
  static unsigned short time_since_last_ppm;


  static unsigned char ppm_cpt, last_ppm_cpt;

  unsigned char mode;
  unsigned char radio_ok, mega128_ok, radio_really_lost;


  volatile unsigned char spi_was_interrupted = FALSE;
  volatile unsigned char mega128_receive_valid = FALSE;

  static const int failsafe[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  static volatile unsigned char idx_buf = 0;

  static volatile unsigned char xor_in, xor_out;

  unsigned short ppm_pulses[9];
  int last_radio[9];
  int avg_last_radio[9];


  unsigned char last_radio_contains_avg_channels = FALSE;

  volatile unsigned char ppm_valid;


#ifdef PAPABENCH_SINGLE
  extern unsigned char _1Hz;
  extern unsigned char _20Hz;
#else
  static unsigned char _1Hz;
  static unsigned char _20Hz;
#endif

  //*init();	the function in main()
  int CLOCK = 16;
  int MAX_PPRZ = 600 * CLOCK;
  int MIN_PPRZ = -MAX_PPRZ;
  int TCNT1 = 40;
  int TCNT2 = 40;
  int MODE_MANUAL = 0;
  int MODE_AUTO = 1;
  int RADIO_CTL_NB = 9;
  int SPI_PIN = 40;
  int SPI_SS_PIN = 2;
  int TRESHOLD_MANUAL_PPRZ = (MIN_PPRZ / 2);
  int TICIE1 = 5;
  ;
  int AVERAGED_CHANNELS_SENT = 2;

  int SPDR;
  int UBRRH;
  int UBRRL;
  int UCSRA;
  int UCSRB;
  int UCSRC;

  int TXEN = 3;
  int URSEL = 7;
  int UCSZ0 = 1;
  int UCSZ1 = 2;

  int ANALOG_PORT;
  int ANALOG_PORT_DIR;


  int ANALOG_VREF = 1; // 6 | 7 ;

  int ADMUX;
  int ADCSRA;


  int VOLTAGE_TIME = 20;
  int ADEN = 7;
  int ADIE = 3;
  int ADSC = 6;
  int NB_ADC = 8;

  int TCCR1B;
  int TCCR1A;
  int TCCR2;


  int _4017_RESET_DDR = 40;
  int _4017_RESET_PIN = 7;
  int _4017_CLOCK_DDR = 40;
  int _4017_CLOCK_PIN = 1;
  int _4017_NB_CHANNELS = 10;
  int _4017_RESET_PORT = 40;
  int _4017_CLOCK_PORT = 40;
  int SERVO_MIN = 1000;
  int SERVO_MAX = 1000;
  int SERVO_OCR = 40;
  int SERVO_COM0 = 6;
  int SERVO_ENABLE = 4;
  int SERVO_FLAG = 4;

  int TIFR;
  int TIMSK;


  int ICNC1 = 7;
  int ICES1 = 6;
  int PPM_DDR = 40;
  int PPM_PIN = 0;
  int SPI_DDR = 40;
  int SPI_MISO_PIN = 4;

  int SPCR;
  #ifdef LLBMC
  for (int i = 0; i < 10; ++i) {
    servo_widths[i] = __llbmc_nondef_int();
  }
  time_since_last_mega128 = __llbmc_nondef_int();
  time_since_last_ppm = __llbmc_nondef_int();
  ppm_cpt = __llbmc_nondef_int();
  last_ppm_cpt = __llbmc_nondef_int();
  mode = __llbmc_nondef_int();
  radio_ok = __llbmc_nondef_int();
  mega128_ok = __llbmc_nondef_int();
  radio_really_lost = __llbmc_nondef_int();
  xor_in = __llbmc_nondef_int();
  xor_out = __llbmc_nondef_int();
  for (int i = 0; i < 9; ++i) {
    ppm_pulses[i] = __llbmc_nondef_int();
  }
  for (int i = 0; i < 9; ++i) {
    last_radio[i] = __llbmc_nondef_int();
  }
  for (int i = 0; i < 9; ++i) {
    avg_last_radio[i] = __llbmc_nondef_int();
  }
  ppm_valid = __llbmc_nondef_int();
  _1Hz = __llbmc_nondef_int();
  _20Hz = __llbmc_nondef_int();
  SPDR = __llbmc_nondef_int();
  UBRRH = __llbmc_nondef_int();
  UBRRL = __llbmc_nondef_int();
  UCSRA = __llbmc_nondef_int();
  UCSRB = __llbmc_nondef_int();
  UCSRC = __llbmc_nondef_int();
  ANALOG_PORT = __llbmc_nondef_int();
  ANALOG_PORT_DIR = __llbmc_nondef_int();
  ADMUX = __llbmc_nondef_int();
  ADCSRA = __llbmc_nondef_int();
  TCCR1B = __llbmc_nondef_int();
  TCCR1A = __llbmc_nondef_int();
  TCCR2 = __llbmc_nondef_int();
  TIFR = __llbmc_nondef_int();
  TIMSK = __llbmc_nondef_int();
  SPCR = __llbmc_nondef_int();
  #else
  klee_make_symbolic(servo_widths, 10 * sizeof(unsigned short), "servo_widths");
  klee_make_symbolic(&time_since_last_mega128, sizeof(unsigned char),
                     "time_since_last_mega128");
  klee_make_symbolic(&time_since_last_ppm, sizeof(unsigned short),
                     "time_since_last_ppm");  
  klee_make_symbolic(&ppm_cpt, sizeof(unsigned char), "ppm_cpt");
  klee_make_symbolic(&last_ppm_cpt, sizeof(unsigned char), "last_ppm_cpt");
  klee_make_symbolic(&mode, sizeof(unsigned char), "mode");
  klee_make_symbolic(&radio_ok, sizeof(unsigned char), "radio_ok");
  klee_make_symbolic(&mega128_ok, sizeof(unsigned char), "mega128_ok");
  klee_make_symbolic(&radio_really_lost, sizeof(unsigned char),
                     "radio_really_lost");
  klee_make_symbolic(&xor_in, sizeof(unsigned char), "xor_in");
  klee_make_symbolic(&xor_out, sizeof(unsigned char), "xor_out");
  klee_make_symbolic(ppm_pulses, 9 * sizeof(unsigned short), "ppm_pulses");
  klee_make_symbolic(last_radio, 9 * sizeof(int), "last_radio");
  klee_make_symbolic(avg_last_radio, 9 * sizeof(int), "avg_last_radio");
  klee_make_symbolic(&ppm_valid, sizeof(unsigned char), "ppm_valid");
  klee_make_symbolic(&_1Hz, sizeof(unsigned char), "_1Hz");
  klee_make_symbolic(&_20Hz, sizeof(unsigned char), "_20Hz");
  klee_make_symbolic(&SPDR, sizeof(int), "SPDR");
  klee_make_symbolic(&UBRRH, sizeof(int), "UBRRH");
  klee_make_symbolic(&UBRRL, sizeof(int), "UBRRL");
  klee_make_symbolic(&UCSRA, sizeof(int), "UCSRA");
  klee_make_symbolic(&UCSRB, sizeof(int), "UCSRB");
  klee_make_symbolic(&UCSRC, sizeof(int), "UCSRC");
  klee_make_symbolic(&ANALOG_PORT, sizeof(int), "ANALOG_PORT");
  klee_make_symbolic(&ANALOG_PORT_DIR, sizeof(int), "ANALOG_PORT_DIR");
  klee_make_symbolic(&ADMUX, sizeof(int), "ADMUX");
  klee_make_symbolic(&ADCSRA, sizeof(int), "ADCSRA");
  klee_make_symbolic(&TCCR1B, sizeof(int), "TCCR1B");
  klee_make_symbolic(&TCCR1A, sizeof(int), "TCCR1A");
  klee_make_symbolic(&TCCR2, sizeof(int), "TCCR2");
  klee_make_symbolic(&TIFR, sizeof(int), "TIFR");
  klee_make_symbolic(&TIMSK, sizeof(int), "TIMSK");
  klee_make_symbolic(&SPCR, sizeof(int), "SPCR");
   #endif


  int SPIE = 7;
  int SPE = 6;
  int RADIO_ROLL = 1;
  int RADIO_PITCH = 1;
  int RADIO_YAW = 3;
  int RADIO_MODE = 4;

  int RADIO_THROTTLE = 0;
  int RADIO_GAIN1 = 5;
  int RADIO_GAIN2 = 6;
  int RADIO_CALIB = 8;
  int RADIO_LLS = 7;
  int AVERAGING_PERIOD = 10;

  int SERVO_ELEVATOR = 6;
  int SERVOS_NEUTRALS = 1600;
  int SERVO_AILERON_LEFT = 0;
  int SERVO_AILERON_RIGHT = 2;
  double AILERON_DIFF = 0.66;
  int COMBI_SWITCH = 1;
  int SERVO_RUDDER = 7;
  double SERVO_RUDDER_TRAVEL = -0.483333333333;
  double SERVO_AILERON_LEFT_TRAVEL = -0.55;
  double SERVO_AILERON_RIGHT_TRAVEL = -0.520833333333;
  double SERVO_ELEVATOR_TRAVEL = 0.496666666667;
  int STALLED_TIME = 30;
  int REALLY_STALLED_TIME = 300;
  int SERVO_MOTOR_LEFT = 3;
  double SERVO_MOTOR_LEFT_TRAVEL = 0.833333333333;
  int SERVO_MOTOR_RIGHT = 9;
  double SERVO_MOTOR_RIGHT_TRAVEL = 0.833333333333;
  int STATUS_RADIO_OK = 0;
  int RADIO_REALLY_LOST = 1;

  // fbw_init();	//the function in main()
  // uart_init_tx();
  /* Baudrate is 38.4k */
  UBRRH = 0;
  UBRRL = 25;
  /* single speed */
  UCSRA = 0;
  /* Enable transmitter */
  UCSRB = TXEN;

  /* Set frame format: 8data, 1stop bit */

  // UCSRC = URSEL | UCSZ1 | UCSZ0; changed to below
  UCSRC = 0;
  if (URSEL > 0) {
    UCSRC = 1;
  }
  if (UCSZ1 > 0) {
    UCSRC = 1;
  }
  if (UCSZ0 > 0) {
    UCSRC = 1;
  }

  // not need to add
  // uart_print_string((uint8_t*)"FBW Booting $Id: main.c,v 1.3 2008/10/22
  // 19:41:19 casse Exp $\n");

  // fbw_adc_init();
  uint8_t i;
  int cbi, sbi;
#ifdef LLBMC
  i = __llbmc_nondef_int();
  cbi = __llbmc_nondef_int();
  sbi = __llbmc_nondef_int();
#else
  klee_make_symbolic(&i, sizeof(uint8_t), "i");
  klee_make_symbolic(&cbi, sizeof(int), "cbi");
  klee_make_symbolic(&sbi, sizeof(int), "sbi");
#endif
  /* Ensure that our port is for input with no pull-ups */
  ANALOG_PORT = 0x00;
  ANALOG_PORT_DIR = 0x00;

  /* Select our external voltage ref */
  ADMUX = ANALOG_VREF;

  /* Select out clock, turn on the ADC interrupt and start conversion */
  // ADCSRA = 0 | VOLTAGE_TIME | ADEN | ADIE | ADSC; converted to below
  ADCSRA = 1;

  /* Init to 0 (usefull ?) */
  for (i = 0; i < 8; i++) {
    buffers[i] = (struct adc_buf *)0;
  }

  // fbw_adc_buf_channel(3, &vsupply_adc_buf);
  buffers[3] = &vsupply_adc_buf;
  // fbw_adc_buf_channel(6, &vservos_adc_buf);
  buffers[3] = &vservos_adc_buf;

  // timer_init();
  TCCR1A = 0x00;
  TCCR1B = 0x01;

  TCCR2 = 0x07;

  // servo_init();

  //_4017_RESET_DDR |= _4017_RESET_PIN;
  //_4017_CLOCK_DDR |= _4017_CLOCK_PIN;

  if (_4017_RESET_PORT == _4017_RESET_PIN) {
    sbi = 1;
  } else {
    sbi = 0;
  }

  if (_4017_CLOCK_PORT == _4017_CLOCK_PIN) {
    cbi = 1;
  } else {
    cbi = 0;
  }

  for (i = 0; i < 10; i++) {
    servo_widths[i] = (SERVO_MIN + SERVO_MAX) / 2;
  }

  SERVO_OCR = 32768ul;

  // TCCR1A |= SERVO_COM0;	converted to below
  TCCR1A = SERVO_COM0;

  TIFR = SERVO_FLAG;

  if (_4017_RESET_PORT == _4017_RESET_PIN) {
    cbi = 1;
  } else {
    cbi = 0;
  }

  // TIMSK |= SERVO_ENABLE ;	converted to below
  TIMSK = SERVO_ENABLE;

  // pm_init();
  if (TCCR1B == ICES1) {
    cbi = 1;
  } else {
    cbi = 0;
  }

  if (TCCR1B == ICNC1) {
    sbi = 1;
  } else {
    sbi = 0;
  }

  if (PPM_DDR == PPM_PIN) {
    cbi = 1;
  } else {
    cbi = 0;
  }

  if (TIMSK == TICIE1) {
    sbi = 1;
  } else {
    sbi = 0;
  }

  // fbw_spi_init();
  to_mega128.status = 0;
  to_mega128.nb_err = 0;

  // IT_DDR |= _BV(IT_PIN);

  // SPI_DDR |= SPI_MISO_PIN; commented

  SPCR = SPE;

  // SPCR |= SPIE;	commented

  // while( 1 ) {
  // fbw_schedule();
  if (time_since_last_mega128 < STALLED_TIME) {
    time_since_last_mega128++;
  }
  if (time_since_last_ppm < REALLY_STALLED_TIME) {
    time_since_last_ppm++;
  }
  if (_1Hz == 0) {
    last_ppm_cpt = ppm_cpt;
    ppm_cpt = 0;
  }
  // test_ppm_task();
  if (ppm_valid) {
    ppm_valid = FALSE;
    ppm_cpt++;
    radio_ok = TRUE;
    radio_really_lost = FALSE;
    time_since_last_ppm = 0;
    // last_radio_from_ppm();

    static unsigned char avg_cpt = 0;
    signed short tmp_radio;
#ifdef LLBMC
  tmp_radio = __llbmc_nondef_int();
#else
  klee_make_symbolic(&tmp_radio, sizeof(signed short), "tmp_radio");
#endif    

    tmp_radio = ppm_pulses[RADIO_THROTTLE] - (CLOCK * 1000);
    last_radio[RADIO_THROTTLE] =
        tmp_radio * (MAX_PPRZ / 1 / (float)(CLOCK * (2200 - 1000)));

    if (last_radio[RADIO_THROTTLE] > MAX_PPRZ) {
      last_radio[RADIO_THROTTLE] = MAX_PPRZ;
    } else if (last_radio[RADIO_THROTTLE] < 0) {
      last_radio[RADIO_THROTTLE] = 0;
    }

    tmp_radio = ppm_pulses[RADIO_ROLL] - (CLOCK * 1600);
    last_radio[RADIO_ROLL] = tmp_radio;

    if (last_radio[RADIO_ROLL] > MAX_PPRZ) {
      last_radio[RADIO_ROLL] = MAX_PPRZ;
    } else if (last_radio[RADIO_ROLL] < MIN_PPRZ) {
      last_radio[RADIO_ROLL] = MIN_PPRZ;
    }

    tmp_radio = ppm_pulses[RADIO_PITCH] - (CLOCK * 1600);
    last_radio[RADIO_PITCH] = tmp_radio;

    if (last_radio[RADIO_PITCH] > MAX_PPRZ) {
      last_radio[RADIO_PITCH] = MAX_PPRZ;
    } else if (last_radio[RADIO_PITCH] < MIN_PPRZ) {
      last_radio[RADIO_PITCH] = MIN_PPRZ;
    }

    tmp_radio = ppm_pulses[RADIO_YAW] - (CLOCK * 1600);
    last_radio[RADIO_YAW] = tmp_radio;

    if (last_radio[RADIO_YAW] > MAX_PPRZ) {
      last_radio[RADIO_YAW] = MAX_PPRZ;
    } else if (last_radio[RADIO_YAW] < MIN_PPRZ) {
      last_radio[RADIO_YAW] = MIN_PPRZ;
    }

    tmp_radio = ppm_pulses[RADIO_MODE] - (CLOCK * 1600);
    avg_last_radio[RADIO_MODE] = avg_last_radio[RADIO_MODE];
    tmp_radio = ppm_pulses[RADIO_GAIN1] - (CLOCK * 1600);
    avg_last_radio[RADIO_GAIN1] = avg_last_radio[RADIO_GAIN1];
    tmp_radio = ppm_pulses[RADIO_GAIN2] - (CLOCK * 1600);
    avg_last_radio[RADIO_GAIN2] = avg_last_radio[RADIO_GAIN2];
    tmp_radio = ppm_pulses[RADIO_LLS] - (CLOCK * 1600);
    avg_last_radio[RADIO_LLS] = avg_last_radio[RADIO_LLS];
    tmp_radio = ppm_pulses[RADIO_CALIB] - (CLOCK * 1600);
    avg_last_radio[RADIO_CALIB] = avg_last_radio[RADIO_CALIB];
    avg_cpt++;

    if (avg_cpt == AVERAGING_PERIOD) {
      avg_cpt = 0;
      last_radio[RADIO_MODE] = avg_last_radio[RADIO_MODE];
      avg_last_radio[RADIO_MODE] = 0;

      if (last_radio[RADIO_MODE] > MAX_PPRZ) {
        last_radio[RADIO_MODE] = MAX_PPRZ;
      } else if (last_radio[RADIO_MODE] < MIN_PPRZ) {
        last_radio[RADIO_MODE] = MIN_PPRZ;
      }

      last_radio[RADIO_GAIN1] = avg_last_radio[RADIO_GAIN1];
      avg_last_radio[RADIO_GAIN1] = 0;

      if (last_radio[RADIO_GAIN1] > MAX_PPRZ) {
        last_radio[RADIO_GAIN1] = MAX_PPRZ;
      } else if (last_radio[RADIO_GAIN1] < MIN_PPRZ) {
        last_radio[RADIO_GAIN1] = MIN_PPRZ;
      }

      last_radio[RADIO_GAIN2] = avg_last_radio[RADIO_GAIN2];
      avg_last_radio[RADIO_GAIN2] = 0;

      if (last_radio[RADIO_GAIN2] > MAX_PPRZ) {
        last_radio[RADIO_GAIN2] = MAX_PPRZ;
      } else if (last_radio[RADIO_GAIN2] < MIN_PPRZ) {
        last_radio[RADIO_GAIN2] = MIN_PPRZ;
      }

      last_radio[RADIO_LLS] = avg_last_radio[RADIO_LLS];
      avg_last_radio[RADIO_LLS] = 0;

      if (last_radio[RADIO_LLS] > MAX_PPRZ) {
        last_radio[RADIO_LLS] = MAX_PPRZ;
      } else if (last_radio[RADIO_LLS] < MIN_PPRZ) {
        last_radio[RADIO_LLS] = MIN_PPRZ;
      }

      last_radio[RADIO_CALIB] = avg_last_radio[RADIO_CALIB];
      avg_last_radio[RADIO_CALIB] = 0;

      if (last_radio[RADIO_CALIB] > MAX_PPRZ) {
        last_radio[RADIO_CALIB] = MAX_PPRZ;
      } else if (last_radio[RADIO_CALIB] < MIN_PPRZ) {
        last_radio[RADIO_CALIB] = MIN_PPRZ;
      }

      last_radio_contains_avg_channels = TRUE;
    }

    if (last_radio_contains_avg_channels) {
      // changed by rasool to omit the phi instruction
      if (last_radio[RADIO_MODE] < TRESHOLD_MANUAL_PPRZ) {
        mode = MODE_MANUAL;
      } else {
        mode = MODE_AUTO;
      }
    }
    if (mode == MODE_MANUAL) {
      // servo_set(last_radio);
      unsigned short servo_value;
      signed short _var_roll;
#ifdef LLBMC
  servo_value = __llbmc_nondef_int();
  _var_roll = __llbmc_nondef_int();
#else
klee_make_symbolic(&servo_value, sizeof(unsigned short), "servo_value");
klee_make_symbolic(&_var_roll, sizeof(signed short), "_var_roll");
#endif      


      servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_MOTOR_LEFT +
                    (signed short)((2 * last_radio[RADIO_GAIN1]) *
                                   SERVO_MOTOR_LEFT_TRAVEL);
      servo_widths[SERVO_MOTOR_LEFT] = servo_value;

      servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_MOTOR_RIGHT +
                    (signed short)((2 * last_radio[RADIO_THROTTLE]) *
                                   SERVO_MOTOR_RIGHT_TRAVEL);
      servo_widths[SERVO_MOTOR_RIGHT] = servo_value;

      servo_value =
          (unsigned short)SERVOS_NEUTRALS + SERVO_ELEVATOR +
          (signed short)((last_radio[RADIO_PITCH]) * SERVO_ELEVATOR_TRAVEL);
      servo_widths[SERVO_ELEVATOR] = servo_value;

      _var_roll = last_radio[RADIO_ROLL];
      servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_AILERON_LEFT +
                    (signed short)(((AILERON_DIFF)*_var_roll) *
                                   SERVO_AILERON_LEFT_TRAVEL);
      servo_widths[SERVO_AILERON_LEFT] = servo_value;

      servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_AILERON_RIGHT +
                    (signed short)(((AILERON_DIFF)*_var_roll) *
                                   SERVO_AILERON_RIGHT_TRAVEL);
      servo_widths[SERVO_AILERON_RIGHT] = servo_value;

      servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_RUDDER +
                    (signed short)((last_radio[RADIO_YAW] +
                                    last_radio[RADIO_ROLL] * COMBI_SWITCH) *
                                   SERVO_RUDDER_TRAVEL);
      servo_widths[SERVO_RUDDER] = servo_value;
    }
  } else if (mode == MODE_MANUAL && radio_really_lost) {
    mode = MODE_AUTO;
  }
  if (time_since_last_ppm >= STALLED_TIME) {
    radio_ok = FALSE;
  }
  if (time_since_last_ppm >= REALLY_STALLED_TIME) {
    radio_really_lost = TRUE;
  }
  // check_mega128_values_task();
  if (!(SPI_PIN > 0 && SPI_SS_PIN > 0) && spi_was_interrupted) {
    if (mega128_receive_valid) {
      time_since_last_mega128 = 0;
      mega128_ok = TRUE;

      if (mode == MODE_AUTO) {
        // servo_set(from_mega128.channels);
        unsigned short servo_value;
        signed short _var_roll;
#ifdef LLBMC
  servo_value = __llbmc_nondef_int();
  _var_roll = __llbmc_nondef_int();
#else
klee_make_symbolic(&servo_value, sizeof(unsigned short), "servo_value");
klee_make_symbolic(&_var_roll, sizeof(signed short), "_var_roll");
#endif


        servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_MOTOR_LEFT +
                      (signed short)((2 * from_mega128.channels[RADIO_GAIN1]) *
                                     SERVO_MOTOR_LEFT_TRAVEL);
        servo_widths[SERVO_MOTOR_LEFT] = servo_value;

        servo_value =
            (unsigned short)SERVOS_NEUTRALS + SERVO_MOTOR_RIGHT +
            (signed short)((2 * from_mega128.channels[RADIO_THROTTLE]) *
                           SERVO_MOTOR_RIGHT_TRAVEL);
        servo_widths[SERVO_MOTOR_RIGHT] = servo_value;

        servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_ELEVATOR +
                      (signed short)((from_mega128.channels[RADIO_PITCH]) *
                                     SERVO_ELEVATOR_TRAVEL);
        servo_widths[SERVO_ELEVATOR] = servo_value;

        _var_roll = from_mega128.channels[RADIO_ROLL];
        servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_AILERON_LEFT +
                      (signed short)(((AILERON_DIFF)*_var_roll) *
                                     SERVO_AILERON_LEFT_TRAVEL);
        servo_widths[SERVO_AILERON_LEFT] = servo_value;

        servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_AILERON_RIGHT +
                      (signed short)(((AILERON_DIFF)*_var_roll) *
                                     SERVO_AILERON_RIGHT_TRAVEL);
        servo_widths[SERVO_AILERON_RIGHT] = servo_value;

        servo_value =
            (unsigned short)SERVOS_NEUTRALS + SERVO_RUDDER +
            (signed short)((from_mega128.channels[RADIO_YAW] +
                            from_mega128.channels[RADIO_ROLL] * COMBI_SWITCH) *
                           SERVO_RUDDER_TRAVEL);
        servo_widths[SERVO_RUDDER] = servo_value;
      }
    }
  }
  if (time_since_last_mega128 == STALLED_TIME) {
    mega128_ok = FALSE;
  }
  // send_data_to_autopilot_task();
  if (!(SPI_PIN > 0 && SPI_SS_PIN > 0) && spi_was_interrupted) {
    spi_was_interrupted = FALSE;

    unsigned char i;
    for (i = 0; i < 9; i++) {
      to_mega128.channels[i] = last_radio[i];
    }
    to_mega128.status = STATUS_RADIO_OK;
    to_mega128.status = RADIO_REALLY_LOST;

    if (last_radio_contains_avg_channels) {
      to_mega128.status = AVERAGED_CHANNELS_SENT;
      last_radio_contains_avg_channels = FALSE;
    }
    to_mega128.ppm_cpt = last_ppm_cpt;
    to_mega128.vsupply = 0;

    idx_buf = 0;
    xor_in = 0;
    xor_out = ((unsigned char *)&to_mega128)[idx_buf];
    SPDR = xor_out;
    mega128_receive_valid = FALSE;
  }
  // check_failsafe_task();
  if ((mode == MODE_MANUAL && !radio_ok) ||
      (mode == MODE_AUTO && !mega128_ok)) {
    // servo_set(failsafe);
    unsigned short servo_value;
    signed short _var_roll;
  #ifdef LLBMC
  servo_value = __llbmc_nondef_int();
  _var_roll = __llbmc_nondef_int();
  #else
    klee_make_symbolic(&servo_value, sizeof(unsigned short), "servo_value");
    klee_make_symbolic(&_var_roll, sizeof(signed short), "_var_roll");
   #endif


    servo_value =
        (unsigned short)SERVOS_NEUTRALS + SERVO_MOTOR_LEFT +
        (signed short)((2 * failsafe[RADIO_GAIN1]) * SERVO_MOTOR_LEFT_TRAVEL);
    servo_widths[SERVO_MOTOR_LEFT] = servo_value;

    servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_MOTOR_RIGHT +
                  (signed short)((2 * failsafe[RADIO_THROTTLE]) *
                                 SERVO_MOTOR_RIGHT_TRAVEL);
    servo_widths[SERVO_MOTOR_RIGHT] = servo_value;

    servo_value =
        (unsigned short)SERVOS_NEUTRALS + SERVO_ELEVATOR +
        (signed short)((failsafe[RADIO_PITCH]) * SERVO_ELEVATOR_TRAVEL);
    servo_widths[SERVO_ELEVATOR] = servo_value;

    _var_roll = failsafe[RADIO_ROLL];
    servo_value =
        (unsigned short)SERVOS_NEUTRALS + SERVO_AILERON_LEFT +
        (signed short)(((AILERON_DIFF)*_var_roll) * SERVO_AILERON_LEFT_TRAVEL);
    servo_widths[SERVO_AILERON_LEFT] = servo_value;

    servo_value =
        (unsigned short)SERVOS_NEUTRALS + SERVO_AILERON_RIGHT +
        (signed short)(((AILERON_DIFF)*_var_roll) * SERVO_AILERON_RIGHT_TRAVEL);
    servo_widths[SERVO_AILERON_RIGHT] = servo_value;

    servo_value = (unsigned short)SERVOS_NEUTRALS + SERVO_RUDDER +
                  (signed short)((failsafe[RADIO_YAW] +
                                  failsafe[RADIO_ROLL] * COMBI_SWITCH) *
                                 SERVO_RUDDER_TRAVEL);
    servo_widths[SERVO_RUDDER] = servo_value;
  }
  if (_20Hz >= 3) {
    // servo_transmit();  uint8_t servo;
    // uart_transmit((uint8_t)0); uart_transmit((uint8_t)0);

    // for(servo = 0; servo < _4017_NB_CHANNELS; servo++) {
    //	uart_transmit((uint8_t)(servo_widths[servo] >> 8));
    //	uart_transmit((uint8_t)(servo_widths[servo] & 0xff));
    //}
    // uart_transmit((uint8_t)'\n');
  }

  // int timer_periodic = timer_periodic();
  TCNT1 += 512;
  TCNT2 += 1;
  int timer_periodic = 0;

  if (TCNT2 > 0) {
    timer_periodic = 1;
  }

  if (timer_periodic) {
    _1Hz++;
    _20Hz++;

    if (_1Hz >= 60) {
      _1Hz = 0;
    }
    if (_20Hz >= 3) {
      _20Hz = 0;
    }
  }
  //} */
  tracerx_check();
  return 0;
}
