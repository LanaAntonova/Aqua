#include "fish.h"	// ����������� ������ "�����"

#ifndef ENEMY_H
#define ENEMY_H

class enemy:public fish{	// ����� "�����"
public:
	int dir;	// ���������� ����������� ��������

	enemy(Image &image, float X, float Y, float W, float H);	
	void checkCollisionWithMap(float Dx, float Dy);	// ������� �������������� � ������
	void update(float time);	// ������� ��������
	
	std::string* e_TileMap;
	void setTileMap(std::string* TileMap){ e_TileMap = TileMap; }	// ������� �������� TileMap
};
#endif