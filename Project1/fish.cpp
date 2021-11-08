#include "fish.h"

using namespace sf;

fish::fish(Image &image, float X, float Y, float W, float H)	// ����������� "�����" � �����������
{
	life = true; 
	w = W; h = H;
	x = X; y = Y; 
	dx = 0.f; dy = 0.f;
	CurrentFrame = 0.f;
	speed = 0.f;

	texture.loadFromImage(image);	// ����������� � ��������
	sprite.setTexture(texture);		// �������� � ������
}

FloatRect fish::getRect(){
	return FloatRect(x, y, w, h);
}
