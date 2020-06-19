//This Program is Problem3-LTL-TRAINING-RERS18.c
#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define BOUND 15
int kappa;

int input,output;
#include <assert.h>
#include <math.h>
#include <stdlib.h>

	// inputs
	int inputs[] = {7,10,8,3,6,1,9,4,5,2};

	int calculate_output(int);
	int calculate_outputm1(int);
	int calculate_outputm2(int);
	int calculate_outputm3(int);
	int calculate_outputm4(int);
	int calculate_outputm5(int);
	int calculate_outputm6(int);
	int calculate_outputm7(int);
	int calculate_outputm8(int);
	int calculate_outputm9(int);
	int calculate_outputm10(int);
	int calculate_outputm11(int);
	int calculate_outputm12(int);
	int calculate_outputm13(int);
	int calculate_outputm14(int);
	int calculate_outputm15(int);
	int calculate_outputm16(int);
	int calculate_outputm17(int);
	int calculate_outputm18(int);
	int calculate_outputm19(int);
	int calculate_outputm20(int);
	int calculate_outputm21(int);
	int calculate_outputm22(int);
	int calculate_outputm23(int);
	int calculate_outputm24(int);
	int calculate_outputm25(int);
	int calculate_outputm26(int);
	int calculate_outputm27(int);
	int calculate_outputm28(int);
	int calculate_outputm29(int);
	int calculate_outputm30(int);
	int calculate_outputm31(int);
	int calculate_outputm32(int);
	int calculate_outputm33(int);
	int calculate_outputm34(int);
	int calculate_outputm35(int);
	int calculate_outputm36(int);

	 int a1056944550  = 32;
	 int a2027611119[] = {2,3,4,5,6,7,8,9};
	 int a778335169 = 2;
	 int a753453731[] = {5,6,7,8,9,10};
	 int a149495938[] = {11,12,13,14,15,16};
	 int a378180103[] = {17,18,19,20,21,22};
	 int *a1979864000 = a753453731;
	 int a162289881 = 12;
	 int a1663271343  = 33;
	 int a1518986556 = 2;
	 int a190474899 = 88;
	 int a1487144088[] = {15,16,17,18,19,20};
	 int a1071644789[] = {21,22,23,24,25,26};
	 int a550880306[] = {27,28,29,30,31,32};
	 int *a1675980795 = a550880306;
	 int cf = 1;

 int calculate_outputm1(int input) {
    if((input == inputs[9] && (a778335169 == a2027611119[0] &&  cf==1 ))) {
    	cf = 0;
    	if((a1663271343 == 35 && ( cf==1  && (( cf==1  && (26 == a1675980795[5])) && a778335169 == a2027611119[7])))) {
    	 
    	}else {
    	a1056944550 = 36 ;
    	a778335169 = a2027611119[6];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 24);  
    } 
    if((a778335169 == a2027611119[0] && ( cf==1  && input == inputs[8]))) {
    	cf = 0;
    	a1663271343 = 32 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((a778335169 == a2027611119[0] && ((18 == a1675980795[3]) &&  cf==1 ))) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 6; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
}
 int calculate_outputm2(int input) {
    if((a778335169 == a2027611119[0] && ( cf==1  && input == inputs[4]))) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 3; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
}
 int calculate_outputm3(int input) {
    if((( cf==1  && (28 == a1675980795[1])) && a778335169 == a2027611119[0])) {
    	cf = 0;
    	a778335169 = a2027611119[7];
    	a190474899 = (((98 * 5) * 5) + -7254); 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 19);  
    } 
}
 int calculate_outputm4(int input) {
    if((a778335169 == a2027611119[1] && (a1518986556 == 1 &&  cf==1 ))) {
    	cf = 0;
    	if((((20 < a190474899) && (101 >= a190474899)) && ((101 < a190474899 || !(a162289881 == 13)) && !(a162289881 == 8)))) {
    	a1663271343 = 34 ;
    	a778335169 = a2027611119[(a1518986556 + 3)]; 
    	}else {
    	a1056944550 = 36 ;
    	a778335169 = a2027611119[(a1518986556 + 5)];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 15);  
    } 
    if(((input == inputs[4] &&  cf==1 ) && a1518986556 == 1)) {
    	cf = 0;
    	a778335169 = a2027611119[(a1518986556 + a1518986556)];
    	a162289881 = ((a1518986556 * a1518986556) + 9); 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if((a778335169 == a2027611119[1] && (input == inputs[7] &&  cf==1 ))) {
    	cf = 0;
    	a778335169 = a2027611119[(a1518986556 - -4)];
    	a1979864000 = a378180103; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 20);  
    } 
    if(((input == inputs[6] &&  cf==1 ) && a1518986556 == 1)) {
    	cf = 0;
    	a1056944550 = 32 ;
    	a778335169 = a2027611119[(a1518986556 - -2)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((( cf==1  && input == inputs[9]) && a1518986556 == 1)) {
    	cf = 0;
    	if((a162289881 == 13 || a778335169 == 9)) {
    	a778335169 = a2027611119[(a1518986556 - -4)];
    	a1979864000 = a149495938; 
    	}else {
    	a1663271343 = 36 ;
    	a778335169 = a2027611119[((a1518986556 / a1518986556) - -3)];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 24);  
    } 
    if(((a778335169 == a2027611119[1] &&  cf==1 ) && a1518986556 == 1)) {
    	cf = 0;
    	a1663271343 = 35 ;
    	a778335169 = a2027611119[((a1518986556 * a1518986556) + 3)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((( cf==1  && a1518986556 == 1) && input == inputs[8])) {
    	cf = 0;
    	if(( cf==1  && ( cf==1  && !(a778335169 == 5)))) {
    	a778335169 = a2027611119[(a1518986556 + 1)];
    	a162289881 = (a1518986556 - -10); 
    	}else {
    	a162289881 = (a1518986556 - -6);
    	a778335169 = a2027611119[(a162289881 - 5)];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 15);  
    } 
    if((( cf==1  && input == inputs[1]) && a778335169 == a2027611119[1])) {
    	cf = 0;
    	a1056944550 = 36 ;
    	a778335169 = a2027611119[((a1518986556 / a1518986556) - -5)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 23);  
    } 
    if((a778335169 == a2027611119[1] && (a1518986556 == 1 &&  cf==1 ))) {
    	cf = 0;
    	a1056944550 = 35 ;
    	a778335169 = a2027611119[(a1518986556 - -2)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 19);  
    } 
    if((a1518986556 == 1 && ( cf==1  && input == inputs[3]))) {
    	cf = 0;
    	a1056944550 = 33 ;
    	a778335169 = a2027611119[(a1518986556 - -2)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
}
 int calculate_outputm5(int input) {
    if((input == inputs[9] && (a1518986556 == 2 &&  cf==1 ))) {
    	cf = 0;
    	if((16 == a1979864000[5])) {
    	a778335169 = a2027611119[a1518986556];
    	a162289881 = (a1518986556 - -11); 
    	}else {
    	a778335169 = a2027611119[a1518986556];
    	a162289881 = (a1518986556 - -8);}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 20);  
    } 
    if((input == inputs[8] && ( cf==1  && a778335169 == a2027611119[1]))) {
    	cf = 0;
    	if((!(19 == a1979864000[2]) && (a1518986556 == 3 || !(a778335169 == 7)))) {
    	a778335169 = a2027611119[a1518986556];
    	a162289881 = (a1518986556 + 10); 
    	}else {
    	a778335169 = a2027611119[(a1518986556 + 3)];
    	a1979864000 = a753453731;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 21);  
    } 
}
 int calculate_outputm6(int input) {
    if((a1518986556 == 3 && ( cf==1  && a778335169 == a2027611119[1]))) {
    	cf = 0;
    	 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 18);  
    } 
    if((( cf==1  && input == inputs[8]) && a1518986556 == 3)) {
    	cf = 0;
    	if((a162289881 == 7 && ((((20 < a190474899) && (101 >= a190474899)) || a778335169 == a2027611119[4]) || !(a162289881 == 13)))) {
    	a778335169 = a2027611119[(a1518986556 + 4)];
    	a190474899 = (((((14 * 73) / 10) - -18623) * 10) / 9); 
    	}else {
    	a778335169 = a2027611119[(a1518986556 - 3)];
    	a1675980795 = a1071644789;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 20);  
    } 
    if((( cf==1  && input == inputs[6]) && a778335169 == a2027611119[1])) {
    	cf = 0;
    	a1518986556 = 4; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 18);  
    } 
}
 int calculate_outputm7(int input) {
    if((( cf==1  && a1518986556 == 4) && input == inputs[0])) {
    	cf = 0;
    	a778335169 = a2027611119[(a1518986556 + 1)];
    	a1979864000 = a149495938; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 18);  
    } 
}
 int calculate_outputm8(int input) {
    if((( cf==1  && a1518986556 == 6) && a778335169 == a2027611119[1])) {
    	cf = 0;
    	a1663271343 = 35 ;
    	a778335169 = a2027611119[(a1518986556 - 2)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 17);  
    } 
}
 int calculate_outputm9(int input) {
    if((( cf==1  && input == inputs[0]) && a778335169 == a2027611119[1])) {
    	cf = 0;
    	a1663271343 = 34 ;
    	a778335169 = a2027611119[(a1518986556 - 3)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
    if((( cf==1  && a1518986556 == 7) && a778335169 == a2027611119[1])) {
    	cf = 0;
    	a1518986556 = 8; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if((a1518986556 == 7 && ( cf==1  && input == inputs[8]))) {
    	cf = 0;
    	if((((20 < a190474899) && (101 >= a190474899)) || ( cf==1  && (a162289881 == 11 && (16 == a1979864000[5]))))) {
    	a778335169 = a2027611119[(a1518986556 - 2)];
    	a1979864000 = a378180103; 
    	}else {
    	a778335169 = a2027611119[a1518986556];
    	a190474899 = ((((53 - -29575) / 5) + 12342) - 27669);}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 21);  
    } 
}
 int calculate_outputm10(int input) {
    if((( cf==1  && a778335169 == a2027611119[1]) && a1518986556 == 8)) {
    	cf = 0;
    	a1663271343 = 34 ;
    	a778335169 = a2027611119[((a1518986556 + a1518986556) + -12)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
}
 int calculate_outputm11(int input) {
    if((input == inputs[6] && (a778335169 == a2027611119[2] &&  cf==1 ))) {
    	cf = 0;
    	if((a1056944550 == 36 || (a1663271343 == 33 && ((16 == a1979864000[5]) && !(9 == a1979864000[4]))))) {
    	a778335169 = a2027611119[((a162289881 / a162289881) + 4)];
    	a1979864000 = a378180103; 
    	}else {
    	a162289881 = 12;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 19);  
    } 
    if((( cf==1  && a162289881 == 7) && a778335169 == a2027611119[2])) {
    	cf = 0;
    	a1056944550 = 34 ;
    	a778335169 = a2027611119[(a162289881 + -1)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
    if(((a162289881 == 7 &&  cf==1 ) && input == inputs[8])) {
    	cf = 0;
    	a1056944550 = 32 ;
    	a778335169 = a2027611119[((a162289881 * a162289881) - 46)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
}
 int calculate_outputm12(int input) {
    if((input == inputs[6] && ( cf==1  && a162289881 == 10))) {
    	cf = 0;
    	if(a1663271343 == 33) {
    	a778335169 = a2027611119[(a162289881 - 10)];
    	a1675980795 = a1487144088; 
    	}else {
    	a1056944550 = 36 ;
    	a778335169 = a2027611119[(a162289881 + -4)];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 24);  
    } 
}
 int calculate_outputm13(int input) {
    if(((input == inputs[6] &&  cf==1 ) && a778335169 == a2027611119[2])) {
    	cf = 0;
    	a1056944550 = 32 ;
    	a778335169 = a2027611119[(a162289881 - 5)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if(((a162289881 == 11 &&  cf==1 ) && a778335169 == a2027611119[2])) {
    	cf = 0;
    	if(((a778335169 == 5 && !(28 == a1675980795[1])) && (18 == a1675980795[3]))) {
    	a162289881 = 7; 
    	}else {
    	a778335169 = a2027611119[(a162289881 / a162289881)];
    	a1518986556 = ((a162289881 + a162289881) - 21);}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 16);  
    } 
    if((( cf==1  && a162289881 == 11) && input == inputs[4])) {
    	cf = 0;
    	a1518986556 = (a162289881 + -5);
    	a778335169 = a2027611119[(a1518986556 + -5)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if((( cf==1  && a162289881 == 11) && input == inputs[5])) {
    	cf = 0;
    	a1518986556 = ((a162289881 * a162289881) - 117);
    	a778335169 = a2027611119[(a162289881 - 10)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if((a778335169 == a2027611119[2] && (input == inputs[2] &&  cf==1 ))) {
    	cf = 0;
    	a162289881 = 7; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((a778335169 == a2027611119[2] && ( cf==1  && input == inputs[1]))) {
    	cf = 0;
    	if((a1663271343 == 33 && (101 < a190474899 || (!(a1663271343 == 32) && (16 == a1979864000[5]))))) {
    	a1056944550 = 35 ;
    	a778335169 = a2027611119[(a162289881 - 8)]; 
    	}else {
    	a1056944550 = 35 ;
    	a778335169 = a2027611119[(a162289881 - 8)];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 15);  
    } 
    if((input == inputs[3] && (a778335169 == a2027611119[2] &&  cf==1 ))) {
    	cf = 0;
    	a778335169 = a2027611119[(a162289881 - 10)];
    	a1518986556 = (a162289881 - 9); 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((( cf==1  && a162289881 == 11) && a778335169 == a2027611119[2])) {
    	cf = 0;
    	if((28 == a1675980795[1])) {
    	a778335169 = a2027611119[(a162289881 + -4)];
    	a190474899 = ((((4 * 5) * 9) / 10) / 5); 
    	}else {
    	a1056944550 = 33 ;
    	a778335169 = a2027611119[(a162289881 - 8)];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 15);  
    } 
    if((input == inputs[7] && (a778335169 == a2027611119[2] &&  cf==1 ))) {
    	cf = 0;
    	a1056944550 = 33 ;
    	a778335169 = a2027611119[(a162289881 - 5)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
    if(((a778335169 == a2027611119[2] &&  cf==1 ) && input == inputs[0])) {
    	cf = 0;
    	a778335169 = a2027611119[(a162289881 - 11)];
    	a1675980795 = a1071644789; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 18);  
    } 
}
 int calculate_outputm14(int input) {
    if(((a162289881 == 12 &&  cf==1 ) && a778335169 == a2027611119[2])) {
    	cf = 0;
    	a1056944550 = 34 ;
    	a778335169 = a2027611119[(a162289881 - 6)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
}
 int calculate_outputm15(int input) {
    if(((input == inputs[6] &&  cf==1 ) && a778335169 == a2027611119[2])) {
    	cf = 0;
    	if(((a162289881 == 13 || ((101 < a190474899 || (28 == a1675980795[1])) || (18 == a1675980795[3]))) && a1518986556 == 1)) {
    	a778335169 = a2027611119[(a162289881 - 13)];
    	a1675980795 = a1487144088; 
    	}else {
    	a1056944550 = 36 ;
    	a778335169 = a2027611119[((a162289881 - a162289881) - -6)];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 24);  
    } 
}
 int calculate_outputm16(int input) {
    if((a778335169 == a2027611119[2] && ( cf==1  && a162289881 == 14))) {
    	cf = 0;
    	a1056944550 = 33 ;
    	a778335169 = a2027611119[(a162289881 - 8)]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
}
 int calculate_outputm17(int input) {
    if((a778335169 == a2027611119[3] && ( cf==1  && a1056944550 == 33))) {
    	cf = 0;
    	a1663271343 = 32 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
    if((( cf==1  && a1056944550 == 33) && a778335169 == a2027611119[3])) {
    	cf = 0;
    	 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 20);  
    } 
    if((( cf==1  && input == inputs[2]) && a778335169 == a2027611119[3])) {
    	cf = 0;
    	a1056944550 = 32 ;
    	a778335169 = a2027611119[6]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if((( cf==1  && a1056944550 == 33) && input == inputs[3])) {
    	cf = 0;
    	if(((a1056944550 == 35 && (a1518986556 == 2 || (16 == a1979864000[5]))) && !(a162289881 == 13))) {
    	a1056944550 = 36 ;
    	a778335169 = a2027611119[6]; 
    	}else {
    	a1056944550 = 36 ;
    	a778335169 = a2027611119[6];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 26);  
    } 
    if((a778335169 == a2027611119[3] && ( cf==1  && input == inputs[7]))) {
    	cf = 0;
    	if((((a1663271343 == 32 || !(a778335169 == 3)) && a162289881 == 8) && a190474899 <=  -129)) {
    	a778335169 = a2027611119[5];
    	a1979864000 = a753453731; 
    	}else {
    	a778335169 = a2027611119[7];
    	a190474899 = ((((84 * 10) / -6) * 5) - 27665);}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 24);  
    } 
    if((a778335169 == a2027611119[3] && ( cf==1  && a1056944550 == 33))) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 7; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
    if((input == inputs[5] && (a778335169 == a2027611119[3] &&  cf==1 ))) {
    	cf = 0;
    	a1663271343 = 32 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
    if((( cf==1  && input == inputs[8]) && a778335169 == a2027611119[3])) {
    	cf = 0;
    	if((a1056944550 == 32 ||  cf!=1 )) {
    	a1663271343 = 34 ;
    	a778335169 = a2027611119[4]; 
    	}else {
    	a778335169 = a2027611119[7];
    	a190474899 = ((((98 + -8134) - -8110) * 10) / 9);}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 23);  
    } 
    if((a1056944550 == 33 && ( cf==1  && input == inputs[0]))) {
    	cf = 0;
    	a778335169 = a2027611119[2];
    	a162289881 = 7; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((( cf==1  && a778335169 == a2027611119[3]) && a1056944550 == 33)) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 8; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 20);  
    } 
}
 int calculate_outputm18(int input) {
    if((a1056944550 == 32 && ( cf==1  && a778335169 == a2027611119[3]))) {
    	cf = 0;
    	a1056944550 = 34 ;
    	a778335169 = a2027611119[6]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
    if(((a778335169 == a2027611119[3] &&  cf==1 ) && a1056944550 == 32)) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 8; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((input == inputs[5] && (a778335169 == a2027611119[3] &&  cf==1 ))) {
    	cf = 0;
    	a1663271343 = 32 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
}
 int calculate_outputm19(int input) {
    if((( cf==1  && a1056944550 == 34) && a778335169 == a2027611119[3])) {
    	cf = 0;
    	a778335169 = a2027611119[2];
    	a162289881 = 7; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
    if((( cf==1  && a1056944550 == 34) && a778335169 == a2027611119[3])) {
    	cf = 0;
    	a778335169 = a2027611119[0];
    	a1675980795 = a1071644789; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
}
 int calculate_outputm20(int input) {
    if(((a778335169 == a2027611119[3] &&  cf==1 ) && input == inputs[1])) {
    	cf = 0;
    	a778335169 = a2027611119[2];
    	a162289881 = 14; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if((( cf==1  && a778335169 == a2027611119[3]) && input == inputs[3])) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 8; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
}
 int calculate_outputm21(int input) {
    if((a1663271343 == 32 && ( cf==1  && input == inputs[4]))) {
    	cf = 0;
    	 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((( cf==1  && input == inputs[5]) && a1663271343 == 32)) {
    	cf = 0;
    	 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
    if((( cf==1  && input == inputs[6]) && a778335169 == a2027611119[4])) {
    	cf = 0;
    	if((a162289881 == 7 || !(a778335169 == a2027611119[6]))) {
    	a778335169 = a2027611119[5];
    	a1979864000 = a378180103; 
    	}else {
    	a778335169 = a2027611119[2];
    	a162289881 = 12;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 18);  
    } 
}
 int calculate_outputm22(int input) {
    if((( cf==1  && a1663271343 == 34) && a778335169 == a2027611119[4])) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 7; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 23);  
    } 
    if(((a778335169 == a2027611119[4] &&  cf==1 ) && input == inputs[8])) {
    	cf = 0;
    	a778335169 = a2027611119[7];
    	a190474899 = ((((65 / 5) + -27119) / 5) - -5410); 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 20);  
    } 
    if((a778335169 == a2027611119[4] && ( cf==1  && a1663271343 == 34))) {
    	cf = 0;
    	a1056944550 = 34 ;
    	a778335169 = a2027611119[3]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
}
 int calculate_outputm23(int input) {
    if((a1663271343 == 35 && (input == inputs[0] &&  cf==1 ))) {
    	cf = 0;
    	a1056944550 = 35 ;
    	a778335169 = a2027611119[3]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 17);  
    } 
}
 int calculate_outputm24(int input) {
    if((a1663271343 == 36 && ( cf==1  && a778335169 == a2027611119[4]))) {
    	cf = 0;
    	a778335169 = a2027611119[0];
    	a1675980795 = a550880306; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
    if((input == inputs[2] && ( cf==1  && a1663271343 == 36))) {
    	cf = 0;
    	a778335169 = a2027611119[7];
    	a190474899 = ((((69 - -12035) - 12008) + 10732) + -10778); 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((( cf==1  && a1663271343 == 36) && a778335169 == a2027611119[4])) {
    	cf = 0;
    	a1056944550 = 35 ;
    	a778335169 = a2027611119[3]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
    if((input == inputs[4] && ( cf==1  && a1663271343 == 36))) {
    	cf = 0;
    	if((a190474899 <=  -129 || !(a1056944550 == 35))) {
    	a778335169 = a2027611119[1];
    	a1518986556 = 3; 
    	}else {
    	a778335169 = a2027611119[2];
    	a162289881 = 10;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 26);  
    } 
    if(((a778335169 == a2027611119[4] &&  cf==1 ) && input == inputs[3])) {
    	cf = 0;
    	if(((a1056944550 == 32 && !(a1663271343 == 33)) && !(26 == a1675980795[5]))) {
    	a778335169 = a2027611119[2];
    	a162289881 = 12; 
    	}else {
    	a778335169 = a2027611119[5];
    	a1979864000 = a378180103;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 24);  
    } 
    if((a778335169 == a2027611119[4] && ( cf==1  && input == inputs[6]))) {
    	cf = 0;
    	if((a1056944550 == 36 && ( cf!=1  && ((!(a1663271343 == 34) ||  cf==1 ) && !(a1663271343 == 36))))) {
    	a1056944550 = 35 ;
    	a778335169 = a2027611119[3]; 
    	}else {
    	a1056944550 = 32 ;
    	a778335169 = a2027611119[3];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 26);  
    } 
    if((a778335169 == a2027611119[4] && (a1663271343 == 36 &&  cf==1 ))) {
    	cf = 0;
    	a1056944550 = 35 ;
    	a778335169 = a2027611119[3]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 26);  
    } 
    if(((a1663271343 == 36 &&  cf==1 ) && a778335169 == a2027611119[4])) {
    	cf = 0;
    	if(((a1056944550 == 35 || (a778335169 == 4 && ((-129 < a190474899) && (20 >= a190474899)))) && !(26 == a1675980795[5]))) {
    	a778335169 = a2027611119[1];
    	a1518986556 = 3; 
    	}else {
    	a778335169 = a2027611119[1];
    	a1518986556 = 3;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 15);  
    } 
    if(((a778335169 == a2027611119[4] &&  cf==1 ) && a1663271343 == 36)) {
    	cf = 0;
    	if(((!(a1663271343 == 36) || (a1663271343 == 36 || (19 == a1979864000[2]))) && a1056944550 == 35)) {
    	a778335169 = a2027611119[7];
    	a190474899 = ((((94 / 5) * 10) / 1) - -29478); 
    	}else {
    	a778335169 = a2027611119[1];
    	a1518986556 = 8;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 24);  
    } 
    if((( cf==1  && a778335169 == a2027611119[4]) && input == inputs[8])) {
    	cf = 0;
    	a1663271343 = 35 ; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
}
 int calculate_outputm25(int input) {
    if((( cf==1  && a778335169 == a2027611119[5]) && input == inputs[5])) {
    	cf = 0;
    	a1056944550 = 34 ;
    	a778335169 = a2027611119[6]; 
    	 __CPROVER_assert(0, "ERROR_VIOLATION");//    	 klee_assert(0);//printf("%d\n", 15);  
    } 
}
 int calculate_outputm26(int input) {
    if((( cf==1  && input == inputs[8]) && a778335169 == a2027611119[5])) {
    	cf = 0;
    	a1056944550 = 32 ;
    	a778335169 = a2027611119[6]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 23);  
    } 
    if((a778335169 == a2027611119[5] && ( cf==1  && input == inputs[6]))) {
    	cf = 0;
    	a778335169 = a2027611119[7];
    	a190474899 = (((4 - -696) + -9086) + 8478); 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 18);  
    } 
}
 int calculate_outputm27(int input) {
    if((a778335169 == a2027611119[5] && ((19 == a1979864000[2]) &&  cf==1 ))) {
    	cf = 0;
    	a1056944550 = 34 ;
    	a778335169 = a2027611119[6]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
}
 int calculate_outputm28(int input) {
    if((a778335169 == a2027611119[6] && (input == inputs[6] &&  cf==1 ))) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 2; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 23);  
    } 
}
 int calculate_outputm29(int input) {
    if((a778335169 == a2027611119[6] && (a1056944550 == 32 &&  cf==1 ))) {
    	cf = 0;
    	a1056944550 = 33 ; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if(((a778335169 == a2027611119[6] &&  cf==1 ) && a1056944550 == 32)) {
    	cf = 0;
    	a1663271343 = 32 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
    if((( cf==1  && input == inputs[4]) && a1056944550 == 32)) {
    	cf = 0;
    	a778335169 = a2027611119[5];
    	a1979864000 = a149495938; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 18);  
    } 
}
 int calculate_outputm30(int input) {
    if((a778335169 == a2027611119[6] && (input == inputs[8] &&  cf==1 ))) {
    	cf = 0;
    	a1056944550 = 32 ; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
    if((( cf==1  && a1056944550 == 34) && a778335169 == a2027611119[6])) {
    	cf = 0;
    	a1663271343 = 34 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
}
 int calculate_outputm31(int input) {
    if(((a778335169 == a2027611119[6] &&  cf==1 ) && a1056944550 == 35)) {
    	cf = 0;
    	a1056944550 = 33 ;
    	a778335169 = a2027611119[3]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 20);  
    } 
    if(((a778335169 == a2027611119[6] &&  cf==1 ) && input == inputs[4])) {
    	cf = 0;
    	a778335169 = a2027611119[2];
    	a162289881 = 11; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if((a1056944550 == 35 && (a778335169 == a2027611119[6] &&  cf==1 ))) {
    	cf = 0;
    	 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if((a778335169 == a2027611119[6] && ( cf==1  && input == inputs[1]))) {
    	cf = 0;
    	if((!(a1056944550 == 33) || (( cf==1  && !(a1518986556 == 4)) ||  cf!=1 ))) {
    	a1056944550 = 32 ; 
    	}else {
    	a778335169 = a2027611119[3];}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 20);  
    } 
    if((( cf==1  && a778335169 == a2027611119[6]) && a1056944550 == 35)) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 1; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 20);  
    } 
    if((( cf==1  && input == inputs[2]) && a1056944550 == 35)) {
    	cf = 0;
    	if(((a778335169 == a2027611119[7] || a1518986556 == 2) && !(a1663271343 == 32))) {
    	a1056944550 = 34 ;
    	a778335169 = a2027611119[3]; 
    	}else {
    	a778335169 = a2027611119[7];
    	a190474899 = ((((87 + 7901) / 5) * 10) / 9);}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 21);  
    } 
    if((( cf==1  && a1056944550 == 35) && input == inputs[6])) {
    	cf = 0;
    	if((a778335169 == a2027611119[3] || a1518986556 == 1)) {
    	a1056944550 = 32 ; 
    	}else {
    	a1056944550 = 33 ;}
    	//__CPROVER_assert(0, "ERROR_VIOLATION");//    	//klee_assert(0);//printf("%d\n", 20);  
    } 
    if((( cf==1  && a1056944550 == 35) && a778335169 == a2027611119[6])) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 1; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((a1056944550 == 35 && ( cf==1  && input == inputs[9]))) {
    	cf = 0;
    	 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if(((a778335169 == a2027611119[6] &&  cf==1 ) && input == inputs[8])) {
    	cf = 0;
    	a778335169 = a2027611119[0];
    	a1675980795 = a1071644789; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 23);  
    } 
}
 int calculate_outputm32(int input) {
    if(((input == inputs[9] &&  cf==1 ) && a1056944550 == 36)) {
    	cf = 0;
    	 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 24);  
    } 
    if(((a1056944550 == 36 &&  cf==1 ) && input == inputs[8])) {
    	cf = 0;
    	a1663271343 = 32 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
    if((input == inputs[6] && (a1056944550 == 36 &&  cf==1 ))) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 6; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 16);  
    } 
}
 int calculate_outputm33(int input) {
    if((input == inputs[5] && ( cf==1  && a190474899 <=  -129))) {
    	cf = 0;
    	a1056944550 = 34 ;
    	a778335169 = a2027611119[6]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
}
 int calculate_outputm34(int input) {
    if((( cf==1  && a778335169 == a2027611119[7]) && input == inputs[6])) {
    	cf = 0;
    	a1663271343 = 34 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
    if((( cf==1  && input == inputs[5]) && ((-129 < a190474899) && (20 >= a190474899)))) {
    	cf = 0;
    	a1663271343 = 34 ;
    	a778335169 = a2027611119[4]; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 15);  
    } 
    if(((input == inputs[3] &&  cf==1 ) && ((-129 < a190474899) && (20 >= a190474899)))) {
    	cf = 0;
    	a778335169 = a2027611119[5];
    	a1979864000 = a753453731; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 19);  
    } 
}
 int calculate_outputm35(int input) {
    if((a778335169 == a2027611119[7] && ( cf==1  && input == inputs[3]))) {
    	cf = 0;
    	a778335169 = a2027611119[5];
    	a1979864000 = a378180103; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
    if((((20 < a190474899) && (101 >= a190474899)) && ( cf==1  && a778335169 == a2027611119[7]))) {
    	cf = 0;
    	a778335169 = a2027611119[5];
    	a1979864000 = a149495938; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 18);  
    } 
}
 int calculate_outputm36(int input) {
    if((input == inputs[4] && (101 < a190474899 &&  cf==1 ))) {
    	cf = 0;
    	a778335169 = a2027611119[1];
    	a1518986556 = 3; 
    	 //__CPROVER_assert(0, "ERROR_VIOLATION");//    	 //klee_assert(0);//printf("%d\n", 21);  
    } 
}

 int calculate_output(int input) {
        cf = 1;

    if(( cf==1  && a778335169 == a2027611119[0])) {
    	if(( cf==1  && (18 == a1675980795[3]))) {
    		calculate_outputm1(input);
    	} 
    	if(( cf==1  && (26 == a1675980795[5]))) {
    		calculate_outputm2(input);
    	} 
    	if(((28 == a1675980795[1]) &&  cf==1 )) {
    		calculate_outputm3(input);
    	} 
    } 
    if((a778335169 == a2027611119[1] &&  cf==1 )) {
    	if(( cf==1  && a1518986556 == 1)) {
    		calculate_outputm4(input);
    	} 
    	if((a1518986556 == 2 &&  cf==1 )) {
    		calculate_outputm5(input);
    	} 
    	if((a1518986556 == 3 &&  cf==1 )) {
    		calculate_outputm6(input);
    	} 
    	if((a1518986556 == 4 &&  cf==1 )) {
    		calculate_outputm7(input);
    	} 
    	if((a1518986556 == 6 &&  cf==1 )) {
    		calculate_outputm8(input);
    	} 
    	if((a1518986556 == 7 &&  cf==1 )) {
    		calculate_outputm9(input);
    	} 
    	if(( cf==1  && a1518986556 == 8)) {
    		calculate_outputm10(input);
    	} 
    } 
    if(( cf==1  && a778335169 == a2027611119[2])) {
    	if((a162289881 == 7 &&  cf==1 )) {
    		calculate_outputm11(input);
    	} 
    	if((a162289881 == 10 &&  cf==1 )) {
    		calculate_outputm12(input);
    	} 
    	if(( cf==1  && a162289881 == 11)) {
    		calculate_outputm13(input);
    	} 
    	if(( cf==1  && a162289881 == 12)) {
    		calculate_outputm14(input);
    	} 
    	if((a162289881 == 13 &&  cf==1 )) {
    		calculate_outputm15(input);
    	} 
    	if(( cf==1  && a162289881 == 14)) {
    		calculate_outputm16(input);
    	} 
    } 
    if(( cf==1  && a778335169 == a2027611119[3])) {
    	if((a1056944550 == 33 &&  cf==1 )) {
    		calculate_outputm17(input);
    	} 
    	if((a1056944550 == 32 &&  cf==1 )) {
    		calculate_outputm18(input);
    	} 
    	if((a1056944550 == 34 &&  cf==1 )) {
    		calculate_outputm19(input);
    	} 
    	if((a1056944550 == 35 &&  cf==1 )) {
    		calculate_outputm20(input);
    	} 
    } 
    if((a778335169 == a2027611119[4] &&  cf==1 )) {
    	if(( cf==1  && a1663271343 == 32)) {
    		calculate_outputm21(input);
    	} 
    	if(( cf==1  && a1663271343 == 34)) {
    		calculate_outputm22(input);
    	} 
    	if(( cf==1  && a1663271343 == 35)) {
    		calculate_outputm23(input);
    	} 
    	if((a1663271343 == 36 &&  cf==1 )) {
    		calculate_outputm24(input);
    	} 
    } 
    if((a778335169 == a2027611119[5] &&  cf==1 )) {
    	if(( cf==1  && (9 == a1979864000[4]))) {
    		calculate_outputm25(input);
    	} 
    	if(((16 == a1979864000[5]) &&  cf==1 )) {
    		calculate_outputm26(input);
    	} 
    	if(((19 == a1979864000[2]) &&  cf==1 )) {
    		calculate_outputm27(input);
    	} 
    } 
    if((a778335169 == a2027611119[6] &&  cf==1 )) {
    	if(( cf==1  && a1056944550 == 33)) {
    		calculate_outputm28(input);
    	} 
    	if((a1056944550 == 32 &&  cf==1 )) {
    		calculate_outputm29(input);
    	} 
    	if((a1056944550 == 34 &&  cf==1 )) {
    		calculate_outputm30(input);
    	} 
    	if(( cf==1  && a1056944550 == 35)) {
    		calculate_outputm31(input);
    	} 
    	if((a1056944550 == 36 &&  cf==1 )) {
    		calculate_outputm32(input);
    	} 
    } 
    if(( cf==1  && a778335169 == a2027611119[7])) {
    	if((a190474899 <=  -129 &&  cf==1 )) {
    		calculate_outputm33(input);
    	} 
    	if(( cf==1  && ((-129 < a190474899) && (20 >= a190474899)))) {
    		calculate_outputm34(input);
    	} 
    	if((((20 < a190474899) && (101 >= a190474899)) &&  cf==1 )) {
    		calculate_outputm35(input);
    	} 
    	if((101 < a190474899 &&  cf==1 )) {
    		calculate_outputm36(input);
    	} 
    } 


    if( cf==1 ) 
	{
    	//fprintf(stderr, "Invalid input: %d\n", input); 

	}
 }

int main()
{
kappa = 0;
    // main i/o-loop
    int symb;
   for (int FLAG=0;FLAG<BOUND;FLAG++)
    {
    symb = nondet_int(); __CPROVER_input("symb",symb);

        // read input
                

        // operate eca engine
        if((symb != 7) && (symb != 10) && (symb != 8) && (symb != 3) && (symb != 6) && (symb != 1) && (symb != 9) && (symb != 4) && (symb!= 5) && (symb != 2))
          return -2;
         calculate_output(symb);
    }
	return 0;
}
