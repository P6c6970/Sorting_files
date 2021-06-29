#pragma once
#include <string>

class Byte {
private:
	std::string unitOfMeasurement(int temp) {
		switch (temp)
		{
		case 0:
			return " �";
			break;
		case 1:
			return " ��";
			break;
		case 2:
			return " ��";
			break;
		case 3:
			return " ��";
			break;
		case 4:
			return " ��";
			break;
		default:
			break;
		}
		return "";
	}

public:
	std::string show(double byte) {
		int temp = 0;
		while (byte / 1024. > 1) {
			temp++;
			byte /= 1024.;
		}
		char s[7];
		sprintf_s(s, "%.2f", byte);
		return s + unitOfMeasurement(temp);
	}
};