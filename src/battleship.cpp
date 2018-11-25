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
					cout << "��";
				}
				else
				{
					cout << "��";
				}				
			}
			cout <<"" <<endl;
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
	int hit()//���ڰ� �� �ʿ����� �𸣰���
	{
		health=health - 1;
		cout << name<<" �ǰ� ����" << endl;
		cout << "ü�� : " << health << endl;
		if (health == 0)
		{
			block = 0;
			cout << name << " ��ħ" << endl;
			return 0;//�� ��ħ
		}
		//move_point--;
		return 1;
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
		ship_index = ship_v.begin();//ship_index �ʱ�ȭ
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
		int heal = s.gethealth();
		if (heal <= 0) {//��ħ�Ǹ� �ʿ� �ȱ׸�
			//cout << "��ħ���� ��� �ȱ׸��ϴ�." << endl;
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
				for (int i = 0; i < unit_max;i++)
				{
					drawship(ship_v[i]);
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
	int attack(int x, int y, player *p)//��ǥ, ���� ���ϴ� ��
	{
		int r;

		r=p->p_hit(x, y);
		if (r != 0)
		{
			p->disunitnum();
		}
		/*if (kind == 1)
		{
			p.hit(x, y);
		}
		else if (kind == 2)
		{

		}
		else if (kind == 3)
		{

		}
		else
		{

		}
		*/
		return r;
	}
	int p_hit(int x, int y)
	{
		int i = map[y][x];
		int result;
		if (i == 0)
		{
			cout << x<<" , "<<y<<"�� �ƹ��͵� �����ϴ�." << endl;
		}
		else
		{
			result=ship_v[i - 1].hit();
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
};
void gamestart_single()
{
	int turn = 0;
	int input, p, tmp, xpos, ypos, i;
	int bot;
	int alive;
	cout << "Single playe" << endl;
	cout << "Map Size "<<MAPSIZE << endl;
	cout << "How many bots? : ";
	cin >> bot;
	cout << "" << endl;
	cout << bot << " ���� ���� ���� �߽��ϴ�." << endl;
	alive = bot + 1;
	//const int bots = bot;
	//player p[bots];
	vector<player> p_v;
	vector<player>::iterator p_index;
	vector<othermap> maps_v;//�¾Ҵ��� �ȸ¾Ҵ��� �����ִ� map vector �ٸ������ ��� �͵� �� �� �ִ�.
	vector<othermap> ::iterator maps_index;
	int who = 0;

	for (int i = 0;i <= bot;i++)//0=���� 1~bot = bot����
	{
		player p(i,bot);
		p_v.push_back(p);
		for (int j = 0;j < p_v[i].get_unitmax();j++)
		{
			p_v[i].makeship("����", 2, 4);//���߿� ship ��ӹ��� ship_�װ�����, ship_����, ship_�������� �� �ڸ�
		}
		othermap map;
		maps_v.push_back(map);//������ ��������� �ش� ��ġ�� ������ �ִ��� �˱� ���� �� 2���� �迭
	}
	while (turn < 50)
	{
		if (alive == 1)//�� �Ѹ� ��Ƴ����� �¸�
		{
			cout << "P" << p_index->getid() << " �� �¸��߽��ϴ�." << endl;
			return;
		}
		for (p_index=p_v.begin();p_index != p_v.end();p_index++) //��� �÷��̾ �Ϸ��Ҷ����� �ݺ�
		{
			who = who % (bot + 1);
			if (p_index->ship_v[0].gethealth() <=0)//�й� ���� ù��°(�װ�����) ������ ��ħ�Ǿ�����
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
				for (p_index->ship_index = p_index->ship_v.begin();p_index->ship_index != p_index->ship_v.end();p_index->ship_index++) //�÷��̾ ������ �ִ� ��� ����� ������ �Ϸ�ɶ����� �ݺ�
				{
					p_index->initmap();
					for (tmp = 0;tmp < p_index->get_unitmax();tmp++) {
						p_index->drawship(p_index->ship_v[tmp]);//��ħ���� ��� ���� �ʿ� �׸� ship ��ü�� ������ vector�� ����Ǽ� �����Ϸ��� �տ� �ִ� �ֵ� �� �� ��� �����
					}
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
					if (p_index->ship_index->gethealth() > 0) {//,�谡 ����ִ°�?
						cout << "��� ������ �� ���Դϱ�? 1 : ����  2. �̵�  �ٸ���. ���� ����" << endl;
						cin >> input;
						if (input == 1)
						{
							do {
								cout << "������ �÷��̾��? (�ִ�) " << bot << endl;
								cin >> p;
							} while (p > bot || p < 0);
							do {
								cout << "������ ��ǥ�� �Է��Ͻÿ� : ";
								cin >> xpos;
								cin >> ypos;
							} while ((xpos > MAPSIZE || xpos <0) && (ypos > MAPSIZE || ypos < 0));
							tmp = p_index->attack(xpos, ypos, &p_v[p]); //p��°�� �ִ� �÷��̾� ���� p_v�� 1���� ������ �ƴ϶� 0���� �����̴�.
							if (tmp != 0)
							{
								maps_v[p].other_map[ypos][xpos] = 1;
							}
						}
						else if (input == 2)
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
						}
						else
						{
							return;//���� ����
						}
					}
					else
					{
						cout << "��ħ�� ���Դϴ�." << endl;
					}
					Sleep(1000);
					system("cls");
					cout << "////////////////���� ��//////////////" << endl;
				}
			}
			who++;
			cout << p_index->getid() << " ��° �÷��̾� ���ʰ� ����Ǿ����ϴ�." << endl;
		}
		turn++;
	}
	//50���� ������ ���� ���� �̰������ �ȳ���
	cout << "50���� �Ѿ����ϴ�. ��⸦ �����մϴ�." << endl;


	//4. �ݺ�����
	//   1. ship vector�� 1��° �ִ� �踦 ������ ���ΰ� ������ ���ΰ�
	//   2. �����̸� ����(0�� 1���� 2��), �����Ҳ��� ���� ��ġ�� ������ �÷��̾�(x,y, player)
	//   3. �ൿ�� ��������(do_point ==0) ���� ship vector�� 2��° �ִ� ship ��ü�� �Ѿ
	//   4. ship vector�� �ִ� ��� ship���� �ൿ�� ������ �� ���� �ִ� map�� othermap_v�� ������
	//4. �ݺ�����(��Ƽ)
}
void gamestart_multi()
{
	int turn = 0;
	int input, p, tmp, xpos, ypos, i;
	int bot;
	cout << "multi play" << endl;
	cout << "Map Size " << MAPSIZE << endl;
	cout << "���� ����� �Դϴ�. : ";
	vector<player> p_v;
	vector<player>::iterator p_index;
	vector<othermap> maps_v;//�¾Ҵ��� �ȸ¾Ҵ��� �����ִ� map vector �ٸ������ ��� �͵� �� �� �ִ�.
	vector<othermap> ::iterator maps_index;

	for (int i = 0;i <= 2;i++)//0=���� 1=����
	{
		player p(i, 2);
		p_v.push_back(p);
		for (int j = 0;j < p_v[i].get_unitmax();j++)
		{
			p_v[i].makeship("����", 2, 4);//���߿� ship ��ӹ��� ship_�װ�����, ship_����, ship_�������� �� �ڸ�
		}
		othermap map;
		maps_v.push_back(map);//������ ��������� �ش� ��ġ�� ������ �ִ��� �˱� ���� �� 2���� �迭
	}


	//1. ��Ƽ�÷���
	//2. ��Ƽ�� 1:1
	//3. �÷��̾� ������ id ������������ ������
	//4. �ݺ�����
}
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
	//system("mode con cols=75 lines=60");
	gamestart_single();

	system("pause");
	return 0;
}