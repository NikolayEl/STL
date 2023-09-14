#include<iostream>
#include<map>
#include<list>
#include<fstream>
#include<string>
#include <locale.h>

#define tab "\t"
#define delimetr "\n------------------------------------------------------------------------------------------------------\n"

const std::map<int, std::string> CRIMES =
{
	{0, "N/A"},
	{1, "Проезд на красный"},
	{2, "Парковка в неположенном месте"},
	{3, "Пересечение сплошной"},
	{4, "Превышение скорости"},
	{5, "Езда в нетрезвом виде"},
	{6, "Оскорбление офицера"},
	{7, "Ремень безопасности"},
};
class Crime;

template<typename it> void print(it begin, it end);
void add(std::map<std::string, std::list<Crime>>& base, std::string& number_of_auto, int number_of_crime, std::string& street);
template<typename it>void save(it begin, it end, std::string& file_name);
void load(std::map<std::string, std::list<Crime>>& base, std::string& file_name);
std::list<class Crime, class std::allocator<class Crime>> operator+(std::list<class Crime, class std::allocator<class Crime>> pLeft, Crime pRight);


class Crime
{
	int id; //статья
	std::string place; //место правонарушение
public:
	int get_id() const {return id;}

	const std::string get_crime(int id, const std::map<int, std::string>& CRIMES)
	{
		return CRIMES.at(get_id());
	}

	const std::string& get_place() const { return place;}

	void set_id(int id) {if (id > CRIMES.size()) id = 0; this->id = id;}

	void set_place(const std::string& place) { this->place = place; }

	Crime(int id, const std::string& place) {set_id(id); set_place(place);}

	~Crime(){}
};

std::ostream& operator<<(std::ostream& os, Crime& obj)
{
	return os << obj.get_crime(obj.get_id(), CRIMES) << tab << (obj.get_crime(obj.get_id(), CRIMES).size() < 22? tab:"") << obj.get_place();
}

//#define CHEK_PRINT_MAIN

void main()
{
	system("chcp 1251");
	setlocale(LC_CTYPE, "");

	std::map<std::string, std::list<Crime>> base =
	{
		{"m777ab", {Crime(1, "ул. Ленина"), Crime(2, "ул. Ленина"), Crime(4, "ул. Парижской комунны")}},
		{"k231cc", {Crime(5, "ул. Карла Маркса"), Crime(6, "ул. Карла Маркса")}},
		{"p441oc", {Crime(3, "ул. Пролетарская"), Crime(7, "ул. Пролетарская")}},
	};
	base.insert({ "m776ab", { Crime(1, "ул. Ленина"), Crime(2, "ул. Ленина"), Crime(4, "ул. Парижской комунны") } });
#ifdef CHEK_PRINT_MAIN
	for (std::map<std::string, std::list<Crime>>::iterator it = base.begin(); it != base.end(); ++it)
	{
		std::cout << it->first << ":" << std::endl;
		//for (Crime i : it->second) std::cout << i << "\t";
		for (std::list<Crime>::iterator l_it = it->second.begin(); l_it != it->second.end(); ++l_it) std::cout << tab << *l_it << "\t" << std::endl;
		std::cout << std::endl << std::endl;
	}
#endif // CHEK_PRINT_MAIN

	std::string file_name = "base_crime.csv";
	print(base.cbegin(), base.cend());
	save(base.cbegin(), base.cend(), file_name);
	std::cout << delimetr;

	std::map<std::string, std::list<Crime>> exam;
	load(exam, file_name);
	//std::string number_of_auto, street;
	//int number_of_crime;
	//std::cout << "Введите гос номер правонарушителя образец (a111aa):"; std::cin >> number_of_auto;
	//std::cout << "Введите номер правонарушения из базы:"; std::cin >> number_of_crime;
	//std::cout << "Введите название улицы - места происшествия образец(Ленина):"; std::cin >> street;
	//add(base, number_of_auto, number_of_crime, street);
	print(exam.cbegin(), exam.cend());

}
template<typename it> void print(it begin, it end)
{
	for (;	begin != end; ++begin)
	{
		std::cout << begin->first << ":" << std::endl;
		for (Crime i : begin->second) std::cout << tab << i << tab << std::endl;
		std::cout << std::endl << std::endl;
	}
}
template<typename it>void save(it begin, it end, std::string& file_name)
{
	std::ofstream fout;
	fout.open(file_name, std::ios_base::trunc);
	for (; begin != end; ++begin)
	{
		fout << begin->first << ";";
		for (Crime i : begin->second) fout << i.get_id() << ";" << i.get_place() << ";";
		fout << std::endl;
	}
	fout.close();
}
void load(std::map<std::string, std::list<Crime>>& base, std::string& file_name)
{
	std::ifstream fin;
	fin.open(file_name);
	if (fin.is_open())
	{
		std::string line;
		std::string delim = ";";
		while (std::getline(fin, line))
		{
			size_t pos = 0;
			std::string* token = new std::string[line.size() / 4];
			int i = 0;
			while ((pos = line.find(delim)) != std::string::npos)
			{
				token[i] = line.substr(0, pos);
				line.erase(0, pos + delim.length());
				i++;
			}
			int l = 1;
			while (token[l] != "")
			{
				add(base, token[0], std::stoi(token[l]), token[l + 1]);
				l += 2;
			}
		}
	}
	else std::cerr << "Error: file not found" << std::endl;
}
void add(std::map<std::string, std::list<Crime>>& base, std::string& number_of_auto, int number_of_crime, std::string& street)
{
	std::map<std::string, std::list<Crime>>::iterator it = base.find(number_of_auto);
	if (it != base.end())
	{
		//Crime temp = { number_of_crime, street };
		base.at(number_of_auto) = it->second + Crime(number_of_crime, "ул. " + street);
	}
	else base.insert({ number_of_auto, {Crime(number_of_crime, "ул. " + street)} });
}
std::list<class Crime, class std::allocator<class Crime>> operator+(std::list<class Crime, class std::allocator<class Crime>> pLeft, Crime pRight)
{
	std::list<class Crime, class std::allocator<class Crime>>::iterator it = pLeft.begin();
	pLeft.insert(it, pRight);
	return pLeft;
}