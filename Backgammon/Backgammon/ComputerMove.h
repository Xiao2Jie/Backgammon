#pragma once
#include"types.h"

#include<QVector>
class judgeWinner;

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
	int Evaluate(ePiece (&arrBoard)[15][15]);  //���ۺ���
	QVector<QVector<int>> GenCandidator(ePiece (&arrBoard)[15][15], ePiece piece);   //�������ӵ�λ��
	QVector<QVector<ePiece>> CutBoard(ePiece (&arrBoard)[15][15]);  //�ָ����̳ɶ��һά����
	int Score(ePiece (&arrBoard)[15][15], ePiece piece, QVector<QVector<ePiece>> &vecSum);  //��ÿ����������
	bool IsOpenOne(QVector<ePiece> vec, int index, ePiece piece);
	bool IsOpenTwo(QVector<ePiece> vec, int index, ePiece piece);
	bool IsOpenThree(QVector<ePiece> vec, int index, ePiece piece);
	bool IsOpenFour(QVector<ePiece> vec, int index, ePiece piece);
	bool IsFive(QVector<ePiece> vec, int index, ePiece piece);
	bool IsCloseOne(QVector<ePiece> vec, int index, ePiece piece);
	bool IsCloseTwO(QVector<ePiece> vec, int index, ePiece piece);
	bool IsCloseThree(QVector<ePiece> vec, int index, ePiece piece);
	bool IsCloseFour(QVector<ePiece> vec, int index, ePiece piece);

	int MinSearch(ePiece (&arrBoard)[15][15], int deep);
	int MaxSearch(ePiece (&arrBoard)[15][15], int deep);


	//ePiece m_arrBoard[15][15];
	int x;
	int y;
	//int nSearchDeep;
	judgeWinner * m_pJudgeWinner;
};

