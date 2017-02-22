#include "ComputerMove.h"
#include<QTime>

ComputerMove::ComputerMove(ePiece (&arrBoard)[15][15])
{
	for(int i = 0; i< 15; i++)
	{
		for(int j = 0; j< 15; j++)
			m_arrBoard[i][j] = arrBoard[i][j];
	}
	x = 0;
	y = 0;
}


ComputerMove::~ComputerMove(void)
{
}

void ComputerMove::Computer_1()
{
	qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
	bool bOk = false;
	
	while(!bOk)
	{
		int randX = qrand()%15;
		int randY = qrand()%15;
		if(m_arrBoard[randX][randY] == NONE && randX != 0 && randY != 0)
		{
			x = randX;
			y = randY;
			bOk = true;
			return;
		}
	}

}
