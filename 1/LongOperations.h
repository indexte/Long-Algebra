#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

//Деление для отрицательных чисел
int my_div(int num, int diver) {
	if ((num < 0) && (num % diver))
		return num / diver - 1;
	else
		return num / diver;
}
//Взятие по модулю для отрицательных чисел
int my_mod(int num, int diver) {
	if ((num < 0) && (num % diver))
		return num % diver + diver;
	else
		return num % diver;
}

//Класс "большое число", описывает способ хранения большого числа и
//длинную арифметику
class BigNumber {
private:
	/*VALUES*/
	vector<int> chunks;
	int sign;
	int BASE = 10;
	int N = 0;

	/*HELPERS*/
	BigNumber _plus(BigNumber &a);
	BigNumber _minus(BigNumber &a);
	BigNumber _simplemulti(BigNumber &num);	//TODO
	BigNumber _multi(BigNumber &num);		//TODO

	bool _greater();
	void _modN();
	void _normalizationSigns();
	void _normalizationChunks();
	void _resize(int newsize);

public:
	/*OPERATIONS*/
	bool operator >= (BigNumber &num);
	bool operator > (BigNumber &num);
	BigNumber operator + (BigNumber &num);
	BigNumber operator - (BigNumber &num);
	BigNumber operator * (BigNumber &num); //TODO

	/*GETTERS SETTERS*/
	int getBASE() {
		return this->BASE;
	}
	int getN() {
		return this->N;
	}
	void printBigNumber();

	//Конструктор
	BigNumber(string str, int n) {
		this->N = n;
		int i;
		for (i = str.size() - 1; i > 0; i--) {
			chunks.push_back((str[i]) - '0');
		}

		//check sign
		if (str[0] == '-') {
			sign = -1;
		}
		else {
			sign = 1;
			chunks.push_back((str[i]) - '0');
		}

		_modN();

	}
	BigNumber(int N) {
		sign = 1;
		this->N = N;
	}
};

//Изменение размера массива с чанками
void BigNumber::_resize(int newSize) {
	chunks.resize(newSize);
}

void BigNumber::printBigNumber() {
	if (sign == -1) {
		cout << '-';
	}
	for (int i = chunks.size() - 1; i >= 0; i--) {
		cout << chunks[i];
	}
	cout << endl;
}

//Оператор >, 

bool BigNumber::operator > (BigNumber &num) {
	if (sign > num.sign) {
		return true;
	}
	if (sign < num.sign) {
		return false;
	}
	if (this->chunks.size() > num.chunks.size()) {
		if (sign == 1) return true;
		else return false;
	}
	if (this->chunks.size() < num.chunks.size()) {
		if (sign == 1) return false;
		else return true;
	}

	for (int i = 0; i < this->chunks.size(); i++) {
		if (this->chunks[i] > num.chunks[i]) return true;
		if (this->chunks[i] < num.chunks[i]) return false;
	}

	return false;
}

bool BigNumber::operator >= (BigNumber &num) {
	if (sign > num.sign) {
		return true;
	}
	if (sign < num.sign) {
		return false;
	}
	if (this->chunks.size() > num.chunks.size()) {
		if (sign == 1) return true;
		else return false;
	}
	if (this->chunks.size() < num.chunks.size()) {
		if (sign == 1) return false;
		else return true;
	}

	for (int i = 0; i < this->chunks.size(); i++) {
		if (this->chunks[i] > num.chunks[i]) return true;
		if (this->chunks[i] < num.chunks[i]) return false;
	}

	return true;
}

void BigNumber::_normalizationChunks() {
	int over = 0;
	for (int i = 0; i < chunks.size() - 1; i++) {
		chunks[i] += over;
		over = my_div(chunks[i], BASE);
		chunks[i] = my_mod(chunks[i], BASE);
	}

	chunks[chunks.size() - 1] += over;
	if (chunks[chunks.size() - 1] / BASE) {
		over = my_div(chunks[chunks.size() - 1], BASE);
		chunks[chunks.size() - 1] = my_mod(chunks[chunks.size() - 1], BASE);
		chunks.push_back(over);
	}
	return;
}

void BigNumber::_normalizationSigns() {

	//Если в последней чанке отрицательное число
	if (chunks[chunks.size() - 1] < 0) {
		sign = -sign;

		chunks[0] = BASE - chunks[0];
		for (int i = 1; i < chunks.size(); i++) {
			chunks[i] = (BASE - chunks[i] - 1) % BASE;
		}
	}

	//Убираем из числа нулевые чанки
	int i = chunks.size() - 1;
	while (chunks[i] == 0) {
		if (i == 0) {
			sign = 1;
			return;
		}
		chunks.pop_back();
		i--;
	}
	return;
}


void  BigNumber::_modN() {
	if (N != 0) { //выравнивание по модулю
		BigNumber N_(std::to_string(N), 0);
		if (sign == 1) {
			while (*this >= N_) {
				*this = *this - N_;
			}
		}
		else {
			BigNumber Nul("0", 0);
			while (Nul > *this) {
				*this = *this + N_;
			}
		}
	}
}
//Функция сложения
BigNumber BigNumber::_plus(BigNumber &num) {
	BigNumber res(N);
	res.sign = this->sign;
	for (int i = 0; i < this->chunks.size(); i++) {
		res.chunks.push_back(this->sign*this->chunks[i] + num.sign* num.chunks[i]);
	}
	return res;
}

//Функция вычитания
BigNumber BigNumber::_minus(BigNumber &num) {
	BigNumber res(N);
	res.sign = this->sign;
	for (int i = 0; i < this->chunks.size(); i++) {
		res.chunks.push_back(this->chunks[i] - num.chunks[i]);
	}
	return res;
}

//Оператор +, выполняет корректное сложение больших чисел
BigNumber BigNumber::operator + (BigNumber &num) {
	BigNumber res(N);

	//Приводим размер чанок обоих чисел
	if (this->chunks.size() > num.chunks.size()) {
		num._resize(chunks.size());
	}
	else {
		(*this)._resize(num.chunks.size());
	}

	//Выполняем операцию в зависимости от знаков чисел
	if (sign == num.sign) {
		res = (*this)._plus(num);
	}
	else {
		res = (*this)._minus(num);
	}

	//Нормализуем результат
	res._normalizationChunks();
	res._normalizationSigns();
	res._modN();

	return res;
}


//Оператор -, выполняет корректное вычитание
BigNumber BigNumber::operator - (BigNumber &num) {
	BigNumber res(N);
	//Приводим размер чанок
	if (this->chunks.size() > num.chunks.size()) {
		num._resize(chunks.size());
	}
	else {
		(*this)._resize(num.chunks.size());
	}
	//В зависимости от знаков, выполняем нужное действие
	if (sign != num.sign) {
		res = (*this)._plus(num);
	}
	else {
		res = (*this)._minus(num);
	}
	//Нормализуем результат
	res._normalizationChunks();
	res._normalizationSigns();
	res._modN();

	return res;
}




///***********часть Антона***************/
////Функция умножения больших чисел
//BigNumber BigNumber::_simplemulti(BigNumber &num) {
//	BigNumber result;
//
//	result._resize(2 * this->chunks.size());
//	result.sign = this->sign;
//
//	for (int i = 0; i < this->chunks.size(); i++) {
//		for (int j = 0; j < num.chunks.size(); j++) {
//			result.chunks[i + j] += this->chunks[i] * num.chunks[j];
//		}
//	}
//
//	result._normalizationChunks();
//	return result;
//}
//
////Функция приводит большие числа к нужному размеру
//BigNumber BigNumber::_multi(BigNumber &num) {
//	auto maxSize = max(this->chunks.size(), num.chunks.size());
//
//	int newSize = 1;
//	while (newSize < maxSize) {
//		newSize *= 2;
//	}
//
//	(*this)._resize(newSize);
//	num._resize(newSize);
//
//	//return (*this)._fastmulti(num);
//	return (*this)._simplemulti(num);
//}
//
//BigNumber BigNumber::operator * (BigNumber &num) {
//	BigNumber result;
//
//	result = (*this)._multi(num);
//	result._normalizationChunks();
//
//	if (this->sign == num.sign) {
//		result.sign = 1;
//	}
//	else {
//		result.sign = -1;
//	}
//
//	return result;
//}
//
///**********************/