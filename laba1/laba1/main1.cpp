#include <windows.h>
#include <iostream>
#include <random>
#include <string>
#include <math.h>

#define METHOD_NUM 7

enum class Method { Sorted, Random, Sawtoothed, Sinusoidal, Stepped, QuasiSorted };

class ArrayGenerator {
public:
	// Auxiliary array generator methods
	void GenerateSortedIntArray(int*, int);
	void GenerateReverseSortedIntArray(int*, int);

	void GenerateSortedDoubleArray(double*, int);
	void GenerateReverseSortedDoubleArray(double*, int);

	void GenerateRandomIntArray(int*, int);
	void GenerateRandomDoubleArray(double*, int);

	void GenerateSawtoothedIntArray(int*, int);
	void GenerateSawtoothedDoubleArray(double*, int);

	void GenerateSinusoidalIntArray(int*, int);
	void GenerateSinusoidalDoubleArray(double*, int);

	void GenerateSteppedIntArray(int*, int);
	void GenerateSteppedDoubleArray(double*, int);

	void GenerateQuasiSortedIntArray(int*, int);
	void GenerateQuasiSortedDoubleArray(double*, int);

	int GenerateRandomInt(int = 0, int = 1000);
	double GenerateRandomDouble(double = 0.0, double = 1000.0);
//public:
	// Sorted arrays
	virtual void GenerateArray(int*, int, bool);
	virtual void GenerateArray(double*, int, bool);

	// Unsorted random arrays
	virtual void GenerateArray(int*, int);
	virtual void GenerateArray(double*, int);

	// Partially sorted arrays
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

// Unsorted random int array
void ArrayGenerator::GenerateArray(int* arr, int size) {
	GenerateRandomIntArray(arr, size);
}

// Unsorted random double array
void ArrayGenerator::GenerateArray(double* arr, int size) {
	GenerateRandomDoubleArray(arr, size);
}

void ArrayGenerator::GenerateArray(int* arr, int size, Method m) {
	switch (m) {
	case Method::Sawtoothed:
		GenerateSawtoothedIntArray(arr, size);
		break;
	case Method::Sinusoidal:
		GenerateSinusoidalIntArray(arr, size);
		break;
	case Method::Stepped:
		GenerateSteppedIntArray(arr, size);
		break;
	case Method::QuasiSorted:
		GenerateQuasiSortedIntArray(arr, size);
		break;
	}
}

void ArrayGenerator::GenerateArray(double* arr, int size, Method m) {
	switch (m) {
	case Method::Sawtoothed:
		GenerateSawtoothedDoubleArray(arr, size);
		break;
	case Method::Sinusoidal:
		GenerateSinusoidalDoubleArray(arr, size);
		break;
	case Method::Stepped:
		GenerateSteppedDoubleArray(arr, size);
		break;
	case Method::QuasiSorted:
		GenerateQuasiSortedDoubleArray(arr, size);
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

void ArrayGenerator::GenerateSawtoothedIntArray(int* arr, int size) {
	int value = 10;

	for (int i = 0; i < size; i++) {
		if (GenerateRandomInt() < 250) {
			value = 10;
		}
		arr[i] = value;
		value += GenerateRandomInt(1, 5);
	}
}

void ArrayGenerator::GenerateSawtoothedDoubleArray(double* arr, int size) {
	double value = 9.6;

	for (int i = 0; i < size; i++) {
		if (GenerateRandomInt() < 250) {
			value = 9.6;
		}
		arr[i] = value;
		value += GenerateRandomDouble(1, 5);
	}
}

void ArrayGenerator::GenerateSinusoidalIntArray(int* arr, int size) {
	// f(x) = amplitude * sin(2 * PI * frequency * x + shift)
	for (int i = 1; i <= size; i++) {
		arr[i - 1] = int(100 * sin(2 * std::_Pi * 0.05 * i + 500));
	}
}

void ArrayGenerator::GenerateSinusoidalDoubleArray(double* arr, int size) {
	for (int i = 1; i <= size; i++) {
		arr[i - 1] = 100 * sin(2 * std::_Pi * 0.05 * i + 500);
	}
}

void ArrayGenerator::GenerateSteppedIntArray(int* arr, int size) {
	int min = 10;
	int value = min;

	for (int i = 0; i < size; i++) {
		if (GenerateRandomInt() < 250) {
			value = int(min * GenerateRandomDouble(1, 1.2));
		}
		arr[i] = value;
		value += GenerateRandomInt(-5, 5);
		if (value > min) {
			min = value;
		}
	}
}

void ArrayGenerator::GenerateSteppedDoubleArray(double* arr, int size) {
	double min = 10;
	double value = min;

	for (int i = 0; i < size; i++) {
		if (GenerateRandomInt() < 250) {
			value = min * GenerateRandomDouble(1, 1.2);
		}
		arr[i] = value;
		value += GenerateRandomInt(-5, 5);
		if (value > min) {
			min = value;
		}
	}
}

void ArrayGenerator::GenerateQuasiSortedIntArray(int* arr, int size) {
	int value = 10;
	int inversions = size / 5;

	for (int i = 0; i < size; i++) {
		if (GenerateRandomInt() < 250 && inversions > 0) {
			arr[i] = GenerateRandomInt();
			--inversions;
		} else {
			arr[i] = value;
			value += GenerateRandomInt(1, 5);
		}
	}
}

void ArrayGenerator::GenerateQuasiSortedDoubleArray(double* arr, int size) {
	double value = 10;
	int inversions = size / 5;

	for (int i = 0; i < size; i++) {
		if (GenerateRandomInt() < 250 && inversions > 0) {
			arr[i] = GenerateRandomDouble();
			--inversions;
		}
		else {
			arr[i] = value;
			value += GenerateRandomDouble(1, 5);
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
		a.GenerateArray(arr, size);
		break;
	case Method::Sawtoothed:
		a.GenerateArray(arr, size, m);
		break;
	case Method::Sinusoidal:
		a.GenerateArray(arr, size, m);
		break;
	case Method::Stepped:
		a.GenerateArray(arr, size, m);
		break;
	case Method::QuasiSorted:
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
		a.GenerateArray(arr, size);
		break;
	case Method::Sawtoothed:
		a.GenerateArray(arr, size, m);
		break;
	case Method::Sinusoidal:
		a.GenerateArray(arr, size, m);
		break;
	case Method::Stepped:
		a.GenerateArray(arr, size, m);
		break;
	case Method::QuasiSorted:
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

void PrintTime(DWORD arr[]) {
	std::string methodsNames[METHOD_NUM] = { "normal sorted", "sorted reverse", "random unsorted", "sawtoothed", "sinusoidal", "stepped", "quasi sorted" };

	for (int i = 0; i < METHOD_NUM; i++) {
		std::cout << methodsNames[i] << ": ";
		std::cout << arr[i] << "." << std::endl;
	}
}

void MeasureTime(int size, bool print = false) {
	ArrayGenerator a;
	int** intArr = NULL;
	double** doubleArr = NULL;

	AllocateArrays(&intArr, &doubleArr, size, METHOD_NUM);

	void (*intFuncs[])(ArrayGenerator, Method, int*, int, bool) = {
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray,
		GenerateGivenIntArray
	};

	void (*doubleFuncs[])(ArrayGenerator, Method, double*, int, bool) = {
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray,
		GenerateGivenDoubleArray
	};

	DWORD intStartTime[METHOD_NUM], intEndTime[METHOD_NUM], intResultTime[METHOD_NUM];

	intStartTime[0] = GetTickCount64();
	(*intFuncs[0])(a, Method::Sorted, intArr[0], size, false);
	intEndTime[0] = GetTickCount64();
	intResultTime[0] = intEndTime[0] - intStartTime[0];

	intStartTime[1] = GetTickCount64();
	(*intFuncs[1])(a, Method::Sorted, intArr[1], size, true);
	intEndTime[1] = GetTickCount64();
	intResultTime[1] = intEndTime[1] - intStartTime[1];

	intStartTime[2] = GetTickCount64();
	(*intFuncs[2])(a, Method::Random, intArr[2], size, NULL);
	intEndTime[2] = GetTickCount64();
	intResultTime[2] = intEndTime[2] - intStartTime[2];

	intStartTime[3] = GetTickCount64();
	(*intFuncs[3])(a, Method::Sawtoothed, intArr[3], size, NULL);
	intEndTime[3] = GetTickCount64();
	intResultTime[3] = intEndTime[3] - intStartTime[3];

	intStartTime[4] = GetTickCount64();
	(*intFuncs[4])(a, Method::Sinusoidal, intArr[4], size, NULL);
	intEndTime[4] = GetTickCount64();
	intResultTime[4] = intEndTime[4] - intStartTime[4];

	intStartTime[5] = GetTickCount64();
	(*intFuncs[5])(a, Method::Stepped, intArr[5], size, NULL);
	intEndTime[5] = GetTickCount64();
	intResultTime[5] = intEndTime[5] - intStartTime[5];

	intStartTime[6] = GetTickCount64();
	(*intFuncs[6])(a, Method::QuasiSorted, intArr[6], size, NULL);
	intEndTime[6] = GetTickCount64();
	intResultTime[6] = intEndTime[6] - intStartTime[6];

	DWORD doubleStartTime[METHOD_NUM], doubleEndTime[METHOD_NUM], doubleResultTime[METHOD_NUM];

	doubleStartTime[0] = GetTickCount64();
	(*doubleFuncs[0])(a, Method::Sorted, doubleArr[0], size, false);
	doubleEndTime[0] = GetTickCount64();
	doubleResultTime[0] = doubleEndTime[0] - doubleStartTime[0];

	doubleStartTime[1] = GetTickCount64();
	(*doubleFuncs[1])(a, Method::Sorted, doubleArr[1], size, true);
	doubleEndTime[1] = GetTickCount64();
	doubleResultTime[1] = doubleEndTime[1] - doubleStartTime[1];

	doubleStartTime[2] = GetTickCount64();
	(*doubleFuncs[2])(a, Method::Random, doubleArr[2], size, NULL);
	doubleEndTime[2] = GetTickCount64();
	doubleResultTime[2] = doubleEndTime[2] - doubleStartTime[2];

	doubleStartTime[3] = GetTickCount64();
	(*doubleFuncs[3])(a, Method::Sawtoothed, doubleArr[3], size, NULL);
	doubleEndTime[3] = GetTickCount64();
	doubleResultTime[3] = doubleEndTime[3] - doubleStartTime[3];
	
	doubleStartTime[4] = GetTickCount64();
	(*doubleFuncs[4])(a, Method::Sinusoidal, doubleArr[4], size, NULL);
	doubleEndTime[4] = GetTickCount64();
	doubleResultTime[4] = doubleEndTime[4] - doubleStartTime[4];

	doubleStartTime[5] = GetTickCount64();
	(*doubleFuncs[5])(a, Method::Stepped, doubleArr[5], size, NULL);
	doubleEndTime[5] = GetTickCount64();
	doubleResultTime[5] = doubleEndTime[5] - doubleStartTime[5];

	doubleStartTime[6] = GetTickCount64();
	(*doubleFuncs[6])(a, Method::QuasiSorted, doubleArr[6], size, NULL);
	doubleEndTime[6] = GetTickCount64();
	doubleResultTime[6] = doubleEndTime[6] - doubleStartTime[6];

	std::cout << "\n\n\tSIZE: " << size << std::endl;
	std::cout << "TYPE: int" << std::endl;
	PrintTime(intResultTime);
	std::cout << "\nTYPE: double" << std::endl;
	PrintTime(doubleResultTime);

	if (print) {
		std::string methodsNames[METHOD_NUM] = {  "normal sorted", "sorted reverse", "random unsorted", "sawtoothed", "sinusoidal", "stepped", "quasi sorted" };

		for (int i = 0; i < METHOD_NUM; i++) {
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

	for (int i = 0; i < METHOD_NUM; i++) {
		delete intArr[i];
	}
	delete intArr;

	for (int i = 0; i < METHOD_NUM; i++) {
		delete doubleArr[i];
	}
	delete doubleArr;
}

int main(int argc, char** argv) {
	MeasureTime(10000);
	MeasureTime(5 * 10000);
	MeasureTime(100000);
	MeasureTime(5 * 100000);
	MeasureTime(100000);
	MeasureTime(5 * 100000);
	MeasureTime(1000000);
	MeasureTime(5 * 1000000);
	MeasureTime(10000000);
	MeasureTime(5 * 10000000);

	return 0;
}