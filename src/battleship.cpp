#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>
#include <string>
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
	int do_point;
	int move_point;
public:
	ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_) :kind(kind_), x(x_), y(y_), compass(compass_), health(health_), block(health_), index(index_), move_point(1), do_point(1) {
		name = name_;
		//mapsize�� ���� unit(��ship) ������ �����ǰ� unit ĭ��=health(ü��) unit ĭ���� ����ؼ� move_point�� ���ݷ��� ������
	}
	ship(const ship& c) : kind(c.kind),x(c.x),y(c.y),compass(c.compass),health(c.health),block(c.block),index(c.index), do_point(c.do_point),move_point(c.move_point){
		name = c.name;
	}
	/////������///////
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
	//////get�Լ���//////
	int shoot(int xpos, int ypos)
	{
		int attack = health;//
	}
	int hit()//���ڰ� �� �ʿ����� �𸣰���
	{
		health--;
		//move_point--;
	}
	void move_ship(int direction)
	{
		if (direction == 0)//��ȸ��
		{
			compass--;
			if (compass < 0)
			{
				compass = 4;
			}
		}
		else if (direction == 1)//����
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
		else//��ȸ��
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
	int unit_max;//�ִ�� ���� �� �ִ� ���� ��
	int unit_num;//���� ������ �ִ� ���� ��
	int unit_index;//iterator ���//unit_index ������ unit_num�� ������ ���� �𸣰���
	int map[MAPSIZE][MAPSIZE];//player ������ ��
public:
	player(int id_) : id(id_), unit_num(0), unit_index(0){
		//unit_max = MAPSIZE * MAPSIZE * 0.04;// �踦 �ִ�� ���� �� �ִ� ���� ��� �ؾ��ұ�?
		unit_max = 5;//TEST �ڵ忡���� 5�븦 �ִ� �������� ��
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				map[i][j] = 0;
			}
		}
		//vector �ʱ�ȭ
		ship_index = ship_v.begin();//ship_index �ʱ�ȭ
	}
	void makeship(string name, int kind, int health)
	{
		int x, y, c;
		//FILE *pt=fopen("/ships/ship_info.txt","r"); ���Ϸ� �о���� �ʹ� �����ϱ� ���ϰ�
		//ship(string name_, int kind_, int x_, int y_, int compass_, int health_, int index_)
		if (unit_max > unit_num)
		{
			srand(time(NULL));
			do {
				x = rand() % MAPSIZE;
				Sleep(100);
				y = rand() % MAPSIZE;
				c = rand() % 4;
				cout << x << y<< c<<"�� ����� �õ�" << endl;
			} while (map_check(map, x, y, c, health) != 1);
			unit_num++;
			ship s_new(name, kind, x, y, c, health, unit_num);
			ship_v.push_back(s_new);
			unit_index = unit_num;//unit_index ������ ���� ���� ���ҿ� ������ ��
			cout << unit_num << " ��° �踦 �����߽��ϴ�." << endl;
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
	void showship()
	{
		int n =1;
		string tmp;
		//vector�� �ִ� ������ ���
		for (ship_index=ship_v.begin();ship_index != ship_v.end();ship_index++)
		{
			tmp = ship_index->getname();
			cout << n << "��° �Լ� : :" << tmp << endl;
			cout << "ü�� : " << ship_index->gethealth()<< endl;
			cout << "��ġ : " << ship_index->getx() << ship_index->gety() << ship_index->getcompass() << endl;
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
			if (direction == 0)//��ȸ��
			{
				compass--;
				if (compass < 0)
				{
					compass = 4;
				}
			}
			else if (direction == 1)//����
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
			else if (direction == 2)//��ȸ��
			{
				compass++;
				if (compass > 4)
				{
					compass = 0;
				}
			}
			else
			{
				cout << "���� ����" << endl;
				return 0;
			}
			if (map_check(map, x, y, compass, s.getblock()) == 1)
			{
				cout << "�踦 " << x << y << compass << " �� �̵����׽��ϴ�." << endl;
				s.move_ship(direction);
				return 1;
			}
			else
			{
				cout << "�踦 �ش� ��ġ�� ǥ���� �� �����ϴ�." << endl;
				return 0;
			}
		}
		else
		{
			cout << "���� �ൿ���� �� ����߽��ϴ�." << endl;
		}
	}
	int attack(int x, int y, player p)
	{
		cout << "������ ��ǥ�� �Է��Ͻÿ� : ";
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
	p1.makeship("�װ�����",1,5);
	p1.makeship("����", 2, 4);
	p1.makeship("����", 2, 4);
	p1.showmap();
	p1.showship();

	p2.makeship("�װ�����", 1, 5);
	p2.makeship("����", 2, 4);
	p2.showmap();
	p2.showship();


	system("pause");
	return 0;
}