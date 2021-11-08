#include "fish.h"	// Подключение класса "рыбки"

#ifndef PLAYER_H
#define PLAYER_H

class player:public fish{	// Класс "игрока"
public:
	unsigned health;

	player(Image &image, float X, float Y, float W, float H);	// Конструктор "игрока"	
	~player();	// Деструктор "игрока"
	void update(float time);	// Функция движения игрока
	void setTileMap(std::string* TileMap){ p_TileMap = TileMap; }	// Текущее значение TileMap

private:
	void control();	// Функция управления
	void checkCollisionWithMap(float Dx, float Dy);	// Функция взаимодействия с картой

	std::string* p_TileMap;
};
#endif