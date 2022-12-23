#include "Logic.h"

using namespace std;

int evaluationFunction::userIntInput()
{
	int input = 0;
	std::cin >> input;
	while (!(std::cin.good()))
	{
		std::cout << "Input error! Enter again" << std::endl;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cin >> input;
	}
	return input;
}
evaluationFunction::evaluationFunction(unsigned int n) : N(n), field(), res(NULL), white(0), black(0), whiteMove(true), whiteWin(false), blackWin(false)
{
	field = new int* [N];
	for (size_t i{}; i < N; i++) {
		field[i] = new int[N];
	}
	for (size_t i{}; i < N; i++) {
		for (size_t j{}; j < N; j++) {
			field[i][j] = 0;
		}
	}

}
/*
Функция оценки игровой ситуации(оценочная функция)
Ввод: -
Вывод: целое, результат
*/
int evaluationFunction::evalFunc(int** f) {
	for (size_t i{}; i < N; i++) {
		for (size_t j{}; j < N; j++) {
			if (field[i][j] == 1) white++;
			if (field[i][j] == -1) black++;
		}
	}
	res = white - black;
	return res;
}
/*
Вывод игрового поля в консоль
Ввод: -
Вывод: -
*/
void evaluationFunction::printField() {
	std::cout << std::endl;
	std::cout << "     ";
	for (size_t i{}; i < N; i++) {
		std::cout << std::setw(2) << "[" << i << "]";
	}
	std::cout << std::endl;
	std::cout << "     ";
	for (size_t i{}; i < N; i++) {
		std::cout << std::setw(3) << "____";
	}
	std::cout << std::endl;
	for (size_t i{}; i < N; i++) {
		std::cout << std::setw(2) << "[" << i << "]" << "|";
		for (size_t j{}; j < N; j++) {
			std::cout << std::setw(3) << field[j][i] << " ";
		}
		std::cout << std::endl;
	}

}
/*
Вывод отладочной информации в консоль
Ввод: -
Вывод: -
*/
void evaluationFunction::debuggingInformation() {
	std::cout << std::endl << "res = " << res << std::endl;
	std::cout << "White: " << white << "| Black: " << black << std::endl;
	if (res > 0) std::cout << "White checkers win by a margin of: " << abs(res) << std::endl;
	else if (res < 0) std::cout << "Black checkers win by a margin of: " << abs(res) << std::endl;
	else if (res == 0) std::cout << "Draw" << std::endl;
	else {
		std::cerr << "Error in evalFunc" << std::endl;
		exit(-1);
	}
}
/*
Случайное заполение поля чёрными и белыми шашками
Ввод: -
Вывод: -
*/
void evaluationFunction::randomField()
{
	srand(time(0));
	for (size_t i{}; i < N * N; i++) {
		field[rand() % N][rand() % N] = (rand() % 3) - 1;
	}
}
/*



*/
void evaluationFunction::move() {
	unsigned int m{}, n{};
	int chose{};
	whiteMove = true;
	if (whiteMove == true) {
		std::cout << "Enter WHITE checker position[i]: ";
		m = evaluationFunction::userIntInput();
		std::cout << "[j]";
		n = evaluationFunction::userIntInput();
		if (field[m][n] == 1) {
			while (true) {
				chose = _getch();
				if ((chose == 75) || (chose == 72) || (chose == 77) || (chose == 80)) { break; }
			}
			if (chose == 72) {	// вверх
				if (m - 1 < N && field[m - 1][n] != 1 && field[m - 1][n] != -1) {
					field[m - 1][n] = field[m][n];
					field[m][n] = 0;
					whiteMove = false;
					return;
				}
				else if (m - 2 < N && field[m - 2][n] == 0 && (field[m - 1][n] == 1 || field[m - 1][n] == -1)) {
					field[m - 2][n] = field[m][n];
					field[m][n] = 0;
					whiteMove = false;
					return;
				}
				else {
					std::cout << std::endl;
					std::cout << "Whong position";
				}
			}
			if (chose == 80) { //down
				if (m + 1 < N && field[m + 1][n] != 1 && field[m + 1][n] != -1) {
					field[m + 1][n] = field[m][n];
					field[m][n] = 0;
					whiteMove = false;
					return;
				}
				else if (m + 2 < N && field[m + 2][n] == 0 && (field[m + 1][n] == 1 || field[m + 1][n] == -1)) {
					field[m + 2][n] = field[m][n];
					field[m][n] = 0;
					whiteMove = false;
					return;
				}
				else {
					std::cout << std::endl;
					std::cout << "Whong position";
				}
			}
			if (chose == 77) { // right
				if (n + 1 < N && field[m][n + 1] != 1 && field[m][n + 1] != -1) {
					field[m][n + 1] = field[m][n];
					field[m][n] = 0;
					whiteMove = false;
					return;
				}
				else if (n + 2 < N && field[m][n + 2] == 0 && (field[m][n + 1] == 1 || field[m][n + 1] == -1)) {
					field[m][n + 2] = field[m][n];
					field[m][n] = 0;
					whiteMove = false;
					return;
				}
				else {
					std::cout << std::endl;
					std::cout << "Whong position";
				}
			}
			if (chose == 75) {
				if (n - 1 < N && field[m][n - 1] != 1 && field[m][n - 1] != -1) {
					field[m][n - 1] = field[m][n];
					field[m][n] = 0;
					whiteMove = false;
					return;
				}
				else if (n - 2 < N && field[m][n - 2] == 0 && (field[m][n - 1] == 1 || field[m][n - 1] == -1)) {
					field[m][n - 2] = field[m][n];
					field[m][n] = 0;
					whiteMove = false;
					return;
				}
				else {
					std::cout << std::endl;
					std::cout << "Whong position";
				}
			}
		}
	}
	else {
		std::cout << "These no white checker";
	}
}
/*
Проверяет победил ли кто-то
Ввод: -
Вывод: -
*/
bool evaluationFunction::win() {
	if (white == 0) {
		blackWin = true;
		return blackWin;
	}
	if (black == 0) {
		whiteWin = true;
		return whiteWin;
	}
	else {
		return false;
	}
}
int** evaluationFunction::getNowField()
{
	return field;
}
void evaluationFunction::setNowField(int** arr)
{
	field = arr;
	return;
}
evaluationFunction::pos* evaluationFunction::minmax(int** fld, int alpha, int beta, bool turn, int depth)
{
	pos* back{nullptr};
	pos* cur{nullptr};
	if (depth == 3) {
		cur = new pos();
		cur->mark = evalFunc(fld);
	}
	else 
	{
		int** fld_copy{nullptr};
		fld_copy = new int* [N];
		for (size_t m{}; m < N; m++) {
			fld_copy[m] = new int[N];
			for (size_t n{}; n < N; n++) {
				fld_copy[m][n] = fld[m][n];
			}
		}
		for (int m{}; m < N; m++) {
			for (int n{}; n < N; n++) {
				if(fld_copy[m][n]==1 && turn==true){ //Ход человека
				if (m - 1 >= 0 && fld_copy[m - 1][n] == 0) { //влево
					fld_copy[m - 1][n] = fld_copy[m][n];
					fld_copy[m][n] = 0;
					eated(fld_copy);
					back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
					back->X = m - 1;
					back->Y = n;
					back->CX = m;
					back->CY = n;
					if (turn==true) {		// ход человека
						cur = min(cur, back);
						beta = cur->mark;
					}
					else if (turn==false) { // ход компьютера
						cur = max(cur, back);
						alpha = cur->mark;
					}
					if (alpha > beta) { break; }
					for (size_t m{}; m < N; m++) {
						for (size_t n{}; n < N; n++) {
							fld_copy[m][n] = fld[m][n];
						}
					}
				}
				if (m - 2 >= 0 && fld_copy[m - 2][n] == 0 && (fld_copy[m - 1][n] == 1 || fld_copy[m - 1][n] == -1)) {
					fld_copy[m - 2][n] = fld_copy[m][n];
					fld_copy[m][n] = 0;
					eated(fld_copy);
					back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
					back->X = m - 2;
					back->Y = n;
					back->CX = m;
					back->CY = n;
					if (turn == true) {
						cur = min(cur, back);
						beta = cur->mark;
					}
					else if (turn == false) {
						cur = max(cur, back);
						alpha = cur->mark;
					}
					if (alpha > beta) { break; }
					for (size_t m{}; m < N; m++) {
						for (size_t n{}; n < N; n++) {
							fld_copy[m][n] = fld[m][n];
						}
					}
				}
				if (m + 1 < N && fld_copy[m + 1][n] != 1 && fld_copy[m + 1][n] != -1) { //вправо
					fld_copy[m + 1][n] = fld_copy[m][n];
					fld_copy[m][n] = 0;
					eated(fld_copy);
					back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
					back->X = m + 1;
					back->Y = n;
					back->CX = m;
					back->CY = n;
					if (turn == true) {
						cur = min(cur, back);
						beta = cur->mark;
					}
					else if (turn == false) {
						cur = max(cur, back);
						alpha = cur->mark;
					}
					if (alpha > beta) { break; }
					for (size_t m{}; m < N; m++) {
						for (size_t n{}; n < N; n++) {
							fld_copy[m][n] = fld[m][n];
						}
					}
				}
				if (m + 2 < N && fld_copy[m + 2][n] == 0 && (fld_copy[m + 1][n] == 1 || fld_copy[m + 1][n] == -1)) {
					fld_copy[m + 2][n] = fld_copy[m][n];
					fld_copy[m][n] = 0;
					eated(fld_copy);
					back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
					back->X = m + 2;
					back->Y = n;
					back->CX = m;
					back->CY = n;
					if (turn == true) {
						cur = min(cur, back);
						beta = cur->mark;
					}
					else if (turn == false) {
						cur = max(cur, back);
						alpha = cur->mark;
					}
					if (alpha > beta) { break; }
					for (size_t m{}; m < N; m++) {
						for (size_t n{}; n < N; n++) {
							fld_copy[m][n] = fld[m][n];
						}
					}
				}
				if (n + 1 < N && fld_copy[m][n + 1] != 1 && fld_copy[m][n + 1] != -1) { //вверх
					fld_copy[m][n + 1] = fld_copy[m][n];
					fld_copy[m][n] = 0;
					eated(fld_copy);
					back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
					back->X = m;
					back->Y = n+1;
					back->CX = m;
					back->CY = n;
					if (turn == true) {
						cur = min(cur, back);
						beta = cur->mark;
					}
					else if (turn == false) {
						cur = max(cur, back);
						alpha = cur->mark;
					}
					if (alpha > beta) { break; }
					for (size_t m{}; m < N; m++) {
						for (size_t n{}; n < N; n++) {
							fld_copy[m][n] = fld[m][n];
						}
					}
				}
				if (n + 2 < N && fld_copy[m][n + 2] == 0 && (fld_copy[m][n + 1] == 1 || fld_copy[m][n + 1] == -1)) {
					fld_copy[m][n + 2] = fld_copy[m][n];
					fld_copy[m][n] = 0;
					eated(fld_copy);
					back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
					back->X = m;
					back->Y = n + 2;
					back->CX = m;
					back->CY = n;
					if (turn == true) {
						cur = min(cur, back);
						beta = cur->mark;
					}
					else if (turn == false) {
						cur = max(cur, back);
						alpha = cur->mark;
					}
					if (alpha > beta) { break; }
					for (size_t m{}; m < N; m++) {
						for (size_t n{}; n < N; n++) {
							fld_copy[m][n] = fld[m][n];
						}
					}
				}
				if (n - 1 >= 0 && fld_copy[m][n - 1] != 1 && fld_copy[m][n - 1] != -1) { //вниз
					fld_copy[m][n - 1] = fld_copy[m][n];
					fld_copy[m][n] = 0;
					eated(fld_copy);
					back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
					back->X = m;
					back->Y = n - 1;
					back->CX = m;
					back->CY = n;
					if (turn == true) {
						cur = min(cur, back);
						beta = cur->mark;
					}
					else if (turn == false) {
						cur = max(cur, back);
						alpha = cur->mark;
					}
					if (alpha > beta) { break; }
					for (size_t m{}; m < N; m++) {
						for (size_t n{}; n < N; n++) {
							fld_copy[m][n] = fld[m][n];
						}
					}
				}
				if (n - 2 >= 0 && fld_copy[m][n - 2] == 0 && (fld_copy[m][n - 1] == 1 || fld_copy[m][n - 1] == -1)) {
					fld_copy[m][n - 2] = fld_copy[m][n];
					fld_copy[m][n] = 0;
					eated(fld_copy);
					back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
					back->X = m;
					back->Y = n-2;
					back->CX = m;
					back->CY = n;
					if (turn == true) {
						cur = min(cur, back);
						beta = cur->mark;
					}
					else if (turn == false) {
						cur = max(cur, back);
						alpha = cur->mark;
					}
					if (alpha > beta) { break; }
					for (size_t m{}; m < N; m++) {
						for (size_t n{}; n < N; n++) {
							fld_copy[m][n] = fld[m][n];
						}
					}
				}
				}
				if (fld_copy[m][n] == -1 && turn == false) { //Ход компа
					if (m - 1 >= 0 && fld_copy[m - 1][n] != 1 && fld_copy[m - 1][n] != -1) { //влево
						fld_copy[m - 1][n] = fld_copy[m][n];
						fld_copy[m][n] = 0;
						eated(fld_copy);
						back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
						back->X = m - 1;
						back->Y = n;
						back->CX = m;
						back->CY = n;
						if (turn == true) {		// ход человека
							cur = min(cur, back);
							beta = cur->mark;
						}
						else if (turn == false) { // ход компьютера
							cur = max(cur, back);
							alpha = cur->mark;
						}
						if (alpha > beta) { break; }
						for (size_t m{}; m < N; m++) {
							for (size_t n{}; n < N; n++) {
								fld_copy[m][n] = fld[m][n];
							}
						}
					}
					if (m - 2 >= 0 && fld_copy[m - 2][n] == 0 && (fld_copy[m - 1][n] == 1 || fld_copy[m - 1][n] == -1)) {
						fld_copy[m - 2][n] = fld_copy[m][n];
						fld_copy[m][n] = 0;
						eated(fld_copy);
						back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
						back->X = m - 2;
						back->Y = n;
						back->CX = m;
						back->CY = n;
						if (turn == true) {
							cur = min(cur, back);
							beta = cur->mark;
						}
						else if (turn == false) {
							cur = max(cur, back);
							alpha = cur->mark;
						}
						if (alpha > beta) { break; }
						for (size_t m{}; m < N; m++) {
							for (size_t n{}; n < N; n++) {
								fld_copy[m][n] = fld[m][n];
							}
						}
					}
					if (m + 1 < N && fld_copy[m + 1][n] != 1 && fld_copy[m + 1][n] != -1) { //вправо
						fld_copy[m + 1][n] = fld_copy[m][n];
						fld_copy[m][n] = 0;
						eated(fld_copy);
						back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
						back->X = m + 1;
						back->Y = n;
						back->CX = m;
						back->CY = n;
						if (turn == true) {
							cur = min(cur, back);
							beta = cur->mark;
						}
						else if (turn == false) {
							cur = max(cur, back);
							alpha = cur->mark;
						}
						if (alpha > beta) { break; }
						for (size_t m{}; m < N; m++) {
							for (size_t n{}; n < N; n++) {
								fld_copy[m][n] = fld[m][n];
							}
						}
					}
					if (m + 2 < N && fld_copy[m + 2][n] == 0 && (fld_copy[m + 1][n] == 1 || fld_copy[m + 1][n] == -1)) {
						fld_copy[m + 2][n] = fld_copy[m][n];
						fld_copy[m][n] = 0;
						eated(fld_copy);
						back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
						back->X = m + 2;
						back->Y = n;
						back->CX = m;
						back->CY = n;
						if (turn == true) {
							cur = min(cur, back);
							beta = cur->mark;
						}
						else if (turn == false) {
							cur = max(cur, back);
							alpha = cur->mark;
						}
						if (alpha > beta) { break; }
						for (size_t m{}; m < N; m++) {
							for (size_t n{}; n < N; n++) {
								fld_copy[m][n] = fld[m][n];
							}
						}
					}
					if (n + 1 < N && fld_copy[m][n + 1] != 1 && fld_copy[m][n + 1] != -1) { //вверх
						fld_copy[m][n + 1] = fld_copy[m][n];
						fld_copy[m][n] = 0;
						eated(fld_copy);
						back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
						back->X = m;
						back->Y = n + 1;
						back->CX = m;
						back->CY = n;
						if (turn == true) {
							cur = min(cur, back);
							beta = cur->mark;
						}
						else if (turn == false) {
							cur = max(cur, back);
							alpha = cur->mark;
						}
						if (alpha > beta) { break; }
						for (size_t m{}; m < N; m++) {
							for (size_t n{}; n < N; n++) {
								fld_copy[m][n] = fld[m][n];
							}
						}
					}
					if (n + 2 < N && fld_copy[m][n + 2] == 0 && (fld_copy[m][n + 1] == 1 || fld_copy[m][n + 1] == -1)) {
						fld_copy[m][n + 2] = fld_copy[m][n];
						fld_copy[m][n] = 0;
						eated(fld_copy);
						back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
						back->X = m;
						back->Y = n+2;
						back->CX = m;
						back->CY = n;
						if (turn == true) {
							cur = min(cur, back);
							beta = cur->mark;
						}
						else if (turn == false) {
							cur = max(cur, back);
							alpha = cur->mark;
						}
						if (alpha > beta) { break; }
						for (size_t m{}; m < N; m++) {
							for (size_t n{}; n < N; n++) {
								fld_copy[m][n] = fld[m][n];
							}
						}
					}
					if (n - 1 >= 0 && fld_copy[m][n - 1] != 1 && fld_copy[m][n - 1] != -1) { //вниз
						fld_copy[m][n - 1] = fld_copy[m][n];
						fld_copy[m][n] = 0;
						eated(fld_copy);
						back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
						back->X = m;
						back->Y = n - 1;
						back->CX = m;
						back->CY = n;
						if (turn == true) {
							cur = min(cur, back);
							beta = cur->mark;
						}
						else if (turn == false) {
							cur = max(cur, back);
							alpha = cur->mark;
						}
						if (alpha > beta) { break; }
						for (size_t m{}; m < N; m++) {
							for (size_t n{}; n < N; n++) {
								fld_copy[m][n] = fld[m][n];
							}
						}
					}
					if (n - 2 >= 0 && fld_copy[m][n - 2] == 0 && (fld_copy[m][n - 1] == 1 || fld_copy[m][n - 1] == -1)) {
						fld_copy[m][n - 2] = fld_copy[m][n];
						fld_copy[m][n] = 0;
						eated(fld_copy);
						back = minmax(fld_copy, alpha, beta, !turn, depth + 1);
						back->X = m;
						back->Y = n - 2;
						back->CX = m;
						back->CY = n;
						if (turn == true) {
							cur = min(cur, back);
							beta = cur->mark;
						}
						else if (turn == false) {
							cur = max(cur, back);
							alpha = cur->mark;
						}
						if (alpha > beta) { break; }
						for (size_t m{}; m < N; m++) {
							for (size_t n{}; n < N; n++) {
								fld_copy[m][n] = fld[m][n];
							}
						}
					}
				}
			}
		}
		for (size_t i{}; i < N; i++) {
			delete[] fld_copy[i];
		}
		delete[] fld_copy;
	}
	return cur;
}
evaluationFunction::pos* evaluationFunction::min(pos* a1, pos* a2)
{
	if (a1 == nullptr) {
		return a2;
	}
	if (a2 == nullptr) {
		return a1;
	}
	if (a1->mark == a2->mark) {
		return a1;
	}
	return a1->mark < a2->mark ? a1 : a2;
}
evaluationFunction::pos* evaluationFunction::max(pos* a1, pos* a2)
{
	if (a1 == nullptr) {
		return a2;
	}
	if (a2 == nullptr) {
		return a1;
	}
	if (a1->mark == a2->mark) {
		return a1;
	}
	return a1->mark > a2->mark ? a1 : a2;
}
void evaluationFunction::eated(int** arr)
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			count = 0;
			/////////////////////////////////////////////////////
			if (arr[i][j] == 1) {
				if (j + 1 < N && arr[i][j + 1] == -1) {
					count += 1;
				}
				if (j - 1 >= 0 && arr[i][j - 1] == -1) {
					count += 1;
				}
				if (i + 1 < N && arr[i + 1][j] == -1) {
					count += 1;
				}
				if (i - 1 >= 0 && arr[i - 1][j] == -1) {
					count += 1;
				}
				if (count >= 3) { arr[i][j] = 0; }
			}
			if (arr[i][j] == -1) {
				if (j + 1 < N && arr[i][j + 1] == 1) {
					count += 1;
				}
				if (j - 1 >= 0 && arr[i][j - 1] == 1) {
					count += 1;
				}
				if (i + 1 < N && arr[i + 1][j] == 1) {
					count += 1;
				}
				if (i - 1 >= 0 && arr[i - 1][j] == 1) {
					count += 1;
				}
				if (count >= 3) { arr[i][j] = 0; }
			}
		}
	}
}
/* Деструктор */
evaluationFunction::~evaluationFunction()
{
	if (field != nullptr) {
		for (size_t i{}; i < N; i++) {
			delete[] field[i];
		}
		delete[] field;
	}
}