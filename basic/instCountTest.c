/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This program is for testing "total instructions" stats of KLEE. The
 * first basic block is quite longer than the other two. The "total 
 * instructions" should be counting the longer basic block only once which 
 * does.
 */
#include <klee/klee.h>

void main(void)
{

	unsigned long tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRLexited_BEREIT_FH_TUERMODUL_CTRL=1; 
	unsigned long tm_entered_WIEDERHOLSPERRE_FH_TUERMODUL_CTRL=1; 
	unsigned long   sc_FH_TUERMODUL_CTRL_2375_2=1 ;
	unsigned long   sc_FH_TUERMODUL_CTRL_2352_1=1 ;
	unsigned long   sc_FH_TUERMODUL_CTRL_2329_1=1 ;
	int FH_TUERMODUL_CTRL__N=1;
	int FH_TUERMODUL_CTRL__N_copy=1;
	int FH_TUERMODUL_CTRL__N_old=1;
	unsigned long   sc_FH_TUERMODUL_CTRL_1781_10=1 ;
	unsigned long   sc_FH_TUERMODUL_CTRL_1739_10=1 ;
	float   FH_TUERMODUL__POSITION=1 ;
	float   FH_TUERMODUL__I_EIN=1 ;
	float FH_TUERMODUL__I_EIN_old=1;
	int FH_DU__MFH=1;
	int FH_DU__MFH_copy=1;
	float   FH_DU__POSITION=1 ;
	float   FH_DU__I_EIN=1 ;
	float FH_DU__I_EIN_old=1;
	float BLOCK_ERKENNUNG_CTRL__I_EIN_MAX=1;
	float BLOCK_ERKENNUNG_CTRL__I_EIN_MAX_copy=1;
	int BLOCK_ERKENNUNG_CTRL__N=1;
	int BLOCK_ERKENNUNG_CTRL__N_copy=1;
	int BLOCK_ERKENNUNG_CTRL__N_old=1;
	char FH_TUERMODUL_CTRL__INREVERS2=1;
	char FH_TUERMODUL_CTRL__INREVERS2_copy=1;
	char FH_TUERMODUL_CTRL__INREVERS1=1;
	char FH_TUERMODUL_CTRL__INREVERS1_copy=1;
	char   FH_TUERMODUL_CTRL__FT=1 ;
	char   FH_TUERMODUL__SFHZ_ZENTRAL=1 ;
	char FH_TUERMODUL__SFHZ_ZENTRAL_old=1;
	char   FH_TUERMODUL__SFHZ_MEC =1;
	char FH_TUERMODUL__SFHZ_MEC_old=1;
	char   FH_TUERMODUL__SFHA_ZENTRAL=1 ;
	char FH_TUERMODUL__SFHA_ZENTRAL_old=1;
	char   FH_TUERMODUL__SFHA_MEC=1 ;
	char FH_TUERMODUL__SFHA_MEC_old=1;
	char   FH_TUERMODUL__KL_50=1 ;
	char FH_TUERMODUL__BLOCK=1;
	char FH_TUERMODUL__BLOCK_copy=1;
	char FH_TUERMODUL__BLOCK_old=1;
	char   FH_TUERMODUL__FT=1 ;
	char FH_TUERMODUL__SFHZ=1;
	char FH_TUERMODUL__SFHZ_copy=1;
	char FH_TUERMODUL__SFHZ_old=1;
	char FH_TUERMODUL__SFHA=1;
	char FH_TUERMODUL__SFHA_copy=1;
	char FH_TUERMODUL__SFHA_old=1;
	char FH_TUERMODUL__MFHZ=1;
	char FH_TUERMODUL__MFHZ_copy=1;
	char FH_TUERMODUL__MFHZ_old=1;
	char FH_TUERMODUL__MFHA=1;
	char FH_TUERMODUL__MFHA_copy=1;
	char FH_TUERMODUL__MFHA_old=1;
	char   FH_TUERMODUL__EKS_LEISTE_AKTIV=1 ;
	char FH_TUERMODUL__EKS_LEISTE_AKTIV_old=1;
	char   FH_TUERMODUL__COM_OPEN =1;
	char   FH_TUERMODUL__COM_CLOSE =1;
	char   FH_DU__KL_50 =1;
	char FH_DU__S_FH_FTZU=1;
	char FH_DU__S_FH_FTAUF=1;
	char   FH_DU__FT =1;
	char   FH_DU__EKS_LEISTE_AKTIV =1;
	char FH_DU__EKS_LEISTE_AKTIV_old=1;
	char FH_DU__S_FH_TMBFAUFCAN=1;
	char FH_DU__S_FH_TMBFAUFCAN_copy=1;
	char FH_DU__S_FH_TMBFAUFCAN_old=1;
	char FH_DU__S_FH_TMBFZUCAN=1;
	char FH_DU__S_FH_TMBFZUCAN_copy=1;
	char FH_DU__S_FH_TMBFZUCAN_old=1;
	char   FH_DU__S_FH_TMBFZUDISC =1;
	char FH_DU__S_FH_TMBFZUDISC_old=1;
	char   FH_DU__S_FH_TMBFAUFDISC =1;
	char FH_DU__S_FH_TMBFAUFDISC_old=1;
	char   FH_DU__S_FH_ZUDISC =1;
	char   FH_DU__S_FH_AUFDISC =1;
	char   FH_DU__DOOR_ID =1;
	char FH_DU__BLOCK=1;
	char FH_DU__BLOCK_copy=1;
	char FH_DU__BLOCK_old=1;
	char FH_DU__MFHZ=1;
	char FH_DU__MFHZ_copy=1;
	char FH_DU__MFHZ_old=1;
	char FH_DU__MFHA=1;
	char FH_DU__MFHA_copy;
	char FH_DU__MFHA_old;
	klee_make_symbolic(&FH_DU__MFHA_copy, sizeof(char), "FH_DU__MFHA_copy");

	if (FH_DU__MFHA_copy > 0)
	{
		FH_DU__MFHA_old=1;
	     
	}else{
		FH_DU__MFHA_old=2;
	     
	}  

	 
}
