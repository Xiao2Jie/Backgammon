#pragma once
enum ePiece  //�������
{
	NONE = 0,
	WHITE = 1,
	BLACK = 2
};

enum eScore
{
	OPEN_ONE = 10,  //open Ϊ���߿���  closeΪһ�߿���
	OPEN_TWO = 100,
	OPEN_THREE = 1000,
	OPEN_FOUR = 1000000,
	FIVE = 10000000,
	
	CLOSE_ONE = 1,
	CLOSE_TWO = 10,
	CLOSE_THREE = 100,
	CLOSE_FOUR  = 1000,
};