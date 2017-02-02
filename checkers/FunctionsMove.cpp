#include "FunctionsMove.h"

#define CELL_ON_BOARD(cell) (cell>>6==0)
#define CELL_IS_BLACK(cell) (((cell>>3)^cell)&1)

int color; //� ���������� �������� � Generate
int coord;

inline int Inside(int cell)
{
	return (CELL_ON_BOARD(cell) && CELL_IS_BLACK(cell));
}

inline int CanMove(int route)	//������ ��� ������� �����
{
	return (Inside(coord+route) && board.IsEmpty(coord + route));
}

inline int CanEat(int route)	//������ ��� ������� �����
{
	return (!board.IsEmpty(coord+route)&&Inside(coord+2*route) && board.IsEmpty(coord+2*route)&&(board[coord+route]->GetColor()!=color));
}

Move temp_move;
inline Move GetMove(Checker *ch) { //������ ��� ������� �����
	//temp_move.SetColor(color);
	temp_move.SetNum(ch->GetNum());
	temp_move.SetCoord(ch->GetCoord());
	return temp_move;
}

int SearchMoveChecker(Checker *ch)
{
	color = ch->GetColor(); //� ���������� �������� � Generate
	coord = ch->GetCoord(); //�� ���� ���������
	if (CanEat(backRight[color])) return 1;
	if (CanEat(backLeft[color])) return 1;
	if (CanEat(forwardLeft[color])) return 1;
	if (CanEat(forwardRight[color])) return 1;

	if (CanMove(forwardRight[color])) cache.Push(GetMove(ch));
	if (CanMove(forwardLeft[color])) cache.Push(GetMove(ch));

	return 0;
}

int SearchMoveDamka(Checker *ch)
{
	return 0;
}