#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cmath>
#include <windows.h>
using std::cout;

class Player;

class Map {
	char **data;
	short int height;
	short int width;
	short int exith;
	short int exitw;
	short int keyh;
	short int keyw;
public:
	friend Player;
	Map();
	short int randomexit(short int enh, short int enw, short int &h, short int &w);
	void randomobject(short int enh, short int enw, short int &h, short int &w);
	void showmap();
};

Map::Map() {
	height = 44;
	width = 44;
	exith = height;
	exitw = width;
	keyh = 0;
	keyw = 0;
	const short int consth = height;
	const short int constw = width;
	data = new char *[consth];
	for (int i = 0; i < consth; ++i)
		data[i] = new char[constw];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; ++j)
		{
			data[i][j] = ' ';
		}
	}

	for (int i = 2; i < height - 2; ++i)
	{
		for (int j = 2; j < width - 2; ++j)
		{
			if (j == 2 || j == width - 3)
				data[i][j] = '#';

			data[2][j] = '#';
			data[height - 3][j] = '#';
		}
	}

	short int exitside;
	exitside = randomexit(height, width, exith, exitw);
	data[exith][exitw] = 'E';

	for (int i = 0; i < (height - 4) * (width - 4) / 10; ++i)
	{
		short int h = 0, w = 0;
		randomobject(height, width, h, w);
		data[h][w] = 'R';
	}

	for (int i = 0; i < 15;)
	{
		short int h = 0, w = 0;
		randomobject(height, width, h, w);
		if (data[h][w] = ' ') {
			data[h][w] = 'M';
			++i;
		}
	}
	for (int i = 0; i < 10;)
	{
		short int h = 0, w = 0;
		randomobject(height, width, h, w);
		if (data[h][w] = ' ') {
			data[h][w] = 'F';
			++i;
		}
	}

	randomobject(height, width, keyh, keyw);

	if (exitside == 1)
		data[exith + 1][exitw] = ' ';
	else if (exitside == 2)
		data[exith][exitw - 1] = ' ';
	else if (exitside == 3)
		data[exith - 1][exitw] = ' ';
	else if (exitside == 4)
		data[exith][exitw + 1] = ' ';
}

short int Map::randomexit(short int enh, short int enw, short int &h, short int &w) {
	short int side;
	side = 1 + rand() % 4;
	if (side == 1)
	{
		h = 2;
		w = 3 + rand() % (enw - 6);
	}
	else if (side == 2)
	{
		w -= 3;
		h = 3 + rand() % (enh - 6);
	}
	else if (side == 3)
	{
		h -= 3;
		w = 3 + rand() % (enw - 6);
	}
	else if (side == 4)
	{
		w = 2;
		h = 3 + rand() % (enh - 6);
	}
	return side;
}

void Map::randomobject(short int enh, short int enw, short int &h, short int &w) {
	h = 3 + rand() % (enw - 6);
	w = 3 + rand() % (enh - 6);
}


void Map::showmap() {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << data[i][j];
		}
		cout << std::endl;
	}
}


class Player {
	short int playerh;
	short int playerw;
	short int hp;
	short int medkitcounter;
	bool keyflag;
	bool doorcheckflag;
	bool halfhpflag;
	bool quarterhpflag;
	bool less10hpflag;
	bool spiritflag;
	short int lampfuel;
	bool lampflag;
	bool lightflag;
public:
	Player(Map &map);
	void stepmessage();
	void rockmessage();
	void medkitmessage();
	void lampmessage();
	void move(Map &map);
};

Player::Player(Map &map) {
	hp = 401;
	medkitcounter = 0;
	keyflag = 0;
	doorcheckflag = 0;
	halfhpflag = 0;
	quarterhpflag = 0;
	less10hpflag = 0;
	spiritflag = 0;
	lampflag = 0;
	lightflag = 0;
	lampfuel = 0;
	playerh = 15 + rand() % 9;
	playerw = 15 + rand() % 9;
	if (map.keyh == playerh && map.keyw == playerw)
		keyflag = 1;
	else
		map.data[map.keyh][map.keyw] = 'K';
	map.data[playerh][playerw] = '@';
}

void Player::stepmessage() {
	short int tmp = 1 + rand() % 29;
	switch (tmp)
	{
	case 1: cout << "Я куда-то иду, это ведь хорошо, да?\n"; break;
	case 2: cout << "Это один маленький шаг для человека и... Всё\n"; break;
	case 3: cout << "Здесь так темно и холдно...\n"; break;
	case 4: cout << "Это вода на меня капнула только что?\n"; break;
	case 5: cout << "Ещё один шаг в пустоту\n"; break;
	case 6: cout << "Когда-нибудь я найду отсюда выход\n"; break;
	case 7: cout << "Чёрт, кажется, что-то коснулось моей ноги!\n"; break;
	case 8: cout << "Неужели здесь совсем никого нет?\n"; break;
	case 9: cout << "На ощупь к свободе, на ощупь к свободе...\n"; break;
	}
}

void Player::rockmessage() {
	short int tmp = 1 + rand() % 10;
	switch (tmp)
	{
	case 1: cout << "В потьмах я нашёл лбом гранитный выступ. Больно...\n"; break;
	case 2: cout << "Ай, чёрт возьми, здесь же камень!\n"; break;
	case 3: cout << "&@#$%!\n"; break;
	case 4: cout << "Громким смехом не скроешь дикой боли, поэтому мне не смешно!\n"; break;
	case 5: cout << "Ай... Кажется, я получил сотрясение\n"; break;
	case 6: cout << "Обожаю впечататься в камень\n"; break;
	case 7: cout << "*+1 ушиб в копилку*\n"; break;
	case 8: cout << "Ударился так, что искры из глаз осветили мне путь\n"; break;
	case 9: cout << "Я споткнулся и упал, но нашёл силы подняться\n"; break;
	case 10: cout << "Как же здесь темно, я бьюсь обо всё подряд...\n"; break;
	}
}

void Player::medkitmessage() {
	switch (medkitcounter)
	{
	case 0:
		medkitcounter++;
		cout << "*Что-то, тарахтя, отлетело от вашей ноги. Кажется, это была банка с таблетками.\nВо тьме вы отыскали её и поняли по форме, что это обезболивающее.\nВам полегчало...*\n";
		break;
	case 1:
		medkitcounter++;
		cout << "*О чудо! Вы нащупали под ногами перевязочный пакет и какие-то ампулы.\nТеперь вам стало немного лучше...*\n";
		break;
	case 2:
		medkitcounter++;
		cout << "Кажется, это ещё одна аптечка!\n*Вы чувствуете себя получше*\n";
		break;
	case 3:
		medkitcounter = 0;
		cout << "*Под ботинком раздался хруст стекла. Похоже, это были ампулы с медикаментами.\nНесколько из них остались целыми - ваше самочувствуе слегка улучшилось*\n";
		break;
	}

}
void Player::lampmessage() {
	short int tmp = 1 + rand() % 5;
	switch (tmp)
	{
	case 1: cout << "*Вы нашли немного топлива* \n"; break; //TODO     понапридумывай тут фраз
	case 2: cout << "*Вы нашли немного топлива* \n"; break;
	case 3: cout << "*Вы нашли немного топлива* \n"; break;
	case 4: cout << "*Вы нашли немного топлива* \n"; break;
	case 5: cout << "*Вы нашли немного топлива* \n"; break;
	}

}
void Player::move(Map &map) {

	short int moves = ++hp;

	while (hp--) {
		std::string key;
		std::cin >> key;
		system("cls");

		if (hp > 0) {
			if ((key[0] == 'w' && key[1] == NULL) || (key[0] == 'W' && key[1] == NULL))
			{
				if (map.data[playerh - 1][playerw] == ' ' || map.data[playerh - 1][playerw] == 'M' || map.data[playerh - 1][playerw] == 'K' || map.data[playerh - 1][playerw] == 'F')
				{
					cout << "*Вы шагнули*\n";
					if (map.data[playerh - 1][playerw] == 'M')
					{
						hp += 20;
						medkitmessage();
					}
					else if (map.data[playerh - 1][playerw] == 'F')
					{
						if (lampflag == 0) {
							cout << "*Вы что-то обнаружили в темноте*\nЧто это здесь такое?.. Неужели... Лампа! И в ней осталось немного топлива... \n<Используйте на [L]/[l]>\n";
							lampflag = 1;
						}
						else
							lampmessage();

						lampfuel += 7;
					}
					else if (map.data[playerh - 1][playerw] == 'K')
					{
						if (doorcheckflag == 0)
							cout << "*Под ногами брякнуло что-то металлическое...*\nХм, какой-то заржавевший ключ...\n";
						else
							cout << "*Под ногами брякнуло что-то металлическое...*\nКакой-то ржавый ключ... Неужели тот самый?!\n";
						keyflag = 1;
					}
					else {
						stepmessage();
					}
					map.data[playerh][playerw] = ' ';
					map.data[playerh - 1][playerw] = '@';
					--playerh;
				}
				else if (map.data[playerh - 1][playerw] == 'R' || map.data[playerh - 1][playerw] == '#')
				{
					hp -= 3;
					cout << "*Вы наткнулись на препятствие*\n";
					rockmessage();
				}
				else if (map.data[playerh - 1][playerw] == 'E')
				{
					if (keyflag == 0)
					{
						if (doorcheckflag == 1)
						{
							cout << "*Запертая дверь*\n";
						}
						else {
							doorcheckflag = 1;
							cout << "*Вы нашли громадную металлическую дверь*\nНе поддаётся. Из замочной скважины дует поток воздуха... Где-то должен быть ключ...\nХм, здесь есть что-то ещё. Похоже на какой-то компас...\n<Используйте на [E]/[e]>\n";
						}
					}
					else
					{
						hp = 0;
						if (doorcheckflag == 1)
						{
							cout << "Да, чёрт возьми! Ключ подошёл!\n*Дверь с гулким скрежетом начала открываться. Вы выбрались из этого кошмара... Вроде бы...*\n\n";
						}
						else {
							hp = 0;
							cout << "*Вы нашли громадную металлическую дверь. Из замочной скважины дует поток воздуха...*\nНеужели этот ключ от неё?! Невероятно!\n*Дверь с гулким скрежетом начала открываться. Вы выбрались из этого кошмара... Вроде бы...*\n\n";
						}
						break;
					}
				}
			}

			else if ((key[0] == 'a' && key[1] == NULL) || (key[0] == 'A' && key[1] == NULL))
			{
				if (map.data[playerh][playerw - 1] == ' ' || map.data[playerh][playerw - 1] == 'M' || map.data[playerh][playerw - 1] == 'K' || map.data[playerh][playerw - 1] == 'F')
				{
					cout << "*Вы шагнули*\n";
					if (map.data[playerh][playerw - 1] == 'M')
					{
						hp += 20;
						medkitmessage();
					}
					else if (map.data[playerh][playerw - 1] == 'F')
					{
						if (lampflag == 0) {
							cout << "*Вы что-то обнаружили в темноте*\nЧто это здесь такое?.. Неужели... Лампа! И в ней осталось немного топлива... \n<Используйте на [L]/[l]>\n";
							lampflag = 1;
						}
						else
							lampmessage();

						lampfuel += 7;
					}
					else if (map.data[playerh][playerw - 1] == 'K')
					{
						if (doorcheckflag == 0)
							cout << "*Под ногами брякнуло что-то металлическое...*\nХм, какой-то заржавевший ключ...\n";
						else
							cout << "*Под ногами брякнуло что-то металлическое...*\nКакой-то ржавый ключ... Неужели тот самый?!\n";
						keyflag = 1;
					}
					else {
						stepmessage();
					}
					map.data[playerh][playerw] = ' ';
					map.data[playerh][playerw - 1] = '@';
					--playerw;
				}
				else if (map.data[playerh][playerw - 1] == 'R' || map.data[playerh][playerw - 1] == '#')
				{
					hp -= 3;
					cout << "*Вы наткнулись на препятствие*\n";
					rockmessage();
				}
				else if (map.data[playerh][playerw - 1] == 'E')
				{
					if (keyflag == 0)
					{
						if (doorcheckflag == 1)
						{
							cout << "*Запертая дверь*\n";
						}
						else {
							doorcheckflag = 1;
							cout << "*Вы нашли громадную металлическую дверь*\nНе поддаётся. Из замочной скважины дует поток воздуха... Где-то должен быть ключ...\nХм, здесь есть что-то ещё. Похоже на какой-то компас...\n<Используйте на [E]/[e]>\n";
						}
					}
					else
					{
						hp = 0;
						if (doorcheckflag == 1)
						{
							cout << "Да, чёрт возьми! Ключ подошёл!\n*Дверь с гулким скрежетом начала открываться. Вы выбрались из этого кошмара... Вроде бы...*\n\n";
						}
						else {
							hp = 0;
							cout << "*Вы нашли громадную металлическую дверь. Из замочной скважины дует поток воздуха...*\nНеужели этот ключ от неё?! Невероятно!\n*Дверь с гулким скрежетом начала открываться. Вы выбрались из этого кошмара... Вроде бы...*\n\n";
						}
						break;
					}
				}
			}

			else if ((key[0] == 's' && key[1] == NULL) || (key[0] == 'S' && key[1] == NULL))
			{
				if (map.data[playerh + 1][playerw] == ' ' || map.data[playerh + 1][playerw] == 'M' || map.data[playerh + 1][playerw] == 'K' || map.data[playerh + 1][playerw] == 'F')
				{
					cout << "*Вы шагнули*\n";
					if (map.data[playerh + 1][playerw] == 'M')
					{
						hp += 20;
						medkitmessage();
					}
					else if (map.data[playerh + 1][playerw] == 'F')
					{
						if (lampflag == 0) {
							cout << "*Вы что-то обнаружили в темноте*\nЧто это здесь такое?.. Неужели... Лампа! И в ней осталось немного топлива... \n<Используйте на [L]/[l]>\n";
							lampflag = 1;
						}
						else
							lampmessage();

						lampfuel += 7;
					}
					else if (map.data[playerh + 1][playerw] == 'K')
					{
						if (doorcheckflag == 0)
							cout << "*Под ногами брякнуло что-то металлическое...*\nХм, какой-то заржавевший ключ...\n";
						else
							cout << "*Под ногами брякнуло что-то металлическое...*\nКакой-то ржавый ключ... Неужели тот самый?!\n";
						keyflag = 1;
					}
					else {
						stepmessage();
					}
					map.data[playerh][playerw] = ' ';
					map.data[playerh + 1][playerw] = '@';
					++playerh;

				}
				else if (map.data[playerh + 1][playerw] == 'R' || map.data[playerh + 1][playerw] == '#')
				{
					hp -= 3;
					cout << "*Вы наткнулись на препятствие*\n";
					rockmessage();
				}
				else if (map.data[playerh + 1][playerw] == 'E')
				{
					if (keyflag == 0)
					{
						if (doorcheckflag == 1)
						{
							cout << "*Запертая дверь*\n";
						}
						else {
							doorcheckflag = 1;
							cout << "*Вы нашли громадную металлическую дверь*\nНе поддаётся. Из замочной скважины дует поток воздуха... Где-то должен быть ключ...\nХм, здесь есть что-то ещё. Похоже на какой-то компас...\n<Используйте на [E]/[e]>\n";
						}
					}
					else
					{
						hp = 0;
						if (doorcheckflag == 1)
						{
							cout << "Да, чёрт возьми! Ключ подошёл!\n*Дверь с гулким скрежетом начала открываться. Вы выбрались из этого кошмара... Вроде бы...*\n\n";
						}
						else {
							hp = 0;
							cout << "*Вы нашли громадную металлическую дверь. Из замочной скважины дует поток воздуха...*\nНеужели этот ключ от неё?! Невероятно!\n*Дверь с гулким скрежетом начала открываться. Вы выбрались из этого кошмара... Вроде бы...*\n\n";
						}
						break;
					}
				}
			}

			else if ((key[0] == 'd' && key[1] == NULL) || (key[0] == 'D' && key[1] == NULL))
			{
				if (map.data[playerh][playerw + 1] == ' ' || map.data[playerh][playerw + 1] == 'M' || map.data[playerh][playerw + 1] == 'K' || map.data[playerh][playerw + 1] == 'F')
				{
					cout << "*Вы шагнули*\n";
					if (map.data[playerh][playerw + 1] == 'M')
					{
						hp += 20;
						medkitmessage();
					}
					else if (map.data[playerh][playerw + 1] == 'F')
					{

						if (lampflag == 0) {
							cout << "*Вы что-то обнаружили в темноте*\nЧто это здесь такое?.. Неужели... Лампа! И в ней осталось немного топлива... \n<Используйте на [L]/[l]>\n";
							lampflag = 1;
						}
						else
							lampmessage();

						lampfuel += 7;
					}
					else if (map.data[playerh][playerw + 1] == 'K')
					{
						if (doorcheckflag == 0)
							cout << "*Под ногами брякнуло что-то металлическое...*\nХм, какой-то заржавевший ключ...\n";
						else
							cout << "*Под ногами брякнуло что-то металлическое...*\nКакой-то ржавый ключ... Неужели тот самый?!\n";
						keyflag = 1;
					}
					else {
						stepmessage();
					}
					map.data[playerh][playerw] = ' ';
					map.data[playerh][playerw + 1] = '@';
					++playerw;
				}
				else if (map.data[playerh][playerw + 1] == 'R' || map.data[playerh][playerw + 1] == '#')
				{
					hp -= 3;
					cout << "*Вы наткнулись на препятствие*\n";
					rockmessage();
				}
				else if (map.data[playerh][playerw + 1] == 'E')
				{
					if (keyflag == 0)
					{
						if (doorcheckflag == 1)
						{
							cout << "*Запертая дверь*\n";
						}
						else {
							doorcheckflag = 1;
							cout << "*Вы нашли громадную металлическую дверь*\nНе поддаётся. Из замочной скважины дует поток воздуха... Где-то должен быть ключ...\nХм, здесь есть что-то ещё. Похоже на какой-то компас...\n<Используйте на [E]/[e]>\n";
						}
					}
					else
					{
						hp = 0;
						if (doorcheckflag == 1)
						{
							cout << "Да, чёрт возьми! Ключ подошёл!\n*Дверь с гулким скрежетом начала открываться. Вы выбрались из этого кошмара... Вроде бы...*\n\n";
						}
						else {
							hp = 0;
							cout << "*Вы нашли громадную металлическую дверь. Из замочной скважины дует поток воздуха...*\nНеужели этот ключ от неё?! Невероятно!\n*Дверь с гулким скрежетом начала открываться. Вы выбрались из этого кошмара... Вроде бы...*\n\n";
						}
						break;
					}
				}
			}

			else if ((key[0] == 'e' && key[1] == NULL) || (key[0] == 'E' && key[1] == NULL))
			{
				if (doorcheckflag == 1 && keyflag == 0) {
					cout << "*Вы нащупали стрелку компаса*\nКажется, она показывает на ";
					if (map.keyw <= playerw && map.keyh < playerh)
					{
						if (map.keyw == playerw)
							cout << "север\n";
						else
							cout << "северо-запад\n";
					}
					else if (map.keyw > playerw && map.keyh <= playerh)
					{
						if (map.keyh == playerh)
							cout << "восток\n";
						else
							cout << "северо-восток\n";
					}
					else if (map.keyw >= playerw && map.keyh > playerh)
					{
						if (map.keyw == playerw)
							cout << "юг\n";
						else
							cout << "юго-восток \n";
					}
					else if (map.keyw < playerw && map.keyh >= playerh)
					{
						if (map.keyh == playerh)
							cout << "запад\n";
						else
							cout << "юго-запад\n";
					}

				}
				else {
					moves++;
					hp++;
					cout << "<Нет предмета>\n";
				}
			}
			else if ((key[0] == 'l' && key[1] == NULL) || (key[0] == 'L' && key[1] == NULL)) {
				if (lampflag == 1) {
					if (lightflag == 0) {
						if (lampfuel > 0) {
							cout << "*Вы зажгли лампу*\n";
							lightflag = 1;
						}
						else {
							cout << "*Топливо закончилось*\n";
						}
					}
					else {
						lightflag = 0;
						cout << "*Вы затушили лампу*\n";
					}
				}
				else {
					moves++;
					hp++;
					cout << "<Нет предмета>\n";
				}
			}
			else
			{
				moves++;
				hp++;
				cout << "<Данная команда отсутствует>\n";
			}

			// отрисовка лампы
			if (lightflag == 1) {
				if (lampfuel > 3) {
					for (int i = -2; i <= 2; ++i)
					{
						if (i == -2 || i == 2) {
							cout << ' ';
							for (int j = -1; j <= 1; ++j)
								cout << map.data[playerh + i][playerw + j];
						}
						else {
							for (int j = -2; j <= 2; ++j)
								cout << map.data[playerh + i][playerw + j];
						}
						cout << std::endl;
					}
					--lampfuel;
				}
				else if (lampfuel <= 3 && lampfuel > 0) {
					cout << "*Топливо кончается*\n";
					for (int i = -1; i <= 1; ++i) {
						for (int j = -1; j <= 1; ++j)
							cout << map.data[playerh + i][playerw + j];
						cout << std::endl;
					}
					--lampfuel;
				}
				else {
					cout << "*Топливо закончилось*\n";
					lightflag = 0;
				}
			}

			moves--;
			if (moves % 5 == 0) {
				if (spiritflag == 0) {
					cout << "Какой-то голос, подозрительно похожий на духа говорит, что д";
					spiritflag = 1;
				}
				else
					cout << "Д";
				cout << "о выхода осталось " << sqrt((playerw - map.exitw) * (playerw - map.exitw) + (playerh - map.exith) * (playerh - map.exith)) << std::endl;
			}
			if (hp <= 200 && hp > 100 && halfhpflag == 0)
			{
				cout << "*Половина жизни покинула ваше тело*\n";
				halfhpflag = 1;
			}
			else if (hp <= 100 && hp > 400 && quarterhpflag == 0)
			{
				cout << "*Вы умираете. Медленно, но верно*\n";
				quarterhpflag = 1;
			}
			else if (hp <= 40 && hp > 0 && less10hpflag == 0)
			{
				cout << "*Смерть наступает вам на пятки*\n";
				less10hpflag = 1;
			}
			if (hp > 200)
				halfhpflag =
                        0;
			else if (hp > 100)
				quarterhpflag = 0;
			else if (hp > 40)
				less10hpflag = 0;

			//map.showmap();
		}
		else
		{
			cout << "Вы рухнули на пол в изнеможении. Попытки выбраться оказались тщетны...\n\n";
			break;
		}
	}
}

void startgame() {
	cout << "\n      ###  The Escape  ###      \n\n";
	cout << " Для управления используйте (введите клавишу и нажмите Enter):\n\n   [W]/[w] - Двигаться вперёд\n   [A]/[a] - Двигаться влево\n   [S]/[s] - Двигаться назад\n   [D]/[d] - Двигаться вправо\n   [E]/[e]/[L]/[l] - Использовать предмет\n\n";
	cout << "                                           Wise Guys Studios\n                                           Все права защищены (нет)\n                                           Pre-Alpha Build v1.1.3\n\n ";
	system("pause");
	system("cls");
	cout << "*Вы очнулись в полнейшей тьме и не понимаете, что происходит*\nГ-где я оказался? Почему здесь так темно и холдно?.. Эээээй! Есть здесь кто?!\nНадо отсюда выбираться...\n\n";
	system("pause");
	system("cls");
}

int main()
{
	setlocale(LC_ALL, "Russian");
    //setlocale(0, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); //set to windows 1251 encoding
	srand(time(NULL));
	Map map;
	Player player(map);
	startgame();
	//map.showmap();
	player.move(map);
	system("pause");
	return 0;
}
