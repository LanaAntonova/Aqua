#include <SFML/Graphics.hpp>

#ifndef FISH_H
#define FISH_H

using namespace sf;

class fish {	// Класс "рыбки"
public:
	Image image;		//	изображение
	Texture texture;	//	текстура
	Sprite sprite;		//	спрайт

	fish(Image &image, float X, float Y, float W, float H);
	FloatRect getRect();

protected:
	enum { left, right, up, down } state;	// Состояния объекта

	bool life;					// Переменные жизни,
	int w, h;					// параметров
	float x, y, dx, dy;			// персонажа,
	float CurrentFrame, speed;	// кадра и скорости
};
#endif