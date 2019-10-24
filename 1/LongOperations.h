#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::string;

//division for negaive numb
int my_div(int num, int diver) {
	if ((num < 0) && (num % diver))
		return num / diver - 1;
	else
		return num / diver;
}

//mod for negaive numb
int my_mod(int num, int diver) {
	if ((num < 0) && (num % diver))
		return num % diver + diver;
	else
		return num % diver;
}

/*class BigNumber*/
class BigNumber {
private:
	/*VALUES*/
	vector<int> chunks;
	int sign;
	const unsigned int BASE = 10;
	int N = 0;

	/*HELPERS*/
	void _modN();
	void _normalizationZero();
	
public:

	/*OPERATIONS*/
	bool operator == (BigNumber &num);
	bool operator >= (BigNumber &num);
	bool operator > (BigNumber &num);
	BigNumber operator + (BigNumber &num);
	BigNumber operator - (BigNumber &num);
	void _reverse();
	void _resize(int newsize);

	/*GETTERS SETTERS*/
	void setBigNumber(BigNumber num) {
		this->chunks = num.getChunks();
		this->sign = num.getSign();
		this->N = num.getN();
	}
	void setChunks(vector<int> chunks) {
		this->chunks = chunks;
	};
	int getBASE()	{ return this->BASE;}
	int getN()		{ return this->N;}
	int getSign()	{ return this->sign;}
	vector<int> getChunks() {	return this->chunks;}
	
	void printBigNumber();

	/*CREATION*/
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

		//_modN();

	}
	BigNumber(int N) {
		sign = 1;
		this->N = N;
	}
	~BigNumber() {}
};

// resize vector
void BigNumber::_resize(int newSize) {
	chunks.resize(newSize);
}

// reverse vector
void BigNumber::_reverse() {
	vector<int>::iterator first = begin(chunks);
	vector<int>::iterator last = end(chunks);
	while ((first != last) && (first != --last)) {
		std::swap(*first++, *last);
	}
}

//  delete extra 0
void BigNumber::_normalizationZero() {

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

// print BigNumber
void BigNumber::printBigNumber() {
	if (sign == -1) {
		cout << '-';
	}
	for (int i = chunks.size() - 1; i >= 0; i--) {
		cout << chunks[i];
	}
	cout << endl;
}

/* mod N
void  BigNumber::_modN() {
	if (this->N == 0) { return; }
	else {
		string sN;
		sN = std::to_string(this->N);
		BigNumber N_(sN, 0);
		if (sign == 1) {
			while ((*this) >= N_) {
				setBigNumber((*this) - N_);
			}
		}
		else {
			BigNumber Nul("0", 0);
			while (Nul > (*this)) {
				setBigNumber((*this) + N_);
			}
		}
	}
}
*/

// operator > 
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

// operator >=
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

// operator ==
bool BigNumber::operator == (BigNumber &num) {
	if ((sign != num.sign) || (this->chunks.size() != num.chunks.size())) {
		return false;
	}
	for (int i = 0; i < this->chunks.size(); i++) {
		if (this->chunks[i] != num.chunks[i]) return false;
	}
	return true;
}

// +
BigNumber BigNumber::operator + (BigNumber &num) {
	
	BigNumber res(N);
	vector<int> reschunks;
	//ѕриводим размер чанок обоих чисел
	if (this->chunks.size() > num.chunks.size()) {
		num._resize(this->chunks.size());
	}
	else {
		_resize(num.chunks.size());
	}

	//¬ыполн€ем операцию в зависимости от знаков чисел
	if (sign == num.sign) {

		res.sign = this->sign;

		int over = 0;
		for (int i = 0; i < this->chunks.size(); i++) {
			reschunks.push_back(this->chunks[i] + num.chunks[i]);
			reschunks[i] += over;
			over = my_div(reschunks[i], BASE);
			reschunks[i] = my_mod(reschunks[i], BASE);
		}

		if (over != 0) {
			reschunks.push_back(over);
		}

	}
	else {
		res.sign = this->sign;
		int over = 0;
		this->sign *= -1;
		if ((*this) >= num) {
			
			for (int i = 0; i < this->chunks.size(); i++) {
				reschunks.push_back(this->chunks[i] - num.chunks[i]);
				reschunks[i] += over;
				over = my_div(reschunks[i], BASE);
				reschunks[i] = my_mod(reschunks[i], BASE);
			}
		}
		else {
			res.sign *= -1;
			for (int i = 0; i < this->chunks.size(); i++) {
				reschunks.push_back(num.chunks[i] - this->chunks[i]);
				reschunks[i] += over;
				over = my_div(reschunks[i], BASE);
				reschunks[i] = my_mod(reschunks[i], BASE);
			}
		}
		this->sign *= -1;

	}

	res.setChunks(reschunks);
	res._normalizationZero();
	num._normalizationZero();
	_normalizationZero();
	
	//res._modN();

	return res;
}

// +
BigNumber BigNumber::operator - (BigNumber &num) {

	BigNumber res(N);
	vector<int> reschunks;
	//ѕриводим размер чанок обоих чисел
	if (this->chunks.size() > num.chunks.size()) {
		num._resize(this->chunks.size());
	}
	else {
		_resize(num.chunks.size());
	}

	//¬ыполн€ем операцию в зависимости от знаков чисел
	if (sign != num.sign) {

		res.sign = this->sign;

		int over = 0;
		for (int i = 0; i < this->chunks.size(); i++) {
			reschunks.push_back(this->chunks[i] + num.chunks[i]);
			reschunks[i] += over;
			over = my_div(reschunks[i], BASE);
			reschunks[i] = my_mod(reschunks[i], BASE);
		}

		if (over != 0) {
			reschunks.push_back(over);
		}

	}
	else {
		res.sign = this->sign;
		int over = 0;
		
		if ((*this) >= num) {

			for (int i = 0; i < this->chunks.size(); i++) {
				reschunks.push_back(this->chunks[i] - num.chunks[i]);
				reschunks[i] += over;
				over = my_div(reschunks[i], BASE);
				reschunks[i] = my_mod(reschunks[i], BASE);
			}
		}
		else {
			res.sign *= -1;
			for (int i = 0; i < this->chunks.size(); i++) {
				reschunks.push_back(num.chunks[i] - this->chunks[i]);
				reschunks[i] += over;
				over = my_div(reschunks[i], BASE);
				reschunks[i] = my_mod(reschunks[i], BASE);
			}
		}

	}

	res.setChunks(reschunks);
	res._normalizationZero();
	num._normalizationZero();
	_normalizationZero();

	//res._modN();

	return res;
}