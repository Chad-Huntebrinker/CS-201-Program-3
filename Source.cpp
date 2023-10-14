//Chad Huntebrinker
//crh92d@umsystem.edu
//12567690
//10/12/20


#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void getUserInfo(int userID[], string userFirstName[], string userLastName[], double userSaving[],
					double userChecking[], const int arraySize);

void printCustomersData(const int userID[], const string userFirstName[], const string userLastName[], const double userSaving[],
						const double userChecking[], const int arraySize);

void printNames(string userFirstName1[], string userLastName1[], int arraySize);

void printBankTotal(double userSaving[], double userChecking[], const int arraySize);

int main() {
	const int arraySize = 10;
	int userID[arraySize];
	string userFirstName[arraySize];
	string userLastName[arraySize];
	string userFirstName1[arraySize];
	string userLastName1[arraySize];
	double userSaving[arraySize];
	double userChecking[arraySize];
	char userInput;
	
	cout << fixed << setprecision(2);
	
	// This program is used to enter the information from the input file to the arrays

	getUserInfo(userID, userFirstName, userLastName, userSaving, userChecking, arraySize);

	/* 
	This loop is used to enter the first and last names of the bank customers into an identical
	array.  The reason for doing this is so that the original list of names doesn't get changed
	when the program needs to order the names alphabetically. Then we have the original array
	of names and an array ordered by their last name.
	*/
	for (int x = 0; x < arraySize; ++x) {
		userFirstName1[x] = userFirstName[x];
		userLastName1[x] = userLastName[x];
	}

	//This do...while loop is used so that when the user enters q/Q, the program exits.
	do {
		cout << "To print customer information, enter 1." << endl;
		cout << "To print all customers Names ordered by their Last Name, enter 2." << endl;
		cout << "To print Bank's total amount, enter 3." << endl;
		cout << "To quit, enter Q/q." << endl;
		cin >> userInput;

		switch (userInput) {
		case '1':
			printCustomersData(userID, userFirstName, userLastName, userSaving, userChecking, arraySize);
			break;
		case '2':
			printNames(userFirstName1, userLastName1, arraySize);
			break;
		case '3':
			printBankTotal(userSaving, userChecking, arraySize);
			break;
		case 'q':
		case 'Q':
			cout << endl;
			cout << "Goodbye" << endl;
			userInput = toupper(userInput);
			break;
		default:
			cout << endl;
			cout << "Invalid input. Please enter a number listed with one of the four options." << endl;
			cout << endl;
			break;
		}

	} while (userInput != 'Q');
	


	return 0;
}

/*
The purpose of this function is to get the information from the file and transfer it to the program.
If the file fails to open, then the error message on line 101 will show.
*/
void getUserInfo(int userID[], string userFirstName[], string userLastName[], double userSaving[],
	double userChecking[], const int arraySize) {
	ifstream fin;
	int tempID, x = 0;
	string tempFirstName, tempLastName;
	double tempSaving, tempChecking;

	fin.open("program3input.txt");
	
	if (fin.fail()) {
		cout << "Failed to open file. Please try again." << endl;
	}

	while (fin >> tempID && x < arraySize) {
		fin >> tempFirstName >> tempLastName;
		fin >> tempSaving >> tempChecking;

		userID[x] = tempID;
		userFirstName[x] = tempFirstName;
		userLastName[x] = tempLastName;
		userSaving[x] = tempSaving;
		userChecking[x] = tempChecking;
		++x;
	}

}

//The purpose of this function is to output the information from the file in a neat and orderly way

void printCustomersData(const int userID[], const string userFirstName[], const string userLastName[], 
	const double userSaving[], const double userChecking[], const int arraySize) {

	int x = 0;

	cout << endl;
	cout << "Last Name , First Name , ID , Saving Account , Checking Account" << endl;
	cout << setfill('-') << setw(63) << "" << endl;
	cout << setfill(' ');
	do {
		cout << setw(9) << userLastName[x] << " , ";
		cout << setw(10) << userFirstName[x] << " , ";
		cout << setw(3) << userID[x] << ", ";
		cout << setw(16) << userSaving[x] << " , ";
		cout << setw(14) << userChecking[x] << endl;

		++x;
	} while (x < arraySize);
	cout << setfill('-') << setw(63) << "" << endl;
	cout << setfill(' ') << endl;

}

/* 
The purpose of this function is to list the names of the customers in the bank in alphabetical order by their
their last name.  If their last name is the same, it then compares it with the first name.
 */
void printNames(string userFirstName1[], string userLastName1[], int arraySize) {
	int i = 0, x;
	string temp1, temp2;
	for (i = 1; i < arraySize; ++i) {
		x = i;
		while (x > 0 && userLastName1[x] < userLastName1[x - 1]) {
			temp1 = userLastName1[x];
			userLastName1[x] = userLastName1[x - 1];
			userLastName1[x - 1] = temp1;
			temp2 = userFirstName1[x];
			userFirstName1[x] = userFirstName1[x - 1];
			userFirstName1[x - 1] = temp2;
			--x;
			if (userLastName1[x] == userLastName1[x - 1] && userFirstName1[x] < userFirstName1[x - 1]) {
				temp1 = userLastName1[x];
				userLastName1[x] = userLastName1[x - 1];
				userLastName1[x - 1] = temp1;
				temp2 = userFirstName1[x];
				userFirstName1[x] = userFirstName1[x - 1];
				userFirstName1[x - 1] = temp2;
			}
		}
	}
	cout << endl;
	cout << "Last Name  , First Name" << endl;
	cout << setfill('-') << setw(22) << "" << endl;
	cout << setfill(' ');
	

	for (i = 0; i < arraySize; ++i) {
		cout << setw(10) << userLastName1[i] << " , " << setw(9) << userFirstName1[i] << endl;
	}
	cout << setfill('-') << setw(22) << "" << endl;
	cout << setfill(' ') << endl;
}

//The purpose of this function is to print the total of the bank's savings and checking account

void printBankTotal(double userSaving[], double userChecking[], const int arraySize) {
	double temp1, temp2, savingTotal = 0, checkingTotal = 0;
	int i;
	
	for (i = 0; i < arraySize; ++i) {
		temp1 = userSaving[i];
		temp2 = userChecking[i];
		savingTotal = temp1 + savingTotal;
		checkingTotal = temp2 + checkingTotal;
	}
	cout << setfill('-') << setw(62) << "" << endl;
	cout << setfill(' ');
	cout << "Bank Savings total is " << savingTotal << " and Checking total is " << checkingTotal << endl;
	cout << setfill('-') << setw(61) << "" << endl;
	cout << setfill(' ') << endl;
}

