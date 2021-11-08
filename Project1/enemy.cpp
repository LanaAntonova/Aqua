#include "enemy.h"

enemy::enemy(Image &image, float X, float Y, float W, float H) : fish(image, X, Y, W, H){	// Конструктор "врага" с параметрами
	speed = 0.08f;
	dx = speed;
	dir = rand() % (2);
	sprite.setTextureRect(IntRect(40, 0, -w, h));	//Задаем спрайту прямоугольник
}

// Функция взаимодействия врага с картой
void enemy::checkCollisionWithMap(float Dx, float Dy){
	for (unsigned i = y / 32; i < (y + h) / 32; i++)
	for (unsigned j = x / 32; j<(x + w) / 32; j++){
		if (p_TileMap[i][j] == '3' || p_TileMap[i][j] == '4'){	// Проверка столкновений с границами карты
			if (Dx>0){
				x = j * 32 - w; dx = 0.08f;
				dir = rand() % (2);
			}
			else if (Dx<0){
				x = j * 32 + 32; dx = 0.08f;
				dir = rand() % (2);
			}
		}
	}
}

// Функция движения врага
void enemy::update(float time){
	switch (dir)
	{
	case right:	//вправо
		dx = speed;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(40 * int(CurrentFrame) + 40, 0, -40, 40));	// Анимация движения вправо
		break;
	case left:	//влево
		dx = -speed;
		CurrentFrame += 0.005*time;											
		if (CurrentFrame > 3) CurrentFrame -= 3;							
		sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 40));	// Анимация движения влево
		break;
	}

	x += dx*time;	//движение по X
	checkCollisionWithMap(dx, 0.f);	// Вызов функции столкновений по X

	sprite.setPosition(x, y);	// Вывод спрайта в позицию (x, y)
}