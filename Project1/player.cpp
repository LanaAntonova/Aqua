#include "player.h"	// Подключение класса "игрока"

player::player(Image &image, float X, float Y, float W, float H) : fish(image, X, Y, W, H){	// Конструктор "игрока" с параметрами
	health = 3;		// 3 жизни
	sprite.setTextureRect(IntRect(36, 36, -w, h));	//Задаем спрайту прямоугольник
}

player::~player() {
	p_TileMap = NULL;
}

// Функция управления по клавишам
void player::control(){
	if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A))) {
		state = left;
		speed = 0.1f;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D))) {
		state = right;
		speed = 0.1f;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W))) {
		state = up;
		speed = 0.1f;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S))) {
		state = down;
		speed = 0.1f;
	}
}

// Функция взаимодействия игрока с картой
void player::checkCollisionWithMap(float Dx, float Dy)
{
	for (unsigned i = y / 32; i < (y + h) / 32; i++)
	for (unsigned j = x / 32; j<(x + w) / 32; j++){
		if (p_TileMap[i][j] == '0' || p_TileMap[i][j] == '2' ||	
			p_TileMap[i][j] == '3' || p_TileMap[i][j] == '4'){	// Столкновение с границами аквариума
			if (Dy>0){ 
				y = i * 32 - h; dy = 0.f;
			}
			else if (Dy<0){ 
				y = i * 32 + 32; dy = 0.f;
			}
			else if(Dx>0){ 
				x = j * 32 - w; dx = 0.f;
			}
			else if(Dx<0){ 
				x = j * 32 + 32; dx = 0.f;
			}
		}
		if (p_TileMap[i][j] == '5') {	// Поедание креветки
			health++;
			sprite.setScale(Vector2f(1.1f, 1.1f));	// Рост игрока
			p_TileMap[i][j] = ' ';
		}
	}
}

// Функция движения игрока
void player::update(float time)
{
	if (life) {
		control();	// Вызов функции управления
		switch (state)
		{
		case right:	//вправо
			dx = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame) + 36, 36, -36, 36)); // Анимация движения вправо
			break;
		case left:	//влево
			dx = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 36, 36, 36));	// Анимация движения влево
			break;
		case down:	//вниз
			dy = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 0, 36, 36));	// Анимация движения вниз
			break;
		case up:	//вверх
			dy = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 72, 36, 36));	// Анимация движения вверх
			break;
		}

		x += dx*time;	//движение по X
		checkCollisionWithMap(dx, 0.f);	// Вызов функции столкновений по X
		y += dy*time;	//движение по Y
		checkCollisionWithMap(0.f, dy);	// Вызов функции столкновений по Y

		speed = 0.f;	// Прекращение движения без нажатой клавиши
		sprite.setPosition(x, y);	// Вывод спрайта в позицию (x, y)
		if (health <= 0) {
			life = false;
		}
	}
}