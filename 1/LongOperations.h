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
	BigNumber operator - () const;
	void operator = (const BigNumber &num);
	bool operator == (const BigNumber &num) const;
	bool operator >= (const BigNumber &num) const;
	bool operator > (const BigNumber &num) const;
	BigNumber operator + (const BigNumber &num) const;
	BigNumber operator - (const BigNumber &num) const;
	BigNumber operator * (const BigNumber &num) const;
	BigNumber inverse() const;
	BigNumber operator/(const BigNumber & num) const;
	bool operator!=(const BigNumber & num) const;
	friend std::ostream & operator << (std::ostream &out, const BigNumber &num);
	void _reverse();
	void _resize(int newsize);
	void modN(string n);

	/*GETTERS SETTERS*/
	void printBigNumber();

	void setBigNumber(BigNumber num) {
		this->chunks = num.getChunks();
		this->sign = num.getSign();
		N = num.getN();
	}
	void pushC(int a) {
		this->chunks.push_back(a);
	}
	void setChunks(vector<int> chunks) {
		this->chunks = chunks;
	};
	void setN(string N) {
		this->N = N;
		modN(N);
	};

	int getBASE() { return this->BASE; }
	string getN() { return this->N; }
	int getSign() { return this->sign; }
	vector<int> getChunks() { return this->chunks; }

	/*CREATION*/
	BigNumber(string str, string n) {
		N = n;
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
		BigNumber temp("");
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
	this->N = N;
}
//*/

// operator > 
bool BigNumber::operator > (const BigNumber &num) const {
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
bool BigNumber::operator >= (const BigNumber &num) const {
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

BigNumber BigNumber::operator-() const
{
	BigNumber res = *this;
	res.sign *= -1;
	res.modN(N);
	return res;
}

void BigNumber::operator =(const BigNumber &num)
{
	this->setBigNumber(num);
}

// operator ==
bool BigNumber::operator == (const BigNumber &num) const {
	if ((sign != num.sign) || (this->chunks.size() != num.chunks.size())) {
		return false;
	}
	for (int i = 0; i < this->chunks.size(); i++) {
		if (this->chunks[i] != num.chunks[i]) return false;
	}
	return true;
}

// operator +
BigNumber BigNumber::operator + (const BigNumber &num) const {

	BigNumber res("0", N);
	vector<int> reschunks;
	//a+b
	BigNumber a = *this;
	BigNumber b = num;
	if (a.chunks.size() > b.chunks.size()) {
		b._resize(a.chunks.size());
	}
	else {
		a._resize(b.chunks.size());
	}

	if (sign == b.sign) {

		res.sign = a.sign;

		int over = 0;
		for (int i = 0; i < a.chunks.size(); i++) {
			reschunks.push_back(a.chunks[i] + b.chunks[i]);
			reschunks[i] += over;
			over = my_div(reschunks[i], BASE);
			reschunks[i] = my_mod(reschunks[i], BASE);
		}

		if (over != 0) {
			reschunks.push_back(over);
		}

	}
	else {
		res.sign = a.sign;
		int over = 0;
		a.sign *= -1;
		if (a >= b) {

			for (int i = 0; i < a.chunks.size(); i++) {
				reschunks.push_back(a.chunks[i] - b.chunks[i]);
				reschunks[i] += over;
				over = my_div(reschunks[i], BASE);
				reschunks[i] = my_mod(reschunks[i], BASE);
			}
		}
		else {

			res.sign *= -1;
			for (int i = 0; i < a.chunks.size(); i++) {
				reschunks.push_back(b.chunks[i] - a.chunks[i]);
				reschunks[i] += over;
				over = my_div(reschunks[i], BASE);
				reschunks[i] = my_mod(reschunks[i], BASE);
			}
		}
		a.sign *= -1;

	}

	res.setChunks(reschunks);
	res._normalizationZero();
	res.modN(N);

	return res;
}

// operator -
BigNumber BigNumber::operator - (const BigNumber &num) const {

	BigNumber res("0",N);
	vector<int> reschunks;
	//a-b
	BigNumber a = *this;
	BigNumber b = num;
	if (a.chunks.size() > b.chunks.size()) {
		b._resize(a.chunks.size());
	}
	else {
		a._resize(b.chunks.size());
	}

	if (sign != b.sign) {

		res.sign = a.sign;

		int over = 0;
		for (int i = 0; i < a.chunks.size(); i++) {
			reschunks.push_back(a.chunks[i] + b.chunks[i]);
			reschunks[i] += over;
			over = my_div(reschunks[i], BASE);
			reschunks[i] = my_mod(reschunks[i], BASE);
		}

		if (over != 0) {
			reschunks.push_back(over);
		}

	}
	else {
		res.sign = a.sign;
		int over = 0;

		if (a >= b) {
			for (int i = 0; i < a.chunks.size(); i++) {
				reschunks.push_back(a.chunks[i] - b.chunks[i]);
				reschunks[i] += over;
				over = my_div(reschunks[i], BASE);
				reschunks[i] = my_mod(reschunks[i], BASE);
			}
		}
		else {
			res.sign *= -1;
			for (int i = 0; i < a.chunks.size(); i++) {
				reschunks.push_back(b.chunks[i] - a.chunks[i]);
				reschunks[i] += over;
				over = my_div(reschunks[i], BASE);
				reschunks[i] = my_mod(reschunks[i], BASE);
			}
		}

	}

	res.setChunks(reschunks);
	res._normalizationZero();
	res.modN(N);

	return res;
}


// operator *
BigNumber BigNumber::operator * (const BigNumber &num) const {

	BigNumber res("0",N);
	vector<int> res_chunks;
	res_chunks.resize(this->chunks.size() + num.chunks.size()+1);
	for (int i = 0; i < this->chunks.size(); i++) {
		for (int j = 0; j < num.chunks.size(); j++) {
			res_chunks[i + j] += this->chunks[i] * num.chunks[j];
			res_chunks[i + j + 1] += res_chunks[i + j] / 10;
			res_chunks[i + j] = res_chunks[i + j] % 10;			
		}
	}
	res.setChunks(res_chunks);
	res._normalizationZero();
	res.modN(res.getN());
	
	return res;
}
//returns 0 if greatest common dividor !=1
BigNumber BigNumber::inverse() const {
	BigNumber a = *this;
	BigNumber b (N,"0");
	BigNumber one("1", N);
	BigNumber zero("0", N);
	BigNumber a_1("1", N);//a count in a
	BigNumber a_2("0", N);//b count in a
	BigNumber b_1("0", N);//a count in b
	BigNumber b_2("1", N);//b count in b
	BigNumber x("0", N);//result
	while (a!=one && b!=one) {
		if ((a == zero) || (b == zero)) {
			return zero;
		}
		if (a >= b) {
			a = a - b;
			a_1 = a_1 - b_1;
			a_2 = a_2 - b_2;
		}
		else
		{
			b = b - a;
			b_1 = b_1 - a_1;
			b_2 = b_2 - a_2;
		}
	}
	if (a == one) {
		x = a_1;
	}
	else {
		x = b_1;
	}
	x.setN(N);
	return x;
}

// operator /
BigNumber BigNumber::operator / (const BigNumber &num) const {

	BigNumber res = (*this)*(num.inverse());

	return res;
}

std::ostream & operator<<(std::ostream & out, const BigNumber & num)
{
	for (int i = num.chunks.size() - 1; i >= 0; i--) {
		out << num.chunks[i];
	}
	return out;
}

bool BigNumber::operator != (const BigNumber &num) const {
	return !(*this == num);
}