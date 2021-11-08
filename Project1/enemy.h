#include "fish.h"	// Подключение класса "рыбки"

#ifndef ENEMY_H
#define ENEMY_H

class enemy:public fish{	// Класс "врага"
public:
	int dir;	// Переменная направления движения

	enemy(Image &image, float X, float Y, float W, float H);	
	void checkCollisionWithMap(float Dx, float Dy);	// Функция взаимодействия с картой
	void update(float time);	// Функция движения
	
	std::string* p_TileMap;
	void setTileMap(std::string* TileMap){ p_TileMap = TileMap; }	// Текущее значение TileMap
};
#endif