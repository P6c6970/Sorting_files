#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::experimental::filesystem;

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string path = R"(Z:\test)";
	if (fs::exists(path)) {
		fs::create_directory(path + "\\imag");
		int size = 0;
		for (const auto &p : fs::directory_iterator(path)) {
			fs::path a(p);
			std::cout << "полное имя = " << a << std::endl;
			std::cout << "имя = " << a.filename() << std::endl;
			std::cout << "адресс = " << a.parent_path() << std::endl;
			if (!fs::is_directory(p)) {
				std::cout << "тип файла = " << a.extension() << std::endl;
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
				fs::path b = a.parent_path();
				b += "\\imag\\";
				b += a.filename();
				fs::rename(a, b);
				std::cout << std::endl;
				std::cout << "полное новое имя = " << a << std::endl;
				std::cout << "новое имя = " << a.filename() << std::endl;
				std::cout << "новое адресс = " << a.parent_path() << std::endl;
				
			}
		}
		if (fs::is_empty(path + "\\imag")) {
			fs::remove(path + "\\imag");
		}
		std::cout << size << " байт" << std::endl;
		std::cout << size / 1024. << " килобайт" << std::endl;
		std::cout << size / 1024. / 1024. << " мегабайт" << std::endl;
	}
	else {
		std::cout << "Не существует" << std::endl;
	}	
	return 0;
}
