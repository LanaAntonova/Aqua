#include <SFML/Graphics.hpp>

#ifndef FISH_H
#define FISH_H

using namespace sf;

class fish {	// ����� "�����"
public:
	Image image;		//	�����������
	Texture texture;	//	��������
	Sprite sprite;		//	������

	fish(Image &image, float X, float Y, float W, float H);
	FloatRect getRect();

protected:
	enum { left, right, up, down } state;	// ��������� �������

	bool life;					// ���������� �����,
	int w, h;					// ����������
	float x, y, dx, dy;			// ���������,
	float CurrentFrame, speed;	// ����� � ��������
};
#endif