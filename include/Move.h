#pragma once

// _ _ | 62 _ _ _ _ ... _ _ _ _ (��������� ����� (10)) 22_ _ _ _ (���������� ��������� �����) 18_ _ _  _ _ _ (�������� ����������) 12_ _ _  _ _ _ (��������� ����������) 6_ _ _ _ (����� �����)  2_ (��������� �� ���) 1_ (���� �����, �� �����������)

typedef unsigned long long ull;
#define BLACK 1
#define WHITE 0

#define DAMKA 1
#define CHECKER 0


#define OFFSET_COLOR 0
#define OFFSET_TYPE 1
#define OFFSET_NUM 2
#define OFFSET_COORD_S 6
#define OFFSET_COORD_F 12
#define OFFSET_NEATEN 18
#define OFFSET_EATEN 22

#define MASK_COLOR 1
#define MASK_TYPE 1
#define MASK_NUM 15
#define MASK_COORD_F 63
#define MASK_COORD_S 63
#define MASK_NEATEN 15
#define MASK_EATEN (ull)1099511627775

#define INVMASK_COLOR ~(MASK_COLOR<<OFFSET_COLOR)
#define INVMASK_TYPE ~(MASK_TYPE<<OFFSET_TYPE)
#define INVMASK_NUM ~(MASK_NUM<<OFFSET_NUM)
#define INVMASK_COORD_S ~(MASK_COORD_S<<OFFSET_COORD_S)
#define INVMASK_COORD_F ~(MASK_COORD_F<<OFFSET_COORD_F)
#define INVMASK_NEATEN ~(MASK_NEATEN<<OFFSET_NEATEN)
#define INVMASK_EATEN ((ull)~(MASK_EATEN<<OFFSET_EATEN))

const int MaxEaten = 10;

class Move {
	ull move;
public:
	Move() { move = 0; }
	Move(int n) { move = n; }
	operator long long() { return move; }
	friend int operator==(const Move& m1, const Move& m2);
	~Move() {}

	void Set(int _color, int _s_coord, int _f_coord, int _num, int _type) { SetColor(_color); SetStartCoord(_s_coord); SetFinalCoord(_f_coord); SetNum(_num); SetType(_type); }
	void SetVarEaten(ull n1,...);

	void SetColor(ull color) { move = move & INVMASK_COLOR | (color << OFFSET_COLOR); }
	void SetStartCoord(ull coord) { move = move & INVMASK_COORD_S | (coord << OFFSET_COORD_S); }
	void SetFinalCoord(ull coord) { move = move & INVMASK_COORD_F | (coord << OFFSET_COORD_F); }
	void SetNum(ull num) { move = move & INVMASK_NUM | (num << OFFSET_NUM); }
	void SetType(ull type) { move = move & INVMASK_TYPE | (type << OFFSET_TYPE); }
	void SetNEaten(ull neaten) { move = move & INVMASK_NEATEN | (neaten << OFFSET_NEATEN); }
	void SetEaten(ull eaten) { move = move & INVMASK_EATEN | (eaten << OFFSET_EATEN); }
	void SetEaten(int* arrEaten) 
	{ move = move & INVMASK_EATEN; 
	for (int i = 0; i < GetNEaten(); i++) 
		move = move | ((ull)arrEaten[i] << (OFFSET_EATEN + 4 * i)); }

	int GetColor() { return move & MASK_COLOR; }
	int GetStartCoord() { return (move >> OFFSET_COORD_S) & MASK_COORD_S; }
	int GetFinalCoord() { return (move >> OFFSET_COORD_F) & MASK_COORD_F; }
	int GetNum() { return (move >> OFFSET_NUM) & MASK_NUM; }
	int GetType() { return (move >> OFFSET_TYPE) & MASK_TYPE; }
	int GetNEaten() { return (move >> OFFSET_NEATEN) & MASK_NEATEN; }
	long long GetEaten() { return (move >> OFFSET_EATEN) & MASK_EATEN; }
	void GetEaten(int* arrEaten) 
	{ for (int i = 0; i < 10; i++) 
		arrEaten[i] = (move >> (OFFSET_EATEN + i * 4)) & MASK_NUM; }
};