#include <iostream>
#include <SFML/Graphics.hpp>
#include "Logic.h"

using namespace sf;

int main()
{
	const int gridSize = 8;			// размер пол€
	const int w = 32;				// размер текстуры клетки пол€
	evaluationFunction Game(gridSize);
	Game.randomField();
	int** tempField = Game.getNowField();
	Game.printField();
	Game.evalFunc();
	RenderWindow app(VideoMode(gridSize *w, gridSize * w), "The Game!");
	// √лавный цикл приложени€: выполн€етс€, пока открыто окно
	while (app.isOpen())
	{
		int gridView[gridSize][gridSize];

		Texture t;
		t.loadFromFile("img/map.png");
		Sprite s(t);

		for (int i = 0; i < gridSize; i++)
			for (int j = 0; j < gridSize; j++)
			{
				gridView[i][j] = (i+j)%2;
				if (tempField[i][j] != 0) {
					if (gridView[i][j] == 0 and tempField[i][j] == -1){
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
		// ”станавливаем белый фон
		app.clear(Color::White);
		for (int i = 0; i < gridSize; i++) {
			for (int j = 0; j < gridSize; j++)
			{
				// ¬ырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));
				// ”станавливаем его в заданную позицию...
				s.setPosition(i * w, j * w);
				// ... и отрисовываем
				app.draw(s);
			}
		}
		// ќтображаем всю композицию на экране
		app.display();
		while (!Game.win()) {
			Game.move();
			tempField = Game.getNowField();
			Game.printField();
			for (int i = 0; i < gridSize; i++)
				for (int j = 0; j < gridSize; j++)
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
			// ”станавливаем белый фон
			app.clear(Color::White);
			for (int i = 0; i < gridSize; i++) {
				for (int j = 0; j < gridSize; j++)
				{
					// ¬ырезаем из спрайта нужный нам квадратик текстуры
					s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));
					// ”станавливаем его в заданную позицию...
					s.setPosition(i * w, j * w);
					// ... и отрисовываем
					app.draw(s);
				}
			}
		}
		Event event;
		while (app.pollEvent(event))
		{
			// ѕользователь нажал на Ђкрестикї и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				app.close();
		}
	}

	return 0;
}