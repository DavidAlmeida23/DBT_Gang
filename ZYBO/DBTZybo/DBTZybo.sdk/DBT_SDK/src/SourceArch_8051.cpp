#include "SourceArch_8051.h"



C8051Arch::C8051Arch( int Ccache_size, CTargetArchitecture *target)
	: CSourceArchitecture(Ccache_size, target)
{

//	env.dataMem = (uint8_t *) new uint8_t[DATA_SIZE];

	static uint8_t ram_8051[DATA_SIZE]; // @ "SEC_RAM_8051";
//	printf("\n\n Varable ram_8051 at %x\n\n", &ram_8051[0]);
	static uint8_t x_ram[XDATA_SIZE];

	env.dataMem = ram_8051;

	xMem = (XDATA_SIZE == 0) ?	NULL	:  x_ram;

	zprintf("XDATA_SIZE base address is 0x%x\n end address is 0x%x\n", xMem, xMem+XDATA_SIZE );



}

C8051Arch::~C8051Arch(void)
{
	delete[] env.dataMem;}

void C8051Arch::envReset(void) {


	env.PC = 0;
	//env.tReg1 = 0;
	//env.tReg2 = 0;

	printf("\n\n Varable env.dataMem at %x\n\n", env.dataMem);

	printf("\n\n Varable env.dataMem[SP] at %x\n\n", &env.dataMem[SP]);


	env.dataMem[SP] = 7;

	env.dataMem[A] = 0;
	env.dataMem[B] = 0;
	env.dataMem[PSW] = 0;
	env.dataMem[DPL] = 0;
	env.dataMem[DPH] = 0;
	memset( env.dataMem, 0, 8);
	target->lzParameters.operand = '0';

};

/*this function inits the condition code handling mechanism, depending on the solution adopter to fit source/target pair
for this implementation, hardware support through debug features is used to update the CCodes in a lazyEvaluation fashion
when the CC mem address is accessed*/
//void CDBTEngine::condCodedHandlerInit(void){
//  	printf("(int*)&env.dataMem[PSW] = 0x%08x\n", (int*)&env.dataMem[PSW]);
//  	printf("(int *)(env.dataMem) = 0x%08x\n", (int *)(env.dataMem));
// 	CM3_DEBUGMONInit( (int*)&env.dataMem[PSW] );
//}
void C8051Arch::condCodedHandlerInit(void){
  	printf("(int *)(env.dataMem) = 0x%08x\n", (int *)(env.dataMem));
  	printf("(int*)&env.dataMem[PSW] = 0x%08x\n", (int*)&env.dataMem[PSW]);
	printf("Configuring Sniffer module...\n");

	// sniffer_config((int*)&env.dataMem[PSW]);

 	//CM3_DEBUGMONInit( (int*)&env.dataMem[PSW] );
}



void C8051Arch::decode(uint8_t op)
{

	uint8_t subOp = op & 0x0F;
	uint8_t regN = op & 0x7;

//	helper_CC_lazyEv_SNIFFER_BACKDOOR();

//	target->gen_helper(&CTargetArchitecture::helper_call);

	switch(op>>4){
		case 0 :
			fineDecode_0x0(subOp, regN);	break;
		case 1 :
			fineDecode_0x1(subOp, regN);	break;
		case 2 :
			fineDecode_0x2(subOp, regN);	break;
		case 3 :
			fineDecode_0x3(subOp, regN);	break;
		case 4 :
			fineDecode_0x4(subOp, regN);	break;
		case 5 :
			fineDecode_0x5(subOp, regN);	break;
		case 6 :
			fineDecode_0x6(subOp, regN);	break;
		case 7 :
			fineDecode_0x7(subOp, regN);	break;
		case 8 :
			fineDecode_0x8(subOp, regN);	break;
		case 9 :
			fineDecode_0x9(subOp, regN);	break;
		case 0xa :
			fineDecode_0xa(subOp, regN);	break;
		case 0xb :
			fineDecode_0xb(subOp, regN);	break;
		case 0xc :
			fineDecode_0xc(subOp, regN);	break;
		case 0xd :
			fineDecode_0xd(subOp, regN);	break;
		case 0xe :
			fineDecode_0xe(subOp, regN);  	break;
		case 0xf :
			fineDecode_0xf(subOp, regN);	break;
		default :
			target->eoExec = true;
			zprintf("OPCODE NOT FOUND\n");
			break;
	}

	return;
}

void C8051Arch::fineDecode_0x0(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1;
	uint16_t newPC;



	switch (subOp) {
	case 0: //NOP

	  	//target->gen_brkp(0xF0);

	  	//target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1);

		zprintf("\tNOP\n\n");
	  	break;
	case 1: // AJMP

		tmp1 = FETCH;

		//5 MSb from PC, 3b from opcode, 8LSb from instruction
		newPC = (env.PC & 0xF800) | 0x0000 | (uint16_t)tmp1;
	    	target->gen_writePC(newPC);

	    	zprintf("\tAJMP 0x%04X\n\n", newPC);
		eoBB = true;

		break;
	case 2:// Long jump : LJMP // ******* Error ******

	  	//DEBUG CALL IN RET INSTRUCTION
		//target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1);


		newPC = FETCH;
		newPC <<= 8;
		newPC |= FETCH;

		target->gen_writePC(newPC);
		eoBB = true;
		zprintf("\tLJMP 0x%04X\n\n", newPC);
		break;
	case 3:// RR A
	  	target->gen_ld8(tReg1, A); // load A

		target->gen_ld_bit(tReg1, tReg2, 0);	//get the carry out bit (before rotation)
		target->gen_st_bit(tReg2, tReg1, 8);	//place it as carry in bit (before rotation)

		target->gen_shri(tReg1, tReg1, 1); // shift A
		target->gen_st8(A, tReg1); 	// Save new A

//		target->gen_ld8(tReg1, A); // load A
//		target->gen_movi(tReg2, 1);
//		target->gen_and(tReg1, tReg2);
//		target->gen_shli(tReg1, tReg1, 8);
//		target->gen_ld8(tReg2, A); // load A again
//		target->gen_or(tReg1, tReg2);
//		target->gen_shri(tReg1, tReg1, 1);
//		target->gen_andi(tReg1, tReg1, 0xFF);
//		target->gen_st8( A, tReg1); // Save to A

		zprintf("\tRR A\n\n");
		break;
	case 4: // INC A
		target->gen_ld8(tReg1, A);  // load A to tReg1
		target->gen_addi(tReg1, 1); // add 1
		target->gen_st8(A, tReg1);  // write back
		//target->gen_helper_update_parity();
		zprintf("\tINC A\n\n");
		break;
	case 5: // INC direct
		tmp1 = FETCH;
		target->gen_ld8(tReg1, tmp1);  // load mem to tReg1
		target->gen_addi(tReg1, 1); // add 1
		target->gen_st8(tmp1, tReg1);  // write back
		zprintf("\tINC (0x%02X)\n\n", tmp1);
		break;
	case 6: // INC @Ri
	case 7: // INC @Ri
	  	target->gen_ld8(tReg2, subOp&0x01);
		target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
		target->gen_addi(tReg1, 1);
		//target->gen_sti8(subOp&0x01, tReg1, tReg2);
		target->gen_sti8(tReg1, MEM_BASE, tReg2);
		zprintf("\tINC @R%X\n\n", subOp&0x01);
		break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // INC Rn
		target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
		target->gen_movi(tReg2, 1);
		target->gen_add(tReg1, tReg1, tReg2); // add 1
		target->gen_st8( Rn, tReg1);
		zprintf("\tINC R%d\n\n", Rn);
		break;
	}
}

void C8051Arch::fineDecode_0x1(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, byteAddr;
	uint16_t newPC;

	switch (subOp) {
	case 0	:// JBC
		uint8_t tmp2;

		tmp1 = FETCH; 	// get bit address
		tmp2 = FETCH;	//get the jump offset

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

//		get_real_bit_addr(&tmp1, &tmp2);
//		target->gen_ld8(tReg1, tmp1); // load register
//
//		target->gen_movi(tReg2, 0x01);
//		target->gen_shli(tReg2, tReg2, tmp2); //
//		target->gen_and(tReg3, tReg1, tReg2);
//
//		target->gen_not(tReg2, tReg2);
//		target->gen_and(tReg1, tReg1, tReg2);
//		target->gen_st8(tmp1, tReg1);
//
//		tmp2 = FETCH;
//		target->gen_movi(tReg1, 0);
//		target->gen_cjne(tReg1, tReg3, tmp2);

//		target->gen_ld_bit( tReg1, tmp1);	//get bit //target->gen_st_bit additionalli loads tmp1 bit in tReg1

		byteAddr = (tmp1 < 128 )	?	32 + (tmp1 >> 3)	: //if bit7 is clear, bit belongs to bit addressable area (base 32)
							tmp1 & 0xF8		; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg2, tmp1&0x07);	//get bit

		target->gen_movi(tReg3, 0);

		target->gen_st_bit(tReg3, tReg1, tmp1&0x07);
		target->gen_st8( byteAddr, tReg1);

		target->gen_cjei(tReg2, 1, tmp2);	//target->generate compare jump equal with tReg2

		eoBB = true;

		zprintf("\t????verify first write pc(was in comment) and ???JBC %d\n\n", env.PC + (int8_t)tmp2);
	  	break;
	case 1	: // ACALL

		tmp1 = FETCH;	//read the page offset first, before storing PC in stack

		newPC = (env.PC & 0xF800) | 0x0000 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

	    	zprintf("\tACALL 0x%04X\n\n", newPC);

	  	break;
	case 2	: // LCALL

	  	//DEBUG CALL IN RET INSTRUCTION
		//target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1);


		newPC = FETCH ;	//new PC must be fetched before PC saving in the stack
		newPC <<= 8;
		newPC |= FETCH;		//otherwise the return address poped from the stack will be incorrect
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

		zprintf("\tLCALL $0x%04x\n\n", newPC);
		break;
	case 3	: // RRC

	  	target->gen_ld8(tReg1, A); // load A
		target->gen_ld8(tReg2, PSW); // load PSW

		target->gen_ld_bit(tReg2, tReg3, CY_POS);	//put the carry bit to A.8 (before rotation)
		target->gen_st_bit(tReg3, tReg1, 8);

		target->gen_ld_bit(tReg1, tReg3, 0);		//get the carry out bit from A to CY (before rotation)
		target->gen_st_bit(tReg3, tReg2, CY_POS);

		target->gen_shri(tReg1, tReg1, 1); // shift A

		target->gen_st8(A, tReg1); 	// Save new A
		target->gen_st8(PSW, tReg2); 	// Save new PSW

//		target->gen_ld8(tReg1, A); // load A
//		target->gen_andi(tReg1, tReg1, 0x01);
//		target->gen_shli(tReg1, tReg1, 7);
//		target->gen_ld8(tReg2, PSW); // load PSW
//		target->gen_andi(tReg3, tReg2, 0x7F); // Clear C
//		target->gen_or(tReg3, tReg1);
//		target->gen_st8(PSW, tReg3); // Save new C to PSW
//
//		target->gen_ld8(tReg1, A); // load A
//		target->gen_shri(tReg1, tReg1, 1); // shift A
//		target->gen_andi(tReg1, tReg1, 0x7F);  // clear A7
//		target->gen_andi(tReg2, tReg2, 0x80);  // get only C
//		target->gen_or(tReg1, tReg2); // New A
//		target->gen_andi(tReg1, tReg1, 0xFF);
//		target->gen_st8(A, tReg1); // Save new A
//		//target->gen_helper_update_parity();

		zprintf("\tRRC A\n\n");
		break;
	case 4	: // DEC A
		target->gen_ld8(tReg1, A);  // load Rn to tmpR[0]
		target->gen_subi(tReg1, 1); // sub 1
		target->gen_st8(A, tReg1);  // write back
		//target->gen_helper_update_parity();
		zprintf("\tDEC A\n\n");
		break;
	case 5	: // DEC direct
		tmp1 = FETCH;
		target->gen_ld8(tReg1, tmp1);  // load mem to tReg1
		target->gen_subi(tReg1, 1); // subb 1
		target->gen_st8(tmp1, tReg1);  // write back
		zprintf("\tDEC 0x%02X\n\n", tmp1);
		break;
	case 6	:
	case 7	: // DEC @Ri
	  	target->gen_ld8(tReg2, subOp&0x01);
		target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
		target->gen_subi(tReg1, 1);
//		target->gen_sti8(Rn, tReg1, tReg2);
		target->gen_sti8(tReg1, MEM_BASE, tReg2);
		//target->gen_helper_inc_dec_indirect(tcg_const(d&1), tcg_const(0));
		zprintf("\tDEC @R%d\n\n", subOp&0x01);
		break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // DEC Rn
		target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
		target->gen_subi(tReg1, 1); // add 1
		target->gen_st8(Rn, tReg1);  // write back
		zprintf("\tDEC R%X\n\n", Rn);
		break;
	}
}
void C8051Arch::fineDecode_0x2(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, byteAddr;

	switch(subOp) {
	case 0	: // JB
		uint8_t tmp2;

	  	tmp1 = FETCH;  	// get bit address
		tmp2 = FETCH;	//get jump offset

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

//		get_real_bit_addr(&tmp1, &tmp2);
//		target->gen_ld8(tReg1, tmp1); // load register
//
//		target->gen_movi(tReg2, 0x01);
//		target->gen_shli(tReg2, tReg2, tmp2); //
//		target->gen_and(tReg3, tReg1, tReg2);
//
//		tmp2 = FETCH;
//		target->gen_movi(tReg1, 0);
//		target->gen_cjne(tReg1, tReg3, tmp2);


		byteAddr = (tmp1 < 128 )	?	32 + (tmp1 >> 3)	: //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 					tmp1 & 0xF8		; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit


		target->gen_cjei(tReg1, 1, tmp2);	//target->generate compare jump equal with tReg2

		eoBB = true;

		zprintf("\t????check write PC????JB %d\n\n", env.PC + (int8_t)tmp1);
	  	break;
	case 1	: // AJMP
	//	decode_ajmp_target->gen(op);
	  	uint16_t tmp3;
		tmp1 = FETCH;

		tmp3 = (env.PC & 0xF800) | 0x0100 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	    	target->gen_writePC(tmp3);

	    	zprintf("\tAJMP 0x%04X\n\n", tmp3);
		eoBB = true;

		break;
	case 2	:// RET

//	  	if (callCount--)
//		{
			//DEBUG CALL IN RET INSTRUCTION
		  	//target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1);

	  		target->gen_helper(&CTargetArchitecture::helper_ret);
//		}
//		else {
//			zprintf("MAIN RETURN DETECTED\nEND OF ENGINE EXECUTION\n");
//			helper_debug(0);
//			target->eoExec = true;
//		}

		eoBB = true;
		zprintf("\tRET\n\n");
		break;
	case 3	: // RL A
  	  	target->gen_ld8(tReg1, A); // load A

//		target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1);

		target->gen_shli(tReg1, tReg1, 1); // shift A

		target->gen_ld_bit(tReg1, tReg2, 8);	//get the carry out bit (before rotation)
		target->gen_st_bit(tReg2, tReg1, 0);	//place it as carry in bit (before rotation)

		target->gen_st8(A, tReg1); 	// Save new A

//		target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1);

//		target->gen_ld8(tReg1, A); // load A
//		target->gen_andi(tReg2, tReg1, 0x80);
//		target->gen_shri(tReg2, tReg2, 7);
//		target->gen_shli(tReg1, tReg1, 1);
//		target->gen_or(tReg1, tReg2);
//		target->gen_andi(tReg1, tReg1, 0xFF);
//		target->gen_st8(A, tReg1); // Save to A
		//target->gen_helper_update_parity();
		zprintf("\tRL A\n\n");
		break;
	case 4	: // ADD A, #imm
		tmp1 = FETCH;
		/* Load register */
		target->gen_ld8(tReg1, A);
		target->gen_movi(tReg2, tmp1);

		target->gen_add(tReg3, tReg1, tReg2);	//flags are alway updated when outside an IT block
		target->gen_st8(A, tReg3);


		//update lazy evaluation of condition codes register
		//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );



		zprintf("\tADD A, #0x%02x\n\n", tmp1);
		break;
	case 5	: // ADD A, Direct
		tmp1 = FETCH;
		/* Load register */

		target->gen_ld8(tReg1, A);
		target->gen_ld8(tReg2, tmp1);

		target->gen_add(tReg3, tReg1, tReg2);	//flags are alway updated when outside an IT block
		target->gen_st8(A, tReg3);

		//update lazy evaluation of condition codes register
		//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );


		zprintf("\tADD A, 0x%02X\n\n", tmp1);
		break;
	case 6	:
	case 7	: // ADD A, @Ri

		target->gen_ld8(tReg1,	subOp&0x01);
	  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

		target->gen_ld8(tReg1, A);
		target->gen_add(tReg3, tReg1, tReg2);
		target->gen_st8(A, tReg3);

		//update lazy evaluation of condition codes register
		//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );


		zprintf("\t??????NYV?????? ADD A, @R%d\n\n", subOp&0x01);
		break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // ADD A, Rn
		target->gen_ld8(tReg1, A); // load Rn to tReg1
		target->gen_ld8(tReg2, Rn); // load A

		target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
		target->gen_st8(A, tReg3);

		//update lazy evaluation of condition codes register
		//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );


		zprintf("\tADD A, R%d\n\n", Rn);
		break;
	}
}
void C8051Arch::fineDecode_0x3(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, tmp2, byteAddr;
	uint16_t newPC;

	switch(subOp) {
	case 0	: // JNB
		tmp1 = FETCH; 	// get bit address
		tmp2 = FETCH;	//get jump offset

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

//		get_real_bit_addr(&tmp1, &tmp2);
//		target->gen_ld8(tReg1, tmp1); // load register
//
//		target->gen_movi(tReg2, 0x01);
//		target->gen_shli(tReg2, tReg2, tmp2);
//		target->gen_and(tReg3, tReg1, tReg2);
//		target->gen_shri(tReg3, tReg2, tmp2);
//
//		tmp2 = FETCH;
//		target->gen_movi(tReg1, 1);
//		target->gen_cjne(tReg1, tReg3, tmp2);

		byteAddr = (tmp1 < 128 )	?	32 + (tmp1 >> 3)	: //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 					tmp1 & 0xF8		; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit


		target->gen_cjnei(tReg1, 1, tmp2);	//target->generate compare jump NOT equal with tReg2

		eoBB = true;

	  	break;
	case 1	: // ACALL

		tmp1 = FETCH;	//read the page offset first, before storing PC in stack

		newPC = (env.PC & 0xF800) | 0x0100 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

	    	zprintf("\tACALL 0x%04X\n\n", newPC);

	case 2	:
		zprintf("\tRETI -UNSUPPORTED- \n\n");
		eoBB = true;
		target->eoExec = true;

	  	break;
	case 3	: // RLC A

//		target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1); //absince of this print causes bad result

	  	target->gen_ld8(tReg1, A); // load A
		target->gen_ld8(tReg2, PSW); // load PSW

		//target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1); //absince of this print causes bad result

		target->gen_shli(tReg1, tReg1, 1); // shift A

		target->gen_ld_bit(tReg2, tReg3, CY_POS);	//get the carry bit to A.8 (before rotation)
		target->gen_st_bit(tReg3, tReg1, 0);

		target->gen_ld_bit(tReg1, tReg3, 8);		//get the carry out bit from A to CY (before rotation)
		target->gen_st_bit(tReg3, tReg2, CY_POS);


		target->gen_st8(A, tReg1); 	// Save new A
		target->gen_st8(PSW, tReg2); 	// Save new PSW

//		target->gen_helper( &CTargetArchitecture::helper_debug, (int)env.PC-1);

//		target->gen_ld8(tReg1, A); // load A
//		target->gen_andi(tReg1, tReg1, 0x80);
//		target->gen_ld8(tReg2, PSW); // load PSW
//		target->gen_andi(tReg3, tReg2, 0x7F); // Clear C
//		target->gen_or(tReg3, tReg1);
//		target->gen_st8(PSW, tReg3); // Save new C to PSW
//
//		target->gen_ld8(tReg1, A); // load A
//		target->gen_shli(tReg1, tReg1, 1); // shift A
//		target->gen_andi(tReg1, tReg1, 0xFE);  // clear A7
//		target->gen_andi(tReg2, tReg2, 0x80);  // get only C
//		target->gen_shri(tReg2, tReg2, 7); //
//		target->gen_or(tReg1, tReg2); // New A
//		target->gen_andi(tReg1, tReg1, 0xFF);
//		target->gen_st8(A, tReg1); // Save new A
		//target->gen_helper_update_parity();
		zprintf("\tRLC A\n\n");
	  	break;
	case 4	: // ADDC A, #immed
		tmp1 = FETCH;

		target->gen_ld8(tReg1, A); // load A
		target->gen_movi(tReg2, tmp1); // load #imm value

		target->gen_ld8(tReg3, PSW);
		target->gen_ld_bit(tReg3, tReg3, CY_POS);

		//update lazy evaluation of condition codes register
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update,LZE_ADDC_OP, tReg1, tReg2, tReg3 );
		//target->gen_assemble_lazyEv_param( LZE_ADDC_OP, tReg1, tReg2, tReg3);

		target->gen_add(tReg1, tReg1, tReg2);
		target->gen_add(tReg1, tReg1, tReg3);
		target->gen_st8(A, tReg1); // Store A

		zprintf("\tADDC A, #0x%02X\n\n", tmp1);
	  	break;
	case 5	: // ADDC A, direct
		tmp1 = FETCH;

		target->gen_ld8(tReg1, A); // load A
		target->gen_ld8(tReg2, tmp1); // load direct address

		target->gen_ld8(tReg3, PSW);
		target->gen_ld_bit(tReg3, tReg3, CY_POS);

		//update lazy evaluation of condition codes register
		//target->gen_helper(&CTargetArchitecture::CC_onDemand_Update,LZE_ADDC_OP, tReg1, tReg2, tReg3 );
		target->gen_assemble_lazyEv_param( LZE_ADDC_OP, tReg1, tReg2, tReg3);

		target->gen_add(tReg1, tReg1, tReg2);
		target->gen_add(tReg1, tReg1, tReg3);
		target->gen_st8(A, tReg1); // Store A

		zprintf("\tADDC A, 0x%02X\n\n", tmp1);
	  	break;
	case 6	:
	case 7	: // ADDC A, @Ri

		target->gen_ld8(tReg1,	subOp&0x01);
	  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

		target->gen_ld8(tReg1, A);

		target->gen_ld8(tReg3, PSW);
		target->gen_ld_bit(tReg3, tReg3, CY_POS);

		//update lazy evaluation of condition codes register
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3);
		//target->gen_assemble_lazyEv_param( LZE_ADDC_OP, tReg1, tReg2, tReg3);

		target->gen_add(tReg1, tReg1, tReg2); // add
		target->gen_add(tReg1, tReg1, tReg3); // Add with C
		target->gen_st8(A, tReg1); // Store A

		zprintf("\t??????NYV??????ADDC A, @R%d\n\n", subOp&0x01);
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	:  // ADDC A, Rn
		target->gen_ld8(tReg1, A); // load A
		target->gen_ld8(tReg2, Rn); // load Rn

		target->gen_ld8(tReg3, PSW);
		target->gen_ld_bit(tReg3, tReg3, CY_POS);

		//update lazy evaluation of condition codes register
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update,LZE_ADDC_OP, tReg1, tReg2, tReg3 );
		//target->gen_assemble_lazyEv_param( LZE_ADDC_OP, tReg1, tReg2, tReg3);

		target->gen_add(tReg1, tReg1, tReg2); // add
		target->gen_add(tReg1, tReg1, tReg3); // Add with C
		target->gen_st8(A, tReg1); // Store A

		zprintf("\tADDC A, R%d\n\n", Rn);
		break;
	}
}
void C8051Arch::fineDecode_0x4(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, tmp2;
	uint16_t newPC;

	switch(subOp) {
	case 0	:// JC

		tmp1 = FETCH;			//get jump offset
		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored


		target->gen_ld8(tReg1, PSW);
		target->gen_ld_bit(tReg1, tReg1, CY_POS);
		target->gen_cjei(tReg1, 1, tmp1);	//target->generate compare jump equal with tReg2

		eoBB = true;

		zprintf("\tJC 0x%x\n\n", env.PC + (int8_t)tmp1);



	      	break;
	case 1	: // AJMP
	//	decode_ajmp_target->gen(op);
		tmp1 = FETCH;

		newPC = (env.PC & 0xF800) | 0x0200 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	    	target->gen_writePC(newPC);

	    	zprintf("\tAJMP 0x%04X\n\n", newPC);
		eoBB = true;

		break;
	case 2	:// ORL direct, A
		tmp1 = FETCH;
		target->gen_ld8(tReg1, tmp1); // load direct to tReg1
		target->gen_ld8(tReg2, A); // load A
		target->gen_or(tReg1, tReg2); // OR
		target->gen_st8(tmp1, tReg1);
		zprintf("\tORL 0x%02X, A\n\n", tmp1);
		break;
	case 3	: // ORL direct, #imm
		tmp1 = FETCH;
		tmp2 = FETCH;
		target->gen_ld8(tReg1, tmp1); // load direct to tReg1
		target->gen_movi(tReg2, tmp2); // load #imm
		target->gen_or(tReg1, tReg2); // OR
		target->gen_st8(tmp1, tReg1);
	  	zprintf("\tORL 0x%02X, #0x%02X\n\n", tmp1, tmp2);
		break;
	case 4	: // ORL A, #imm
		tmp1 = FETCH;
		target->gen_ld8(tReg1, A); // load direct to tReg1
		target->gen_movi(tReg2, tmp1); // load #imm
		target->gen_or(tReg1, tReg2); // OR
		target->gen_st8(A, tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tORL A, #0x%02X\n\n", tmp1);
		break;
	case 5	: // ORL A, direct
		tmp1 = FETCH;
		target->gen_ld8(tReg1, tmp1); // load direct to tReg1
		target->gen_ld8(tReg2, A); // load A
		target->gen_or(tReg2, tReg1); // OR
		target->gen_st8(A, tReg2);
		//target->gen_helper_update_parity();
		zprintf("\tORL A, 0x%02X\n\n", tmp1);
		break;
	case 6	:
	case 7	: // ORL A, @Ri
	  	target->gen_ld8(tReg2, subOp&0x01);
		target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
		target->gen_ld8(tReg2, A); // load A
		target->gen_or(tReg2, tReg1); // OR
		target->gen_st8(A, tReg2);
		//target->gen_helper_update_parity();
		zprintf("\tORL A, @R%d\n\n", subOp&0x01);
		break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	:
	  	 // ORL A, Rn
		target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
		target->gen_ld8(tReg2, A);
		target->gen_or(tReg1, tReg2);
		//check if order of parameter are inverted
		target->gen_st8(A, tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tORL A, R%d\n\n", Rn);
		break;
	}
}
void C8051Arch::fineDecode_0x5(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, tmp2;
	uint16_t newPC;

	switch (subOp) {
	case 0	:// JNC
//		tmp1 = FETCH; // get relative address
//
//		target->gen_ld8(tReg1, PSW); // load register
//		target->gen_movi(tReg2, 0x80);
//		target->gen_and(tReg2, tReg1, tReg2);
//
//		target->gen_movi(tReg1, 0x80);
//		target->gen_cjne(tReg1, tReg2, tmp1);
		tmp1 = FETCH;			//get jump offset

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

//	  	target->gen_ld_bit( tReg1, CY_BIT);	//get bit
		target->gen_ld8(tReg1, PSW);
		target->gen_ld_bit(tReg1, tReg1, CY_POS);

		//target->gen_movi(tReg2, 1);
		target->gen_cjnei(tReg1, 1, tmp1);	//target->generate compare jump NOT equal with tReg2

		eoBB = true;

		zprintf("\tJNC 0x%x\n\n", env.PC + (int8_t)tmp1);
	  	break;
	case 1	: // ACALL

		tmp1 = FETCH;	//read the page offset first, before storing PC in stack

		newPC = (env.PC & 0xF800) | 0x0200 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

	    	zprintf("\tACALL 0x%04X\n\n", newPC);

	  	break;
	case 2	: // ANL direct, A
		tmp1 = FETCH;
		target->gen_ld8(tReg1, tmp1); // load
		target->gen_ld8(tReg2, A); // load A
		target->gen_and(tReg1, tReg2); // AND
		target->gen_st8(tmp1 , tReg1);
		zprintf("\tANL 0x%02X, A\n\n", tmp1);
	  	break;
	case 3	:// ANL direct, #imm
		tmp1 = FETCH;
		tmp2 = FETCH;
		target->gen_ld8(tReg1, tmp1); // load
		target->gen_movi(tReg2, tmp2); // load #imm to register
		target->gen_and(tReg1, tReg2); // AND A, A, Rn
		target->gen_st8(tmp1 , tReg1);
		zprintf("\tANL 0x%02X, #0x%02X\n\n", tmp1, tmp2);
	  	break;
	case 4	: // ANL A, #imm
		tmp1 = FETCH;
		target->gen_ld8(tReg1, A); // load  A
		target->gen_movi(tReg2, tmp1); // load #imm to register
		target->gen_and(tReg1, tReg2); // AND A, A, Rn
		target->gen_st8(A , tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tANL A, #0x%02X\n\n", tmp1);
	  	break;
	case 5	: // ANL A, direct
		tmp1 = FETCH;
		target->gen_ld8(tReg1, A); // load  A
		target->gen_ld8(tReg2, tmp1); // load from address
		target->gen_and(tReg1, tReg2); // AND A, A, Rn
		target->gen_st8(A , tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tANL A, 0x%02X\n\n", tmp1);
	  	break;
	case 6	:
	case 7	: // ANL A, @Ri
		//target->gen_helper_orl_anl_xrl_indirect(tcg_const(d&0x1), tcg_const(1)); // 0 = orl, 1 = anl
		target->gen_ld8(tReg2, subOp&0x01);
	  	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
		target->gen_ld8(tReg2, A); // load A
		target->gen_and(tReg2, tReg1); // OR
		target->gen_st8(A, tReg2);
		//target->gen_helper_update_parity();
		zprintf("\tANL A, @R%d\n\n", subOp&0x01);
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // ANL A, Rn
		target->gen_ld8(tReg1, Rn); // load Rn to tReg1
		target->gen_ld8(tReg2, A); // load A
		target->gen_and(tReg1, tReg2); // AND A, A, Rn
		target->gen_st8(A , tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tANL A, R%d\n\n", Rn);
	  	break;
	}
}
void C8051Arch::fineDecode_0x6(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, tmp2;
	uint16_t newPC;

	switch (subOp) {
	case 0	://JZ
		tmp1 = FETCH; // get relative address

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

		target->gen_ld8(tReg1, A);

		target->gen_cjei(tReg1, 0, tmp1);

		eoBB = true;

		zprintf("\tJZ 0x%x\n\n", env.PC + (int8_t)tmp1);
	  	break;
	case 1	: // AJMP
	//	decode_ajmp_target->gen(op);

		tmp1 = FETCH;

		newPC = (env.PC & 0xF800) | 0x0300 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	    	target->gen_writePC(newPC);

	    	zprintf("\tAJMP 0x%04X\n\n", newPC);
		eoBB = true;

		break;
	case 2	:
		tmp1 = FETCH;
		target->gen_ld8(tReg1, tmp1); // load direct address to tReg1
		target->gen_ld8(tReg2, A); // load A
		target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
		target->gen_st8(tmp1 , tReg1);
		//target->gen_helper_update_parity();
		zprintf("\t??????\n\n");
	  	break;
	case 3	: // XRL direct, #imm
		tmp1 = FETCH;
		tmp2 = FETCH;
		target->gen_ld8(tReg1, tmp1); // load
		target->gen_movi(tReg2, tmp2); // load #imm to register
		target->gen_xor(tReg1, tReg2); // XOR direct, #imm
		target->gen_st8(tmp1 , tReg1);
		zprintf("\tXRL 0x%02X, #0x%02X\n\n", tmp1, tmp2);
	  	break;
	case 4	: // XRL A, #imm
		tmp1 = FETCH;
		target->gen_ld8(tReg1, A); // load  A
		target->gen_movi(tReg2, tmp1); // load #imm to register
		target->gen_xor(tReg1, tReg2); // XOR A, #imm
		target->gen_st8(A , tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tXRL 0x%02X\n\n", tmp1);
	  	break;
	case 5	: // XRL A, direct
		tmp1 = FETCH;
		target->gen_ld8(tReg1, A); // load  A
		target->gen_ld8(tReg2, tmp1); // load from address
		target->gen_xor(tReg1, tReg2); // XOR A, A, direct
		target->gen_st8(A , tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tXRL A, 0x%02X\n\n", tmp1);
	  	break;
	case 6	:
	case 7	: // XRL A, @Ri
		//target->gen_helper_orl_anl_xrl_indirect(tcg_const(d&0x1), tcg_const(2)); // 0 = orl, 1 = anl, 2 = xrl
		target->gen_ld8(tReg2, subOp&0x01);
	  	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
		target->gen_ld8(tReg2, A); // load A
		target->gen_xor(tReg2, tReg1); // OR
		target->gen_st8(A, tReg2);
		//target->gen_helper_update_parity();
		zprintf("\tXRL A, @R%d\n\n", subOp&0x01);
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // XRL A, Rn
		target->gen_ld8(tReg1, Rn); // load Rn to tReg1
		target->gen_ld8(tReg2, A); // load A
		target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
		target->gen_st8(A , tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tXRL A, R%d\n\n", Rn);
	  	break;
	}
}
void C8051Arch::fineDecode_0x7(uint8_t subOp, uint8_t Rn){
	 uint8_t tmp1, tmp2, byteAddr;
	 uint16_t newPC;

	 switch (subOp) {
	case 0	://JNZ
		tmp1 = FETCH; // get relative address

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

		target->gen_ld8(tReg1, A);
		//target->gen_movi(tReg2, 0);


		target->gen_cjnei(tReg1,0, tmp1); //???check execution, before was target->gen_cjne, but I think was a bug

		eoBB = true;

		zprintf("\tJNZ 0x%x\n\n", env.PC + (int8_t)tmp1);
	  	break;
	case 1	: // ACALL

		tmp1 = FETCH;	//read the page offset first, before storing PC in stack

		newPC = (env.PC & 0xF800) | 0x0300 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

	    	zprintf("\tACALL 0x%04X\n\n", newPC);

	  	break;
	case 2	: // ORL C, bit
		tmp1 = FETCH;
//		get_real_bit_addr(&tmp1, &tmp2);
//		target->gen_ld8(tReg1, tmp1); // load register
//		target->gen_movi(tReg2, 0x01);
//		target->gen_shli(tReg2, tReg2, tmp2); //
//		target->gen_and(tReg1, tReg1, tReg2);
//		target->gen_shli(tReg1, tReg1, 7-tmp2); //

		byteAddr = (tmp1 < 128 )	?	32 + (tmp1 >> 3)	: //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 						tmp1 & 0xF8		; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit

		target->gen_ld8(tReg2, PSW);
		target->gen_ld_bit(tReg2, tReg3, CY_POS );

		target->gen_or(tReg1, tReg3);
		target->gen_st_bit(tReg1, tReg2, CY_POS);
		target->gen_st8(PSW, tReg2); // save to PSW

		zprintf("\tORL C, 0x%02X\n\n", tmp1);
	  	break;
	case 3	: // JMP @A+DPTR

		target->gen_ld8(tReg1, A);
		target->gen_ld16(tReg2, DPL);
		target->gen_add(tReg1, tReg1, tReg2);

		//target->gen_movi(tReg2, (int)env.dataMem  );

		target->gen_writePCreg(tReg1);

		eoBB = true;
		zprintf("\tJMP @A+DPTR\n\n");
	  	break;
	case 4	:  //MOV A, #im
		tmp1 = FETCH;
		target->gen_movi(tReg1, tmp1);
		target->gen_st8(A, tReg1);
		//target->gen_helper_update_parity();
		zprintf("\tMOV A, #0x%02X\n\n", tmp1);
	  	break;
	case 5	:  // MOV direct, #imm
		tmp1 = FETCH;
		tmp2 = FETCH;
		target->gen_movi(tReg1, tmp2); // move #imme to temp TCG register
		target->gen_st8(tmp1, tReg1);
		zprintf("\tMOV 0x%02X, #0x%02X\n\n", tmp1, tmp2);
	  	break;
	case 6	:
	case 7	: //MOV @Ri,#data
		tmp1 = FETCH;

		target->gen_movi(tReg1, tmp1);
		target->gen_ld8(tReg2, subOp&0x01);
		//target->gen_sti8(Rn, tReg2, tReg3);
		target->gen_sti8(tReg1, MEM_BASE, tReg2);
		zprintf("\tMOV @R%d, #0x%02X\n\n", subOp&0x01, tmp1);
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // MOV Rn, #data
		tmp1 = FETCH;
		//zprintf("imediato d%d x%x\n",tmp1, tmp1);
		target->gen_movi(tReg1, tmp1);
		target->gen_st8(Rn, tReg1);
		zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
	  	break;
	}
}
void C8051Arch::fineDecode_0x8(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, tmp2, byteAddr;
	uint16_t newPC;

	switch (subOp) {
	case 0	:// SJMP
		tmp1 = FETCH;
//		if((tmp1&0x80)==0)
//			pc = tmp1;
//		else
//			pc = tmp1|0xFFFFFF00;
		if (tmp1 > 127)
			tmp1 |=  0xFFFFFF00;


		target->gen_writePC( (uint16_t)((int)env.PC + (int8_t)tmp1));

		eoBB = true;

		zprintf("\tSJMP 0x%x\n\n", env.PC + (int8_t)tmp1);
	  	break;
	case 1	: // AJMP
	//	decode_ajmp_target->gen(op);
		tmp1 = FETCH;

		newPC = (env.PC & 0xF800) | 0x0400 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	    	target->gen_writePC(newPC);

	    	zprintf("\tAJMP 0x%04X\n\n", newPC);
		eoBB = true;

		break;
	case 2	: // ANL C, bit
		tmp1 = FETCH;
////		get_real_bit_addr(&tmp1, &tmp2);
////		target->gen_ld8(tReg1, tmp1); // load register
////		target->gen_movi(tReg2, 0x01);
////		target->gen_shli(tReg2, tReg2, tmp2);
////		target->gen_and(tReg1, tReg1, tReg2);
////		target->gen_shli(tReg1, tReg1, 7-tmp2);
////		target->gen_ori(tReg1, tReg1, 0x7F);

//		target->gen_ld_bit(tReg1, tmp1);
//		target->gen_shli(tReg1, tReg1, 7);
//		target->gen_ori(tReg1, tReg1, 0x7F);
//
//		target->gen_ld8(tReg2, PSW);
//		target->gen_and(tReg1, tReg1, tReg2);
//		target->gen_st8(PSW, tReg1); // save to PSW

		byteAddr = (tmp1 < 128 ) ?	32 + (tmp1 >> 3) : //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 					tmp1 & 0xF8	 ; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit

		target->gen_ld8(tReg2, PSW);
		target->gen_ld_bit(tReg2, tReg3, CY_POS );

		target->gen_and(tReg1, tReg3);
		target->gen_st_bit(tReg1, tReg2, CY_POS);
		target->gen_st8(PSW, tReg2); // save to PSW

		zprintf("\tANL C, 0x%02X\n\n", tmp1);
	  	break;
	case 3	: // MOVC A, @A+PC

	  	target->gen_ld8(tReg1, A);
		target->gen_movi(tReg2, env.PC);
		target->gen_add(tReg1, tReg1, tReg2);

		target->gen_movi(tReg2, (int)pSourceProgMem );
		target->gen_ldi8(tReg1, tReg2, tReg1 );
		target->gen_st8( A, tReg1 );

		zprintf("\tMOVC A, @A+PC\n\n");
	  	break;

	case 4	: // DIV AB	(unsigned division)
		/* clear C, OV if DIV by ZERO */

	  	target->gen_ld8(tReg1, A);
		target->gen_ld8(tReg2, B);

		target->gen_ld8(tReg3, PSW);
		target->gen_andi(tReg3, tReg3, 0x7B);

		target->gen_cmpi( tReg2, 0);		//if division by zero is attempted
		target->gen_it( IT_EQ, IT_TTEE);	//THEN
		  target->gen_ori(tReg3, tReg3, 0x04); 	//set Overflow flag to 1
		  target->gen_st8(PSW, tReg3);

		  target->gen_st8(PSW, tReg3); 		//ELSE
		  target->gen_div(tReg3, tReg1, tReg2);

		target->gen_st8(A, tReg3);

		target->gen_mul(tReg2, tReg3 );		//multiply the result with the divisor
		target->gen_sub(tReg3, tReg1, tReg2);


		target->gen_st8(B, tReg3);

		zprintf("\tDIV AB\n\n");
	  	break;
	case 5	: //MOD IRAM ADDR, IRAM ADDR
		tmp1 = FETCH; // get direct address
		tmp2 = FETCH; // get direct address
		target->gen_ld8(tReg1, tmp1);
		target->gen_st8(tmp2, tReg1);
		zprintf("\tMOV %d, %d\n", tmp2, tmp1);
	  	break;
	case 6	:
	case 7	: // MOV direct, @Ri
		tmp1 = FETCH;

		target->gen_ld8(tReg2, subOp&0x01 );
		target->gen_ldi8(tReg1, MEM_BASE, tReg2 );
		target->gen_st8(tmp1, tReg1);
		zprintf("\tMOV 0x%02X, @R%d\n\n", tmp1, subOp&0x01);
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // ox88 to 0x8F is : MOV direct, Rn
		tmp1 = FETCH; // get direct address
		target->gen_ld8(tReg1, Rn);
		target->gen_st8(tmp1, tReg1);
		zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
	  	break;
	}
}
void C8051Arch::fineDecode_0x9(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, byteAddr;
	uint16_t tmp3;
	uint16_t newPC;

		switch (subOp) {
	case 0	:  // MOV DPTR, #imm
		tmp3 = FETCH;
		tmp3 <<= 8;
		tmp3 |= FETCH;
		target->gen_movi(tReg1, tmp3);
		target->gen_st16(DPL, tReg1);
		zprintf("\tMOV DPTR, #0x%x\n\n", tmp3);
		break;
	case 1	: // ACALL

		tmp1 = FETCH;	//read the page offset first, before storing PC in stack


		newPC = (env.PC & 0xF800) | 0x0400 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

	    	zprintf("\tACALL 0x%04X\n\n", newPC);

	  	break;
	case 2	:  // MOV bit, C
		tmp1 = FETCH;

		target->gen_ld8(tReg1, PSW); // load PSW
		//target->gen_shri(tReg1, tReg1, 7);
		target->gen_ld_bit(tReg1, tReg1, CY_POS);

		byteAddr = (tmp1 < 128 ) ?	32 + (tmp1 >> 3) : //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 					tmp1 & 0xF8	 ; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg2, byteAddr);

		target->gen_st_bit( tReg1, tReg2, tmp1&0x07);	//get bit
		target->gen_st8(byteAddr, tReg2);

//		target->gen_st_bit(tReg1, tReg2, tmp1);


//		get_real_bit_addr(&tmp1, &tmp2);
//		target->gen_ld8(tReg1, tmp1); // load register
//		target->gen_movi(tReg2, 0x01);
//		target->gen_shli(tReg2, tReg2, tmp2);
//		target->gen_not(tReg2, tReg2);
//		target->gen_and(tReg1, tReg1, tReg2);
//
//		target->gen_ld8(tReg2, PSW); // load PSW
//		target->gen_andi(tReg2, tReg2, 0x80);
//		target->gen_shri(tReg2, tReg2, 7-tmp2);
//		target->gen_or(tReg1, tReg2);
//		target->gen_st8(tmp1, tReg1);

		zprintf("\tMOV 0x%02X, C\n\n", tmp1);
	  	break;
	case 3	: // MOVC A,@A+DPTR

	  	target->gen_ld8(tReg1, A);
		target->gen_ld16(tReg2, DPL);
		target->gen_add(tReg1, tReg1, tReg2);

		target->gen_movi(tReg2, (int)pSourceProgMem  );
		target->gen_ldi8(tReg1, tReg2, tReg1 );
		target->gen_st8( A, tReg1 );

		zprintf("\tMOVC A, @A+DPTR\n\n");
	  	break;
	case 4	: // SUBB A, #imm
		tmp1 = FETCH;
		target->gen_ld8(tReg1, A);
		target->gen_movi(tReg2, tmp1);

		target->gen_ld8(tReg3, PSW);
		target->gen_ld_bit(tReg3, tReg3, CY_POS);

		//update lazy evaluation of condition codes register
		//target->gen_assemble_lazyEv_param( LZE_SUBB_OP, tReg1, tReg2, tReg3);
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update,LZE_SUBB_OP, tReg1, tReg2, tReg3 );

		target->gen_sub(tReg1, tReg1, tReg2);
		target->gen_sub(tReg1, tReg1, tReg3);
		target->gen_st8(A, tReg1); // Store A

		zprintf("\tMUST REVIEW\nSUBB A, #0x%02X\n\n", tmp1);
	  	break;
	case 5	: // SUBB A, direct
		tmp1 = FETCH;
		target->gen_ld8(tReg1, A); // load A
		target->gen_ld8(tReg2, tmp1);

		target->gen_ld8(tReg3, PSW);
		target->gen_ld_bit(tReg3, tReg3, CY_POS);

		//update lazy evaluation of condition codes register
		//target->gen_assemble_lazyEv_param( LZE_SUBB_OP, tReg1, tReg2, tReg3);
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update,LZE_SUBB_OP, tReg1, tReg2, tReg3 );

		target->gen_sub(tReg1, tReg1, tReg2);
		target->gen_sub(tReg1, tReg1, tReg3);
		target->gen_st8(A, tReg1); // Store A

		zprintf("\tMUST REVIEW\nSUBB A, 0x%02X\n\n", tmp1);
	  	break;
	case 6	:
	case 7	: // SUBB A, @Ri

	  	target->gen_ld8(tReg1,	subOp&0x01);
	  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

		target->gen_ld8(tReg1, A);

		target->gen_ld8(tReg3, PSW);
		target->gen_ld_bit(tReg3, tReg3, CY_POS);

		//update lazy evaluation of condition codes register
		//target->gen_assemble_lazyEv_param( LZE_SUBB_OP, tReg1, tReg2, tReg3);
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update,LZE_SUBB_OP, tReg1, tReg2, tReg3 );

		target->gen_sub(tReg1, tReg1, tReg2); // sub
		target->gen_sub(tReg1, tReg1, tReg3); // sub with C
		target->gen_st8(A, tReg1); // Store A

		zprintf("\tMUST REVIEW\nSUBB A, #@R%d\n\n", subOp&0x01);
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // SUBB A, Rn
	  	target->gen_ld8(tReg1, A); // load A
		target->gen_ld8(tReg2, Rn); // load Rn

		target->gen_ld8(tReg3, PSW);
		target->gen_ld_bit(tReg3, tReg3, CY_POS);

		//update lazy evaluation of condition codes register
		//target->gen_assemble_lazyEv_param( LZE_SUBB_OP, tReg1, tReg2, tReg3);
		target->gen_helper(&CTargetArchitecture::CC_onDemand_Update,LZE_SUBB_OP, tReg1, tReg2, tReg3 );

		target->gen_sub(tReg1, tReg1, tReg2); // sub
		target->gen_sub(tReg1, tReg1, tReg3); // sub with C
		target->gen_st8(A, tReg1); // Store A

		zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
	  	break;
	}
}
void C8051Arch::fineDecode_0xa(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, byteAddr;
	uint16_t newPC;

	switch (subOp) {
	case 0	: // ORL C,/bit addr
		tmp1 = FETCH;

//		target->gen_ld_bit(tReg1, tmp1);

//		get_real_bit_addr(&tmp1, &tmp2);
//		target->gen_ld8(tReg1, tmp1); // load register
//		target->gen_not(tReg1, tReg1);
//		target->gen_movi(tReg2, 0x01);
//		target->gen_shli(tReg2, tReg2, tmp2); //
//		target->gen_and(tReg1, tReg1, tReg2);
//		target->gen_shli(tReg1, tReg1, 7-tmp2); //

		byteAddr = (tmp1 < 128 ) ?	32 + (tmp1 >> 3) : //if bit7 is clear, bit belongs to bit addressable area (base 32)
						tmp1 & 0xF8	 ; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit

		target->gen_not(tReg1, tReg1);

		target->gen_ld8(tReg2, PSW );
		target->gen_ld_bit(tReg2, tReg3, CY_POS);

//		target->gen_andi(tReg3, tReg1, 1);
//		target->gen_shli(tReg1, tReg1, 7);
//
//		target->gen_ld8(tReg2, PSW);
		target->gen_or(tReg1, tReg3);
		target->gen_st_bit(tReg1, tReg2, CY_POS);
		target->gen_st8(PSW, tReg2); // save to PSW
		zprintf("\tORL C, XXX\n\n");
		break;
	case 1	: // AJMP
	//	decode_ajmp_target->gen(op);
		tmp1 = FETCH;

		newPC = (env.PC & 0xF800) | 0x0500 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	    	target->gen_writePC(newPC);

	    	zprintf("\tAJMP 0x%04X\n\n", newPC);
		eoBB = true;

		break;
	case 2	: // MOV C, bit
		tmp1 = FETCH;

		byteAddr = (tmp1 < 128 ) ?	32 + (tmp1 >> 3) : //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 				tmp1 & 0xF8	 ; //if bit7 is set, bit belongs to SFR area (base 1228)


		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit

		target->gen_ld8(tReg2, PSW);

		target->gen_st_bit(tReg1, tReg2, CY_POS);

		target->gen_st8(PSW, tReg2);

////		target->gen_ld_bit(tReg1, tmp1);
////		target->gen_shli(tReg1, tReg1, 7);
//
////		get_real_bit_addr(&tmp1, &tmp2);
////		target->gen_ld8(tReg1, tmp1); // load register
////		target->gen_movi(tReg2, 0x01);
////		target->gen_shli(tReg2, tReg2, tmp2); //
////		target->gen_and(tReg1, tReg1, tReg2); //
////		target->gen_shli(tReg1, tReg1, 7 - tmp2);
//
//		target->gen_ld8(tReg2, PSW);
//		target->gen_andi(tReg2, tReg2, 0x7F);
//		target->gen_or(tReg1, tReg2);
//		target->gen_st8(PSW, tReg1); // save to PSW
		zprintf("\tMOV C, 0x%02x.%d\n\n", byteAddr, tmp1&0x07);
	  	break;
	case 3	: // INC DPTR
		target->gen_ld16(tReg1, DPL);
		target->gen_addi(tReg1, 1);

		target->gen_st16(DPL, tReg1); // save dpl + dph

		zprintf("\tINC DPTR\n\n");
	  	break;
	case 4	: // MUL AB
		target->gen_ld8(tReg1, A); // get A
		target->gen_ld8(tReg2, B); // get B
		target->gen_mul(tReg1, tReg2);

		target->gen_st8(A, tReg1); // save to A
		target->gen_shri(tReg1, tReg1, 8);
		target->gen_st8(B, tReg1); // save B

		target->gen_ld8(tReg2, PSW); // get psw
		target->gen_andi(tReg2, tReg2, 0x7B); // clear carry and OV

		target->gen_movi(tReg3, 0);
		target->gen_cmp(tReg1, tReg3);
		target->gen_it( IT_NEQ, IT_T);		//if not equal (!= 0) then
		target->gen_ori( tReg2, tReg2, 0x04 );	//set carry

		target->gen_st8(PSW, tReg2); // save PSW

		zprintf("\tMUL AB\n\n");
	  	break;
	case 5	: //UNDEFINED INSTRUCTION
	  	zprintf("\tUNDEFINED INSTRUCTION \n\n");
	  	break;
	case 6	:
	case 7	: // MOV @Ri, direct
		tmp1 = FETCH;
		//target->gen_helper_mov_indirect(tcg_const(d&0x01), tcg_const(b), tcg_const(2));
		target->gen_ld8(tReg1, tmp1);
		target->gen_ld8(tReg2, subOp&0x01);
		//target->gen_sti8(subOp&0x01, tReg1, tReg2);
		target->gen_sti8(tReg1, MEM_BASE, tReg2);

		zprintf("\tMOV @Ri, 0x%x\n\n", subOp&0x01);
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // oxA8 to 0xAF is : MOV Rn, direct
		tmp1 = FETCH; // get direct address
		target->gen_ld8(tReg1, tmp1); // load data from direct address
		target->gen_st8(Rn, tReg1); // Store the value to Rn.
		zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
	  	break;
	}
}
void C8051Arch::fineDecode_0xb(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, tmp2, byteAddr;
  	uint16_t newPC;

	switch (subOp) {
	case 0 : // ANL C, /bit
		tmp1 = FETCH;

////		get_real_bit_addr(&tmp1, &tmp2);
////		target->gen_ld8(tReg1, tmp1); // load register
////		target->gen_not(tReg1, tReg1);
////		target->gen_movi(tReg2, 0x01);
////		target->gen_shli(tReg2, tReg2, tmp2);
////		target->gen_and(tReg1, tReg1, tReg2);
////		target->gen_shli(tReg1, tReg1, 7-tmp2);
////		target->gen_ori(tReg1, tReg1, 0x7F);
//
//		target->gen_ld_bit(tReg1, tmp1);
//		target->gen_shli(tReg1, tReg1, 7);
//		target->gen_not(tReg1, tReg1);
//
//
//		target->gen_ld8(tReg2, PSW);
//		target->gen_and(tReg1, tReg1, tReg2);
//		target->gen_st8(PSW, tReg1); // save to PSW

		byteAddr = (tmp1 < 128 ) ?	32 + (tmp1 >> 3) : //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 					tmp1 & 0xF8	 ; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit

		target->gen_not(tReg1, tReg1);

		target->gen_ld8(tReg2, PSW );
		target->gen_ld_bit(tReg2, tReg3, CY_POS);

		target->gen_and(tReg1, tReg3);
		target->gen_st_bit(tReg1, tReg2, CY_POS);
		target->gen_st8(PSW, tReg2); // save to PSW

		zprintf("\t??????NYV??????ANL C, /%d\n\n", tmp1);

		break;
	case 1	: // ACALL

		tmp1 = FETCH;	//read the page offset first, before storing PC in stack

		newPC = (env.PC & 0xF800) | 0x0500 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

	    	zprintf("\tACALL 0x%04X\n\n", newPC);

	  	break;
	case 2 : // CPL bit
		tmp1 = FETCH;

//		get_real_bit_addr(&tmp1, &tmp2);
//		target->gen_ld8(tReg1, tmp1); // load register
//		target->gen_mov(tReg3, tReg1); // backup
//		target->gen_not(tReg1, tReg1); // cpl
//		target->gen_movi(tReg2, 0x01);
//		target->gen_shli(tReg2, tReg2, tmp2);
//		target->gen_and(tReg1, tReg1, tReg2); // keep only the bit.

//		target->gen_not(tReg2, tReg2);
//		target->gen_and(tReg3, tReg3, tReg2); // clear the bit
//		target->gen_or(tReg1, tReg3);
//
//		target->gen_st8(tmp1, tReg1); // save

		byteAddr = (tmp1 < 128 ) ?	32 + (tmp1 >> 3) : //if bit7 is clear, bit belongs to bit addressable area (base 32)
						tmp1 & 0xF8	 ; //if bit7 is set, bit belongs to SFR area (base 1228)

		target->gen_ld8(tReg1, byteAddr);
		target->gen_ld_bit( tReg1, tReg2, tmp1&0x07);	//get bit

		target->gen_not(tReg2, tReg2);

		target->gen_st_bit(tReg2, tReg1, tmp1&0x07);
		target->gen_st8(byteAddr, tReg1);

		zprintf("\t??????NYV??????CPL %d\n\n", tmp1);

		break;
	case 3 : // CPL C

		target->gen_ld8(tReg1, PSW);

		target->gen_ld_bit(tReg1, tReg2, CY_POS);
		target->gen_not(tReg2, tReg2);
		target->gen_st_bit(tReg2, tReg1, CY_POS);

//		target->gen_mov(tReg2, tReg1);
//		target->gen_not(tReg1, tReg1);
//		target->gen_andi(tReg1, tReg1, 0x80);
//		target->gen_andi(tReg2, tReg2, 0x7F);
//		target->gen_or(tReg1, tReg2);
		target->gen_st8(PSW, tReg1);

		zprintf("\t??????NYV??????'CPL C\n\n");

		break;
	case 4 : // CJNE A, #imm
		tmp1 = FETCH; // get #imm
		tmp2 = FETCH; // get relative address

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is taken, on next execution the PC will be restored

		target->gen_ld8(tReg1, A); // Load Rn
		target->gen_movi(tReg2, tmp1); // Load Rn

		target->gen_sub(tReg3, tReg1, tReg2);		//target->generate the C
		target->gen_shri(tReg3, tReg3, 8);
		target->gen_ld8(tReg1, PSW);
		target->gen_st_bit(tReg3, tReg1, CY_POS);
		target->gen_st8(PSW, tReg1);

		target->gen_ld8(tReg1, A); // Load Rn

		target->gen_cjne(tReg1, tReg2, tmp2);
		eoBB = true;

		zprintf("\tCJNE A, #0x%02x\n\n", tmp1);
		break;
	case 5 : // CJNE A, direct
		tmp1 = FETCH; // get direct address
		tmp2 = FETCH; // get offset

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

		target->gen_ld8(tReg1, A); // Load Rn
		target->gen_ld8(tReg2, tmp1); // Load Rn

		target->gen_sub(tReg3, tReg1, tReg2);		//target->generate the C
		///changed sh left to sh right!
		target->gen_shri(tReg3, tReg3, 8);
		target->gen_ld8(tReg1, PSW);
		target->gen_st_bit(tReg3, tReg1, CY_POS);
		//tReg1!!! not tReg3
		target->gen_st8(PSW, tReg1);

		target->gen_ld8(tReg1, A); // Load Rn

		target->gen_cjne(tReg1, tReg2, tmp2);
		eoBB = true;

		zprintf("\tCJNE A, #0x%x\n\n", tmp1);
		break;
	case 6 :
	case 7 : // CJNE @Ri, #imm
		tmp1 = FETCH; // get #imm
		tmp2 = FETCH; // get relative address

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

		target->gen_ld8(tReg2, subOp&0x01 );
		target->gen_ldi8(tReg1, MEM_BASE, tReg2);	// Load
		target->gen_movi(tReg2, tmp1);

		target->gen_sub(tReg3, tReg1, tReg2);		//target->generate the C
		target->gen_shri(tReg3, tReg3, 8);
		target->gen_ld8(tReg2, PSW);
		target->gen_st_bit(tReg3, tReg2, CY_POS);
		target->gen_st8(PSW, tReg1);

		target->gen_movi(tReg2, tmp1);			//load again value from #imm

		target->gen_cjne(tReg1, tReg2, tmp2);
		eoBB = true;

		zprintf("\tCJNE @R%d, #0x%02x\n\n",subOp&0x01, tmp1);
		break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // CJNE Rn, #imm
		tmp1 = FETCH; // get #imm
		tmp2 = FETCH; // get relative address

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

		target->gen_ld8(tReg1, Rn); // Load Rn
		target->gen_movi(tReg2, tmp1);

		target->gen_sub(tReg3, tReg1, tReg2);		//target->generate the C
		target->gen_shri(tReg3, tReg3, 8);
		target->gen_ld8(tReg1, PSW);
		target->gen_st_bit(tReg3, tReg1, CY_POS);
		target->gen_st8(PSW, tReg1);

		target->gen_ld8(tReg1, Rn); // Load Rn

		target->gen_cjne(tReg1, tReg2, tmp2);
		eoBB = true;

		zprintf("\tCJNE R%d, #0x%02x\n\n",Rn, tmp1);
	  	break;
	}
}
void C8051Arch::fineDecode_0xc(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, byteAddr;
	uint16_t newPC;

	switch (subOp) {
	case 0 : // push
		tmp1 = FETCH;
		target->gen_ld8(tReg1, SP);
		target->gen_addi(tReg1, 1); // SP + 1;
		target->gen_st8( SP, tReg1);

		target->gen_ld8(tReg2, tmp1); // load
		target->gen_sti8(tReg2, MEM_BASE, tReg1);


		zprintf("\t???????NYV?????????PUSH\n\n");
		break;
	case 1	: // AJMP
	//	decode_ajmp_target->gen(op);

		tmp1 = FETCH;

		newPC = (env.PC & 0xF800) | 0x0600 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	    	target->gen_writePC(newPC);

	    	zprintf("\tAJMP 0x%04X\n\n", newPC);
		eoBB = true;

		break;
	case 2 : // CLR bit
		tmp1 = FETCH;
//			get_real_bit_addr(&tmp1, &tmp2);
//			target->gen_ld8(tReg1, tmp1); // load register
//			target->gen_movi(tReg3, 0x01);
//			target->gen_shli(tReg3, tReg3, tmp2);
//			target->gen_not(tReg3, tReg3);
//			target->gen_and(tReg1, tReg1, tReg3);
//			target->gen_st8(tmp1, tReg1);	 // save back

		byteAddr = (tmp1 < 128 ) ?	32 + (tmp1 >> 3) : //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 				tmp1 & 0xF8	 ; //if bit7 is set, bit belongs to SFR area (base 1228)
		target->gen_ld8(tReg1, byteAddr);

		target->gen_movi(tReg2, 0);

		target->gen_st_bit(tReg2, tReg1, tmp1&0x07);
		target->gen_st8(byteAddr, tReg1);

		zprintf("\tCLR bit %d\n\n",tmp1);
		break;
	case 3 : // CLR C
		target->gen_ld8(tReg1, PSW); // load PSW register
		target->gen_andi(tReg1, tReg1, 0x7F);
		target->gen_st8(PSW, tReg1);	 // save back

		zprintf("\tCLR C\n\n");
		break;
	case 4 : // SWAP A
		target->gen_ld8(tReg1, A);
		target->gen_shli(tReg2, tReg1, 4);
		target->gen_andi(tReg2, tReg2, 0xF0);


		target->gen_shri(tReg1, tReg1, 4);
		target->gen_andi(tReg1, tReg1, 0x0F);

		target->gen_or(tReg1, tReg2);
		target->gen_st8(A, tReg1);
		//target->gen_helper_update_parity();

		zprintf("\tSWAP A\n\n");
		break;
	case 5 : // XCH A, direct
		tmp1 = FETCH; // get direct address

		target->gen_ld8(tReg1, A);
		target->gen_ld8(tReg2, tmp1); // load data from direct address

		target->gen_st8(A, tReg2);
		target->gen_st8(tmp1, tReg1);
		//target->gen_helper_update_parity();

		zprintf("\tXCH A, 0x%x\n\n",tmp1);
		break;
	case 6 :
	case 7 :// XCH A, @Ri
		target->gen_ld8(tReg1, A);
		target->gen_ld8(tReg3, subOp&0x01 );
		target->gen_ldi8(tReg2, MEM_BASE, tReg3 ); // load data from direct address

		target->gen_st8(A, tReg2);
//		target->gen_sti8(subOp&0x01, tReg1, tReg2);
		target->gen_sti8(tReg1, MEM_BASE, tReg3);

		//target->gen_helper_update_parity();

		zprintf("\tXCH A, @R%d\n\n",subOp&0x01);
		break;
	case 8	:  // XCH A, Rn
	case 9	:  // XCH A, Rn
	case 10	:  // XCH A, Rn
	case 11	:  // XCH A, Rn
	case 12	:  // XCH A, Rn
	case 13	:  // XCH A, Rn
	case 14	:  // XCH A, Rn
	case 15	:  // XCH A, Rn
		target->gen_ld8(tReg1, Rn); // Load Rn.
		target->gen_ld8(tReg2, A); // Load A.
		target->gen_st8(A, tReg1); // Store the value to A.
		target->gen_st8(Rn, tReg2); // Store the value to Rn.
		//target->gen_helper_update_parity();

		zprintf("\tXCH A, R%d\n\n",Rn);
		break;
	}
}
void C8051Arch::fineDecode_0xd(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1, tmp2, byteAddr;
	uint16_t newPC;

	switch (subOp) {
	case 0	:  // pop
		tmp1 = FETCH;
		target->gen_ld8(tReg2, SP);
		target->gen_ldi8(tReg1, MEM_BASE, tReg2);
		target->gen_st8(tmp1, tReg1);

		//target->gen_ld8(tReg1, SP);
		//target->gen_sub(tReg1, tReg1, 1);
		//target->gen_st8(SP, tReg1);
		target->gen_subi(tReg2, 1);
		target->gen_st8(SP, tReg2);

		zprintf("\t????NYV???POP\n\n");
		break;
	case 1	: // ACALL

		tmp1 = FETCH;	//read the page offset first, before storing PC in stack

		newPC = (env.PC & 0xF800) | 0x0600 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

	    	zprintf("\tACALL 0x%04X\n\n", newPC);

	  	break;
	case 2	: // SETB bit.
		tmp1 = FETCH;

////		get_real_bit_addr(&tmp1, &tmp2);
////		target->gen_ld8(tReg1, tmp1); // load register
////		target->gen_movi(tReg3, 0x01);
////		target->gen_shli(tReg3, tReg3, tmp2); //
////		target->gen_or(tReg1, tReg3);
////		target->gen_st8(tmp1, tReg1);	 // save back
//
//	  	target->gen_movi(tReg2, 1);		//set bit
//		target->gen_st_bit(tReg2, tReg1, tmp1);
//

		byteAddr = (tmp1 < 128 ) ?	32 + (tmp1 >> 3) : //if bit7 is clear, bit belongs to bit addressable area (base 32)
		 					tmp1 & 0xF8	 ; //if bit7 is set, bit belongs to SFR area (base 1228)
		target->gen_ld8(tReg1, byteAddr);


		target->gen_movi(tReg2, 1);

		target->gen_st_bit(tReg2, tReg1, tmp1&0x07);
		target->gen_st8(byteAddr, tReg1);

		zprintf("\tSETB %d\n\n", tmp1);
	  	break;
	case 3	: // SETB C
		target->gen_ld8(tReg1, PSW); // load PSW register
		target->gen_ori(tReg1, tReg1, 0x80);
		target->gen_st8(PSW, tReg1);	 // save back

		zprintf("\tSETBC \n\n");
	  	break;
	case 4	: // DA
	  target->gen_helper(&CTargetArchitecture::helper_DA );
		//target->gen_helper_update_parity();
		zprintf("\tDA A\n\n");
	  	break;
	case 5	: // DJNZ direct, offset
		tmp1 = FETCH;	//direct address
		tmp2 = FETCH;	//jmp offset

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

		target->gen_ld8(tReg1, tmp1);
		target->gen_subi(tReg1, 1);
		target->gen_st8(tmp1, tReg1);

	//	target->gen_movi(tReg2, 0);

		target->gen_cjnei(tReg1, 0, tmp2);
		eoBB = true;

		zprintf("\tDJNZ %d, 0x%x\n\n",tmp1, env.PC + (int8_t)tmp2);
	  	break;
	case 6	:
	case 7	: // XCHD A, @Ri
		target->gen_ld8(tReg1, A);
		target->gen_ld8(tReg3, subOp&0x01 );
		target->gen_ldi8(tReg2, MEM_BASE, tReg3);

		target->gen_mov(tReg3, tReg1);
		target->gen_andi(tReg3, tReg3, 0xF0);
		target->gen_andi(tReg2, tReg2, 0x0F);
		target->gen_or(tReg2, tReg3);
		target->gen_st8(A, tReg2);

		target->gen_ld8(tReg3, subOp&0x01 );
		target->gen_ldi8(tReg2, MEM_BASE, tReg3);
		target->gen_andi(tReg1, tReg1, 0x0F);
		target->gen_andi(tReg2, tReg2, 0xF0);
		target->gen_or(tReg1, tReg2);
		//target->gen_sti8(subOp&0x01, tReg1, tReg2);
		target->gen_sti8(tReg1, MEM_BASE, tReg3);

		//target->gen_helper_update_parity();

		zprintf("\tXCH A, @R%d\n\n",subOp&0x01);
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	:// DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
		tmp1 = FETCH;

		target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

		target->gen_ld8(tReg1, Rn);
		target->gen_subi(tReg1, 1);
		target->gen_st8(Rn, tReg1);

//		target->gen_movi(tReg2, 0);

		target->gen_cjnei(tReg1, 0, tmp1);
		eoBB = true;
		zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
	  	break;
	}
}
void C8051Arch::fineDecode_0xe(uint8_t subOp, uint8_t Rn){
	unsigned tmp1;
	uint16_t newPC;

	switch (subOp) {
	case 0	: // MOVX A,@DPTR
// 		target->gen_helper_movx_A_indirect(2); // 0 = R0, 1 = R1, 2 = @DPTR
// 		target->gen_helper_update_parity();

	  	if (xMem == NULL){
	  		printf("EXTERNAL MEMORY NOT ALLOCATED\n\n");
			target->eoExec = 1;
			return;
	  	}
		else {
			target->gen_ld16(tReg1, DPL);
			target->gen_movi(tReg2, (uint32_t)xMem  );
			target->gen_ldi8(tReg1, tReg2, tReg1 );

			DEBUG_XMEM_ACCESS();

			target->gen_st8( A, tReg1 );
			zprintf("\tMOVX A, @DPTR\n\n");
		}

	  	break;
	case 1	: // AJMP
	//	decode_ajmp_target->gen(op);
		tmp1 = FETCH;

		newPC = (env.PC & 0xF800) | 0x0700 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	    	target->gen_writePC(newPC);

	    	zprintf("\tAJMP 0x%04X\n\n", newPC);
		eoBB = true;

		break;
	case 2	:
	case 3	: // MOVX A,@Ri

	  	if (xMem == NULL){
	  		printf("EXTERNAL MEMORY NOT ALLOCATED\n\n");
			target->eoExec = 1;
			return;
	  	}
		else {


			target->gen_ld8(tReg1, subOp&0x01);

			target->gen_movi(tReg2, (uint32_t)xMem  );
			target->gen_ldi8(tReg1, tReg2, tReg1 );

			DEBUG_XMEM_ACCESS();

			target->gen_st8( A, tReg1 );

			zprintf("\tMOVX A, @R%d\n\n", subOp&0x01);
		}

	  	break;
	case 4	: // CLR A
		target->gen_movi(tReg1, 0);
		target->gen_st8(A, tReg1); // Store the value to A.
		zprintf("\tCLR A\n\n");
		//target->gen_helper_update_parity();
	  	break;
	case 5	: // MOV A, direct
		tmp1 = FETCH;
		target->gen_ld8(tReg1, tmp1); // Load.
		target->gen_st8(A, tReg1); // Store the value to A.
		zprintf("\tMOV A, #0x%x\n\n", tmp1);
		//target->gen_helper_update_parity();
	  	break;
	case 6	:
	case 7	: // MOV A, @Ri
		//target->gen_helper_mov_indirect(tcg_const(d&0x01), tcg_const(0), tcg_const(3));
		target->gen_ld8(tReg2, subOp&0x01 );
	  	target->gen_ldi8(tReg1, MEM_BASE, tReg2);
		target->gen_st8(A, tReg1);
		zprintf("\tMOV A, @R%d\n\n", subOp&0x01);
		//target->gen_helper_update_parity();
	  	break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // 0xE8 to 0xEF : MOV A, Rn
		target->gen_ld8(tReg1, Rn); // Load Rn.
		target->gen_st8(A, tReg1); // Store the value to A.
		zprintf("\tMOV A, R%d\n\n", Rn);
	  	break;
	}
}
void C8051Arch::fineDecode_0xf(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1;
	uint16_t newPC;

	switch (subOp) {
	case 0 : // MOVX @DPTR, A

	  	if (xMem == NULL){
	  		printf("EXTERNAL MEMORY NOT ALLOCATED\n\n");
			target->eoExec = 1;
			return;
	  	}
		else {
			target->gen_ld8(tReg1, A);
			target->gen_ld16(tReg2, DPL);
			target->gen_movi(tReg3, (uint32_t)xMem  );

			DEBUG_XMEM_ACCESS();

			target->gen_sti8( tReg1, tReg3, tReg2);

			zprintf("\tMOVX @DPTR, A\n\n");
		}
	  	break;
	case 1	: // ACALL

		tmp1 = FETCH;	//read the page offset first, before storing PC in stack

		newPC = (env.PC & 0xF800) | 0x0700 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
	  	target->gen_helper(&CTargetArchitecture::helper_call);

		target->gen_writePC(newPC);

		//callCount++;
		eoBB = true;

	    	zprintf("\tACALL 0x%04X\n\n", newPC);

	  	break;
	case 2	:
	case 3	: // MOVX @Ri, A

	  	if (xMem == NULL){
	  		printf("EXTERNAL MEMORY NOT ALLOCATED\n\n");
			target->eoExec = 1;
			return;
	  	}
		else
		{

			target->gen_ld8(tReg1, A);
			target->gen_ld8(tReg2, subOp&0x01);
			target->gen_movi(tReg3, (uint32_t)xMem  );

			DEBUG_XMEM_ACCESS();

			target->gen_sti8( tReg1, tReg3, tReg2);

			zprintf("\tMOVX @R%d, A\n\n", subOp&0x01);
		}

		break;
	case 4	: // CPL A
		target->gen_ld8(tReg1, A); // Load register A.
		target->gen_not(tReg1, tReg1); // complement
		target->gen_st8(A, tReg1); // Store the value to A.
		//target->gen_helper_update_parity();
		zprintf("\tCPL A\n\n");
		break;
	case 5	: // MOV direct, A
		tmp1 = FETCH;
		target->gen_ld8(tReg1, A);
		target->gen_st8(tmp1, tReg1); // Load.
		zprintf("\tMOV 0x%x, A\n\n", tmp1);
		break;
	case 6	:
	case 7	: // MOV @Ri, A
		target->gen_ld8(tReg1, A);
		target->gen_ld8(tReg2, subOp&0x01);
		target->gen_sti8(tReg1, MEM_BASE, tReg2);
		zprintf("\tMOV @R%d, A\n\n",subOp&0x01);
		break;
	case 8	:
	case 9	:
	case 10	:
	case 11	:
	case 12	:
	case 13	:
	case 14	:
	case 15	: // MOV Rn, A
		target->gen_ld8(tReg1, A); // Load register A.
		target->gen_st8(Rn, tReg1); // Store the value to Rn.
		zprintf("\tMOV R%d, A\n\n", Rn);
	  	break;
	}
}



//extern CDBTEngine * globalTeste;
//
//
////void call_helper_CC_lazyEv()
////{ return (globalTeste)->helper_CC_lazyEv(); }
//
//void call_helper_CC_lazyEv_SNIFFER_BACKDOOR()
//{ return (globalTeste)->target.helper_CC_lazyEv_SNIFFER_BACKDOOR(); }
//
//
//void call_helper_debug(/*CDBTEngine* transPtr,*/ int soft_brkp_addr)
//{return (globalTeste)->target.helper_debug(soft_brkp_addr);}


/************ End Helper ****************/