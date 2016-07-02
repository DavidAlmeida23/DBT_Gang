#ifndef TARGET_ARCHITECTURE_H
#define TARGET_ARCHITECTURE_H

//#include "TransTabl.h"
//#include "TransCache.h"
#include "CBuffer.h"
#include "TransBuffer.h"
#include "types.h"
#include <stdio.h>
#include <stddef.h>



//CONDITION FLAGS
#define IT_EQ	0x0
#define IT_NEQ	0x1
#define IT_CS	0x2
#define IT_CC	0x3
#define IT_MI	0x4
#define IT_PL	0x5
#define IT_VS	0x6
#define IT_VC	0x7
#define IT_HI	0x8
#define IT_LS	0x9
#define IT_GE	0xA
#define IT_LT	0xB
#define IT_GT	0xC
#define IT_LE	0xD
#define IT_AL	0xE
#define IT_NV	0xF

//IT BLOCK SEQUENCE
#define IT_TTTT	0x1
#define IT_TTT	0x2
#define IT_TTTE	0x3
#define IT_TT	0x4
#define IT_TTET	0x5
#define IT_TTE	0x6
#define IT_TTEE	0x7
#define IT_T	0x8
#define IT_TETT	0x9
#define IT_TET	0xA
#define IT_TETE	0xB
#define IT_TE	0xC
#define IT_TEET	0xD
#define IT_TEE	0xE
#define IT_TEEE	0xF

//REGISTER SIGN FOR PUSH/POP OPERATIONS
#define LST_R0	0x0001
#define LST_R1	0x0002
#define LST_R2	0x0004
#define LST_R3	0x0008
#define LST_R4	0x0010
#define LST_R5	0x0020
#define LST_R6	0x0040
#define LST_R7	0x0080
#define LST_R8	0x0100
#define LST_R9	0x0200
#define LST_R10	0x0400
#define LST_R11 0x0800
#define LST_R12	0x1000

#define LST_LR	0x4000
#define LST_PC	0x8000


//DIRECT BIT ADDRESSES
#define PAR_POS	0x00
#define F1_POS	0x01
#define OV_POS	0x02
#define RS0_POS	0x03
#define RS1_POS	0x04
#define F0_POS	0x05
#define AC_POS	0x06
#define CY_POS	0x07


#define PAR_BIT	0x01
#define F1_BIT	0x02
#define OV_BIT	0x04
#define RS0_BIT	0x08
#define RS1_BIT	0x10
#define F0_BIT	0x20
#define AC_BIT	0x40
#define CY_BIT	0x80

//#define DEBUG_XMEM_ACCESS()	gen_helper(&CCortexM3::helper_xmem_range)
#define DEBUG_XMEM_ACCESS()

#define SAVE_EXEC_CONTEXT() 	gen_PUSH( LST_MEM_BASE | LST_tReg1 | LST_tReg2 | LST_tReg3 | LST_aReg1 | LST_aReg2 )
#define RESTORE_EXEC_CONTEXT()	gen_POP( LST_MEM_BASE | LST_tReg1 | LST_tReg2 | LST_tReg3 | LST_aReg1 | LST_aReg2 )

typedef struct SourceEnvironment {
	SOURCE_PC PC;
	uint8_t* dataMem;
	uint8_t type;

} SourceEnvironment;



#define SWITCH_TO_EXEC(x)		((void (*)(void))x)()
#define FETCH *(codeCache.baseBufferAddr + (env.PC++))

#define TARGET_CODE_SIZE 0x10000	//64KB

typedef struct lzEvParam{
	uint8_t inputOp1;
	uint8_t inputOp2;
	uint8_t carryIn;
	uint8_t operand;
} lzEvParStruct;


extern void sniffer_config( int * );


class CTargetArchitecture{
  friend class CDBTEngine;

private:
protected:
  CTransBuffer transCache;		//translation cache, to store generated code and know the correspondence of sour/target PC addresses

  SourceEnvironment volatile *env;
  uint8_t *xMem;

public:

  CTargetArchitecture(int Tcache_size);
  ~CTargetArchitecture();

  bool volatile eoExec;
  lzEvParStruct lzParameters;

  void setEnv(SourceEnvironment volatile *envaddr){env=envaddr;}
  void setxMem(uint8_t *xMem){xMem=xMem;}

  virtual void gen_prolog(void) = 0;
  virtual void gen_epilog(void) = 0;

  virtual void gen_helper(void (CTargetArchitecture::*i)(void)) = 0;

  virtual void CC_onDemand_Update(uint8_t op, uint8_t r1, uint8_t r2, uint8_t car) = 0;


  //virtual void gen_helper(void (CDBTEngine::*i)(int), int arg1) = 0;
  //virtual void gen_helper_pcArg(void (CDBTEngine::*i)(int)) = 0;
  //virtual void gen_helper_r4(void (CDBTEngine::*i)(int,int)) = 0;

  virtual void helper_ret(void) = 0;
  virtual void helper_call(void) = 0;
  virtual void helper_xmem_range(void) = 0;
  virtual void helper_CC_lazyEv_SNIFFER_BACKDOOR(void) = 0;
  virtual void helper_DA(void) = 0;
  virtual void helper_debug(int soft_brkp_addr) = 0;
  virtual void gen_helper(void (CTargetArchitecture::*i)(uint8_t, uint8_t, uint8_t, uint8_t), uint8_t op, uint8_t op1, uint8_t op2, uint8_t car) = 0;

  virtual void gen_assemble_lazyEv_param(char operation, uint8_t Op1Reg, uint8_t Op2Reg, uint8_t caryReg) = 0;

  virtual void gen_brkp( uint8_t imm) = 0;
  virtual void gen_blx(uint8_t DReg) = 0;
  virtual void gen_PUSH(uint16_t reg_lst) = 0;
  virtual void gen_POP(uint16_t reg_lst) = 0;
  virtual void gen_cmp(uint8_t SReg1, uint8_t SReg2) = 0;
  virtual void gen_cmpi(uint8_t SReg, uint8_t imm) = 0;
  virtual void gen_it(uint8_t firstcond, uint8_t mask) = 0;
  virtual void gen_cje(uint8_t SReg1, uint8_t SReg2, uint8_t offset) = 0;
  virtual void gen_cjne(uint8_t SReg1, uint8_t SReg2, uint8_t offset) = 0;
  virtual void gen_cjei(uint8_t SReg, uint8_t imm, uint8_t offset) = 0;	//removed AReg
  virtual void gen_cjnei(uint8_t SReg1,  uint8_t imm, uint8_t offset) = 0;	//removed AReg

  virtual void gen_writePC(uint16_t npc) = 0;
  virtual void gen_writePCreg(uint8_t SReg) = 0;

  virtual void gen_mov(uint8_t DReg, uint8_t SReg) = 0;
//	void gen_movi8(uint8_t DReg, uint8_t imm);
//	void gen_movi16(uint8_t DReg, uint16_t imm);
//	void gen_movi32(uint8_t DReg, uint32_t imm);
  virtual void gen_movi(uint8_t DReg, uint32_t imm) = 0;

  virtual void gen_ld8(uint8_t DReg, unsigned int imm) = 0;
  virtual void gen_ld16(uint8_t DReg, unsigned int imm) = 0;
  virtual void gen_ldi8(uint8_t DReg, uint8_t SReg1, uint8_t SReg2) = 0;

  virtual void gen_st8(unsigned int imm, uint8_t SReg) = 0;
  virtual void gen_st16(unsigned int imm, uint8_t SReg) = 0;
  virtual void gen_sti8(uint8_t SReg, uint8_t DReg1, uint8_t DReg2) = 0;

//	void gen_st8_imm_abs(unsigned int addr, uint8_t imm);
//	void gen_st8_abs(unsigned int addr, uint8_t SReg);

  virtual void gen_ld_bit(uint8_t SReg, uint8_t DReg, uint8_t bit_addr) = 0;
  virtual void gen_st_bit(uint8_t SReg, uint8_t DReg, uint8_t bit_addr) = 0;

  virtual void gen_add(uint8_t DReg, uint8_t SReg1, uint8_t SReg2) = 0;
  virtual void gen_addi(uint8_t Reg, uint16_t imm) = 0;
  virtual void gen_sub(uint8_t DReg, uint8_t SReg1, uint8_t SReg2) = 0;
  virtual void gen_subi(uint8_t Reg, uint16_t imm) = 0;

  virtual void gen_div(uint8_t DReg, uint8_t SReg1, uint8_t SReg2) = 0;
  virtual void gen_mul(uint8_t DReg, uint8_t SReg) = 0;
//void gen_rem(uint8_t DReg, uint8_t SReg1, uint8_t SReg2);

  virtual void gen_not(uint8_t DReg, uint8_t SReg) = 0;
  virtual void gen_or(uint8_t DReg, uint8_t SReg) = 0;
  virtual void gen_ori(uint8_t DReg, uint8_t SReg, uint8_t imm) = 0;
  virtual void gen_and(uint8_t DReg, uint8_t SReg) = 0;
  virtual void gen_andi(uint8_t DReg, uint8_t SReg, uint8_t imm) = 0;
  virtual void gen_xor(uint8_t DReg, uint8_t SReg) = 0;

//	void gen_shr(uint8_t DReg, uint8_t SReg1, uint8_t SReg2);
  virtual void gen_shri(uint8_t DReg, uint8_t SReg, uint8_t imm) = 0;
//	void gen_shl(uint8_t DReg, uint8_t SReg1, uint8_t SReg2);
  virtual void gen_shli(uint8_t DReg, uint8_t SReg, uint8_t imm) = 0;

  virtual void gen_orShl(uint8_t SDReg, uint8_t SReg, int Byte) = 0;



};

extern "C" void call_helper_CC_lazyEv_SNIFFER_BACKDOOR();
extern "C" void call_helper_debug(/*CTranslator8051* transPtr,*/ int soft_brkp_addr);

#endif
