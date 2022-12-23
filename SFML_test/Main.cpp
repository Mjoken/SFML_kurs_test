#include <iostream>
#include <SFML/Graphics.hpp>
#include "Logic.h"

using namespace sf;

int main()
{
	const int gridSize = 8;		// размер поля
	const int w = 32;				// размер текстуры клетки поля
	int posX{}, posY{};
	struct ch {
		bool chose{ false };
		int pX{}, pY{};
		unsigned int check{0};		// 5 - white on white; 3 - white on black; 2 - black on white; 4 - black on black
	};
	ch turn;
	bool whiteTurn{ true };
	Time t3;
	Clock c3;
	size_t count{};

	evaluationFunction Game(gridSize);
	Game.randomField();
	int** tempField = Game.getNowField();
	Game.printField();
	Game.evalFunc();


	RenderWindow app(VideoMode(gridSize *w, gridSize * w), "The Game!", Style::Titlebar | Style::Close);
	Texture t;
	t.loadFromFile("img/map.png");
	Sprite s(t);
	///////
	int gridView[gridSize][gridSize];

	for (size_t i = 0; i < gridSize; i++) {
		for (size_t j = 0; j < gridSize; j++)
		{
			gridView[i][j] = (i + j) % 2;
			if (tempField[i][j] != 0) {
				if (gridView[i][j] == 0 and tempField[i][j] == -1) {
					gridView[i][j] = 4;
				}
				else if (gridView[i][j] == 0 and tempField[i][j] == 1) {
					gridView[i][j] = 3;
				}
				else if (gridView[i][j] == 1 and tempField[i][j] == -1) {
					gridView[i][j] = 2;
				}
				else if (gridView[i][j] == 1 and tempField[i][j] == 1) {
					gridView[i][j] = 5;
				}
			}
		}
	}
	//////
	// Главный цикл приложения: выполняется, пока открыто окно
	while (app.isOpen())
	{
		t3 = c3.getElapsedTime();
		if (t3.asSeconds() >= 5) {
			c3.restart();
			for (int i = 0; i < gridSize; i++) 
			{
				for (int j = 0; j < gridSize; j++)
				{
					count = 0;
						if (gridView[i][j] == 0 || gridView[i][j] == 1) {
							tempField[i][j] = 0;
						}
						else if (gridView[i][j] == 2 || gridView[i][j] == 4) {
							tempField[i][j] = -1;
						}
						else if (gridView[i][j] == 3 || gridView[i][j] == 5) {
							tempField[i][j] = 1;
						}
						if (tempField[i][j] == 1) {
							if (j + 1 < gridSize && tempField[i][j + 1]==-1) {
								count += 1;
							}
							if (j + 1 >= 0 && tempField[i][j - 1]==-1) {
								count += 1;
							}
							if (i + 1 < gridSize && tempField[i + 1][j]==-1) {
								count += 1;
							}
							if (i - 1 >= 0 && tempField[i - 1][j]==-1) {
								count += 1;
							}
							if (count >= 3) { gridView[i][j] = (i + j) % 2; }
						}
						if (tempField[i][j] == -1) {
							if (j + 1 < gridSize && tempField[i][j + 1] == 1) {
								count += 1;
							}
							if (j + 1 >= 0 && tempField[i][j - 1] == 1) {
								count += 1;
							}
							if (i + 1 < gridSize && tempField[i + 1][j] == 1) {
								count += 1;
							}
							if (i - 1 >= 0 && tempField[i - 1][j] == 1) {
								count += 1;
							}
							if (count >= 3) { gridView[i][j] = (i + j) % 2; }
						}
				}
			}
			Game.setNowField(tempField);
			Game.printField();
		}
		Vector2i pixelPos = Mouse::getPosition(app);//забираем коорд курсора
		Vector2f pos = app.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		//std::cout << pos.x << "\n";//смотрим на Х,которая преобразовалась в мировые координаты
		posX = pos.x / w;
		posY = pos.y / w;
		Event event;
		while (app.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				app.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left && turn.chose == false) {
					if ((gridView[posX][posY] == 2 || gridView[posX][posY] == 4) && whiteTurn == false) { // black check
						if (gridView[posX][posY] == 2) { turn.check = 2; }
						else { turn.check = 4; }
						turn.chose = true;
						turn.pX = posX;
						turn.pY = posY;
						gridView[posX][posY] = 6;
					}
					if ((gridView[posX][posY] == 3 || gridView[posX][posY] == 5) && whiteTurn == true) { // white check
						if (gridView[posX][posY] == 3) { turn.check = 3; }
						else { turn.check = 5; }
						turn.chose = true;
						turn.pX = posX;
						turn.pY = posY;
						gridView[posX][posY] = 7;
					}
				}
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape && turn.chose == true) {
					gridView[turn.pX][turn.pY] = turn.check;
					turn.chose = false;
				}
				if ((event.key.code == Keyboard::Up || event.key.code == Keyboard::W) && turn.chose == true) {			// Ход Вверх
					if (turn.pY - 1 > -1 && gridView[turn.pX][turn.pY - 1] == 0 || gridView[turn.pX][turn.pY - 1] == 1) {
						if (turn.check == 5) { gridView[turn.pX][turn.pY - 1] = 3; }
						if (turn.check == 3) { gridView[turn.pX][turn.pY - 1] = 5; }
						if (turn.check == 2) { gridView[turn.pX][turn.pY - 1] = 4; }
						if (turn.check == 4) { gridView[turn.pX][turn.pY - 1] = 2; }
						if (turn.check == 5 || turn.check == 2) { gridView[turn.pX][turn.pY] = 1; }
						else if (turn.check == 3 || turn.check == 4) { gridView[turn.pX][turn.pY] = 0; }
						whiteTurn = !whiteTurn;
						turn.chose = false;
					}
					else if (turn.pY - 2 > -1 && gridView[turn.pX][turn.pY - 2] == 0 || gridView[turn.pX][turn.pY - 2] == 1 && (gridView[turn.pX][turn.pY - 1] >= 2 || gridView[turn.pX][turn.pY - 1] <= 5)) {
						gridView[turn.pX][turn.pY - 2] = turn.check;
						if (turn.check == 5 || turn.check == 2) { gridView[turn.pX][turn.pY] = 1; }
						else if (turn.check == 3 || turn.check == 4) { gridView[turn.pX][turn.pY] = 0; }
						whiteTurn = !whiteTurn;
						turn.chose = false;
					}
				}
				if ((event.key.code == Keyboard::Down || event.key.code == Keyboard::S) && turn.chose == true) {			// Ход Вниз
					if (turn.pY + 1 < gridSize && gridView[turn.pX][turn.pY + 1] == 0 || gridView[turn.pX][turn.pY + 1] == 1) {
						if (turn.check == 5) { gridView[turn.pX][turn.pY + 1] = 3; }
						if (turn.check == 3) { gridView[turn.pX][turn.pY + 1] = 5; }
						if (turn.check == 2) { gridView[turn.pX][turn.pY + 1] = 4; }
						if (turn.check == 4) { gridView[turn.pX][turn.pY + 1] = 2; }
						if (turn.check == 5 || turn.check == 2) { gridView[turn.pX][turn.pY] = 1; }
						else if (turn.check == 3 || turn.check == 4) { gridView[turn.pX][turn.pY] = 0; }
						whiteTurn = !whiteTurn;
						turn.chose = false;
					}
					else if (turn.pY + 2 < gridSize && gridView[turn.pX][turn.pY + 2] == 0 || gridView[turn.pX][turn.pY + 2] == 1 && (gridView[turn.pX][turn.pY + 1] >= 2 || gridView[turn.pX][turn.pY + 1] <= 5)) {
						gridView[turn.pX][turn.pY + 2] = turn.check;
						if (turn.check == 5 || turn.check == 2) { gridView[turn.pX][turn.pY] = 1; }
						else if (turn.check == 3 || turn.check == 4) { gridView[turn.pX][turn.pY] = 0; }
						whiteTurn = !whiteTurn;
						turn.chose = false;
					}
				}
				if ((event.key.code == Keyboard::Left || event.key.code == Keyboard::A) && turn.chose == true) {			// Ход Влево
					if (turn.pX - 1 > -1 && gridView[turn.pX - 1][turn.pY] == 0 || gridView[turn.pX - 1][turn.pY] == 1) {
						if (turn.check == 5) { gridView[turn.pX - 1][turn.pY] = 3; }
						if (turn.check == 3) { gridView[turn.pX - 1][turn.pY] = 5; }
						if (turn.check == 2) { gridView[turn.pX - 1][turn.pY] = 4; }
						if (turn.check == 4) { gridView[turn.pX - 1][turn.pY] = 2; }
						if (turn.check == 5 || turn.check == 2) { gridView[turn.pX][turn.pY] = 1; }
						else if (turn.check == 3 || turn.check == 4) { gridView[turn.pX][turn.pY] = 0; }
						whiteTurn = !whiteTurn;
						turn.chose = false;
					}
					else if (turn.pX - 2 > -1 && gridView[turn.pX - 2][turn.pY] == 0 || gridView[turn.pX - 2][turn.pY] == 1 && (gridView[turn.pX - 2][turn.pY] >= 2 || gridView[turn.pX - 2][turn.pY] <= 5)) {
						gridView[turn.pX - 2][turn.pY] = turn.check;
						if (turn.check == 5 || turn.check == 2) { gridView[turn.pX][turn.pY] = 1; }
						else if (turn.check == 3 || turn.check == 4) { gridView[turn.pX][turn.pY] = 0; }
						whiteTurn = !whiteTurn;
						turn.chose = false;
					}
				}
				if ((event.key.code == Keyboard::Right || event.key.code == Keyboard::D) && turn.chose == true) {			// Ход вправо
					if (turn.pX + 1 < gridSize && gridView[turn.pX + 1][turn.pY] == 0 || gridView[turn.pX + 1][turn.pY] == 1) {
						if (turn.check == 5) { gridView[turn.pX + 1][turn.pY] = 3; }
						if (turn.check == 3) { gridView[turn.pX + 1][turn.pY] = 5; }
						if (turn.check == 2) { gridView[turn.pX + 1][turn.pY] = 4; }
						if (turn.check == 4) { gridView[turn.pX + 1][turn.pY] = 2; }
						if (turn.check == 5 || turn.check == 2) { gridView[turn.pX][turn.pY] = 1; }
						else if (turn.check == 3 || turn.check == 4) { gridView[turn.pX][turn.pY] = 0; }
						whiteTurn = !whiteTurn;
						turn.chose = false;
					}
					else if (turn.pX + 2 < gridSize && gridView[turn.pX + 2][turn.pY] == 0 || gridView[turn.pX + 2][turn.pY] == 1 && (gridView[turn.pX + 2][turn.pY] >= 2 || gridView[turn.pX + 2][turn.pY] <= 5)) {
						gridView[turn.pX + 2][turn.pY] = turn.check;
						if (turn.check == 5 || turn.check == 2) { gridView[turn.pX][turn.pY] = 1; }
						else if (turn.check == 3 || turn.check == 4) { gridView[turn.pX][turn.pY] = 0; }
						whiteTurn = !whiteTurn;
						turn.chose = false;
					}
				}

			}
		}

		// Устанавливаем белый фон
		app.clear(Color::White);
		for (int i = 0; i < gridSize; i++) {
			for (int j = 0; j < gridSize; j++)
			{
				// Вырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));
				// Устанавливаем его в заданную позицию...
				s.setPosition(i * w, j * w);
				// ... и отрисовываем
				app.draw(s);
			}
		}
		// Отображаем всю композицию на экране
		app.display();

	}

	return 0;
}