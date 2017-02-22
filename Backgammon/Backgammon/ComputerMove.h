#pragma once
#include"types.h"
class ComputerMove
{
public:
	ComputerMove(ePiece (&arrBoard)[15][15]);
	~ComputerMove(void);

	int X(){return x;}
	int Y(){return y;}

	void Computer_1(); //最初级，随意落子
private:
	ePiece m_arrBoard[15][15];
	int x;
	int y;
};

