#include <iostream>
#include <filesystem>
#include <Windows.h>

#include "Byte.h"
#include "SettingsSort.h"

namespace fs = std::experimental::filesystem;
void setColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void message(std::string mes1, std::string mes2) {
	setColor(14, 0);
	std::cout << mes1;
	setColor(11, 0);
	//mes2.resize(10, ' ');
	std::cout << mes2 << std::endl;
}

void reduction(std::string &temp, short a) {
	if (temp.size() > a) {
		temp.resize(a - 3);
		temp += "...";
	}
	else {
		temp.resize(a, ' ');
	}
}

void message(std::string mes1, std::string mes2, std::string mes3, std::string mes4) {
	reduction(mes1, 30);
	reduction(mes2, 5);
	reduction(mes3, 9);
	reduction(mes4, 11);
	setColor(11, 0);
	std::cout << '|';
	setColor(14, 0);
	std::cout << mes1;
	setColor(11, 0);
	std::cout << '|';
	setColor(13, 0);
	std::cout << mes2;
	setColor(11, 0);
	std::cout << '|';
	setColor(12, 0);
	std::cout << mes3;
	setColor(11, 0);
	std::cout << '|';
	setColor(10, 0);
	std::cout << mes4;
	setColor(11, 0);
	std::cout << '|';
	std::cout << std::endl;
}

void messageUp() {
	setColor(11, 0);
	std::cout << '|';
	setColor(14, 0);
	std::cout << "Имя                           ";
	setColor(11, 0);
	std::cout << '|';
	setColor(13, 0);
	std::cout << "Тип  ";
	setColor(11, 0);
	std::cout << '|';
	setColor(12, 0);
	std::cout << "Размер   ";
	setColor(11, 0);
	std::cout << '|';
	setColor(10, 0);
	std::cout << "Перенесён в";
	setColor(11, 0);
	std::cout << '|';
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
}

int main()
{
	//имя >>    тип файла >>   размер >>       файл перенесён в >> 
	setlocale(LC_ALL, "Russian");
	//system("cls");//отчистить экран
	SettingsSort settingSort;
	if (!settingSort.reader("settings.txt")) {
		setColor(12, 0);
		std::cout << "Не существует файла настроек" << std::endl;
	}
	else {
		std::string path;
		//= R"(Z:\test)";
		setColor(14, 0);
		std::cout << "Введите адрес папки, которую нужно отсортировать >> ";
		setColor(15, 0);
		std::cin >> path;
		if (!fs::exists(path)) {
			setColor(12, 0);
			std::cout << "Не существует" << std::endl << std::endl;
		}
		else {
			Byte byte;
			for (int i = 0; i < static_cast<int>(settingSort.typeNames.size()); i++)
			{
				fs::create_directory(path + "\\"+ settingSort.typeNames[i]);
			}
			int sizeAll = 0;
			int size;
			messageUp();
			for (const auto &p : fs::directory_iterator(path)) {
				fs::path a(p);
				if (!fs::is_directory(p)) {
					std::string temp{ a.extension().string() };
					try
					{
						size = static_cast<int>(fs::file_size(a));
						sizeAll += size;
					}
					catch (fs::filesystem_error& e)
					{
						std::cout << e.what() << std::endl;
					}
					temp = settingSort.typeFind(temp);
					if (temp != "") {
						fs::path b = a.parent_path();
						b += "\\" + temp + "\\";
						b += a.filename();
						fs::rename(a, b);
					}
					message(a.filename().string(), a.extension().string(), byte.show(size), temp);
				}
			}
			
			for (int i = 0; i < static_cast<int>(settingSort.typeNames.size()); i++)
			{
				if (fs::is_empty(path + "\\" + settingSort.typeNames[i])) {
					fs::remove(path + "\\" + settingSort.typeNames[i]);
				}
			}
			std::cout << std::endl << std::endl;
			message("Итоговый вес файлов(кроме папок) >> ", byte.show(sizeAll));
		}
	}
	setColor(15, 0);
	return 0;
}
