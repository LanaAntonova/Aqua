#include "enemy.h"

enemy::enemy(Image &image, float X, float Y, float W, float H) : fish(image, X, Y, W, H){	// ����������� "�����" � �����������
	speed = 0.08f;
	dx = speed;
	dir = rand() % (2);
	sprite.setTextureRect(IntRect(40, 0, -w, h));	//������ ������� �������������
}

// ������� �������������� ����� � ������
void enemy::checkCollisionWithMap(float Dx, float Dy){
	for (unsigned i = y / 32; i < (y + h) / 32; i++)
	for (unsigned j = x / 32; j<(x + w) / 32; j++){
		if (e_TileMap[i][j] == '3' || e_TileMap[i][j] == '4'){	// �������� ������������ � ��������� �����
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

// ������� �������� �����
void enemy::update(float time){
	if (life) {
		switch (dir)
		{
		case right:	//������
			dx = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(39 * int(CurrentFrame) + 39, 0, -39, 34));	// �������� �������� ������
			break;
		case left:	//�����
			dx = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(39 * int(CurrentFrame), 0, 39, 34));	// �������� �������� �����
			break;
		}

		x += dx*time;	//�������� �� X
		checkCollisionWithMap(dx, 0.f);	// ����� ������� ������������ �� X

		sprite.setPosition(x, y);	// ����� ������� � ������� (x, y)
		if (health <= 0) {
			life = false;
		}
	}
}