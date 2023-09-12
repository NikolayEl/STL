#include<iostream>
#include<array>
#include<vector>
#include<list>
#include<forward_list>

#define tab "\t"
#define delimitr "\n------------------------------------------------------------------------------------------\n"

template<typename T>void vector_properties(const std::vector<T>& vec);
template<typename it> void print(it begin, it end);
template<typename it> int size_forward_list(it begin, it end);


//#define STL_ARRAY
//#define STL_VECTOR
//#define STL_LIST
#define STL_FORWARD_LIST
void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY

	const int N = 5;
	std::array<int, N> arr = { 3, 5, 8 , 13, 21 };
	for (int i = 0; i < arr.size(); i++)std::cout << arr[i] << tab;
	for (int i : arr) std::cout << i << tab;
	std::cout << std::endl;
	//print(arr.cbegin(), arr.cend());

#endif // STL_ARRAY

#ifdef STL_VECTOR
	std::vector<int> vec = {0, 1, 1, 2, 3, 5, 8 , 13, 21,34 };
	try
	{
		for (int i = 0; i < vec.size() * 2; i++) /*std::cout << vec[i] << tab*/std::cout << vec.at(i) << tab;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;
	vec.push_back(55);
	vector_properties(vec);
	//vec.resize(18);
	vec.reserve(120);
	vec.shrink_to_fit();
	for (int i : vec) std::cout << i << tab;
	std::cout << std::endl;
	std::cout << delimitr;
	vector_properties(vec);
	std::cout << delimitr;
	//vector_properties(vec);
	//std::vector<int> vec2(100);
	//vector_properties(vec2);
	//std::cout << delimitr;	
	//vec2.push_back(1024);
	//vector_properties(vec2);
	//std::cout << delimitr;

	//std::vector<double> d_vec = { 2.7, 3.14, 8.3 };
	//vector_properties(d_vec);

	int index;
	int beg;
	int value;
	std::cout << "Enter index added value: "; std::cin >> index;
	std::cout << "Enter count added values: "; std::cin >> beg;
	std::cout << "Enter value added: "; std::cin >> value;
	//std::vector<int>::iterator it;
	//vec.insert(vec.begin() + index, beg, value);
	vec.insert(vec.begin() + 8, vec.begin() + 3, vec.begin() + 7);
	vec.insert(vec.begin() + 5, { 1024, 2048, 3072 });
	//for (int i : vec) std::cout << i << tab;
	std::cout << delimitr;
	for(std::vector<int>::iterator it = vec.begin(); it < vec.end(); ++it)std::cout << *it << tab;
	std::cout << delimitr;
	for(std::vector<int>::reverse_iterator it = vec.rbegin(); it < vec.rend(); ++it)std::cout << *it << tab;
	std::cout << delimitr;
	std::cout << std::endl;
	int index2;
	std::cout << "Enter index erase value: "; std::cin >> index2;
	vec.erase(vec.begin() + index);
	for (int i : vec) std::cout << i << tab;
	std::cout << "Exam print:" << std::endl;
	print(vec.cbegin(), vec.cend());
#endif // STL_VECTOR
#ifdef STL_LIST
	std::list<int> list = { 3, 5, 8, 13, 21, 34 };
	print(list.cbegin(), list.cend());
	std::cout << delimitr;

	int index;
	int value;
	std::list<int>::iterator it;
	std::cout << "Enter index added value: "; std::cin >> index;
	std::cout << "Enter value: "; std::cin >> value;
	if (index < list.size() / 2)
	{
		it = list.begin();
		for (int i = 0; i < index; i++) ++it;
	}
	else
	{
		it = list.end();
		for (int i = list.size(); i > index; i--) --it;
	}
	list.insert(it, value);
	print(list.cbegin(), list.cend());
	std::cout << delimitr;

	int index2;
	std::cout << "Enter index erased value: "; std::cin >> index2;
	if (index2 < list.size() / 2)
	{
		it = list.begin();
		for (int i = 0; i < index2; i++) ++it;
	}
	else
	{
		it = list.end();
		for (int i = list.size(); i > index2; i--) --it;
	}
	list.erase(it);
	print(list.cbegin(), list.cend());
	

#endif // STL_LIST

#ifdef STL_FORWARD_LIST

	std::forward_list<int> forward_list = { 1, 2, 3, 5, 8, 13, 21 };
	print(forward_list.cbegin(), forward_list.cend());

	std::cout << delimitr;

	int index;
	int value;
	int size = size_forward_list(forward_list.cbegin(), forward_list.cend());
	std::cout << "Enter index added value: "; std::cin >> index;
	std::cout << "Enter added value: "; std::cin >> value;

	std::forward_list<int>::iterator it;
	if (index == 0) forward_list.push_front(value);
	else
	{
		int count = 0;
		for (it = forward_list.before_begin(); it != forward_list.end(); ++it, count++)
		{
			if (count == (index < size? index: size)) break; //Условие потому что если индекс больше размера списка, дойдем до end(nullptr)
		}
		forward_list.insert_after(it, value);
	}

	print(forward_list.cbegin(), forward_list.cend());
	std::cout << delimitr;
#endif // STL_FORWARD_LIST


}
template<typename T>void vector_properties(const std::vector<T>& vec)
{
	std::cout << "Size:      " << vec.size() << std::endl;
	std::cout << "MaxSize:   " << vec.max_size() << std::endl;
	std::cout << "Capacity:  " << vec.capacity() << std::endl;
}
template<typename it> void print(it begin, it end)
{
	for (; begin != end; ++begin)std::cout << *begin << tab; std::cout << std::endl;
}
template<typename it> int size_forward_list(it begin, it end)
{
	int size = 0;
	for (; begin != end; ++begin, size++);
	return size;
}