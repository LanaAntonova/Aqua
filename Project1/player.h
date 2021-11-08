#include "fish.h"	// ����������� ������ "�����"

#ifndef PLAYER_H
#define PLAYER_H

class player:public fish{	// ����� "������"
public:
	unsigned health;

	player(Image &image, float X, float Y, float W, float H);	// ����������� "������"	
	~player();	// ���������� "������"
	void update(float time);	// ������� �������� ������
	void setTileMap(std::string* TileMap){ p_TileMap = TileMap; }	// ������� �������� TileMap

private:
	void control();	// ������� ����������
	void checkCollisionWithMap(float Dx, float Dy);	// ������� �������������� � ������

	std::string* p_TileMap;
};
#endif