#pragma once
#include"types.h"

#include<QVector>
class judgeWinner;
class Evaluation;

class ComputerMove
{
public:
	ComputerMove();
	~ComputerMove(void);

	int X(){return x;}
	int Y(){return y;}

	void Computer_1(ePiece (&arrBoard)[15][15]); //���������������

	void MaxMinSearch(ePiece (&arrBoard)[15][15], int deep);  //����Сֵ����

private:

	QVector<QVector<int>> GenCandidator(ePiece (&arrBoard)[15][15], ePiece piece);   //�������ӵ�λ��

	int MinSearch(ePiece (&arrBoard)[15][15], int deep, int alpha, int beta);
	int MaxSearch(ePiece (&arrBoard)[15][15], int deep, int alpha, int beta);

	int x;
	int y;

	judgeWinner * m_pJudgeWinner;
	Evaluation *m_pEvalution;
};

