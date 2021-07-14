/*
Features of our project:

	Dealer(or Admin)
						***Password  protected***
		newProd() -> To add new products with product name, price and quantity.
		dispStock() -> To display the current stock.
		refill() -> Refill or restock current products.
		removeItem() -> To remove a certain product by entering the product name.
		empName() -> Has the name, employee ID number, salary and attandance of all the employees.
		viewAttendance() -> Shows the Employee name, Employee ID and Employee Attandance of all Employees.
		dailyAttandance() -> Marks the attandance of all the employees daily.
		removeEmp() -> To remove an employee by typing the employee ID number.

	Employee 
		newProd() -> To add new products with product name, price and quantity.
		dispStock() -> To display the current stock.
		refill() -> Refill or restock current products.
		removeItem() -> To remove a certain product by entering the product name.
	Customer
		buyProd() -> Displays all the products, its quantity available and its price and 
					 asks the user to enter the name and quantity of the product to be purchased.
		getBill() -> Generates the bill for the products bought by the customer.
*/
#include<iostream>
#include<string.h>
#include<conio.h>
#include<math.h>
#include<fstream>

using namespace std;

int num, i;
fstream fileOne;
ifstream fin;
ofstream fout;

void dispStock();

//**************************************************************Product Class**************************************************************
class Products
{
public:
	char prodName[30];
	int prodNumber;
	float Price;
	int Quantity;
	void refill(int qty)
	{

		Quantity += qty;
		cout << "\n\nStock updated.";
		//getch();  Error: Return value ignored getch()

	}
	void show()
	{

		cout << "\n" << prodName << "\t\t" << prodNumber << "\t\t" << Price << "\t\t" << Quantity;
	}
	void get()
	{
		cin >> prodName >> prodNumber >> Price >> Quantity;

	}
	int prodCheck(char nm[30])
	{
		if (strcmp(nm, prodName) == 0)
			return 0;
		else
			return 1;
	}
	void removeItem(int qty)
	{
		if (Quantity >= qty)
		{
			Quantity -= qty;
			cout << "\n\nStock updated.\n";
		}
		else
			cout << "\n\nInsufficient stock";
		//getch();  Error: Return value ignored getch()
	}
}st;  //________object created along with the class________

//**************************************************************Employee Class**************************************************************
class Employee : protected Products
{
	string ename[50];
	int eid[50];
	float salary[50];
	int attandance[50];

protected:

	void newProd()
	{
		system("cls");

		dispStock();
		//getch();  Error: Return value ignored getch()
		system("cls");

		cout << "\nEnter the No. of Products that you wish to add: ";
		cin >> num;

		if (num != 0)
		{

			fout.open("shop.dat", ios::binary | ios::app);
			for (i = 0; i < num; i++)

			{

				cout << "\n\nInput the name, price and the quantity of item respectively\n\n";
				st.get();
				fout.write((char*)&st, sizeof(st));
				cout << "\n\nitem updated";
				cin.get();


			}
			cout << "\n\nStock Updated!!";

			fout.close();
			cin.get();
			system("cls");
			dispStock();
		}

		else
		{

			fout.close();
			cin.get();
			system("cls");
			cout << "\n\nNo items to be added";

		}
	}
	void refill()
	{
		system("cls");
		char temp[100]; int qty;
		int i = 0;
		long pos = 0;
		dispStock();
		cout << "\n\nEnter the products name \n" << endl;
		cin >> temp;
		cout << "\n\nEnter quantity: \n" << endl;
		cin >> qty;
		fileOne.open("shop.dat", ios::binary | ios::out | ios::in);
		while (fileOne)
		{
			pos = fileOne.tellp();
			fileOne.read((char*)&st, sizeof(st));
			if (st.prodCheck(temp) == 0)
			{

				st.refill(qty);
				fileOne.seekp(pos);
				fileOne.write((char*)&st, sizeof(st));
				i++; break;
			}
		}
		if (i != 1)
			cout << "\n\n!!Record not found!!";
		fileOne.close();
		system("cls");
		cin.get();
		dispStock(); cin.get();
	}
};

//****************************************************Individual Functions***************************************************
void dispStock()
{
	int i = 1;
	cout << "\n==================================================================";
	cout << "\n\n=================\tTHE STOCK ITEMS ARE\t==================";
	cout << "\n\n==================================================================\n";
	cout << "\nName\t Product No.\tPrice\t Quantity";
	cout << "\n\n============================================================\n";
	fin.open("shop.dat", ios::binary);
	while (!fin.eof())
	{
		fin.read((char*)&st, sizeof(st));
		if (!fin.eof())
		{
			if (fin.tellg() < 0)
			{
				i = 0; break;
			}
			st.show();
		}
	}
	if (i == 0)
	{
		cout << "\n\n\t\t\t!!Empty record room!!";
		//getch();  Error: Return value ignored getch()
	}
	fin.close();
}

// ***************************************************main function***************************************************
int main()
{

	char filename[] = "store.txt";
	fstream fileOne;

	fileOne.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

	// If file does not exist, Creating new file
	if (!fileOne)
	{
		cout << "Cannot open file as file does not exist. \nCreating new file...";

		fileOne.open(filename, fstream::in | fstream::out | fstream::trunc);
		fileOne << "\n";
		fileOne.close();

	}
	else
	{    // use existing file
		cout << "Success! " << filename << " found. \n";
		fileOne.close();
		cout << "\n";

	}
	return 0;
}
