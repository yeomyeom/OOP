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
class othermap {
public:
	int other_map[MAPSIZE][MAPSIZE];
	othermap() {
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
};
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
				compass = 3;
			}
		}
		else if (direction == 1)//����
		{
			if (compass == 0)
			{
				y-=move_point;
			}
			else if (compass == 1)
			{
				x+= move_point;
			}
			else if (compass == 2)
			{
				y+= move_point;
			}
			else
			{
				x-= move_point;
			}
		}
		else//��ȸ��
		{
			compass++;
			if (compass >= 4)
			{
				compass = 0;
			}
		}
	}
};

class player {
private:
	int id;
	int unit_max;//�ִ�� ���� �� �ִ� ���� ��
	int unit_num;//���� ������ �ִ� ���� ��
	//int unit_index;//iterator ���//unit_index ������ unit_num�� ������ ���� �𸣰���
	int map[MAPSIZE][MAPSIZE];//player ������ ��
	int bot_num;
public:
	vector<ship> ship_v;
	vector<ship>::iterator ship_index;
	vector<othermap> othermap_v;//��� �÷��̾� ���� ������ �̱��̶�� �������� �ɼ���
	vector<othermap>::iterator othermap_index;
	//unit_index(0)
	player(int id_, int bot_num_) : id(id_), bot_num(bot_num_), unit_num(0){
		//unit_max = MAPSIZE * MAPSIZE * 0.04;// �踦 �ִ�� ���� �� �ִ� ���� ��� �ؾ��ұ�?
		unit_max = 4;//TEST �ڵ忡���� 4�븦 �ִ� �������� ��
		for (int i = 0;i < MAPSIZE;i++)
		{
			for (int j = 0;j < MAPSIZE;j++)
			{
				map[i][j] = 0;
			}
		}
		for (int i = 0;i < bot_num;i++)
		{
			othermap m;
			othermap_v.push_back(m);
		}
		ship_index = ship_v.begin();//ship_index �ʱ�ȭ
		othermap_index = othermap_v.begin();
	}
	/*player(const player &c):id(c.id),unit_max(c.unit_max),unit_num(c.unit_num),unit_index(c.unit_index),bot_num(c.bot_num)
	{
		//copy constructer ���� ���߿� �ʿ�������....
	}*/
	//////������////////
	int get_unitmax()
	{
		return unit_max;
	}
	void makeship(string name, int kind, int health)
	{
		int x, y, c;
		//FILE *pt=fopen("/ships/ship_info.txt","r"); ���Ϸ� �о���� �ʹ� �����ϱ� ���ϰ�
		if (unit_max > unit_num)
		{
			srand(time(NULL));
			do {
				x = rand() % MAPSIZE;
				Sleep(100);
				y = rand() % MAPSIZE;
				Sleep(100);
				c = rand() % 4;
				cout << x << y<< c<<"�� ����� �õ�" << endl;
			} while (map_check(map, x, y, c, health) != 1);
			unit_num++;
			ship s_new(name, kind, x, y, c, health, unit_num);
			ship_v.push_back(s_new);
			//unit_index = unit_num;//unit_index ������ ���� ���� ���ҿ� ������ ��
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
		cout << "���� " << index << "��° ship �Դϴ�." << endl;
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
		for (int a = 0;a < bot_num;a++)
		{
			for (y = 0;y < MAPSIZE;y++)
			{
				for (x = 0;x < MAPSIZE;x++)
				{
					if (othermap_v[a].other_map[y][x] == 0)
					{
						cout << "��";
					}
					else
					{
						cout << " H";
					}
				}
				cout << "" << endl;
			}
		}
		cout << "===========================================" << endl;
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
		//vector�� �ִ� ������ ���
		cout << ship_index->getindex()<< "��° �Լ� : " << ship_index->getname() << endl;
		cout << "ü�� : " << ship_index->gethealth()<< endl;
		cout << "��ġ : " << ship_index->getx() << ship_index->gety() << ship_index->getcompass() << endl;
	}
	int userinput(int input)
	{

	}
	void erasemap(int index)//move �Լ��� ���� move ���� ship�� ���� �ܻ��� map�� ���� �־ �浹������ �� �׷��� �̵� ���� �� �ܻ���� ����� �۾� �ʿ�
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
			if (direction == 0)//��ȸ��
			{
				compass--;
				if (compass < 0)
				{
					compass = 3;
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
				if (compass >= 4)
				{
					compass = 0;
				}
			}
			else
			{
				cout << "���� ����" << endl;
				return 0;
			}
			if (map_check(map, x, y, compass, s.getblock()) == 1)//�̰� Ȯ���ϱ� ���� �� ������ �������� �����Ҷ� �̹� �ش� ĭ�� ���ڰ� �� �־(�̵� ���� ��) �浹 ���� �� 
			{
				cout << s.getindex()<<" �踦 " << x << y << compass << " �� �̵����׽��ϴ�." << endl;
				s.move_ship(direction);
				ship_v[s.getindex()-1] = s;//�ٲ� ship�� ��ġ ������ �����Ѵ�.�� �̰� -1 ���ؼ� �������ſ��� GG
				initmap();
				for (int i = 0; i < unit_max;i++)
				{
					drawship(ship_v[i]);
				}
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
	void attack(int x, int y, player p)
	{
		do {
			cout << "������ ��ǥ�� �Է��Ͻÿ� : ";
			cin >> x;
			cin >> y;
		} while (x < MAPSIZE && y < MAPSIZE && x>=0 && y>=0);

	}
	int hit(int x, int y, int kind)
	{

	}
};
void gamestart_single()
{
	int turn = 0;
	int input;
	int bot;
	cout << "Single playe" << endl;
	cout << "Map Size "<<MAPSIZE << endl;
	cout << "How many bots? : ";
	cin >> bot;
	cout << "" << endl;
	cout << bot << " ���� ���� ���� �߽��ϴ�." << endl;
	//const int bots = bot;
	//player p[bots];
	vector<player> p_v;
	vector<player>::iterator p_index;
	int who = 0;

	for (int i = 0;i <= bot;i++)
	{
		player p(i,bot);
		p_v.push_back(p);
		for (int j = 0;j < p_v[i].get_unitmax();j++)
		{
			p_v[i].makeship("����", 2, 4);//���߿� ship ��ӹ��� ship_�װ�����, ship_����, ship_�������� �� �ڸ�
		}
	}
	while (turn < 50)
	{
		for (p_index=p_v.begin();p_index != p_v.end();p_index++) //��� �÷��̾ �Ϸ��Ҷ����� �ݺ�
		{
			who = turn % (bot + 1);
			for (p_index->ship_index = p_index->ship_v.begin();p_index->ship_index != p_index->ship_v.end();p_index->ship_index++) //�÷��̾ ������ �ִ� ��� ����� ������ �Ϸ�ɶ����� �ݺ�
			{
				p_index->showmap();
				p_index->showship();
				cout << "��� ������ �� ���Դϱ�? 1 : ����  2. �̵�  �ٸ���. ���� ����" << endl;
				cin >> input;
				if (input == 1)
				{
					//cout << "x y�� �Է��� �ֽʽÿ�" << endl;
					//p_index->attack(); //����� ����
				}
				else if(input == 2)
				{
					do {
						cout << p_index->ship_index->getmove_point() << " ��ŭ 0 : ��ȸ�� 1 :���� 2 : ��ȸ��" << endl;
						cin >> input;
					} while (input != 0 && input != 1 && input != 2);
					if (p_index->move(input, *(p_index->ship_index)) == 1)
					{
						cout << "�̵��߽��ϴ�." << endl;
					}
					else
					{
						cout << "���� �̻��մϴ�." << endl;
					}
					/*if(p_index->move(input, p_index->ship_v[s_index])==1)//�̰� �����۵������� �𸣰ڳ�
					{
						cout<<"�̵��߽��ϴ�."<<endl;
					}
					else
					{
						cout << "���� �̻��մϴ�." << endl;
					}*/
				}
				else
				{
					return;//���� ����
				}
				//system("cls");
			}
		}
		turn++;
	}
	//4. �ݺ�����
	//   1. ship vector�� 1��° �ִ� �踦 ������ ���ΰ� ������ ���ΰ�
	//   2. �����̸� ����(0�� 1���� 2��), �����Ҳ��� ���� ��ġ�� ������ �÷��̾�(x,y, player)
	//   3. �ൿ�� ��������(do_point ==0) ���� ship vector�� 2��° �ִ� ship ��ü�� �Ѿ
	//   4. ship vector�� �ִ� ��� ship���� �ൿ�� ������ �� ���� �ִ� map�� othermap_v�� ������
	//4. �ݺ�����(��Ƽ)
}
/*void gamestart_multi()
{
	int p1[MAPSIZE][MAPSIZE];
	int p2[MAPSIZE][MAPSIZE];
	//1. ��Ƽ�÷���
	//2. ��Ƽ�� 1:1
	//3. �÷��̾� ������ id ������������ ������
	//4. �ݺ�����
}*/
int main()
{
	/*player p1(1);
	player p2(1);
	p1.makeship("�װ�����",1,5);
	p1.makeship("����", 2, 4);
	p1.makeship("����", 2, 4);
	p1.showmap();
	p1.showship();

	p2.makeship("�װ�����", 1, 5);
	p2.makeship("����", 2, 4);
	p2.showmap();
	p2.showship();*/
	gamestart_single();

	system("pause");
	return 0;
}