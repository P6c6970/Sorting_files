#pragma once
#include <string>

class Byte {
private:
	std::string unitOfMeasurement(int temp) {
		switch (temp)
		{
		case 0:
			return " ม";
			break;
		case 1:
			return " สม";
			break;
		case 2:
			return " ฬม";
			break;
		case 3:
			return " รม";
			break;
		case 4:
			return " าม";
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