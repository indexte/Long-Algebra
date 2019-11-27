#pragma once
#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

/**
 * The declaration of the class that is used in functions that factorize BigNumber and return
 *  the array of dividers and their powers.
 */
class factorization;

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
	BigNumber operator % (const BigNumber &num) const;
	BigNumber operator + (const BigNumber &num) const;
	BigNumber operator - (const BigNumber &num) const;
	BigNumber operator * (const BigNumber &num) const;
	BigNumber inverse() const;
	BigNumber operator/(const BigNumber & num) const;
	bool operator!=(const BigNumber & num) const;
	string to_string()const;
	friend std::ostream & operator << (std::ostream &out, const BigNumber &num);
	void _reverse();
	void _resize(int newsize);
	void modN(string n);

    /**
     * This funtion implements tha naive factorization of the number on the prime dividers
     * @return the structure "factorization" that contains all of the dividers and the proper powers
     */
    factorization factorize_naive();

    /**
     * The actual pollard factorization algo that finds the one and only one divider. It could be
     *     non-prime.
     * @param _c the const that is used in function formula. For default user it should equals 1.
     * @return one of the dividers
     */
    BigNumber _factorize_pollard(string _c);

    /**
     * The "wrap" function for the pollard factorization. It gets the divider from the pollard's algo
     *      and recursively do it for both divider and the divided/divider. Writes the answer in
     *      factorization structure.
     * @return the factorization structure that contains the factual prime factorization
     */
    factorization factorize_pollard();

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
		for (int i = n.size()-1; i >=0 ; i--) {
			this->chunks.push_back(n[i] - '0');
		}
		N = "0";
	}

	~BigNumber() {}
};

/**
 * The initialization of the class that is used in functions that factorize BigNumber and return
 *  the array of dividers and their powers.
 */
class factorization{
public:
    vector<BigNumber> base;
    vector<BigNumber> power;

    /**
     * This function checks if the number is prime
     * @return 0 if the number is compositive and 1 if the number is prime
     */
    bool is_prime() {
        vector<int> one;
        one.push_back(1);

        if (power.size() == 1 && power[0].getChunks() == one) {
            return 1;
        }
        return 0;
    }

    /**
     * This functions just prints the factorization data of the structure on the screen
     */
    void print(){
        vector<int> one;
        one.push_back(1);
        if(is_prime()){
            cout << "The number is prime" << endl;
            return;
        }
        cout << "The factorization is:" << endl;
        for(int i = 0; i < base.size(); i++){
            cout << "The base: " << base[i] << ". The power: " << power[i] << endl;
        }
    }

    /**
     * This function updates the current data in structure with new data in the same structure
     * @param in the data that should be added for this structure
     */
    void add_factorization(factorization in){
        bool present = 0;
        for(int i = 0; i < in.base.size(); i++){
            for(int j = 0; j < base.size(); j++){
                if(in.base[i] == base[j]) {
                    in.power[i] = in.power[i] + power[j];
                    present = 1;
                }
            }
            if(present == 0){
                base.push_back(in.base[i]);
                power.push_back(in.power[i]);
            }
            present = 0;
        }
    }
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

string BigNumber::to_string() const
{
	string res;
	for (int i = chunks.size() - 1; i >= 0; i--) {
	    // commented the cout cuz I thought it was used only for debugging
		//cout << char(chunks[i] + int('0')) << endl;            /*********************************
		res.push_back(char(chunks[i] + int('0')));
	}
	return res;
}


BigNumber BigNumber::operator%(const BigNumber & num) const
{
	BigNumber res = BigNumber("0", N);
	res.setChunks(chunks);
	string _N = N;
	res.setN(num.to_string());
	res.setN(_N);
	return res;
}
/**
 * This funtion implements tha naive factorization of the number on the prime dividers
 * @return the structure "factorization" that contains all of the dividers and the proper powers
 */
factorization BigNumber::factorize_naive() {
    vector<BigNumber> _base;
    vector<BigNumber> _power;
    factorization out;
    out.base = _base;
    out.power = _power;

    BigNumber zero = BigNumber("0", N);
    BigNumber one = BigNumber("1", N);
    BigNumber iterator = BigNumber("2", N);
    BigNumber divided = *this;
    if(iterator > divided){
        cout << "This number is less than two. *This cout is used to developers. "
                "Comment it if u dont need it*" << endl;
        out.base.push_back(one);
        out.power.push_back(one);
        return out;
    }
    else {
        int pos = 0;
        while(divided >= iterator){
            if(divided % iterator == zero){
                out.base.push_back(iterator);
                out.power.push_back(zero);
                while(divided % iterator == zero){
                    if (divided == zero)
                        return out;
                    divided = divided / iterator;
                    out.power[pos] = out.power[pos] + one;
                }
                pos++;
            }
            iterator = iterator + one;
        }
    }
    return out;
}

/**
 * This function is used in Pollard factorization algorithm. Finds the gcd form two numbers.
 * @param a the first number
 * @param b the second number
 * @return the gcd of a and b
 */
BigNumber gcd(BigNumber a, BigNumber b){
    BigNumber zero = BigNumber("0", a.getN());

    if(a == zero)
        return b;
    if(b == zero)
        return a;
    if(a == b)
        return a;
    if(a > b)
        return gcd(a - b, b);
    return gcd(a, b - a);
}
/**
 * The actual pollard factorization algo that finds the one and only one divider. It could be
 *     non-prime.
 * @param _c the const that is used in function formula. For default user it should equals 1.
 * @return one of the dividers
 */
BigNumber BigNumber::_factorize_pollard(string _c){

    vector<BigNumber> _base;
    vector<BigNumber> _power;
    factorization out;
    out.base = _base;
    out.power = _power;

    BigNumber zero = BigNumber("0", this->to_string());
    BigNumber one = BigNumber("1", this->to_string());
    BigNumber two = BigNumber("2", this->to_string());

    if(two > *this){
        return zero;
    }

    out = this->factorize_naive();
    if(out.is_prime())
        return one;

    if(_c == "0" || _c == "-2"){
        cout << "You can not choose 0 or -2 for this algorithm" << endl;
        return one;
    }

    BigNumber a = BigNumber("2", "0");
    BigNumber b = BigNumber("2", "0");
    BigNumber d = BigNumber("1", this->to_string());
    BigNumber c = BigNumber(_c, "0");
    BigNumber b_b = BigNumber("0", "0");

    while(d == one){
        BigNumber a_a = a * a + c;
        a = BigNumber(a_a.to_string(), this->to_string());              //
        b_b = b * b + c;
        b = BigNumber(b_b.to_string(), this->to_string());
        b.setN("0");
        b_b = b * b + c;
        b = BigNumber(b_b.to_string(), this->to_string());

        if(a > b)
            d = gcd(a - b, *this);
        else
            d = gcd(b - a, *this);

        if(d == *this){
            cout << "starting doing the algorithm with c = c + 1" << endl;
            BigNumber temp = c + one;
            d = _factorize_pollard(temp.to_string());
        }

        a.setN("0");
        b.setN("0");
    }
    return d;
}
/**
 * The "wrap" function for the pollard factorization. It gets the divider from the pollard's algo
 *      and recursively do it for both divider and the divided/divider. Writes the answer in
 *      factorization structure.
 * @return the factorization structure that contains the factual prime factorization
 */
factorization BigNumber::factorize_pollard() {
    string c = "1";

    vector<BigNumber> _base;
    vector<BigNumber> _power;
    factorization out;
    out.base = _base;
    out.power = _power;

    vector<BigNumber> _base_temp;
    vector<BigNumber> _power_temp;
    factorization temp_out;
    temp_out.base = _base_temp;
    temp_out.power = _power_temp;

    BigNumber zero = BigNumber("0", N);
    BigNumber one = BigNumber("1", N);
    BigNumber two = BigNumber("2", N);
    BigNumber divided = *this;
    if(two > *this){
        cout << "This number is less than two. *This cout is used to developers. "
                "Comment it if u dont need it*" << endl;
        out.base.push_back(one);
        out.power.push_back(one);
        return out;
    }
    else {
        //cout << "ya";
        BigNumber temp = divided._factorize_pollard(c);
        //cout << "here";
        temp.setN(N);
        while(divided % temp == zero && divided > one){
            bool present = 0;
            divided = divided / temp;
            if(temp > one) {
                temp_out.add_factorization(temp.factorize_pollard());
                if (temp_out.is_prime()) {
                    for (int i = 0; i < out.base.size(); i++) {
                        if (out.base[i] == temp) {
                            out.power[i] = out.power[i] + one;
                            present = 1;
                            break;
                        }
                    }

                    if (present == 0) {
                        out.base.push_back(temp);
                        out.power.push_back(one);
                    }
                    present = 0;
                } else {
                    out.add_factorization(temp_out);
                }
            }
            temp = divided._factorize_pollard(c);
            temp.setN(N);
            if(temp == one) {
                for(int i = 0; i < out.base.size(); i++){
                    if(out.base[i] == divided) {
                        out.power[i] = out.power[i] + one;
                        present = 1;
                    }
                }
                if(present == 0){
                    out.base.push_back(divided);
                    out.power.push_back(one);
                }
                return out;
            }
            present = 0;
        }
    }
    return out;
}
