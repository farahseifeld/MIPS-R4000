class instCU
{
public:
	instCU();
	instCU(int x);
	int inst;
	int Iimm, Jimm, A1, A2, RsD, RtD, RdE;
	int op,funct,jump, branch, MemtoReg, MemWrite, RegWrite,aluctrl,alusrc,RegDst;
	void setinst(int x);
private:
	void instdec(int inst);
	void control();
};
instCU::instCU()
{
	inst = 0;
	instdec(inst);
	control();
}
instCU::instCU(int x)
{
	inst = x;
	instdec(inst);
	control();

}
void instCU::instdec(int inst)
{
	op = inst >> 26;
	funct = inst & 0x3f;
	Iimm = inst & 0xffff;
	Jimm = (inst << 6) >> 5;
	A1 = (inst << 6) >> 27;
	RsD = A1;
	A2 = (inst << 11) >> 27;
	RtD = A2;
	RdE = (inst << 16) >> 27;

}
void instCU::control()
{
	if (op == 0 && funct == 0x20)//add
	{
		RegWrite = 1;
		MemtoReg = 0;
		MemWrite = 0;
		aluctrl = 2;
		alusrc = 0;
		RegDst = 1;
		jump = 0;
		branch = 0;
	}
	else if (op == 0x8)//addi
	{
		RegWrite = 1;
		MemtoReg = 0;
		MemWrite = 0;
		aluctrl = 2;
		alusrc = 1;
		RegDst = 0;
		jump = 0;
		branch = 0;
	}
	else if (op == 0x26)//xor
	{
		RegWrite = 1;
		MemtoReg = 0;
		MemWrite = 0;
		aluctrl = 4;
		alusrc = 0;
		RegDst = 1;
		jump = 0;
		branch = 0;
	}
	else if (op == 0x23)//lw
	{
		RegWrite = 1;
		MemtoReg = 1;
		MemWrite = 0;
		aluctrl = 2;
		alusrc = 1;
		RegDst = 0;
		jump = 0;
		branch = 0;
	}
	else if (op == 0x2b)//sw
	{
		RegWrite = 0;
		MemtoReg = 0;
		MemWrite = 1;
		aluctrl = 2;
		alusrc = 1;
		RegDst = 1;
		jump = 0;
		branch = 0;
	}
	else if (op == 0 && funct == 0x2a)//slt
	{
		RegWrite = 1;
		MemtoReg = 0;
		MemWrite = 0;
		aluctrl = 7;
		alusrc = 0;
		RegDst = 1;
		jump = 0;
		branch = 0;
	}
	else if (op == 0x4)//ble
	{
		RegWrite = 0;
		MemtoReg = 0;
		MemWrite = 0;
		aluctrl = 6;
		alusrc = 1;
		RegDst = 1;
		jump = 0;
		branch = 1;
	}
	else if (op == 0x2)//j
	{
		RegWrite = 0;
		MemtoReg = 0;
		MemWrite = 0;
		aluctrl = 6;
		alusrc = 0;
		RegDst = 1;
		jump = 1;
		branch = 0;
	}
	else if (op == 0 && funct == 0x8)//jr
	{
		RegWrite = 0;
		MemtoReg = 0;
		MemWrite = 0;
		aluctrl = 6;
		alusrc = 0;
		RegDst = 1;
		jump = 0;
		branch = 0;
	}

}
void instCU::setinst(int x)
{
	inst = x;
	instdec(inst);
	control();
}