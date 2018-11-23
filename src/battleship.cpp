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
				compass = 3;
			}
		}
		else if (direction == 1)//직진
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
		else//우회전
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
	int unit_max;//최대로 가질 수 있는 배의 수
	int unit_num;//현재 가지고 있는 배의 수
	//int unit_index;//iterator 기능//unit_index 변수는 unit_num과 같은데 아직 모르겠음
	int map[MAPSIZE][MAPSIZE];//player 본인의 맵
	int bot_num;
public:
	vector<ship> ship_v;
	vector<ship>::iterator ship_index;
	vector<othermap> othermap_v;//모든 플레이어 맵을 저장함 싱글이라면 여러개가 될수도
	vector<othermap>::iterator othermap_index;
	//unit_index(0)
	player(int id_, int bot_num_) : id(id_), bot_num(bot_num_), unit_num(0){
		//unit_max = MAPSIZE * MAPSIZE * 0.04;// 배를 최대로 만들 수 있는 수를 어떻게 해야할까?
		unit_max = 4;//TEST 코드에서는 4대를 최대 보유수로 함
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
		ship_index = ship_v.begin();//ship_index 초기화
		othermap_index = othermap_v.begin();
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
	void makeship(string name, int kind, int health)
	{
		int x, y, c;
		//FILE *pt=fopen("/ships/ship_info.txt","r"); 파일로 읽어오고 싶다 수정하기 편하게
		if (unit_max > unit_num)
		{
			srand(time(NULL));
			do {
				x = rand() % MAPSIZE;
				Sleep(100);
				y = rand() % MAPSIZE;
				Sleep(100);
				c = rand() % 4;
				cout << x << y<< c<<"배 만들기 시도" << endl;
			} while (map_check(map, x, y, c, health) != 1);
			unit_num++;
			ship s_new(name, kind, x, y, c, health, unit_num);
			ship_v.push_back(s_new);
			//unit_index = unit_num;//unit_index 변수는 아직 무슨 역할에 넣을지 모름
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
		cout << "나는 " << index << "번째 ship 입니다." << endl;
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
						cout << "□";
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
		//vector에 있는 정보들 출력
		cout << ship_index->getindex()<< "번째 함선 : " << ship_index->getname() << endl;
		cout << "체력 : " << ship_index->gethealth()<< endl;
		cout << "위치 : " << ship_index->getx() << ship_index->gety() << ship_index->getcompass() << endl;
	}
	int userinput(int input)
	{

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
				cout << s.getindex()<<" 배를 " << x << y << compass << " 로 이동시켰습니다." << endl;
				s.move_ship(direction);
				ship_v[s.getindex()-1] = s;//바뀐 ship의 위치 정보를 갱신한다.와 이거 -1 안해서 오류난거였네 GG
				initmap();
				for (int i = 0; i < unit_max;i++)
				{
					drawship(ship_v[i]);
				}
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
	void attack(int x, int y, player p)
	{
		do {
			cout << "공격할 좌표를 입력하시오 : ";
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
	cout << bot << " 개의 봇을 생성 했습니다." << endl;
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
			p_v[i].makeship("전함", 2, 4);//나중에 ship 상속받은 ship_항공모함, ship_전함, ship_구축함이 들어갈 자리
		}
	}
	while (turn < 50)
	{
		for (p_index=p_v.begin();p_index != p_v.end();p_index++) //모든 플레이어가 완료할때까지 반복
		{
			who = turn % (bot + 1);
			for (p_index->ship_index = p_index->ship_v.begin();p_index->ship_index != p_index->ship_v.end();p_index->ship_index++) //플래이어가 가지고 있는 모든 배들의 조종이 완료될때까지 반복
			{
				p_index->showmap();
				p_index->showship();
				cout << "어느 동작을 할 것입니까? 1 : 공격  2. 이동  다른값. 강제 종료" << endl;
				cin >> input;
				if (input == 1)
				{
					//cout << "x y를 입력해 주십시오" << endl;
					//p_index->attack(); //여기는 아직
				}
				else if(input == 2)
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
						cout << "값이 이상합니다." << endl;
					}
					/*if(p_index->move(input, p_index->ship_v[s_index])==1)//이게 정상작동할지는 모르겠네
					{
						cout<<"이동했습니다."<<endl;
					}
					else
					{
						cout << "값이 이상합니다." << endl;
					}*/
				}
				else
				{
					return;//강제 종료
				}
				//system("cls");
			}
		}
		turn++;
	}
	//4. 반복시작
	//   1. ship vector에 1번째 있는 배를 움직일 것인가 공격할 것인가
	//   2. 움직이면 방향(0왼 1직진 2오), 공격할꺼면 공격 위치와 공격할 플레이어(x,y, player)
	//   3. 행동을 마쳤으면(do_point ==0) 다음 ship vector에 2번째 있는 ship 객체로 넘어감
	//   4. ship vector에 있는 모든 ship들의 행동을 결정한 후 현재 있는 map을 othermap_v에 복사함
	//4. 반복시작(멀티)
}
/*void gamestart_multi()
{
	int p1[MAPSIZE][MAPSIZE];
	int p2[MAPSIZE][MAPSIZE];
	//1. 멀티플레이
	//2. 멀티는 1:1
	//3. 플레이어 순서는 id 오름차순으로 정해짐
	//4. 반복시작
}*/
int main()
{
	/*player p1(1);
	player p2(1);
	p1.makeship("항공모함",1,5);
	p1.makeship("전함", 2, 4);
	p1.makeship("전함", 2, 4);
	p1.showmap();
	p1.showship();

	p2.makeship("항공모함", 1, 5);
	p2.makeship("전함", 2, 4);
	p2.showmap();
	p2.showship();*/
	gamestart_single();

	system("pause");
	return 0;
}