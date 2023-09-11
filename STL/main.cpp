#include<iostream>
#include<array>
#include<vector>

#define tab "\t"
#define delimitr "\n------------------------------------------------------------------------------------------\n"

template<typename T>void vector_properties(const std::vector<T>& vec);

//#define STL_ARRAY
#define STL_VECTOR
void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY

	const int N = 5;
	std::array<int, N> arr = { 3, 5, 8 , 13, 21 };
	for (int i = 0; i < arr.size(); i++)std::cout << arr[i] << tab;
	for (int i : arr) std::cout << i << tab;
	std::cout << std::endl;

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
	int count;
	int value;
	std::cout << "Enter index added value: "; std::cin >> index;
	std::cout << "Enter count added values: "; std::cin >> count;
	std::cout << "Enter value added: "; std::cin >> value;
	//std::vector<int>::iterator it;
	//vec.insert(vec.begin() + index, count, value);
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
#endif // STL_VECTOR

}
template<typename T>void vector_properties(const std::vector<T>& vec)
{
	std::cout << "Size:      " << vec.size() << std::endl;
	std::cout << "MaxSize:   " << vec.max_size() << std::endl;
	std::cout << "Capacity:  " << vec.capacity() << std::endl;
}