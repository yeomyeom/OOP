#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>
#include <string>
using namespace std;
#define MAPSIZE 10//맵 사이즈를 내가 원하는대로 바꾸면 좋은데 계속 2차원 배열에서 변수 말고 상수 집어넣으라 하네;;;

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
		if (x <= MAPSIZE-blocks)
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
	ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_) :kind(kind_), x(x_), y(y_), compass(compass_), health(health_), block(health_), index(index_), move_point(1), do_point(1) {
		name = name_;
		//mapsize에 따라서 unit(배ship) 갯수가 결정되고 unit 칸수=health(체력) unit 칸수에 비례해서 move_point와 공격력이 결정됨
	}
	ship(const ship& c) : kind(c.kind),x(c.x),y(c.y),compass(c.compass),health(c.health),block(c.block),index(c.index), do_point(c.do_point),move_point(c.move_point){
		name = c.name;
	}
	/////생성자///////
	string getname()
	{
		return name;
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
	int shoot(int xpos, int ypos)
	{
		int attack = health;//
	}
	int hit()//인자가 뭐 필요한지 모르겠음
	{
		health--;
		//move_point--;
	}
	void move_ship(int direction)
	{
		if (direction == 0)//좌회전
		{
			compass--;
			if (compass < 0)
			{
				compass = 4;
			}
		}
		else if (direction == 1)//직진
		{
			if (compass == 0)
			{
				y--;
			}
			else if (compass == 1)
			{
				x++;
			}
			else if (compass == 2)
			{
				y++;
			}
			else
			{
				x--;
			}
		}
		else//우회전
		{
			compass++;
			if (compass > 4)
			{
				compass = 0;
			}
		}
	}
};

class player {
private:
	int id;
	vector<ship> ship_v;
	vector<ship>::iterator ship_index;
	int unit_max;//최대로 가질 수 있는 배의 수
	int unit_num;//현재 가지고 있는 배의 수
	int unit_index;//iterator 기능//unit_index 변수는 unit_num과 같은데 아직 모르겠음
	int map[MAPSIZE][MAPSIZE];//player 본인의 맵
public:
	player(int id_) : id(id_), unit_num(0), unit_index(0){
		//unit_max = MAPSIZE * MAPSIZE * 0.04;// 배를 최대로 만들 수 있는 수를 어떻게 해야할까?
		unit_max = 5;//TEST 코드에서는 5대를 최대 보유수로 함
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				map[i][j] = 0;
			}
		}
		//vector 초기화
		ship_index = ship_v.begin();//ship_index 초기화
	}
	void makeship(string name, int kind, int health)
	{
		int x, y, c;
		//FILE *pt=fopen("/ships/ship_info.txt","r"); 파일로 읽어오고 싶다 수정하기 편하게
		//ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_)
		if (unit_max > unit_num)
		{
			srand(time(NULL));
			do {
				x = rand() % MAPSIZE;
				Sleep(100);
				y = rand() % MAPSIZE;
				c = rand() % 4;
				cout << x << y<< c<<"배 만들기 시도" << endl;
			} while (map_check(map, x, y, c, health) != 1);
			unit_num++;
			ship s_new(name, kind, x, y, c, health, unit_num);
			ship_v.push_back(s_new);
			unit_index = unit_num;//unit_index 변수는 아직 무슨 역할에 넣을지 모름
			cout << unit_num << " 번째 배를 생성했습니다." << endl;
			drawship(s_new);
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
				else if(map[y][x] ==1)
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
		int n =1;
		string tmp;
		//vector에 있는 정보들 출력
		for (ship_index=ship_v.begin();ship_index != ship_v.end();ship_index++)
		{
			tmp = ship_index->getname();
			cout << n << "번째 함선 : :" << tmp << endl;
			cout << "체력 : " << ship_index->gethealth()<< endl;
			cout << "위치 : " << ship_index->getx() << ship_index->gety() << ship_index->getcompass() << endl;
		}
		ship_index = ship_v.begin();
	}
	int userinput(int input)
	{

	}
	int move(int direction, ship s)
	{
		int compass = s.getcompass();
		int x = s.getx();
		int y = s.gety();
		int dp = s.getdo_point();
		int mp = s.getmove_point();
		if (dp > 0) {
			if (direction == 0)//좌회전
			{
				compass--;
				if (compass < 0)
				{
					compass = 4;
				}
			}
			else if (direction == 1)//직진
			{
				if (compass == 0)
				{
					y-=mp;
				}
				else if (compass == 1)
				{
					x+=mp;
				}
				else if (compass == 2)
				{
					y+=mp;
				}
				else
				{
					x-=mp;
				}
			}
			else if (direction == 2)//우회전
			{
				compass++;
				if (compass > 4)
				{
					compass = 0;
				}
			}
			else
			{
				cout << "방향 오류" << endl;
				return 0;
			}
			if (map_check(map, x, y, compass, s.getblock()) == 1)
			{
				cout << "배를 " << x << y << compass << " 로 이동시켰습니다." << endl;
				s.move_ship(direction);
				return 1;
			}
			else
			{
				cout << "배를 해당 위치에 표시할 수 없습니다." << endl;
				return 0;
			}
		}
		else
		{
			cout << "배의 행동력을 다 사용했습니다." << endl;
		}
	}
	int attack(int x, int y, player p)
	{
		cout << "공격할 좌표를 입력하시오 : ";
		do {
			cin >> x;
			cin >> y;
		} while (x < MAPSIZE && y < MAPSIZE);
		if (p.map[y][x] != 0)
		{

		}
		else
		{
			cout << "miss" << endl;
		}
	}
};
void gamestart()
{

}
int main()
{
	player p1(1);
	player p2(1);
	p1.makeship("항공모함",1,5);
	p1.makeship("전함", 2, 4);
	p1.makeship("전함", 2, 4);
	p1.showmap();
	p1.showship();

	p2.makeship("항공모함", 1, 5);
	p2.makeship("전함", 2, 4);
	p2.showmap();
	p2.showship();


	system("pause");
	return 0;
}