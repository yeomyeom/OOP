#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>
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
	int move_point;
public:
	ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_) :kind(kind_), x(x_), y(y_), compass(compass_), health(health_), block(health_), index(index_), move_point(1) {
		name = name_;
	}
	/*ship(const ship& copy) : {
		//vector에 복사할때 쓸 예정인 copy constructure
		//ship temp =
	}*/
	int move(int wheres)
	{
		if (wheres == 1)
		{
			//left 그방향에 map이 비어있는가 확인하는 절차 필요
		}
		else if (wheres == 2)
		{
			//right
		}
		else
		{
			//forward
		}
	}
	/////생성자///////
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
	//////get함수들//////
	int shoot(int xpos, int ypos)
	{

	}
	int hit()//인자가 뭐 필요한지 모르겠음
	{
		health--;
		move_point--;
	}
};

class player {
private:
	int id;
	//vector<ship> ship_v;
	//vector<ship>::iterator ship_index;
	int unit_max;//최대로 가질 수 있는 배의 수
	int unit_num;//현재 가지고 있는 배의 수
	int unit_index;//iterator 기능
	int map[MAPSIZE][MAPSIZE];//player 본인의 맵
public:
	player(int id_) : id(id_), unit_num(1), unit_index(0){
		//vector 초기화
		//ship_index 초기화
		//unit_max = MAPSIZE * MAPSIZE * 0.04;// 배를 최대로 만들 수 있는 수를 어떻게 해야할까?

		unit_max = 5;//TEST 코드에서는 8대가 최대로 합시다.
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				map[i][j] = 0;
			}
		}
	}
	void makeship(string name, int kind, int health)
	{
		int x, y, c;
		//FILE *pt=fopen("/ships/ship_info.txt","r"); 파일로 읽어오고 싶다 수정하기 편하게
		//ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_)
		if (unit_max >= unit_num)
		{
			srand(time(NULL));
			do {
				x = rand() % MAPSIZE;
				Sleep(100);
				y = rand() % MAPSIZE;
				c = rand() % 4;
				cout << x << y<< c<<"배 만들기 시도" << endl;
			} while (map_check(map, x, y, c, health) != 1);
			ship s_new(name, kind, x, y, c, health, unit_num);
			unit_num++;
			unit_index = unit_num;
			cout << unit_num << " 번째 배를 생성했습니다." << endl;
			//ship s(s_new);
			//ship_v.insert(s_new);
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
	/*int showship()
	{
		//vector에 있는 정보들 출력
		
	}
	int userinput(int input)
	{

	}
	int move_ship()
	{

	}
	int attack()
	{

	}
	*/
};

int main()
{
	player p1(1);
	player p2(1);
	//makeship(string name, int kind, int health)
	p1.makeship("항공모함",1,5);
	p1.makeship("전함", 2, 4);
	p1.makeship("전함", 2, 4);
	p1.showmap();

	p2.makeship("항공모함", 1, 5);
	p2.makeship("전함", 2, 4);
	p2.makeship("전함", 2, 4);
	p2.makeship("전함", 2, 4);
	p2.makeship("전함", 2, 4);
	p2.makeship("전함", 2, 4);//여기서 문제가 생겨야 할텐데
	p2.makeship("전함", 2, 4);
	p2.makeship("전함", 2, 4);
	p2.makeship("전함", 2, 4);
	p2.showmap();

	system("pause");
	return 0;
}