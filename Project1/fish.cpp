#include "fish.h"

using namespace sf;

fish::fish(Image &image, float X, float Y, float W, float H)	// Конструктор "рыбки" с параметрами
{
	life = true; 
	w = W; h = H;
	x = X; y = Y; 
	dx = 0.f; dy = 0.f;
	CurrentFrame = 0.f;
	speed = 0.f;

	texture.loadFromImage(image);	// Изображение в текстуру
	sprite.setTexture(texture);		// Текстуру в спрайт
}

FloatRect fish::getRect(){
	return FloatRect(x, y, w, h);
}
