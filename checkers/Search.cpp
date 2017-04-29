#include "Search.h"

Cache cache(MaxCache);

static int tmp;
int UsualSearch(int color, int depth, Move* bestMove, int ev_num = 0) {

	if (depth == 0)  return evaluate[ev_num](color);  //���� �� ��� �������

	int score = -INF;
	Move* saved = cache.GetpLast();

	Generate(checkers[color]);

	for (Move* pmove = saved; pmove < cache.GetpLast(); pmove++) {
		MakeMove(*pmove);
		tmp = -UsualSearch(!color, depth - 1,0, ev_num);
		UnMakeMove(*pmove);
		if (score < tmp) {
			score = tmp;
			if (bestMove) *bestMove = *pmove;
		}
	}

	cache.Rollback(saved);

	return score;
}


int SearchAlphaBeta(int color, int depth, int alpha, int beta, Move * bestMove, int ev_num=0) {

	if (depth == 0) return evaluate[ev_num](color); //���� �� ��� �������

	Move* saved = cache.GetpLast();
	Generate(checkers[color]);

	for (Move* pmove = saved; pmove < cache.GetpLast(); pmove++) {
		MakeMove(*pmove);
		tmp = -SearchAlphaBeta(!color, depth - 1, -beta, -alpha,0, ev_num);
		UnMakeMove(*pmove);
		
		if (tmp > alpha) {
			alpha = tmp;
			if (bestMove) *bestMove = *pmove;
		}
		if (alpha>=beta){
			cache.Rollback(saved);
			return alpha;//������� ��, ��� ������, ����� �� �����������
		}
	}

	cache.Rollback(saved);
	return alpha;
}

int Quies(int color, int alpha, int beta, int ev_num = 0) 
{
	Move* savedF = cache.GetpLast();
	GenerateForcing(checkers[color]); //GenerataForcing ����� ������� ���, ����� GenerateForcing ���������� �� ����� ������� �����������									  

	if (cache.GetpLast()-savedF <=0) return evaluate[ev_num](color);

	for (Move* pmove = savedF; pmove < cache.GetpLast(); pmove++) {
		MakeMove(*pmove);
		tmp = -Quies(!color, -beta, -alpha,  ev_num); //��������� ����������, ������� ����� ����� �� Move
		UnMakeMove(*pmove);

		if (tmp > alpha) {
			alpha = tmp;
		}
		if (alpha >= beta) {
			cache.Rollback(savedF);
			return alpha;//������� ��, ��� ������, ����� �� �����������
		}
	}

	cache.Rollback(savedF);
	return alpha;
}

int AlphaBetaForcing(int color, int depth, int alpha, int beta, Move * bestMove, int ev_num = 0)
{
	if (depth == 0)						   //���� �� ��� �������, ��������� ������������
	{
		return Quies(color, alpha, beta, ev_num);
	}

	Move* saved = cache.GetpLast();
	Generate(checkers[color]);

	for (Move* pmove = saved; pmove < cache.GetpLast(); pmove++) {
		MakeMove(*pmove);
		tmp = -AlphaBetaForcing(!color, depth - 1, -beta, -alpha, 0, ev_num);
		UnMakeMove(*pmove);

		if (tmp > alpha) {
			alpha = tmp;
			if (bestMove) *bestMove = *pmove;
		}
		if (alpha >= beta) {
			cache.Rollback(saved);
			return alpha;//������� ��, ��� ������, ����� �� �����������
		}
	}

	cache.Rollback(saved);
	return alpha;
}
void GenerateForcing(ListOfCheckers& list)
{

}