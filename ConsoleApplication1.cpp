// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include<cmath>
#include <ctime>
#include<cstdlib>


using namespace std;


class Creature
{
public:

	friend void fightMonster();

	Creature()
	{
		this->name = "No name";
		this->symbol = '0';
		this->health = 0;
		this->damage = 0;
		this->gold = 0;
	}

	Creature(string name,char symbol,int health,int damage,int gold)
	{
		this->name = name;
		this->symbol = symbol;
		this->health = health;
		this->damage = damage;
		this->gold = gold;
	}

	string getName() { return name; }
	char getSymbol() { return symbol; }
	int getHealth() { return health; }
	int getDamage() { return damage; }
	int getGold() { return gold; }

	string enterName()
	{
		cout<<  "Enter you name " << endl;
		string ename;
		cin >> ename;
		cout << "Welcome " << ename << "! " << endl
			<< "You have " << health << " health and are carrying "
			<< gold << " gold.";

		return ename;
	}

	void reduceHealth(int health)
	{
		this->health = this->health - health;
	}

	bool isDead() {return this->health <= 0;}

	void addGold(int gold)
	{
		this->gold = this->gold + gold;
	}
	void damageUp()
	{
		this->damage = this->damage + 1;
	}

private:
	string name;
	char symbol;
	int health;
	int damage;
	int gold;
};

class Player: public Creature
{
public:
	Player() :Creature("No name", '@',10, 1, 0)
	{
		enterName();
	}

	unsigned int getLevel()
	{
		return level;
	}

	void levelUp()
	{
		this->level++;
	}

	bool hasWon()
	{
		return this->level >= 20;
	}
	

private:
	unsigned int level;

};

class Monster : public Creature
{
public:
	enum Type
	{
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};

	Monster(Type type):Creature(monsterData[type].name, monsterData[type].symbol, monsterData[type].health, monsterData[type].damage, monsterData[type].gold)
	{
	}

 	static Type getRandomMonster()
	{
		int r =(static_cast<int>(MAX_TYPES));
		int t = rand() % r;
		return static_cast<Type>(t);
	}

	struct MonsterData
	{
		string name;
		char symbol;
		int health;
		int damage;
		int gold;
	};
	static MonsterData monsterData[];
	
private:
	
};

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
	{ "dragon", 'D', 20, 4, 100 },
	{ "orc", 'o', 4, 2, 25 },
	{ "slime", 's', 1, 1, 10 }
};



void attackMonster(Player& player, Monster& monster)
{
	monster.reduceHealth(player.getDamage());
	if (monster.isDead())
	{
		player.levelUp();
		player.addGold(monster.getGold());
		player.damageUp();
		cout << "Monster is dead!"<<endl;
	}
	else
	{
		attackPlayer(player,monster);
	}
}

void attackPlayer(Player &player, Monster &monster)
{
	player.reduceHealth(monster.getDamage());
}

void fightMonster(Player &player, Monster &monster)
{

		while (true)
		{
			cout << "(r)un or (f)ight:";
			char x;
			cin >> x;
			if (x == 'r')
			{
				int r = rand() % 2;
				if (r)
				{
					break;
				}
				else
				{
					attackPlayer(player,monster);
				}
			}
			if (x == 'f')
			{
				attackMonster(player, monster);
			}
		}

}

int main()
{
	Player player;

	while (!player.isDead()||!player.hasWon())
	{
		Monster monster = Monster::getRandomMonster();
		cout << endl << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ")." << endl << endl;
		fightMonster(player, monster);

	}
		
	if (player.isDead())
	{
		cout << "You have " << player.getHealth() << " health and are carrying "
			<< player.getGold() << " gold." << endl;
		cout << "You is dead" << endl;
	}
	if (player.hasWon())
	{
		cout << "You have " << player.getHealth() << " health and are carrying "
			<< player.getGold() << " gold." << endl;
		cout << "You is win" << endl << endl;
	}

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
