#ifndef TYPES_H
#define TYPES_H

// IAR has no namespace std, so advises to define std
//#define std


#include <stdint.h>
#include <stdio.h>
//#include "mallocstats.h"

//#define SOUR_CODE_SIZE 680

#define SOURCE_MEM_BASE uint8_t

#define TARGET_MEM_BASE uint16_t

#define SOURCE_PC uint16_t



//R0 to R3 and R12 are scratch registers: Any function is permitted
// to destroy the contents of a scratch register, without preserving it
//R4 to R11 are Preserved Registers: called functions can use the registers,
// but must save them in advance and restore them before returning.
#define MEM_BASE 4

#define tReg1 	 5	//prev cpuT0  tmpR1
#define tReg2 	 6	//prev cpuT1  tmpR2
#define tReg3 	 7	//prev cpuT2  tmpR3
#define aReg1	 8      //            auxR1
#define aReg2	 9      //            auxR2
//#define cpuCC	 10
//#define cpuCC_LST LST_R10

#define LST_MEM_BASE (1<<MEM_BASE)
#define LST_tReg1 (1<<tReg1)
#define LST_tReg2 (1<<tReg2)
#define LST_tReg3 (1<<tReg3)
#define LST_aReg1 (1<<aReg1)
#define LST_aReg2 (1<<aReg2)

//#define CM3_C 29
//#define CM3_V 28


//if defined MEASURE will configure timer and run measure runDBT() execution in clock cycles.
//#define MEASURE

//printf setting
//if in Measuement mode, no print desired
#ifdef MEASURE
	#define zprintf(...)		//used for debug purposees. if no debug capabilities are desired, uncoment this line and
	#define vzprintf(...)		//verbose debug purposees. if no debug capabilities are desired, uncoment this line and
#else
	#define zprintf printf	//comment this one instead
	#define vzprintf printf	//comment this one instead
	//#define vzprintf(...)

	//if defined will execute some code not necessary to execution
	//(verifications and extra info) that brings unnecessary overhead
	//#define CHECK_MEM_ACCESS

#endif




//to enable/disable include/exclude the file dlmalloc from build
//#define  SHOW_HEAP_STATS()	__iar_dlmalloc_stats() //for heap stats collection
#define SHOW_HEAP_STATS()


#define SourceArch8051 true

//#ifdef SourceArch8051
//	#define SOURCE_ARCH_CONSTRUCTOR	CSourceArch8051()	//source architecture environment conctructor
//#endif

#define TCG_STYLE_GEN true

#define SPECIFIER virtual
#define TRAILING = 0

//OPERATIONS CODE FOR COND CODES LAZY EVALUATION
#define	LZE_UP2DATE	'0'
#define	LZE_ADD_OP	'+'
#define	LZE_ADDC_OP	'@'
#define	LZE_SUBB_OP	'-'



//SHIFT OPERAND
#define SH_BYTE_0	0<<12
#define SH_BYTE_1	2<<12	//shift 8 bits, but since shift operand imm5 is divided in imm3:imm2
#define SH_BYTE_2	4<<12	//this operand is only intended to imm3, and then shifted into position <14:12>
#define SH_BYTE_3	6<<12

//#define ENABLE_CC_MONITORING	  SCB->DFSR = SCB->DFSR; \
				  DWT->FUNCTION0 =  0x5; \
				    printf("ACTIVO\n")
				  //CoreDebug->DEMCR |= (CoreDebug_DEMCR_TRCENA_Msk | CoreDebug_DEMCR_MON_EN_Msk);	\
				  //DWT->FUNCTION0 =  0x5

//#define DISABLE_CC_MONITORING  	  DWT->FUNCTION0 =  0x0;\
				  printf("DESACTIVO\n")
				//SCB->DFSR = SCB->DFSR; \
				//CoreDebug->DEMCR &= ~(CoreDebug_DEMCR_TRCENA_Msk | CoreDebug_DEMCR_MON_EN_Msk); 	\
				//DWT->FUNCTION0 =  0x0

////requires manual CC enabling after being called
//#define CC_MANUAL_UPDATE	helper_CC_lazyEv();\
//				DISABLE_CC_MONITORING
//requires manual CC enabling after being called
//#define CC_MANUAL_UPDATE	helper_CC_lazyEv_SNIFFER_BACKDOOR();\
				DISABLE_CC_MONITORING

//number of bytes required for a jump instruction, used in the cache, as a threshold value
//#define LINK_ARROUND_REQ_BYTES  8

#define EOBB true
#define NO_EOBB false

#define TARGET_NOP 0xBF00
//#define TARGET_JMP


//COM PORT USED IN THE M2S PROJECT
#define COM &g_mss_uart0

#endif
