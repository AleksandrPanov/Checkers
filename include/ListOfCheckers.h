#pragma once
#include "Checker.h"

/*
����� � ��� ���� ������ head->1->4->6->8->11->head (������ head=0)
Delete(1);
Delete(8);
head->4->6->11->head
Insert(7);
head->4->6->7->11->head
Insert(1);
head->1->4->6->7->11->head
*/

/*�����, �������� ��������?*/

class ListOfCheckers {
private:				
	Checker List[13];	//12 ����� + ������, ����� ������ ������� �� ��� ������
						//����� ����� ������������ �� 1 �� 12
public:
	ListOfCheckers();							//��������� �������������� ������ ����� ������������
	~ListOfCheckers() {}

	void GenerateInitialPosition(char* filename);	//���������� �������������� ������� ��� ����� ���.�����

	void Insert(int num);						//?//��������� ����� � ������� � ������, �� ������� ��������������� �������
	void Delete(int num);						//������� ����� � ������� �� ������

	int IsEmpty() { if (List[0].GetNextNum() == 0) return 1; return 0; }
	Checker& operator[] (int i) { return List[i]; }
	int GetFirstNum() { return List[0].GetNextNum(); }
};