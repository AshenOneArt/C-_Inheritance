
#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <algorithm>
#include <typeinfo>
#include <sstream>
#include <Windows.h>
#include <memory>
class Dice
{
public:
	int Roll(int nDice)
	{
		int total = 0;
		for (int n = 0; n < nDice; n++)
		{
			total += d6(rng);
		}
		return total;
	} 
private:
	std::uniform_int_distribution<int> d6 = std::uniform_int_distribution<int>(1, 6);
	std::mt19937 rng = std::mt19937(std::random_device{}());
};

struct Attribution
{
	int hp;
	int speed;
	int power;
};

class Weapon
{
public:
	Weapon(const std::string name, int rank)
		:
		name(name), rank(rank)
	{
	}
	const std::string GetName()const
	{
		return name;
	}
	int GetRank()const
	{
		return rank;
	}
	virtual int ClculateDamage(const Attribution attri,Dice& d) = 0;
	virtual ~Weapon() = default;
private:
	std::string name;
	int rank;
};

class Fists : public Weapon
{
public:
	Fists()
		:
		Weapon( "fists", 0)
	{
	}
	virtual int ClculateDamage(const Attribution attri, Dice& d) override
	{
		return attri.power + d.Roll(2);
	}

};

class Knife : public Weapon
{
public:
	Knife()
		:
		Weapon("Knife", 1)
	{
	}
	int ClculateDamage(const Attribution attri, Dice& d) override
	{
		return attri.power + d.Roll(2);
	}
};

class Bat : public Weapon
{
public:
	Bat()
		:
		Weapon("Bat", 2)
	{
	}
	int ClculateDamage(const Attribution attri, Dice& d) override
	{
		return attri.power + d.Roll(2);
	}
};

class MemeFighter
{
public:
	const std::string& GetName() const
	{
		return name;
	}
	bool isAlive() const
	{
		return attribution.hp > 0;
	}
	int GetInitiative()
	{
		return attribution.speed + Roll(2);
	}
	void Attack(MemeFighter& other) const
	{
		if (this->isAlive() && other.isAlive())
		{
			std::cout << name << " Attacks " << other.name << " with his " << weapon->GetName() << " ! " << std::endl;
		}
		ApplyDamageTo(other, weapon->ClculateDamage(attribution,d));
	}
	virtual void Tick()
	{
		if (this->isAlive())
		{
			const int recovery = Roll();
			std::cout << name << " Recove " << recovery << " HP " << std::endl;
			attribution.hp += recovery;
		}
	}
	virtual void SpecialMove(MemeFighter& other) = 0;
	void GiveWeapon(std::unique_ptr<Weapon> pWeapon)
	{
		weapon = std::move(pWeapon);
	}
	std::unique_ptr<Weapon> PilferWeapon()
	{
		return std::move(weapon);
	}

	
protected:
	MemeFighter(const std::string& _name, int _hp, int _speed, int _power, std::unique_ptr<Weapon> weapon)
		:
		attribution({ _hp, _speed, _power }), name(_name), weapon(std::move(weapon))
	{
		std::cout << name << " Enter the ring!" << std::endl;
	}	
	
	void ApplyDamageTo(MemeFighter& target, int damage) const
	{
		target.attribution.hp -= damage;
		std::cout << target.name << " Takes " << damage << " damage " << std::endl;
		if (!target.isAlive())
		{
			std::cout << target.name << " Is Dead " << std::endl;
		}
	}
	int Roll(int nDice = 1)const
	{
		return d.Roll(nDice);
	}
	
protected:
	Attribution attribution;
	std::string name;
private:
	mutable Dice d;
	std::unique_ptr<Weapon> weapon;
};



class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string& name, std::unique_ptr<Weapon> weapon)
		:
		MemeFighter(name, 69, 7, 14, std::move(weapon))
	{

	}
	void SpecialMove(MemeFighter& other) override
	{
		if (this->isAlive() && other.isAlive())
		{
			std::cout << this->GetName() << " Attacks " << other.GetName() << " with a rainbow beam ! " << std::endl;
			ApplyDamageTo(other, Roll(3) + 20);
		}
		else
		{
			std::cout << " The Game is Over, no more rainbow beam! " << std::endl;
		}
	}
	void Tick() override
	{
		if (this->isAlive())
		{
			MemeFighter::Tick();
			std::cout << name << " is hurt by the bad AIDS ! " << std::endl;
			ApplyDamageTo(*this, Roll());
		}

	}
};

class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name, std::unique_ptr<Weapon> weapon)
		:
		MemeFighter(name, 80, 4, 14, std::move(weapon))
	{

	}
	void SpecialMove(MemeFighter& other) override
	{
		if (this->isAlive())
		{
			if (MemeFrog* fog = dynamic_cast<MemeFrog*>(&other))
			{
				std::cout << " this is frog due !!! " << std::endl;
			}
			if (typeid(other) == typeid(MemeFrog))
			{
				std::cout << " this is frog due !!! " << std::endl;
			}
			std::cout << GetName() << " becoming Super" << name << std::endl;
			name = "Super" + name;
			attribution.speed += 3;
			attribution.power = (attribution.power * 69) / 42;
			attribution.hp += 10;
		}
		else
		{
			std::cout << name << " is dead ,no more Super Stoner! " << std::endl;
		}
	}
};

void Engage(MemeFighter& f1, MemeFighter& f2)
{
	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;
	// determine attack order
	if (p1->GetInitiative() < p2->GetInitiative())
	{
		std::swap(p1, p2);
	}
	// execute attacks
	p1->Attack(*p2);
	p2->Attack(*p1);

}

void DoSpecial(MemeFighter& f1, MemeFighter& f2)
{

	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;
	// determine attack order
	if (p1->GetInitiative() < p2->GetInitiative())
	{
		std::swap(p1, p2);
	}
	// execute attacks
	p1->SpecialMove(*p2);
	p2->SpecialMove(*p1);

}

void Tick(MemeFighter& f1, MemeFighter& f2)
{
	f1.Tick();
	f2.Tick();
}

std::string take(Weapon& weapon)
{
	return weapon.GetName();
}


int main()
{
	std::vector<std::unique_ptr<MemeFighter>> MemeFrogP;
	MemeFrogP.emplace_back(std::make_unique<MemeFrog>("Frog", std::make_unique<Bat>() ) );
	MemeFrogP.emplace_back(std::make_unique<MemeFrog>("Frog1", std::make_unique<Bat>() ) );
	MemeFrogP.emplace_back(std::make_unique<MemeFrog>("Frog2", std::make_unique<Bat>() ) );
	
	std::vector<std::unique_ptr<MemeFighter>> StonerP;
	StonerP.emplace_back(std::make_unique<MemeFrog>("Stoner", std::make_unique<Fists>() ) );
	StonerP.emplace_back(std::make_unique<MemeFrog>("Stoner1", std::make_unique<Fists>() ) );
	StonerP.emplace_back(std::make_unique<MemeFrog>("Stoner2", std::make_unique<Fists>() ) );
	
	const auto alive = [](std::unique_ptr<MemeFighter> &other) {return other->isAlive(); };

	while(
		std::any_of(MemeFrogP.begin(), MemeFrogP.end(),alive) &&
		std::any_of(StonerP.begin(), StonerP.end(), alive)
		)
	{
		std::random_shuffle(MemeFrogP.begin(), MemeFrogP.end());
		std::partition(MemeFrogP.begin(), MemeFrogP.end(), alive);
		std::random_shuffle(StonerP.begin(), StonerP.end());
		std::partition(StonerP.begin(), StonerP.end(), alive);

		for (size_t i = 0; i < MemeFrogP.size(); i++)
		{
			Engage(*MemeFrogP[i], *StonerP[i]);
			DoSpecial(*MemeFrogP[i], *StonerP[i]);
			std::cout << "-------------------------------------------------" << std::endl;
		}
		std::cout << "===================================================" << std::endl;
		for (size_t i = 0; i < MemeFrogP.size(); i++)
		{
			Tick(*MemeFrogP[i],  *StonerP[i]);			
		}

		std::cout << "press any key to continue" << std::endl;
		while (!_kbhit);		
		_getch();
		std::cout << std::endl << std::endl;
	}
	if (std::any_of(MemeFrogP.begin(), MemeFrogP.end(), alive))
	{
		std::cout << "Team One Is Win !!!!" << std::endl;
	}
	else
	{
		std::cout << "Team Two Is Win !!!!" << std::endl;
	}
	

	std::cin.get();
	return 0;
}
