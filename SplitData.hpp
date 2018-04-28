#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<windows.h>

int get_random_int(int upbound) {
	std::random_device seed;
	std::default_random_engine rd(seed());
	std::uniform_int_distribution<> u(0, upbound);
	int res = u(rd);
	return res;
}

class SplitData {
public:
	SplitData(std::string categories, std::string list, int _categories_num, float ratio) {
		categories_num = _categories_num;
		category_id = get_categories(categories, categories_num);
		category_id_mapping = label_to_id(list, categories_num);
		to_val_vector.resize(categories_num);

		std::cout << "creating random num for moving datasets to val_dir..." << std::endl;
		for (int i = 0; i < categories_num; ++i) {
			to_val_vector[i].resize(int(category_id_mapping[i].size()*ratio));
			std::cout << to_val_vector[i].size() << std::endl;
			for (auto j = 0; j < to_val_vector[i].size(); ++j) {
				int temp = get_random_int(category_id_mapping[i].size() - 1);
				while (is_Same(to_val_vector[i], temp)) {
					temp = get_random_int(category_id_mapping[i].size() - 1);
				}
				to_val_vector[i][j] = temp;
			}
		}
	}//���캯��

	void moving(std::string source_dir) {
		std::string train_dir = source_dir + "\\train";
		std::string val_dir = source_dir + "\\val";
		if (CreateDirectory(train_dir.c_str(), nullptr) == false) {
			std::cout << "failed to create train_dir" << std::endl;
			return;
		}
		if (CreateDirectory(val_dir.c_str(), nullptr) == false) {
			std::cout << "failed to create val_dir" << std::endl;
			return;
		}

		for (auto i = 0; i < categories_num; ++i) {
			std::string train_category_dir = train_dir + "\\" + std::string(category_id[i]);
			std::string val_category_dir = val_dir + "\\" + std::string(category_id[i]);
			if (CreateDirectory(train_category_dir.c_str(), nullptr) == false) {
				std::cout << "failed to create train_category_dir" << std::endl;
				return;
			}
			if (CreateDirectory(val_category_dir.c_str(), nullptr) == false) {
				std::cout << "failed to create val_category_dir" << std::endl;
				return;
			}
		}

		for (auto i = 0; i < categories_num; ++i) {
			for (auto j = 0; j < category_id_mapping[i].size(); ++j) {
				std::string file_name = source_dir + "\\" + category_id_mapping[i][j] + ".jpg";
				if (is_Same(to_val_vector[i], j)) {
					std::string traget_val_file = val_dir + "\\" + std::string(category_id[i]) + "\\" + category_id_mapping[i][j] + ".jpg";
					std::cout << "moving to val      " << category_id_mapping[i][j] << std::endl;
					CopyFile(file_name.c_str(), traget_val_file.c_str(), true);
				}
				else {
					std::string target_train_file = train_dir + "\\" + std::string(category_id[i]) + "\\" + category_id_mapping[i][j] + ".jpg";
					std::cout << "moving to train    " << category_id_mapping[i][j] << std::endl;
					CopyFile(file_name.c_str(), target_train_file.c_str(), true);
				}
			}//for
		}//for
		std::cout << "done" << std::endl;
	}//
private:
	int categories_num;
	std::vector<std::vector<std::string>> category_id_mapping;
	std::vector<std::string> category_id;
	std::vector<std::vector<int>> to_val_vector;

	std::vector<std::string> get_categories(std::string categories, int categories_num) {
		std::ifstream fin(categories);
		std::string line;
		std::vector<std::string> res(categories_num);
		if (!fin.is_open()) {
			std::cout << "failed to open 'categories'" << std::endl;
		}
		while (getline(fin, line)) {
			int category_id = 0;
			std::string id, name;
			int index = line.find(',');
			id = line.substr(0, index);
			name = line.substr(index + 1, line.size() - index - 1);
			category_id = std::stoi(id);
			res[category_id] = name;
		}
		return res;
	}

	std::vector<std::vector<std::string>> label_to_id(std::string list, int categories_num) {
		std::ifstream fin(list);
		std::string line;
		std::vector<std::vector<std::string>> res(categories_num);
		if (!fin.is_open()) {
			std::cout << "failed to open 'list'" << std::endl;
		}
		while (getline(fin, line)) {
			int category_id = 0;
			std::string id, file_name;
			int index = line.find(',');
			file_name = line.substr(0, index);
			id = line.substr(index + 1, line.size() - index - 1);
			//std::cout << id << "---------" <<file_name << std::endl;
			category_id = std::stoi(id);
			res[category_id].push_back(file_name);
		}
		return res;
	}
	bool is_Same(std::vector<int> input, int num) {
		for (auto it = input.cbegin(); it != input.cend(); ++it) {
			if (*it == num) {
				return true;
			}
		}
		return false;
		/*auto it = std::find(input.begin(), input.end(), num);
		if (it == input.end()) { return false; }
		else { return true; }*/
	}


};