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
Функция userInput
Проверки ввода типа int
Ввод: -
Вывод: переменная типа int
*/

class evaluationFunction
{
public:
	evaluationFunction(unsigned int n); // конструктор класса evaluationFunction| параметры: размер поля n*n
	~evaluationFunction();				// деструктор класса evaluationFunction 
	int userIntInput();
	int evalFunc(int** f);						// функция сравнения
	void printField();					// функция вывода игрового поля в консоль поля
	void debuggingInformation();		// функция вывода отладочной информации в консоль
	void randomField();					// функция случайного заполенения поля
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
	int white;							// число белых шашек(счётчик)
	int black;							// число чёрных шашек(счётчик)
	int** field;						// указатель на начала двумерного массива поля
	unsigned int N;						// размера КВАДРАТНОГО поля
	int res;							// результат работы оценочной функции
	bool whiteMove;
	bool whiteWin;
	bool blackWin;
};