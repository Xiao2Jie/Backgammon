#include "ComputerMove.h"
#include<QTime>
#include "judgeWinner.h"
#include "Evaluation.h"

ComputerMove::ComputerMove()
{
	x = 0;
	y = 0;

	m_pJudgeWinner = new judgeWinner;
	m_pEvalution = new Evaluation;
}


ComputerMove::~ComputerMove(void)
{
	delete m_pJudgeWinner;
	delete m_pEvalution;
}

void ComputerMove::Computer_1(ePiece (&arrBoard)[15][15])
{
	qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
	bool bOk = false;
	
	while(!bOk)
	{
		int randX = qrand()%15;
		int randY = qrand()%15;
		//if(m_arrBoard[randX][randY] == NONE && randX != 0 && randY != 0)
		if(arrBoard[randX][randY] == NONE)
		{
			x = randX;
			y = randY;
			bOk = true;
			return;
		}
	}

}


QVector<QVector<int>> ComputerMove::GenCandidator(ePiece (&arrBoard)[15][15], ePiece piece)
{
	QVector<QVector<int>> vecSum;
	for(int i = 0; i< 15; ++i)
	{
		for(int j = 0; j< 15; ++j)
		{
			//�ѿհ׵ĵ㵱����ѡ
			//if(arrBoard[i][j] == NONE)
			//{
			//	QVector<int> vec;
			//	vec.push_back(i);
			//	vec.push_back(j);
			//	vecSum.push_back(vec);
			//}
			if(arrBoard[i][j] == NONE)
			{
				//ĳ�������Χ�˸����Ƿ�������
				if((i-1>=0 && j-1>=0 && arrBoard[i-1][j-1] != NONE)||
					(i-1 >=0 &&arrBoard[i-1][j] != NONE) ||
					(i-1 >=0 && j+1<=14 && arrBoard[i-1][j+1] != NONE) ||
					(j-1>=0 && arrBoard[i][j-1] != NONE) ||
					(j+1<=14 && arrBoard[i][j+1] != NONE) ||
					(i+1<=14 && j-1>=0 && arrBoard[i+1][j-1] != NONE) ||
					(i+1<=14 && arrBoard[i+1][j] != NONE) ||
					(i+1<=14 && j+1 <=14 && arrBoard[i+1][j+1] != NONE))
				{
					QVector<int> vec;
					vec.push_back(i);
					vec.push_back(j);
					vecSum.push_back(vec);
				}
			}

		}
	}
	return vecSum;
}



void ComputerMove::MaxMinSearch(ePiece (&arrBoard)[15][15], int deep)
{
	QVector<QVector<int>> vecCandidator =  GenCandidator(arrBoard, WHITE);

	QVector<QVector<int>> vecBestPoints;
	int nBestScore = 0x8fffffff;  //��ֵ����С�ĸ���
	for(int i = 0; i< vecCandidator.size(); ++i)
	{
		QVector<int> vecPoint = vecCandidator[i];        //��ѡ�ĵ�
		arrBoard[vecPoint[0]][vecPoint[1]] = WHITE;     //������һ����
		int nScore = MinSearch(arrBoard, deep-1, nBestScore>0x8fffffff ? nBestScore:0x8fffffff, 0x7fffffff);     //Ԥ���������ӵķ���

		if(nScore == nBestScore)
		{
			vecBestPoints.push_back(vecPoint);
		}
		if(nScore >nBestScore)
		{
			nBestScore = nScore;
			vecBestPoints.clear();
			vecBestPoints.push_back(vecPoint);
		}
		arrBoard[vecPoint[0]][vecPoint[1]] = NONE;     //����µ���
	}
	
	//�ڷ�����ߵļ����������ѡһ��
	qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
	int index = qrand()%vecBestPoints.size();
	x = vecBestPoints[index][0];
	y = vecBestPoints[index][1];
}

int ComputerMove::MinSearch(ePiece (&arrBoard)[15][15], int deep, int alpha, int beta)
{
	int nScore = m_pEvalution->EvaluateBoard(arrBoard);
	if(deep <=0 || m_pJudgeWinner->IsWon(BLACK, arrBoard) || m_pJudgeWinner->IsWon(WHITE, arrBoard))
	{
		return nScore;
	}

	int nBestScore = 0x7fffffff;  //��ֵ�����ĵ�������Ҫѡ����С�ķ���
	QVector<QVector<int>> vecCandidator =  GenCandidator(arrBoard, BLACK);

	for(int i = 0; i< vecCandidator.size(); ++i)
	{
		QVector<int> vecPoint = vecCandidator[i];        //��ѡ�ĵ�
		arrBoard[vecPoint[0]][vecPoint[1]] = BLACK;     //������һ����
		int nScore = MaxSearch(arrBoard, deep-1, nBestScore<alpha?nBestScore:alpha, beta);     //Ԥ���������ӵķ���
		if(nScore < nBestScore)
			nBestScore = nScore;
		arrBoard[vecPoint[0]][vecPoint[1]] = NONE;

		//����min�㣬��Ҫ����һ�����ҵ���Сֵ����nScore��Ŀǰ�õ�����һ���һ��ֵ��
		//beta����һ��Ŀǰ�õ���һ�����ֵ������һ��Ҫѡ��һ�����ֵ����һ�㣬���Ŀǰ��
		//��������ڵ㣬��Ҫѡһ����Сֵ����ôѡ����ֵ�϶���С�ڵ���nScore�ģ�����һ����Ҫѡ�����ֵ
		//����һ�㣬��˿϶�����ѡ����ڵ��ˣ�������ӽڵ�ĺ�����ӽڵ㲻Ҫ�ˡ�
		if(nScore<beta)
			break;
	}
	return nBestScore;
}

int ComputerMove::MaxSearch(ePiece (&arrBoard)[15][15], int deep, int alpha, int beta)
{
	int nScore = m_pEvalution->EvaluateBoard(arrBoard);

	if(deep <=0 || m_pJudgeWinner->IsWon(BLACK, arrBoard) || m_pJudgeWinner->IsWon(WHITE, arrBoard))
	{
		return nScore;
	}

	int nBestScore = 0x8fffffff;  //��ֵ����С�ĸ�����Ҫѡ�����ķ���
	QVector<QVector<int>> vecCandidator =  GenCandidator(arrBoard, WHITE);

	for(int i = 0; i< vecCandidator.size(); ++i)
	{
		QVector<int> vecPoint = vecCandidator[i];        //��ѡ�ĵ�
		arrBoard[vecPoint[0]][vecPoint[1]] = WHITE;     //������һ����
		int nScore = MinSearch(arrBoard, deep-1, alpha, nBestScore>beta?nBestScore:beta);     //Ԥ���������ӵķ���
		if(nScore > nBestScore)
			nBestScore = nScore;
		arrBoard[vecPoint[0]][vecPoint[1]] = NONE; 		
		
		//����max�㣬Ҫ���ӽڵ����ҵ�һ��max,Ŀǰ�ӽڵ��и�ֵ��nScore,��ô����ڵ��ֵ�϶��Ͳ���С��nScore�ˣ�
		//����һ����min�㣬��Ҫ����һ�����ҵ�һ��min����Ŀǰ��һ���min��alpha�����nScore����alpha����ô�϶�����ѡ������ڵ���
		//��������ӽڵ������ֵܽڵ㶼��Ҫ�ˡ�
		if(nScore>alpha)
			break;
	}
	return nBestScore;
}
