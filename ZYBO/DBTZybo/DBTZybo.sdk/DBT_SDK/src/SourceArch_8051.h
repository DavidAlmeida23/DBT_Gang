#ifndef C8051_H
#define C8051_H

#include "SourceArchitecture.h"

#define NUM_Instructions	256
class C8051Arch;
typedef void (C8051Arch::*fineDecode)(uint8_t, uint8_t);


#define A 0xE0
#define B 0xF0
#define SP 0x81
#define PSW 0xD0
#define DPH 0x83
#define DPL 0x82


#define DATA_SIZE 256
#define XDATA_SIZE  8192



class C8051Arch: public CSourceArchitecture
{

	fineDecode *JmpTable;
public:
        C8051Arch(int Ccache_size = 0, CTargetArchitecture *target = 0 );
        ~C8051Arch();


    	void fineDecode_0x0(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x1(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x2(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x3(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x4(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x5(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x6(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x7(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x8(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x9(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x10(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x11(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x12(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x13(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x14(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x15(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x16(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x17(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x18(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x19(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x1a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x1b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x1c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x1d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x1e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x1f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x20(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x21(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x22(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x23(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x24(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x25(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x26(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x27(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x28(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x29(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x2a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x2b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x2c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x2d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x2e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x2f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x30(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x31(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x32(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x33(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x34(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x35(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x36(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x37(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x38(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x39(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x3a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x3b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x3c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x3d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x3e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x3f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x40(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x41(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x42(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x43(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x44(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x45(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x46(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x47(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x48(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x49(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x4a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x4b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x4c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x4d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x4e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x4f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x50(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x51(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x52(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x53(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x54(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x55(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x56(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x57(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x58(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x59(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x5a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x5b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x5c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x5d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x5e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x5f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x60(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x61(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x62(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x63(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x64(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x65(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x66(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x67(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x68(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x69(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x6a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x6b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x6c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x6d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x6e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x6f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x70(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x71(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x72(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x73(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x74(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x75(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x76(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x77(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x78(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x79(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x7a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x7b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x7c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x7d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x7e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x7f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x80(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x81(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x82(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x83(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x84(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x85(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x86(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x87(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x88(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x89(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x8a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x8b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x8c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x8d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x8e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x8f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x90(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x91(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x92(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x93(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x94(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x95(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x96(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x97(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x98(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x99(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x9a(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x9b(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x9c(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x9d(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x9e(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0x9f(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa0(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa1(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa2(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa3(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa4(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa5(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa6(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa7(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa8(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xa9(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xaa(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xab(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xac(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xad(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xae(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xaf(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb0(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb1(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb2(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb3(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb4(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb5(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb6(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb7(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb8(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xb9(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xba(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xbb(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xbc(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xbd(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xbe(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xbf(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc0(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc1(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc2(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc3(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc4(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc5(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc6(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc7(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc8(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xc9(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xca(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xcb(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xcc(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xcd(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xce(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xcf(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd0(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd1(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd2(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd3(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd4(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd5(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd6(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd7(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd8(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xd9(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xda(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xdb(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xdc(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xdd(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xde(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xdf(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe0(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe1(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe2(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe3(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe4(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe5(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe6(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe7(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe8(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xe9(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xea(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xeb(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xec(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xed(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xee(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xef(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf0(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf1(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf2(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf3(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf4(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf5(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf6(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf7(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf8(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xf9(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xfa(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xfb(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xfc(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xfd(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xfe(uint8_t subOp, uint8_t Rn);
    	void fineDecode_0xff(uint8_t subOp, uint8_t Rn);


    virtual void envReset(void);
	virtual void condCodedHandlerInit(void);
	//virtual void decode(uint8_t op);
	virtual void decode();

	void initJumpTable();



	int getMyAddr(void);


};

#endif
