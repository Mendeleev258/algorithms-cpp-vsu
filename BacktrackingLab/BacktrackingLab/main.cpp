#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <list>


struct Domino
{
	short l, r;

	Domino(short l, short r) : l(l), r(r) {}

	bool operator==(const Domino& other) const
	{
		return (l == other.l && r == other.r) || (l == other.r && r == other.l);
	}

    bool operator<(const Domino& other) const
    {
		if (l != other.l)
			return l < other.l;
		return r < other.r;
    }
	void print() const
	{
		std::cout << "[ " << l << " | " << r << " ]";
	}
};


class Bazar
{
private:
	std::set<Domino> set;

public:
	Bazar()
	{
		for (short i = 0; i <= 6; ++i)
			for (short j = i; j <= 6; ++j)
				set.insert(Domino(i, j));
	}

	void print() const
	{
		for (const Domino& d : set)
		{
			d.print();
			std::cout << '\n';
		}
		std::cout << '\n';
	}

	bool erase(const Domino& d)
	{
		bool res{ false };
		auto it = set.find(d);
		if (it != set.end())
		{
			set.erase(it);
			res = true;
		}
		return res;
	}
};

struct Player
{
	std::set<Domino> set;

	Player() {}

	void print() const
	{
		for (const auto& d : set)
		{
			d.print();
			std::cout << '\n';
		}
		std::cout << '\n';
	}
};

void first_distribute(Player& p1, Player& p2, Bazar& bazar)
{
	short l{}, r{};
	while (p1.set.size() != 7)
	{
		l = rand() % 6;
		r = l + rand() % (6 - l);
		if (bazar.erase(Domino(l, r)))
			p1.set.insert(Domino(l, r));
	}
	while (p2.set.size() != 7)
	{
		l = rand() % 6;
		r = l + rand() % (6 - l);
		if (bazar.erase(Domino(l, r)))
			p2.set.insert(Domino(l, r));
	}
}

bool canPlay(const Domino& bone, const std::list<Domino>& chain, bool toLeft) 
{
	bool res{};

	if (chain.empty())
		res = true;

	if (toLeft) 
		res = bone.r == chain.front().l || bone.l == chain.front().l;
	else
		res = bone.l == chain.back().r || bone.r == chain.back().r;

	return res;
}

bool isFish(const std::list<Domino>& chain, const Player& p1, const Player& p2)
{
	bool result = false;

	// Проверка, что у игрока есть ход
	auto playerCanPlay = [&](const Player& player) 
		{
		bool canMove = false;
		while (canMove != true)
		{
			auto bone = player.set.begin();
			if (canPlay(*bone, chain, true) || canPlay(*bone, chain, false)) // сыграть слева или справа
				canMove = true;
			bone++;
		}
		return canMove;
		};

	if (!chain.empty()) 
	{
		bool p1CanPlay = playerCanPlay(p1);
		bool p2CanPlay = playerCanPlay(p2);

		// Рыба, т.е. когда у обоих есть кости, но никто не может ходить
		result = !p1.set.empty() && !p2.set.empty() && !p1CanPlay && !p2CanPlay;
	}

	return result;
}

bool isPlayer1First(const Player & p1, const Player & p2)
{
	auto findHighestDouble = [](const Player& player)
		{
			int value{ 6 };
			int res{ -1 };
			while (value >= 0 && res == -1)
			{
				Domino d(value, value);
				if (player.set.count(d) > 0)
					res = value;
				value--;
			}
			return res;
		};

	int p1Double = findHighestDouble(p1);
	int p2Double = findHighestDouble(p2);

	bool res;
	if (p1Double > p2Double)
		res = true;
	else if (p2Double > p1Double)
		res = false;
	else
		res = true; // если нельзя определить, по умолчанию ходит первый

	return res;
}



int main()
{
	srand(time(NULL));
	Bazar bazar;
	bazar.print();
	std::cout << "\ndistributing\n";
	Player p1, p2;
	first_distribute(p1, p2, bazar);
	std::cout << "Player 1:\n";
	p1.print();
	std::cout << "Player 2:\n";
	p2.print();
	std::cout << "Bazar:\n";
	bazar.print();
	std::cout << "Player1 is first: " << std::boolalpha << isPlayer1First(p1, p2) << '\n';
}