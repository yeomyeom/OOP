#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>
#include <string>
using namespace std;
#define MAPSIZE 10//맵 사이즈를 내가 원하는대로 바꾸면 좋은데 계속 2차원 배열에서 변수 말고 상수 집어넣으라 하네;;;
#define UNIT_BALANCE 0.4
#define MAX_TURN 5
int map_check(int m[][MAPSIZE], int x, int y, int c, int blocks)
{
	int tmp = 0;
	if (c == 0)//북쪽
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
	else if (c == 1)//동쪽
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
	else if (c == 2)//남쪽
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
	else//서쪽
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
class othermap {
public:
	int other_map[MAPSIZE][MAPSIZE];
	othermap()
	{
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				other_map[i][j] = 0;
			}
		}
	}
	othermap(const othermap& c)
	{
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				other_map[i][j] = c.other_map[i][j];
			}
		}
	}
	void showothermap()
	{
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				if (other_map[i][j] == 0)
				{
					cout << "□";
				}
				else
				{
					cout << "■";
				}
			}
			cout << "" << endl;
		}
	}
	void initothermap()
	{
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				other_map[i][j] = 0;
			}
		}
	}
};
class ship {
private:
	string name;//깊은 복사가 아니라면 char형으로 바꿀 예정
	int kind;
	int x, y;
	int compass;
	int health;
	int block;
	int index;
	int do_point;
	int move_point;
public:
	ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_, int mp_) :kind(kind_), x(x_), y(y_), compass(compass_), health(health_), block(health_), index(index_), move_point(mp_), do_point(1) {
		name = name_;
		//mapsize에 따라서 unit(배ship) 갯수가 결정되고 unit 칸수=health(체력) unit 칸수에 비례해서 move_point와 공격력이 결정됨
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
	int hit()//인자가 뭐 필요한지 모르겠음
	{
		health = health - 1;
		cout << name << " 피격 당함" << endl;
		cout << "체력 : " << health << endl;
		if (health == 0)
		{
			block = 0;
			cout << name << " 격침" << endl;
			return 0;//배 격침
		}
		//move_point--;
		return 1;
	}
	int search()
	{
		cout << "상대편 군함을 발견했습니다." << endl;
		cout << "체력 : " << health << endl;
		return 1;
	}
	void move_ship(int direction)
	{
		if (direction == 0)//좌회전
		{
			compass--;
			if (compass < 0)
			{
				compass = 3;
			}
		}
		else if (direction == 1)//직진
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
		else//우회전
		{
			compass++;
			if (compass >= 4)
			{
				compass = 0;
			}
		}
	}
	virtual void comment(int kind) {
		if (kind == 1)
		{
			cout << "어느 동작을 할 것입니까? 1 : 정찰  2. 이동  다른값. 강제 종료" << endl;
		}
		else
		{
			cout << "어느 동작을 할 것입니까? 1 : 공격  2. 이동  다른값. 강제 종료" << endl;
		}
	}
};
class ship_carrier :public ship {
public:
	ship_carrier(int x_, int y_, int compass_, int index_) :ship("항공모함", 1, x_, y_, compass_, 5, index_, 1) {}
	void comment(int kind) {
		cout << "어느 동작을 할 것입니까? 1 : 정찰  2. 이동  다른값. 강제 종료" << endl;
	}
};
class ship_battleship :public ship {
public:
	ship_battleship(int x_, int y_, int compass_, int index_) :ship("전함", 2, x_, y_, compass_, 4, index_, 2) {}
};
class ship_patrol :public ship {
public:
	ship_patrol(int x_, int y_, int compass_, int index_) :ship("초계함", 3, x_, y_, compass_, 3, index_, 3) {}
};

class player {
private:
	int id;
	int unit_max;//최대로 가질 수 있는 배의 수
	int unit_num;//현재 가지고 있는 배의 수
				 //int unit_index;//iterator 기능//unit_index 변수는 unit_num과 같은데 아직 모르겠음
	int map[MAPSIZE][MAPSIZE];//player 본인의 맵
	int bot_num;
public:
	vector<ship> ship_v;
	vector<ship>::iterator ship_index;
	int state;//멀티에서 쓸거
	player(int id_, int bot_num_) : id(id_), bot_num(bot_num_), unit_num(0), state(0) {
		unit_max = (int)(MAPSIZE * UNIT_BALANCE) + 1;// 배를 최대로 만들 수 있는 수를 어떻게 해야할까?
													 //unit_max = 4;//TEST 코드에서는 4대를 최대 보유수로 함
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				map[i][j] = 0;
			}
		}
		ship_index = ship_v.begin();//ship_index 초기화
	}
	/*player(const player &c):id(c.id),unit_max(c.unit_max),unit_num(c.unit_num),unit_index(c.unit_index),bot_num(c.bot_num)
	{
	//copy constructer 생략 나중에 필요할지도....
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
	void makeship(int input_kind)
	{
		int x, y, c, health;
		//FILE *pt=fopen("/ships/ship_info.txt","r"); 파일로 읽어오고 싶다 수정하기 편하게
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
			else
			{
				health = 3;
			}
			srand(time(NULL));
			do {
				x = rand() % MAPSIZE;
				Sleep(100);
				y = rand() % MAPSIZE;
				Sleep(100);
				c = rand() % 4;
			} while (map_check(map, x, y, c, health) != 1);
			unit_num++;
			if (input_kind == 1)
			{
				//ship_carrier(int x_, int y_, int compass_, int index_)
				ship_carrier *c_new = new ship_carrier(x, y, c, unit_num);
				ship_v.push_back(*c_new);////////////////
				drawship(*c_new);
			}
			else if (input_kind == 2)
			{
				ship_battleship *b_new = new ship_battleship(x, y, c, unit_num);
				ship_v.push_back(*b_new);//////////////////
				drawship(*b_new);
			}
			else
			{
				ship_patrol *p_new = new ship_patrol(x, y, c, unit_num);
				ship_v.push_back(*p_new);///////////////////
				drawship(*p_new);
			}
			//ship s_new(name, kind, x, y, c, health, unit_num);
			//ship_v.push_back(s_new);
			//unit_index = unit_num;//unit_index 변수는 아직 무슨 역할에 넣을지 모름
			//cout << unit_num << " 번째 배를 생성했습니다." << endl;
			//drawship(s_new);
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
		if (heal <= 0) {//격침되면 맵에 안그림
						//cout << "격침당한 배는 안그립니다." << endl;
			index = 0;
		}
		if (c == 0)
		{
			for (tmp = 0;tmp < block;tmp++)
			{
				map[y][x] = index;
				y--;
			}
		}
		else if (c == 1)
		{
			for (tmp = 0;tmp < block;tmp++)
			{
				map[y][x] = index;
				x++;
			}
		}
		else if (c == 2)
		{
			for (tmp = 0;tmp < block;tmp++)
			{
				map[y][x] = index;
				y++;
			}
		}
		else
		{
			for (tmp = 0;tmp < block;tmp++)
			{
				map[y][x] = index;
				x--;
			}
		}
	}
	void initmap()
	{
		int i, j;
		for (i = 0;i < MAPSIZE;i++)
		{
			for (j = 0;j < MAPSIZE;j++)
			{
				map[i][j] = 0;
			}
		}
	}
	void showmap()
	{
		int x, y;

		for (y = 0;y < MAPSIZE;y++)
		{
			for (x = 0;x < MAPSIZE;x++)
			{
				if (map[y][x] == 0)
				{
					cout << "□";
				}
				else if (map[y][x] == 1)
				{
					cout << " 1";
				}
				else if (map[y][x] == 2)
				{
					cout << " 2";
				}
				else if (map[y][x] == 3)
				{
					cout << " 3";
				}
				else if (map[y][x] == 4)
				{
					cout << " 4";
				}
				else if (map[y][x] == 5)
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
	void showship()
	{
		//vector에 있는 정보들 출력
		cout << ship_index->getindex() << "번째 함선 : " << ship_index->getname() << endl;
		cout << "체력 : " << ship_index->gethealth() << endl;
		cout << "위치 : " << ship_index->getx() << ship_index->gety() << ship_index->getcompass() << endl;
	}
	void erasemap(int index)//move 함수를 쓸때 move 전에 ship에 대한 잔상이 map에 남아 있어서 충돌판정을 함 그래서 이동 전에 내 잔상부터 지우는 작업 필요
	{
		int x, y;
		for (y = 0;y < MAPSIZE;y++)
		{
			for (x = 0;x < MAPSIZE;x++)
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
		int compass = s.getcompass();
		int x = s.getx();
		int y = s.gety();
		int dp = s.getdo_point();
		int mp = s.getmove_point();
		erasemap(s.getindex());
		if (dp > 0) {
			if (direction == 0)//좌회전
			{
				compass--;
				if (compass < 0)
				{
					compass = 3;
				}
			}
			else if (direction == 1)//직진
			{
				if (compass == 0)
				{
					y -= mp;
				}
				else if (compass == 1)
				{
					x += mp;
				}
				else if (compass == 2)
				{
					y += mp;
				}
				else
				{
					x -= mp;
				}
			}
			else if (direction == 2)//우회전
			{
				compass++;
				if (compass >= 4)
				{
					compass = 0;
				}
			}
			else
			{
				cout << "방향 오류" << endl;
				return 0;
			}
			if (map_check(map, x, y, compass, s.getblock()) == 1)//이거 확인하기 전에 내 정보를 지워야함 직진할때 이미 해당 칸에 숫자가 들어가 있어서(이동 전의 나) 충돌 판정 남 
			{
				cout << s.getindex() << " 배를 " << x << y << compass << " 로 이동시켰습니다." << endl;
				s.move_ship(direction);
				ship_v[s.getindex() - 1] = s;//바뀐 ship의 위치 정보를 갱신한다.와 이거 -1 안해서 오류난거였네 GG
				initmap();
				for (int i = 0; i < unit_max;i++)
				{
					drawship(ship_v[i]);
				}
				return 1;
			}
			else
			{
				for (int i = 0; i < unit_max;i++)
				{
					drawship(ship_v[i]);
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
	int attack(int x, int y, player *p, ship s)//좌표, 공격 당하는 애, 공격을 하는애
	{
		int r;

		if (s.getkind() == 1)
		{
			r = p->p_search(x, y);
		}
		else
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
			result = ship_v[i - 1].hit();
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
			result = ship_v[i - 1].search();
		}
		Sleep(2000);
		return i;
	}
};
void make_ship_num(int *c, int *b, int *p, int *custom)//밸런스에 맞게 유닛들 생성
{
	srand(time(NULL));
	cout << "생성할 전함들의 갯수는 " << endl;
	*c = 1;//항공모함은 항상 1
	*b = 2;
	*p = 2;
	*custom = 0;
	//일단 커스텀 객체는 0
	/*do {
	*b = rand() % (int)(MAPSIZE*UNIT_BALANCE/2);
	Sleep(2000);
	*p = rand() % (int)(MAPSIZE*UNIT_BALANCE/2);
	} while ((*b) + (*p) + (*custom) > (int)(MAPSIZE*UNIT_BALANCE));*/
}
void gamestart_single()
{
	int turn = 0;
	int input, p, tmp, xpos, ypos, i, j;
	int bot;
	int c_num, b_num, p_num, custom;
	int alive;
	cout << "Single playe" << endl;
	cout << "Map Size " << MAPSIZE << endl;
	cout << "How many bots? : ";
	cin >> bot;
	cout << bot << " 개의 봇을 생성 했습니다." << endl;
	alive = bot + 1;
	//const int bots = bot;
	//player p[bots];
	vector<player> p_v;
	vector<player>::iterator p_index;
	vector<othermap> maps_v;//맞았는지 안맞았는지 보여주는 map vector 다른사람이 쏘는 것도 볼 수 있다.
	vector<othermap> ::iterator maps_index;
	int who = 0;
	make_ship_num(&c_num, &b_num, &p_num, &custom);
	cout << c_num << b_num << p_num << endl;
	for (int i = 0;i <= bot;i++)//0=본인 1~bot = bot갯수
	{
		player p(i, bot);
		p_v.push_back(p);
		for (j = 0;j < c_num;j++)
		{
			p_v[i].makeship(1);//ship 상속받은 ship_항공모함, ship_전함, ship_초계함이 들어갈 자리
		}
		for (j = 0;j < b_num;j++)
		{
			p_v[i].makeship(2);//ship 상속받은 ship_항공모함, ship_전함, ship_초계함이 들어갈 자리
		}
		for (j = 0;j < p_num;j++)
		{
			p_v[i].makeship(3);//ship 상속받은 ship_항공모함, ship_전함, ship_초계함이 들어갈 자리
		}
		othermap map;
		maps_v.push_back(map);//상대방이 사격했을때 해당 위치에 무엇이 있는지 알기 위한 빈 2차원 배열
	}
	while (turn < MAX_TURN)
	{
		if (alive == 1)//단 한명만 살아남으면 승리
		{
			for (p_index = p_v.begin();p_index != p_v.end();p_index++) {
				if (p_index->ship_v[0].gethealth() != 0)
				{
					cout << "P" << p_index->getid() << " 가 승리했습니다." << endl;
				}
			}
			return;
		}
		alive = bot + 1;
		for (p_index = p_v.begin();p_index != p_v.end();p_index++) //모든 플레이어가 완료할때까지 반복
		{
			who = who % (bot + 1);
			if (p_index->ship_v[0].gethealth() <= 0)//패배 조건 첫번째(항공모함) 전함이 격침되었을때
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
				for (p_index->ship_index = p_index->ship_v.begin();p_index->ship_index != p_index->ship_v.end();p_index->ship_index++) //플래이어가 가지고 있는 모든 배들의 조종이 완료될때까지 반복
				{
					p_index->initmap();
					for (tmp = 0;tmp < p_index->get_unitmax();tmp++) {
						p_index->drawship(p_index->ship_v[tmp]);//격침당한 배는 빼고 맵에 그림 ship 객체는 안지움 vector에 저장되서 삭제하려면 앞에 있는 애들 다 시 당겨 줘야함
					}
					if (who == 0)
					{
						for (i = 0;i <= bot;i++)
						{
							cout << "P" << i << endl;
							cout << "=======================" << endl;
							maps_v[i].showothermap();
							cout << "=======================" << endl;
						}
						cout << "P" << who << endl;
						cout << "=======================" << endl;
						p_index->showmap();
						cout << "=======================" << endl;
						p_index->showship();
						if (p_index->ship_index->gethealth() > 0) {//배가 살아있는가?
							p_index->ship_index->comment(p_index->ship_index->getkind());
							cin >> input;
							if (input == 1)
							{
								do {
									cout << "공격할 플레이어는? (최대) " << bot << endl;
									cin >> p;
								} while (p > bot || p < 0);
								p_index->ship_index->getkind();
								do {
									cout << "공격할 좌표를 입력하시오 : " << endl;
									cout << "X 좌표 : ";
									cin >> xpos;
									cout << "\nY 좌표 : ";
									cin >> ypos;
								} while ((xpos > MAPSIZE || xpos < 0) && (ypos > MAPSIZE || ypos < 0));
								tmp = p_index->attack(xpos, ypos, &p_v[p], *(p_index->ship_index)); //p번째에 있는 플레이어 공격 p_v는 1부터 시작이 아니라 0부터 시작이다.
								if (tmp != 0)
								{
									maps_v[p].other_map[ypos][xpos] = 1;
								}
							}
							else if (input == 2)
							{
								do {
									cout << p_index->ship_index->getmove_point() << " 만큼 0 : 좌회전 1 :직진 2 : 우회전" << endl;
									cin >> input;
								} while (input != 0 && input != 1 && input != 2);
								if (p_index->move(input, *(p_index->ship_index)) == 1)
								{
									cout << "이동했습니다." << endl;
								}
								else
								{
									cout << "해당 위치로 이동이 불가능 합니다." << endl;
								}
							}
							else
							{
								return;//강제 종료
							}
						}
						else
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
						if (p_index->ship_index->gethealth() > 0) {//,배가 살아있는가?
							input = rand() % 2;
							if (input == 1)
							{
								xpos = rand() % MAPSIZE;
								Sleep(1000);
								ypos = rand() % MAPSIZE;
								Sleep(1000);
								p = rand() % (bot + 1);
								tmp = p_index->attack(xpos, ypos, &p_v[p], *(p_index->ship_index));
								if (tmp != 0)
								{
									maps_v[p].other_map[ypos][xpos] = 1;
								}
							}
							else
							{
								cout << "이동중입니다." << endl;
								Sleep(1000);
								input = rand() % 3;
								p_index->move(input, *(p_index->ship_index));
							}
						}
						system("cls");
					}
				}
			}
			who++;
			cout << "P" << p_index->getid() << " 차례가 종료되었습니다." << endl;
		}
		turn++;
	}
	//50턴이 끝나고 나면 누가 이겼는지는 안나옴
	cout << "50턴이 넘었습니다. 경기를 종료합니다." << endl;
	//4. 반복시작
	//   1. ship vector에 1번째 있는 배를 움직일 것인가 공격할 것인가
	//   2. 움직이면 방향(0왼 1직진 2오), 공격할꺼면 공격 위치와 공격할 플레이어(x,y, player)
	//   3. 행동을 마쳤으면(do_point ==0) 다음 ship vector에 2번째 있는 ship 객체로 넘어감
	//   4. ship vector에 있는 모든 ship들의 행동을 결정한 후 현재 있는 map을 othermap_v에 복사함
	//4. 반복시작(멀티)
}
void server(int level)//message send
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
	for (int i = 0;i < MAX_TURN*level;i++)
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
		cout << (int)message[0] << (int)message[1] << "를 전송합니다." << endl;
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
	strlen=recv(hsocket, message, sizeof(message) - 1, 0);
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
	int level = (int)MAPSIZE / 2;
	cout << "1. 공격 2. 수비 (강제종료는 다른 숫자)" << endl;
	cin >> input;
	if (input == 1)
	{
		cout << "난이도 " << level << "서버 open" << endl;
		server(level);
	}
	else if (input == 2)
	{
		int turn = 0;
		int i = 0;
		int bot = 0;
		int c_num, b_num, p_num, custom, j, tmp;
		int xpos, ypos;
		cout << "공격자 IP 입력" << endl;
		cin >> c_ip;
		const char *connect_ip = c_ip.c_str();
		cout << connect_ip << " 로 연결 시도합니다." << endl;
		make_ship_num(&c_num, &b_num, &p_num, &custom);
		cout << c_num << b_num << p_num << endl;
		player p(i, bot);
		ship_battleship sb(5, 5, 0, 1);
		for (j = 0;j < c_num;j++)
		{
			p.makeship(1);//ship 상속받은 ship_항공모함, ship_전함, ship_초계함이 들어갈 자리
		}
		for (j = 0;j < b_num;j++)
		{
			p.makeship(2);
		}
		for (j = 0;j < p_num;j++)
		{
			p.makeship(3);
		}
		othermap map;//상대방이 사격했을때 해당 위치에 무엇이 있는지 알기 위한 빈 2차원 배열

		while (turn < MAX_TURN)
		{
			cout << turn << "번째 턴" << endl;
			cout << MAX_TURN - turn << " 번 남았습니다." << endl;
			if (p.ship_v[0].gethealth() <= 0)//패배 조건 첫번째(항공모함) 전함이 격침되었을때
			{
				cout << "Player가 패배했습니다." << endl;
				return;
			}
			else
			{
				for (j = 0;j < level;j++)
				{
					cout << "서버 " << connect_ip << "로 연결 요청중입니다." << endl;
					client(connect_ip, &xpos, &ypos);
					cout << "포격이 날라옵니다" << endl;
					tmp = p.attack(xpos, ypos, &p, sb); //p번째에 있는 플레이어 공격 p_v는 1부터 시작이 아니라 0부터 시작이다.
					if (tmp != 0)
					{
						map.other_map[ypos][xpos] = 1;
					}
				}
				system("cls");
				for (p.ship_index = p.ship_v.begin();p.ship_index != p.ship_v.end();p.ship_index++) //플래이어가 가지고 있는 모든 배들의 조종이 완료될때까지 반복
				{
					p.initmap();
					for (tmp = 0;tmp < p.get_unitmax();tmp++) {
						p.drawship(p.ship_v[tmp]);//격침당한 배는 빼고 맵에 그림 ship 객체는 안지움 vector에 저장되서 삭제하려면 앞에 있는 애들 다 시 당겨 줘야함
					}
					cout << "=======================" << endl;
					map.showothermap();
					cout << "=======================" << endl;
					cout << "=======================" << endl;
					p.showmap();
					cout << "=======================" << endl;
					p.showship();
					do {
						cout << p.ship_index->getmove_point() << " 만큼 0 : 좌회전 1 :직진 2 : 우회전" << endl;
						cin >> input;
					} while (input != 0 && input != 1 && input != 2);
					if (p.move(input, *(p.ship_index)) == 1)
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
		int alive = 0;
		int count = 0;
		for (p.ship_index = p.ship_v.begin();p.ship_index != p.ship_v.end();p.ship_index++) {
			p.showship();
			if (p.ship_index->gethealth() > 0)
			{
				alive++;
			}
			count++;
		}
		cout <<"총 "<<count <<"척 중에서 "<<alive<<" 척이 살아남았습니다. \n player 승리" << endl;
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
	//system("mode con cols=75 lines=60");
	int user_input;
	cout << "1. single play \n2. multi play \n3. tutorial" << endl;
	cin >> user_input;
	if (user_input == 1)
	{
		gamestart_single();
	}
	else if (user_input == 2)
	{
		gamestart_multi();
	}
	else if (user_input == 3)
	{
		cout << "tutorial" << endl;
	}
	else
	{
		cout << "bye" << endl;
	}
	system("pause");
	return 0;
}