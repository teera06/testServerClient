#pragma once
#include <list>
#include <string>

class stackClass
{
public:
	void StackPush(int _n)
	{
		Stacklist.push_back(_n);
	}

	int StackPop()
	{
		if (StackSize() == 0)
		{
			return -1;
		}

		int Value = Stacklist.back();
		Stacklist.pop_back();
		return Value;
	}

	int StackSize()
	{
		return Stacklist.size();
	}

	int Stackempty()
	{
		if (StackSize() == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	int StackTop()
	{
		if (StackSize() == 0)
		{
			return -1;
		}
		else
		{
			return Stacklist.back();
		}
	}




private:

	std::list<int> Stacklist;
};

