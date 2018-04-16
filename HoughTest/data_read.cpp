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
	std::string name, fullpass;
	char dir[255];
	std::cout << "データを入力してください" << std::endl;
	//std::cin >> s;
	getline(std::cin, name);
	//文字列でなければ，ファイル名とみなす
	if (!checkInt(name)) {

		//ファイルのfullパスを取得(必ず現在のディレクトリに入れる事)
		GetCurrentDirectory(sizeof(dir), dir);
		fullpass = dir + std::string("\\") + name;
		std::ifstream ifs(fullpass);

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
	}else{ //標準入力から読み込む
		n = std::stoi(name);
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
