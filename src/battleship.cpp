#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"winmm.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>
#include <string>
using namespace std;
#define MAPSIZE 10
#define UNIT_BALANCE 0.4
#define MAX_TURN 5
int map_check(int m[][MAPSIZE], int x, int y, int c, int blocks)
{
	int tmp = 0;
	if (c == 0) //����
	{
		if (y >= blocks)
		{
			while (tmp < blocks)
			{
				if (m[y][x] == 0)
				{
					y--;
				}
				else
				{
					return 0;
				}
				tmp++;
			}
			return 1;
		}
		else { return 0; }
	}
	else if (c == 1) //����
	{
		if (x <= MAPSIZE - blocks)
		{
			while (tmp < blocks)
			{
				if (m[y][x] == 0)
				{
					x++;
				}
				else
				{
					return 0;
				}
				tmp++;
			}
			return 1;
		}
		else { return 0; }
	}
	else if (c == 2) //����
	{
		if (y <= MAPSIZE - blocks)
		{
			while (tmp < blocks)
			{
				if (m[y][x] == 0)
				{
					y++;
				}
				else
				{
					return 0;
				}
				tmp++;
			}
			return 1;
		}
		else { return 0; }
	}
	else //����
	{
		if (x >= blocks)
		{
			while (tmp < blocks)
			{
				if (m[y][x] == 0)
				{
					x--;
				}
				else
				{
					return 0;
				}
				tmp++;
			}
			return 1;
		}
		else { return 0; }
	}
}
class othermap {// �ٸ� �÷��̾��� map�� ǥ���ϱ� ���� Ŭ����
public:
	int other_map[MAPSIZE][MAPSIZE];
	othermap()
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				other_map[i][j] = 0;
			}
		}
	}
	othermap(const othermap& c)
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				other_map[i][j] = c.other_map[i][j];
			}
		}
	}
	void showothermap()
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				if (other_map[i][j] == 0)
				{
					cout << "��";
				}
				else // �����̳� �������� ���
				{
					cout << "��";
				}
			}
			cout << "" << endl;
		}
	}
	void initothermap()
	{
		for (int i = 0; i < MAPSIZE; i++)
		{
			for (int j = 0; j < MAPSIZE; j++)
			{
				other_map[i][j] = 0;
			}
		}
	}
};
class ship {
private:
	string name;
	int kind;
	int x, y;
	int compass;
	int health;
	int block;
	int index;
	int do_point;
	int move_point;
public:
	ship() {}
	ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_, int mp_) :kind(kind_), x(x_), y(y_), compass(compass_), health(health_), block(health_), index(index_), move_point(mp_), do_point(1) {
		name = name_;
		//mapsize�� ���� unit(��ship) ������ �����ǰ� unit ĭ��= health (ó�� ü��) 
	}
	ship(const ship& c) : kind(c.kind), x(c.x), y(c.y), compass(c.compass), health(c.health), block(c.block), index(c.index), do_point(c.do_point), move_point(c.move_point) {
		name = c.name;
	}
	/////������///////
	string getname()
	{
		return name;
	}
	int getkind()
	{
		return kind;
	}
	int getx()
	{
		return x;
	}
	int gety()
	{
		return y;
	}
	int getcompass()
	{
		return compass;
	}
	int getblock()
	{
		return block;
	}
	int getindex()
	{
		return index;
	}
	int getdo_point()
	{
		return do_point;
	}
	int getmove_point()
	{
		return move_point;
	}
	int gethealth()
	{
		return health;
	}
	//////get�Լ���//////
	int hit()
	{
		health = health - 1;
		cout << name << " �ǰ� ����" << endl;
		cout << "ü�� : " << health << endl;
		if (health == 0)
		{
			block = 0;
			cout << name << " ��ħ" << endl;
			return 0; // �� ��ħ
		}
		return 1;
	}
	virtual int search()
	{
		cout << "����� " << name << "�� �߰��߽��ϴ�." << endl;
		return 1;
	}
	void move_ship(int direction)
	{
		if (direction == 0) //��ȸ��
		{
			compass--;
			if (compass < 0)
			{
				compass = 3;
			}
		}
		else if (direction == 1) //����
		{
			if (compass == 0)
			{
				y -= move_point;
			}
			else if (compass == 1)
			{
				x += move_point;
			}
			else if (compass == 2)
			{
				y += move_point;
			}
			else
			{
				x -= move_point;
			}
		}
		else //��ȸ��
		{
			compass++;
			if (compass >= 4)
			{
				compass = 0;
			}
		}
	}
	virtual void comment() {
		cout << "��� ������ �� ���Դϱ�? (1 ����)   (2 �̵�)" << endl;
	}
	virtual void sound() {}
};
class ship_carrier :public ship {
public:
	ship_carrier(int x_, int y_, int compass_, int index_) :ship("�װ�����", 1, x_, y_, compass_, 5, index_, 1) {}
	void comment() {
		cout << "��� ������ �� ���Դϱ�?  (1 ����)   (2 �̵�)" << endl;
	}
	void sound() {
		int i = rand() % 5;
		if (i == 0) {
			PlaySound("sound/carrier1.wav", 0, SND_ASYNC);
		}
		else if (i == 1)
		{
			PlaySound("sound/carrier2.wav", 0, SND_ASYNC);
		}
		else if (i == 2)
		{
			PlaySound("sound/carrier3.wav", 0, SND_ASYNC);
		}
		else if (i == 3)
		{
			PlaySound("sound/carrier4.wav", 0, SND_ASYNC);
		}
		else
		{
			PlaySound("sound/carrier5.wav", 0, SND_ASYNC);
		}
	}
};
class ship_battleship :public ship {
public:
	ship_battleship(int x_, int y_, int compass_, int index_) :ship("����", 2, x_, y_, compass_, 4, index_, 1) {}
	void sound() {
		int i = rand() % 5;
		if (i == 0) {
			PlaySound("sound/battleship1", 0, SND_ASYNC);
		}
		else if (i == 1)
		{
			PlaySound("sound/battleship2", 0, SND_ASYNC);
		}
		else if (i == 2)
		{
			PlaySound("sound/battleship3", 0, SND_ASYNC);
		}
		else if (i == 3)
		{
			PlaySound("sound/battleship4", 0, SND_ASYNC);
		}
		else
		{
			PlaySound("sound/battleship5", 0, SND_ASYNC);
		}
	}
};
class ship_patrol :public ship {
public:
	ship_patrol(int x_, int y_, int compass_, int index_) :ship("�ʰ���", 3, x_, y_, compass_, 3, index_, 3) {}
	void sound() {
		int i = rand() % 5;
		if (i == 0) {
			PlaySound("sound/patrol1", 0, SND_ASYNC);
		}
		else if (i == 1)
		{
			PlaySound("sound/patrol2", 0, SND_ASYNC);
		}
		else if (i == 2)
		{
			PlaySound("sound/patrol3", 0, SND_ASYNC);
		}
		else if (i == 3)
		{
			PlaySound("sound/patrol4", 0, SND_ASYNC);
		}
		else
		{
			PlaySound("sound/patrol5", 0, SND_ASYNC);
		}
	}
};
class ship_submarin :public ship {
public:
	ship_submarin(int x_, int y_, int compass_, int index_) :ship("�����", 4, x_, y_, compass_, 2, index_, 1) {}
	int search()
	{
		return 0;
	}
	void sound() {
		int i = rand() % 5;
		if (i == 0) {
			PlaySound("sound/submarin1", 0, SND_ASYNC);
		}
		else if (i == 1)
		{
			PlaySound("sound/submarin2", 0, SND_ASYNC);
		}
		else if (i == 2)
		{
			PlaySound("sound/submarin3", 0, SND_ASYNC);
		}
		else if (i == 3)
		{
			PlaySound("sound/submarin4", 0, SND_ASYNC);
		}
		else
		{
			PlaySound("sound/submarin5", 0, SND_ASYNC);
		}
	}
};

class player {
private:
	int id;
	int unit_max; //�ִ�� ���� �� �ִ� ���� ��
	int unit_num; //���� ������ �ִ� ���� ��
	int map[MAPSIZE][MAPSIZE]; //player ������ ��
	int bot_num;
public:
	ship * ship_arr[(int)(MAPSIZE * UNIT_BALANCE) + 2];
	int ship_index;
	int state; //��Ƽ���� ���
	player(int id_, int bot_num_) : id(id_), bot_num(bot_num_), unit_num(0), state(0) {
		unit_max = (int)(MAPSIZE * UNIT_BALANCE) + 1;
		initmap();
		ship_index = 0;//ship_index �ʱ�ȭ
	}
	/*player(const player &c):id(c.id),unit_max(c.unit_max),unit_num(c.unit_num),unit_index(c.unit_index),bot_num(c.bot_num)
	{
	//copy constructer ����
	}*/
	//////������////////
	int get_unitmax()
	{
		return unit_max;
	}
	int getid()
	{
		return id;
	}
	int getunitnum()
	{
		return unit_num;
	}
	void disunitnum()
	{
		unit_num--;
	}
	///////get �Լ���//////
	void initmap()
	{
		int i, j;
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				map[i][j] = 0;
			}
		}
	}
	void makeship(int input_kind)
	{
		int x, y, c, health;
		if (unit_max > unit_num)
		{
			if (input_kind == 1)
			{
				health = 5;
			}
			else if (input_kind == 2)
			{
				health = 4;
			}
			else if (input_kind == 3)
			{
				health = 3;
			}
			else
			{
				health = 2;
			}
			srand(time(NULL));
			do {
				x = rand() % MAPSIZE;
				Sleep(1000);
				y = rand() % MAPSIZE;
				Sleep(1000);
				c = rand() % 4;
			} while (map_check(map, x, y, c, health) != 1);
			unit_num++;
			if (input_kind == 1)
			{
				ship_arr[ship_index] = new ship_carrier(x, y, c, unit_num);
			}
			else if (input_kind == 2)
			{
				ship_arr[ship_index] = new ship_battleship(x, y, c, unit_num);
			}
			else if (input_kind == 3)
			{
				ship_arr[ship_index] = new ship_patrol(x, y, c, unit_num);
			}
			else
			{
				ship_arr[ship_index] = new ship_submarin(x, y, c, unit_num);
			}
			drawship(*ship_arr[ship_index]);
			ship_index++;
		}
		else
		{
			cout << "�踦 ���� �� �ִ� ���� �ʰ��߽��ϴ�." << endl;
		}
	}
	void drawship(ship s)
	{
		int tmp;
		int x = s.getx();
		int y = s.gety();
		int c = s.getcompass();
		int block = s.getblock();
		int index = s.getindex();
		int heal = s.gethealth();
		if (heal <= 0) //��ħ�Ǹ� �ʿ� �ȱ׸�
		{
			index = 0;
		}
		if (c == 0) // ����
		{
			for (tmp = 0; tmp < block; tmp++)
			{
				map[y][x] = index;
				y--;
			}
		}
		else if (c == 1) // ����
		{
			for (tmp = 0; tmp < block; tmp++)
			{
				map[y][x] = index;
				x++;
			}
		}
		else if (c == 2) // ����
		{
			for (tmp = 0; tmp < block; tmp++)
			{
				map[y][x] = index;
				y++;
			}
		}
		else // ����
		{
			for (tmp = 0; tmp < block; tmp++)
			{
				map[y][x] = index;
				x--;
			}
		}
	}
	void showmap()
	{
		int x, y;

		for (y = 0; y < MAPSIZE; y++)
		{
			for (x = 0; x < MAPSIZE; x++)
			{
				if (map[y][x] == 0) // �� ����
				{
					cout << "��";
				}
				else if (map[y][x] == 1) // ù ��° ship
				{
					cout << " 1";
				}
				else if (map[y][x] == 2) // �� ��° ship
				{
					cout << " 2";
				}
				else if (map[y][x] == 3) // �� ��° ship
				{
					cout << " 3";
				}
				else if (map[y][x] == 4) // �� ��° ship
				{
					cout << " 4";
				}
				else if (map[y][x] == 5) // �ټ� ��° ship
				{
					cout << " 5";
				}
				else
				{
					cout << "��";
				}
			}
			cout << "" << endl;
		}
	}
	void showship(int index)
	{
		//vector�� �ִ� ������ ���
		string com;
		cout << ship_arr[index]->getindex() << "��° �Լ�: " << ship_arr[index]->getname() << endl;
		cout << "ü��: " << ship_arr[index]->gethealth() << endl;
		if (ship_arr[index]->getcompass() == 0)
		{
			com = "��";
		}
		else if (ship_arr[index]->getcompass() == 1)
		{
			com = "��";
		}
		else if (ship_arr[index]->getcompass() == 2)
		{
			com = "��";
		}
		else
		{
			com = "��";
		}
		cout << "��ġ: " << " x��ǥ: " << ship_arr[index]->getx() << " y��ǥ: " << ship_arr[index]->gety() << " ����: " << com << endl;
	}
	void erasemap(int index) //move �Լ��� ���� move ���� ship�� ���� �ܻ��� map�� ���� �־ �浹������ �� �׷��� �̵� ���� �� �ܻ���� ����� �۾� �ʿ�
	{
		int x, y;
		for (y = 0; y < MAPSIZE; y++)
		{
			for (x = 0; x < MAPSIZE; x++)
			{
				if (map[y][x] == index)
				{
					map[y][x] = 0;
				}
			}
		}
	}
	int move(int direction, ship s)
	{
		string com;
		int compass = s.getcompass();
		int x = s.getx();
		int y = s.gety();
		int dp = s.getdo_point();
		int mp = s.getmove_point();
		erasemap(s.getindex());
		if (dp > 0) {
			if (direction == 0) //��ȸ��
			{
				compass--;
				if (compass < 0) // ������ �����̾��� ���
				{
					compass = 3; // ���� ����Ŵ
				}
			}
			else if (direction == 1) // ����
			{
				if (compass == 0) // ����
				{
					y -= mp;
				}
				else if (compass == 1) // ����
				{
					x += mp;
				}
				else if (compass == 2) // ����
				{
					y += mp;
				}
				else // ����
				{
					x -= mp;
				}
			}
			else if (direction == 2)//��ȸ��
			{
				compass++;
				if (compass >= 4) // ������ �����̾��� ���
				{
					compass = 0; // ����
				}
			}
			else
			{
				cout << "���� ����" << endl;
				return 0;
			}
			//�̰� Ȯ���ϱ� ���� �� ������ �������� �����Ҷ� �̹� �ش� ĭ�� ���ڰ� �� �־(�̵� ���� ��) �浹 ���� ��
			if (map_check(map, x, y, compass, s.getblock()) == 1)
			{

				if (compass == 0)
				{
					com = "��";
				}
				else if (compass == 1)
				{
					com = "��";
				}
				else if (compass == 2)
				{
					com = "��";
				}
				else
				{
					com = "��";
				}
				//cout << s.getindex() << " �踦 " << " x��ǥ : " << x << " y��ǥ : " << y << " ���� : " << com << " �� �̵����׽��ϴ�." << endl;
				s.move_ship(direction);
				*ship_arr[s.getindex() - 1] = s; //�ٲ� ship�� ��ġ ������ �����Ѵ�.
				initmap();
				for (int i = 0; i < unit_max; i++)
				{
					drawship(*ship_arr[i]);
				}
				return 1;
			}
			else
			{
				for (int i = 0; i < unit_max; i++)
				{
					drawship(*ship_arr[i]);
				}
				cout << "�踦 �ش� ��ġ�� ǥ���� �� �����ϴ�." << endl;
				return 0;
			}
		}
		else
		{
			cout << "���� �ൿ���� �� ����߽��ϴ�." << endl;
		}
	}
	int attack(int x, int y, player *p, ship s) //��ǥ, ���� ���ϴ� ��, ������ �ϴ¾�
	{
		int r;

		if (s.getkind() == 1) // �谡 �װ������� ���
		{
			PlaySound(TEXT("sound/search.wav"), 0, SND_ASYNC);
			r = p->p_search(x, y);
		}
		else // �谡 �װ������� �ƴ� ���
		{
			r = p->p_hit(x, y);
			if (r != 0)
			{
				p->disunitnum();
			}
		}
		return r;
	}
	int p_hit(int x, int y)
	{
		int i = map[y][x];
		int result;
		if (i == 0)
		{
			cout << x << " , " << y << "�� �ƹ��͵� �����ϴ�." << endl;
		}
		else
		{
			PlaySound(TEXT("sound/attack.wav"), 0, SND_ASYNC);
			result = ship_arr[i - 1]->hit();
			if (result == 0)
			{
				cout << "�踦 ��ħ���׽��ϴ�." << endl;
			}
			else
			{
				cout << "�¾ҽ��ϴ�." << endl;
			}
		}
		Sleep(2000);
		return i;
	}
	int p_search(int x, int y)
	{
		int i = map[y][x];
		int result;
		if (i == 0)
		{
			cout << x << " , " << y << "�� �ƹ��͵� �����ϴ�." << endl;
		}
		else
		{
			result = ship_arr[i - 1]->search();
			if (result == 0) //����� Ž�� ����
			{
				cout << x << " , " << y << "�� �ƹ��͵� �����ϴ�." << endl;
				i = 0;
			}
		}
		Sleep(2000);
		return i;
	}
};
void make_ship_num(int *c, int *b, int *p, int *custom)//�뷱���� �°� ���ֵ� ����
{
	srand(time(NULL));
	cout << "������ ���Ե��� ������ " << endl;
	*c = 1; //�װ������� �׻� 1
	*b = (int)MAPSIZE*UNIT_BALANCE*0.5; //������ MAPSIZE * UNIT_MAX * 0.5
	*p = (int)MAPSIZE*UNIT_BALANCE*0.25; //�ʰ����� MAPSIZE * UNIT_MAX * 0.25
	*custom = (int)MAPSIZE*UNIT_BALANCE*0.25;; // ������� MAPSIZE * UNIT_MAX * 0.25
}
void gamestart_single()
{
	int turn = 0;
	int input, p, q, tmp, xpos, ypos, i, j;
	int bot;
	int c_num, b_num, p_num, custom;
	int alive;
	cout << "Single play" << endl;
	cout << "Map Size " << MAPSIZE << endl;
	cout << "How many bots? : ";
	cin >> bot;
	cout << bot << " ���� ���� ���� �߽��ϴ�." << endl;
	alive = bot + 1;
	//const int bots = bot;
	//player p[bots];
	vector<player> p_v;
	vector<player>::iterator p_index;
	vector<othermap> maps_v; //�¾Ҵ��� �ȸ¾Ҵ��� �����ִ� map vector �ٸ������ ��� �͵� �� �� �ִ�.
	vector<othermap> ::iterator maps_index;
	int who = 0;
	make_ship_num(&c_num, &b_num, &p_num, &custom);
	cout << "�װ����� �� : " << c_num << endl;
	cout << "���� �� : " << b_num << endl;
	cout << "�ʰ��� �� : " << p_num << endl;
	cout << "����� �� : " << custom << endl;
	for (i = 0; i <= bot; i++) //0=���� 1 ~ bot = bot����
	{
		player p(i, bot);
		p_v.push_back(p);
		for (j = 0; j < c_num; j++)
		{
			p_v[i].makeship(1); //ship ��ӹ��� ship_�װ������� �� �ڸ�
		}
		for (j = 0; j < b_num; j++)
		{
			p_v[i].makeship(2); //ship ��ӹ��� ship_������ �� �ڸ�
		}
		for (j = 0; j < p_num; j++)
		{
			p_v[i].makeship(3); //ship ��ӹ��� ship_�ʰ����� �� �ڸ�
		}
		for (j = 0; j < custom; j++)
		{
			p_v[i].makeship(4); //ship ��ӹ��� ship_������� �� �ڸ�
		}
		othermap map;
		maps_v.push_back(map); // ������ ��������� �ش� ��ġ�� ������ �ִ��� �˱� ���� �� 2���� �迭
	}
	while (turn < MAX_TURN)
	{
		if (alive == 1) // �� �Ѹ� ��Ƴ����� �¸�
		{
			for (p_index = p_v.begin(); p_index != p_v.end(); p_index++) {
				if (p_index->ship_arr[0]->gethealth() != 0)
				{
					cout << "P" << p_index->getid() << " �� �¸��߽��ϴ�." << endl;
				}
			}
			return;
		}
		alive = bot + 1;
		for (p_index = p_v.begin(); p_index != p_v.end(); p_index++) // ��� �÷��̾ �Ϸ��Ҷ����� �ݺ�
		{
			who = who % (bot + 1);
			if (p_index->ship_arr[0]->gethealth() <= 0) // �й� ���� ù��°(�װ�����) ������ ��ħ�Ǿ�����
			{
				alive--;
				cout << "Player " << who << "�� �й��߽��ϴ�." << endl;
				if (alive <= 1)
				{
					break;
				}
			}
			else
			{
				//q = p_index->ship_index;
				for (q = 0; q < p_index->get_unitmax(); q++) //�÷��̾ ������ �ִ� ��� ����� ������ �Ϸ�ɶ����� �ݺ�
				{
					p_index->initmap();
					for (tmp = 0; tmp < p_index->get_unitmax(); tmp++) {
						//���⼭ ������ ���� ���� ��ħ���� ��� ���� �ʿ� �׸� ship ��ü�� ������ vector�� ����Ǽ� �����Ϸ��� �տ� �ִ� �ֵ� ��� �����
						p_index->drawship(*(p_index->ship_arr[tmp]));
					}
					if (who == 0) // �÷��̾��� ����
					{
						for (i = 0; i <= bot; i++)
						{
							if (p_v[i].ship_arr[0]->gethealth() >= 1) // �̹� �й��� �÷��̾��� ���� ��� ����
							{
								cout << "P" << i << endl;
								cout << "=======================" << endl;
								maps_v[i].showothermap();
								cout << "=======================" << endl;
							}
						}
						cout << "P" << who << endl;
						cout << "=======================" << endl;
						p_index->showmap();
						cout << "=======================" << endl;
						p_index->showship(q);
						if (p_index->ship_arr[q]->gethealth() > 0) // �谡 ��������� ���� Ȥ�� �̵�
						{
							p_index->ship_arr[q]->sound();
							do {
								p_index->ship_arr[q]->comment();
								cin >> input;
							} while (input < 1 || input > 2); // ����, �̵� �߿� ����

							if (input == 1) // ����
							{
								do {
									cout << "������ �÷��̾��? (�ִ� : " << bot << ") : ";
									cin >> p;
								} while (p > bot || p < 0);
								p_index->ship_arr[q]->getkind();
								do {
									cout << "������ ��ǥ�� �Է��Ͻÿ� : " << endl;
									cout << "X ��ǥ : ";
									cin  >>  xpos;
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(256, '\n');
									}
								} while ((xpos > MAPSIZE || xpos < 0));
								do {
									cout << endl;
									cout << "Y ��ǥ : ";
									cin >> ypos;
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(256, '\n');
									}
								} while ((ypos > MAPSIZE || ypos < 0));
								tmp = p_index->attack(xpos, ypos, &p_v[p], *(p_index->ship_arr[q])); //p��°�� �ִ� �÷��̾� ���� p_v�� 1���� ������ �ƴ϶� 0���� �����̴�.
								if (tmp != 0)
								{
									maps_v[p].other_map[ypos][xpos] = 1;
								}
								else
								{
									maps_v[p].other_map[ypos][xpos] = 0;
								}
							}
							else if (input == 2) // �̵�
							{
								do {
									cout << p_index->ship_arr[q]->getmove_point() << " ��ŭ (0 ��ȸ��)  (1 ����)  (2 ��ȸ��)" << endl;
									cin >> input;
								} while (input != 0 && input != 1 && input != 2);
								if (p_index->move(input, *(p_index->ship_arr[q])) == 1)
								{
									cout << "�̵��߽��ϴ�." << endl;
								}
								else
								{
									cout << "�ش� ��ġ�� �̵��� �Ұ��� �մϴ�." << endl;
								}
							}
						}
						else // �谡 ��ħ�� ���
						{
							cout << "��ħ�� ���Դϴ�." << endl;
						}
						Sleep(1000);
						system("cls");
						cout << "////////////////���� ��//////////////" << endl;
					}
					else//bot
					{
						system("cls");
						cout << who << " bot ���� ���Դϴ�." << endl;
						if (p_index->ship_arr[q]->gethealth() > 0) {//�谡 ����ִ°�?
							input = rand() % 2;
							if (input == 1)
							{
								xpos = rand() % MAPSIZE;
								Sleep(1000);
								ypos = rand() % MAPSIZE;
								Sleep(1000);
								do {
									p = rand() % (bot + 1);
								} while (p_v[p].ship_arr[0]->gethealth() <= 0); // ������ �÷��̾ �̹� �й��� ��� �ٽ� �÷��̾� ����
								tmp = p_index->attack(xpos, ypos, &p_v[p], *(p_index->ship_arr[q]));
								if (tmp != 0)
								{
									maps_v[p].other_map[ypos][xpos] = 1;
								}
								else
								{
									maps_v[p].other_map[ypos][xpos] = 0;
								}
							}
							else
							{
								cout << "�̵����Դϴ�." << endl;
								Sleep(1000);
								input = rand() % 3;
								p_index->move(input, *(p_index->ship_arr[q]));
							}
						}
						system("cls");
					}
				}
			}
			who++; // ���� �ѱ�
			cout << "P" << p_index->getid() << " ���ʰ� ����Ǿ����ϴ�." << endl;
		}
		turn++;
	}
	//50���� ������ ���� ���� �̰������ �ȳ���
	cout << "50���� �Ѿ����ϴ�. ��⸦ �����մϴ�." << endl;
	//4. �ݺ�����
	//   1. ship vector�� 1��° �ִ� �踦 ������ ���ΰ� ������ ���ΰ�
	//   2. �����̸� ����(0�� 1���� 2��) ����, �����Ѵٸ� ���� ��ġ�� ������ �÷��̾�(x,y, player) ����
	//   3. �ൿ�� ��������(do_point ==0) ���� ship vector�� �ִ� ship ��ü�� �Ѿ
	//   4. ship vector�� �ִ� ��� ship���� �ൿ�� ������ �� ���� �ִ� map�� othermap_v�� ������
	//4. �ݺ�����(��Ƽ)
}
void server(int level) //message send
{
	WSADATA wsadata;
	SOCKET hservsocket;
	SOCKET hclntsocket;
	SOCKADDR_IN servaddr;
	SOCKADDR_IN clntaddr;
	int sizeclntaddr;
	int x, y;
	char message[2];

	if (WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		cout << "WSAStartup fuc error" << endl;
	}

	hservsocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hservsocket == INVALID_SOCKET)
	{
		cout << "socket fuc error" << endl;
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi("50000"));

	if (bind(hservsocket, (SOCKADDR*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)//���� �ּ� �Ҵ�
	{
		cout << "bind fuc error" << endl;
	}

	if (listen(hservsocket, 500) == SOCKET_ERROR)//���� ��û ��� 5ȸ
	{
		cout << "listen fuc error" << endl;
	}
	srand(time(NULL));
	system("ipconfig");
	cout << "�÷��̾� ������ ��ٸ��� �ֽ��ϴ�." << endl;
	for (int i = 0; i < MAX_TURN*level; i++)
	{
		sizeclntaddr = sizeof(clntaddr);
		hclntsocket = accept(hservsocket, (SOCKADDR *)&clntaddr, &sizeclntaddr);//���� ��û ����
		if (hclntsocket == INVALID_SOCKET)
		{
			cout << "accept fuc error" << endl;
			cout << "�ش� ��Ʈ�� �̹� ����� �Դϴ�. ���� ���� �մϴ�." << endl;
			closesocket(hclntsocket);
			WSACleanup();
			return;
		}
		cout << "�÷��̾ �����߽��ϴ�." << endl;
		x = rand() % MAPSIZE;
		message[0] = (char)x;
		Sleep(3000);
		y = rand() % MAPSIZE;
		message[1] = (char)y;
		cout << "x ��ǥ : " << (int)message[0] << " y ��ǥ : " << (int)message[1] << "�� �����մϴ�." << endl; // �������� map�� �ش� ��ǥ�� ����
		send(hclntsocket, message, sizeof(message), 0);//������ ����
		closesocket(hclntsocket);
	}
	WSACleanup();
}

void client(const char *ip, int *x, int *y)//message receive
{
	WSADATA wsadata;
	SOCKET hsocket;
	char message[20];
	int strlen;
	SOCKADDR_IN servaddr;

	//Load Winsocket 2.2 DLL
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		cout << "WSAStartup fuc error" << endl;
	}
	hsocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hsocket == INVALID_SOCKET)
	{
		cout << "hsocket fuc error" << endl;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip);
	servaddr.sin_port = htons(atoi("50000"));

	if (connect(hsocket, (SOCKADDR*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
	{
		cout << "connect fuc error" << endl;
		cout << "���� ��û Ƚ���� �ʰ��߽��ϴ�." << endl;
		closesocket(hsocket);
		WSACleanup();
	}
	strlen = recv(hsocket, message, sizeof(message) - 1, 0);
	if (strlen == -1)
	{
		cout << "read fuc error" << endl;
		cout << "���� ��û Ƚ���� �ʰ��߽��ϴ�." << endl;
	}
	*x = (int)message[0];
	*y = (int)message[1];
	closesocket(hsocket);
	WSACleanup();
}
void gamestart_multi()
{
	int input;
	string c_ip;
	int level = 5;
	cout << "1. ���� 2. ���� (��������� �ٸ� ����)" << endl;
	cin >> input;
	if (input == 1) // ���� ����
	{
		cout << "���̵� " << level << "���� open" << endl;
		server(level);
	}
	else if (input == 2) // ���� ����
	{
		int turn = 0;
		int i = 0;
		int bot = 0;
		int c_num, b_num, p_num, custom, j, tmp, q;
		int xpos, ypos;
		int alive = 0;
		int count = 0;
		cout << "������ IP �Է�" << endl;
		cin >> c_ip;
		const char *connect_ip = c_ip.c_str();
		cout << connect_ip << " �� ���� �õ��մϴ�." << endl;
		make_ship_num(&c_num, &b_num, &p_num, &custom);
		cout << "�װ����� �� : " << c_num << endl;
		cout << "���� �� : " << b_num << endl;
		cout << "�ʰ��� �� : " << p_num << endl;
		cout << "����� �� : " << custom << endl;
		player p(i, bot);
		ship_battleship sb(5, 5, 0, 1); // �������� map���� ������ ������ ����
		for (j = 0; j < c_num; j++)
		{
			p.makeship(1); //ship ��ӹ��� ship_�װ������� �� �ڸ�
		}
		for (j = 0; j < b_num; j++)
		{
			p.makeship(2); //ship ��ӹ��� ship_������ �� �ڸ�
		}
		for (j = 0; j < p_num; j++)
		{
			p.makeship(3); // ship ��ӹ��� ship_�ʰ����� �� �ڸ�
		}
		for (j = 0; j < custom; j++)
		{
			p.makeship(4); // ship ��ӹ��� ship_������� �� �ڸ�
		}
		othermap map;//������ ��������� �ش� ��ġ�� ������ �ִ��� �˱� ���� �� 2���� �迭

		while (turn < MAX_TURN)
		{
			cout << turn << "��° ��" << endl;
			cout << MAX_TURN - turn << " �� ���ҽ��ϴ�." << endl;
			if (p.ship_arr[0]->gethealth() <= 0)//�й� ���� ù��°(�װ�����) ������ ��ħ�Ǿ�����
			{
				cout << "Player�� �й��߽��ϴ�." << endl;
				return;
			}
			else
			{
				for (j = 0; j < level; j++)
				{
					cout << "���� " << connect_ip << "�� ���� ��û���Դϴ�." << endl;
					client(connect_ip, &xpos, &ypos);
					cout << "������ ����ɴϴ�" << endl;
					tmp = p.attack(xpos, ypos, &p, sb); //sb �������� ������ player p�� map���� ������ ������� ��ó�� ǥ��
					if (tmp != 0) // ���ݿ� ���� ���
					{
						map.other_map[ypos][xpos] = 1;
					}
					else // ������ ���� ���
					{
						map.other_map[ypos][xpos] = 0;
					}
				}
				system("cls");
				for (q = 0; q < p.get_unitmax(); q++) //�÷��̾ ������ �ִ� ��� ����� ������ �Ϸ�ɶ����� �ݺ�
				{
					p.initmap();
					for (tmp = 0; tmp < p.get_unitmax(); tmp++) {
						p.drawship(*p.ship_arr[tmp]);//��ħ���� ��� ���� �ʿ� �׸� ship ��ü�� ������ vector�� ����Ǽ� �����Ϸ��� �տ� �ִ� �ֵ� �� �� ��� �����
					}
					cout << "=======================" << endl;
					map.showothermap();
					cout << "=======================" << endl;
					cout << "=======================" << endl;
					p.showmap();
					cout << "=======================" << endl;
					p.showship(q);
					p.ship_arr[q]->sound();
					do {
						cout << p.ship_arr[q]->getmove_point() << " ��ŭ (0 ��ȸ��)  (1 ����)  (2 ��ȸ��)" << endl;
						cin >> input;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(256, '\n');
						}
					} while (input != 0 && input != 1 && input != 2);
					if (p.move(input, *(p.ship_arr[q])) == 1)
					{
						cout << "�̵��߽��ϴ�." << endl;
					}
					else
					{
						cout << "�ش� ��ġ�� �̵��� �Ұ��� �մϴ�." << endl;
					}

					Sleep(1000);
					system("cls");
				}
			}
			cout << "P" << p.getid() << " ���ʰ� ����Ǿ����ϴ�." << endl;
			turn++;
		}
		//p.get_unitmax()�� �� ô(alive ���� ��)�� ��Ƴ��Ҵ��� ǥ��
		for (q = 0; q < p.get_unitmax(); q++) {
			p.showship(q);
			if (p.ship_arr[q]->gethealth() > 0)
			{
				alive++;
			}
			count++;
		}
		cout << "�� " << count << "ô �߿��� " << alive << " ô�� ��Ƴ��ҽ��ϴ�." << endl;
		cout << "player �¸�" << endl;
	}
	else
	{
		return;
	}
	//1. ��Ƽ�÷���
	//2. ��Ƽ�� 1:1
}
int main()
{
	system("mode con cols=80 lines=62");
	int user_input;
	while (1 == 1) {
		cout << "                 ���������������������" << endl;
		cout << "                 ��                                    ��" << endl;
		cout << "                 ��                                    ��" << endl;
		cout << "                 ��           1. single play           ��" << endl;
		cout << "                 ��                                    ��" << endl;
		cout << "                 ��            2. multi play           ��" << endl;
		cout << "                 ��                                    ��" << endl;
		cout << "                 ��            3. game rule            ��" << endl;
		cout << "                 ��                                    ��" << endl;
		cout << "                 ��           other. game end          ��" << endl;
		cout << "                 ��                                    ��" << endl;
		cout << "                 ��                                    ��" << endl;
		cout << "                 ���������������������\n" << endl;
		cout << "                                �޴� ���� : ";
		cin >> user_input;
		system("cls");
		if (user_input == 1)
		{
			gamestart_single(); // �̱��÷���
		}
		else if (user_input == 2)
		{
			gamestart_multi(); // ��Ƽ�÷���
		}
		else if (user_input == 3) // ���� ����
		{
			cout << "game rule " << endl << endl;
			cout << "single play" << endl << endl;
			cout << "1:1:1...�� ���� ���� �ùķ��̼� ����" << endl;
			cout << "n * n�� ��" << endl;
			cout << "�װ�����(1ô), ����(n * 0.4 * 0.5ô), �����(n * 0.4 * 0.25��), ������(n * 0.4 * 0.25ô) " << endl;
			cout << "�� n * 0.4 + 1 ô�� �谡 �����Ѵ�." << endl;
			cout << "ó�� �����Ҷ� ���� ��ġ�� �����ϰ� �����ȴ�. " << endl;
			cout << "�� ������ ����(�Ǵ� ����) �� �̵� �ΰ��� �ൿ�� 1������ �����ؼ� �� �� �ִ�." << endl;
			cout << "50�� ����" << endl;
			cout << "�װ������� ��ħ���ϸ� �� �÷��̾�� �й�\n" << endl;
			cout << "multi play" << endl << endl;
			cout << "1:1 ���" << endl;
			cout << "������ ���� �÷��̾�� ����" << endl;
			cout << "������ ���� Ƚ���� ���� ���̵�(level) * MAX_TURN �Դϴ�." << endl;
			cout << "���� ���̵�(level) == �� �ϴ� �����ڰ� ���� �ϴ� Ƚ��" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "bye" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}