#include <windows.h>
#include <iostream>
#include <random>
#include <string>

enum class Method { Sorted, Random, Partially };

class ArrayGenerator {
private:
	// Auxiliary array generator methods
	void GenerateSortedIntArray(int*, int);
	void GenerateReverseSortedIntArray(int*, int);
	void GenerateSortedDoubleArray(double*, int);
	void GenerateReverseSortedDoubleArray(double*, int);
	void GenerateRandomIntArray(int*, int);
	void GenerateRandomDoubleArray(double*, int);
	void GeneratePartialIntArray(int*, int);
	void GeneratePartialDoubleArray(double*, int);
	int GenerateRandomInt(int = 0, int = 1000);
	double GenerateRandomDouble(double = 0.0, double = 1000.0);
public:
	// Sorted arrays
	virtual void GenerateArray(int*, int, bool);
	virtual void GenerateArray(double*, int, bool);

	// Unsorted and partially sorted random arrays
	virtual void GenerateArray(int*, int, Method);
	virtual void GenerateArray(double*, int, Method);
};

#pragma region GenerateArray overloads

// Sorted int array
void ArrayGenerator::GenerateArray(int* arr, int size, bool reverse) {
	if (reverse) {
		GenerateReverseSortedIntArray(arr, size);
	}
	else {
		GenerateSortedIntArray(arr, size);
	}

}

// Sorted double array
void ArrayGenerator::GenerateArray(double* arr, int size, bool reverse) {
	if (reverse) {
		GenerateReverseSortedDoubleArray(arr, size);
	}
	else {
		GenerateSortedDoubleArray(arr, size);
	}
}

// Unsorted random or partially sorted int array
void ArrayGenerator::GenerateArray(int* arr, int size, Method m) {
	switch (m) {
	case Method::Random:
		GenerateRandomIntArray(arr, size);
		break;
	case Method::Partially:
		GeneratePartialIntArray(arr, size);
		break;
	}
}

// Unsorted random or partially sorted double array
void ArrayGenerator::GenerateArray(double* arr, int size, Method m) {
	switch (m) {
	case Method::Random:
		GenerateRandomDoubleArray(arr, size);
		break;
	case Method::Partially:
		GeneratePartialDoubleArray(arr, size);
		break;
	}
}

#pragma endregion

#pragma region auxiliary generators

void ArrayGenerator::GenerateSortedIntArray(int* arr, int size) {
	int val = 100;
	for (int i = 0; i < size; i++) {
		val += 2;
		arr[i] = val;
	}
}

void ArrayGenerator::GenerateReverseSortedIntArray(int* arr, int size) {
	int val = 100;
	for (int i = 0; i < size; i++) {
		val -= 2;
		arr[i] = val;
	}
}

void ArrayGenerator::GenerateSortedDoubleArray(double* arr, int size) {
	double val = 100.678;
	for (int i = 0; i < size; i++) {
		val += 2.35;
		arr[i] = val;
	}
}

void ArrayGenerator::GenerateReverseSortedDoubleArray(double* arr, int size) {
	double val = 100.678;
	for (int i = 0; i < size; i++) {
		val -= 2.35;
		arr[i] = val;
	}
}

void ArrayGenerator::GenerateRandomIntArray(int* arr, int size) {
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++) {
		arr[i] = GenerateRandomInt();
	}
}

void ArrayGenerator::GenerateRandomDoubleArray(double* arr, int size) {
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++) {
		arr[i] = GenerateRandomDouble();
	}
}

void ArrayGenerator::GeneratePartialIntArray(int* arr, int size) {
	bool sorted = true;
	int  intervalLength = 0;
	int unsortedLength = 5, sortedLength = 5;
	int start = 100;
	for (int i = 0; i < size; i++) {
		if (sorted) {
			start += 5;
			arr[i] = start;
			if (++intervalLength == sortedLength) {
				sorted = false;
				intervalLength = 0;
			}
		}
		else {
			arr[i] = GenerateRandomInt();
			start = arr[i];

			if (++intervalLength == unsortedLength) {
				sorted = true;
				intervalLength = 0;
			}
		}
	}
}

void ArrayGenerator::GeneratePartialDoubleArray(double* arr, int size) {
	bool sorted = true;
	int  intervalLength = 0;
	int unsortedLength = 5, sortedLength = 5;
	double start = 100.678;
	for (int i = 0; i < size; i++) {
		if (sorted) {
			start += 2.35;
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

int ArrayGenerator::GenerateRandomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

double ArrayGenerator::GenerateRandomDouble(double min, double max) {
	return min + ((double)rand() / RAND_MAX) * (max - min);
}

#pragma endregion

void GenerateGivenIntArray(ArrayGenerator a, Method m, int* arr, int size, bool reverse) {
	switch (m) {
	case Method::Sorted:
		a.GenerateArray(arr, size, reverse);
		break;
	case Method::Random:
		a.GenerateArray(arr, size, m);
		break;
	case Method::Partially:
		a.GenerateArray(arr, size, m);
		break;
	}
}

void GenerateGivenDoubleArray(ArrayGenerator a, Method m, double* arr, int size, bool reverse) {
	switch (m) {
	case Method::Sorted:
		a.GenerateArray(arr, size, reverse);
		break;
	case Method::Random:
		a.GenerateArray(arr, size, m);
		break;
	case Method::Partially:
		a.GenerateArray(arr, size, m);
		break;
	}
}

void AllocateArrays(int*** intArr, double*** doubleArr, int size, int methodNum) {
	*intArr = (int**)malloc(sizeof(int*) * methodNum);
	for (int i = 0; i < methodNum; i++) {
		(*intArr)[i] = (int*)malloc(sizeof(int) * size);
	}

	*doubleArr = (double**)malloc(sizeof(double*) * methodNum);
	for (int i = 0; i < methodNum; i++) {
		(*doubleArr)[i] = (double*)malloc(sizeof(double) * size);
	}
}

ULONGLONG MeasureTime(void* (*intFuncs[])(ArrayGenerator, Method, int*, int, bool), void* (*doubleFuncs[])(ArrayGenerator, Method, double*, int, bool), ArrayGenerator a, int*** intArr, double*** doubleArr, int size) {
	ULONGLONG startTime, endTime;

	startTime = GetTickCount64();

	(*(*intFuncs[0]))(a, Method::Sorted, (*intArr)[0], size, true); // sorted reverse
	(*(*intFuncs[1]))(a, Method::Sorted, (*intArr)[1], size, false); // sorted not reverse
	(*(*intFuncs[2]))(a, Method::Partially, (*intArr)[2], size, NULL); // partially sorted
	(*(*intFuncs[3]))(a, Method::Random, (*intArr)[3], size, NULL); // random unsorted

	(*(*doubleFuncs[0]))(a, Method::Sorted, (*doubleArr)[0], size, true);
	(*(*doubleFuncs[0]))(a, Method::Sorted, (*doubleArr)[1], size, false);
	(*(*doubleFuncs[0]))(a, Method::Partially, (*doubleArr)[2], size, NULL);
	(*(*doubleFuncs[0]))(a, Method::Random, (*doubleArr)[3], size, NULL);

	endTime = GetTickCount64();

	std::cout << startTime << " --- " << endTime << std::endl;
	std::cout << endTime - startTime << std::endl;

	return endTime - startTime;
}

int main(int argc, char** argv) {
	ArrayGenerator a;
	const int methodNum = 4;
	int size = 5 * 10000;
	int** intArr = NULL;
	double** doubleArr = NULL;

	AllocateArrays(&intArr, &doubleArr, size, methodNum);

	void (*intFuncs[])(ArrayGenerator, Method, int*, int, bool) = {
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray
	};

	void (*doubleFuncs[])(ArrayGenerator, Method, double*, int, bool) = {
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray
	};

	DWORD startTime, endTime;

	startTime = GetTickCount64();

	(*intFuncs[0])(a, Method::Sorted, intArr[0], size, true); // sorted reverse
	(*intFuncs[1])(a, Method::Sorted, intArr[1], size, false); // sorted not reverse
	(*intFuncs[2])(a, Method::Partially, intArr[2], size, NULL); // partially sorted
	(*intFuncs[3])(a, Method::Random, intArr[3], size, NULL); // random unsorted

	(*doubleFuncs[0])(a, Method::Sorted, doubleArr[0], size, true);
	(*doubleFuncs[1])(a, Method::Sorted, doubleArr[1], size, false);
	(*doubleFuncs[2])(a, Method::Partially, doubleArr[2], size, NULL);
	(*doubleFuncs[3])(a, Method::Random, doubleArr[3], size, NULL);

	endTime = GetTickCount64();

	std::cout << startTime << " --- " << endTime << std::endl;
	std::cout << endTime - startTime << std::endl;

	

	bool print = false;
	if (print) {
		std::string methodsNames[4] = { "sorted reverse", "normal sorted", "partially sorted", "random unsorted" };

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
		}
	}

	return 0;
}