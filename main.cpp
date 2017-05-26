#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef enum {
	WAIT_X,
	WAIT_Y,
	ACCUMULATE_X,
	ACCUMULATE_Y
} State;

struct tpoint_r {
	double X;
	double Y;

	tpoint_r(void) {
		this->X = 0.;
		this->Y = 0.;
	}
	
	void Print(void) {
		cout << this->X << ":" << this->Y << endl;
	}
};

bool IsNumeral(char sym) {
	if ((sym >= '0' && sym <= '9') || sym == '.') {
		return true;
	}
	return false;
}


vector <tpoint_r> Parse(string in) {
	vector <tpoint_r> res(0);
	State state = WAIT_X;
	string tmp_str = "";
	tpoint_r tmp_val;
	bool point_log = false;

	for (size_t i = 0; i < in.size(); i++) {
		switch (state) {
			case WAIT_X:
				if (IsNumeral(in[i])) {
					state = ACCUMULATE_X;
				} else {
					break;
				}
			case ACCUMULATE_X:
				if (IsNumeral(in[i])) {
					if (in[i] == '.') {
						if (point_log) {
							break;
						}
						point_log = true;
					}
					tmp_str += in[i];
				} else {
					tmp_val.X = stod(tmp_str);
					tmp_str = "";
					state = WAIT_Y;
					point_log = false;
				}
				break;
			case WAIT_Y:
				if (IsNumeral(in[i])) {
					state = ACCUMULATE_Y;
				} else {
					break;
				}
			case ACCUMULATE_Y:
				if (IsNumeral(in[i])) {
					if (in[i] == '.') {
						if (point_log) {
							break;
						}
						point_log = true;
					}
					tmp_str += in[i];
				} else {
					tmp_val.Y = stod(tmp_str);
					res.resize(res.size() + 1);
					res[res.size() - 1] = tmp_val;
					tmp_str = "";
					state = WAIT_X;
					point_log = false;
				}
				break;
		}
	}
	return res;
}

int main(void) {
	vector <tpoint_r> arr;
	string input = "";
	char sym;
	//Start adaptation for console
	while ((sym = getchar()) != EOF) {
		input += sym;
	}
	//End adaptation for console

	arr = Parse(input);
	for (size_t i = 0; i < arr.size(); i++) {
		arr[i].Print();
	}
	return 0;
}
