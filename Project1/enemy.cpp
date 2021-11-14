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
		if (e_TileMap[i][j] == '3' || e_TileMap[i][j] == '4'){	// Проверка столкновений с границами карты
			if (Dx>0){
				x = j * 32 - w; dx = 0.08f;
				dir = 0;
			}
			else if (Dx<0){
				x = j * 32 + 32; dx = 0.08f;
				dir = 1;
			}
		}
	}
}

// Функция движения врага
void enemy::update(float time){
	if (life) {
		switch (dir)
		{
		case right:	//вправо
			dx = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(39 * int(CurrentFrame) + 39, 0, -39, 34));	// Анимация движения вправо
			break;
		case left:	//влево
			dx = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(39 * int(CurrentFrame), 0, 39, 34));	// Анимация движения влево
			break;
		}

		x += dx*time;	//движение по X
		checkCollisionWithMap(dx, 0.f);	// Вызов функции столкновений по X

		sprite.setPosition(x, y);	// Вывод спрайта в позицию (x, y)
		if (health <= 0) {
			life = false;
		}
	}
}