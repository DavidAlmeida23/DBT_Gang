#include "TargetArch_CortexM3.h"


typedef struct CCparameters {
	uint8_t op;
	uint8_t op1;
	uint8_t op2;
	uint8_t car;
};

CCparameters cc;

CCortexM3::CCortexM3(int Tcache_size)
    :CTargetArchitecture(Tcache_size)
    {
    }

CCortexM3::~CCortexM3(){


}

void CCortexM3::gen_st_bit(uint8_t SReg, uint8_t DReg, uint8_t bit_addr) {
//Suport function to store the bit 0 from Source register to any position at Destination address

// BFI T1 BFI<c> <Rd>,<Rn>,#<lsb>,#<width>

 	uint16_t tmp1, tmp2;

	tmp1 = 0xF360 | SReg ;
	tmp2 = 0x0000 | (bit_addr & 0x1C)<< 10 | DReg<< 8 |  (bit_addr& 0x03)<<6 | bit_addr;

	transCache.cacheCode(tmp1, tmp2);
	vzprintf("BFI R%d, R%d, bit %d\n", DReg, SReg, bit_addr );

}

void CCortexM3::gen_ld_bit(uint8_t SReg, uint8_t DReg, uint8_t bit_addr){
//Suport function to load a bit from his bit addr to a Destination register at position 0
//UBFX T1 UBFX<c> <Rd>,<Rn>,#<lsb>,#<width>

	uint16_t tmp1, tmp2;

	tmp1 = 0xF3C0 | SReg ;
	tmp2 = 0x0000 | (bit_addr&0x1C)<< 10 | DReg << 8 |  (bit_addr& 0x03)<<6 ;	//for width of 1 bit, width-1 = 0

	transCache.cacheCode(tmp1, tmp2);
	vzprintf("UBFX R%d, R%d, bit %d\n", DReg, SReg, bit_addr );

}


/*********** End Support Function **********/


void CCortexM3::gen_helper(void (CTargetArchitecture::*i)(void)){
  	//generates the code for calling a helper function
	//SAVE_EXEC_CONTEXT();

	gen_movi(0, (int)this);
	gen_movi(1, *(int*)((*(int*)(void*)(this)) + (*(int*)(void*)&i)));
	gen_blx(1);

	//RESTORE_EXEC_CONTEXT();
	vzprintf("helper() call1 @0x%p\n", (void*)(this->*i));
	vzprintf("helper() call2 @0x%x\n", *(int*)((*(int*)(void*)(this)) + (*(int*)(void*)&i)));

}

//void gen_helper(void (CCortexM3::*i)(uint8_t, uint8_t, uint8_t, uint8_t), uint8_t op, uint8_t op1, uint8_t op2, uint8_t car);
//void CC_onDemand_Update(uint8_t op, uint8_t r1, uint8_t r2, uint8_t car);

void CCortexM3::gen_helper(void (CTargetArchitecture::*i)(uint8_t, uint8_t, uint8_t, uint8_t), uint8_t op, uint8_t op1, uint8_t op2, uint8_t car ){

	//this->*i

	//void (A::*mfp)() = &A::func;

	printf("address: %d", (void*)(this->*i));
	printf("content: %d", *(int*)((*(int*)(void*)(this)) + (*(int*)(void*)&i)));
	printf("content: %p", *(int*)((*(int*)(void*)(this)) + (*(int*)(void*)&i)));
	//gen_movi(0, (int)this);


//	gen_movi(4, (int)this);
//	gen_ld8(4, *(int*)&i);


	gen_movi(0, (int)this);
	gen_mov(1, (int)op);
	gen_mov(2, (int)op1);
	gen_mov(3, (int)op2);
	gen_PUSH((1<<(int)car));

	gen_movi(aReg1, *(int*)((*(int*)(void*)(this)) + (*(int*)(void*)&i)));
	//gen_ld16(4, *(int*)((*(int*)(void*)(this)) + (*(int*)(void*)&i)));
	gen_blx(aReg1);


	vzprintf("helper() CC @0x%x\n", *(int*)&i);
}

void CCortexM3::CC_onDemand_Update(uint8_t op, uint8_t r1, uint8_t r2, uint8_t car){
	//helper fuction to calculate the condition codes when the PSW e read.
	////this function will be called by the Condition codes handler mechanis
	////it will read the Condition Codes lazy evaluation register (R12) and:
	//// if operation field is 0
	////	-CC are updated, except Parity
	////	-calculae only P33116
	MOVT R0
	////else
	////	-pending condition code update
	////  	-calculate all the Cond Codes
	////	-calculate P


	  	unsigned int res, cout, ac, ov;

	//load the old Condition Codes and Acc from memory
		uint8_t temp_CondCodes = env->dataMem[PSW];
		uint8_t tmpAcc = env->dataMem[A];


	//Odd Parity Calculation
		int cnt = 0;
		vzprintf("\tOld PSW 0x%02x\n", temp_CondCodes);
		vzprintf("\tUpdating PSW on... ");

		for(int i= 0; i<8; i++) {
			cnt ^= tmpAcc & 1;
			tmpAcc >>= 1;
		}

		temp_CondCodes &= ~PAR_BIT;
		temp_CondCodes |= cnt;

		vzprintf("\nLazy Evaluation Operand�: %c\n", op);


		switch ( op )	{
		  //decode the operation:
		case LZE_UP2DATE:	//if the Operation Field is zero means no pending operation, calculate only P
		  	break;
		case LZE_ADD_OP :	//Add operation, calculate C, AC and OV

			res = (unsigned)(r1 + r2);

			cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7
		//	ac = (((uint16_t)res>>4)&0xF != (((uint8_t)lzParameters.inputOp1>>4)&0xF + ((uint8_t)lzParameters.inputOp2>>4)&0xF)) ?	1 : 0;
			ac = ((  (r1&0xF) +  (r2&0xF) ) & 16) >>4 ;

			ov =  (r1&0x80 == r2&0x80) & (r1&0x80 != res&0x80)  ;
			temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
			temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update

			op = '0';	//clean the pending operation

			vzprintf(", CY, AC, OV\n");
			vzprintf("\tADD op1 0x%02x, op2 0x%02x, res 0x%02x\n", r1, r2, res);
			vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);

		  	break;
		case LZE_ADDC_OP :	//Add Carry operation, calculate C, AC and OV

		  	res = (unsigned)(r1 + r2 + car);

			cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7

			zprintf("res %x\n", (((uint16_t)res>>4)&0xF));
			zprintf("op1 %x\n", (r1>>4)&0xF);
			zprintf("op2 %x\n", (r2>>4)&0xF);
			zprintf("carry %x\n", (car) );
			//ac =  (((uint16_t)res>>4)&0xF) != (  (((uint8_t)lzParameters.inputOp1>>4)&0xF) +  (((uint8_t)lzParameters.inputOp2>>4)&0xF) + (uint8_t)lzParameters.carryIn ) ?  1 : 0;
			ac = ((  (r1&0xF) +  (r2&0xF) + car ) & 16) >>4 ;

			zprintf("new AC %d\n", ac);

			ov =  (r1&0x80 ==r2&0x80) & (r1&0x80 != res&0x80) 	;

			temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
			temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update

			op = '0';	//clean the pending operation

			vzprintf(", CY, AC, OV\n");
			vzprintf("\tADDC op1 0x%02x, op2 0x%02x, cin %x, res 0x%02x\n", r1, r2, car, res);
			vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);

		  	break;
		case LZE_SUBB_OP :	//Sub with borrow operation, calculate C, AC and OV

		  	res = (unsigned)(r1 - r2 - car);

			cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7
			//ac = ((uint16_t)res>>4)&0xF != (((uint8_t)lzParameters.inputOp1>>4)&0xF - ((uint8_t)lzParameters.inputOp2>>4)&0xF - ((uint8_t)lzParameters.carryIn)) ?	1 : 0;
			ac = ((  ((r1)&0xF) -  ((r2)&0xF) - car ) & 16) >>4 ;

			ov =  (r1&0x80 != r2&0x80) & (r1&0x80 != res&0x80)  ;

			temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
			temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update

			op = '0';	//clean the pending operation

			vzprintf(", CY, AC, OV\n");
			vzprintf("\tSUBB op1 0x%02x, op2 0x%02x, cin %x, res 0x%02x\n", r1, r2, car, res);
			vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);

			break;
		default:
		  	vzprintf("\nLazy Evaluation Parameters corrupted %c!!!!!!!\n", op);
			break;
		}

		env->dataMem[PSW] = temp_CondCodes;

		vzprintf("\n\tNew PSW 0x%02x\n", temp_CondCodes);
}

//void CCortexM3::gen_helper(void (CDBTEngine::*i)(int), int arg1){
//  	//generates the code for calling a helper function
//
//	//doesn need to save context because execution uses only preserved registers
//  	//that are preserved by the compiler
//
//	gen_movi(0, (int)this);	//must put in R0 class head addr
//	gen_movi(1, arg1);		//argument 1
//	gen_movi(2, *(int*)&i);	//method's address to be called
//
//	gen_blx(2);
//
//	vzprintf("helper() call @0x%x, arg = 0x%x\n", *(int*)&i, arg1);
//}
//
//void CCortexM3::gen_helper_pcArg(void (CDBTEngine::*i)(int)){
//  	//generates the code for calling a helper function
//	//SAVE_EXEC_CONTEXT();
//
//	gen_movi(0, (int)this);
//	gen_mov(1, 15);
//	gen_movi(2, *(int*)&i);
//	gen_blx(2);
//
//	//RESTORE_EXEC_CONTEXT();
//
//	vzprintf("helper() call @0x%x\n", *(int*)&i);
//
//}
//
//void CCortexM3::gen_helper_r4(void (CDBTEngine::*i)(int, int)){
//  	//generates the code for calling a helper function
//	//SAVE_EXEC_CONTEXT();
//
//	gen_movi(0, (int)this);	//must put in R0 class head addr
//	gen_mov(1, 15);		//argument 1
//	gen_mov(2, 4);		//move register 4 to input parameter 2
//	gen_movi(3, *(int*)&i);	//method's address to be called
//
//	gen_blx(3);
//
//	//RESTORE_EXEC_CONTEXT();
//
//	vzprintf("helper() call @0x%x", *(int*)&i);
//
//}

void CCortexM3::gen_blx(uint8_t DReg){
 //BLX (register) T1 BLX<c> <Rm>

	transCache.cacheCode( 0x4780 | (DReg << 3) );

	vzprintf("BLX R%d\n", DReg);
}


void CCortexM3::gen_mov(uint8_t DReg, uint8_t SReg){
//////MOV (register) T1 MOV<c> <Rd>,<Rm>
//
  	uint16_t tmp = 0x4600;

 	tmp |= SReg << 3;
	tmp |= DReg & 0x7;
	tmp |= (DReg & 0x8) << 4;
//	transCache.cacheCode( TARGET_NOP );	//NOP instruction

	transCache.cacheCode(tmp);


	vzprintf("MOV R%d, R%d\n", DReg, SReg );


////T3 MOV{S}<c>.W <Rd>,<Rm>
//
//  	uint16_t tmp1, tmp2;
//
//	tmp1 = 0xEA4F;
//	tmp2 = 0x0000 | (DReg << 8) | (SReg);
//
//	transCache.cacheCode(tmp1, tmp2);
//
//	vzprintf("MOV R%d, R%d\n", DReg, SReg );
}


void CCortexM3::gen_prolog(void){
//// PUSH T1 PUSH<c> <registers>
//
//  //PUSH {LR | REG_LST}
//  	transCache.cacheCode( 0xB500);
//  //PUSH { REG_LST}
//  	transCache.cacheCode( 0xB400 | LST_R0 ...);
///////////////////////////////////////////////////////////
//  //prolog V2 - must restore the saved r3, r4 and r5 for lazy condition of the codes evaluation
//  //		and save LR to stack
//
//  //POP { REG_LST (no PC)}
//	transCache.cacheCode( 0xBC00 | LST_R4 | LST_R5 | LST_R6 );
//  //PUSH {LR }
//  	transCache.cacheCode( 0xB500);
//////////////////////////////////////////////////////////

  //PUSH {LR | REG_LST}
  	//save return address and all the working registers (preserved registers) to the stack
	gen_PUSH( LST_LR | LST_MEM_BASE | LST_tReg1 | LST_tReg2 | LST_tReg3 | LST_aReg1 | LST_aReg2 );
	// transfer parameter from R0 (env->dataMem address) to MEM_BASE register
	gen_mov( MEM_BASE, 0);

}

void CCortexM3::gen_epilog(void){
////POP T1 POP<c> <registers>
//
////POP {PC | REG_LST}
//	transCache.cacheCode( 0xBD00 );
////POP {REG_LST}
//	transCache.cacheCode( 0xBC00 | LST_R0 ... );
//BX T1 BX<c> <Rm>
//	transCache.cacheCode( 0x4700 | (REG<<3) );
////////////////////////////////////////////////////////////
//  //epilog V2 - LR value is restored from stack to LR,
//  //		r3, r4 and r5 are puched for lazy condition of the codes evaluation
//  //		branch to LR address
//
// 	transCache.cacheCode( 0xBC00 | LST_R0 );	//pop LR to R0
//
//	transCache.cacheCode( 0xB400 | LST_R4 | LST_R5 | LST_R6 );	//push r3, r4 and r5
//
//	transCache.cacheCode( 0x4700 );		//branch to LR value (stored in R0)
///////////////////////////////////////////////////////////////


  ////POP {PC | REG_LST}
	//restore all the preserved registers from th stack and return to the saved ink Register
  	gen_POP( LST_PC | LST_MEM_BASE | LST_tReg1 | LST_tReg2 | LST_tReg3 | LST_aReg1 | LST_aReg2 );

}


//void CCortexM3::gen_assemble_lazyEv_reg(int operation, uint8_t Op1, uint8_t Op2, uint8_t carry){
//
//
//  	gen_movi(cpuCC, operation);		//store the type of operation, with ZeroExtend to 32 bit
//
//	gen_orShl(cpuCC, Op1, SH_BYTE_1);	//save Op1 in [15:8]
//
//	gen_orShl(cpuCC, Op2, SH_BYTE_2);	//save Op2 in [23:16]
//
//	gen_orShl(cpuCC, carry, SH_BYTE_3);	//save carry in [31:24]
//
//	vzprintf("\tLazy Ev for\n\t\texp: %c\n\t\top1: %d\n\t\top2: %d\n\t\tc: %d\n", operation, Op1, Op2, carry);
//}

void CCortexM3::gen_assemble_lazyEv_param(char operation, uint8_t Op1Reg, uint8_t Op2Reg, uint8_t caryReg){
// STRB (immediate) T1 STRB<c> <Rt>,[<Rn>,#<imm>]

//  	uint16_t tmp1 = 0x7000;
//	uint16_t tmp2;
//
//	gen_movi(aReg1, (unsigned int)& lzParameters );	//move the base structure address to auxReg1
//
//	tmp2 = ( offsetof(lzEvParStruct, inputOp1) << 6 ) | (aReg1 << 3) | Op1Reg ;
//	transCache.cacheCode(tmp1 | tmp2);
//	vzprintf("STRB R%d,[R%d, #%d]\n", Op1Reg, aReg1, ( offsetof(lzEvParStruct, inputOp1)<< 6 ));
//
//	tmp2 = ( offsetof(lzEvParStruct, inputOp2)<< 6 ) | (aReg1 << 3) | Op2Reg ;
//	transCache.cacheCode(tmp1 | tmp2);
//	vzprintf("STRB R%d,[R%d, #%d]\n", Op2Reg, aReg1, ( offsetof(lzEvParStruct, inputOp2)<< 6 ));
//
//	tmp2 = ( offsetof(lzEvParStruct, carryIn)<< 6 ) | (aReg1 << 3) | caryReg ;
//	transCache.cacheCode(tmp1 | tmp2);
//	vzprintf("STRB R%d,[R%d, #%d]\n", caryReg, aReg1, ( offsetof(lzEvParStruct, carryIn)<< 6 ));
//
//	gen_movi(aReg2, (unsigned)operation);
//	tmp2 = ( offsetof(lzEvParStruct, operand)<< 6 ) | (aReg1 << 3) | aReg2 ;
//	transCache.cacheCode(tmp1 | tmp2);
//	vzprintf("STRB R%d,[R%d, #%d]\n", aReg2, aReg1, ( offsetof(lzEvParStruct, operand)<< 6 ));

  //T2 STRB<c>.W <Rt,[<Rn>,#<imm12>]

    	uint16_t tmp1;
	uint16_t tmp2;

	gen_movi(aReg1, (unsigned int)& lzParameters );	//move the base structure address to auxReg1
	tmp1 = 0xF880 | aReg1;

	vzprintf("addr 1 %x addr 2 %x\n",&( lzParameters.inputOp1), &( lzParameters.inputOp2));
	tmp2 = ( offsetof(lzEvParStruct, inputOp1)) | Op1Reg << 12;
	transCache.cacheCode(tmp1, tmp2);
	vzprintf("STRBW R%d,[R%d, #%d]\n", Op1Reg, aReg1, offsetof(lzEvParStruct, inputOp1));

	tmp2 = ( offsetof(lzEvParStruct, inputOp2)) | Op2Reg << 12;
	transCache.cacheCode(tmp1, tmp2);
	vzprintf("STRBW R%d,[R%d, #%d]\n", Op2Reg, aReg1, offsetof(lzEvParStruct, inputOp2));

	tmp2 = ( offsetof(lzEvParStruct, carryIn)) | caryReg << 12;
	transCache.cacheCode(tmp1, tmp2);
	vzprintf("STRBW R%d,[R%d, #%d]\n", caryReg, aReg1, offsetof(lzEvParStruct, carryIn));

	gen_movi(aReg2, (unsigned)operation);
	tmp2 = ( offsetof(lzEvParStruct, operand)) | aReg2 << 12;
	transCache.cacheCode(tmp1, tmp2);
	vzprintf("STRBW R%d,[R%d, #%d]\n", aReg2, aReg1, offsetof(lzEvParStruct, operand));
	vzprintf("OPERAND char:%c, int:%d\n", operation, operation);

}

//void CCortexM3::gen_st8_abs(unsigned int addr, uint8_t SReg){
//// //STRH (immediate) T1 STRH<c> <Rt>,[<Rn>,#<imm>]
////
////  	uint16_t tmp;
////
////	gen_movi(aReg1, addr );
////
////	tmp = 0x8000 | (aReg1 << 3) | SReg ;
////
////	transCache.cacheCode(tmp);
////
////	vzprintf("STRH R%d,[R%d, #%d]\n", SReg, aReg1, 0);
//
// //STRH (immediate) T2 STRH<c>.W <Rt,[<Rn>,#<imm12>]
//
//  	uint16_t tmp1, tmp2;
//
//	gen_movi(aReg1, addr );
//
//	tmp1 = 0xF8A0 | aReg1;
//	tmp2 = 0x0000 | SReg<<12;
//
//	transCache.cacheCode(tmp1, tmp2);
//
//	vzprintf("STRH R%d,[R%d, #%d]\n", SReg, aReg1, 0);
//}

//void CCortexM3::gen_st8_imm_abs(unsigned int addr, uint8_t imm){
// //STRH (immediate) T1 STRH<c> <Rt>,[<Rn>,#<imm>]
//  	uint16_t tmp;
//
//	gen_movi(aReg1, imm);
//	gen_movi(aReg2, addr );
//
//	tmp = 0x8000 | (aReg2 << 3) | aReg1 ;
//
//	transCache.cacheCode(tmp);
//
//	vzprintf("STRH R%d,[R%d, #%d]\n", aReg1, aReg2, 0);
//
//}

void CCortexM3::gen_orShl(uint8_t SDReg, uint8_t SReg, int Byte){
//ORR (register) T2 ORR{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}

	uint16_t tmp1, tmp2;

	tmp1 = 0xEA40 | SDReg ;

	tmp2 = 0x0000 | Byte | (SDReg << 8) | SReg ;

	transCache.cacheCode(tmp1, tmp2);

	vzprintf("ORR R%d, R%d, R%d<<%d\n", SDReg, SReg, SDReg, Byte>>10);

}


void CCortexM3::gen_PUSH(uint16_t reg_lst){
  //PUSH T2 PUSH<c>.W <registers>

  	transCache.cacheCode( 0xE92D , reg_lst );

	vzprintf("PUSH {");
	vzprintf("%s", (reg_lst&0x0001) ? "R0, " : "");
	vzprintf("%s", (reg_lst&0x0002) ? "R1, " : "");
	vzprintf("%s", (reg_lst&0x0004) ? "R2, " : "");
	vzprintf("%s", (reg_lst&0x0008) ? "R3, " : "");
	vzprintf("%s", (reg_lst&0x0010) ? "R4, " : "");
	vzprintf("%s", (reg_lst&0x0020) ? "R5, " : "");
	vzprintf("%s", (reg_lst&0x0040) ? "R6, " : "");
	vzprintf("%s", (reg_lst&0x0080) ? "R7, " : "");

	vzprintf("%s", (reg_lst&0x0100) ? "R8, " : "");
	vzprintf("%s", (reg_lst&0x0200) ? "R9, " : "");
	vzprintf("%s", (reg_lst&0x0400) ? "R10, " : "");
	vzprintf("%s", (reg_lst&0x0800) ? "R11, " : "");
	vzprintf("%s", (reg_lst&0x1000) ? "R12, " : "");
	vzprintf("%s", (reg_lst&0x4000) ? "LR, " : "");

	vzprintf("}\n");

}

void CCortexM3::gen_POP(uint16_t reg_lst){
  //PUSH T2 POP<c>.W <registers>

  	transCache.cacheCode( 0xE8BD , reg_lst );

	vzprintf("POP {");
	vzprintf("%s", (reg_lst&0x0001) ? "R0, " : "");
	vzprintf("%s", (reg_lst&0x0002) ? "R1, " : "");
	vzprintf("%s", (reg_lst&0x0004) ? "R2, " : "");
	vzprintf("%s", (reg_lst&0x0008) ? "R3, " : "");
	vzprintf("%s", (reg_lst&0x0010) ? "R4, " : "");
	vzprintf("%s", (reg_lst&0x0020) ? "R5, " : "");
	vzprintf("%s", (reg_lst&0x0040) ? "R6, " : "");
	vzprintf("%s", (reg_lst&0x0080) ? "R7, " : "");

	vzprintf("%s", (reg_lst&0x0100) ? "R8, " : "");
	vzprintf("%s", (reg_lst&0x0200) ? "R9, " : "");
	vzprintf("%s", (reg_lst&0x0400) ? "R10, " : "");
	vzprintf("%s", (reg_lst&0x0800) ? "R11, " : "");
	vzprintf("%s", (reg_lst&0x1000) ? "R12, " : "");
	vzprintf("%s", (reg_lst&0x4000) ? "LR, " : "");
	vzprintf("%s", (reg_lst&0x8000) ? "PC, " : "");

	vzprintf("}\n");

}


void CCortexM3::gen_cmp(uint8_t SReg1, uint8_t SReg2){
// //CMP (register) T1 CMP<c> <Rn>,<Rm>
//
//  	uint16_t tmp = (SReg2 << 3) |  SReg1 | 0x4280;
//
//	transCache.cacheCode(tmp);
//
//	vzprintf("CMP R%d, R%d\n", SReg1, SReg2);

 //CMP (register) T3 CMP<c>.W <Rn>, <Rm> {,<shift>}

  	uint16_t tmp1, tmp2;

	tmp1 = 0xEBB0 | SReg1;
	tmp2 = 0x0F00 | SReg2;

	transCache.cacheCode(tmp1, tmp2);

	vzprintf("CMP R%d, R%d\n", SReg1, SReg2);

}

void CCortexM3::gen_cmpi(uint8_t SReg, uint8_t imm){
// //CMP (immediate) T1 CMP <Rn>,#<imm8>
//
//  	uint16_t tmp = 0x2800 | (SReg << 8) |  imm ;
//
//	transCache.cacheCode(tmp);
//
//	vzprintf("CMP R%d, #%d\n", SReg, imm);

 //CMP (immediate) T2 CMP<c>.W <Rn>,#<const>

  	uint16_t tmp1, tmp2;

	tmp1 = 0xF1B0 | SReg;
	tmp2 = 0x0F00 | imm;

	transCache.cacheCode(tmp1, tmp2);

	vzprintf("CMP R%d, #%d\n", SReg, imm);
}

void CCortexM3::gen_it(uint8_t firstcond, uint8_t mask){
//IT T1 IT{x{y{z}}} <firstcond>

  	uint16_t tmp;
  	//mask |= (firstcond << 4);

	tmp = 0xBF00 | mask | (firstcond << 4);

//	transCache.cacheByte( mask );
//	transCache.cacheByte( 0xBF);

	transCache.cacheCode(tmp);

	vzprintf("IT %d\n", firstcond );
}

void CCortexM3::gen_cjne(uint8_t SReg1, uint8_t SReg2, uint8_t offset){

	int npc;

	//sign extension for 8bit offset
	npc = ((offset&0x80)==0) ? offset : offset | 0xFFFFFF00;

	npc += env->PC;

	gen_cmp(SReg1, SReg2); // compare
	gen_it(IT_NEQ,IT_TEEE); // Generate If-Then NOT EQUAL

	gen_writePC(npc);
}

void CCortexM3::gen_cje(uint8_t SReg1, uint8_t SReg2, uint8_t offset){

	int npc;

	//sign extension for 8bit offset
	npc = ((offset&0x80)==0) ? offset : offset | 0xFFFFFF00;

	npc += env->PC;

	gen_cmp(SReg1, SReg2); // compare
	gen_it(IT_EQ,IT_TTTT); 	// Generate If-Then EQUAL

	gen_writePC(npc);	// gen jump instruction if EQUAL

}


void CCortexM3::gen_cjnei(uint8_t SReg, uint8_t imm, uint8_t offset){

 	int npc;

	npc = (int8_t)offset;

	gen_cmpi(SReg, imm); // compare
	gen_movi(SReg, env->PC);
	gen_movi(aReg1, npc );
	gen_it(IT_NEQ,IT_T); 	// Generate If-Then EQUAL
		gen_add(SReg, aReg1, SReg);	//THEN

	gen_writePCreg(SReg);	// gen jump instruction if EQUAL
}

void CCortexM3::gen_cjei(uint8_t SReg,uint8_t imm, uint8_t offset){

	int npc;

	//sign extension for 8bit offset
//	npc = ((offset&0x80)==0) ? offset : offset | 0xFFFFFF00;
	npc = (int8_t)offset;

	gen_cmpi(SReg, imm); // compare
	gen_movi(SReg, env->PC);
	gen_movi(aReg1, npc );
	gen_it(IT_EQ,IT_T); 	// Generate If-Then EQUAL
		gen_add(SReg, aReg1, SReg);	//THEN

	gen_writePCreg(SReg);	// gen jump instruction if EQUAL

}


//void CCortexM3::gen_movi8(uint8_t DReg, uint8_t imm){
//
////MOV(immediate) T1 MOVS <Rd>,#<imm8>
//
//  	uint16_t tmp1 = (uint16_t)((0x20 | (DReg&0x7))<< 8) | (uint16_t)imm;
//	transCache.cacheCode(tmp1);
//
//	vzprintf("MOVS R%d,#%d\n", DReg, imm);
//
//}

//void CCortexM3::gen_movi16(uint8_t DReg, uint16_t imm){
//
////MOV(immediate) T3 MOVW<c> <Rd>,#<imm16>
//
//  	uint16_t tmp1, tmp2;
//
//	tmp1 = (imm & 0xFF) | (DReg << 8) | ((imm & 0x700)<<4);
//	tmp2 = ((imm & 0x800) == 0) ?	0xF240 : 0xF640 ;
//	tmp2 |= (imm >> 12);
//
//	transCache.cacheCode(tmp2, tmp1);
//
//	vzprintf("MOVW R%d,#%d\n", DReg, imm);
//
//}

//void CCortexM3::gen_movi32(uint8_t DReg, uint32_t imm){
//
// //MOV(immediate) T3 MOVW <Rd>,#<imm16>
// //+
// //MOVT T1 MOVT<c> <Rd>,#<imm16>
//
//  	uint16_t tmp1, tmp2;
//	uint16_t half_imm = (uint16_t)imm;
//
//	tmp1 = (half_imm & 0xFF) | (DReg << 8) | ((half_imm & 0x700)<<4);
//	tmp2 = ((half_imm & 0x800) == 0) ?	0xF240 : 0xF640 ;
//	tmp2 |= (half_imm >> 12);
//
//	transCache.cacheCode(tmp2, tmp1);
//	vzprintf("MOVW R%d,#%d\n", DReg, half_imm);
//
//
//	half_imm = imm >> 16;
//
//	tmp1 = (half_imm & 0xFF) | (DReg << 8) | ((half_imm & 0x700)<<4);
//	tmp2 = ((half_imm & 0x800) == 0) ?	0xF2C0 : 0xF6C0 ;
//	tmp2 |= (half_imm >> 12);
//
//	transCache.cacheCode(tmp2, tmp1);
//	vzprintf("MOVT R%d,#%d\n", DReg, half_imm);
//
//}

void CCortexM3::gen_movi(uint8_t DReg, uint32_t imm){

 //MOV(immediate) T3 MOVW <Rd>,#<imm16>
 //+
 //MOVT T1 MOVT<c> <Rd>,#<imm16>

  	uint16_t tmp1, tmp2;
	uint16_t half_imm = (uint16_t)imm;

	tmp1 = (half_imm & 0xFF) | (DReg << 8) | ((half_imm & 0x700)<<4);
	tmp2 = ((half_imm & 0x800) == 0) ?	0xF240 : 0xF640 ;
	tmp2 |= (half_imm >> 12);

	transCache.cacheCode(tmp2, tmp1);
	vzprintf("MOVW R%d,#%d\n", DReg, half_imm);

	half_imm = imm >> 16;

	if ( half_imm ) {	//if immediate bigger that 16 bit, then use second part of instruction

	    tmp1 = (half_imm & 0xFF) | (DReg << 8) | ((half_imm & 0x700)<<4);
	    tmp2 = ((half_imm & 0x800) == 0) ?	0xF2C0 : 0xF6C0 ;
	    tmp2 |= (half_imm >> 12);

	    transCache.cacheCode(tmp2, tmp1);
	    vzprintf("MOVT R%d,#%d\n", DReg, half_imm);
	}
}

void CCortexM3::gen_not(uint8_t DReg, uint8_t SReg){
//// MVN (register) T1 MVNS <Rd>,<Rm>
//
//  uint16_t tmp = 0x43C0 | (SReg << 3) | DReg ;
//
//
//  	transCache.cacheCode(tmp);
//
//	vzprintf("MVNS R%d, R%d\n", DReg, SReg);

// MVN (register) T2 MVN{S}<c>.W <Rd>,<Rm>{,shift>}

 	uint16_t tmp1, tmp2;

	tmp1 = 0xEA6F;
	tmp2 = (DReg << 8) | SReg;

  	transCache.cacheCode(tmp1, tmp2);

	vzprintf("MVNS R%d, R%d\n", DReg, SReg);
}
void CCortexM3::gen_sub(uint8_t DReg, uint8_t SReg1, uint8_t SReg2){
////SUB (register) T1 SUBS <Rd>,<Rn>,<Rm>
//
// 	uint16_t tmp = 0x1A00 | (SReg2 << 6) | (SReg1 << 3) | DReg ;
//
//	transCache.cacheCode(tmp );
//
//	vzprintf("SUBS R%d, R%d, R%d\n", DReg, SReg1, SReg2);

//SUB (register) T2 SUB{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}

 	uint16_t tmp1, tmp2;

	tmp1 = 0xEBA0 | SReg1;
	tmp2 = (DReg<< 8) | SReg2;


	transCache.cacheCode(tmp1, tmp2 );

	vzprintf("SUBS R%d, R%d, R%d\n", DReg, SReg1, SReg2);
}
void CCortexM3::gen_subi(uint8_t Reg, uint16_t imm){
//SUB (immediate) T4 SUBW<c> <Rd>,<Rn>,#<imm12>

  	if(imm > 4095 )	//4095 is the biggest number with 12 bit
	{
		zprintf("immediate exceed range in \"gen_subi\" micro-Op\n");
		eoExec = 1;
		return;
	}

  	uint16_t tmp1, tmp2;

	tmp1 = imm & 0xFF;
	tmp1 |= (imm<<4)& 0x7000;
	tmp1 |= Reg << 8;

	tmp2 = Reg;
	tmp2 |= (imm < 0x800) ?	0xF2A0	:
	  			0xF6A0	;

	transCache.cacheCode(tmp2, tmp1);

	vzprintf("SUBW R%d, R%d, #%d\n",Reg, Reg, imm);



}
void CCortexM3::gen_div(uint8_t DReg, uint8_t SReg1, uint8_t SReg2){
//UDIV UDIV<c> <Rd>,<Rn>,<Rm>

	uint16_t tmp1, tmp2;

	tmp1 = 0xF0F0 | (DReg << 8) | SReg2 ;
	tmp2 = 0xFBB0 | SReg1 ;

	transCache.cacheCode( tmp2, tmp1 );

	vzprintf("UDIV R%d, R%d, R%d\n", DReg, SReg1, SReg2 );
}
void CCortexM3::gen_mul(uint8_t DReg, uint8_t SReg){
//  // MUL T1 MULS <Rdm>,<Rn>,<Rdm>
//
//  	uint16_t tmp = 0x4340 | (SReg << 3) | DReg;
//	transCache.cacheCode( tmp );
//
//	vzprintf("MULS R%d, R%d, R%d\n", DReg, SReg, DReg );

  // MUL T2 MUL<c> <Rd>,<Rn>,<Rm>

  	uint16_t tmp1, tmp2;

	tmp1 = 0xFB00 | SReg;
	tmp2 = 0xF000 | (DReg << 8) | DReg;

	transCache.cacheCode( tmp1, tmp2 );

	vzprintf("MULS R%d, R%d, R%d\n", DReg, SReg, DReg );
}

//void CCortexM3::gen_rem(uint8_t DReg, uint8_t SReg1, uint8_t SReg2){
//// SReg -> result
//// SReg1 -> dividend
//// SReg2 -> divisor
//
//	gen_mul(SReg2, DReg );	//multiply the result with the divisor
//	gen_sub(DReg, SReg1, SReg2);
//}

void CCortexM3::gen_xor(uint8_t DReg, uint8_t SReg){


//	DReg |= (SReg<<3);
//	DReg |= 0x40;
//
//	transCache.cacheByte( DReg);
//	transCache.cacheByte( 0x40);

  uint16_t tmp = 0x4040 | DReg | (SReg<<3);
  transCache.cacheCode(tmp);

	vzprintf("XOR\n");
}

void CCortexM3::gen_or(uint8_t DReg, uint8_t SReg){
////ORR (register) T1 ORRS   <Rdn>,<Rm>
//
//  	uint16_t tmp = 0x4300 | (SReg<<3) | DReg ;
//
//	transCache.cacheCode( tmp );
//
//	vzprintf("ORRS R%d, R%d\n",DReg, SReg);

//ORR (register) T2 ORR{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}

  	uint16_t tmp1, tmp2;

	tmp1 = 0xEA40 | DReg;
	tmp2 = 0x0000 | (DReg << 8) | SReg;

	transCache.cacheCode( tmp1, tmp2 );

	vzprintf("ORRS R%d, R%d\n",DReg, SReg);
}
void CCortexM3::gen_ori(uint8_t DReg, uint8_t SReg, uint8_t imm){
//ORR (immediate) T1 ORR{S}<c> <Rd>,<Rn>,#<const>
//CURRENT ENCODING FOR 8BIT IMEDIATE ONLY
//FULL ENCODING SUpports up to 12bit immediate
 	uint16_t tmp1, tmp2;

	tmp1 = imm | (DReg<< 8);
	tmp2 = 0xF040 | SReg;

	transCache.cacheCode(tmp2, tmp1);

	vzprintf("ORR R%d, R%d, #%d\n", DReg, SReg, imm);
}
//void CCortexM3::gen_shr(uint8_t DReg, uint8_t SReg1, uint8_t SReg2){
//	//0xFA 0x2X 0xFX 0x0X
//	SReg2 |= 0x20;
//	DReg |= 0xF0;
//
//	transCache.cacheByte( SReg2);
//	transCache.cacheByte( 0xFA);
//	transCache.cacheByte( SReg1);
//	transCache.cacheByte( DReg);
//}
//void CCortexM3::gen_shl(uint8_t DReg, uint8_t SReg1, uint8_t SReg2){
//	//0xFA 0x0X 0xFX 0x0X
//	DReg |= 0xF0;
//
//	transCache.cacheByte( SReg2);
//	transCache.cacheByte( 0xFA);
//	transCache.cacheByte( SReg1);
//	transCache.cacheByte( DReg);
//}
void CCortexM3::gen_shli(uint8_t DReg, uint8_t SReg, uint8_t imm){
//	//LSL (immediate) LSLS <Rd>,<Rm>,#<imm5>
//
//  	//0x0x 0xXX
//	uint16_t tmp1;
//
//	tmp1 = (imm&0x1F) << 6;
//	tmp1 |= SReg << 3;
//	tmp1 |= DReg;
//
//	transCache.cacheCode(tmp1);
//
//	vzprintf("LSLS R%d, R%d, #%d\n", DReg, SReg, imm);

	//LSL (immediate) T2 LSL{S}<c>.W <Rd>,<Rm>,#<imm5>

	uint16_t tmp1, tmp2;

	tmp1 = 0xEA4F;
	tmp2 = 0x0000 | ((imm&0x1C)<<10) | (DReg<<8) | ((imm&0x3)<<6) | SReg;

	transCache.cacheCode(tmp1, tmp2);

	vzprintf("LSLS R%d, R%d, #%d\n", DReg, SReg, imm);
}
void CCortexM3::gen_shri(uint8_t DReg, uint8_t SReg, uint8_t imm){
////LSR (immediate) T1 LSRS <Rd>,<Rm>,#<imm5>
//
//  	uint16_t tmp = 0x0800 | ((0x1F & imm)<< 6) | (SReg << 3) | (DReg);
//
//	transCache.cacheCode( tmp );
//
//	vzprintf("LSRS R%d, R%d, #%d\n",DReg, SReg, 0x1F & imm);

////LSR (immediate) T2 LSR{S}<c>.W <Rd>,<Rm>,#<imm5>

	uint16_t tmp1, tmp2;

	tmp1 = 0xEA4F;
	tmp2 = 0x0010 | ((imm&0x1C)<<10) | (DReg<<8) | ((imm&0x3)<<6) | SReg;

	transCache.cacheCode(tmp1, tmp2);

  vzprintf("LSRS R%d, R%d, #%d\n",DReg, SReg, 0x1F & imm);


}
void CCortexM3::gen_and(uint8_t DReg, uint8_t SReg){
////AND (register) - T1 ANDS   <Rdn>,<Rm>
//
//	uint16_t tmp1 = 0x4000 | (SReg << 3) | DReg;
//
//	transCache.cacheCode(tmp1);
//
//	vzprintf("AND R%d, R%d, R%d\n", DReg, DReg, SReg);

//AND (register) - T2 AND{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}

	uint16_t tmp1, tmp2;

	tmp1 = 0xEA00 | DReg;
	tmp2 = 0x0000 | (DReg<<8) | SReg;

	transCache.cacheCode(tmp1, tmp2);

	vzprintf("AND R%d, R%d, R%d\n", DReg, DReg, SReg);
}
void CCortexM3::gen_andi(uint8_t DReg, uint8_t SReg, uint8_t imm){
  //0xF0 0x0X 0x0X 0x0X
  // AND (immediate) T1 AND{S}<c> <Rd>,<Rn>,#<const>

  	uint16_t tmp1, tmp2;

//	if(imm > 4095 )	//4095 is the biggest number with 12 bit
//	{
//		zprintf("immediate exceed range in \"gen_andi\" micro-Op\n");
//		eoExec = 1;
//		return;
//	}

	tmp1 = 0xF000 | SReg;
	tmp2 = 0x0000 | imm  | (DReg<<8);


	transCache.cacheCode(tmp1, tmp2 );

	vzprintf("AND R%d, R%d, #%d\n", DReg, SReg, imm);

}
void CCortexM3::gen_add(uint8_t DReg, uint8_t SReg1, uint8_t SReg2){
////ADD (register) T1 ADDS <Rd>,<Rn>,<Rm>
//
//  	uint16_t tmp = 0x1800 | (SReg1 << 6) | (SReg2 << 3) | DReg;
//
//	transCache.cacheCode(tmp);
//
//	vzprintf("ADDS R%d, R%d, R%d\n",DReg, SReg2, SReg1 );

// ADD (register) T3 ADD{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}

	uint16_t tmp1, tmp2;

	tmp1 = 0xEB00 | SReg2;
	tmp2 = 0x0000 | (DReg<<8) | SReg1;

	transCache.cacheCode(tmp1, tmp2);

	vzprintf("ADDS R%d, R%d, R%d\n",DReg, SReg2, SReg1 );
}


void CCortexM3::gen_addi(uint8_t Reg, uint16_t imm){
  	//ADD(immediate) T4 ADDW<c> <Rd>,<Rn>,#<imm12>

  	uint16_t tmp1, tmp2;

	if(imm > 4095 )	//4095 is the biggest number with 12 bit
	{
		zprintf("immediate exceed range in \"gen_addi\" micro-Op\n");
		eoExec = 1;
		return;
	}

	tmp1 = imm & 0xFF;
	tmp1 |= (imm<<4)& 0x7000;
	tmp1 |= Reg << 8;

	tmp2 = Reg;
	tmp2 |= (imm < 0x800) ?	0xF200	:
	  			0xF600	;

	transCache.cacheCode(tmp2, tmp1);

	vzprintf("ADDW R%d, R%d, #%d\n",Reg, Reg, imm);

}
void CCortexM3::gen_ld8(uint8_t DReg, unsigned int imm){

//LDRB (immediate) - T2 LDRB<c>.W <Rt,[<Rn>,#<imm12>]
//  	uint16_t tmp1, tmp2;
// +
// NOP T1 NOP<c> -> this nop has to be inserted after load8 instruction to prevent the execution of the
// instrution after load8 in the memory when PSW refresh event

	unsigned int tmp3;

	if(imm > 4095 )	//4095 is the biggest number with 12 bit
	{
		zprintf("offset exceed memory range of 4096 Bytes in \"gen_ld8\" micro-Op\n");
		eoExec = 1;
		return;
	}


	tmp3 = 0xF8900000  | (MEM_BASE<<16) | imm;
	tmp3 |= (DReg << 12);

////	gen_helper_r4( &CCortexM3::helper_r4);

//	int * p;
//	p = (int *)transCache.getCurrInsAddr();
//	vzprintf("(int)p = 0x%08x\n", (int)p);
//	if ( !((int)p&2) )
//	{
//		transCache.cacheCode( TARGET_NOP );	//NOP instruction to unalign NOP intruction in the memory
//	  	vzprintf("NOP\n");
//	}

	transCache.cacheCode( (uint16_t)(tmp3>>16), (uint16_t)tmp3);

//	transCache.cacheCode( TARGET_NOP );	//NOP instruction
//	transCache.cacheCode( TARGET_NOP );	//NOP instruction

	vzprintf("LDRB R%d,[R%d,#0x%x]\nNOP\nNOP\n",DReg, MEM_BASE, imm);
}

void CCortexM3::gen_ld16(uint8_t DReg, unsigned int imm){

//LDRH (immediate) - T2 LDRH<c>.W <Rt,[<Rn>,#<imm12>]

  	uint16_t tmp1, tmp2;

	if(imm > 4095 )	//4095 is the biggest number with 12 bit
	{
		zprintf("offset exceed memory range of 4096 Bytes in \"gen_ld16\" micro-Op\n");
		eoExec = 1;
		return;
	}

	tmp1 = imm;
	tmp1 |= (DReg << 12);

	tmp2 = 0xF8B0;
	tmp2 |= MEM_BASE;


	transCache.cacheCode(tmp2, tmp1);

	vzprintf("LDRH R%d,[R%d,#%x]\n",DReg, MEM_BASE, imm);

}

//void CCortexM3::gen_ldi8(uint8_t DReg, uint8_t imm){
void CCortexM3::gen_ldi8(uint8_t DReg, uint8_t SReg1, uint8_t SReg2){
//// Sreg1 = base addres (Rn)
//// Sreg2 = offset (Rt)
//// LDRB (register) T1 LDRB<c> <Rt>,[<Rn>,<Rm>]
//
//
//  	uint16_t tmp1;
//
//
//	tmp1 = 0x5C00 | (SReg2 << 6) | SReg1 << 3 | DReg ;
//	transCache.cacheCode(tmp1);
//
//	vzprintf("LDRB R%d,[R%d, R%d]\n", DReg, SReg1, SReg2 );

  // Sreg1 = base addres (Rn)
// Sreg2 = offset (Rt)
// LDRB (register) T2 LDRB<c>.W <Rt>,[<Rn>,<Rm>{,LSL #<shift>}]


  	uint16_t tmp1, tmp2;

	tmp1 = 0xF810 | SReg1;
	tmp2 = 0x0000 | (DReg << 12) | SReg2;

	transCache.cacheCode(tmp1, tmp2);

	vzprintf("LDRB R%d,[R%d, R%d]\n", DReg, SReg1, SReg2 );


}
//void CCortexM3::gen_sti8(unsigned int imm, uint8_t SReg1, uint8_t AReg){
void CCortexM3::gen_sti8(uint8_t SReg, uint8_t DReg1, uint8_t DReg2){
////  STRB (register) - T1 STRB<c> <Rt>,[<Rn>,<Rm>]
//
//  	uint16_t tmp1;
//
//	tmp1 = 0x5400 | (DReg2<<6) | (DReg1<<3) | SReg;
//
//	transCache.cacheCode(tmp1);
//
//  	vzprintf("STRB R%d, [R%d , R%d]\n",SReg, DReg1, DReg2 );

//  STRB (register) - T2 STRB<c>.W <Rt>,[<Rn>,<Rm>{,LSL #<shift>}]

  	uint16_t tmp1, tmp2;

	tmp1 = 0xF800 | DReg1;
	tmp2 = 0x0000 | (SReg << 12) | DReg2;

	transCache.cacheCode(tmp1, tmp2);

  	vzprintf("STRB R%d, [R%d , R%d]\n",SReg, DReg1, DReg2 );
}

void CCortexM3::gen_st8(unsigned int imm, uint8_t SReg){
////STRB (imediate) T2 STRB<c>.W <Rt,[<Rn>,#<imm12>]

  	uint16_t tmp1, tmp2;

	if(imm > 4095 )	//4095 is the biggest number with 12 bit
	{
		zprintf("offset exceed memory range of 4096 Bytes in \"gen_st8\" micro-Op\n");
		eoExec = 1;
		return;
	}

	tmp1 = imm;
	tmp1 |= (SReg & 0xF)<<12;
	tmp2 = (MEM_BASE & 0xF) | (0xF88 << 4);

	transCache.cacheCode(tmp2, tmp1);
//	transCache.cacheCode( TARGET_NOP );	//NOP instruction

	vzprintf("STRB R%d, [R%d + #0x%x]\n",SReg, MEM_BASE, imm );

}

void CCortexM3::gen_st16(unsigned int imm, uint8_t SReg){
//STRH (immediate) T2 STRH<c>.W <Rt,[<Rn>,#<imm12>]
	uint16_t tmp1, tmp2;

	if(imm > 4095 )	//4095 is the biggest number with 12 bit
	{
		zprintf("offset exceed memory range of 4096 Bytes in \"gen_st16\" micro-Op\n");
		eoExec = 1;
		return;
	}

	tmp1 = imm ;
	tmp1 |= (SReg & 0xF)<<12;
	tmp2 = (MEM_BASE & 0xF) | (0xF8A << 4);

	transCache.cacheCode(tmp2, tmp1);

	vzprintf("STRH R%d, [R%d + #0x%x]\n",SReg, MEM_BASE, imm );

}


void CCortexM3::gen_writePC(uint16_t npc){
// auxiliary function, used a mov plus a WritePCreg

	gen_movi(aReg2, npc);
	gen_writePCreg( aReg2 );
}

void CCortexM3::gen_writePCreg(uint8_t SReg){
// //STRH (immediate) T1 STRH<c> <Rt>,[<Rn>,#<imm>]
//
//  	uint16_t tmp;
//
//	gen_movi(aReg1, (int)&(env->PC) );
//
//	tmp = 0x8000 | (aReg1 << 3) | SReg ;
//
//	transCache.cacheCode(tmp);
//
//	vzprintf("STRH R%d,[R%d, #%d]\n", SReg, aReg1, 0);

 //STRH (immediate) T2 STRH<c>.W <Rt,[<Rn>,#<imm12>]

  	uint16_t tmp1, tmp2;

	gen_movi(aReg1, (int)&(env->PC) );

	tmp1 = 0xF8A0 | aReg1;
	tmp2 = (SReg << 12);

	transCache.cacheCode(tmp1, tmp2);

	vzprintf("STRH R%d,[R%d, #%d]\n", SReg, aReg1, 0);
}


void CCortexM3::gen_brkp( uint8_t imm){
	//BKPT T1 BKPT #<imm8>

  	transCache.cacheCode( 0xBE00 | imm);
	vzprintf("BKPT #0x%02x\n", imm );
}


int CCortexM3::generate(void)
{
	return 1;
}

void CCortexM3::helper_ret(void){
	unsigned int tmp1,tmp2;

	vzprintf("{ ret from 0x%x\n", env->PC);

	tmp2 = env->dataMem[SP];
	vzprintf("{ current half SP 0x%x\n", tmp2);

	tmp1 = (env->dataMem[tmp2]) << 8;
	vzprintf("{ half PC addr 0x%x\n", tmp1);

	tmp1 |= (uint8_t)(env->dataMem[tmp2-1]);
	vzprintf("{ full RET PC addr 0x%x\n\n", tmp1);

	env->dataMem[SP] -= 2;

	env->PC = (uint16_t)tmp1;

	//vzprintf("0x%x}\n\n", env->PC);
}

void CCortexM3::helper_call(void){
//this helper updates the PC with the function location
//and pushes in the stack the previous PC in order to return
//from the function call

	uint8_t tmp1,auxSP;

	env->dataMem[SP]++;		//increment the SP
	tmp1 = (uint8_t)env->PC;		//access the PC's LSB
	auxSP = env->dataMem[SP];	//locate the stack head
	env->dataMem[auxSP] = tmp1;	//push the PC's LSB

	env->dataMem[SP]++;		//increment the SP
	tmp1 = (uint8_t)(env->PC >> 8 );	//access the PC's MSB
	auxSP++;			//locate the stack head
	env->dataMem[auxSP] = tmp1;	//push the PC's MSB

}


void CCortexM3::helper_DA(void){
//this helper function adjusts the eight-bit value in the Accumulator resulting
//from the earlier addition of two variables (each in packed-BCD format), producing two four-bit digits

//  CC_MANUAL_UPDATE; << this is done automaticaly, right?

  int temp_Acc = env->dataMem[A];
  int temp_PSW = env->dataMem[PSW];

  zprintf("DA ACC read value 0x%04x: \n",temp_Acc);
  zprintf("DA PSW read value 0x%04x: \n",temp_PSW);

  if ( ((temp_Acc&0x0F) > 0x09) || ((temp_PSW&AC_BIT) != 0) )
  {
  	temp_Acc += 0x06;
   	zprintf("ADJUST ACC + 0x06\n");
  }

  if ( ((temp_Acc&0xF0) > 0x90) || ((temp_PSW&CY_BIT) != 0) )
  {
  	temp_Acc += 0x60;
   	zprintf("ADJUST ACC + 0x60\n");
  }

  env->dataMem[A] = temp_Acc&0xFF;
  env->dataMem[PSW] = (temp_PSW&~AC_BIT) | ((temp_Acc&AC_BIT >>8)<< CY_POS);

//  ENABLE_CC_MONITORING;

}

//void CDBTEngine::helper_CC_lazyEv(void) {
////helper fuction to calculate the condition codes when the PSW e read.
////this function will be called by the Condition codes handler mechanis
////it will read the Condition Codes lazy evaluation register (R12) and:
//// if operation field is 0
////	-CC are updated, except Parity
////	-calculae only P
////else
////	-pending condition code update
////  	-calculate all the Cond Codes
////	-calculate P
//
//  	unsigned int res, cout, ac, ov;
//
//	//load the old Condition Codes and Acc from memory
//	uint8_t temp_CondCodes = env->dataMem[PSW];
//	uint8_t tmpAcc = env->dataMem[A];
//
//	/*Re-enable Debug Monitor for watchpoint generated interrupts generation*/
//  	//ENABLE_CC_MONITORING;
//
//	//Odd Parity Calculation
//	int cnt = 0;
//	vzprintf("\tOld PSW 0x%02x\n", temp_CondCodes);
//	vzprintf("\tUpdating PSW on... ");
//
//	for(int i= 0; i<8; i++) {
//		cnt ^= tmpAcc &1;
//		tmpAcc >>= 1;
//	}
//	temp_CondCodes &= ~PAR_BIT;
//	temp_CondCodes |= cnt;
//
//	vzprintf("\nLazy Evaluation Operand�: %c\n", (char)lzParameters.operand);
//
//	vzprintf("P");
//
//	switch ( lzParameters.operand )	{
//	  //decode the operation:
//	case LZE_UP2DATE:	//if the Operation Field is zero means no pending operation, calculate only P
//	  	break;
//	case LZE_ADD_OP :	//Add operation, calculate C, AC and OV
//
//		res = (unsigned)(lzParameters.inputOp1 + lzParameters.inputOp2);
//
//		cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7
//	//	ac = (((uint16_t)res>>4)&0xF != (((uint8_t)lzParameters.inputOp1>>4)&0xF + ((uint8_t)lzParameters.inputOp2>>4)&0xF)) ?	1 : 0;
//		ac = ((  (((uint8_t)lzParameters.inputOp1)&0xF) +  (((uint8_t)lzParameters.inputOp2)&0xF) ) & 16) >>4 ;
//
//		ov =  (lzParameters.inputOp1&0x80 == lzParameters.inputOp2&0x80) & (lzParameters.inputOp1&0x80 != res&0x80)  ;
//		temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
//		temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update
//
//		lzParameters.operand = '0';	//clean the pending operation
//
//		vzprintf(", CY, AC, OV\n");
//		vzprintf("\tADD op1 0x%02x, op2 0x%02x, res 0x%02x\n", lzParameters.inputOp1, lzParameters.inputOp2, res);
//		vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);
//
//	  	break;
//	case LZE_ADDC_OP :	//Add Carry operation, calculate C, AC and OV
//
//	  	res = (unsigned)(lzParameters.inputOp1 + lzParameters.inputOp2 + lzParameters.carryIn);
//
//		cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7
//
//		zprintf("res %x\n", (((uint16_t)res>>4)&0xF));
//		zprintf("op1 %x\n", ((uint8_t)lzParameters.inputOp1>>4)&0xF);
//		zprintf("op2 %x\n", ((uint8_t)lzParameters.inputOp2>>4)&0xF );
//		zprintf("carry %x\n", ((uint8_t)lzParameters.carryIn) );
//		//ac =  (((uint16_t)res>>4)&0xF) != (  (((uint8_t)lzParameters.inputOp1>>4)&0xF) +  (((uint8_t)lzParameters.inputOp2>>4)&0xF) + (uint8_t)lzParameters.carryIn ) ?  1 : 0;
//		ac = ((  (((uint8_t)lzParameters.inputOp1)&0xF) +  (((uint8_t)lzParameters.inputOp2)&0xF) + (uint8_t)lzParameters.carryIn ) & 16) >>4 ;
//
//		zprintf("new AC %d\n", ac);
//
//		ov =  (lzParameters.inputOp1&0x80 == lzParameters.inputOp2&0x80) & (lzParameters.inputOp1&0x80 != res&0x80) 	;
//
//		temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
//		temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update
//
//		lzParameters.operand = '0';	//clean the pending operation
//
//		vzprintf(", CY, AC, OV\n");
//		vzprintf("\tADDC op1 0x%02x, op2 0x%02x, cin %x, res 0x%02x\n", lzParameters.inputOp1, lzParameters.inputOp2, lzParameters.carryIn, res);
//		vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);
//
//	  	break;
//	case LZE_SUBB_OP :	//Sub with borrow operation, calculate C, AC and OV
//
//	  	res = (unsigned)(lzParameters.inputOp1 - lzParameters.inputOp2 - lzParameters.carryIn);
//
//		cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7
//		//ac = ((uint16_t)res>>4)&0xF != (((uint8_t)lzParameters.inputOp1>>4)&0xF - ((uint8_t)lzParameters.inputOp2>>4)&0xF - ((uint8_t)lzParameters.carryIn)) ?	1 : 0;
//		ac = ((  (((uint8_t)lzParameters.inputOp1)&0xF) -  (((uint8_t)lzParameters.inputOp2)&0xF) - (uint8_t)lzParameters.carryIn ) & 16) >>4 ;
//
//		ov =  (lzParameters.inputOp1&0x80 != lzParameters.inputOp2&0x80) & (lzParameters.inputOp1&0x80 != res&0x80)  ;
//
//		temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
//		temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update
//
//		lzParameters.operand = '0';	//clean the pending operation
//
//		vzprintf(", CY, AC, OV\n");
//		vzprintf("\tSUBB op1 0x%02x, op2 0x%02x, cin %x, res 0x%02x\n", lzParameters.inputOp1, lzParameters.inputOp2, lzParameters.carryIn, res);
//		vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);
//
//		break;
//	default:
//	  	vzprintf("\nLazy Evaluation Parameters corrupted %c!!!!!!!\n", lzParameters.operand);
//		break;
//	}
//
//	env->dataMem[PSW] = temp_CondCodes;
//
//	vzprintf("\n\tNew PSW 0x%02x\n", temp_CondCodes);
//
////	/*Re-enable Debug Monitor for watchpoint generated interrupts generation*/
////  	ENABLE_CC_MONITORING;
//
//}

void CCortexM3::helper_CC_lazyEv_SNIFFER_BACKDOOR(void) {
//helper fuction to calculate the condition codes when the PSW e read.
//this function will be called by the BusFault Handler
//it will read the Condition Codes lazy evaluation register (R12) and:
// if operation field is 0
//	-CC are updated, except Parity
//	-calculae only P
//else
//	-pending condition code update
//  	-calculate all the Cond Codes
//	-calculate P

  	unsigned int res, cout, ac, ov;

//	//load the old Condition Codes and Acc from memory
//	uint8_t temp_CondCodes = env->dataMem[PSW];
//	uint8_t tmpAcc = env->dataMem[A];



//#define BACKDOOR_GET_UINT8_T(x)

//	//load the old Condition Codes and Acc from memory


//	unsigned char * ptr_a;
//	ptr_a = &env->dataMem[PSW] + 0x80000;//[PSW];


	uint8_t temp_CondCodes = env->dataMem[PSW];//BACKDOOR_GET_UINT8_T(env->dataMem[PSW]);


	uint8_t tmpAcc = env->dataMem[A];


	//Odd Parity Calculation
	int cnt = 0;
	vzprintf("\tOld PSW 0x%02x\n", temp_CondCodes);
	vzprintf("\tUpdating PSW on... ");

	for(int i= 0; i<8; i++) {
		cnt ^= tmpAcc &1;
		tmpAcc >>= 1;
	}
	temp_CondCodes &= ~PAR_BIT;
	temp_CondCodes |= cnt;

	vzprintf("\nLazy Evaluation Operand�: %c\n", (char)lzParameters.operand);

	vzprintf("\t\t\tP\n");

	switch ( lzParameters.operand )	{
	  //decode the operation:
	case LZE_UP2DATE:	//if the Operation Field is zero means no pending operation, calculate only P
	  	break;
	case LZE_ADD_OP :	//Add operation, calculate C, AC and OV

		res = (unsigned)(lzParameters.inputOp1 + lzParameters.inputOp2);

		cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7
	//	ac = (((uint16_t)res>>4)&0xF != (((uint8_t)lzParameters.inputOp1>>4)&0xF + ((uint8_t)lzParameters.inputOp2>>4)&0xF)) ?	1 : 0;
		ac = ((  (((uint8_t)lzParameters.inputOp1)&0xF) +  (((uint8_t)lzParameters.inputOp2)&0xF) ) & 16) >>4 ;

		ov =  (lzParameters.inputOp1&0x80 == lzParameters.inputOp2&0x80) & (lzParameters.inputOp1&0x80 != res&0x80)  ;
		temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
		temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update

		lzParameters.operand = '0';	//clean the pending operation

		vzprintf("\t\t\tCY\n\t\t\tAC\n\t\t\tOV\n");
		vzprintf("\tADD op1 0x%02x, op2 0x%02x, res 0x%02x\n", lzParameters.inputOp1, lzParameters.inputOp2, res);
		vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);

	  	break;
	case LZE_ADDC_OP :	//Add Carry operation, calculate C, AC and OV

	  	res = (unsigned)(lzParameters.inputOp1 + lzParameters.inputOp2 + lzParameters.carryIn);

		cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7

		zprintf("res %x\n", (((uint16_t)res>>4)&0xF));
		zprintf("op1 %x\n", ((uint8_t)lzParameters.inputOp1>>4)&0xF);
		zprintf("op2 %x\n", ((uint8_t)lzParameters.inputOp2>>4)&0xF );
		zprintf("carry %x\n", ((uint8_t)lzParameters.carryIn) );
		//ac =  (((uint16_t)res>>4)&0xF) != (  (((uint8_t)lzParameters.inputOp1>>4)&0xF) +  (((uint8_t)lzParameters.inputOp2>>4)&0xF) + (uint8_t)lzParameters.carryIn ) ?  1 : 0;
		ac = ((  (((uint8_t)lzParameters.inputOp1)&0xF) +  (((uint8_t)lzParameters.inputOp2)&0xF) + (uint8_t)lzParameters.carryIn ) & 16) >>4 ;

		zprintf("new AC %d\n", ac);

		ov =  (lzParameters.inputOp1&0x80 == lzParameters.inputOp2&0x80) & (lzParameters.inputOp1&0x80 != res&0x80) 	;

		temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
		temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update

		lzParameters.operand = '0';	//clean the pending operation

		vzprintf("\t\t\tCY\n\t\t\tAC\n\t\t\tOV\n");
		vzprintf("\tADDC op1 0x%02x, op2 0x%02x, cin %x, res 0x%02x\n", lzParameters.inputOp1, lzParameters.inputOp2, lzParameters.carryIn, res);
		vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);

	  	break;
	case LZE_SUBB_OP :	//Sub with borrow operation, calculate C, AC and OV

	  	res = (unsigned)(lzParameters.inputOp1 - lzParameters.inputOp2 - lzParameters.carryIn);

		cout = (res >> 8)&1;			//The Carry bit (C) is set if there is a carry-out of bit 7
		//ac = ((uint16_t)res>>4)&0xF != (((uint8_t)lzParameters.inputOp1>>4)&0xF - ((uint8_t)lzParameters.inputOp2>>4)&0xF - ((uint8_t)lzParameters.carryIn)) ?	1 : 0;
		ac = ((  (((uint8_t)lzParameters.inputOp1)&0xF) -  (((uint8_t)lzParameters.inputOp2)&0xF) - (uint8_t)lzParameters.carryIn ) & 16) >>4 ;

		ov =  (lzParameters.inputOp1&0x80 != lzParameters.inputOp2&0x80) & (lzParameters.inputOp1&0x80 != res&0x80)  ;

		temp_CondCodes &= ~( CY_BIT | AC_BIT | OV_BIT );			//clear the bits to update
		temp_CondCodes |= (cout << CY_POS) | (ac << AC_POS) | (ov << OV_POS);	//insert the bits to update

		lzParameters.operand = '0';	//clean the pending operation

		vzprintf("\t\t\tCY\n\t\t\tAC\n\t\t\tOV\n");
		vzprintf("\tSUBB op1 0x%02x, op2 0x%02x, cin %x, res 0x%02x\n", lzParameters.inputOp1, lzParameters.inputOp2, lzParameters.carryIn, res);
		vzprintf("\tcy %d, ac %d, ov %d", cout, ac, ov);

		break;
	default:
	  	vzprintf("\nLazy Evaluation Parameters corrupted %c!!!!!!!\n", lzParameters.operand);
		break;
	}

	env->dataMem[PSW] = temp_CondCodes;

	vzprintf("\n\tNew PSW 0x%02x\n", temp_CondCodes);

//	/*Re-enable Debug Monitor for watchpoint generated interrupts generation*/
//  	ENABLE_CC_MONITORING;

}

//void CCortexM3::helper_exception(int pc)
//  {
//    	zprintf("Current PC %08x\n", pc);
//   	zprintf("SHCSR - monitor active = 10: %08x\n", SCB->SHCSR);
//  	zprintf("DFSR - DWT trigger %08x\n", SCB->DFSR);
//  	zprintf("SHPR3 - Monitor priority %02x\n", SCB->SHP[8] );
//  }

//void CCortexM3::helper_r4(int pc, int r4){
//    	zprintf("Current PC %08x\n", pc);
//	zprintf("Current R4 %08x\n", r4);
//}

void CCortexM3::helper_debug(int soft_brkp_addr) {

  char menu;
  char dummy;
  int addr;
  int addr_end;

  static int ign_addr=0;

  int tmp;

  bool exit = true;


  //condition to skip debug call untill reaching the desired address
  if ( ign_addr != 0) {
    if (soft_brkp_addr >= ign_addr)
      ign_addr = 0;
    else
      return;
  }

  //manual update Condition Codes before debug actions and disable Debug Monitor while in Debug Routine
  //CC_MANUAL_UPDATE;
  //	DISABLE_CC_MONITORING;
	//helper_CC_lazyEv();
  	helper_CC_lazyEv_SNIFFER_BACKDOOR();


  do {
    printf("\n#####################Remote Debug Routine#####################\n\n");
    printf("\t\t##################################\n");
    printf("\t\t##   Debug call @ PC = 0x%04x   ##\n", (uint16_t)soft_brkp_addr);
    printf("\t\t##################################\n");

    printf("\tEnter option:\n");
    printf("\tq - Register dump\n");
    printf("\tw - Memory dump\n");
    printf("\te - Memory address\n");
    printf("\tr - PC value\n");
    printf("\tt - PSW value\n");
    printf("\ty - A value\n");
    printf("\tu - B value\n");
    printf("\ti - DPTR value\n");
    printf("\to - XMEM dump\n");
    printf("\tp - General Internal dump\n");
    printf("\ta - Code Stats\n");

    printf("\t+ - skip debug until...\n\t");
    scanf("%c",&menu);
    scanf("%c",&dummy);

    printf("menu option: %c\n", menu);
    switch (menu) {
    case 'q':
      //Register Dump
      printf("R0 0x%02x\n", (uint8_t)env->dataMem[0] );
      printf("R1 0x%02x\n", (uint8_t)env->dataMem[1] );
      printf("R2 0x%02x\n", (uint8_t)env->dataMem[2] );
      printf("R3 0x%02x\n", (uint8_t)env->dataMem[3] );
      printf("R4 0x%02x\n", (uint8_t)env->dataMem[4] );
      printf("R5 0x%02x\n", (uint8_t)env->dataMem[5] );
      printf("R6 0x%02x\n", (uint8_t)env->dataMem[6] );
      printf("R7 0x%02x\n", (uint8_t)env->dataMem[7] );
      break;
    case 'w':
      //Memory Dump
      printf("Insert FIRST memory Address in Hex format: \n");
      scanf("%x", &addr);
      scanf("%c", &dummy);
      printf("Insert LAST memory Address in Hex format: \n");
      scanf("%x", &addr_end);
      scanf("%c", &dummy);
      for( ; addr <= addr_end; addr++) {
      	printf("mem[0x%02x] 0x%02x\n", addr, (uint8_t)env->dataMem[addr] );
      }
      break;
    case 'e':
      //Memory address
      printf("Insert memory Address in Hex format: \n");
      scanf("%x", &addr);
      scanf("%c", &dummy);
      printf("mem[0x%02x] 0x%02x\n", addr, (uint8_t)env->dataMem[addr] );
      break;
    case 'r':
      //PC value
      printf("PC $ 0x%04x\n", env->PC);
      break;
    case 't':
      //PSW value
      tmp = (uint8_t)env->dataMem[PSW];
      printf("PSW 0x%02x\n", tmp );
      printf("C   A   F0  RS1 RS0 OV  -   P\n");
      printf("%d    %d    %d     %d       %d       %d     %d   %d\n", (tmp>>7)&1, \
							(tmp>>6)&1, \
							(tmp>>5)&1, \
							(tmp>>4)&1, \
							(tmp>>3)&1, \
							(tmp>>2)&1, \
							(tmp>>1)&1, \
							(tmp)&1 );
      break;
    case 'y':
      //A value
      printf("A 0x%02x\n", (uint8_t)env->dataMem[A] );
      break;
    case 'u':
      //B value
      printf("B 0x%02x\n", (uint8_t)env->dataMem[B] );
      break;
    case 'i':
      //DPTR
      printf("DPTR 0x%04x\n", *(uint16_t*)&env->dataMem[DPL] );
      break;
    case 'o':
      //XMEM Dump
      printf("Insert FIRST XMEM Address in Hex format: \n");
      scanf("%x", &addr);
      scanf("%c", &dummy);
      printf("Insert LAST XMEM Address in Hex format: \n");
      scanf("%x", &addr_end);
      scanf("%c", &dummy);
      for( ; addr <= addr_end; addr++) {
      	printf("mem[0x%02x] 0x%02x\n", addr, (uint8_t)xMem[addr] );
      }
      break;
    case 'p':
      //General Inter Dump

      printf("R0 0x%02x\n", (uint8_t)env->dataMem[0] );
      printf("R1 0x%02x\n", (uint8_t)env->dataMem[1] );
      printf("R2 0x%02x\n", (uint8_t)env->dataMem[2] );
      printf("R3 0x%02x\n", (uint8_t)env->dataMem[3] );
      printf("R4 0x%02x\n", (uint8_t)env->dataMem[4] );
      printf("R5 0x%02x\n", (uint8_t)env->dataMem[5] );
      printf("R6 0x%02x\n", (uint8_t)env->dataMem[6] );
      printf("R7 0x%02x\n\n", (uint8_t)env->dataMem[7] );

      printf("A 0x%02x\n", (uint8_t)env->dataMem[A] );
      printf("B 0x%02x\n", (uint8_t)env->dataMem[B] );
      printf("SP 0x%02x\n\n", (uint8_t)env->dataMem[SP] );

      printf("PC $ 0x%04x\n\n", env->PC );

      printf("DPTR 0x%04x\n\n\n", *(uint16_t*)&env->dataMem[DPL]);


      printf("PSW 0x%02x\n\n", (uint8_t)env->dataMem[PSW] );

      break;

//    case 'a':
//      //cache size and code stats
//      	printf("Source Code Size: %d bytes\n", sByteCount);
//	printf("Target Code Size: %d bytes\n", transCache.getCodeSize());
//	printf("Code size Ratio: 1/%d\n\n", transCache.getCodeSize()/sByteCount );
//
//	printf("Source Instruction Count: %d inst\n", sInstCount);
//	printf("Target Instruction Count: %d inst\n", tInstCount);
//	printf("Instruction Ratio: 1/%d\n\n", tInstCount/sInstCount );
//
//	printf("PSW read accesses %d", PSWrCounter);


      break;
    case '+':
      printf("Insert Code Address to ignore debug calls until reached, in Hex format: \n");
      scanf("%x", &ign_addr);
      scanf("%c", &dummy);
      exit = false;
      break;
    default:
	exit = false;
	break;
      }

  }while ( exit );

  //Re-enable Debug Monitor for watchpoint generated interrupts generation
  //ENABLE_CC_MONITORING;

}

void CCortexM3::helper_xmem_range(void){



}

/************ End Helper ****************/






