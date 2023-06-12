#include"Composite.h"

void Leaf::Add(Component* c)
{
	std::cout << "leaf   add" << std::endl;
}
void Leaf::Remove(Component* c)
{
	std::cout << "leaf   remove" << std::endl;

}
void Leaf::Display(int depth)
{
	std::string str(depth, '-');
	std::cout << "cur   is: " << str <<name << std::endl;

}


void Composite::Add(Component* c)
{
	child.push_back(c);
}

void Composite::Remove(Component* c)
{
	auto iter = find(child.begin(), child.end(), c);
	if (iter != child.end())
	{
		child.erase(iter);
	}
}

void Composite::Display(int depth)
{
	std::string str(depth, '-');

	std::cout << "cur   is: " << str << name  << std::endl;
	for (auto iter = child.begin(); iter != child.end(); ++iter)
	{
		(*iter)->Display(depth + 2);
	}
}