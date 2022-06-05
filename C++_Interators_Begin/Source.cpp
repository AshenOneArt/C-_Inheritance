#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <numeric>

class TestA
{
public:
	TestA() = default;
	TestA(int a,int b)
		:
		Num_0(a),
		Num_1(b)
	{
	}
	void Num_0_Add_10()
	{
		Num_0 += 10;
	}
	void Num_1_Add_20()
	{
		Num_0 + 20;
	}
	int Get0() const
	{
		return Num_0;
	}
	int Get1() const
	{
		return Num_1;
	}
protected:
	int Num_0;
	int Num_1;
};

class TestB : public TestA
{
public:
	TestB(int a)
		:
		TestA(0,0),
		ExtraNum(a)
	{
	}
	void Num_0_Add_10()
	{
		TestA::Num_0_Add_10();
		Num_0 += 5;
	}
private:
	int ExtraNum;
};

//int main()
//{
//	TestA a = { 0,0 };
//	TestB b(5);
//
//	a.Num_0_Add_10();
//	b.Num_0_Add_10();
//	std::cout << a.Get0() << std::endl;
//	std::cout << b.Get0() << std::endl;
//	std::cin.get();
//	
//}