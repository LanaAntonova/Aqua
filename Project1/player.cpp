#include "player.h"	// ����������� ������ "������"

player::player(Image &image, float X, float Y, float W, float H) : fish(image, X, Y, W, H){	// ����������� "������" � �����������
	sprite.setTextureRect(IntRect(36, 35, -w, h));	//������ ������� �������������
}

player::~player() {
	p_TileMap = NULL;
}

// ������� ���������� �� ��������
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

// ������� �������������� ������ � ������
void player::checkCollisionWithMap(float Dx, float Dy)
{
	for (unsigned i = y / 32; i < (y + h) / 32; i++)
	for (unsigned j = x / 32; j<(x + w) / 32; j++){
		if (p_TileMap[i][j] == '0' || p_TileMap[i][j] == '2' ||	
			p_TileMap[i][j] == '3' || p_TileMap[i][j] == '4'){	// ������������ � ��������� ���������
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
		if (p_TileMap[i][j] == '5') {	// �������� ��������
			health++;
			p_TileMap[i][j] = ' ';
		}
	}
}

// ������� �������� ������
void player::update(float time)
{
	if (life) {
		control();	// ����� ������� ����������
		switch (state)
		{
		case right:	//������
			dx = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame) + 36, 35, -36, 19)); // �������� �������� ������
			break;
		case left:	//�����
			dx = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(36 * int(CurrentFrame), 35, 36, 19));	// �������� �������� �����
			break;
		case down:	//����
			dy = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(22 * int(CurrentFrame), 0, 22, 35));	// �������� �������� ����
			break;
		case up:	//�����
			dy = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(24 * int(CurrentFrame), 54, 24, 34));	// �������� �������� �����
			break;
		}

		x += dx*time;	//�������� �� X
		checkCollisionWithMap(dx, 0.f);	// ����� ������� ������������ �� X
		y += dy*time;	//�������� �� Y
		checkCollisionWithMap(0.f, dy);	// ����� ������� ������������ �� Y

		speed = 0.f;	// ����������� �������� ��� ������� �������
		sprite.setPosition(x, y);	// ����� ������� � ������� (x, y)
		if (health <= 0) {
			life = false;
			sprite.setTextureRect(IntRect(66, 0, 35, 18));
		}
	}
}