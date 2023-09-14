#include<iostream>
#include<map>
#include<list>
#include<fstream>

#define tab "\t"

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

template<typename it> void print(it begin, it end);
template<typename it>void save(it begin, it end, std::string& file_name);


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
	setlocale(LC_ALL, "");

	std::map<std::string, std::list<Crime>> base =
	{
		{"m777ab", {Crime(1, "ул. Ленина"), Crime(2, "ул. Ленина"), Crime(4, "ул. Парижской комунны")}},
		{"k231cc", {Crime(5, "ул. Карла Маркса"), Crime(6, "ул. Карла Маркса")}},
		{"p441oc", {Crime(3, "ул. Пролетарская"), Crime(7, "ул. Пролетарская")}},
	};
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
	std::ofstream out;
	out.open(file_name, std::ios_base::trunc);
	for (; begin != end; ++begin)
	{
		out << begin->first << ";";
		for (Crime i : begin->second) out << i.get_id() << ";" << i.get_place() << ";";
		out << std::endl;
	}
	out.close();
}