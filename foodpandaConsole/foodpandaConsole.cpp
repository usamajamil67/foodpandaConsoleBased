#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<conio.h>
#include<chrono>
#include<ctime>
using namespace std;
using namespace chrono;
static float disc;
int main();
//Menue Hover
int showMenu(string list[], int SIZE) {
	int cursor = 0, //this defines cursor position
		choice; // this stores selected option
	do {
		system("cls");
		cout << "-----------------------------------------------------------" << endl;
		cout << "|          $ Welcome to Food Panda Ordering System $      |" << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << "\n            Chose One Of the Following " << endl;

		for (int i = 0; i < SIZE; i++) { //  prints all choices from passed list.
			if (cursor == i) //this prints cursor around a choice, value of cursor can be incremented and decremented.
				cout << "[" << list[i] << "]" << endl;
			else
				cout << list[i] << endl;
		}
		choice = _getch();
		switch (choice)
		{

		case 80: // 80 is keycode for up key
			if (cursor == SIZE - 1)
				cursor = 0;
			else
				cursor++;
			break;
		case 72: //72 is keycode for down key 
			if (cursor == 0)
				cursor = SIZE - 1;
			else
				cursor--;
			break;
		case 13: // 13 is keycode for enter key
			return cursor; // on enter key, selected option index is returned.
			break;
		}
	} while (choice != 13);
}

string fname, lname, username, email, contact, address, password, TOC;
const int SIZE = 100;
void activityLog(string s);

struct login {
	char username[SIZE];
	char password[SIZE];
};

struct createAcc {
	char fname[SIZE];
	char lname[SIZE];
	char username[SIZE];
	char contact[SIZE];
	char email[SIZE];
	char address[SIZE];
	char password[SIZE];
};

string spaceToDash(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (isspace(s[i]) && i != s.length() - 1)
			s[i] = '_';
		if (s[i] == '\n')
			s.erase(i, 1);

	}
	return s;
}

string getTime()
{
	auto timenow = system_clock::to_time_t(system_clock::now());
	return  spaceToDash(ctime(&timenow));
}

void activityLog(string s) {
	ofstream file("activity.log", ios::app);
	file << "[" << getTime() << "]: " << s << endl;
	file.close();
}


void writeNewAcc(createAcc newAcc) {
	ofstream file;
	file.open("users.dat", ios::app);
	file << setw(50) << setfill('=') << "\n";
	file << "username: " << newAcc.username << endl;
	file << "password: " << newAcc.password << endl;
	file << "fname: " << newAcc.fname << endl;
	file << "lname: " << newAcc.lname << endl;
	file << "address: " << newAcc.address << endl;
	file << "email: " << newAcc.email << endl;
	file << "contact: " << newAcc.contact << endl;
	file << "Time of Account Creation: " << getTime() << endl;
	file << setw(50) << setfill('=') << "\n";
	file.close();
	cout << "\nYou have Created an Account Successfully!\n";
	system("pause");
}

void createAccount();

int accountInfo() {
	cout << "Current Account Information";
	cout << "\nName: " << fname << " " << lname
		<< "\nUsername: " << username
		<< "\nAddress: " << address
		<< "\nEmail: " << email
		<< "\nContact: " << contact
		<< "\nPassword: " << password
		<< "\nTime of Account Creation: " << TOC << "\n\n";
	system("pause");
	return 1;
}

int checkUser(char username[]) {
	ifstream file("users.dat");
	string s;
	size_t pos;
	string search = "username: " + (string)username;
	while (file.good()) //not end of file
	{
		getline(file, s);
		pos = s.find(search);
		if (pos != string::npos && s.size() == search.size())
		{
			cout << "\nUser with this Username Already Exists! Try another Username.\n";
			return 1;
		}
	}
	return 0;
}
//Creates Account
void createAccount() {
	createAcc newAcc;
	cout << endl;
	cout << "Create An Account\n";
	cout << "Enter your First Name: "; cin >> newAcc.fname;
	cout << "Enter your Last Name: "; cin >> newAcc.lname;
	do {
		cout << "Enter a Username: "; cin >> newAcc.username;
		int i = 0;
		while (newAcc.username[i] != '\0') {
			if (newAcc.username[i] >= 97 && newAcc.username[i] <= 122)
			{
				newAcc.username[i] = newAcc.username[i] - 32; //Converts Uppercase to Lowercase.
			}
			i++;
		}
	} while (checkUser(newAcc.username));
	cout << "Enter your Address: "; cin >> newAcc.address;
	cout << "Enter your Email: "; cin >> newAcc.email;
	cout << "Enter your Contact: "; cin >> newAcc.contact;
	int length = 0, a = 0;
	do {
		if (a > 0)
			cout << "\nYour Password Must Contain Minimum of 8 Characters!\n";
		cout << "Enter your Password ";
		if (a > 0)
			cout << "Again";
		else
			cout << "(Minimum 8 Characters)";
		cout << ": ";
		cin >> newAcc.password;

		while (newAcc.password[length] != '\0')
			length++;
		a++;
	} while (length < 8);
	writeNewAcc(newAcc);

}

int loginAccount() {
	bool check = 0;
	do {
		cout << endl;
		cout << "Login Panel";
		login login;
		cout << "\nEnter a Username: "; cin >> login.username;
		cout << "Enter your Password: "; cin >> login.password;
		int i = 0;
		while (login.username[i] != '\0') { // '\0' null Character tells end of char array
			if (login.username[i] >= 97 && login.username[i] <= 122)
			{
				login.username[i] = login.username[i] - 32; // converting lowercase to uppercase
			}
			i++;
		}
		ifstream file("users.dat");
		if (!file) {
			cout << "\nNo Database Found.\n";
			system("pause");
		}
		else {
			username = login.username;
			password = login.password;
			string s;
			size_t user_pos;
			size_t pass_pos;
			string user = "username: " + (string)login.username;
			string pass = "password: " + (string)login.password;
			bool acc = 0;
			while (file.good())
			{
				getline(file, s);
				user_pos = s.find(user);
				if (user_pos != string::npos && s.size() == user.size())
				{
					bool pas = 0;
					acc = 1;
					getline(file, s);
					pass_pos = s.find(pass);
					if (pass_pos != string::npos && s.size() == pass.size())
					{
						pas = 1;
						getline(file, s, ':');
						file >> fname;
						getline(file, s, ':');
						file >> lname;
						getline(file, s, ':');
						file >> address;
						getline(file, s, ':');
						file >> email;
						getline(file, s, ':');
						file >> contact;
						getline(file, s, ':');
						file >> TOC;
						activityLog(username + " Logged In.");
						check = 1;
						return 1;
					}
					if (!pas) {
						cout << "\nIncorrect Password.\n";
						system("pause");
						check = 0;
					}
				}

			}
			if (!acc) {
				cout << "\nNo Account found with this Username.\n";
				system("pause");
				check = 0;
			}

			file.close();
		}
	} while (!check);
	return 0;
}
//Forgot Pssword
void forgot()
{
	system("cls");
	int count = 0, i = 0;
	char searchuser[SIZE];
	cout << "\nEnter your remembered username: ";
	cin >> searchuser;
	while (searchuser[i] != '\0') { // '\0' null Character tells end of char array
		if (searchuser[i] >= 97 && searchuser[i] <= 122)
		{
			searchuser[i] = searchuser[i] - 32; // converting lowercase to uppercase
		}
		i++;
	}
	ifstream file("users.dat");
	string s;
	size_t user_pos;
	string user = "username: " + (string)searchuser;
	bool acc = 0;
	while (file.good())
	{
		getline(file, s);
		user_pos = s.find(user);
		if (user_pos != string::npos && s.size() == user.size())
		{
			getline(file, s);
			count = 1;
			break;
		}

	}
	file.close();
	if (count == 1)
	{
		cout << "\n\nCongradulation, account found\n";
		cout << s << endl;
		system("pause");
		main();
	}
	else
	{
		cout << "\nSorry, Your userID not found in our database.\n";
		cout << "\nPlease contact your system administrator for more details.\n";
		system("pause");
		main();
	}

}

int welcome() {
	int loginChoice = 0;

	string menu[4] = { "Login", "Sign Up","Forgot Password", "Exit" };
	loginChoice = showMenu(menu, 4);
	if (loginChoice == 0) {
		if (loginAccount())
			return 1;
	}
	else if (loginChoice == 1) {
		createAccount();
		system("cls");
		if (welcome())
			return 1;
	}
	else if (loginChoice == 2) {
		forgot();
	}
	else if (loginChoice == 3) {
		exit;
	}

	return 0;
}


//Discount Function
float Disc(float choice)
{
	cout << "\nYour Original bill was: " << choice << " RS";

	if (choice >= 5000) {

		disc += choice * 0.5;
		cout << "\nAfter discount it is: " << disc << " RS";
		return disc;
	}
	else
		cout << "\n----------No Discount----------";
	return choice;
}
//Main Menue
int displaymainMenu() {
	int total = 0;
	char name[30], pizza1[] = "Chicken Fazita", pizza2[] = "Chicken Bar BQ", pizza3[] = "Peri Peri", pizza4[] = "Creamy Max", roll1[] = "Chicken Chatni Roll", roll2[] = "Chicken Mayo Roll", roll3[] = "Veg Roll With Fries", bur1[] = "Zinger Burger", bur2[] = "Chicken Burger", bur3[] = "Beef Burger";
	char sand1[] = "Club Sandwich", sand2[] = "Chicken Crispy Sandwich", sand3[] = "Extream Veg Sandwich";
	char bir1[] = "Chicken Biryani", bir2[] = "Prawn Biryani", bir3[] = "Beef Biryani", gotostart;
	int choice = 0, pchoice, pchoice1, quantity, time = 40;
beginning:
	system("CLS");
	cout << "\t\t\t----------WELCOME to FoodPanda-----------\n\n";
	system("cls");
	//cout << "Hello " << name << "\n\nWhat would you like to order?\n\n";

	/*cout << "\n--------------------------Menu-----------------------------------" << endl;
	cout << "|\t1) Pizzas\t.............5 Types" << "\t\t\t|" << endl;
	cout << "|\t2) Burgers\t.............3 Types" << "\t\t\t|" << endl;
	cout << "|\t3) Sandwich\t.............3 Types" << "\t\t\t|" << endl;
	cout << "|\t4) Rolls\t.............3 Types" << "\t\t\t|" << endl;
	cout << "|\t5) Biryani\t.............3 Types" << "\t\t\t|" << endl;
	cout << "-----------------------------------------------------------------" << endl;

	cout << "\nPlease Enter your Choice: ";
	cin >> choice;
	cout << "\n--------------------------Choices--------------------------------" << endl;*/

	string menu[5] = { "Pizzas", "Burgers", "Sandwich", "Rolls", "Biryani" };
	choice = showMenu(menu, 5);
	if (choice == 0)
	{

		string menu[4] = { pizza1,	pizza2, pizza3, pizza4 };
		pchoice1 = showMenu(menu, 4);
		if (pchoice1 >= 0 && pchoice1 <= 3)
		{
			/*cout << "\n1) Small Rs.250\n" << "2) Regular Rs.500\n" << "3) Large Rs.900\n";
			cout << "\nChoose Size Please:";
			cin >> pchoice1;*/
			string menu[3] = { "Small Rs.250" ,"Regular Rs.500","Large Rs.900" };
			pchoice = showMenu(menu, 3);
			if (pchoice >= 0 && pchoice <= 2)
				cout << "\nPlease Enter Quantity: ";
			cin >> quantity;
			switch (pchoice)
			{
			case 0: total += 250 * quantity;
				break;

			case 1: total += 500 * quantity;
				break;

			case 2: total += 900 * quantity;
				break;
			}
			system("CLS");
			switch (pchoice1)
			{
			case 0:
				cout << "\t\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << pizza1;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Please select your payment method." << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 1:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << "  " << pizza2;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 2:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << pizza3;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 3:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << pizza4;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;

			}
			cout << "Would you like to order anything else? Y / N:";
			cin >> gotostart;
			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				return 0;
			}



		}

	}

	else if (choice == 1)

	{
		string menu[3] = { bur1 ,bur2,bur3 };
		pchoice = showMenu(menu, 3);
		/*cout << "\n1 " << bur1 << " Rs.180" << "\n";
		cout << "2 " << bur2 << " Rs.150" << "\n";
		cout << "3 " << bur3 << " Rs.160" << "\n";
		cout << "\nPlease Enter which Burger you would like to have?: ";
		cin >> pchoice1;*/
		if (pchoice >= 0 && pchoice <= 3)
		{
			cout << "\nPlease Enter Quantity: ";
			cin >> quantity;
			switch (pchoice)
			{
			case 0: total += 180 * quantity;
				break;

			case 1: total += 150 * quantity;
				break;

			case 2: total += 160 * quantity;
				break;

			}
			system("CLS");
			switch (pchoice)
			{
			case 0:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << bur1;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 1:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << "  " << bur2;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 2:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << bur3;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;


			}
			cout << "\nWould you like to order anything else? Y / N:";
			cin >> gotostart;
			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				return 0;
			}

		}
	}
	else if (choice == 2)
	{
		string menu[3] = { sand1 ,sand2,sand3 };
		pchoice = showMenu(menu, 3);
		/*cout << "\n1  " << sand1 << " Rs.240" << "\n";
		cout << "2  " << sand2 << " Rs.160" << "\n";
		cout << "3  " << sand3 << " Rs.100" << "\n";
		cout << "\nPlease Enter which Sandwich you would like to have?:";
		cin >> pchoice1;*/
		if (pchoice >= 1 && pchoice <= 3)
		{
			cout << "\nPlease Enter Quantity: ";
			cin >> quantity;
			switch (pchoice)
			{
			case 0: total += 240 * quantity;
				break;

			case 1: total += 160 * quantity;
				break;

			case 2: total += 100 * quantity;
				break;

			}
			system("CLS");
			switch (pchoice)
			{
			case 0:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << sand1;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 1:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << "  " << sand2;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 2:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << sand2;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;


			}
			cout << "Would you like to order anything else? Y / N:";
			cin >> gotostart;
			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				return 0;
			}
		}
	}


	else if (choice == 3)
	{
		string menu[3] = { roll1 ,roll2,roll3 };
		pchoice = showMenu(menu, 3);
		/*cout << "\n1 " << roll1 << " Rs.150" << "\n";
		cout << "2 " << roll2 << " Rs.100" << "\n";
		cout << "3 " << roll3 << " Rs.120" << "\n";
		cout << "\nPlease Enter which you would like to have?: ";
		cin >> pchoice1;*/
		if (pchoice >= 0 && pchoice <= 2)
		{
			cout << "\nHow Much Rolls Do you want: ";
			cin >> quantity;
			switch (pchoice)
			{
			case 0: total += 150 * quantity;
				break;

			case 1: total += 100 * quantity;
				break;

			case 2: total += 120 * quantity;
				break;

			}
			system("CLS");
			switch (pchoice)
			{
			case 0:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << roll1;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 1:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << "  " << roll2;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 2:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << roll3;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;


			}

		}
	}
	else if (choice == 4)
	{
		string menu[3] = { bir1 ,bir2,bir3 };
		pchoice = showMenu(menu, 3);
		/*cout << "\n1 " << bir1 << " Rs.160" << "\n";
		cout << "2 " << bir2 << " Rs.220" << "\n";
		cout << "3 " << bir3 << " Rs.140" << "\n";
		cout << "\nPlease Enter which Biryani you would like to have?:";
		cin >> pchoice1;*/
		if (pchoice >= 0 && pchoice <= 2)
		{
			cout << "\nPlease Enter Quantity: ";
			cin >> quantity;
			switch (pchoice)
			{
			case 0: total += 160 * quantity;
				break;

			case 1: total += 220 * quantity;
				break;

			case 2: total += 140 * quantity;
				break;

			}
			system("CLS");
			switch (pchoice)
			{
			case 0:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << bir1;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 1:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << "  " << bir2;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;
			case 2:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << bir3;
				cout << "\nYour Total Bill is " << Disc(total) << " RS" << endl;
				cout << "Your Order Will be delivered in 40 Minutes" << endl;
				cout << "Thank you For Ordering From FoodPanda." << endl;
				break;


			}
			cout << "Would you like to order anything else? Y / N:";
			cin >> gotostart;
			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				return 0;
			}
		}
	}
	else
	{
		system("CLS");
		cout << "Please Select Right Option: \n";
		cout << "Would You like to Start the program again? Y / N: ";
		cin >> gotostart;

		if (gotostart == 'Y' || gotostart == 'y')
		{
			goto beginning;
			return 0;
		}
	}
}
int main()
{
	if (welcome())
		displaymainMenu();
	return 0;
}
