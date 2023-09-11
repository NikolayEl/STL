#include<iostream>

void main()
{
	setlocale(LC_ALL, "");
	try
	{
		throw 1;
	}
	catch (int e)
	{
		std::cerr << "Error #" << e << std::endl;
	}
	catch (double e)
	{
		std::cerr << "Error #" << e << std::endl;
	}

	try
	{
		throw std::exception("C++ Exeption");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}