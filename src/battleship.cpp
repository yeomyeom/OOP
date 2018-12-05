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
	if (c == 0) //북쪽
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
	else if (c == 1) //동쪽
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
	else if (c == 2) //남쪽
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
	else //서쪽
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
class othermap {// 다른 플레이어의 map을 표현하기 위한 클래스
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
					cout << "□";
				}
				else // 공격이나 정찰당한 경우
				{
					cout << "■";
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
		//mapsize에 따라서 unit(배ship) 갯수가 결정되고 unit 칸수= health (처음 체력) 
	}
	ship(const ship& c) : kind(c.kind), x(c.x), y(c.y), compass(c.compass), health(c.health), block(c.block), index(c.index), do_point(c.do_point), move_point(c.move_point) {
		name = c.name;
	}
	/////생성자///////
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
	//////get함수들//////
	int hit()
	{
		health = health - 1;
		cout << name << " 피격 당함" << endl;
		cout << "체력 : " << health << endl;
		if (health == 0)
		{
			block = 0;
			cout << name << " 격침" << endl;
			return 0; // 배 격침
		}
		return 1;
	}
	virtual int search()
	{
		cout << "상대편 " << name << "을 발견했습니다." << endl;
		return 1;
	}
	void move_ship(int direction)
	{
		if (direction == 0) //좌회전
		{
			compass--;
			if (compass < 0)
			{
				compass = 3;
			}
		}
		else if (direction == 1) //직진
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
		else //우회전
		{
			compass++;
			if (compass >= 4)
			{
				compass = 0;
			}
		}
	}
	virtual void comment() {
		cout << "어느 동작을 할 것입니까? (1 공격)   (2 이동)" << endl;
	}
	virtual void sound() {}
};
class ship_carrier :public ship {
public:
	ship_carrier(int x_, int y_, int compass_, int index_) :ship("항공모함", 1, x_, y_, compass_, 5, index_, 1) {}
	void comment() {
		cout << "어느 동작을 할 것입니까?  (1 정찰)   (2 이동)" << endl;
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
	ship_battleship(int x_, int y_, int compass_, int index_) :ship("전함", 2, x_, y_, compass_, 4, index_, 1) {}
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
	ship_patrol(int x_, int y_, int compass_, int index_) :ship("초계함", 3, x_, y_, compass_, 3, index_, 3) {}
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
	ship_submarin(int x_, int y_, int compass_, int index_) :ship("잠수함", 4, x_, y_, compass_, 2, index_, 1) {}
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
	int unit_max; //최대로 가질 수 있는 배의 수
	int unit_num; //현재 가지고 있는 배의 수
	int map[MAPSIZE][MAPSIZE]; //player 본인의 맵
	int bot_num;
public:
	ship * ship_arr[(int)(MAPSIZE * UNIT_BALANCE) + 2];
	int ship_index;
	int state; //멀티에서 사용
	player(int id_, int bot_num_) : id(id_), bot_num(bot_num_), unit_num(0), state(0) {
		unit_max = (int)(MAPSIZE * UNIT_BALANCE) + 1;
		initmap();
		ship_index = 0;//ship_index 초기화
	}
	/*player(const player &c):id(c.id),unit_max(c.unit_max),unit_num(c.unit_num),unit_index(c.unit_index),bot_num(c.bot_num)
	{
	//copy constructer 생략
	}*/
	//////생성자////////
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
	///////get 함수들//////
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
			cout << "배를 만들 수 있는 수를 초과했습니다." << endl;
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
		if (heal <= 0) //격침되면 맵에 안그림
		{
			index = 0;
		}
		if (c == 0) // 북쪽
		{
			for (tmp = 0; tmp < block; tmp++)
			{
				map[y][x] = index;
				y--;
			}
		}
		else if (c == 1) // 동쪽
		{
			for (tmp = 0; tmp < block; tmp++)
			{
				map[y][x] = index;
				x++;
			}
		}
		else if (c == 2) // 남쪽
		{
			for (tmp = 0; tmp < block; tmp++)
			{
				map[y][x] = index;
				y++;
			}
		}
		else // 서쪽
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
				if (map[y][x] == 0) // 빈 공간
				{
					cout << "□";
				}
				else if (map[y][x] == 1) // 첫 번째 ship
				{
					cout << " 1";
				}
				else if (map[y][x] == 2) // 두 번째 ship
				{
					cout << " 2";
				}
				else if (map[y][x] == 3) // 세 번째 ship
				{
					cout << " 3";
				}
				else if (map[y][x] == 4) // 네 번째 ship
				{
					cout << " 4";
				}
				else if (map[y][x] == 5) // 다섯 번째 ship
				{
					cout << " 5";
				}
				else
				{
					cout << "■";
				}
			}
			cout << "" << endl;
		}
	}
	void showship(int index)
	{
		//vector에 있는 정보들 출력
		string com;
		cout << ship_arr[index]->getindex() << "번째 함선: " << ship_arr[index]->getname() << endl;
		cout << "체력: " << ship_arr[index]->gethealth() << endl;
		if (ship_arr[index]->getcompass() == 0)
		{
			com = "북";
		}
		else if (ship_arr[index]->getcompass() == 1)
		{
			com = "동";
		}
		else if (ship_arr[index]->getcompass() == 2)
		{
			com = "남";
		}
		else
		{
			com = "서";
		}
		cout << "위치: " << " x좌표: " << ship_arr[index]->getx() << " y좌표: " << ship_arr[index]->gety() << " 방향: " << com << endl;
	}
	void erasemap(int index) //move 함수를 쓸때 move 전에 ship에 대한 잔상이 map에 남아 있어서 충돌판정을 함 그래서 이동 전에 내 잔상부터 지우는 작업 필요
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
			if (direction == 0) //좌회전
			{
				compass--;
				if (compass < 0) // 이전에 북쪽이었던 경우
				{
					compass = 3; // 서쪽 가리킴
				}
			}
			else if (direction == 1) // 직진
			{
				if (compass == 0) // 북쪽
				{
					y -= mp;
				}
				else if (compass == 1) // 동쪽
				{
					x += mp;
				}
				else if (compass == 2) // 남쪽
				{
					y += mp;
				}
				else // 서쪽
				{
					x -= mp;
				}
			}
			else if (direction == 2)//우회전
			{
				compass++;
				if (compass >= 4) // 이전에 서쪽이었던 경우
				{
					compass = 0; // 북쪽
				}
			}
			else
			{
				cout << "방향 오류" << endl;
				return 0;
			}
			//이거 확인하기 전에 내 정보를 지워야함 직진할때 이미 해당 칸에 숫자가 들어가 있어서(이동 전의 나) 충돌 판정 남
			if (map_check(map, x, y, compass, s.getblock()) == 1)
			{

				if (compass == 0)
				{
					com = "북";
				}
				else if (compass == 1)
				{
					com = "동";
				}
				else if (compass == 2)
				{
					com = "남";
				}
				else
				{
					com = "서";
				}
				//cout << s.getindex() << " 배를 " << " x좌표 : " << x << " y좌표 : " << y << " 방향 : " << com << " 로 이동시켰습니다." << endl;
				s.move_ship(direction);
				*ship_arr[s.getindex() - 1] = s; //바뀐 ship의 위치 정보를 갱신한다.
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
				cout << "배를 해당 위치에 표시할 수 없습니다." << endl;
				return 0;
			}
		}
		else
		{
			cout << "배의 행동력을 다 사용했습니다." << endl;
		}
	}
	int attack(int x, int y, player *p, ship s) //좌표, 공격 당하는 애, 공격을 하는애
	{
		int r;

		if (s.getkind() == 1) // 배가 항공모함인 경우
		{
			PlaySound(TEXT("sound/search.wav"), 0, SND_ASYNC);
			r = p->p_search(x, y);
		}
		else // 배가 항공모함이 아닌 경우
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
			cout << x << " , " << y << "에 아무것도 없습니다." << endl;
		}
		else
		{
			PlaySound(TEXT("sound/attack.wav"), 0, SND_ASYNC);
			result = ship_arr[i - 1]->hit();
			if (result == 0)
			{
				cout << "배를 격침시켰습니다." << endl;
			}
			else
			{
				cout << "맞았습니다." << endl;
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
			cout << x << " , " << y << "에 아무것도 없습니다." << endl;
		}
		else
		{
			result = ship_arr[i - 1]->search();
			if (result == 0) //잠수함 탐지 못함
			{
				cout << x << " , " << y << "에 아무것도 없습니다." << endl;
				i = 0;
			}
		}
		Sleep(2000);
		return i;
	}
};
void make_ship_num(int *c, int *b, int *p, int *custom)//밸런스에 맞게 유닛들 생성
{
	srand(time(NULL));
	cout << "생성할 전함들의 갯수는 " << endl;
	*c = 1; //항공모함은 항상 1
	*b = (int)MAPSIZE*UNIT_BALANCE*0.5; //전함은 MAPSIZE * UNIT_MAX * 0.5
	*p = (int)MAPSIZE*UNIT_BALANCE*0.25; //초계함은 MAPSIZE * UNIT_MAX * 0.25
	*custom = (int)MAPSIZE*UNIT_BALANCE*0.25;; // 잠수함은 MAPSIZE * UNIT_MAX * 0.25
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
	cout << bot << " 개의 봇을 생성 했습니다." << endl;
	alive = bot + 1;
	//const int bots = bot;
	//player p[bots];
	vector<player> p_v;
	vector<player>::iterator p_index;
	vector<othermap> maps_v; //맞았는지 안맞았는지 보여주는 map vector 다른사람이 쏘는 것도 볼 수 있다.
	vector<othermap> ::iterator maps_index;
	int who = 0;
	make_ship_num(&c_num, &b_num, &p_num, &custom);
	cout << "항공모함 수 : " << c_num << endl;
	cout << "전함 수 : " << b_num << endl;
	cout << "초계함 수 : " << p_num << endl;
	cout << "잠수함 수 : " << custom << endl;
	for (i = 0; i <= bot; i++) //0=본인 1 ~ bot = bot갯수
	{
		player p(i, bot);
		p_v.push_back(p);
		for (j = 0; j < c_num; j++)
		{
			p_v[i].makeship(1); //ship 상속받은 ship_항공모함이 들어갈 자리
		}
		for (j = 0; j < b_num; j++)
		{
			p_v[i].makeship(2); //ship 상속받은 ship_전함이 들어갈 자리
		}
		for (j = 0; j < p_num; j++)
		{
			p_v[i].makeship(3); //ship 상속받은 ship_초계함이 들어갈 자리
		}
		for (j = 0; j < custom; j++)
		{
			p_v[i].makeship(4); //ship 상속받은 ship_잠수함이 들어갈 자리
		}
		othermap map;
		maps_v.push_back(map); // 상대방이 사격했을때 해당 위치에 무엇이 있는지 알기 위한 빈 2차원 배열
	}
	while (turn < MAX_TURN)
	{
		if (alive == 1) // 단 한명만 살아남으면 승리
		{
			for (p_index = p_v.begin(); p_index != p_v.end(); p_index++) {
				if (p_index->ship_arr[0]->gethealth() != 0)
				{
					cout << "P" << p_index->getid() << " 가 승리했습니다." << endl;
				}
			}
			return;
		}
		alive = bot + 1;
		for (p_index = p_v.begin(); p_index != p_v.end(); p_index++) // 모든 플레이어가 완료할때까지 반복
		{
			who = who % (bot + 1);
			if (p_index->ship_arr[0]->gethealth() <= 0) // 패배 조건 첫번째(항공모함) 전함이 격침되었을때
			{
				alive--;
				cout << "Player " << who << "가 패배했습니다." << endl;
				if (alive <= 1)
				{
					break;
				}
			}
			else
			{
				//q = p_index->ship_index;
				for (q = 0; q < p_index->get_unitmax(); q++) //플래이어가 가지고 있는 모든 배들의 조종이 완료될때까지 반복
				{
					p_index->initmap();
					for (tmp = 0; tmp < p_index->get_unitmax(); tmp++) {
						//여기서 문제가 생길 수도 격침당한 배는 빼고 맵에 그림 ship 객체는 안지움 vector에 저장되서 삭제하려면 앞에 있는 애들 당겨 줘야함
						p_index->drawship(*(p_index->ship_arr[tmp]));
					}
					if (who == 0) // 플레이어의 차례
					{
						for (i = 0; i <= bot; i++)
						{
							if (p_v[i].ship_arr[0]->gethealth() >= 1) // 이미 패배한 플레이어의 맵은 출력 안함
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
						if (p_index->ship_arr[q]->gethealth() > 0) // 배가 살아있으면 공격 혹은 이동
						{
							p_index->ship_arr[q]->sound();
							do {
								p_index->ship_arr[q]->comment();
								cin >> input;
							} while (input < 1 || input > 2); // 공격, 이동 중에 선택

							if (input == 1) // 공격
							{
								do {
									cout << "공격할 플레이어는? (최대 : " << bot << ") : ";
									cin >> p;
								} while (p > bot || p < 0);
								p_index->ship_arr[q]->getkind();
								do {
									cout << "공격할 좌표를 입력하시오 : " << endl;
									cout << "X 좌표 : ";
									cin  >>  xpos;
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(256, '\n');
									}
								} while ((xpos > MAPSIZE || xpos < 0));
								do {
									cout << endl;
									cout << "Y 좌표 : ";
									cin >> ypos;
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(256, '\n');
									}
								} while ((ypos > MAPSIZE || ypos < 0));
								tmp = p_index->attack(xpos, ypos, &p_v[p], *(p_index->ship_arr[q])); //p번째에 있는 플레이어 공격 p_v는 1부터 시작이 아니라 0부터 시작이다.
								if (tmp != 0)
								{
									maps_v[p].other_map[ypos][xpos] = 1;
								}
								else
								{
									maps_v[p].other_map[ypos][xpos] = 0;
								}
							}
							else if (input == 2) // 이동
							{
								do {
									cout << p_index->ship_arr[q]->getmove_point() << " 만큼 (0 좌회전)  (1 직진)  (2 우회전)" << endl;
									cin >> input;
								} while (input != 0 && input != 1 && input != 2);
								if (p_index->move(input, *(p_index->ship_arr[q])) == 1)
								{
									cout << "이동했습니다." << endl;
								}
								else
								{
									cout << "해당 위치로 이동이 불가능 합니다." << endl;
								}
							}
						}
						else // 배가 격침된 경우
						{
							cout << "격침된 배입니다." << endl;
						}
						Sleep(1000);
						system("cls");
						cout << "////////////////다음 배//////////////" << endl;
					}
					else//bot
					{
						system("cls");
						cout << who << " bot 진행 중입니다." << endl;
						if (p_index->ship_arr[q]->gethealth() > 0) {//배가 살아있는가?
							input = rand() % 2;
							if (input == 1)
							{
								xpos = rand() % MAPSIZE;
								Sleep(1000);
								ypos = rand() % MAPSIZE;
								Sleep(1000);
								do {
									p = rand() % (bot + 1);
								} while (p_v[p].ship_arr[0]->gethealth() <= 0); // 공격할 플레이어가 이미 패배한 경우 다시 플레이어 선택
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
								cout << "이동중입니다." << endl;
								Sleep(1000);
								input = rand() % 3;
								p_index->move(input, *(p_index->ship_arr[q]));
							}
						}
						system("cls");
					}
				}
			}
			who++; // 차례 넘김
			cout << "P" << p_index->getid() << " 차례가 종료되었습니다." << endl;
		}
		turn++;
	}
	//50턴이 끝나고 나면 누가 이겼는지는 안나옴
	cout << "50턴이 넘었습니다. 경기를 종료합니다." << endl;
	//4. 반복시작
	//   1. ship vector에 1번째 있는 배를 움직일 것인가 공격할 것인가
	//   2. 움직이면 방향(0왼 1직진 2오) 선택, 공격한다면 공격 위치와 공격할 플레이어(x,y, player) 선택
	//   3. 행동을 마쳤으면(do_point ==0) 다음 ship vector에 있는 ship 객체로 넘어감
	//   4. ship vector에 있는 모든 ship들의 행동을 결정한 후 현재 있는 map을 othermap_v에 복사함
	//4. 반복시작(멀티)
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

	if (bind(hservsocket, (SOCKADDR*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)//소켓 주소 할당
	{
		cout << "bind fuc error" << endl;
	}

	if (listen(hservsocket, 500) == SOCKET_ERROR)//연결 요청 대기 5회
	{
		cout << "listen fuc error" << endl;
	}
	srand(time(NULL));
	system("ipconfig");
	cout << "플레이어 접속을 기다리고 있습니다." << endl;
	for (int i = 0; i < MAX_TURN*level; i++)
	{
		sizeclntaddr = sizeof(clntaddr);
		hclntsocket = accept(hservsocket, (SOCKADDR *)&clntaddr, &sizeclntaddr);//연결 요청 수락
		if (hclntsocket == INVALID_SOCKET)
		{
			cout << "accept fuc error" << endl;
			cout << "해당 포트가 이미 사용중 입니다. 강제 종료 합니다." << endl;
			closesocket(hclntsocket);
			WSACleanup();
			return;
		}
		cout << "플레이어가 접속했습니다." << endl;
		x = rand() % MAPSIZE;
		message[0] = (char)x;
		Sleep(3000);
		y = rand() % MAPSIZE;
		message[1] = (char)y;
		cout << "x 좌표 : " << (int)message[0] << " y 좌표 : " << (int)message[1] << "를 전송합니다." << endl; // 수비자의 map의 해당 좌표로 포격
		send(hclntsocket, message, sizeof(message), 0);//데이터 전송
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
		cout << "서버 요청 횟수가 초과했습니다." << endl;
		closesocket(hsocket);
		WSACleanup();
	}
	strlen = recv(hsocket, message, sizeof(message) - 1, 0);
	if (strlen == -1)
	{
		cout << "read fuc error" << endl;
		cout << "서버 요청 횟수가 초과했습니다." << endl;
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
	cout << "1. 공격 2. 수비 (강제종료는 다른 숫자)" << endl;
	cin >> input;
	if (input == 1) // 공격 선택
	{
		cout << "난이도 " << level << "서버 open" << endl;
		server(level);
	}
	else if (input == 2) // 수비 선택
	{
		int turn = 0;
		int i = 0;
		int bot = 0;
		int c_num, b_num, p_num, custom, j, tmp, q;
		int xpos, ypos;
		int alive = 0;
		int count = 0;
		cout << "공격자 IP 입력" << endl;
		cin >> c_ip;
		const char *connect_ip = c_ip.c_str();
		cout << connect_ip << " 로 연결 시도합니다." << endl;
		make_ship_num(&c_num, &b_num, &p_num, &custom);
		cout << "항공모함 수 : " << c_num << endl;
		cout << "전함 수 : " << b_num << endl;
		cout << "초계함 수 : " << p_num << endl;
		cout << "잠수함 수 : " << custom << endl;
		player p(i, bot);
		ship_battleship sb(5, 5, 0, 1); // 수비자의 map으로 포격을 날리는 전함
		for (j = 0; j < c_num; j++)
		{
			p.makeship(1); //ship 상속받은 ship_항공모함이 들어갈 자리
		}
		for (j = 0; j < b_num; j++)
		{
			p.makeship(2); //ship 상속받은 ship_전함이 들어갈 자리
		}
		for (j = 0; j < p_num; j++)
		{
			p.makeship(3); // ship 상속받은 ship_초계함이 들어갈 자리
		}
		for (j = 0; j < custom; j++)
		{
			p.makeship(4); // ship 상속받은 ship_잠수함이 들어갈 자리
		}
		othermap map;//상대방이 사격했을때 해당 위치에 무엇이 있는지 알기 위한 빈 2차원 배열

		while (turn < MAX_TURN)
		{
			cout << turn << "번째 턴" << endl;
			cout << MAX_TURN - turn << " 번 남았습니다." << endl;
			if (p.ship_arr[0]->gethealth() <= 0)//패배 조건 첫번째(항공모함) 전함이 격침되었을때
			{
				cout << "Player가 패배했습니다." << endl;
				return;
			}
			else
			{
				for (j = 0; j < level; j++)
				{
					cout << "서버 " << connect_ip << "로 연결 요청중입니다." << endl;
					client(connect_ip, &xpos, &ypos);
					cout << "포격이 날라옵니다" << endl;
					tmp = p.attack(xpos, ypos, &p, sb); //sb 전함으로 수비자 player p의 map으로 포격이 날라오는 것처럼 표현
					if (tmp != 0) // 포격에 맞은 경우
					{
						map.other_map[ypos][xpos] = 1;
					}
					else // 포격을 피한 경우
					{
						map.other_map[ypos][xpos] = 0;
					}
				}
				system("cls");
				for (q = 0; q < p.get_unitmax(); q++) //플래이어가 가지고 있는 모든 배들의 조종이 완료될때까지 반복
				{
					p.initmap();
					for (tmp = 0; tmp < p.get_unitmax(); tmp++) {
						p.drawship(*p.ship_arr[tmp]);//격침당한 배는 빼고 맵에 그림 ship 객체는 안지움 vector에 저장되서 삭제하려면 앞에 있는 애들 다 시 당겨 줘야함
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
						cout << p.ship_arr[q]->getmove_point() << " 만큼 (0 좌회전)  (1 직진)  (2 우회전)" << endl;
						cin >> input;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(256, '\n');
						}
					} while (input != 0 && input != 1 && input != 2);
					if (p.move(input, *(p.ship_arr[q])) == 1)
					{
						cout << "이동했습니다." << endl;
					}
					else
					{
						cout << "해당 위치로 이동이 불가능 합니다." << endl;
					}

					Sleep(1000);
					system("cls");
				}
			}
			cout << "P" << p.getid() << " 차례가 종료되었습니다." << endl;
			turn++;
		}
		//p.get_unitmax()중 몇 척(alive 변수 값)이 살아남았는지 표현
		for (q = 0; q < p.get_unitmax(); q++) {
			p.showship(q);
			if (p.ship_arr[q]->gethealth() > 0)
			{
				alive++;
			}
			count++;
		}
		cout << "총 " << count << "척 중에서 " << alive << " 척이 살아남았습니다." << endl;
		cout << "player 승리" << endl;
	}
	else
	{
		return;
	}
	//1. 멀티플레이
	//2. 멀티는 1:1
}
int main()
{
	system("mode con cols=80 lines=62");
	int user_input;
	while (1 == 1) {
		cout << "                 ■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "                 ■                                    ■" << endl;
		cout << "                 ■                                    ■" << endl;
		cout << "                 ■           1. single play           ■" << endl;
		cout << "                 ■                                    ■" << endl;
		cout << "                 ■            2. multi play           ■" << endl;
		cout << "                 ■                                    ■" << endl;
		cout << "                 ■            3. game rule            ■" << endl;
		cout << "                 ■                                    ■" << endl;
		cout << "                 ■           other. game end          ■" << endl;
		cout << "                 ■                                    ■" << endl;
		cout << "                 ■                                    ■" << endl;
		cout << "                 ■■■■■■■■■■■■■■■■■■■■\n" << endl;
		cout << "                                메뉴 선택 : ";
		cin >> user_input;
		system("cls");
		if (user_input == 1)
		{
			gamestart_single(); // 싱글플레이
		}
		else if (user_input == 2)
		{
			gamestart_multi(); // 멀티플레이
		}
		else if (user_input == 3) // 게임 설명
		{
			cout << "game rule " << endl << endl;
			cout << "single play" << endl << endl;
			cout << "1:1:1...의 턴제 전략 시뮬레이션 게임" << endl;
			cout << "n * n의 맵" << endl;
			cout << "항공모함(1척), 전함(n * 0.4 * 0.5척), 잠수함(n * 0.4 * 0.25대), 구축함(n * 0.4 * 0.25척) " << endl;
			cout << "총 n * 0.4 + 1 척의 배가 등장한다." << endl;
			cout << "처음 시작할때 배의 위치는 랜덤하게 생성된다. " << endl;
			cout << "각 군함은 공격(또는 정찰) 과 이동 두가지 행동중 1가지만 선택해서 할 수 있다." << endl;
			cout << "50턴 제한" << endl;
			cout << "항공모함이 격침당하면 그 플레이어는 패배\n" << endl;
			cout << "multi play" << endl << endl;
			cout << "1:1 대결" << endl;
			cout << "서버는 공격 플레이어는 수비" << endl;
			cout << "공격자 공격 횟수는 서버 난이도(level) * MAX_TURN 입니다." << endl;
			cout << "서버 난이도(level) == 한 턴당 공격자가 공격 하는 횟수" << endl;
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