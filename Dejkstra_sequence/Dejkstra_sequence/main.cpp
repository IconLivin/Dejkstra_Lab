#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#define MAX_PATH 10000

void Generate_matrix(std::vector<std::vector<int>> &matr, int size) {
	matr.resize(size);
	for (size_t i = 0; i < matr.size(); ++i) {
		matr[i].resize(size);
	}
	for (size_t i = 0; i < matr.size(); ++i) {
		for (size_t j = i + 1; j < matr.size(); ++j) {
			int num = rand() % 100;
			matr[i][j] = num;
			matr[j][i] = num;
		}

	}
}

void Print_Matrix(const std::vector<std::vector<int>> &matrix) {
	
	if (matrix.size() <= 30) {
		for (const auto &row : matrix) {
			for (const auto &num : row) {
				std::cout <<std::setw(5) << num << " ";
			}
			std::cout << std::endl;
		}
	}
	else{
		std::ofstream ofs;
		ofs.open("matrix.txt");
		for (const auto &row : matrix) {
			for (const auto &num : row) {
				ofs << num << " ";
			}
			ofs << std::endl;
		}
	}
}

void Input_Matrix(std::vector<std::vector<int>> &matr, int size) {
	matr.resize(size);
	for (size_t i = 0; i < matr.size(); ++i) {
		matr[i].resize(size);
	}
	for (size_t i = 0; i < matr.size(); ++i) {
		for (size_t j = i + 1; j < matr.size(); ++j) {
			int num;
			std::cout << "Insert distance " << i + 1 << "-" << j + 1 << ":";
			std::cin >> num;
			matr[i][j] = num;
			matr[j][i] = num;
		}

	}
}

int main() {
	int t;
	std::vector<std::vector<int>> matr;
	std::cout << "Insert peaks count:";
	std::cin >> t;
	while (t < 1) {
		std::cout << "Peaks number can't be less than 1!\nInsert correct peaks count:";
		std::cin >> t;
	}
	int key = 1;
	
	std::cout << "Input matrix by yourself [1] [default]:\nGenerate matrix [2] :\n\nChoose one option:";
	std::cin >> key;
	key = key != 2 ? 1 : 0;
	if (key) {
		Input_Matrix(matr, t);
	}
	else Generate_matrix(matr, t);
		
	std::vector<int> visited(t, 1);
	std::vector<int> min_path(t, MAX_PATH);
	Print_Matrix(matr);
	int begin_index;
	std::cout << "Insert peak number:";
	std::cin >> begin_index;
	while (begin_index >= matr.size()) {
		std::cout << "Index can't be more than:" << matr.size() << "\nInsert correct peak number [0, " << matr.size() - 1 << "]:";
		std::cin >> begin_index;
	}
	min_path[begin_index] = 0;
	int min_index, min;
	do {
		min_index = MAX_PATH;
		min = MAX_PATH;
		for (size_t i = 0; i < visited.size(); ++i) {
			if (visited[i] == 1 && (min_path[i] < min)) {
				min = min_path[i];
				min_index = i;
			}
		}
		if (min_index != MAX_PATH) {
			for (size_t i = 0; i < visited.size(); ++i) {
				if (matr[min_index][i] > 0) {
					int temp = min + matr[min_index][i];
					if (temp < min_path[i]) {
						min_path[i] = temp;
					}
				}
			}
			visited[min_index] = 0;
		}
	} while (min_index < MAX_PATH);

	for (const auto row : min_path) {
		std::cout << row << " ";
	}
	std::cout << std::endl;
	return 0;
}