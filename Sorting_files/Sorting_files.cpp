#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>

namespace fs = std::experimental::filesystem;

struct Types
{
	std::string type;
	std::string nameType;
	Types(std::string type, std::string nameType) : type(type), nameType(nameType) {};
};

std::string cutString(std::string a, short b, short c) { //a[b:c)
	std::string d = "";
	for (int i = b; i < c; i++) {
		d += a[i];
	}
	return d;
}

bool reader(std::string adress, std::vector<Types> &types, std::vector<std::string> &typeNames) {
	bool status = false;
	std::string line;
	std::ifstream fin;
	fin.open(adress);
	if (fin.is_open()) {//if the file is open
		status = true;
		std::cout << 1 << std::endl;
		while (std::getline(fin, line)) {
			if (line != "") {
				short tempI = line.find(':');
				std::string nameType = cutString(line, 0, tempI);
				typeNames.push_back(nameType);
				line = cutString(line, ++tempI, line.length());
				tempI = 0;
				short len = line.length();
				for (int i = 0; i < len; i++)
				{
					if (line[i] == ',' || i + 1 == len) {
						if (i + 1 == len) i++;
						std::string tempS = cutString(line, tempI, i);
						if (tempS[0] == ' ') tempS.erase(0, 1);
						if (tempS[tempS.length() - 1] == ' ') tempS.erase(tempS.length() - 1, 1);
						types.push_back(Types('.' + tempS, nameType));
						tempI = i + 1;
					}
				}				
			}
		}
	}
	fin.close(); // закрываем файл
	return status;
}

std::string typeFind(std::vector<Types> &types, std::string temp) {
	std::string type = "";
	for (int i = 0; i < types.size(); i++)
	{
		if (types[i].type == temp) {
			type = types[i].nameType;
			break;
		}
	}
	return type;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::vector<Types> types;
	std::vector<std::string> typeNames;
	if (reader("settings.txt", types, typeNames)) {
		std::string path = R"(Z:\test)";
		if (fs::exists(path)) {
			for (int i = 0; i < typeNames.size(); i++)
			{
				fs::create_directory(path + "\\"+ typeNames[i]);
			}
			int size = 0;
			for (const auto &p : fs::directory_iterator(path)) {
				fs::path a(p);
				std::cout << "полное имя = " << a << std::endl;
				std::cout << "имя = " << a.filename() << std::endl;
				std::cout << "адресс = " << a.parent_path() << std::endl;
				if (!fs::is_directory(p)) {
					std::cout << "тип файла = " << a.extension() << std::endl;
					std::string temp{ a.extension().u8string() };
					try
					{
						int temp = fs::file_size(a);
						size += temp;
						std::cout << "размер = " << temp << " байт" << std::endl;
					}
					catch (fs::filesystem_error& e)
					{
						std::cout << e.what() << std::endl;
					}
					temp = typeFind(types, temp);
					if (temp != "") {
						fs::path b = a.parent_path();
						b += "\\" + temp + "\\";
						b += a.filename();
						fs::rename(a, b);
						std::cout << std::endl;
						std::cout << "полное новое имя = " << a << std::endl;
						std::cout << "новое имя = " << a.filename() << std::endl;
						std::cout << "новое адресс = " << a.parent_path() << std::endl;
					}
				}
			}
			for (int i = 0; i < typeNames.size(); i++)
			{
				if (fs::is_empty(path + "\\" + typeNames[i])) {
					fs::remove(path + "\\" + typeNames[i]);
				}
			}
			
			std::cout << size << " байт" << std::endl;
			std::cout << size / 1024. << " килобайт" << std::endl;
			std::cout << size / 1024. / 1024. << " мегабайт" << std::endl;
		}
		else {
			std::cout << "Не существует" << std::endl;
		}
	}
	else {
		std::cout << "Не существует файла настроек" << std::endl;
	}
	
	return 0;
}
