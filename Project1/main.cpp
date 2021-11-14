#include <iostream>
#include <sstream>
#include <list>
#include "player.h"	// Подключение классов "игрока"
#include "enemy.h"	// и "врага"

using namespace sf;
using namespace std;

/*****	Игровая карта	*****/
#define HEIGHT_MAP 17	// высота карты
#define WIDTH_MAP 35	// ширина карты 
string TileMap[HEIGHT_MAP] = {
	"32222222222222222222222222222222224",
	"31111111111111111111111111111111114",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"3               5                 4",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"3                                 4",
	"30000000000000000000000000000000004",
};
/*****	Произвольная генерация креветок	*****/
void randShrimp(){
	int randX = 0;	int randY = 0;
	srand(time(0));		// рандом	
	int countShrimp = 1;		// Количество новых креветок
	while (countShrimp>0){	// за прохождение цикла
		randX = 1 + rand() % (WIDTH_MAP - 1);
		randY = 1 + rand() % (HEIGHT_MAP - 1);
		if (TileMap[randY][randX] == ' ')   { 
			TileMap[randY][randX] = '5';
			countShrimp--;
		}
	}
}
/*****	Функция игры	*****/
bool beginGame(){
	RenderWindow window(VideoMode(1120, 544), "Aquarium");	// Окно приложения
	
	// Шрифт
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setStyle(Text::Bold);

	// Карта
	Image i_map;
	i_map.loadFromFile("images/aqua.png");	// Загружаем изображение
	Texture t_map;
	t_map.loadFromImage(i_map);	// Закидываем изображение в текстуру
	Sprite s_map;
	s_map.setTexture(t_map);	// Заливаем спрайт текстурой

	// Игрок
	Image i_hero;
	i_hero.loadFromFile("images/fish.png");
	player p(i_hero, 400, 200, 36, 36);	// Объект p класса "игрок"

	// Враг
	Image i_enemy;
	i_enemy.loadFromFile("images/enemy.png");
	list <enemy*> enemies;	// Список врагов
	int countEnemy = 3;		// Количество врагов
	while (countEnemy>0){	// Генерация случайного расположения объектов класса "враг"
		enemies.push_back(new enemy(i_enemy, 80 + rand() % 1040, 80 + rand() % 464, 40, 40));
		countEnemy--;
	}

	Clock clock;	
	Event event;
	float time = 0; // Переменная времени	
	int timerShrimp = 0;	// Таймер для креветок

	while (window.isOpen())	// Пока открыто окно
	{
		// Таймер по системному времени
		float time = clock.getElapsedTime().asMicroseconds();
		time = time / 800;
		clock.restart();

		// Закрытие окна по клавишам
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) //|| (Keyboard::isKeyPressed(Keyboard::Escape)))	
				window.close();
		}
		
		//	Вызов генерации креветок по таймеру
		timerShrimp += time;
		if (timerShrimp>7000){
			randShrimp(); 
			timerShrimp = 0;
		}

		window.clear();		// Очистка экрана

		/*****	Рисовка аквариума	*****/
		for (int i = 0; i < HEIGHT_MAP; i++)	
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == '2')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if (TileMap[i][j] == '1')  s_map.setTextureRect(IntRect(64, 0, 32, 32));
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(96, 0, 32, 32));
			if (TileMap[i][j] == '3')  s_map.setTextureRect(IntRect(128, 0, 32, 32));
			if (TileMap[i][j] == '4')  s_map.setTextureRect(IntRect(160, 0, -32, 32));
			if (TileMap[i][j] == '5')  s_map.setTextureRect(IntRect(160, 0, 32, 32));

			s_map.setPosition(j * 32, i * 32);
			window.draw(s_map);
		}
		/*****	*****	*****	*****	*****/
	
		// Отображение "здоровья" игрока
		ostringstream health;    
		health << p.health;		
		text.setString("Health:\t"+health.str());
		text.setPosition(70, 0);
		window.draw(text);	

		p.setTileMap(TileMap); // Текущий TileMap игрока
		p.update(time);		// Вызов update класса "игрок"

		for (auto it = enemies.begin(); it != enemies.end(); it++){	// Для всех элементов списка врагов
			(*it)->setTileMap(TileMap);	// Текущий TileMap врага
			(*it)->update(time);		// Вызов update класса "враг"
			if ((*it)->getRect().intersects(p.getRect())){	// При пересечении:
				p.health -= 3;				// -3 от здоровья игрока
				if ((*it)->dir == 0) (*it)->dir = 1; else (*it)->dir = 0;	// изменение направления врага
			}
			if (p.life == false){
				time = 0;	timerShrimp = 0;	// Остановка таймеров
				p.health = 0;	(*it)->health = 0;	// и персонажей
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }

		for (auto it = enemies.begin(); it != enemies.end(); it++){	// Рисовка врагов
			window.draw((*it)->sprite);
		}
		if (p.life == false){
			text.setString("\t\t*** You're dead ***\n\n[Tab]\t-\trestarting the game.\n\n[Esc]\t-\texit the game.");	// Справка о возможных действиях
			text.setPosition(400, 200);
			window.draw(text);
		}
		window.draw(p.sprite);	// Рисовка игрока
		window.display();	// Отрисовка окна
	}
}
/*****	*****	*****	*****	*****/
void restart(){
	if (beginGame()) { restart(); }
}

int main(){
	restart();
	return 0;
}