// BubbleSort.cpp
// by Xiaoguang Zhu (id est smdsbz) of the Backstage Group

#include <iostream>
#include <vector>
using namespace std;

int main() {
	// get the numbers from user input
	vector<int> array;
	cout << "Enter at least two numbers to start the bubble sort." << endl;
	for (int p = 0, input = 0; cin >> input; ++p) {
		array.push_back(input);
		cout << "I get that! Give me some more OR Enter \'eof\' to start sorting!" << endl;
	}
	// print out the input numbers
	cout << "\nThe array you\'ve entered was: ";
	for (int p = 0; p < array.size(); ++p)
		cout << array [p] << " ";

	cout << "\n\nNow sorting..." << endl;
	// start bubble sorting
	int i = 1, exch = 0;
	while (i < array.size()) {
		if (array [i - 1] <= array [i])
			++i;
		else {
			// block of code to move the bigger number to the end of the line like a bubble!
			for (int p = i; p < array.size(); ++p) {
				exch = array [p - 1];
				array [p - 1] = array [p];
				array [p] = exch;
// debug output
//				for (int p = 0; p < array.size(); ++p)
//					cout << array [p] << " ";
//				cout << endl;
				}
			// roll back to the first number if there is number moved
			i = 1;
			}
		}
	// giving the final output - the sorted array
	cout << "\nThe moment of truth!" << endl;
	for (int p = 0; p < array.size(); ++p)
		cout << array [p] << " ";
	cout << endl;
	return 0;
} 
