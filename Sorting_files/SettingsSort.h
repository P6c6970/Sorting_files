#pragma once
#include <string>
#include <vector>
#include <fstream>

class SettingsSort {
private:
	struct Types //type:nameType (img:png)
	{
		std::string type;
		std::string nameType;
		Types(std::string type, std::string nameType) : type(type), nameType(nameType) {};
	};

public:
	std::vector<Types> types;
	std::vector<std::string> typeNames;

	bool reader(std::string adress) {
		bool status = false;
		std::string line;
		std::ifstream fin;
		fin.open(adress);
		if (fin.is_open()) {//if the file is open
			status = true;
			while (std::getline(fin, line)) {
				if (line != "") {
					short tempI = line.find(':');
					std::string nameType = line.substr(0, tempI);
					typeNames.push_back(nameType);
					line = line.substr(++tempI);
					tempI = 0;
					short len = line.length();
					for (int i = 0; i < len; i++)
					{
						if (line[i] == ',' || i + 1 == len) {
							if (i + 1 == len) i++;
							std::string tempS = line.substr(tempI, i - tempI);
							if (tempS[0] == ' ') tempS.erase(0, 1);
							if (tempS[tempS.length() - 1] == ' ') tempS.erase(tempS.length() - 1, 1);
							types.push_back(Types('.' + tempS, nameType));
							tempI = i + 1;
						}
					}
				}
			}
		}
		fin.close(); // close file
		return status;
	}

	std::string typeFind(std::string temp) {
		std::string type = "";
		for (int i = 0; i < static_cast<int>(types.size()); i++)
		{
			if (types[i].type == temp) {
				type = types[i].nameType;
				break;
			}
		}
		return type;
	}
};