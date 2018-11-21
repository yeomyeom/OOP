#include <iostream>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>
using namespace std;
#define MAPSIZE 10//맵 사이즈를 내가 원하는대로 바꾸면 좋은데 계속 2차원 배열에서 변수 말고 상수 집어넣으라 하네;;;

class ship {
	string name;
	int kind;
	int x, y;
	int compass;
	int health;
	int block;
	int index;
	int move_point;
	ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_):name(name_),kind(kind_),x(x_),y(y_),compass(compass_), health(health_), block(health_), index(index_), move_point(1) {}
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
	int shoot(int xpos, int ypos)
	{

	}
	int hit()//인자가 뭐 필요한지 모르겠음
	{
		health--;
	}
};

class player {
	int id;
	vector<ship> ship_v;
	vector<ship>::iterator ship_index;
	int map[MAPSIZE][MAPSIZE];//player 본인의 맵
	player(int id) {
		//vector 초기화
		//ship_index 초기화
	}
	int makeship()
	{
		FILE *pt=fopen("/ships/ship_info.txt","r");
		//ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_)

	}
	int initalmap()
	{

	}
	int userinput(int input)
	{

	}
	int show_ship()
	{
		//vector에 있는 정보들 출력
	}
	
};

int main()
{

	return 0;
}