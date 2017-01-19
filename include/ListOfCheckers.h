#pragma once
#include "Checker.h"

class LChIterator {
	Checker* begin; //��������� �� ������ ������ 
					//�� ���� ���� ����� ����������, ������ ���� ������� �� ����� ��������� �����, � ���������� �� ��������� �����
	Checker* p; //�����, �� ������� ��������� ��������
public:
	LChIterator(Checker* p_, Checker* begin_) :p(p_), begin(begin_) {};

	LChIterator& operator++() { p = begin + p->GetNextNum(); return *this; }
	LChIterator& operator--() { p = begin + p->GetPrevNum(); return *this; }
	LChIterator& operator++(int) { p = begin + p->GetNextNum(); return *this; }
	LChIterator& operator--(int) { p = begin + p->GetPrevNum(); return *this; }

	operator Checker* () { return p; }
	operator int() { return p - begin; }

	Checker operator* (LChIterator it) { return *(it.p); }
	friend int operator==(LChIterator it, Checker* pch) { if (pch == it.p) return 1; return 0; }
	friend int operator!=(LChIterator it1, LChIterator it2) { if (it1 == it2) return 0; return 1; }
};


class ListOfCheckers {				
	Checker List[13];	//12 ����� + ������, ����� ������ ������� �� ��� ������
						//����� ���������� �� 1 �� 12
public:
	ListOfCheckers();							//��������� ������
	~ListOfCheckers() {}

	void GenerateInitialPosition(char* filename="");	//��������:���������� �������������� �������

	void Insert(int num);						//��������� ����� � ������
	void Delete(int num);						//������� ����� �� ������

	int IsEmpty() { if (List[0].GetNextNum() == 0) return 1; return 0; }
	Checker& operator[] (int i) { return List[i]; }

	typedef LChIterator iterator;
	iterator begin() { return iterator(&(List[List[0].GetNextNum()]),List); }
	iterator end() { return iterator(List, List); }
};
