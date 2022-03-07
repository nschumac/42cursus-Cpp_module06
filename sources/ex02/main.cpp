#include <iostream>
#include <random>
#include <time.h>

class Base
{
	public:
	virtual ~Base(){};
};

class A : public Base{};
class B : public Base{};
class C : public Base{};

Base *generate(void)
{
	int r = rand() % 3;
	if (r == 0)
		return (new A);
	else if (r == 1)
		return (new B);
	else
		return (new C);
}

void	identify(Base *p)
{
	Base *t1;

	t1 = dynamic_cast<A*>(p);
	if (!t1)
	{
		t1 = dynamic_cast<B*>(p);
		if (!t1)
		{
			t1 = dynamic_cast<C*>(p);
			if (t1)
				std::cout << "C" << std::endl;
			return ;
		}
		std::cout << "B" << std::endl;
		return ;
	}
	std::cout << "A" << std::endl;
}

void identify(Base& p)
{
	try
	{
		A A1 = dynamic_cast<A&>(p);
		(void)(A1);
		std::cout << "A" << std::endl;
	}
	catch(const std::exception & e)
	{
		try
		{
			B B1 = dynamic_cast<B&>(p);
			(void)(B1);
			std::cout << "B" << std::endl;
		}
		catch(const std::exception & e)
		{
			try
			{
				C C1 = dynamic_cast<C&>(p);
				(void)(C1);
				std::cout << "C" << std::endl;
			}
			catch(const std::exception& e)
			{
			}
		}
	}	
}

int main()
{
	srand((unsigned int)(time(NULL)));
	Base * t1 = generate();
	Base * t2 = generate();
	identify(t1);
	identify(t2);

	Base &t3 = *t1;
	Base &t4 = *t2;
	identify(t3);
	identify(t4);

	delete t1;
	delete t2;
}