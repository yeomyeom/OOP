#include <iostream>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>
using namespace std;
#define MAPSIZE 10//�� ����� ���� ���ϴ´�� �ٲٸ� ������ ��� 2���� �迭���� ���� ���� ��� ��������� �ϳ�;;;

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
		//vector�� �����Ҷ� �� ������ copy constructure
		//ship temp = 
	}*/
	int move(int wheres)
	{
		if (wheres == 1)
		{
			//left �׹��⿡ map�� ����ִ°� Ȯ���ϴ� ���� �ʿ�
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
	int hit()//���ڰ� �� �ʿ����� �𸣰���
	{
		health--;
	}
};

class player {
	int id;
	vector<ship> ship_v;
	vector<ship>::iterator ship_index;
	int map[MAPSIZE][MAPSIZE];//player ������ ��
	player(int id) {
		//vector �ʱ�ȭ
		//ship_index �ʱ�ȭ
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
		//vector�� �ִ� ������ ���
	}
	
};

int main()
{

	return 0;
}