#include "data_read.h"



DataRead::DataRead()
{
}

bool DataRead::checkInt(std::string s)
{
	if (std::all_of(s.cbegin(), s.cend(), isdigit))
	{
		return true;
	}
	else {
		return false;
	}
}


void DataRead::read(int &n, std::vector<cv::Rect> &rect)
{
	std::string line;
	std::string s;
	std::cout << "�f�[�^����͂��Ă�������" << std::endl;
	//std::cin >> s;
	getline(std::cin, s);
	//������łȂ���΁C�t�@�C�����Ƃ݂Ȃ�
	if (!checkInt(s)) {
		std::ifstream ifs(s);

		if (ifs.fail()) {
			std::cerr << "File do not exist.\n";
			exit(0);
		}
		getline(ifs, line);
		n = std::stoi(line);
		rect.resize(n);

		int x, y, w, h, count = 0;
		while (getline(ifs, line)) {
			x = 0; y = 0; w = 0, h = 0;
			sscanf_s(line.data(), "%d %d %d %d", &x, &y, &w, &h, sizeof(x), sizeof(y), sizeof(w), sizeof(h));
			rect[count] = cv::Rect{x,y,w,h};
			count++;
		}
	}else{ //�W�����͂���ǂݍ���
		n = std::stoi(s);
		rect.resize(n);
		int x, y, w, h, count = 0;
		for (count = 0; count < n; count++) {
			getline(std::cin, line);
			x = 0; y = 0; w = 0, h = 0;
			sscanf_s(line.data(), "%d %d %d %d", &x, &y, &w, &h, sizeof(x), sizeof(y), sizeof(w), sizeof(h));
			rect[count] = cv::Rect{ x,y,w,h };
		}
	}
}

DataRead::~DataRead()
{
}
