#include "Bot.h"
#include "Search.h"

Board board;
ListOfCheckers checkers[2];

//���� ���������� ����� �� ������� �������, �.�. ����� ���������� ������ ��������� �����
extern "C" __declspec(dllexport) int __stdcall CallBot(int* w_coords, int* w_types, int w_n, int* b_coords, int* b_types, int b_n, int color) {
	
	//����������� �����
	checkers[WHITE].GenerateInitialPosition(WHITE, w_types, w_coords, w_n);
	checkers[BLACK].GenerateInitialPosition(BLACK, b_types, b_coords, b_n);

	board.Set(checkers[WHITE], checkers[BLACK]);

	//����� Search
	Move bestMove;
	SearchAlphaBeta(color, MaxDepth, -INF, INF, &bestMove);

	//�������������� bestMove � res: ����� �� ����(1���)->��������� ���������� �����(6)->�������� ���������� �����(6)->
	//->��������� �� ���(1)->��������� �����(12)
	int res=0;
	Move emptyMove;
	if (bestMove == emptyMove) res |= 1;
	else {
		res |= bestMove.GetStartCoord() << 1;
		res |= bestMove.GetFinalCoord() << 7;
		res |= bestMove.GetType() << 13;
		int eaten[MaxEaten]; bestMove.GetEaten(eaten);
		//������������ ������-������, ��� ��� ���������
		for (int i = 0; i < bestMove.GetNEaten(); i++) {
			res |= 1 << (14+eaten[i]-1);
		}
	}

	//�������
	checkers[WHITE].Clean();
	checkers[BLACK].Clean();
	board.Clean();

	return res;
}