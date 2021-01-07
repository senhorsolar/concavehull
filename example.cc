#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <span>
#include <vector>

#include "concavehull.hpp"

using namespace std;

//
// Writes vector to file with a given delimiter
//
template<class T>
void write_vector(const std::vector<T>& vec, std::string filename, char delimiter='\n') {
	std::ofstream out;
	out.open(filename);
	
	bool write_sep = false;
	for (const auto& e: vec) {
		if (write_sep)
			out << delimiter;
		else
			write_sep = true;
		out << e;
		std::cout << "";
	}

	out.close();
}

//
// Generates a random vector<double> with given bounds and length
//
std::vector<double> randn(unsigned lower_bound, unsigned upper_bound, size_t size) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(lower_bound, upper_bound);

	std::vector<double> v(size);
	
	for (size_t i = 0; i < size; i++) {
		v[i] = dis(gen);
	}
	
	return v;
}

int main(int argc, char** argv) {

	double lower_bound = 0;
	double upper_bound = 2;

	size_t size = 100;
	if (argc > 1) {
		size = atoi(argv[1]);
	}

	double chi_factor = 0.2;
	if (argc > 2) {
		chi_factor = atof(argv[2]);
	}

	cout << "Chi factor: " << chi_factor << '\n';

	vector<double> coords = randn(lower_bound, upper_bound, size);
	
	delaunator::Delaunator d(coords);
	vector<double> convexhull = d.get_hull_coords();

	clock_t start = std::clock();
	vector<double> chihull = concavehull(coords, chi_factor);
	double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

	cout << "Time to find concave hull: " << duration << '\n';
	
	write_vector(convexhull, "convexhull.txt");
	write_vector(chihull, "concavehull.txt");
	write_vector(coords, "coords.txt");
	
	return 0;
}
