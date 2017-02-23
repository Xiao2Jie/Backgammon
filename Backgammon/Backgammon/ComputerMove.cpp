#include "ComputerMove.h"
#include<QTime>
#include "judgeWinner.h"


ComputerMove::ComputerMove()
{
	//for(int i = 0; i< 15; i++)
	//{
	//	for(int j = 0; j< 15; j++)
	//		m_arrBoard[i][j] = arrBoard[i][j];
	//}
	x = 0;
	y = 0;

	//nSearchDeep = 4;

	m_pJudgeWinner = new judgeWinner;

}


ComputerMove::~ComputerMove(void)
{
	delete m_pJudgeWinner;
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

/************************************************************************/
/* 
将棋盘分成横竖斜四种，每一行看成一个vector,再对每一行评分
*/
/************************************************************************/
int ComputerMove::Evaluate(ePiece (&arrBoard)[15][15])
{
	int nScore = 0;
	QVector<QVector<ePiece>> vecSum = CutBoard(arrBoard);

	nScore = Score(arrBoard, WHITE, vecSum) - Score(arrBoard, BLACK, vecSum);

	return nScore;
}

QVector<QVector<int>> ComputerMove::GenCandidator(ePiece (&arrBoard)[15][15], ePiece piece)
{
	QVector<QVector<int>> vecSum;
	for(int i = 0; i< 15; ++i)
	{
		for(int j = 0; j< 15; ++j)
		{
			//把空白的点当作候选
			//if(arrBoard[i][j] == NONE)
			//{
			//	QVector<int> vec;
			//	vec.push_back(i);
			//	vec.push_back(j);
			//	vecSum.push_back(vec);
			//}
			if(arrBoard[i][j] == NONE)
			{
				//某个点的周围八个点是否有点
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

QVector<QVector<ePiece>> ComputerMove::CutBoard(ePiece (&arrBoard)[15][15])
{
	QVector<QVector<ePiece>> vecSum;

	//横
	for(int j = 0; j < 15; j++)
	{
		QVector<ePiece> vec;
		for(int i = 0; i< 15; i++)
		{
			vec.push_back(arrBoard[i][j]);
		}
		vecSum.push_back(vec);
	}

	//竖
	for(int j = 0; j < 15; j++)
	{
		QVector<ePiece> vec;
		for(int i = 0; i< 15; i++)
		{
			vec.push_back(arrBoard[j][i]);
		}
		vecSum.push_back(vec);
	}

	//左上到右下
	for(int j = 14; j>=0; --j)
	{
		QVector<ePiece> vec;
		int m = 0; 
		int n = j; 
		while(n<15)
		{
			vec.push_back(arrBoard[m][n]);
			++n;
			++m;
		}
		vecSum.push_back(vec);
	}
	for(int i = 1; i< 15; ++i)
	{
		QVector<ePiece> vec;
		int m = i; 
		int n = 0; 
		while(m<15)
		{
			vec.push_back(arrBoard[m][n]);
			++n;
			++m;
		}
		vecSum.push_back(vec);
	}

	//右上到左下
	for(int j = 14; j>=0; --j)
	{
		QVector<ePiece> vec;
		int m = 14; 
		int n = j; 
		while(n<15)
		{
			vec.push_back(arrBoard[m][n]);
			++n;
			--m;
		}
		vecSum.push_back(vec);
	}
	for(int i = 13; i >= 0; --i)
	{
		QVector<ePiece> vec;
		int m = i; 
		int n = 0; 
		while(m>=0)
		{
			vec.push_back(arrBoard[m][n]);
			++n;
			--m;
		}
		vecSum.push_back(vec);
	}

	return vecSum;
}

int ComputerMove::Score(ePiece (&arrBoard)[15][15], ePiece piece, QVector<QVector<ePiece>> &vecSum)
{
	int nSocre = 0;
	for(int i = 0; i< vecSum.size(); ++i)
	{
		for(int j = 0; j< vecSum[i].size(); ++j)
		{
			if(IsOpenOne(vecSum[i], j, piece))
			{
				nSocre += OPEN_ONE;
			}
			else if(IsOpenTwo(vecSum[i], j, piece))
			{
				nSocre += OPEN_TWO;
			}
			else if(IsOpenThree(vecSum[i], j, piece))
			{
				nSocre += OPEN_THREE;
			}
			else if(IsOpenFour(vecSum[i], j, piece))
			{
				nSocre += OPEN_FOUR;
			}
			else if(IsFive(vecSum[i], j, piece))
			{
				nSocre += FIVE;
			}
			else if(IsCloseOne(vecSum[i], j, piece))
			{
				nSocre += CLOSE_ONE;
			}
			else if(IsCloseTwO(vecSum[i], j, piece))
			{
				nSocre += CLOSE_TWO;
			}
			else if(IsCloseThree(vecSum[i], j, piece))
			{
				nSocre += CLOSE_THREE;
			}
			else if(IsCloseFour(vecSum[i], j, piece))
			{
				nSocre += CLOSE_FOUR;
			}
			else
				nSocre += 0;
		}
	}
	return nSocre;
}

bool ComputerMove::IsOpenOne(QVector<ePiece> vec, int index, ePiece piece)
{
	if(index-1>= 0 && index+1 <= vec.size()-1)
	{
		if(vec[index-1] == NONE && vec[index+1] == NONE && vec[index] == piece)
		{
			return true;
		}
	}
	return false;
}

bool ComputerMove::IsOpenTwo(QVector<ePiece> vec, int index, ePiece piece)
{
	if(index-1>= 0 && index+2 <= vec.size()-1)
	{
		if(vec[index-1] == NONE &&
			vec[index+2] == NONE &&
			vec[index] == piece &&
			vec[index+1] == piece)
		{
			return true;
		}
	}
	return false;
}

bool ComputerMove::IsOpenThree(QVector<ePiece> vec, int index, ePiece piece)
{
	if(index-1>= 0 && index+3 <= vec.size()-1)
	{
		if(vec[index-1] == NONE &&
			vec[index+3] == NONE &&
			vec[index] == piece &&
			vec[index+1] == piece &&
			vec[index+2] == piece)
		{
			return true;
		}
	}
	return false;
}

bool ComputerMove::IsOpenFour(QVector<ePiece> vec, int index, ePiece piece)
{
	if(index-1>= 0 && index+4 <= vec.size()-1)
	{
		if(vec[index-1] == NONE &&
			vec[index+4] == NONE &&
			vec[index] == piece &&
			vec[index+1] == piece &&
			vec[index+2] == piece &&
			vec[index+3] == piece)
		{
			return true;
		}
	}
	return false;
}

bool ComputerMove::IsFive(QVector<ePiece> vec, int index, ePiece piece)
{
	if(index+4 <= vec.size()-1)
	{
		if(	vec[index+4] == piece &&
			vec[index] == piece &&
			vec[index+1] == piece &&
			vec[index+2] == piece &&
			vec[index+3] == piece)
		{
			return true;
		}
	}
	return false;
}

bool ComputerMove::IsCloseOne(QVector<ePiece> vec, int index, ePiece piece)
{
	if(vec.size()>1 && index == 0 && vec[index] == piece && vec[index+1] == NONE )  //在最左边
	{
		return true;
	}
	else if(vec.size()>1 && index == vec.size()-1 && vec[index] == piece && vec[index-1] == NONE)  //在最右边
	{
		return true;
	}
	else if(vec.size()>2 && index-1>=0 && index+1<=vec.size()-1 && vec[index] == piece)  //在中间
	{
		if(vec[index-1] != piece && vec[index-1] != NONE && vec[index+1] == NONE)
		{
			return true;
		}
		else if(vec[index+1] != piece && vec[index+1] != NONE && vec[index-1] == NONE)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool ComputerMove::IsCloseTwO(QVector<ePiece> vec, int index, ePiece piece)
{
	if(vec.size()>2 && index == 0 && vec[index] == piece && vec[index+1] == piece && vec[index+2] == NONE )  //在最左边
	{
		return true;
	}
	else if(vec.size()>2 && index == vec.size()-1 && vec[index] == piece && vec[index-1] == piece && vec[index-2] == NONE)  //在最右边
	{
		return true;
	}
	else if(vec.size()>3 && index-1>=0 && index+2<=vec.size()-1 && vec[index] == piece&& vec[index+1] == piece)  //在中间
	{
		if(vec[index-1] != piece && vec[index-1] != NONE && vec[index+2] == NONE)
		{
			return true;
		}
		else if(vec[index+2] != piece && vec[index+2] != NONE && vec[index-1] == NONE)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool ComputerMove::IsCloseThree(QVector<ePiece> vec, int index, ePiece piece)
{
	if(vec.size()>3 && index == 0 && vec[index] == piece && vec[index+1] == piece && vec[index+2] == piece &&vec[index+3] == NONE)  //在最左边
	{
		return true;
	}
	else if(vec.size()>3 && index == vec.size()-1 && vec[index] == piece && vec[index-1] == piece && vec[index-2] == piece && vec[index-3] == NONE)  //在最右边
	{
		return true;
	}
	else if(vec.size()>4 && index-1>=0 && index+3<=vec.size()-1 && vec[index] == piece&& vec[index+1] == piece&& vec[index+2] == piece)  //在中间
	{
		if(vec[index-1] != piece && vec[index-1] != NONE && vec[index+3] == NONE)
		{
			return true;
		}
		else if(vec[index+3] != piece && vec[index+3] != NONE && vec[index-1] == NONE)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool ComputerMove::IsCloseFour(QVector<ePiece> vec, int index, ePiece piece)
{
	if(vec.size()>4 && index == 0 && vec[index] == piece && vec[index+1] == piece && vec[index+2] == piece&& vec[index+3] == piece &&vec[index+4] == NONE)  //在最左边
	{
		return true;
	}
	else if(vec.size()>4 && index == vec.size()-1 && vec[index] == piece && vec[index-1] == piece && vec[index-2] == piece&& vec[index-3] == piece && vec[index-4] == NONE)  //在最右边
	{
		return true;
	}
	else if(vec.size()>5 && index-1>=0 && index+4<=vec.size()-1 && vec[index] == piece&& vec[index+1] == piece&& vec[index+2] == piece&& vec[index+3] == piece)  //在中间
	{
		if(vec[index-1] != piece && vec[index-1] != NONE && vec[index+4] == NONE)
		{
			return true;
		}
		else if(vec[index+4] != piece && vec[index+4] != NONE && vec[index-1] == NONE)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void ComputerMove::MaxMinSearch(ePiece (&arrBoard)[15][15], int deep)
{
	QVector<QVector<int>> vecCandidator =  GenCandidator(arrBoard, WHITE);

	QVector<QVector<int>> vecBestPoints;
	int nBestScore = -100000000;
	for(int i = 0; i< vecCandidator.size(); ++i)
	{
		QVector<int> vecPoint = vecCandidator[i];        //待选的点
		arrBoard[vecPoint[0]][vecPoint[1]] = WHITE;     //机器下一个子
		int nScore = MinSearch(arrBoard, deep-1);     //预估人类下子的分数

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
		arrBoard[vecPoint[0]][vecPoint[1]] = NONE;     //清除下的子
	}
	
	//在分数最高的几个点中随机选一个
	qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
	int index = qrand()%vecBestPoints.size();
	x = vecBestPoints[index][0];
	y = vecBestPoints[index][1];
}

int ComputerMove::MinSearch(ePiece (&arrBoard)[15][15], int deep)
{
	int nScore = Evaluate(arrBoard);
	if(deep <=0 || m_pJudgeWinner->IsWon(BLACK, arrBoard) || m_pJudgeWinner->IsWon(WHITE, arrBoard))
	{
		return nScore;
	}

	int nBestScore = 100000000;  //选出最小的分数
	QVector<QVector<int>> vecCandidator =  GenCandidator(arrBoard, BLACK);

	for(int i = 0; i< vecCandidator.size(); ++i)
	{
		QVector<int> vecPoint = vecCandidator[i];        //待选的点
		arrBoard[vecPoint[0]][vecPoint[1]] = BLACK;     //人类下一个子
		int nScore = MaxSearch(arrBoard, deep-1);     //预估机器下子的分数
		if(nScore < nBestScore)
			nBestScore = nScore;
		arrBoard[vecPoint[0]][vecPoint[1]] = NONE;     
	}
	return nBestScore;
}

int ComputerMove::MaxSearch(ePiece (&arrBoard)[15][15], int deep)
{
	int nScore = Evaluate(arrBoard);
	if(deep <=0 || m_pJudgeWinner->IsWon(BLACK, arrBoard) || m_pJudgeWinner->IsWon(WHITE, arrBoard))
	{
		return nScore;
	}

	int nBestScore = -100000000;  //选出最大的分数
	QVector<QVector<int>> vecCandidator =  GenCandidator(arrBoard, WHITE);

	for(int i = 0; i< vecCandidator.size(); ++i)
	{
		QVector<int> vecPoint = vecCandidator[i];        //待选的点
		arrBoard[vecPoint[0]][vecPoint[1]] = WHITE;     //机器下一个子
		int nScore = MinSearch(arrBoard, deep-1);     //预估人类下子的分数
		if(nScore > nBestScore)
			nBestScore = nScore;
		arrBoard[vecPoint[0]][vecPoint[1]] = NONE;     
	}
	return nBestScore;
}
