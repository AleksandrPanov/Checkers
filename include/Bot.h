#pragma once
#include "Search.h"
//���� ���������� ����� �� ������� �������, �.�. ����� ���������� ������ ��������� �����
extern "C" __declspec(dllexport) int __stdcall CallBot(
	int* w_coords,int* w_types,int w_n,
	int* b_coords, int* b_types, int b_n,
	int color//,
	//int type_search, int max_depth
);
