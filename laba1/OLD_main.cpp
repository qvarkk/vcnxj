#include <windows.h>
#include <iostream>
#include <random>
#include <string>

class ArrayGenerator {
private:
	// Auxiliary array generator methods
	void GenerateSortedIntArray(int*, int, int, int);
	void GenerateReverseSortedIntArray(int*, int, int, int);
	void GenerateSortedDoubleArray(double*, int, double, double);
	void GenerateReverseSortedDoubleArray(double*, int, double, double);
	int GenerateRandomInt(int = 0, int = 1000);
	double GenerateRandomDouble(double = 0.0, double = 1000.0);
public:
	// Sorted arrays
	virtual void GenerateArray(int*, int, int, int, bool);
	virtual void GenerateArray(double*, int, double, double, bool);

	// Unsorted random arrays
	virtual void GenerateArray(int*, int, int, int);
	virtual void GenerateArray(double*, int, double, double);

	// Partially sorted arrays
	virtual void GenerateArray(int*, int, int, int, int, int);
	virtual void GenerateArray(double*, int, double, double, int, int);
};

#pragma region GenerateArray overloads

// Sorted int array
void ArrayGenerator::GenerateArray(int* arr, int size, int start, int step, bool reverse) {
	if (reverse) {
		GenerateReverseSortedIntArray(arr, size, start, step);
	} else {
		GenerateSortedIntArray(arr, size, start, step);
	}

}

// Sorted double array
void ArrayGenerator::GenerateArray(double* arr, int size, double start, double step, bool reverse) {
	if (reverse) {
		GenerateReverseSortedDoubleArray(arr, size, start, step);
	}
	else {
		GenerateSortedDoubleArray(arr, size, start, step);
	}
}

// Unsorted random int array
void ArrayGenerator::GenerateArray(int* arr, int size, int min, int max) {
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++) {
		arr[i] = GenerateRandomInt(min, max);
	}
}

// Unsorted random double array
void ArrayGenerator::GenerateArray(double* arr, int size, double min, double max) {
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++) {
		arr[i] = GenerateRandomDouble(min, max);
	}
}

// Partially sorted int array
void ArrayGenerator::GenerateArray(int *arr, int size, int start, int step, int unsortedLength, int sortedLength) {
	bool sorted = true;
	int  intervalLength = 0;
	for (int i = 0; i < size; i++) {
		if (sorted) {
			start += step;
			arr[i] = start;
			if (++intervalLength == sortedLength) {
				sorted = false;
				intervalLength = 0;
			}
		} else {
			arr[i] = GenerateRandomInt();
			start = arr[i];

			if (++intervalLength == unsortedLength) {
				sorted = true;
				intervalLength = 0;
			}
		}
	}
}

// Partially sorted double array
void ArrayGenerator::GenerateArray(double* arr, int size, double start, double step, int unsortedLength, int sortedLength) {
	bool sorted = true;
	int  intervalLength = 0;
	for (int i = 0; i < size; i++) {
		if (sorted) {
			start += step;
			arr[i] = start;
			if ((intervalLength++) == sortedLength) {
				sorted = false;
				intervalLength = 0;
			}
		}
		else {
			arr[i] = GenerateRandomDouble();
			start = arr[i];

			if ((intervalLength++) == unsortedLength) {
				sorted = true;
				intervalLength = 0;
			}
		}
	}
}

#pragma endregion

#pragma region auxiliary generators

void ArrayGenerator::GenerateSortedIntArray(int* arr, int size, int start, int step) {
	int val = start;
	for (int i = 0; i < size; i++) {
		val += step;
		arr[i] = val;
	}
}

void ArrayGenerator::GenerateReverseSortedIntArray(int* arr, int size, int start, int step) {
	int val = start;
	for (int i = 0; i < size; i++) {
		val -= step;
		arr[i] = val;
	}
}

void ArrayGenerator::GenerateSortedDoubleArray(double* arr, int size, double start, double step) {
	double val = start;
	for (int i = 0; i < size; i++) {
		val += step;
		arr[i] = val;
	}
}

void ArrayGenerator::GenerateReverseSortedDoubleArray(double* arr, int size, double start, double step) {
	double val = start;
	for (int i = 0; i < size; i++) {
		val -= step;
		arr[i] = val;
	}
}

int ArrayGenerator::GenerateRandomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

double ArrayGenerator::GenerateRandomDouble(double min, double max) {
	return min + ((double)rand() / RAND_MAX) * (max - min);
}

#pragma endregion

enum class Method { Sorted, Random, Partially };

void GenerateGivenIntArray(ArrayGenerator a, Method m, int* arr, int size, int min, int max, int start, int step, int unsortedLength, int sortedLength, bool reverse) {
	switch (m) {
	case Method::Sorted:
		a.GenerateArray(arr, size, start, step, reverse);
		break;
	case Method::Random:
		a.GenerateArray(arr, size, min, max);
		break;
	case Method::Partially:
		a.GenerateArray(arr, size, start, step, unsortedLength, sortedLength);
		break;
	}
}

void GenerateGivenDoubleArray(ArrayGenerator a, Method m, double* arr, int size, double min, double max, double start, double step, int unsortedLength, int sortedLength, bool reverse) {
	switch (m) {
	case Method::Sorted:
		a.GenerateArray(arr, size, start, step, reverse);
		break;
	case Method::Random:
		a.GenerateArray(arr, size, min, max);
		break;
	case Method::Partially:
		a.GenerateArray(arr, size, start, step, unsortedLength, sortedLength);
		break;
	}
}

int main(int argc, char** argv) {
	ArrayGenerator a;
	const int methodNum = 4, size = 50 * 10000;
	int** intArr = (int**)malloc(sizeof(int*) * methodNum);
	for (int i = 0; i < methodNum; i++) {
		intArr[i] = (int*)malloc(sizeof(int) * size);
	}

	double** doubleArr = (double**)malloc(sizeof(double*) * methodNum);
	for (int i = 0; i < methodNum; i++) {
		doubleArr[i] = (double*)malloc(sizeof(double) * size);
	}

	void (*intFuncs[])(ArrayGenerator, Method, int*, int, int, int, int, int, int, int, bool) = {
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray
	};

	void (*doubleFuncs[])(ArrayGenerator, Method, double*, int, double, double, double, double, int, int, bool) = { 
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray
	};

	DWORD startTime, endTime;
	
	startTime = GetTickCount64();

	(*intFuncs[0])(a, Method::Sorted, intArr[0], size, 0, 0, 1, 2, 0, 0, true); // sorted reverse
	(*intFuncs[1])(a, Method::Sorted, intArr[1], size, 0, 0, 1, 2, 0, 0, false); // sorted not reverse
	(*intFuncs[2])(a, Method::Partially, intArr[2], size, 0, 0, 1, 2, 5, 5, NULL); // partially sorted
	(*intFuncs[3])(a, Method::Random, intArr[3], size, 1, 100, 0, 0, 0, 0, NULL); // random unsorted

	(*doubleFuncs[0])(a, Method::Sorted, doubleArr[0], size, 0, 0, 100.6, 2.2, 0, 0, true);
	(*doubleFuncs[1])(a, Method::Sorted, doubleArr[1], size, 0, 0, 100.6, 2.2, 0, 0, false);
	(*doubleFuncs[2])(a, Method::Partially, doubleArr[2], size, 0, 0, 1.5, 2.2, 5, 5, NULL);
	(*doubleFuncs[3])(a, Method::Random, doubleArr[3], size, 1, 100, 0, 0, 0, 0, NULL);
	
	endTime = GetTickCount64();

	std::cout << startTime << " --- " << endTime << std::endl;
	std::cout << endTime - startTime  << std::endl;

/*	std::string methodsNames[4] = {"sorted reverse", "normal sorted", "partially sorted", "random unsorted"};

	for (int i = 0; i < methodNum; i++) {
		std::cout << "Method: " << methodsNames[i] << "." << std::endl;
		std::cout << "Type: int." << std::endl;
		for (int j = 0; j < size; j++) {
			std::cout << intArr[i][j] << ", ";
		}
		std::cout << "\b\b.\n" << std::endl;

		std::cout << "Type: double." << std::endl;
		for (int j = 0; j < size; j++) {
			std::cout << doubleArr[i][j] << ", ";
		}
		std::cout << "\b\b.\n\n" << std::endl;
	}*/

	return 0;
}