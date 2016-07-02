/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "m2sxxx.h"
#include <stdio.h>
//#include "measure_m2s150.h"
//#include "m2s150.h"
#include "DBTEngine.h"

#include "platform.h"
#include "ps7_init.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "xil_io.h"



//#include "sniffer.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/*
#ifdef USE_STM32F103_ETT
  #define MESSAGE1   "STM32 Medium Density"
  #define MESSAGE2   " Device running on  "
  #define MESSAGE3   "   STM32F103-ETT    "
#endif
#ifdef USE_SF2_MSS
  #define MESSAGE1   "MicroSemi SmartFusion2"
  #define MESSAGE2   "  Device running on   "
  #define MESSAGE3   "        M2S150        "
#elif
  #define MESSAGE1   "Problem on Device or Board"
  #define MESSAGE2   "   System configuration   "
  #define MESSAGE3   "  not defined correctly   "
#endif
*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private functions ---------------------------------------------------------*/

extern "C"  {
  extern void SER_Init (void);          /* Initialize Serial Interface  */
//  extern void INT_Init (void);          /* Initialize Interrups       	*/
//  extern void SER_RX_IT_Init(void);
//  extern void LED_Init (void);       	/* Initialize LED peripherals 	*/
	}

int S_CODE_LOCATION = 0x60040000;
int S_CODE_SIZE = 32*1024;

//number of loops to write and read the memory in the memory test routine
#define LOOP_COUNT 100



CDBTEngine * globalTeste;

//  int sByteCount;
//  int sInstCount;
//  int tInstCount;
//  int PSWrCounter;

//auxiliary memory latency function
void measure_memory_latency(unsigned int * external_mem_p);



int main(void)
{
//according to main.c from IAR, the initializations take place in the through
//SystemInit() function which is called from startup file (startup_stm32f10x_xx.s)
  //SER_Init ();                                  // STM32 setup


  init_platform();

  ps7_post_config();

  xil_printf("Hello World\n\r");

  /*
	// Write Operation - Code Cache
  for(i=0; i<10; i++)
  	Xil_Out32(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + 4*i, i + 0xaabbccdd);

  xil_printf("Hello World2\n\r");
  // Read Operation - Code Cache
  for(i=0; i<10; i++)
  	xil_printf("value at address %x is %x \n\r", XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + i*4, Xil_In32(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + 4*i));
  */


  fflush(stdin);
  fflush(stdout);
  setbuf(stdout, NULL);


  //printf("\n%s", MESSAGE1);
  //printf("\n%s", MESSAGE2);
  //printf("\n%s\n\n", MESSAGE3);

//  static int a @ "SEC_RAM_8051";
//  printf("a address %x\n", &a);
//  a = 0xFF;
//  printf("a %x\n", a);
//
//  static uint8_t b[16] @ "SEC_RAM_8051";
//
//  for (int iter = 0; iter<=16; iter++)
//  {
//  	b[iter]=iter;
//  }
//
//  for (int iter = 0; iter<=16; iter++)
//  {
//  	printf("b address %x\n", &b[iter]);
//	printf("b %x\n\n", b[iter]);
//  }


//  static uint8_t b[16] @ "SEC_RAM_8051";
//
//  b[0] = 0;
//  b[1] = 1;
//  b[2] = 2;
//
//  uint8_t * var_ptr = &b[2];
//
//  uint8_t var_b = *var_ptr;


//  static unsigned int external_mem[LOOP_COUNT] @ "SEC_RAM_8051";
//  static unsigned int var_for_sniff @ "SEC_RAM_8051";
//
//  static uint8_t byte_4_sniff @ "SEC_RAM_8051";
//
//
//
////  #define BACKDOOR_GET_UINT8_T(x)	 *(uint8_t *)(0x80000 + x)
//
//  	byte_4_sniff = 0xFF;
//  	uint8_t * ptr_a = &byte_4_sniff;
////	*(int*)&ptr_c =   *(int*)&ptr_a & 0x7FFFF;
//	uint8_t * ptr_b = 0x80000 + ptr_a;
//   	uint8_t var_b = *(uint8_t *)ptr_b;
//	uint8_t var_c = BACKDOOR_GET_UINT8_T(&byte_4_sniff);

//  measure_memory_latency(external_mem);

//  printf("writing to LEDs...\n");
//  set_sniffer_leds((uint8_t)0xCC);


////write memory through the normal bus
//  external_mem[0] = 0x00000000;
//  external_mem[1] = 0x44444444;
////read memory through the normal bus
//  printf("addr 0x00000000 %x\n", external_mem[0x0]);
//  printf("addr 0x00000004 %x\n", external_mem[0x1]);
//  printf("addr 0x00000000 %x\n", MEMORY_BACKDOOR_INT(0x00000000));
//  printf("addr 0x00000004 %x\n", MEMORY_BACKDOOR_INT(0x00000001));
//
////write and read using the back-door
//  MEMORY_BACKDOOR_INT(0x2) = 0x88888888;
//  MEMORY_BACKDOOR_INT(0x3) = 0xcccccccc;
////read memory through the normal bus
//  printf("addr 0x00000008 %x\n", MEMORY_BACKDOOR_INT(0x2));
//  printf("addr 0x0000000c %x\n", MEMORY_BACKDOOR_INT(0x3));
//
////mix write
//  external_mem[0x4] = 0x10101010;
//  MEMORY_BACKDOOR_INT(0x5) = 0x14141414;
////mix read
//  printf("addr 0x00000010 %x\n", MEMORY_BACKDOOR_INT(0x4));
//  printf("addr 0x00000014 %x\n", external_mem[0x5]);
//
//  printf("addr 0x00000010 %x\n", external_mem[0x4]);
//  printf("addr 0x00000014 %x\n", MEMORY_BACKDOOR_INT(0x5));
//
//init external interrupt
//  printf("enable external interrup on SW2 and Sniffer Module\n");
//  NVIC_EnableIRQ( FabricIrq0_IRQn );
//
//
//  printf("sniffer_match: %d\n",  get_sniffer_match_list());
//
//  printf("Writting 0xBEEFBEEF to var var_for_sniff\n");
//  var_for_sniff = 0xBEEFBEEF;
//
//  printf("Reading from var_for_sniff: ");
//  tmp_var = var_for_sniff;
//  printf("0x%x\n", tmp_var);
//  printf("Reading from var_for_sniff: ");
//  tmp_var = var_for_sniff;
//  printf("0x%x\n", tmp_var);
//
//  //write FFFFFFFF
//  printf("Writting 0xFFFFFFFF to var var_for_sniff\n");
//  var_for_sniff = 0xFFFFFFFF;
//
//  printf("Reading from var_for_sniff: ");
//  tmp_var = var_for_sniff;
//  printf("0x%x\n", tmp_var);
//
//
//  printf("Reconfig sniff enable\n");
//  sniff_conf.sniff_en = WRITE_EN;
//  set_sniffer_config( &sniff_conf );
//
//  //write FFFFFFFF
//  printf("Writting 0xCCCCCCCC to var var_for_sniff\n");
//  var_for_sniff = 0xCCCCCCCC;
//
//  printf("Reading from var_for_sniff: ");
//  tmp_var = var_for_sniff;
//  printf("0x%x\n", tmp_var);
//
//
//  printf("DISABLE\n");
//  sniff_conf.sniff_en =  DISABLED;
//  set_sniffer_config( &sniff_conf );
//
//  //write FFFFFFFF
//  printf("Writting 0xCCCCCCCC to var var_for_sniff\n");
//  var_for_sniff = 0xDDDDDDDD;
//
//  printf("Reading from var_for_sniff: ");
//  tmp_var = var_for_sniff;
//  printf("0x%x\n", tmp_var);
//
//
//  printf("END OF TEST\n");
//  while(1);

  			//400, 0x2000
  //CDBTEngine teste(0 ,0x2000);	//0x5000 = 20K byte, 0x2800 = 10K bytes
   CDBTEngine teste(0x2000 ,0);	//0x5000 = 20K byte, 0x2800 = 10K bytes

//pass the source code location and size to the init method
//  #pragma section = "S_CODE_SEC"
//  int s_code_size = __section_size("S_CODE_SEC");

  static uint8_t srcCode[13] = {0X94, 5, 0x75, 0x82, 0xb1, 0x75, 0x83, 0x1a, 0x74, 0x20, 0x12, 0x20,
		  	  	  	  	  	  	  	  	  0x68};




  int s_code_size = S_CODE_SIZE;
  SOURCE_MEM_BASE* s_code_base = (SOURCE_MEM_BASE*)S_CODE_LOCATION;

  teste.initTranslator((void *)srcCode,13 ,(int) (srcCode + 10));
  teste.runDBT();



  globalTeste = &teste;

  printf("Starting runDBT now...\n");

  printf("Measurement about to start...\n");


#ifdef MEASURE /*
  configEnable_timer();
  printf("Measurement about to start...\n");
  START_MEASURE();
  teste.runDBT();
  STOP_MEASURE();
  uint32_t upper_cyc, lower_cyc;
  get_cycles_past(&upper_cyc, &lower_cyc);
  unsigned long long cycles_concat = upper_cyc<<16;
  cycles_concat <<= 16;
  cycles_concat |= lower_cyc;
  printf("cycles spent where %llu \n",cycles_concat);
  printf("translation_cycles = %u\n", teste.translation_cycles ); */
#else
  teste.runDBT();
#endif

  cleanup_platform();
  printf("End of Program\n");

  while(1);

  return 0;

}


void measure_memory_latency(unsigned int * external_mem_p)
{
  static unsigned int * external_mem = external_mem_p;
  static unsigned int internal_mem[LOOP_COUNT];


  printf("internal_mem addr %x\n", internal_mem);
  printf("external_mem addr %x\n", external_mem);

  int i;
  uint32_t upper_cyc, lower_cyc;
  volatile int tmp;

  /*
  configEnable_timer();
  START_MEASURE();
  for(i=0; i<=LOOP_COUNT; i++);
  STOP_MEASURE();
  get_cycles_past(&upper_cyc, &lower_cyc);
  printf("%d cycles latency:%d %d\n",LOOP_COUNT, upper_cyc, lower_cyc);
  reset_timer();

 //configEnable_timer();
  START_MEASURE();
  for(i=0; i<=LOOP_COUNT; i++)
  {
  	internal_mem[i]=i;
  }
  STOP_MEASURE();
  get_cycles_past(&upper_cyc, &lower_cyc);
  printf("%d cycles internal write:%d %d\n", LOOP_COUNT, upper_cyc, lower_cyc);
  reset_timer();

  //configEnable_timer();
  START_MEASURE();
  for(i=0; i<=LOOP_COUNT; i++)
  {
    	if( internal_mem[i] != i)
	{
		printf("error on read at address 0x%x\n",i);
		break;
	}
  }
  STOP_MEASURE();
  get_cycles_past(&upper_cyc, &lower_cyc);
  printf("%d cycles internal read:%d %d\n", LOOP_COUNT,upper_cyc, lower_cyc);
  reset_timer();


    START_MEASURE();
  for(i=0; i<=LOOP_COUNT; i++)
  {
  	external_mem[i]=i;
  }
  STOP_MEASURE();
  get_cycles_past(&upper_cyc, &lower_cyc);
  printf("%d cycles external write:%d %d\n", LOOP_COUNT ,upper_cyc, lower_cyc);
  reset_timer();

  //configEnable_timer();
  START_MEASURE();
  for(i=0; i<=LOOP_COUNT; i++)
  {
    	//printf("%d\n", external_mem[i]);
  	if( external_mem[i] != i)
	{
		printf("error on read at address 0x%x\n",i);
		break;
	}
  }
  STOP_MEASURE();
  get_cycles_past(&upper_cyc, &lower_cyc);
  printf("%d cycles external read:%d %d\n", LOOP_COUNT, upper_cyc, lower_cyc);
  reset_timer();

  */

}



