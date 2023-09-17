#include<iostream>
#include<map>
#include<list>
#include<fstream>
#include<string>

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
std::map<std::string, std::list<Crime>> add(const std::map<std::string, std::list<Crime>>& base, 
	const std::string& number_of_auto, const int number_of_crime, const std::string& street);
template<typename it>void save(it begin, it end, const std::string& file_name);
std::map<std::string, std::list<Crime>> load(const std::map<std::string, std::list<Crime>>& base, std::string& file_name);
std::list<class Crime, class std::allocator<class Crime>> operator+(const std::list<class Crime, class std::allocator<class Crime>>& pLeft, const Crime& pRight);
void print_car_number(const std::map<std::string, std::list<Crime>>& base, const std::string& with_number);

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
//std::ostream& operator<<(std::ostream& os, Crime& obj)  //code with OA
//{
//	return os << CRIMES.at(obj.get_id()) << tab << (obj.get_crime(obj.get_id(), CRIMES).size() < 22 ? tab : "") << obj.get_place();
//}
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_id() << " " << obj.get_place();
	return ofs;
}

//#define CHEK_PRINT_MAIN
//#define CHEK_SAVE
//#define CHEK_LOAD
//#define CHEK_ADD

void main()
{
	system("chcp 1251");
	setlocale(LC_CTYPE, "");

	std::map<std::string, std::list<Crime>> base =
	{
		{"m777ab", {Crime(1, "ул. Ленина"), Crime(2, "ул. Ленина"), Crime(4, "ул. Парижской комунны")}},
		{"k231cc", {Crime(5, "ул. Карла Маркса"), Crime(6, "ул. Карла Маркса")}},
		{"k232cc", {Crime(3, "ул. Серетенский бульвар"), Crime(4, "ул. Байкальская")}},
		{"k233cc", {Crime(2, "ул. Кузнечный мост"), Crime(2, "ул. Полянка")}},
		{"k240cc", {Crime(4, "ул. Арбат"), Crime(7, "ул. Старый Арбат")}},
		{"k240ck", {Crime(1, "ул. Декабрьских Событий"), Crime(2, "ул. Ново-разводная")}},
		{"l240cc", {Crime(6, "ул. Советская"), Crime(3, "ул. пер. Ландышева")}},
		{"m240cc", {Crime(7, "ул. Подаптечная"), Crime(1, "ул. Житницкая")}},
		{"p441oc", {Crime(3, "ул. Пролетарская"), Crime(7, "ул. Стародворье")}},
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

#ifdef CHEK_SAVE
	//-----------------------------------SAVE-----------------------------
	std::cout << "CHEK_SAVE_FUNCTION:" << std::endl;
	print(base.cbegin(), base.cend());
	std::string file_name = "base_crime.csv";
	save(base.cbegin(), base.cend(), file_name);
	std::cout << delimetr;
#endif // CHEK_SAVE

#ifdef CHEK_LOAD

	//-----------------------------------LOAD-----------------------------
	std::cout << "CHEK_LOAD_FUNCTION:" << std::endl;
	std::map<std::string, std::list<Crime>> exam;
	exam = load(base, file_name);
	print(exam.cbegin(), exam.cend());

#endif // CHEK_LOAD

#ifdef CHEK_ADD
	//-----------------------------------ADD-------------------------------
	std::cout << "CHEK_ADD_FUNCTION:" << std::endl;
	std::string number_of_auto, street;
	int number_of_crime;
	std::cout << "Введите гос номер правонарушителя образец (a111aa):"; std::cin >> number_of_auto;
	std::cout << "Введите номер правонарушения из базы:"; std::cin >> number_of_crime;
	std::cout << "Введите название улицы - места происшествия образец(Ленина):"; std::cin >> street;
	base = add(base, number_of_auto, number_of_crime, street);
	print(base.cbegin(), base.cend());
#endif // CHEK_ADD


	//----------------------------------PRINT NUMBER-----------------------
	print(base.cbegin(), base.cend());
	std::string with_number;
	std::cout << "Введите гос номер правонарушителя образец (a111aa) или список номеров" << std::endl;
		std::cout << " - образец(a111aa - b222bb от меньшего к большему) :"; std::cin >> with_number;
	print_car_number(base, with_number);

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
template<typename it>void save(it begin, it end, const std::string& file_name)
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
std::map<std::string, std::list<Crime>> load(const std::map<std::string, std::list<Crime>>& base, std::string& file_name)
{
	std::map<std::string, std::list<Crime>> temp = base;
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
				add(temp, token[0], std::stoi(token[l]), token[l + 1]);
				l += 2;
			}
		}
		fin.close();
	}
	else std::cerr << "Error: file not found" << std::endl;
	return temp;
}
std::map<std::string, std::list<Crime>> add(const std::map<std::string, std::list<Crime>>& base, 
	const std::string& number_of_auto, const int number_of_crime, const std::string& street)
{
	std::map<std::string, std::list<Crime>> temp = base;
	std::map<std::string, std::list<Crime>>::iterator it = temp.find(number_of_auto);
	if (it != temp.end()) 
	{
		temp.at(number_of_auto) = it->second + Crime(number_of_crime, (street.substr(0, 1) != "ул" ? "ул. " + street : street));
	}
	else
	{
		temp.insert({ number_of_auto, {Crime(number_of_crime, (street.substr(0, 1) != "ул" ? "ул. " + street : street))} });
	}
	return temp;
}
std::list<class Crime, class std::allocator<class Crime>> operator+(const std::list<class Crime, class std::allocator<class Crime>>& pLeft, const Crime& pRight)
{
	std::list<class Crime, class std::allocator<class Crime>> temp = pLeft;
	temp.push_back(pRight);
	return temp;
}
void print_car_number(const std::map<std::string, std::list<Crime>>& base, const std::string& with_number)
{
	std::map<std::string, std::list<Crime>>::const_iterator it;
	if (with_number.size() < 7)
	{
		it = base.find(with_number);
		if (it != base.end())
		{
			std::cout << it->first << ":" << std::endl;
			for (Crime i : it->second) std::cout << tab << CRIMES.at(i.get_id()) << tab << i.get_place() << std::endl;
		}
		else std::cerr << "Number not found" << std::endl;
		
	}
	else
	{
		if (with_number.size() > 13)
		{
			std::cerr << "Вы ввели не правильный интервал, образец - a111aa-c333cc" << std::endl;
			return;
		}
		unsigned temp[14];
		for (int i = 0; i <= with_number.size(); i++)
		{
			temp[i] = static_cast<unsigned>(static_cast<unsigned char>(with_number[i]));
		}
		for (it = base.begin(); it != base.end(); ++it)
		{
			bool exam;
			unsigned temp_number[6];
			for (int k = 0; k < it->first.size(); k++)
			{
				temp_number[k] = static_cast<unsigned>(static_cast<unsigned char>(it->first[k]));
			}
			for (int k = 0; k < it->first.size(); k++)
			{
				exam = false;
				if (it->first == with_number.substr(0, 6) || it->first == with_number.substr(7, 6))
				{
					exam = true;
					break;
				}
				if (temp_number[k] > temp[k] && temp_number[k] < temp[k + 7])
				{
					if (temp_number[0] <= temp[7])
					{
						exam = true;
						break;
					}
					else continue;
				}
				else if (temp_number[k] == temp[k] || temp_number[k] == temp[k+7])
				{
					if (temp_number[0] <= temp[7])
					{
						exam = true;
						continue;
					}
					else break;
				}
				else break;
			}
			if (exam)
			{
				std::cout << it->first << ":" << std::endl;
				for (Crime i : it->second) std::cout << tab << CRIMES.at(i.get_id()) << tab << i.get_place() << std::endl;
			}
		}
	}
}