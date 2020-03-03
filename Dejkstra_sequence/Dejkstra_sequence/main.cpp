#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <random>
#include <ctime>
#include <string>
#include <python.h>

#define MAX_PATH 1000000000000000000

void Generate_matrix(std::vector<std::vector<int>> &matr, int size) {
	matr.resize(size);
	for (size_t i = 0; i < matr.size(); ++i) {
		matr[i].resize(size);
	}
	std::mt19937 random(static_cast<unsigned int>(time(0)));
	for (size_t i = 0; i < matr.size(); ++i) {
		for (size_t j = i + 1; j < matr.size(); ++j) {
			int num = random() % 100;
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

void Generate_Connected_Graph(std::vector<std::vector<int>> &matr,const int& size) {
	std::ofstream out;
	out.open("../../graph.txt");
	out << size;
	out.close();
	Py_SetProgramName(L"../../ss.py");
	Py_Initialize();
	PyRun_SimpleFile(fopen("../../ss.py", "r"), "ss.py");
	matr.resize(size);
	for (size_t i = 0; i < matr.size(); ++i) {
		matr[i].resize(size, 0);
	}
	std::ifstream in;
	in.open("graph.txt");
	int x, y, weight;
	while (in >> x >> y >> weight) {
		matr[x][y] = matr[y][x] = weight;
	}
	in.close();
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
	
	std::cout << "Input matrix by yourself [1] [default]:\nGenerate matrix(Full graph) [2] :\nGenerate connected graph [3]:\n\nChoose one option:";
	std::cin >> key;
	switch (key) {
	case 2:
		Generate_matrix(matr, t);
		break;
	case 3:
		Generate_Connected_Graph(matr, t);
		break;
	default:
		Input_Matrix(matr, t);
	}

	std::vector<uint64_t> visited(t, 1);
	std::vector<uint64_t> min_path(t, MAX_PATH);
	Print_Matrix(matr);
	int begin_index;
	std::cout << "Insert peak number:";
	std::cin >> begin_index;
	while (begin_index >= matr.size()) {
		std::cout << "Index can't be more than:" << matr.size() << "\nInsert correct peak number [0, " << matr.size() - 1 << "]:";
		std::cin >> begin_index;
	}
	min_path[begin_index] = 0;
	uint64_t min_index, min;
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
	//if (min_path.size() < 20) {
		for (const auto row : min_path) {
			std::cout << row << " ";
		}
		std::cout << std::endl;
	//}
	//else {
		//std::ofstream out;
	//	out.open("result.txt");
	//	for(int i=0;i<min_path.size();++i)
	//		out << min_path[i] << " ";
	//	out << std::endl;
	//}
	return 0;
}