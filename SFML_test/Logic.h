#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <conio.h>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <conio.h>

/*
������� userInput
�������� ����� ���� int
����: -
�����: ���������� ���� int
*/

class evaluationFunction
{
public:
	evaluationFunction(unsigned int n); // ����������� ������ evaluationFunction| ���������: ������ ���� n*n
	~evaluationFunction();				// ���������� ������ evaluationFunction 
	int userIntInput();
	int evalFunc(int** f);						// ������� ���������
	void printField();					// ������� ������ �������� ���� � ������� ����
	void debuggingInformation();		// ������� ������ ���������� ���������� � �������
	void randomField();					// ������� ���������� ����������� ����
	void move();
	bool win();
	int** getNowField();
	void setNowField(int** arr);
	struct pos {
		int X{}, Y{}, mark{}, CX{}, CY{};
	};
	pos* minmax(int** fld , int alpha, int beta, bool turn, int depth = 0);
	pos* min(pos* a1, pos* a2);
	pos* max(pos* a1, pos* a2);
	void eated(int** arr);
private:
	int white;							// ����� ����� �����(�������)
	int black;							// ����� ������ �����(�������)
	int** field;						// ��������� �� ������ ���������� ������� ����
	unsigned int N;						// ������� ����������� ����
	int res;							// ��������� ������ ��������� �������
	bool whiteMove;
	bool whiteWin;
	bool blackWin;
};