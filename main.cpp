#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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
		cout << this->X << " : " << this->Y << endl;
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

vector <tpoint_r> Sort(vector <tpoint_r> arr) {
	bool change;
	for (size_t i = 0; i < arr.size(); i++) {
		change = false;
		for (size_t j = 1; j < arr.size() - i; j++) {
			if (arr[j - 1].X > arr[j].X) {
				tpoint_r tmp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = tmp;
				change = true;
			}
		}
		if (!change) {
			break;
		}
	}
	return arr;
}

double Distance(tpoint_r a, tpoint_r b) {
	double x_quadr = pow(a.X - b.X, 2);
	double y_quadr = pow(a.Y - b.Y, 2);
	return sqrt(x_quadr + y_quadr);
}

double Length(vector <tpoint_r> arr) {
	double summ = 0.;
	for (size_t i = 1; i < arr.size(); i++) {
		summ += Distance(arr[i - 1], arr[i]);
	}
	return summ;
}
double MaxDistance(vector <tpoint_r> arr) {
	double max = 0.;
	for (size_t i = 1; i < arr.size(); i++) {
		double tmp = Distance(arr[i - 1], arr[i]);
		if (tmp > max) {
			max = tmp;
		}
	}
	return max;
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
	cout << "Basic array:" << endl;
	for (size_t i = 0; i < arr.size(); i++) {
		arr[i].Print();
	}
	vector <tpoint_r> sorted_arr = Sort(arr);
	cout << "Sorted array:" << endl;
	for (size_t i = 0; i < sorted_arr.size(); i++) {
		sorted_arr[i].Print();
	}
	cout << "Line length: " << Length(sorted_arr) << endl;
	cout << "Maximal distance: " << MaxDistance(sorted_arr) << endl;

	return 0;
}
