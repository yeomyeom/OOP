#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>
using namespace std;
#define MAPSIZE 10//�� ����� ���� ���ϴ´�� �ٲٸ� ������ ��� 2���� �迭���� ���� ���� ��� ��������� �ϳ�;;;

int map_check(int m[][MAPSIZE], int x, int y, int c, int blocks)
{
	int tmp = 0;
	if (c == 0)//����
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
	else if (c == 1)//����
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
	else if (c == 2)//����
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
	else//����
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
	string name;//���� ���簡 �ƴ϶�� char������ �ٲ� ����
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
	/////������///////
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
	//////get�Լ���//////
	int shoot(int xpos, int ypos)
	{

	}
	int hit()//���ڰ� �� �ʿ����� �𸣰���
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
	int unit_max;//�ִ�� ���� �� �ִ� ���� ��
	int unit_num;//���� ������ �ִ� ���� ��
	int unit_index;//iterator ���
	int map[MAPSIZE][MAPSIZE];//player ������ ��
public:
	player(int id_) : id(id_), unit_num(1), unit_index(0){
		//vector �ʱ�ȭ
		//ship_index �ʱ�ȭ
		//unit_max = MAPSIZE * MAPSIZE * 0.04;// �踦 �ִ�� ���� �� �ִ� ���� ��� �ؾ��ұ�?

		unit_max = 5;//TEST �ڵ忡���� 8�밡 �ִ�� �սô�.
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
		//FILE *pt=fopen("/ships/ship_info.txt","r"); ���Ϸ� �о���� �ʹ� �����ϱ� ���ϰ�
		//ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_)
		if (unit_max >= unit_num)
		{
			srand(time(NULL));
			do {
				x = rand() % MAPSIZE;
				Sleep(100);
				y = rand() % MAPSIZE;
				c = rand() % 4;
				cout << x << y<< c<<"�� ����� �õ�" << endl;
			} while (map_check(map, x, y, c, health) != 1);
			ship s_new(name, kind, x, y, c, health, unit_num);
			unit_num++;
			unit_index = unit_num;
			cout << unit_num << " ��° �踦 �����߽��ϴ�." << endl;
			//ship s(s_new);
			//ship_v.insert(s_new);
			drawship(s_new);
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
					cout << "��";
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
					cout << "��";
				}
			}
			cout << "" << endl;
		}
	}
	/*int showship()
	{
		//vector�� �ִ� ������ ���
		
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
	p1.makeship("�װ�����",1,5);
	p1.makeship("����", 2, 4);
	p1.makeship("����", 2, 4);
	p1.showmap();

	p2.makeship("�װ�����", 1, 5);
	p2.makeship("����", 2, 4);
	p2.makeship("����", 2, 4);
	p2.makeship("����", 2, 4);
	p2.makeship("����", 2, 4);
	p2.makeship("����", 2, 4);//���⼭ ������ ���ܾ� ���ٵ�
	p2.makeship("����", 2, 4);
	p2.makeship("����", 2, 4);
	p2.makeship("����", 2, 4);
	p2.showmap();

	system("pause");
	return 0;
}