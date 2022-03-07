#include <iostream>
#include <cstdint>

struct Data
{
	int test;
};

uintptr_t serialize(Data* ptr)
{
	ptr->test <<= 10;
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* deserialize(uintptr_t raw)
{
	Data *ret;

	ret = reinterpret_cast<Data *>(raw);
	ret->test >>= 10;
	return (ret);
}

int main()
{
	Data  *t1 = new Data;
	t1->test = 1;
	uintptr_t ptr = serialize(t1);
	Data *t3 = reinterpret_cast<Data *>(ptr);
	std::cout << t3->test << std::endl;
	Data *t2 = deserialize(ptr);
	std::cout << t2 << " " << t1 << " " << t2->test << std::endl;
}