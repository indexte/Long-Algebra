#pragma once
#include <string>
#include <iostream>
#include <vector>

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
	string N;

	/*HELPERS*/
	void _modN(BigNumber N_);
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
	void modN(string n);

	/*GETTERS SETTERS*/
	void printBigNumber();

	void setBigNumber(BigNumber num) {
		this->chunks = num.getChunks();
		this->sign = num.getSign();
		string n = num.getN();
		for (int i = 0; i < n.size(); i++) {
			this->N.push_back(n[i]);
		}
	}
	void pushC(int a) {
		this->chunks.push_back(a);
	}
	void setChunks(vector<int> chunks) {
		this->chunks = chunks;
	};

	int getBASE() { return this->BASE; }
	string getN() { return this->N; }
	int getSign() { return this->sign; }
	vector<int> getChunks() { return this->chunks; }

	/*CREATION*/
	BigNumber(string str, string n) {
		for (int i = 0; i < n.size(); i++) {
			this->N.push_back(n[i]);
		}

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

		modN(N);

	}

	BigNumber(string n) {
		sign = 1;
		for (int i = 0; i < n.size(); i++) {
			this->chunks.push_back(n[i]);
		}
		this->N.push_back('0');
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

//* mod N
void  BigNumber::_modN(BigNumber N_) {
	BigNumber temp = (*this);
	while (temp >= N_) {
		temp.setBigNumber(temp - N_);
	}
	setBigNumber(temp);
}
//*/
//* mod N
void  BigNumber::modN(string N) {

	if (this->N == "0") { return; }
	else {

		BigNumber N_(N, "0");
		BigNumber temp("0");
		temp.pushC(chunks[this->chunks.size() - 1]);
		for (int i = this->chunks.size() - 2; i >= 0; i--) {

			if (temp >= N_) {
				temp._modN(N_);
			}

			temp._reverse();
			temp.pushC(chunks[i]);
			temp._reverse();
			temp._normalizationZero();
		}
		if (temp >= N_) { temp._modN(N_); }

		if (this->sign == -1) {
			setBigNumber(N_ - (temp));
		}
		else {
			setBigNumber(temp);
		}
	}
}
//*/

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

	for (int i = this->chunks.size() - 1; i >= 0; i--) {
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

	for (int i = this->chunks.size() - 1; i >= 0; i--) {
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

// operator +
BigNumber BigNumber::operator + (BigNumber &num) {

	BigNumber res(N);
	vector<int> reschunks;

	if (this->chunks.size() > num.chunks.size()) {
		num._resize(this->chunks.size());
	}
	else {
		_resize(num.chunks.size());
	}

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
	res.modN(N);

	num._normalizationZero();
	_normalizationZero();

	return res;
}

// operator -
BigNumber BigNumber::operator - (BigNumber &num) {

	BigNumber res(N);
	vector<int> reschunks;

	if (this->chunks.size() > num.chunks.size()) {
		num._resize(this->chunks.size());
	}
	else {
		_resize(num.chunks.size());
	}

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
	res.modN(N);

	num._normalizationZero();
	_normalizationZero();

	return res;
}