#include <iostream>
#include <vector>

using namespace std;

class Mask {
protected:
	short _1 = 0, _2 = 0, _3 = 0, _4 = 0;
	Mask() :_1(0), _2(0), _3(0), _4(0) {}
	bool err = 0;
public:
	Mask(short _1, short _2, short _3, short _4)
	{
		if ((_1 != 255) ||
			(_2 != 255 && _2 != 0) ||
			(_2 == 0 && _3 != 0) || (_2 == 255 && (_3 != 255 && _3 != 0)) ||
			(_3 == 0 && _4 != 0) || (_2 == 255 && (_4 != 255 && _4 != 0))) {
			cout << "(!) syntax err\n";
			err++;
			return;
		}
		this->_1 = _1;
		this->_2 = _2;
		this->_3 = _3;
		this->_4 = _4;

	}
	bool M_err() { return err; }
	inline short get_1() { return _1; }
	inline short get_2() { return _2; }
	inline short get_3() { return _3; }
	inline short get_4() { return _4; }
};

class Address {
protected:
	short _1 = 0, _2 = 0, _3 = 0, _4 = 0;
	Address() :_1(0), _2(0), _3(0), _4(0) {}
	bool err = 0;
public:
	Address(short _1, short _2, short _3, short _4)
	{
		if ((_1 == 0) ||
			(_1 != 0 && _2 == 0 && (_3 != 0 || _4 != 0)) ||
			(_1 != 0 && _2 != 0 && _3 == 0 && _4 != 0)) {
			cout << "(!) syntax err\n";
			err++;
			return;
		}
		this->_1 = _1;
		this->_2 = _2;
		this->_3 = _3;
		this->_4 = _4;

	}
	bool A_err() { return err; }
	inline short get_1() { return _1; }
	inline short get_2() { return _2; }
	inline short get_3() { return _3; }
	inline short get_4() { return _4; }
};

vector<Address> AlreadyExists;
bool isexist(Address A) {
	for (auto i = AlreadyExists.begin(); i != AlreadyExists.end(); i++)
		if ((*i).get_1() == A.get_1())
			if ((*i).get_2() == A.get_2())
				if ((*i).get_3() == A.get_3())
					if ((*i).get_4() == A.get_4())
						return true;
	return false;
}


bool isexist(short _1, short _2, short _3, short _4) {
	for (auto i = AlreadyExists.begin(); i != AlreadyExists.end(); i++)
		if ((*i).get_1() == _1)
			if ((*i).get_2() == _2)
				if ((*i).get_3() == _3)
					if ((*i).get_4() == _4)
						return true;
	return false;
}

class Network :Mask, Address {
private:
	vector<Address> All;
	short sequence = 0, t_sequence = 0, s_sequence = 0;
public:
	Network(Mask M, Address A) {
		if (M.M_err()) {
			cout << "(!) impossible to create network<mask syntax error>\n";
			return;
		}
		if (A.A_err()) {
			cout << "(!) impossible to create network<address syntax error>\n";
			return;
		}
		if (isexist(A)) {
			cout << "(!) impossible to create network<that address already exists>\n";
			return;
		}
		if (A.get_4() != 0) {
			cout << "(!) impossible to create network<address syntax error>\n";
			return;
		}
		AlreadyExists.push_back(A);
		Mask::_1 = M.get_1();
		Mask::_2 = M.get_2();
		Mask::_3 = M.get_3();
		Mask::_4 = M.get_4();
		Address::_1 = A.get_1();
		Address::_2 = A.get_2();
		Address::_3 = A.get_3();
		Address::_4 = A.get_4();
		sequence = Address::get_4(), t_sequence = Address::get_3(), s_sequence = Address::get_2();
	}
	Network(short M_1, short M_2, short M_3, short M_4, short A_1, short A_2, short A_3, short A_4) {
		if ((M_1 != 255) ||
			(M_2 != 255 && M_2 != 0) ||
			(M_2 == 0 && M_3 != 0) || (M_2 == 255 && (M_3 != 255 && M_3 != 0)) ||
			(M_3 == 0 && M_4 != 0) || (M_2 == 255 && (M_4 != 255 && M_4 != 0))) {
			cout << "(!) impossible to create network<mask syntax error>\n";
			return;
		}
		if ((A_1 == 0) ||
			(A_1 != 0 && A_2 == 0 && (A_3 != 0 || A_4 != 0)) ||
			(A_1 != 0 && A_2 != 0 && A_3 == 0 && A_4 != 0)) {
			cout << "(!) impossible to create network<address syntax error>\n";
			return;
		}
		if (isexist(A_1, A_2, A_3, A_4)) {
			cout << "(!) impossible to create network<that address already exists>\n";
			return;
		}
		if (A_4 != 0) {
			cout << "(!) impossible to create network<address syntax error>\n";
			return;
		}
		Mask::_1 = M_1;
		Mask::_2 = M_2;
		Mask::_3 = M_3;
		Mask::_4 = M_4;
		Address::_1 = A_1;
		Address::_2 = A_2;
		Address::_3 = A_3;
		Address::_4 = A_4;
		sequence = Address::get_4(), t_sequence = Address::get_3(), s_sequence = Address::get_2();
	}
	inline void info() {
		cout << "Network Mask: " << Mask::_1 << "." << Mask::_2 << "." << Mask::_3 << "." << Mask::_4 <<
			"\nNetwork Address: " << Address::_1 << "." << Address::_2 << "." << Address::_3 << "." << Address::_4 << 
			"\nAll Addresses: " << All.size() << endl;
	}
	inline void showAll() {
		for (auto& i : All)
			cout << i.get_1() << "." << i.get_2() << "." << i.get_3() << "." << i.get_4() << "; ";
	}
	inline bool isinnetwork(Address A) {
		for (auto i = All.begin(); i != All.end(); i++)
			if ((*i).get_1() == A.get_1())
				if ((*i).get_2() == A.get_2())
					if ((*i).get_3() == A.get_3())
						if ((*i).get_4() == A.get_4())
							return true;
		return false;
	}
	inline bool isinnetwork(short _1, short _2, short _3, short _4) {
		for (auto i = All.begin(); i != All.end(); i++)
			if ((*i).get_1() == _1)
				if ((*i).get_2() == _2)
					if ((*i).get_3() == _3)
						if ((*i).get_4() == _4)
							return true;
		return false;
	}
protected:
	inline short returnindex(short _1, short _2, short _3, short _4) {
		for (auto i = All.begin(); i != All.end(); i++)
			if ((*i).get_1() == _1)
				if ((*i).get_2() == _2)
					if ((*i).get_3() == _3)
						if ((*i).get_4() == _4)
							return i - All.begin();
		return -1;
	}
	inline short returnindex(Address A) {
		for (auto i = All.begin(); i != All.end(); i++)
			if ((*i).get_1() == A.get_1())
				if ((*i).get_2() == A.get_2())
					if ((*i).get_3() == A.get_3())
						if ((*i).get_4() == A.get_4())
							return i - All.begin();
		return -1;
	}
public:
	void add() {
		if (All.size() == 0 && Mask::get_4() == 255) {
			cout << "(!) impossible to add new address<maximum reached>\n";
			return;
		}
		if (sequence == 255 && Mask::get_3() == 255) {
			cout << "(!) impossible to add new address<maximum reached>\n";
			return;
		}
		if (sequence == 255 && Mask::get_3() != 255) {
			sequence = 0;
			Address New(Address::get_1(), Address::get_2(), ++t_sequence, sequence);
			if (isinnetwork(New)) {
				cout << "(!) impossible to add new address<already exists>\n";
				return;
			}
			All.push_back(New);
			return;
		}
		if (t_sequence == 255 && Mask::get_2() == 255) {
			cout << "(!) impossible to add new address<maximum reached>\n";
			return;
		}
		if (t_sequence == 255 && Mask::get_2() != 255) {
			sequence = 0;
			t_sequence = 0;
			Address New(Address::get_1(), ++s_sequence, t_sequence, sequence);
			if (isinnetwork(New)) {
				cout << "(!) impossible to add new address<already exists>\n";
				return;
			}
			All.push_back(New);
			return;
		}
		if (s_sequence == 255) {
			cout << "(!) impossible to add new address<maximum reached>\n";
			return;
		}
		Address New(Address::get_1(), s_sequence, t_sequence, ++sequence);
		if (isinnetwork(New)) {
			cout << "(!) impossible to add new address<already exists>\n";
			return;
		}
		All.push_back(New);
		return;
	}
	void add_special(Address A) {
		if (isinnetwork(A)) {
			cout << "(!) impossible to add new address<already exists>\n";
			return;
		}
		if (Mask::get_1() == Mask::get_2() == Mask::get_3() == Mask::get_4()) {
			cout << "(!) impossible to add new address<maximum reached>\n";
			return;
		}
		if (Mask::get_1() == Mask::get_2() == Mask::get_3() != Mask::get_4()) {
			if (A.get_1() == Address::get_1() && A.get_2() == Address::get_2() && A.get_3() == Address::get_3()) {
				Address New = A;
				All.push_back(New);
				return;
			}
			else {
				cout << "(!) impossible to add new address<syntax error>\n";
				return;
			}
		}
		if (Mask::get_1() == Mask::get_2() != Mask::get_3()) {
			if (A.get_1() == Address::get_1() && A.get_2() == Address::get_2()) {
				Address New = A;
				All.push_back(New);
				return;
			}
			else {
				cout << "(!) impossible to add new address<syntax error>\n";
				return;
			}
		}
		if (Mask::get_1() != Mask::get_2()) {
			if (A.get_1() == Address::get_1()) {
				Address New = A;
				All.push_back(New);
				return;
			}
			else {
				cout << "(!) impossible to add new address<syntax error>\n";
				return;
			}
		}
	}
	void add_special(short _1, short _2, short _3, short _4) {
		if (isinnetwork(_1, _2, _3, _4)) {
			cout << "(!) impossible to add new address<already exists>\n";
			return;
		}
		if (Mask::get_1() == Mask::get_2() == Mask::get_3() == Mask::get_4()) {
			cout << "(!) impossible to add new address<maximum reached>\n";
			return;
		}
		if (Mask::get_1() == Mask::get_2() == Mask::get_3() != Mask::get_4()) {
			if (_1 == Address::get_1() && _2 == Address::get_2() && _3 == Address::get_3()) {
				Address New(_1, _2, _3, _4);
				All.push_back(New);
				return;
			}
			else {
				cout << "(!) impossible to add new address<syntax error>\n";
				return;
			}
		}
		if (Mask::get_1() == Mask::get_2() != Mask::get_3()) {
			if (_1 == Address::get_1() && _2 == Address::get_2()) {
				Address New(_1, _2, _3, _4);
				All.push_back(New);
				return;
			}
			else {
				cout << "(!) impossible to add new address<syntax error>\n";
				return;
			}
		}
		if (Mask::get_1() != Mask::get_2()) {
			if (_1 == Address::get_1()) {
				Address New(_1, _2, _3, _4);
				All.push_back(New);
				return;
			}
			else {
				cout << "(!) impossible to add new address<syntax error>\n";
				return;
			}
		}
	}
	void deleteIP(Address A) {
		if (returnindex(A) > 0) {
			if(sequence > All[returnindex(A) - 1].get_4())
				sequence = All[returnindex(A)-1].get_4();
			if (t_sequence > All[returnindex(A) - 1].get_3())
				t_sequence = All[returnindex(A) - 1].get_3();
			if (s_sequence > All[returnindex(A) - 1].get_2())
				s_sequence = All[returnindex(A) - 1].get_2();
			All.erase(All.begin() + returnindex(A));
			return;
		}
		cout << "(!) impossible to delete address<invalid address>\n";
		return;
	}
	void deleteIP(short _1, short _2, short _3, short _4) {
		if (returnindex(_1, _2, _3, _4) > 0) {
			if (sequence > All[returnindex(_1, _2, _3, _4) - 1].get_4())
				sequence = All[returnindex(_1, _2, _3, _4) - 1].get_4();
			if (t_sequence > All[returnindex(_1, _2, _3, _4) - 1].get_3())
				t_sequence = All[returnindex(_1, _2, _3, _4) - 1].get_3();
			if (s_sequence > All[returnindex(_1, _2, _3, _4) - 1].get_2())
				s_sequence = All[returnindex(_1, _2, _3, _4) - 1].get_2();
			All.erase(All.begin() + returnindex(_1, _2, _3, _4));
			return;
		}
		cout << "(!) impossible to delete address<invalid address>\n";
		return;
	}
};

int main() {
	Mask M(255, 255, 255, 0);
	Address A(196, 8, 54, 0);
	Network N(M, A);
	N.info();
	cout << endl;
	Network N2(255, 255, 255, 0, 196, 8, 54, 0);
	N2.info();
	cout << endl;
	for (int i = 0; i < 256; i++) {
		N.add();
	}
	N.info();
	cout << endl;
	for (int i = 3; i < 253; i++) {
		N.deleteIP(196, 8, 54, i);
	}
	N.info();
	cout << endl;
	N.deleteIP(255, 255, 255, 255);
	cout << endl;
	N.showAll();
	N.add();
	N.add();
	cout << endl;
	N.showAll();
	cout << endl;
	cout << N.isinnetwork(196, 8, 54, 0);
	cout << endl;
	Address Add(196, 8, 54, 1);
	cout << N.isinnetwork(Add);
}