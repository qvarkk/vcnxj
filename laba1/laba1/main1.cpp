#include <windows.h>
#include <iostream>
#include <random>
#include <stdarg.h>

enum Type {Int, Double};
enum Method {Sorted, Partially, Unsorted};

class ArrayGenerator {
public:
	virtual void GenerateArray(int*, int, int, int, Method);
	virtual void GenerateArray(double*, int, double, double, Method);
	virtual void GenerateArray(int*, int, int, int, int);
	virtual void GenerateArray(double*, int, double, double, double);
	void GenerateSortedIntArray(int*, int, int, int);
	void GenerateUnsortedIntArray(int*, int, int, int);
	void GenerateSortedDoubleArray(double*, int, double, double);
	void GenerateUnsortedDoubleArray(double*, int, double, double);
};

// sorted or unsorted
void ArrayGenerator::GenerateArray(int* arr, int size, int min, int max, Method m) {
	switch (m) {
	case Sorted:
		GenerateSortedIntArray(arr, size, min, max);
		break;
	case Unsorted:
		GenerateUnsortedIntArray(arr, size, min, max);
		break;
	}
}

// sorted or unsorted
void ArrayGenerator::GenerateArray(double* arr, int size, double min, double max, Method m) {
	switch(m) {
	case Sorted:
		GenerateSortedDoubleArray(arr, size, min, max);
		break;
	case Unsorted:
		GenerateUnsortedDoubleArray(arr, size, min, max);
		break;
	}
}

// partially sorted
void ArrayGenerator::GenerateArray(int* arr, int size, int min, int max, int step) {
}

// partially sorted
void ArrayGenerator::GenerateArray(double* arr, int size, double min, double max, double step) {
}

void ArrayGenerator::GenerateSortedIntArray(int* arr, int size, int min, int max) {
}

void ArrayGenerator::GenerateUnsortedIntArray(int* arr, int size, int min, int max) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		arr[i] = (rand() % (max - min + 1) + min);
	}
}

void ArrayGenerator::GenerateSortedDoubleArray(double* arr, int size, double min, double max) {
}


void ArrayGenerator::GenerateUnsortedDoubleArray(double* arr, int size, double min, double max) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		arr[i] = min + ((double)rand() / RAND_MAX) * (max - min);
	}
}

int main(int argc, char** argv) {
	ArrayGenerator a;
	int size = 10, min = 0, max = 10000;
	double* arr = (double*)malloc(sizeof(double) * size);
	a.GenerateArray(arr, size, min, max, Unsorted);
//	for (int i = 0; i < size; i++) {
//		std::cout << arr[i] << std::endl;
//	}

	return 0;
}