#pragma once

#include"types.h"
#include<QVector>
/************************************************************************/
/* 
�����̷ֳɺ���б���֣�ÿһ�п���һ��vector,�ٶ�ÿһ������
*/
/************************************************************************/

class Evaluation
{
public:
	Evaluation(void);
	~Evaluation(void);
	int EvaluateBoard(ePiece (&arrBoard)[15][15]);

private:

	//�����̰��պ���б�ֳ������������ÿһ�ж����һ������
	QVector<QVector<ePiece>> CutBoard(ePiece (&arrBoard)[15][15]);  //�ָ����̳ɶ��һά����
	
	//�Ե�ǰĳ�����ӵľ�������
	int Score(ePiece (&arrBoard)[15][15], ePiece piece, QVector<QVector<ePiece>> &vecSum);  //��ÿ����������
	
	//�жϵ�ǰ�е������������
	bool IsOpenOne(QVector<ePiece> vec, int index, ePiece piece);
	bool IsOpenTwo(QVector<ePiece> vec, int index, ePiece piece);
	bool IsOpenThree(QVector<ePiece> vec, int index, ePiece piece);
	bool IsOpenFour(QVector<ePiece> vec, int index, ePiece piece);
	bool IsFive(QVector<ePiece> vec, int index, ePiece piece);
	bool IsCloseOne(QVector<ePiece> vec, int index, ePiece piece);
	bool IsCloseTwO(QVector<ePiece> vec, int index, ePiece piece);
	bool IsCloseThree(QVector<ePiece> vec, int index, ePiece piece);
	bool IsCloseFour(QVector<ePiece> vec, int index, ePiece piece);
};

