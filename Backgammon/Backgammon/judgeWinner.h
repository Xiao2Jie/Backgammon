#pragma once
#include "types.h"
class judgeWinner
{
public:
	judgeWinner();
	~judgeWinner(void);
	bool IsWon(ePiece piece, ePiece (&array)[15][15]);

	bool SituationHor();  //����
	bool SituationVer();  //����
	bool SituationLef();  //������б��
	bool SituationRig();  //������б��
private:
	ePiece m_piece;
	ePiece m_arrBoard[15][15];
};

