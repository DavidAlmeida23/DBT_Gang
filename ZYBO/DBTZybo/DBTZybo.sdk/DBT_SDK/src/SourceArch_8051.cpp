#include "SourceArch_8051.h"
#include "TargetArch_CortexM3.h"



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

	static fineDecode JmpTable_v[NUM_Instructions];
	JmpTable = JmpTable_v;
	initJumpTable();


}


void C8051Arch::initJumpTable(){

	JmpTable[0] = &C8051Arch::fineDecode_0x0;
	JmpTable[1] = &C8051Arch::fineDecode_0x1;
	JmpTable[2] = &C8051Arch::fineDecode_0x2;
	JmpTable[3] = &C8051Arch::fineDecode_0x3;
	JmpTable[4] = &C8051Arch::fineDecode_0x4;
	JmpTable[5] = &C8051Arch::fineDecode_0x5;
	JmpTable[6] = &C8051Arch::fineDecode_0x6;
	JmpTable[7] = &C8051Arch::fineDecode_0x7;
	JmpTable[8] = &C8051Arch::fineDecode_0x8;
	JmpTable[9] = &C8051Arch::fineDecode_0x9;
	JmpTable[10] = &C8051Arch::fineDecode_0xa;
	JmpTable[11] = &C8051Arch::fineDecode_0xb;
	JmpTable[12] = &C8051Arch::fineDecode_0xc;
	JmpTable[13] = &C8051Arch::fineDecode_0xd;
	JmpTable[14] = &C8051Arch::fineDecode_0xe;
	JmpTable[15] = &C8051Arch::fineDecode_0xf;
	JmpTable[16] = &C8051Arch::fineDecode_0x10;
	JmpTable[17] = &C8051Arch::fineDecode_0x11;
	JmpTable[18] = &C8051Arch::fineDecode_0x12;
	JmpTable[19] = &C8051Arch::fineDecode_0x13;
	JmpTable[20] = &C8051Arch::fineDecode_0x14;
	JmpTable[21] = &C8051Arch::fineDecode_0x15;
	JmpTable[22] = &C8051Arch::fineDecode_0x16;
	JmpTable[23] = &C8051Arch::fineDecode_0x17;
	JmpTable[24] = &C8051Arch::fineDecode_0x18;
	JmpTable[25] = &C8051Arch::fineDecode_0x19;
	JmpTable[26] = &C8051Arch::fineDecode_0x1a;
	JmpTable[27] = &C8051Arch::fineDecode_0x1b;
	JmpTable[28] = &C8051Arch::fineDecode_0x1c;
	JmpTable[29] = &C8051Arch::fineDecode_0x1d;
	JmpTable[30] = &C8051Arch::fineDecode_0x1e;
	JmpTable[31] = &C8051Arch::fineDecode_0x1f;
	JmpTable[32] = &C8051Arch::fineDecode_0x20;
	JmpTable[33] = &C8051Arch::fineDecode_0x21;
	JmpTable[34] = &C8051Arch::fineDecode_0x22;
	JmpTable[35] = &C8051Arch::fineDecode_0x23;
	JmpTable[36] = &C8051Arch::fineDecode_0x24;
	JmpTable[37] = &C8051Arch::fineDecode_0x25;
	JmpTable[38] = &C8051Arch::fineDecode_0x26;
	JmpTable[39] = &C8051Arch::fineDecode_0x27;
	JmpTable[40] = &C8051Arch::fineDecode_0x28;
	JmpTable[41] = &C8051Arch::fineDecode_0x29;
	JmpTable[42] = &C8051Arch::fineDecode_0x2a;
	JmpTable[43] = &C8051Arch::fineDecode_0x2b;
	JmpTable[44] = &C8051Arch::fineDecode_0x2c;
	JmpTable[45] = &C8051Arch::fineDecode_0x2d;
	JmpTable[46] = &C8051Arch::fineDecode_0x2e;
	JmpTable[47] = &C8051Arch::fineDecode_0x2f;
	JmpTable[48] = &C8051Arch::fineDecode_0x30;
	JmpTable[49] = &C8051Arch::fineDecode_0x31;
	JmpTable[50] = &C8051Arch::fineDecode_0x32;
	JmpTable[51] = &C8051Arch::fineDecode_0x33;
	JmpTable[52] = &C8051Arch::fineDecode_0x34;
	JmpTable[53] = &C8051Arch::fineDecode_0x35;
	JmpTable[54] = &C8051Arch::fineDecode_0x36;
	JmpTable[55] = &C8051Arch::fineDecode_0x37;
	JmpTable[56] = &C8051Arch::fineDecode_0x38;
	JmpTable[57] = &C8051Arch::fineDecode_0x39;
	JmpTable[58] = &C8051Arch::fineDecode_0x3a;
	JmpTable[59] = &C8051Arch::fineDecode_0x3b;
	JmpTable[60] = &C8051Arch::fineDecode_0x3c;
	JmpTable[61] = &C8051Arch::fineDecode_0x3d;
	JmpTable[62] = &C8051Arch::fineDecode_0x3e;
	JmpTable[63] = &C8051Arch::fineDecode_0x3f;
	JmpTable[64] = &C8051Arch::fineDecode_0x40;
	JmpTable[65] = &C8051Arch::fineDecode_0x41;
	JmpTable[66] = &C8051Arch::fineDecode_0x42;
	JmpTable[67] = &C8051Arch::fineDecode_0x43;
	JmpTable[68] = &C8051Arch::fineDecode_0x44;
	JmpTable[69] = &C8051Arch::fineDecode_0x45;
	JmpTable[70] = &C8051Arch::fineDecode_0x46;
	JmpTable[71] = &C8051Arch::fineDecode_0x47;
	JmpTable[72] = &C8051Arch::fineDecode_0x48;
	JmpTable[73] = &C8051Arch::fineDecode_0x49;
	JmpTable[74] = &C8051Arch::fineDecode_0x4a;
	JmpTable[75] = &C8051Arch::fineDecode_0x4b;
	JmpTable[76] = &C8051Arch::fineDecode_0x4c;
	JmpTable[77] = &C8051Arch::fineDecode_0x4d;
	JmpTable[78] = &C8051Arch::fineDecode_0x4e;
	JmpTable[79] = &C8051Arch::fineDecode_0x4f;
	JmpTable[80] = &C8051Arch::fineDecode_0x50;
	JmpTable[81] = &C8051Arch::fineDecode_0x51;
	JmpTable[82] = &C8051Arch::fineDecode_0x52;
	JmpTable[83] = &C8051Arch::fineDecode_0x53;
	JmpTable[84] = &C8051Arch::fineDecode_0x54;
	JmpTable[85] = &C8051Arch::fineDecode_0x55;
	JmpTable[86] = &C8051Arch::fineDecode_0x56;
	JmpTable[87] = &C8051Arch::fineDecode_0x57;
	JmpTable[88] = &C8051Arch::fineDecode_0x58;
	JmpTable[89] = &C8051Arch::fineDecode_0x59;
	JmpTable[90] = &C8051Arch::fineDecode_0x5a;
	JmpTable[91] = &C8051Arch::fineDecode_0x5b;
	JmpTable[92] = &C8051Arch::fineDecode_0x5c;
	JmpTable[93] = &C8051Arch::fineDecode_0x5d;
	JmpTable[94] = &C8051Arch::fineDecode_0x5e;
	JmpTable[95] = &C8051Arch::fineDecode_0x5f;
	JmpTable[96] = &C8051Arch::fineDecode_0x60;
	JmpTable[97] = &C8051Arch::fineDecode_0x61;
	JmpTable[98] = &C8051Arch::fineDecode_0x62;
	JmpTable[99] = &C8051Arch::fineDecode_0x63;
	JmpTable[100] = &C8051Arch::fineDecode_0x64;
	JmpTable[101] = &C8051Arch::fineDecode_0x65;
	JmpTable[102] = &C8051Arch::fineDecode_0x66;
	JmpTable[103] = &C8051Arch::fineDecode_0x67;
	JmpTable[104] = &C8051Arch::fineDecode_0x68;
	JmpTable[105] = &C8051Arch::fineDecode_0x69;
	JmpTable[106] = &C8051Arch::fineDecode_0x6a;
	JmpTable[107] = &C8051Arch::fineDecode_0x6b;
	JmpTable[108] = &C8051Arch::fineDecode_0x6c;
	JmpTable[109] = &C8051Arch::fineDecode_0x6d;
	JmpTable[110] = &C8051Arch::fineDecode_0x6e;
	JmpTable[111] = &C8051Arch::fineDecode_0x6f;
	JmpTable[112] = &C8051Arch::fineDecode_0x70;
	JmpTable[113] = &C8051Arch::fineDecode_0x71;
	JmpTable[114] = &C8051Arch::fineDecode_0x72;
	JmpTable[115] = &C8051Arch::fineDecode_0x73;
	JmpTable[116] = &C8051Arch::fineDecode_0x74;
	JmpTable[117] = &C8051Arch::fineDecode_0x75;
	JmpTable[118] = &C8051Arch::fineDecode_0x76;
	JmpTable[119] = &C8051Arch::fineDecode_0x77;
	JmpTable[120] = &C8051Arch::fineDecode_0x78;
	JmpTable[121] = &C8051Arch::fineDecode_0x79;
	JmpTable[122] = &C8051Arch::fineDecode_0x7a;
	JmpTable[123] = &C8051Arch::fineDecode_0x7b;
	JmpTable[124] = &C8051Arch::fineDecode_0x7c;
	JmpTable[125] = &C8051Arch::fineDecode_0x7d;
	JmpTable[126] = &C8051Arch::fineDecode_0x7e;
	JmpTable[127] = &C8051Arch::fineDecode_0x7f;
	JmpTable[128] = &C8051Arch::fineDecode_0x80;
	JmpTable[129] = &C8051Arch::fineDecode_0x81;
	JmpTable[130] = &C8051Arch::fineDecode_0x82;
	JmpTable[131] = &C8051Arch::fineDecode_0x83;
	JmpTable[132] = &C8051Arch::fineDecode_0x84;
	JmpTable[133] = &C8051Arch::fineDecode_0x85;
	JmpTable[134] = &C8051Arch::fineDecode_0x86;
	JmpTable[135] = &C8051Arch::fineDecode_0x87;
	JmpTable[136] = &C8051Arch::fineDecode_0x88;
	JmpTable[137] = &C8051Arch::fineDecode_0x89;
	JmpTable[138] = &C8051Arch::fineDecode_0x8a;
	JmpTable[139] = &C8051Arch::fineDecode_0x8b;
	JmpTable[140] = &C8051Arch::fineDecode_0x8c;
	JmpTable[141] = &C8051Arch::fineDecode_0x8d;
	JmpTable[142] = &C8051Arch::fineDecode_0x8e;
	JmpTable[143] = &C8051Arch::fineDecode_0x8f;
	JmpTable[144] = &C8051Arch::fineDecode_0x90;
	JmpTable[145] = &C8051Arch::fineDecode_0x91;
	JmpTable[146] = &C8051Arch::fineDecode_0x92;
	JmpTable[147] = &C8051Arch::fineDecode_0x93;
	JmpTable[148] = &C8051Arch::fineDecode_0x94;
	JmpTable[149] = &C8051Arch::fineDecode_0x95;
	JmpTable[150] = &C8051Arch::fineDecode_0x96;
	JmpTable[151] = &C8051Arch::fineDecode_0x97;
	JmpTable[152] = &C8051Arch::fineDecode_0x98;
	JmpTable[153] = &C8051Arch::fineDecode_0x99;
	JmpTable[154] = &C8051Arch::fineDecode_0x9a;
	JmpTable[155] = &C8051Arch::fineDecode_0x9b;
	JmpTable[156] = &C8051Arch::fineDecode_0x9c;
	JmpTable[157] = &C8051Arch::fineDecode_0x9d;
	JmpTable[158] = &C8051Arch::fineDecode_0x9e;
	JmpTable[159] = &C8051Arch::fineDecode_0x9f;
	JmpTable[160] = &C8051Arch::fineDecode_0xa0;
	JmpTable[161] = &C8051Arch::fineDecode_0xa1;
	JmpTable[162] = &C8051Arch::fineDecode_0xa2;
	JmpTable[163] = &C8051Arch::fineDecode_0xa3;
	JmpTable[164] = &C8051Arch::fineDecode_0xa4;
	JmpTable[165] = &C8051Arch::fineDecode_0xa5;
	JmpTable[166] = &C8051Arch::fineDecode_0xa6;
	JmpTable[167] = &C8051Arch::fineDecode_0xa7;
	JmpTable[168] = &C8051Arch::fineDecode_0xa8;
	JmpTable[169] = &C8051Arch::fineDecode_0xa9;
	JmpTable[170] = &C8051Arch::fineDecode_0xaa;
	JmpTable[171] = &C8051Arch::fineDecode_0xab;
	JmpTable[172] = &C8051Arch::fineDecode_0xac;
	JmpTable[173] = &C8051Arch::fineDecode_0xad;
	JmpTable[174] = &C8051Arch::fineDecode_0xae;
	JmpTable[175] = &C8051Arch::fineDecode_0xaf;
	JmpTable[176] = &C8051Arch::fineDecode_0xb0;
	JmpTable[177] = &C8051Arch::fineDecode_0xb1;
	JmpTable[178] = &C8051Arch::fineDecode_0xb2;
	JmpTable[179] = &C8051Arch::fineDecode_0xb3;
	JmpTable[180] = &C8051Arch::fineDecode_0xb4;
	JmpTable[181] = &C8051Arch::fineDecode_0xb5;
	JmpTable[182] = &C8051Arch::fineDecode_0xb6;
	JmpTable[183] = &C8051Arch::fineDecode_0xb7;
	JmpTable[184] = &C8051Arch::fineDecode_0xb8;
	JmpTable[185] = &C8051Arch::fineDecode_0xb9;
	JmpTable[186] = &C8051Arch::fineDecode_0xba;
	JmpTable[187] = &C8051Arch::fineDecode_0xbb;
	JmpTable[188] = &C8051Arch::fineDecode_0xbc;
	JmpTable[189] = &C8051Arch::fineDecode_0xbd;
	JmpTable[190] = &C8051Arch::fineDecode_0xbe;
	JmpTable[191] = &C8051Arch::fineDecode_0xbf;
	JmpTable[192] = &C8051Arch::fineDecode_0xc0;
	JmpTable[193] = &C8051Arch::fineDecode_0xc1;
	JmpTable[194] = &C8051Arch::fineDecode_0xc2;
	JmpTable[195] = &C8051Arch::fineDecode_0xc3;
	JmpTable[196] = &C8051Arch::fineDecode_0xc4;
	JmpTable[197] = &C8051Arch::fineDecode_0xc5;
	JmpTable[198] = &C8051Arch::fineDecode_0xc6;
	JmpTable[199] = &C8051Arch::fineDecode_0xc7;
	JmpTable[200] = &C8051Arch::fineDecode_0xc8;
	JmpTable[201] = &C8051Arch::fineDecode_0xc9;
	JmpTable[202] = &C8051Arch::fineDecode_0xca;
	JmpTable[203] = &C8051Arch::fineDecode_0xcb;
	JmpTable[204] = &C8051Arch::fineDecode_0xcc;
	JmpTable[205] = &C8051Arch::fineDecode_0xcd;
	JmpTable[206] = &C8051Arch::fineDecode_0xce;
	JmpTable[207] = &C8051Arch::fineDecode_0xcf;
	JmpTable[208] = &C8051Arch::fineDecode_0xd0;
	JmpTable[209] = &C8051Arch::fineDecode_0xd1;
	JmpTable[210] = &C8051Arch::fineDecode_0xd2;
	JmpTable[211] = &C8051Arch::fineDecode_0xd3;
	JmpTable[212] = &C8051Arch::fineDecode_0xd4;
	JmpTable[213] = &C8051Arch::fineDecode_0xd5;
	JmpTable[214] = &C8051Arch::fineDecode_0xd6;
	JmpTable[215] = &C8051Arch::fineDecode_0xd7;
	JmpTable[216] = &C8051Arch::fineDecode_0xd8;
	JmpTable[217] = &C8051Arch::fineDecode_0xd9;
	JmpTable[218] = &C8051Arch::fineDecode_0xda;
	JmpTable[219] = &C8051Arch::fineDecode_0xdb;
	JmpTable[220] = &C8051Arch::fineDecode_0xdc;
	JmpTable[221] = &C8051Arch::fineDecode_0xdd;
	JmpTable[222] = &C8051Arch::fineDecode_0xde;
	JmpTable[223] = &C8051Arch::fineDecode_0xdf;
	JmpTable[224] = &C8051Arch::fineDecode_0xe0;
	JmpTable[225] = &C8051Arch::fineDecode_0xe1;
	JmpTable[226] = &C8051Arch::fineDecode_0xe2;
	JmpTable[227] = &C8051Arch::fineDecode_0xe3;
	JmpTable[228] = &C8051Arch::fineDecode_0xe4;
	JmpTable[229] = &C8051Arch::fineDecode_0xe5;
	JmpTable[230] = &C8051Arch::fineDecode_0xe6;
	JmpTable[231] = &C8051Arch::fineDecode_0xe7;
	JmpTable[232] = &C8051Arch::fineDecode_0xe8;
	JmpTable[233] = &C8051Arch::fineDecode_0xe9;
	JmpTable[234] = &C8051Arch::fineDecode_0xea;
	JmpTable[235] = &C8051Arch::fineDecode_0xeb;
	JmpTable[236] = &C8051Arch::fineDecode_0xec;
	JmpTable[237] = &C8051Arch::fineDecode_0xed;
	JmpTable[238] = &C8051Arch::fineDecode_0xee;
	JmpTable[239] = &C8051Arch::fineDecode_0xef;
	JmpTable[240] = &C8051Arch::fineDecode_0xf0;
	JmpTable[241] = &C8051Arch::fineDecode_0xf1;
	JmpTable[242] = &C8051Arch::fineDecode_0xf2;
	JmpTable[243] = &C8051Arch::fineDecode_0xf3;
	JmpTable[244] = &C8051Arch::fineDecode_0xf4;
	JmpTable[245] = &C8051Arch::fineDecode_0xf5;
	JmpTable[246] = &C8051Arch::fineDecode_0xf6;
	JmpTable[247] = &C8051Arch::fineDecode_0xf7;
	JmpTable[248] = &C8051Arch::fineDecode_0xf8;
	JmpTable[249] = &C8051Arch::fineDecode_0xf9;
	JmpTable[250] = &C8051Arch::fineDecode_0xfa;
	JmpTable[251] = &C8051Arch::fineDecode_0xfb;
	JmpTable[252] = &C8051Arch::fineDecode_0xfc;
	JmpTable[253] = &C8051Arch::fineDecode_0xfd;
	JmpTable[254] = &C8051Arch::fineDecode_0xfe;
	JmpTable[255] = &C8051Arch::fineDecode_0xff;
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
	  printf("Starting runDBT now...\n");

	  printf("Measurement about to start...\n");

	// sniffer_config((int*)&env.dataMem[PSW]);

 	//CM3_DEBUGMONInit( (int*)&env.dataMem[PSW] );
}




/*
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
}*/

void C8051Arch::decode()
{
	uint8_t op = FETCH;
	uint8_t subOp = op & 0x0F;
	uint8_t regN = op & 0x7;

//	helper_CC_lazyEv_SNIFFER_BACKDOOR();
//	target->gen_helper(&CTargetArchitecture::helper_call);

	(this->*(JmpTable[op]))(subOp, regN);

	return;
}



void  C8051Arch::fineDecode_0x0(uint8_t subOp, uint8_t Rn){	//NOP
	//target->gen_brkp(0xF0);
  	//target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1);

	zprintf("\tNOP\n\n");
}

void  C8051Arch::fineDecode_0x1(uint8_t subOp, uint8_t Rn){	// AJMP
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;
	//5 MSb from PC, 3b from opcode, 8LSb from instruction
	newPC = (env.PC & 0xF800) | 0x0000 | (uint16_t)tmp1;
    	target->gen_writePC(newPC);

    	zprintf("\tAJMP 0x%04X\n\n", newPC);
	eoBB = true;

}

void  C8051Arch::fineDecode_0x2(uint8_t subOp, uint8_t Rn){	// Long jump : LJMP // ******* Error ******
	uint16_t newPC;
	//DEBUG CALL IN RET INSTRUCTION
	//target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1);

	newPC = FETCH;
	newPC <<= 8;
	newPC |= FETCH;

	target->gen_writePC(newPC);
	eoBB = true;
	zprintf("\tLJMP 0x%04X\n\n", newPC);
}

void  C8051Arch::fineDecode_0x3(uint8_t subOp, uint8_t Rn){	// RR A
	target->gen_ld8(tReg1, A); // load A

	target->gen_ld_bit(tReg1, tReg2, 0);	//get the carry out bit (before rotation)
	target->gen_st_bit(tReg2, tReg1, 8);	//place it as carry in bit (before rotation)

	target->gen_shri(tReg1, tReg1, 1); // shift A
	target->gen_st8(A, tReg1); 	// Save new A

//	target->gen_ld8(tReg1, A); // load A
//	target->gen_movi(tReg2, 1);
//	target->gen_and(tReg1, tReg2);
//	target->gen_shli(tReg1, tReg1, 8);
//	target->gen_ld8(tReg2, A); // load A again
//	target->gen_or(tReg1, tReg2);
//	target->gen_shri(tReg1, tReg1, 1);
//	target->gen_andi(tReg1, tReg1, 0xFF);
//	target->gen_st8( A, tReg1); // Save to A

	zprintf("\tRR A\n\n");
}

void  C8051Arch::fineDecode_0x4(uint8_t subOp, uint8_t Rn){	// INC A
	target->gen_ld8(tReg1, A);  // load A to tReg1
	target->gen_addi(tReg1, 1); // add 1
	target->gen_st8(A, tReg1);  // write back
	//target->gen_helper_update_parity();

	zprintf("\tINC A\n\n");
}

void  C8051Arch::fineDecode_0x5(uint8_t subOp, uint8_t Rn){	// INC direct
	uint8_t tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, tmp1);  // load mem to tReg1
	target->gen_addi(tReg1, 1); // add 1
	target->gen_st8(tmp1, tReg1);  // write back

	zprintf("\tINC (0x%02X)\n\n", tmp1);
}

void  C8051Arch::fineDecode_0x6(uint8_t subOp, uint8_t Rn){	// INC @Ri
	target->gen_ld8(tReg2, subOp&0x01);
	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_addi(tReg1, 1);
	//target->gen_sti8(subOp&0x01, tReg1, tReg2);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);

	zprintf("\tINC @R%X\n\n", subOp&0x01);
}

void  C8051Arch::fineDecode_0x7(uint8_t subOp, uint8_t Rn){	// INC @Ri
	target->gen_ld8(tReg2, subOp&0x01);
	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_addi(tReg1, 1);
	//target->gen_sti8(subOp&0x01, tReg1, tReg2);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);

	zprintf("\tINC @R%X\n\n", subOp&0x01);
}

void  C8051Arch::fineDecode_0x8(uint8_t subOp, uint8_t Rn){	// INC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
	target->gen_movi(tReg2, 1);
	target->gen_add(tReg1, tReg1, tReg2); // add 1
	target->gen_st8( Rn, tReg1);

	zprintf("\tINC R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0x9(uint8_t subOp, uint8_t Rn){	// INC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
	target->gen_movi(tReg2, 1);
	target->gen_add(tReg1, tReg1, tReg2); // add 1
	target->gen_st8( Rn, tReg1);

	zprintf("\tINC R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xa(uint8_t subOp, uint8_t Rn){	// INC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
	target->gen_movi(tReg2, 1);
	target->gen_add(tReg1, tReg1, tReg2); // add 1
	target->gen_st8( Rn, tReg1);

	zprintf("\tINC R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xb(uint8_t subOp, uint8_t Rn){	// INC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
	target->gen_movi(tReg2, 1);
	target->gen_add(tReg1, tReg1, tReg2); // add 1
	target->gen_st8( Rn, tReg1);

	zprintf("\tINC R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0xc(uint8_t subOp, uint8_t Rn){	// INC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
	target->gen_movi(tReg2, 1);
	target->gen_add(tReg1, tReg1, tReg2); // add 1
	target->gen_st8( Rn, tReg1);

	zprintf("\tINC R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0xd(uint8_t subOp, uint8_t Rn){	// INC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
	target->gen_movi(tReg2, 1);
	target->gen_add(tReg1, tReg1, tReg2); // add 1
	target->gen_st8( Rn, tReg1);

	zprintf("\tINC R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0xe(uint8_t subOp, uint8_t Rn){	// INC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
	target->gen_movi(tReg2, 1);
	target->gen_add(tReg1, tReg1, tReg2); // add 1
	target->gen_st8( Rn, tReg1);

	zprintf("\tINC R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0xf(uint8_t subOp, uint8_t Rn){	// INC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tReg1
	target->gen_movi(tReg2, 1);
	target->gen_add(tReg1, tReg1, tReg2); // add 1
	target->gen_st8( Rn, tReg1);

	zprintf("\tINC R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x10(uint8_t subOp, uint8_t Rn){	// JBC
	uint8_t tmp1, tmp2, byteAddr;

	tmp1 = FETCH; 	// get bit address
	tmp2 = FETCH;	//get the jump offset

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

//	get_real_bit_addr(&tmp1, &tmp2);
//	target->gen_ld8(tReg1, tmp1); // load register
//
//	target->gen_movi(tReg2, 0x01);
//	target->gen_shli(tReg2, tReg2, tmp2); //
//	target->gen_and(tReg3, tReg1, tReg2);
//
//	target->gen_not(tReg2, tReg2);
//	target->gen_and(tReg1, tReg1, tReg2);
//	target->gen_st8(tmp1, tReg1);
//
//	tmp2 = FETCH;
//	target->gen_movi(tReg1, 0);
//	target->gen_cjne(tReg1, tReg3, tmp2);

//	target->gen_ld_bit( tReg1, tmp1);	//get bit //target->gen_st_bit additionalli loads tmp1 bit in tReg1

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
}

void C8051Arch::fineDecode_0x11(uint8_t subOp, uint8_t Rn){	// ACALL
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;	//read the page offset first, before storing PC in stack
	newPC = (env.PC & 0xF800) | 0x0000 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
  	target->gen_helper(&CTargetArchitecture::helper_call);

	target->gen_writePC(newPC);

	//callCount++;
	eoBB = true;

    zprintf("\tACALL 0x%04X\n\n", newPC);
}

void C8051Arch::fineDecode_0x12(uint8_t subOp, uint8_t Rn){	// LCALL
	uint16_t newPC;

	//DEBUG CALL IN RET INSTRUCTION
	//target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1);

	newPC = FETCH ;	//new PC must be FETCHed before PC saving in the stack
	newPC <<= 8;
	newPC |= FETCH;		//otherwise the return address poped from the stack will be incorrect
  	target->gen_helper(&CTargetArchitecture::helper_call);

	target->gen_writePC(newPC);

	//callCount++;
	eoBB = true;

	zprintf("\tLCALL $0x%04x\n\n", newPC);
}

void C8051Arch::fineDecode_0x13(uint8_t subOp, uint8_t Rn){	// RRC
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, PSW); // load PSW

	target->gen_ld_bit(tReg2, tReg3, CY_POS);	//put the carry bit to A.8 (before rotation)
	target->gen_st_bit(tReg3, tReg1, 8);

	target->gen_ld_bit(tReg1, tReg3, 0);		//get the carry out bit from A to CY (before rotation)
	target->gen_st_bit(tReg3, tReg2, CY_POS);

	target->gen_shri(tReg1, tReg1, 1); // shift A

	target->gen_st8(A, tReg1); 	// Save new A
	target->gen_st8(PSW, tReg2); 	// Save new PSW

//	target->gen_ld8(tReg1, A); // load A
//	target->gen_andi(tReg1, tReg1, 0x01);
//	target->gen_shli(tReg1, tReg1, 7);
//	target->gen_ld8(tReg2, PSW); // load PSW
//	target->gen_andi(tReg3, tReg2, 0x7F); // Clear C
//	target->gen_or(tReg3, tReg1);
//	target->gen_st8(PSW, tReg3); // Save new C to PSW
//
//	target->gen_ld8(tReg1, A); // load A
//	target->gen_shri(tReg1, tReg1, 1); // shift A
//	target->gen_andi(tReg1, tReg1, 0x7F);  // clear A7
//	target->gen_andi(tReg2, tReg2, 0x80);  // get only C
//	target->gen_or(tReg1, tReg2); // New A
//	target->gen_andi(tReg1, tReg1, 0xFF);
//	target->gen_st8(A, tReg1); // Save new A
//	//target->gen_helper_update_parity();

	zprintf("\tRRC A\n\n");
}

void C8051Arch::fineDecode_0x14(uint8_t subOp, uint8_t Rn){	// DEC A
	target->gen_ld8(tReg1, A);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // sub 1
	target->gen_st8(A, tReg1);  // write back
	//target->gen_helper_update_parity();

	zprintf("\tDEC A\n\n");
}

void C8051Arch::fineDecode_0x15(uint8_t subOp, uint8_t Rn){	//DEC direct
	uint8_t tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, tmp1);  // load mem to tReg1
	target->gen_subi(tReg1, 1); // subb 1
	target->gen_st8(tmp1, tReg1);  // write back

	zprintf("\tDEC 0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x16(uint8_t subOp, uint8_t Rn){	// DEC @Ri
	target->gen_ld8(tReg2, subOp&0x01);
	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_subi(tReg1, 1);
//	target->gen_sti8(Rn, tReg1, tReg2);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);
//	target->gen_helper_inc_dec_indirect(tcg_const(d&1), tcg_const(0));

	zprintf("\tDEC @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x17(uint8_t subOp, uint8_t Rn){	// DEC @Ri
	target->gen_ld8(tReg2, subOp&0x01);
	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_subi(tReg1, 1);
//	target->gen_sti8(Rn, tReg1, tReg2);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);
	//target->gen_helper_inc_dec_indirect(tcg_const(d&1), tcg_const(0));

	zprintf("\tDEC @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x18(uint8_t subOp, uint8_t Rn){	// DEC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // add 1
	target->gen_st8(Rn, tReg1);  // write back

	zprintf("\tDEC R%X\n\n", Rn);
}

void C8051Arch::fineDecode_0x19(uint8_t subOp, uint8_t Rn){	// DEC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // add 1
	target->gen_st8(Rn, tReg1);  // write back

	zprintf("\tDEC R%X\n\n", Rn);
}

void C8051Arch::fineDecode_0x1a(uint8_t subOp, uint8_t Rn){	// DEC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // add 1
	target->gen_st8(Rn, tReg1);  // write back

	zprintf("\tDEC R%X\n\n", Rn);
}

void C8051Arch::fineDecode_0x1b(uint8_t subOp, uint8_t Rn){	// DEC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // add 1
	target->gen_st8(Rn, tReg1);  // write back
	zprintf("\tDEC R%X\n\n", Rn);
}

void C8051Arch::fineDecode_0x1c(uint8_t subOp, uint8_t Rn){	// DEC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // add 1
	target->gen_st8(Rn, tReg1);  // write back
	zprintf("\tDEC R%X\n\n", Rn);
}

void C8051Arch::fineDecode_0x1d(uint8_t subOp, uint8_t Rn){	// DEC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // add 1
	target->gen_st8(Rn, tReg1);  // write back
	zprintf("\tDEC R%X\n\n", Rn);
}

void C8051Arch::fineDecode_0x1e(uint8_t subOp, uint8_t Rn){	// DEC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // add 1
	target->gen_st8(Rn, tReg1);  // write back

	zprintf("\tDEC R%X\n\n", Rn);
}

void C8051Arch::fineDecode_0x1f(uint8_t subOp, uint8_t Rn){	// DEC Rn
	target->gen_ld8(tReg1, Rn);  // load Rn to tmpR[0]
	target->gen_subi(tReg1, 1); // add 1
	target->gen_st8(Rn, tReg1);  // write back

	zprintf("\tDEC R%X\n\n", Rn);
}

void C8051Arch::fineDecode_0x20(uint8_t subOp, uint8_t Rn){	// JB
	uint8_t tmp1, tmp2, byteAddr;

  	tmp1 = FETCH;  	// get bit address
	tmp2 = FETCH;	//get jump offset

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

//	get_real_bit_addr(&tmp1, &tmp2);
//	target->gen_ld8(tReg1, tmp1); // load register
//
//	target->gen_movi(tReg2, 0x01);
//	target->gen_shli(tReg2, tReg2, tmp2); //
//	target->gen_and(tReg3, tReg1, tReg2);
//
//	tmp2 = FETCH;
//	target->gen_movi(tReg1, 0);
//	target->gen_cjne(tReg1, tReg3, tmp2);

	byteAddr = (tmp1 < 128 )	?	32 + (tmp1 >> 3)	: //if bit7 is clear, bit belongs to bit addressable area (base 32)
	 					tmp1 & 0xF8		; //if bit7 is set, bit belongs to SFR area (base 1228)

	target->gen_ld8(tReg1, byteAddr);
	target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit


	target->gen_cjei(tReg1, 1, tmp2);	//target->generate compare jump equal with tReg2

	eoBB = true;

	zprintf("\t????check write PC????JB %d\n\n", env.PC + (int8_t)tmp1);
}

void C8051Arch::fineDecode_0x21(uint8_t subOp, uint8_t Rn){	// AJMP
//	decode_ajmp_target->gen(op);
	uint8_t tmp1;
  	uint16_t tmp3;

	tmp1 = FETCH;
	tmp3 = (env.PC & 0xF800) | 0x0100 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
    	target->gen_writePC(tmp3);

    	zprintf("\tAJMP 0x%04X\n\n", tmp3);
	eoBB = true;
}

void C8051Arch::fineDecode_0x22(uint8_t subOp, uint8_t Rn){	// RET
//	if (callCount--)
//	{
		//DEBUG CALL IN RET INSTRUCTION
	  	//target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1);

  		target->gen_helper(&CTargetArchitecture::helper_ret);
//	}
//	else {
//		zprintf("MAIN RETURN DETECTED\nEND OF ENGINE EXECUTION\n");
//		helper_debug((0);
//		eoExec = true;
//	}

	eoBB = true;
	zprintf("\tRET\n\n");
}

void C8051Arch::fineDecode_0x23(uint8_t subOp, uint8_t Rn){	// RL A
	target->gen_ld8(tReg1, A); // load A

//	target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1);

	target->gen_shli(tReg1, tReg1, 1); // shift A

	target->gen_ld_bit(tReg1, tReg2, 8);	//get the carry out bit (before rotation)
	target->gen_st_bit(tReg2, tReg1, 0);	//place it as carry in bit (before rotation)

	target->gen_st8(A, tReg1); 	// Save new A

//	target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1);

//	target->gen_ld8(tReg1, A); // load A
//	target->gen_andi(tReg2, tReg1, 0x80);
//	target->gen_shri(tReg2, tReg2, 7);
//	target->gen_shli(tReg1, tReg1, 1);
//	target->gen_or(tReg1, tReg2);
//	target->gen_andi(tReg1, tReg1, 0xFF);
//	target->gen_st8(A, tReg1); // Save to A
	//target->gen_helper_update_parity();

	zprintf("\tRL A\n\n");
}

void C8051Arch::fineDecode_0x24(uint8_t subOp, uint8_t Rn){	// ADD A, #imm
	uint8_t tmp1;

	tmp1 = FETCH;
	/* Load register */
	target->gen_ld8(tReg1, A);
	target->gen_movi(tReg2, tmp1);

	target->gen_add(tReg3, tReg1, tReg2);	//flags are alway updated when outside an IT block
	target->gen_st8(A, tReg3);


	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );



	zprintf("\tADD A, #0x%02x\n\n", tmp1);
}

void C8051Arch::fineDecode_0x25(uint8_t subOp, uint8_t Rn){	// ADD A, Direct
	uint8_t tmp1;

	tmp1 = FETCH;
	/* Load register */
	target->gen_ld8(tReg1, A);
	target->gen_ld8(tReg2, tmp1);

	target->gen_add(tReg3, tReg1, tReg2);	//flags are alway updated when outside an IT block
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, 0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x26(uint8_t subOp, uint8_t Rn){	// ADD A, @Ri
	target->gen_ld8(tReg1,	subOp&0x01);
  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

	target->gen_ld8(tReg1, A);
	target->gen_add(tReg3, tReg1, tReg2);
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\t??????NYV?????? ADD A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x27(uint8_t subOp, uint8_t Rn){	// ADD A, @Ri
	target->gen_ld8(tReg1,	subOp&0x01);
  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

	target->gen_ld8(tReg1, A);
	target->gen_add(tReg3, tReg1, tReg2);
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\t??????NYV?????? ADD A, @R%d\n\n", subOp&0x01);
}


void C8051Arch::fineDecode_0x28(uint8_t subOp, uint8_t Rn){	// ADD A, Rn
	target->gen_ld8(tReg1, A); // load Rn to tReg1
	target->gen_ld8(tReg2, Rn); // load A

	target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x29(uint8_t subOp, uint8_t Rn){	// ADD A, Rn
	target->gen_ld8(tReg1, A); // load Rn to tReg1
	target->gen_ld8(tReg2, Rn); // load A

	target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x2a(uint8_t subOp, uint8_t Rn){	// ADD A, Rn
	target->gen_ld8(tReg1, A); // load Rn to tReg1
	target->gen_ld8(tReg2, Rn); // load A

	target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x2b(uint8_t subOp, uint8_t Rn){	// ADD A, Rn
	target->gen_ld8(tReg1, A); // load Rn to tReg1
	target->gen_ld8(tReg2, Rn); // load A

	target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x2c(uint8_t subOp, uint8_t Rn){	// ADD A, Rn
	target->gen_ld8(tReg1, A); // load Rn to tReg1
	target->gen_ld8(tReg2, Rn); // load A

	target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x2d(uint8_t subOp, uint8_t Rn){	// ADD A, Rn
	target->gen_ld8(tReg1, A); // load Rn to tReg1
	target->gen_ld8(tReg2, Rn); // load A

	target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x2e(uint8_t subOp, uint8_t Rn){	// ADD A, Rn
	target->gen_ld8(tReg1, A); // load Rn to tReg1
	target->gen_ld8(tReg2, Rn); // load A

	target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	//target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x2f(uint8_t subOp, uint8_t Rn){	// ADD A, Rn
	target->gen_ld8(tReg1, A); // load Rn to tReg1
	target->gen_ld8(tReg2, Rn); // load A

	target->gen_add(tReg3, tReg1, tReg2); // add A, A, Rn
	target->gen_st8(A, tReg3);

	//update lazy evaluation of condition codes register
	target->gen_assemble_lazyEv_param( LZE_ADD_OP, tReg1, tReg2, 0x00);
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADD_OP, tReg1, tReg2, 0x00 );

	zprintf("\tADD A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x30(uint8_t subOp, uint8_t Rn){	// JNB
	uint8_t tmp1, tmp2, byteAddr;

	tmp1 = FETCH; 	// get bit address
	tmp2 = FETCH;	//get jump offset

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

//	get_real_bit_addr(&tmp1, &tmp2);
//	target->gen_ld8(tReg1, tmp1); // load register
//
//	target->gen_movi(tReg2, 0x01);
//	target->gen_shli(tReg2, tReg2, tmp2);
//	target->gen_and(tReg3, tReg1, tReg2);
//	target->gen_shri(tReg3, tReg2, tmp2);
//
//	tmp2 = FETCH;
//	target->gen_movi(tReg1, 1);
//	target->gen_cjne(tReg1, tReg3, tmp2);

	byteAddr = (tmp1 < 128 )	?	32 + (tmp1 >> 3)	: //if bit7 is clear, bit belongs to bit addressable area (base 32)
	 					tmp1 & 0xF8		; //if bit7 is set, bit belongs to SFR area (base 1228)

	target->gen_ld8(tReg1, byteAddr);
	target->gen_ld_bit( tReg1, tReg1, tmp1&0x07);	//get bit


	target->gen_cjnei(tReg1, 1, tmp2);	//target->generate compare jump NOT equal with tReg2

	eoBB = true;
}

void C8051Arch::fineDecode_0x31(uint8_t subOp, uint8_t Rn){	// ACALL
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;	//read the page offset first, before storing PC in stack
	newPC = (env.PC & 0xF800) | 0x0100 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
  	target->gen_helper(&CTargetArchitecture::helper_call);

	target->gen_writePC(newPC);

	//callCount++;
	eoBB = true;

    zprintf("\tACALL 0x%04X\n\n", newPC);
}

void C8051Arch::fineDecode_0x32(uint8_t subOp, uint8_t Rn){
	zprintf("\tRETI -UNSUPPORTED- \n\n");

	eoBB = true;
	target->eoExec = true;
}

void C8051Arch::fineDecode_0x33(uint8_t subOp, uint8_t Rn){	// RLC A
//	target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1); //absince of this print causes bad result

  	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, PSW); // load PSW

//	target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1); //absince of this print causes bad result

	target->gen_shli(tReg1, tReg1, 1); // shift A

	target->gen_ld_bit(tReg2, tReg3, CY_POS);	//get the carry bit to A.8 (before rotation)
	target->gen_st_bit(tReg3, tReg1, 0);

	target->gen_ld_bit(tReg1, tReg3, 8);		//get the carry out bit from A to CY (before rotation)
	target->gen_st_bit(tReg3, tReg2, CY_POS);


	target->gen_st8(A, tReg1); 	// Save new A
	target->gen_st8(PSW, tReg2); 	// Save new PSW

//	target->gen_helper( &C8051Arch::helper_debug(, (int)env.PC-1);

//	target->gen_ld8(tReg1, A); // load A
//	target->gen_andi(tReg1, tReg1, 0x80);
//	target->gen_ld8(tReg2, PSW); // load PSW
//	target->gen_andi(tReg3, tReg2, 0x7F); // Clear C
//	target->gen_or(tReg3, tReg1);
//	target->gen_st8(PSW, tReg3); // Save new C to PSW
//
//	target->gen_ld8(tReg1, A); // load A
//	target->gen_shli(tReg1, tReg1, 1); // shift A
//	target->gen_andi(tReg1, tReg1, 0xFE);  // clear A7
//	target->gen_andi(tReg2, tReg2, 0x80);  // get only C
//	target->gen_shri(tReg2, tReg2, 7); //
//	target->gen_or(tReg1, tReg2); // New A
//	target->gen_andi(tReg1, tReg1, 0xFF);
//	target->gen_st8(A, tReg1); // Save new A
//	target->gen_helper_update_parity();

	zprintf("\tRLC A\n\n");
}

void C8051Arch::fineDecode_0x34(uint8_t subOp, uint8_t Rn){	// ADDC A, #immed
	uint8_t tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, A); // load A
	target->gen_movi(tReg2, tmp1); // load #imm value

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register


	//target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2);
	target->gen_add(tReg1, tReg1, tReg3);
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, #0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x35(uint8_t subOp, uint8_t Rn){	// ADDC A, direct
	uint8_t tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, tmp1); // load direct address

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2);
	target->gen_add(tReg1, tReg1, tReg3);
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, 0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x36(uint8_t subOp, uint8_t Rn){	// ADDC A, @Ri
	target->gen_ld8(tReg1,	subOp&0x01);
  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

	target->gen_ld8(tReg1, A);

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\t??????NYV??????ADDC A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x37(uint8_t subOp, uint8_t Rn){	// ADDC A, @Ri
	target->gen_ld8(tReg1,	subOp&0x01);
  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

	target->gen_ld8(tReg1, A);

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\t??????NYV??????ADDC A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x38(uint8_t subOp, uint8_t Rn){	// ADDC A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x39(uint8_t subOp, uint8_t Rn){	// ADDC A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x3a(uint8_t subOp, uint8_t Rn){	// ADDC A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x3b(uint8_t subOp, uint8_t Rn){	// ADDC A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x3c(uint8_t subOp, uint8_t Rn){	// ADDC A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x3d(uint8_t subOp, uint8_t Rn){	// ADDC A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x3e(uint8_t subOp, uint8_t Rn){	// ADDC A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x3f(uint8_t subOp, uint8_t Rn){	// ADDC A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_ADDC_OP, tReg1, tReg2, tReg3 );

	target->gen_add(tReg1, tReg1, tReg2); // add
	target->gen_add(tReg1, tReg1, tReg3); // Add with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tADDC A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x40(uint8_t subOp, uint8_t Rn){	// JC
	uint8_t tmp1;

	tmp1 = FETCH;			//get jump offset
	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored


	target->gen_ld8(tReg1, PSW);
	target->gen_ld_bit(tReg1, tReg1, CY_POS);
	target->gen_cjei(tReg1, 1, tmp1);	//target->generate compare jump equal with tReg2

	eoBB = true;

	zprintf("\tJC 0x%x\n\n", env.PC + (int8_t)tmp1);
}

void C8051Arch::fineDecode_0x41(uint8_t subOp, uint8_t Rn){	// AJMP
//	decode_ajmp_target->gen(op);
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;
	newPC = (env.PC & 0xF800) | 0x0200 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
    	target->gen_writePC(newPC);

    	zprintf("\tAJMP 0x%04X\n\n", newPC);
	eoBB = true;
}

void C8051Arch::fineDecode_0x42(uint8_t subOp, uint8_t Rn){	// ORL direct, A
	uint8_t tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, tmp1); // load direct to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_or(tReg1, tReg2); // OR
	target->gen_st8(tmp1, tReg1);

	zprintf("\tORL 0x%02X, A\n\n", tmp1);
}

void C8051Arch::fineDecode_0x43(uint8_t subOp, uint8_t Rn){	// ORL direct, #imm
	uint8_t tmp1, tmp2;

	tmp1 = FETCH;
	tmp2 = FETCH;

	target->gen_ld8(tReg1, tmp1); // load direct to tReg1
	target->gen_movi(tReg2, tmp2); // load #imm
	target->gen_or(tReg1, tReg2); // OR
	target->gen_st8(tmp1, tReg1);

  	zprintf("\tORL 0x%02X, #0x%02X\n\n", tmp1, tmp2);
}

void C8051Arch::fineDecode_0x44(uint8_t subOp, uint8_t Rn){	// ORL A, #imm
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg1, A); // load direct to tReg1
	target->gen_movi(tReg2, tmp1); // load #imm
	target->gen_or(tReg1, tReg2); // OR
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, #0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x45(uint8_t subOp, uint8_t Rn){	// ORL A, direct
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg1, tmp1); // load direct to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_or(tReg2, tReg1); // OR
	target->gen_st8(A, tReg2);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, 0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x46(uint8_t subOp, uint8_t Rn){	// ORL A, @Ri
	target->gen_ld8(tReg2, subOp&0x01);
	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_ld8(tReg2, A); // load A
	target->gen_or(tReg2, tReg1); // OR
	target->gen_st8(A, tReg2);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x47(uint8_t subOp, uint8_t Rn){	// ORL A, @Ri
	target->gen_ld8(tReg2, subOp&0x01);
	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_ld8(tReg2, A); // load A
	target->gen_or(tReg2, tReg1); // OR
	target->gen_st8(A, tReg2);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x48(uint8_t subOp, uint8_t Rn){	// ORL A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
	target->gen_ld8(tReg2, A);
	target->gen_or(tReg1, tReg2);
	//check if order of parameter are inverted
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x49(uint8_t subOp, uint8_t Rn){	// ORL A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
	target->gen_ld8(tReg2, A);
	target->gen_or(tReg1, tReg2);
	//check if order of parameter are inverted
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x4a(uint8_t subOp, uint8_t Rn){	// ORL A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
	target->gen_ld8(tReg2, A);
	target->gen_or(tReg1, tReg2);
	//check if order of parameter are inverted
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x4b(uint8_t subOp, uint8_t Rn){	// ORL A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
	target->gen_ld8(tReg2, A);
	target->gen_or(tReg1, tReg2);
	//check if order of parameter are inverted
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x4c(uint8_t subOp, uint8_t Rn){	// ORL A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
	target->gen_ld8(tReg2, A);
	target->gen_or(tReg1, tReg2);
	//check if order of parameter are inverted
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x4d(uint8_t subOp, uint8_t Rn){	// ORL A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
	target->gen_ld8(tReg2, A);
	target->gen_or(tReg1, tReg2);
	//check if order of parameter are inverted
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x4e(uint8_t subOp, uint8_t Rn){	// ORL A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
	target->gen_ld8(tReg2, A);
	target->gen_or(tReg1, tReg2);
	//check if order of parameter are inverted
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x4f(uint8_t subOp, uint8_t Rn){	// ORL A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn to tReg1
	target->gen_ld8(tReg2, A);
	target->gen_or(tReg1, tReg2);
	//check if order of parameter are inverted
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tORL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x50(uint8_t subOp, uint8_t Rn){	// JNC
//	tmp1 = FETCH; // get relative address
//
//	target->gen_ld8(tReg1, PSW); // load register
//	target->gen_movi(tReg2, 0x80);
//	target->gen_and(tReg2, tReg1, tReg2);
//
//	target->gen_movi(tReg1, 0x80);
//	target->gen_cjne(tReg1, tReg2, tmp1);
	uint8_t tmp1;

	tmp1 = FETCH;			//get jump offset

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

//	target->gen_ld_bit( tReg1, CY_BIT);	//get bit
	target->gen_ld8(tReg1, PSW);
	target->gen_ld_bit(tReg1, tReg1, CY_POS);

//	target->gen_movi(tReg2, 1);
	target->gen_cjnei(tReg1, 1, tmp1);	//target->generate compare jump NOT equal with tReg2

	eoBB = true;

	zprintf("\tJNC 0x%x\n\n", env.PC + (int8_t)tmp1);
}

void C8051Arch::fineDecode_0x51(uint8_t subOp, uint8_t Rn){	// ACALL
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;	//read the page offset first, before storing PC in stack
	newPC = (env.PC & 0xF800) | 0x0200 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
  	target->gen_helper(&CTargetArchitecture::helper_call);

	target->gen_writePC(newPC);

	//callCount++;
	eoBB = true;

    zprintf("\tACALL 0x%04X\n\n", newPC);
}

void C8051Arch::fineDecode_0x52(uint8_t subOp, uint8_t Rn){	// ANL direct, A
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg1, tmp1); // load
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND
	target->gen_st8(tmp1 , tReg1);

	zprintf("\tANL 0x%02X, A\n\n", tmp1);
}

void C8051Arch::fineDecode_0x53(uint8_t subOp, uint8_t Rn){	// ANL direct, #imm
	uint8_t tmp1, tmp2;

	tmp1 = FETCH;
	tmp2 = FETCH;

	target->gen_ld8(tReg1, tmp1); // load
	target->gen_movi(tReg2, tmp2); // load #imm to register
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(tmp1 , tReg1);

	zprintf("\tANL 0x%02X, #0x%02X\n\n", tmp1, tmp2);
}

void C8051Arch::fineDecode_0x54(uint8_t subOp, uint8_t Rn){	// ANL A, #imm
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg1, A); // load  A
	target->gen_movi(tReg2, tmp1); // load #imm to register
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, #0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x55(uint8_t subOp, uint8_t Rn){	// ANL A, direct
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg1, A); // load  A
	target->gen_ld8(tReg2, tmp1); // load from address
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, 0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x56(uint8_t subOp, uint8_t Rn){	// ANL A, @Ri
	//target->gen_helper_orl_anl_xrl_indirect(tcg_const(d&0x1), tcg_const(1)); // 0 = orl, 1 = anl
	target->gen_ld8(tReg2, subOp&0x01);
  	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg2, tReg1); // OR
	target->gen_st8(A, tReg2);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x57(uint8_t subOp, uint8_t Rn){	// ANL A, @Ri
	//target->gen_helper_orl_anl_xrl_indirect(tcg_const(d&0x1), tcg_const(1)); // 0 = orl, 1 = anl
	target->gen_ld8(tReg2, subOp&0x01);
  	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg2, tReg1); // OR
	target->gen_st8(A, tReg2);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x58(uint8_t subOp, uint8_t Rn){	// ANL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x59(uint8_t subOp, uint8_t Rn){	// ANL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x5a(uint8_t subOp, uint8_t Rn){	// ANL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x5b(uint8_t subOp, uint8_t Rn){	// ANL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x5c(uint8_t subOp, uint8_t Rn){	// ANL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x5d(uint8_t subOp, uint8_t Rn){	// ANL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x5e(uint8_t subOp, uint8_t Rn){	// ANL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x5f(uint8_t subOp, uint8_t Rn){	// ANL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_and(tReg1, tReg2); // AND A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tANL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x60(uint8_t subOp, uint8_t Rn){	//JZ
	uint8_t tmp1;

	tmp1 = FETCH; // get relative address

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, A);

	target->gen_cjei(tReg1, 0, tmp1);

	eoBB = true;

	zprintf("\tJZ 0x%x\n\n", env.PC + (int8_t)tmp1);
}

void C8051Arch::fineDecode_0x61(uint8_t subOp, uint8_t Rn){	// AJMP
//	decode_ajmp_target->gen(op);
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;
	newPC = (env.PC & 0xF800) | 0x0300 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
    	target->gen_writePC(newPC);

    	zprintf("\tAJMP 0x%04X\n\n", newPC);
	eoBB = true;
}

void C8051Arch::fineDecode_0x62(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg1, tmp1); // load direct address to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(tmp1 , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\t??????\n\n");
}

void C8051Arch::fineDecode_0x63(uint8_t subOp, uint8_t Rn){	// XRL direct, #imm
	uint8_t tmp1, tmp2;

	tmp1 = FETCH;
	tmp2 = FETCH;

	target->gen_ld8(tReg1, tmp1); // load
	target->gen_movi(tReg2, tmp2); // load #imm to register
	target->gen_xor(tReg1, tReg2); // XOR direct, #imm
	target->gen_st8(tmp1 , tReg1);

	zprintf("\tXRL 0x%02X, #0x%02X\n\n", tmp1, tmp2);
}

void C8051Arch::fineDecode_0x64(uint8_t subOp, uint8_t Rn){	// XRL A, #imm
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg1, A); // load  A
	target->gen_movi(tReg2, tmp1); // load #imm to register
	target->gen_xor(tReg1, tReg2); // XOR A, #imm
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL 0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x65(uint8_t subOp, uint8_t Rn){	// XRL A, direct
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg1, A); // load  A
	target->gen_ld8(tReg2, tmp1); // load from address
	target->gen_xor(tReg1, tReg2); // XOR A, A, direct
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, 0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x66(uint8_t subOp, uint8_t Rn){	// XRL A, @Ri
	//target->gen_helper_orl_anl_xrl_indirect(tcg_const(d&0x1), tcg_const(2)); // 0 = orl, 1 = anl, 2 = xrl
	target->gen_ld8(tReg2, subOp&0x01);
  	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg2, tReg1); // OR
	target->gen_st8(A, tReg2);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x67(uint8_t subOp, uint8_t Rn){	// XRL A, @Ri
	//target->gen_helper_orl_anl_xrl_indirect(tcg_const(d&0x1), tcg_const(2)); // 0 = orl, 1 = anl, 2 = xrl
	target->gen_ld8(tReg2, subOp&0x01);
  	target->gen_ldi8(tReg1, MEM_BASE, tReg2); // load Indirect
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg2, tReg1); // OR
	target->gen_st8(A, tReg2);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, @R%d\n\n", subOp&0x01);
}

void C8051Arch::fineDecode_0x68(uint8_t subOp, uint8_t Rn){	// XRL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x69(uint8_t subOp, uint8_t Rn){	// XRL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x6a(uint8_t subOp, uint8_t Rn){	// XRL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x6b(uint8_t subOp, uint8_t Rn){	// XRL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x6c(uint8_t subOp, uint8_t Rn){	// XRL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x6d(uint8_t subOp, uint8_t Rn){	// XRL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x6e(uint8_t subOp, uint8_t Rn){	// XRL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x6f(uint8_t subOp, uint8_t Rn){	// XRL A, Rn
	target->gen_ld8(tReg1, Rn); // load Rn to tReg1
	target->gen_ld8(tReg2, A); // load A
	target->gen_xor(tReg1, tReg2); // XRL A, A, Rn
	target->gen_st8(A , tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXRL A, R%d\n\n", Rn);
}

void C8051Arch::fineDecode_0x70(uint8_t subOp, uint8_t Rn){	//JNZ
	uint8_t tmp1;

	tmp1 = FETCH; // get relative address

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, A);
	//target->gen_movi(tReg2, 0);


	target->gen_cjnei(tReg1,0, tmp1); //???check execution, before was target->gen_cjne, but I think was a bug

	eoBB = true;

	zprintf("\tJNZ 0x%x\n\n", env.PC + (int8_t)tmp1);
}

void C8051Arch::fineDecode_0x71(uint8_t subOp, uint8_t Rn){	// ACALL
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;	//read the page offset first, before storing PC in stack
	newPC = (env.PC & 0xF800) | 0x0300 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
  	target->gen_helper(&CTargetArchitecture::helper_call);

	target->gen_writePC(newPC);

	//callCount++;
	eoBB = true;

    zprintf("\tACALL 0x%04X\n\n", newPC);
}

void C8051Arch::fineDecode_0x72(uint8_t subOp, uint8_t Rn){	// ORL C, bit
	uint8_t tmp1, byteAddr;

	tmp1 = FETCH;
//	get_real_bit_addr(&tmp1, &tmp2);
//	target->gen_ld8(tReg1, tmp1); // load register
//	target->gen_movi(tReg2, 0x01);
//	target->gen_shli(tReg2, tReg2, tmp2); //
//	target->gen_and(tReg1, tReg1, tReg2);
//	target->gen_shli(tReg1, tReg1, 7-tmp2); //

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
}

void C8051Arch::fineDecode_0x73(uint8_t subOp, uint8_t Rn){	// JMP @A+DPTR
	target->gen_ld8(tReg1, A);
	target->gen_ld16(tReg2, DPL);
	target->gen_add(tReg1, tReg1, tReg2);

	//target->gen_movi(tReg2, (int)env.dataMem  );

	target->gen_writePCreg(tReg1);

	eoBB = true;
	zprintf("\tJMP @A+DPTR\n\n");
}

void C8051Arch::fineDecode_0x74(uint8_t subOp, uint8_t Rn){	//MOV A, #im
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_movi(tReg1, tmp1);
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tMOV A, #0x%02X\n\n", tmp1);
}

void C8051Arch::fineDecode_0x75(uint8_t subOp, uint8_t Rn){	// MOV direct, #imm
	uint8_t tmp1, tmp2;

	tmp1 = FETCH;
	tmp2 = FETCH;

	target->gen_movi(tReg1, tmp2); // move #imme to temp TCG register
	target->gen_st8(tmp1, tReg1);

	zprintf("\tMOV 0x%02X, #0x%02X\n\n", tmp1, tmp2);
}

void C8051Arch::fineDecode_0x76(uint8_t subOp, uint8_t Rn){	//MOV @Ri,#data
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_movi(tReg1, tmp1);
	target->gen_ld8(tReg2, subOp&0x01);
	//target->gen_sti8(Rn, tReg2, tReg3);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);

	zprintf("\tMOV @R%d, #0x%02X\n\n", subOp&0x01, tmp1);
}

void C8051Arch::fineDecode_0x77(uint8_t subOp, uint8_t Rn){	//MOV @Ri,#data
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_movi(tReg1, tmp1);
	target->gen_ld8(tReg2, subOp&0x01);
	//target->gen_sti8(Rn, tReg2, tReg3);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);

	zprintf("\tMOV @R%d, #0x%02X\n\n", subOp&0x01, tmp1);
}

void C8051Arch::fineDecode_0x78(uint8_t subOp, uint8_t Rn){	// MOV Rn, #data
	uint8_t tmp1;

	tmp1 = FETCH;

	//zprintf("imediato d%d x%x\n",tmp1, tmp1);
	target->gen_movi(tReg1, tmp1);
	target->gen_st8(Rn, tReg1);

	zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
}

void C8051Arch::fineDecode_0x79(uint8_t subOp, uint8_t Rn){	// MOV Rn, #data
	uint8_t tmp1;

	tmp1 = FETCH;

	//zprintf("imediato d%d x%x\n",tmp1, tmp1);
	target->gen_movi(tReg1, tmp1);
	target->gen_st8(Rn, tReg1);

	zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
}

void C8051Arch::fineDecode_0x7a(uint8_t subOp, uint8_t Rn){	// MOV Rn, #data
	uint8_t tmp1;

	tmp1 = FETCH;

	//zprintf("imediato d%d x%x\n",tmp1, tmp1);
	target->gen_movi(tReg1, tmp1);
	target->gen_st8(Rn, tReg1);

	zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
}

void C8051Arch::fineDecode_0x7b(uint8_t subOp, uint8_t Rn){	// MOV Rn, #data
	uint8_t tmp1;

	tmp1 = FETCH;

	//zprintf("imediato d%d x%x\n",tmp1, tmp1);
	target->gen_movi(tReg1, tmp1);
	target->gen_st8(Rn, tReg1);

	zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
}

void C8051Arch::fineDecode_0x7c(uint8_t subOp, uint8_t Rn){	// MOV Rn, #data
	uint8_t tmp1;

	tmp1 = FETCH;

	//zprintf("imediato d%d x%x\n",tmp1, tmp1);
	target->gen_movi(tReg1, tmp1);
	target->gen_st8(Rn, tReg1);

	zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
}

void C8051Arch::fineDecode_0x7d(uint8_t subOp, uint8_t Rn){	// MOV Rn, #data
	uint8_t tmp1;

	tmp1 = FETCH;

	//zprintf("imediato d%d x%x\n",tmp1, tmp1);
	target->gen_movi(tReg1, tmp1);
	target->gen_st8(Rn, tReg1);

	zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
}

void C8051Arch::fineDecode_0x7e(uint8_t subOp, uint8_t Rn){	// MOV Rn, #data
	uint8_t tmp1;

	tmp1 = FETCH;

	//zprintf("imediato d%d x%x\n",tmp1, tmp1);
	target->gen_movi(tReg1, tmp1);
	target->gen_st8(Rn, tReg1);

	zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
}

void C8051Arch::fineDecode_0x7f(uint8_t subOp, uint8_t Rn){	// MOV Rn, #data
	uint8_t tmp1;

	tmp1 = FETCH;

	//zprintf("imediato d%d x%x\n",tmp1, tmp1);
	target->gen_movi(tReg1, tmp1);
	target->gen_st8(Rn, tReg1);

	zprintf("\tMOV R%d, #0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0x80(uint8_t subOp, uint8_t Rn){   //  SJMP
	uint8_t tmp1;

	tmp1 = FETCH;

	if (tmp1 > 127)
		tmp1 |=  0xFFFFFF00;

	target->gen_writePC( (uint16_t)((int)env.PC + (int8_t)tmp1));
	eoBB = true;

	zprintf("\tSJMP 0x%x\n\n", env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0x81(uint8_t subOp, uint8_t Rn){      // AJMP
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;

	newPC = (env.PC & 0xF800) | 0x0400 | (uint16_t)tmp1; //5 MSb from PC, 3b from subOp, Rn, 8LSb from instruction
	    target->gen_writePC(newPC);

	    zprintf("\tAJMP 0x%04X\n\n", newPC);
	eoBB = true;
}

void  C8051Arch::fineDecode_0x82(uint8_t subOp, uint8_t Rn){     // ANL C, bit
	uint8_t tmp1, byteAddr;

	tmp1 = FETCH;

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
}

void  C8051Arch::fineDecode_0x83(uint8_t subOp, uint8_t Rn){        // MOVC A, @A+PC
	target->gen_ld8(tReg1, A);
	target->gen_movi(tReg2, env.PC);
	target->gen_add(tReg1, tReg1, tReg2);

	target->gen_movi(tReg2, (int)pSourceProgMem );
	target->gen_ldi8(tReg1, tReg2, tReg1 );
	target->gen_st8( A, tReg1 );

	zprintf("\tMOVC A, @A+PC\n\n");
}

void  C8051Arch::fineDecode_0x84(uint8_t subOp, uint8_t Rn){       // DIV AB	(unsigned division)
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
}

void  C8051Arch::fineDecode_0x85(uint8_t subOp, uint8_t Rn){    //MOD IRAM ADDR, IRAM ADDR
	uint8_t tmp1, tmp2;

	tmp1 = FETCH; // get direct address
	tmp2 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1);
	target->gen_st8(tmp2, tReg1);
	zprintf("\tMOV %d, %d\n", tmp2, tmp1);
}

void  C8051Arch::fineDecode_0x86(uint8_t subOp, uint8_t Rn){     // MOV direct, @Ri
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg2, subOp&0x01 );
	target->gen_ldi8(tReg1, MEM_BASE, tReg2 );
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, @R%d\n\n", tmp1, subOp&0x01);
}

void  C8051Arch::fineDecode_0x87(uint8_t subOp, uint8_t Rn){    // MOV direct, @Ri
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_ld8(tReg2, subOp&0x01 );
	target->gen_ldi8(tReg1, MEM_BASE, tReg2 );
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, @R%d\n\n", tmp1, subOp&0x01);
}

void  C8051Arch::fineDecode_0x88(uint8_t subOp, uint8_t Rn){   //MOV direct, Rn
	uint8_t tmp1;

	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, Rn);
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
}

void  C8051Arch::fineDecode_0x89(uint8_t subOp, uint8_t Rn){   //MOV direct, Rn
	uint8_t tmp1;

	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, Rn);
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
}

void  C8051Arch::fineDecode_0x8a(uint8_t subOp, uint8_t Rn){    //MOV direct, Rn
	uint8_t tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, Rn);
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
}

void  C8051Arch::fineDecode_0x8b(uint8_t subOp, uint8_t Rn){    //MOV direct, Rn
	uint8_t tmp1;

	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, Rn);
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
}

void  C8051Arch::fineDecode_0x8c(uint8_t subOp, uint8_t Rn){     //MOV direct, Rn
	uint8_t tmp1;

	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, Rn);
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
}

void  C8051Arch::fineDecode_0x8d(uint8_t subOp, uint8_t Rn){    //MOV direct, Rn
	uint8_t tmp1;
	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, Rn);
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
}

void  C8051Arch::fineDecode_0x8e(uint8_t subOp, uint8_t Rn){    //MOV direct, Rn
	uint8_t tmp1;
	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, Rn);
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
}

void  C8051Arch::fineDecode_0x8f(uint8_t subOp, uint8_t Rn){    //MOV direct, Rn
	uint8_t tmp1;
	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, Rn);
	target->gen_st8(tmp1, tReg1);
	zprintf("\tMOV 0x%02X, R%d\n\n", tmp1, Rn);
}

void  C8051Arch::fineDecode_0x90(uint8_t subOp, uint8_t Rn){    // MOV DPTR, #imm
	uint16_t tmp3;

	tmp3 = FETCH;
	tmp3 <<= 8;
	tmp3 |= FETCH;
	target->gen_movi(tReg1, tmp3);
	target->gen_st16(DPL, tReg1);
	zprintf("\tMOV DPTR, #0x%x\n\n", tmp3);
}

void  C8051Arch::fineDecode_0x91(uint8_t subOp, uint8_t Rn){     // ACALL
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;	//read the page offset first, before storing PC in stack
	newPC = (env.PC & 0xF800) | 0x0400 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
  	target->gen_helper(&CTargetArchitecture::helper_call);
	target->gen_writePC(newPC);
	//callCount++;
	eoBB = true;
    zprintf("\tACALL 0x%04X\n\n", newPC);
}

void  C8051Arch::fineDecode_0x92(uint8_t subOp, uint8_t Rn){    // MOV bit, C
	uint8_t tmp1, byteAddr;

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
}

void  C8051Arch::fineDecode_0x93(uint8_t subOp, uint8_t Rn){     // MOVC A,@A+DPTR
  	target->gen_ld8(tReg1, A);
	target->gen_ld16(tReg2, DPL);
	target->gen_add(tReg1, tReg1, tReg2);

	target->gen_movi(tReg2, (int)pSourceProgMem  );
	target->gen_ldi8(tReg1, tReg2, tReg1 );
	target->gen_st8( A, tReg1 );

	zprintf("\tMOVC A, @A+DPTR\n\n");
}

void  C8051Arch::fineDecode_0x94(uint8_t subOp, uint8_t Rn){   // SUBB A, #imm
	uint8_t tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, A);
	target->gen_movi(tReg2, tmp1);

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2);
	target->gen_sub(tReg1, tReg1, tReg3);
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, #0x%02X\n\n", tmp1);
}

void  C8051Arch::fineDecode_0x95(uint8_t subOp, uint8_t Rn){   // SUBB A, direct
	uint8_t tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, tmp1);

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2);
	target->gen_sub(tReg1, tReg1, tReg3);
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, 0x%02X\n\n", tmp1);
}

void  C8051Arch::fineDecode_0x96(uint8_t subOp, uint8_t Rn){     // SUBB A, @Ri
  	target->gen_ld8(tReg1,	subOp&0x01);
  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

	target->gen_ld8(tReg1, A);

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, #@R%d\n\n", subOp&0x01);
}

void  C8051Arch::fineDecode_0x97(uint8_t subOp, uint8_t Rn){  // SUBB A, @Ri
  	target->gen_ld8(tReg1,	subOp&0x01);
  	target->gen_ldi8(tReg2, MEM_BASE, tReg1); // load Indirect

	target->gen_ld8(tReg1, A);

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, #@R%d\n\n", subOp&0x01);
}

void  C8051Arch::fineDecode_0x98(uint8_t subOp, uint8_t Rn){   // SUBB A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0x99(uint8_t subOp, uint8_t Rn){   // SUBB A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0x9a(uint8_t subOp, uint8_t Rn){  // SUBB A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0x9b(uint8_t subOp, uint8_t Rn){   // SUBB A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0x9c(uint8_t subOp, uint8_t Rn){   // SUBB A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0x9d(uint8_t subOp, uint8_t Rn){    // SUBB A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0x9e(uint8_t subOp, uint8_t Rn){    // SUBB A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0x9f(uint8_t subOp, uint8_t Rn){    // SUBB A, Rn
	target->gen_ld8(tReg1, A); // load A
	target->gen_ld8(tReg2, Rn); // load Rn

	target->gen_ld8(tReg3, PSW);
	target->gen_ld_bit(tReg3, tReg3, CY_POS);

	//update lazy evaluation of condition codes register
	target->gen_helper(  &CTargetArchitecture::CC_onDemand_Update, LZE_SUBB_OP, tReg1, tReg2, tReg3 );

	target->gen_sub(tReg1, tReg1, tReg2); // sub
	target->gen_sub(tReg1, tReg1, tReg3); // sub with C
	target->gen_st8(A, tReg1); // Store A

	zprintf("\tMUST REVIEW\nSUBB A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xa0(uint8_t subOp, uint8_t Rn){      // ORL C,/bit addr
	uint8_t tmp1, byteAddr;

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
//		target->gen_ld8(tReg2, PSW);
	target->gen_or(tReg1, tReg3);
	target->gen_st_bit(tReg1, tReg2, CY_POS);
	target->gen_st8(PSW, tReg2); // save to PSW
	zprintf("\tORL C, XXX\n\n");
}

void  C8051Arch::fineDecode_0xa1(uint8_t subOp, uint8_t Rn){   // AJMP
	uint8_t tmp1;
	uint16_t newPC;

	//	decode_ajmp_target->gen(op);
	tmp1 = FETCH;

	newPC = (env.PC & 0xF800) | 0x0500 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
    	target->gen_writePC(newPC);

    	zprintf("\tAJMP 0x%04X\n\n", newPC);
	eoBB = true;
}

void  C8051Arch::fineDecode_0xa2(uint8_t subOp, uint8_t Rn){    // MOV C, bit
	uint8_t tmp1, byteAddr;

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
}

void  C8051Arch::fineDecode_0xa3(uint8_t subOp, uint8_t Rn){    // INC DPTR
	target->gen_ld16(tReg1, DPL);
	target->gen_addi(tReg1, 1);

	target->gen_st16(DPL, tReg1); // save dpl + dph

	zprintf("\tINC DPTR\n\n");
}

void  C8051Arch::fineDecode_0xa4(uint8_t subOp, uint8_t Rn){    // MUL AB
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
}

void  C8051Arch::fineDecode_0xa5(uint8_t subOp, uint8_t Rn){    //UNDEFINED INSTRUCTION
	zprintf("\tUNDEFINED INSTRUCTION \n\n");
}

void  C8051Arch::fineDecode_0xa6(uint8_t subOp, uint8_t Rn){   // MOV @Ri, direct
	uint8_t tmp1;

	tmp1 = FETCH;
	//target->gen_helper_mov_indirect(tcg_const(d&0x01), tcg_const(b), tcg_const(2));
	target->gen_ld8(tReg1, tmp1);
	target->gen_ld8(tReg2, subOp&0x01);
	//target->gen_sti8(subOp&0x01, tReg1, tReg2);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);

	zprintf("\tMOV @Ri, 0x%x\n\n", subOp&0x01);
}

void  C8051Arch::fineDecode_0xa7(uint8_t subOp, uint8_t Rn){    // MOV @Ri, direct
	uint8_t tmp1;

	tmp1 = FETCH;
	//target->gen_helper_mov_indirect(tcg_const(d&0x01), tcg_const(b), tcg_const(2));
	target->gen_ld8(tReg1, tmp1);
	target->gen_ld8(tReg2, subOp&0x01);
	//target->gen_sti8(subOp&0x01, tReg1, tReg2);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);

	zprintf("\tMOV @Ri, 0x%x\n\n", subOp&0x01);
}

void  C8051Arch::fineDecode_0xa8(uint8_t subOp, uint8_t Rn){    //MOV Rn, direct
	uint8_t tmp1;

	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1); // load data from direct address
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0xa9(uint8_t subOp, uint8_t Rn){    //MOV Rn, direct
	uint8_t tmp1;

	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1); // load data from direct address
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0xaa(uint8_t subOp, uint8_t Rn){    //MOV Rn, direct
	uint8_t tmp1;

	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1); // load data from direct address
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0xab(uint8_t subOp, uint8_t Rn){   //MOV Rn, direct
	uint8_t tmp1;
	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1); // load data from direct address
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0xac(uint8_t subOp, uint8_t Rn){   //MOV Rn, direct
	uint8_t tmp1;
	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1); // load data from direct address
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0xad(uint8_t subOp, uint8_t Rn){    //MOV Rn, direct
	uint8_t tmp1;
	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1); // load data from direct address
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0xae(uint8_t subOp, uint8_t Rn){    //MOV Rn, direct
	uint8_t tmp1;
	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1); // load data from direct address
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0xaf(uint8_t subOp, uint8_t Rn){    //MOV Rn, direct
	uint8_t tmp1;
	tmp1 = FETCH; // get direct address
	target->gen_ld8(tReg1, tmp1); // load data from direct address
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, 0x%02X\n\n", Rn, tmp1);
}

void  C8051Arch::fineDecode_0xb0(uint8_t subOp, uint8_t Rn){   // ANL C, /bit
	uint8_t tmp1, byteAddr;

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
 }

void  C8051Arch::fineDecode_0xb1(uint8_t subOp, uint8_t Rn){     // ACALL
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;	//read the page offset first, before storing PC in stack

	newPC = (env.PC & 0xF800) | 0x0500 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
  	target->gen_helper(&CTargetArchitecture::helper_call);

	target->gen_writePC(newPC);

	//callCount++;
	eoBB = true;
    zprintf("\tACALL 0x%04X\n\n", newPC);
}

void  C8051Arch::fineDecode_0xb2(uint8_t subOp, uint8_t Rn){     // CPL bit

	uint8_t tmp1, byteAddr;

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
}

void  C8051Arch::fineDecode_0xb3(uint8_t subOp, uint8_t Rn){     // CPL C
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
}

void  C8051Arch::fineDecode_0xb4(uint8_t subOp, uint8_t Rn){    // CJNE A, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xb5(uint8_t subOp, uint8_t Rn){    // CJNE A, direct
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xb6(uint8_t subOp, uint8_t Rn){  	// CJNE @Ri, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xb7(uint8_t subOp, uint8_t Rn){   // CJNE @Ri, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xb8(uint8_t subOp, uint8_t Rn){
// CJNE Rn, #imm
	uint8_t tmp1, tmp2;

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

}

void  C8051Arch::fineDecode_0xb9(uint8_t subOp, uint8_t Rn){    // CJNE Rn, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xba(uint8_t subOp, uint8_t Rn){    // CJNE Rn, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xbb(uint8_t subOp, uint8_t Rn){   // CJNE Rn, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xbc(uint8_t subOp, uint8_t Rn){   // CJNE Rn, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xbd(uint8_t subOp, uint8_t Rn){   // CJNE Rn, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xbe(uint8_t subOp, uint8_t Rn){  // CJNE Rn, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xbf(uint8_t subOp, uint8_t Rn){   // CJNE Rn, #imm
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xc0(uint8_t subOp, uint8_t Rn){
	uint8_t tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, SP);
	target->gen_addi(tReg1, 1); // SP + 1;
	target->gen_st8( SP, tReg1);

	target->gen_ld8(tReg2, tmp1); // load
	target->gen_sti8(tReg2, MEM_BASE, tReg1);


	zprintf("\t???????NYV?????????PUSH\n\n");
}

void  C8051Arch::fineDecode_0xc1(uint8_t subOp, uint8_t Rn){   // AJMP
//	decode_ajmp_target->gen(op);
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;

	newPC = (env.PC & 0xF800) | 0x0600 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
    	target->gen_writePC(newPC);

    	zprintf("\tAJMP 0x%04X\n\n", newPC);
	eoBB = true;
}

void  C8051Arch::fineDecode_0xc2(uint8_t subOp, uint8_t Rn){    // CLR bit
	uint8_t tmp1, byteAddr;

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
}

void  C8051Arch::fineDecode_0xc3(uint8_t subOp, uint8_t Rn){    // CLR C
	target->gen_ld8(tReg1, PSW); // load PSW register
	target->gen_andi(tReg1, tReg1, 0x7F);
	target->gen_st8(PSW, tReg1);	 // save back

	zprintf("\tCLR C\n\n");
}

void  C8051Arch::fineDecode_0xc4(uint8_t subOp, uint8_t Rn){   // SWAP A
	target->gen_ld8(tReg1, A);
	target->gen_shli(tReg2, tReg1, 4);
	target->gen_andi(tReg2, tReg2, 0xF0);


	target->gen_shri(tReg1, tReg1, 4);
	target->gen_andi(tReg1, tReg1, 0x0F);

	target->gen_or(tReg1, tReg2);
	target->gen_st8(A, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tSWAP A\n\n");
}

void  C8051Arch::fineDecode_0xc5(uint8_t subOp, uint8_t Rn){   // XCH A, direct
	uint8_t tmp1;

	tmp1 = FETCH; // get direct address

	target->gen_ld8(tReg1, A);
	target->gen_ld8(tReg2, tmp1); // load data from direct address

	target->gen_st8(A, tReg2);
	target->gen_st8(tmp1, tReg1);
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, 0x%x\n\n",tmp1);
}

void  C8051Arch::fineDecode_0xc6(uint8_t subOp, uint8_t Rn){    // XCH A, @Ri

	target->gen_ld8(tReg1, A);
	target->gen_ld8(tReg3, subOp&0x01 );
	target->gen_ldi8(tReg2, MEM_BASE, tReg3 ); // load data from direct address

	target->gen_st8(A, tReg2);
//		target->gen_sti8(subOp&0x01, tReg1, tReg2);
	target->gen_sti8(tReg1, MEM_BASE, tReg3);

	//target->gen_helper_update_parity();

	zprintf("\tXCH A, @R%d\n\n",subOp&0x01);
}

void  C8051Arch::fineDecode_0xc7(uint8_t subOp, uint8_t Rn){     // XCH A, @Ri
	target->gen_ld8(tReg1, A);
	target->gen_ld8(tReg3, subOp&0x01 );
	target->gen_ldi8(tReg2, MEM_BASE, tReg3 ); // load data from direct address

	target->gen_st8(A, tReg2);
//		target->gen_sti8(subOp&0x01, tReg1, tReg2);
	target->gen_sti8(tReg1, MEM_BASE, tReg3);

	//target->gen_helper_update_parity();

	zprintf("\tXCH A, @R%d\n\n",subOp&0x01);
}

void  C8051Arch::fineDecode_0xc8(uint8_t subOp, uint8_t Rn){  	 // XCH A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_ld8(tReg2, A); // Load A.
	target->gen_st8(A, tReg1); // Store the value to A.
	target->gen_st8(Rn, tReg2); // Store the value to Rn.
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, R%d\n\n",Rn);
}

void  C8051Arch::fineDecode_0xc9(uint8_t subOp, uint8_t Rn){  		 // XCH A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_ld8(tReg2, A); // Load A.
	target->gen_st8(A, tReg1); // Store the value to A.
	target->gen_st8(Rn, tReg2); // Store the value to Rn.
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, R%d\n\n",Rn);
}

void  C8051Arch::fineDecode_0xca(uint8_t subOp, uint8_t Rn){   // XCH A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_ld8(tReg2, A); // Load A.
	target->gen_st8(A, tReg1); // Store the value to A.
	target->gen_st8(Rn, tReg2); // Store the value to Rn.
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, R%d\n\n",Rn);
}

void  C8051Arch::fineDecode_0xcb(uint8_t subOp, uint8_t Rn){    // XCH A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_ld8(tReg2, A); // Load A.
	target->gen_st8(A, tReg1); // Store the value to A.
	target->gen_st8(Rn, tReg2); // Store the value to Rn.
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, R%d\n\n",Rn);
}

void  C8051Arch::fineDecode_0xcc(uint8_t subOp, uint8_t Rn){   // XCH A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_ld8(tReg2, A); // Load A.
	target->gen_st8(A, tReg1); // Store the value to A.
	target->gen_st8(Rn, tReg2); // Store the value to Rn.
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, R%d\n\n",Rn);
}

void  C8051Arch::fineDecode_0xcd(uint8_t subOp, uint8_t Rn){    // XCH A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_ld8(tReg2, A); // Load A.
	target->gen_st8(A, tReg1); // Store the value to A.
	target->gen_st8(Rn, tReg2); // Store the value to Rn.
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, R%d\n\n",Rn);
}

void  C8051Arch::fineDecode_0xce(uint8_t subOp, uint8_t Rn){   // XCH A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_ld8(tReg2, A); // Load A.
	target->gen_st8(A, tReg1); // Store the value to A.
	target->gen_st8(Rn, tReg2); // Store the value to Rn.
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, R%d\n\n",Rn);
}

void  C8051Arch::fineDecode_0xcf(uint8_t subOp, uint8_t Rn){   // XCH A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_ld8(tReg2, A); // Load A.
	target->gen_st8(A, tReg1); // Store the value to A.
	target->gen_st8(Rn, tReg2); // Store the value to Rn.
	//target->gen_helper_update_parity();

	zprintf("\tXCH A, R%d\n\n",Rn);
}

void  C8051Arch::fineDecode_0xd0(uint8_t subOp, uint8_t Rn){    //POP
	uint8_t tmp1;

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
}

void  C8051Arch::fineDecode_0xd1(uint8_t subOp, uint8_t Rn){   	// ACALL
	uint8_t tmp1;
	uint16_t newPC;

	tmp1 = FETCH;	//read the page offset first, before storing PC in stack

	newPC = (env.PC & 0xF800) | 0x0600 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
  	target->gen_helper(&CTargetArchitecture::helper_call);

	target->gen_writePC(newPC);

	//callCount++;
	eoBB = true;

    zprintf("\tACALL 0x%04X\n\n", newPC);
}

void  C8051Arch::fineDecode_0xd2(uint8_t subOp, uint8_t Rn){    // SETB bit.
	uint8_t tmp1, byteAddr;

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
}

void  C8051Arch::fineDecode_0xd3(uint8_t subOp, uint8_t Rn){    // SETB C
	target->gen_ld8(tReg1, PSW); // load PSW register
	target->gen_ori(tReg1, tReg1, 0x80);
	target->gen_st8(PSW, tReg1);	 // save back

	zprintf("\tSETBC \n\n");
}

void  C8051Arch::fineDecode_0xd4(uint8_t subOp, uint8_t Rn){   // DA
  	target->gen_helper(&CTargetArchitecture::helper_DA);
	//target->gen_helper_update_parity();
	zprintf("\tDA A\n\n");
}

void  C8051Arch::fineDecode_0xd5(uint8_t subOp, uint8_t Rn){   // DJNZ direct, offset
	uint8_t tmp1, tmp2;

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
}

void  C8051Arch::fineDecode_0xd6(uint8_t subOp, uint8_t Rn){   // XCHD A, @Ri
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
}

void  C8051Arch::fineDecode_0xd7(uint8_t subOp, uint8_t Rn){    // XCHD A, @Ri
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
}

void  C8051Arch::fineDecode_0xd8(uint8_t subOp, uint8_t Rn){    // DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, Rn);
	target->gen_subi(tReg1, 1);
	target->gen_st8(Rn, tReg1);

//		target->gen_movi(tReg2, 0);

	target->gen_cjnei(tReg1, 0, tmp1);
	eoBB = true;
	zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0xd9(uint8_t subOp, uint8_t Rn){    // DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, Rn);
	target->gen_subi(tReg1, 1);
	target->gen_st8(Rn, tReg1);

//		target->gen_movi(tReg2, 0);

	target->gen_cjnei(tReg1, 0, tmp1);
	eoBB = true;
	zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0xda(uint8_t subOp, uint8_t Rn){   // DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
	uint8_t tmp1;

	tmp1 = FETCH;

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, Rn);
	target->gen_subi(tReg1, 1);
	target->gen_st8(Rn, tReg1);

//		target->gen_movi(tReg2, 0);

	target->gen_cjnei(tReg1, 0, tmp1);
	eoBB = true;
	zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0xdb(uint8_t subOp, uint8_t Rn){    // DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
	uint8_t tmp1;
	tmp1 = FETCH;

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, Rn);
	target->gen_subi(tReg1, 1);
	target->gen_st8(Rn, tReg1);

//		target->gen_movi(tReg2, 0);

	target->gen_cjnei(tReg1, 0, tmp1);
	eoBB = true;
	zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0xdc(uint8_t subOp, uint8_t Rn){   // DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
	uint8_t tmp1;
	tmp1 = FETCH;

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, Rn);
	target->gen_subi(tReg1, 1);
	target->gen_st8(Rn, tReg1);

//		target->gen_movi(tReg2, 0);

	target->gen_cjnei(tReg1, 0, tmp1);
	eoBB = true;
	zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0xdd(uint8_t subOp, uint8_t Rn){   // DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
	uint8_t tmp1;
	tmp1 = FETCH;

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, Rn);
	target->gen_subi(tReg1, 1);
	target->gen_st8(Rn, tReg1);

//		target->gen_movi(tReg2, 0);

	target->gen_cjnei(tReg1, 0, tmp1);
	eoBB = true;
	zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0xde(uint8_t subOp, uint8_t Rn){   // DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
	uint8_t tmp1;
	tmp1 = FETCH;

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, Rn);
	target->gen_subi(tReg1, 1);
	target->gen_st8(Rn, tReg1);

//		target->gen_movi(tReg2, 0);

	target->gen_cjnei(tReg1, 0, tmp1);
	eoBB = true;
	zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0xdf(uint8_t subOp, uint8_t Rn){    // DJNZ : 0xD8 to 0xDF is DJNZ Rn, offset
	uint8_t tmp1;
	tmp1 = FETCH;

	target->gen_writePC(env.PC);	//restore the nextBB addr to PC, so if the jump is take, on next execution the PC will be restored

	target->gen_ld8(tReg1, Rn);
	target->gen_subi(tReg1, 1);
	target->gen_st8(Rn, tReg1);
//	target->gen_movi(tReg2, 0);
	target->gen_cjnei(tReg1, 0, tmp1);
	eoBB = true;
	zprintf("\tDJNZ R%d, 0x%x\n\n",Rn, env.PC + (int8_t)tmp1);
}

void  C8051Arch::fineDecode_0xe0(uint8_t subOp, uint8_t Rn){  // MOVX A,@DPTR
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
}

void  C8051Arch::fineDecode_0xe1(uint8_t subOp, uint8_t Rn){   // AJMP
	// Decode_ajmp_target->gen(op);
	unsigned tmp1;
	uint16_t newPC;
	tmp1 = FETCH;

	newPC = (env.PC & 0xF800) | 0x0700 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
    	target->gen_writePC(newPC);

    	zprintf("\tAJMP 0x%04X\n\n", newPC);
	eoBB = true;
}

void  C8051Arch::fineDecode_0xe2(uint8_t subOp, uint8_t Rn){   	  // MOVX A,@Ri
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
}

void  C8051Arch::fineDecode_0xe3(uint8_t subOp, uint8_t Rn){    // MOVX A,@Ri
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
}

void  C8051Arch::fineDecode_0xe4(uint8_t subOp, uint8_t Rn){   // CLR A
	target->gen_movi(tReg1, 0);
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tCLR A\n\n");
	//target->gen_helper_update_parity();
}

void  C8051Arch::fineDecode_0xe5(uint8_t subOp, uint8_t Rn){   // MOV A, direct
	unsigned tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, tmp1); // Load.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, #0x%x\n\n", tmp1);
	//target->gen_helper_update_parity();
}

void  C8051Arch::fineDecode_0xe6(uint8_t subOp, uint8_t Rn){   // MOV A, @Ri
	//target->gen_helper_mov_indirect(tcg_const(d&0x01), tcg_const(0), tcg_const(3));
	target->gen_ld8(tReg2, subOp&0x01 );
  	target->gen_ldi8(tReg1, MEM_BASE, tReg2);
	target->gen_st8(A, tReg1);
	zprintf("\tMOV A, @R%d\n\n", subOp&0x01);
	//target->gen_helper_update_parity();
}

void  C8051Arch::fineDecode_0xe7(uint8_t subOp, uint8_t Rn){   // MOV A, @Ri
	//target->gen_helper_mov_indirect(tcg_const(d&0x01), tcg_const(0), tcg_const(3));
	target->gen_ld8(tReg2, subOp&0x01 );
  	target->gen_ldi8(tReg1, MEM_BASE, tReg2);
	target->gen_st8(A, tReg1);
	zprintf("\tMOV A, @R%d\n\n", subOp&0x01);
	//target->gen_helper_update_parity();
}

void  C8051Arch::fineDecode_0xe8(uint8_t subOp, uint8_t Rn){   // 0xE8 to 0xEF : MOV A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xe9(uint8_t subOp, uint8_t Rn){   // 0xE8 to 0xEF : MOV A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xea(uint8_t subOp, uint8_t Rn){   // 0xE8 to 0xEF : MOV A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xeb(uint8_t subOp, uint8_t Rn){   // 0xE8 to 0xEF : MOV A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xec(uint8_t subOp, uint8_t Rn){   // 0xE8 to 0xEF : MOV A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xed(uint8_t subOp, uint8_t Rn){    // 0xE8 to 0xEF : MOV A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xee(uint8_t subOp, uint8_t Rn){   // 0xE8 to 0xEF : MOV A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xef(uint8_t subOp, uint8_t Rn){   // 0xE8 to 0xEF : MOV A, Rn
	target->gen_ld8(tReg1, Rn); // Load Rn.
	target->gen_st8(A, tReg1); // Store the value to A.
	zprintf("\tMOV A, R%d\n\n", Rn);
}

void  C8051Arch::fineDecode_0xf0(uint8_t subOp, uint8_t Rn){   // MOVX @DPTR, A

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
}

void  C8051Arch::fineDecode_0xf1(uint8_t subOp, uint8_t Rn){   // ACALL
	unsigned tmp1;
	uint16_t newPC;

	tmp1 = FETCH;	//read the page offset first, before storing PC in stack

	newPC = (env.PC & 0xF800) | 0x0700 | (uint16_t)tmp1; //5 MSb from PC, 3b from opcode, 8LSb from instruction
  	target->gen_helper(&CTargetArchitecture::helper_call);

	target->gen_writePC(newPC);

	//callCount++;
	eoBB = true;

    	zprintf("\tACALL 0x%04X\n\n", newPC);
}

void  C8051Arch::fineDecode_0xf2(uint8_t subOp, uint8_t Rn){   // MOVX @Ri, A

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
}

void  C8051Arch::fineDecode_0xf3(uint8_t subOp, uint8_t Rn){   // MOVX @Ri, A

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
}

void  C8051Arch::fineDecode_0xf4(uint8_t subOp, uint8_t Rn){   // CPL A
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_not(tReg1, tReg1); // complement
	target->gen_st8(A, tReg1); // Store the value to A.
	//target->gen_helper_update_parity();
	zprintf("\tCPL A\n\n");
}

void  C8051Arch::fineDecode_0xf5(uint8_t subOp, uint8_t Rn){  // MOV direct, A
	unsigned tmp1;

	tmp1 = FETCH;
	target->gen_ld8(tReg1, A);
	target->gen_st8(tmp1, tReg1); // Load.
	zprintf("\tMOV 0x%x, A\n\n", tmp1);
}

void  C8051Arch::fineDecode_0xf6(uint8_t subOp, uint8_t Rn){   // MOV @Ri, A
	target->gen_ld8(tReg1, A);
	target->gen_ld8(tReg2, subOp&0x01);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);
	zprintf("\tMOV @R%d, A\n\n",subOp&0x01);
}

void  C8051Arch::fineDecode_0xf7 (uint8_t subOp, uint8_t Rn){    // MOV @Ri, A
	target->gen_ld8(tReg1, A);
	target->gen_ld8(tReg2, subOp&0x01);
	target->gen_sti8(tReg1, MEM_BASE, tReg2);
	zprintf("\tMOV @R%d, A\n\n",subOp&0x01);
}

void  C8051Arch::fineDecode_0xf8(uint8_t subOp, uint8_t Rn){
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, A\n\n", Rn);
}

void  C8051Arch::fineDecode_0xf9(uint8_t subOp, uint8_t Rn){
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, A\n\n", Rn);
}

void  C8051Arch::fineDecode_0xfa(uint8_t subOp, uint8_t Rn){
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, A\n\n", Rn);
}

void  C8051Arch::fineDecode_0xfb(uint8_t subOp, uint8_t Rn){
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, A\n\n", Rn);
}

void  C8051Arch::fineDecode_0xfc(uint8_t subOp, uint8_t Rn){
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, A\n\n", Rn);
}

void  C8051Arch::fineDecode_0xfd(uint8_t subOp, uint8_t Rn){
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, A\n\n", Rn);
}

void  C8051Arch::fineDecode_0xfe(uint8_t subOp, uint8_t Rn){
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, A\n\n", Rn);
}

void  C8051Arch::fineDecode_0xff(uint8_t subOp, uint8_t Rn){
	target->gen_ld8(tReg1, A); // Load register A.
	target->gen_st8(Rn, tReg1); // Store the value to Rn.
	zprintf("\tMOV R%d, A\n\n", Rn);
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
