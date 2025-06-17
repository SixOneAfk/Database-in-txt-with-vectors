#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Car {
public:
	string label;
	string model;
	int year;
	double price;

	void setData() {
		cout << "Enter label: " << endl;
		cin >> label;
		cout << "Enter model: " << endl;
		cin >> model;
		cout << "Enter year: " << endl;
		cin >> year;
		cout << "Enter price: " << endl;
		cin >> price;
	}


	void displayData() {
		cout << label << endl;
		cout << model << endl;
		cout << year << endl;
		cout << price << endl;
	}
};

void saveToFile(vector<Car>& cars, const string& filename) {
	ofstream outfile(filename);

	if (!outfile) {
		cerr << "Error opening file for writing" << endl;
	} else {
		for (const auto& car : cars) {
			outfile << car.label << ' ' << car.model << ' ' << car.year << ' ' << car.price << endl;
		}
	}

	outfile.close();
}

void readFromFile(vector<Car>& cars, const string& filename) {
	ifstream infile(filename);
	if (!infile) {
		cerr << "Error opening file for reading" << endl;
		return;
	}

	cars.clear();
	Car car;
	while (infile >> car.label >> car.model >> car.year >> car.price) {
		cars.push_back(car);
	}
	cout << "Loaded " << cars.size() << " cars from file." << endl;
}

void deleteObject(vector<Car>& cars, const string& filename) {
	if (cars.empty()) {
		cout << "No data available" << endl;
		return;
	}

	for (size_t i = 0; i < cars.size(); ++i) {
		cout << i << ' ' << cars[i].label << ' ' << cars[i].model << endl;
	}

	int index;
	cout << "Enter index of object to delete: ";
	cin >> index;

	if (index < 0 || index >= cars.size()) {
		cerr << "Invalid index" << endl;
		return;
	}

	cars.erase(cars.begin() + index);
	saveToFile(cars, filename);
}

int main() {
	vector<Car> cars;
	const string filename = "data.txt";

	int choice = 0;
	while (choice != 5) {

		cout << "\nMenu:\n";
		cout << "1. Add car\n";
		cout << "2. View all cars\n";
		cout << "3. Read data from file\n";
		cout << "4. Delete car\n";
		cout << "5. Save and exit\n";
		cout << "Enter your choice: ";

		cin >> choice;


		switch (choice) {

			case 1: 
			{
				Car car;
				car.setData();
				cars.push_back(car);
				break;
			}
			case 2:
			{
				if (cars.empty()) {
					cout << "No data available" << endl;
				}
				else {
					vector <Car>::iterator it;
					for (it = cars.begin(); it != cars.end(); it++) {
						it->displayData();
					}
				}
				break;
			}
			case 3:
			{
				readFromFile(cars, filename);
				break;
			}
			case 4:
			{
				deleteObject(cars, filename);
				break;
			}
			case 5: 
			{
				saveToFile(cars, filename);
				cout << "Exiting.." << endl;
				return 1;
			}

		}



		
	}
	return 0;
}