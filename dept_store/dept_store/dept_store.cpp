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
#include<iomanip>
#include<string.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<vector>
#include<fstream>
#include<ctime>

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
			cout<<"\n"<<prodName<<setw(36 - strlen(prodName))<<prodNumber<<setw(17)<<Price<<setw(20)<<Quantity;
		}
		void get()
		{
			cout<<"Enter product name: ";
			cin>>prodName;
			cout<<"Enter product ID: ";
			cin>>prodNumber;
			cout<<"Enter MRP: ";
			cin>>Price;
			cout<<"Enter quantity: ";
			cin>>Quantity;
		}
		int prodCheck(char nm[30])
		{
			if (strcmp(nm, prodName) == 0)
				return 0;
			else
				return 1;
		}
		/*
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
		*/
		// buyProd() supplement function
		int sellProd(int qty)
		{
			int ret_val = 0;
			if (Quantity >= qty)
				Quantity -= qty;
			else
				ret_val = 1;
			
			return ret_val;
		}
		
		void custQty(int qty)
		{
			Quantity = qty;
		}
		
		float totalPrice()
		{
			return (Price * Quantity);
		}
		
		void showBilling()
		{
			cout<<"\n"<<prodName<<setw(36 - strlen(prodName))<<prodNumber<<setw(14)<<Price<<setw(12)<<Quantity<<setw(12)<<totalPrice();
		}
		
		
}st;  //________object created along with the class________

//**************************************************************Employee Class**************************************************************
class Employee : protected Products
{
	protected:	
		string ename;
		int eid;		//limit eid to 4 digits
		double salary;
		int attendance;

	public:
		void newProd()
		{
			//system("cls");	
			//dispStock();
			int num;
			system("cls");
			cout<<"\nEnter the No. of Products that you wish to add: ";
			cin>>num;
			
			Products p[num];

			if (num != 0)
			{
				fout.open("shop.dat", ios::binary | ios::app);
				for (int i = 0; i < num; i++)
				{	
					cout << "\n\nInput the name, price and the quantity of item respectively\n\n";
					p[i].get();
					fout.write((char*)&p[i], sizeof(p[i]));
					cout<<"\n\nitem updated";
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
			refill_totop:
			system("cls");
			char temp[30]; int qty;
			int j = 0;
			long pos = 0;
			dispStock();
			cout<<"\nEnter the products name: ";
			cin>>temp;
			
			cout<<"Enter quantity: ";
			cin>>qty;
			
			// adding negative int check
			if (qty < 0)
			{
				cout<<"\nQuantity cannot be negative.\nPress any key to re-enter"<<endl;
				getch();
				goto refill_totop;
			}
			
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
					j++; 
					break;
				}
			}
			
			if (j == 0)
			{
				cout<<"\n\n!!Record not found!!";
				getch();
				fileOne.close();
				goto refill_totop;
			}
			fileOne.close();
			system("cls");
			cin.get();
			dispStock();
			cin.get();
		} 
};

//****************************************************Individual Functions***************************************************
void dispStock()
{
	int i = 1;
	/*
	cout << "\n==================================================================";
	cout << "\n\n=================\tTHE STOCK ITEMS ARE\t==================";
	cout << "\n\n==================================================================\n";
	cout << "\nName\t Product No.\tPrice\t Quantity";
	cout << "\n\n============================================================\n";
	*/
	
	for (int i=0;i<74;i++) cout<<"=";
	cout<<endl<<endl;
	cout<<setw(49)<<"THE STOCK ITEMS ARE"<<endl<<endl;
	for (int i=0;i<74;i++) cout<<"=";
	cout<<endl<<endl;
	cout<<"Name"<<setw(32)<<"Product_ID"<<setw(17)<<"Price"<<setw(20)<<"Quantity";
	cout<<endl<<endl;
	for (int i=0;i<74;i++) cout<<"=";
	cout<<endl;
	
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
	
	cout<<endl<<endl;
	for (int i=0;i<74;i++) cout<<"=";
	cout<<endl;
	
	fin.close();
}

// file check [for any db file exist check]
bool ifFileExists(string file)
{
	ifstream f(file);
	return f.good();
}

// for hiding password
/*
	IMPLEMENT LIKE THIS:
	main()
	{
		int limit = 10;			// say.. we can add custom limit [another method]
		string pass = PasswordHide(limit);			//function call
		cout<<"Your entered password: "<<pass<<endl;	// showing the returned string..
	}
*/
string PasswordHide (int limit)
{
	char pass[limit];
	int i;
	while(i < limit)
	{
		pass[i] = getch();
		putch('*');
		i++;
	}
	cout<<endl;
	return pass;
}

string getTime()
{
	time_t ttime = time(0);
	tm *local_time = localtime(&ttime);
	
	string hr = ((local_time->tm_hour) / 10 == 0) ? "0" + to_string(local_time->tm_hour) : to_string(local_time->tm_hour);
	string min = ((local_time->tm_min) / 10 == 0) ? "0" + to_string(local_time->tm_min) : to_string(local_time->tm_min);
	string sec = ((local_time->tm_sec) / 10 == 0) ? "0" + to_string(local_time->tm_sec) : to_string(local_time->tm_sec);
	
	return(hr + ":" + min + ":" + sec);
}

string getDate()
{
	time_t ttime = time(0);
	tm *local_time = localtime(&ttime);
	
	string year = to_string(1900 + local_time->tm_year);
    string mnth = ((1 + local_time->tm_mon) / 10 == 0) ? "0" + to_string(1 + local_time->tm_mon) : to_string(1 + local_time->tm_mon);
    string day = ((local_time->tm_mday) / 10 == 0) ? "0" + to_string(local_time->tm_mday) : to_string(local_time->tm_mday);
    
    return (day + "/" + mnth + "/" + year);
    
}

//******************************************************* Dealer Class ********************************************************

class Dealer : public Employee
{
	public:
		void addEmp()
		{
			fflush(stdin);
			cout<<"Enter name of employee: ";
			getline(cin, ename);
			cout<<"Enter Employee ID: ";
			cin>>eid;
			cout<<"Enter base salary: ";
			cin>>salary;
		}	
		
		void viewEmp()
		{
			/*	// shows individual records
			USE THIS IN main() WHILE DISPLAYING EMP DETAILS
			cout<<"EMP_NAME"<<setw(21)<<"EID"<<setw(20)<<"SALARY"<<endl;
			*/
			cout<<ename<<setw(29 - ename.length())<<eid<<setw(20)<<salary<<endl;	
		}
		void viewAttendance()
		{
			/*	// shows individual records
			USE THIS IN main() WHILE DISPLAYING EMP DETIALS
			cout<<"EMP_NAME"<<setw(21)<<"EID"<<setw(20)<<"ATTENDANCE"<<endl;
			*/
			cout<<ename<<setw(29 - ename.length())<<eid<<setw(20)<<attendance<<endl;
		}
};

// *********************************************** Customer Class *************************************************************

class Customer : protected Products					// in progress
{
	vector<Products> list;
	
	public:
	void buyProd()
	{
		buypr_top:
		system("cls");
		dispStock();
		
		char temp[30];
		int qty, tag = 0;
		long pos = 0;
		
		cout<<endl<<endl<<"Enter following details to purchase:"<<endl;
		cout<<"Enter product name: ";
		cin>>temp;
		
		fileOne.open("shop.dat", ios::binary | ios::out | ios::in);
		while (fileOne)
		{
			pos = fileOne.tellp();
			fileOne.read((char*)&st, sizeof(st));
			if (st.prodCheck(temp) == 0)
			{
				
				cout<<"Enter quantity: ";
				cin>>qty;
				
				int a = st.sellProd(qty);
				if (a == 0)
				{
					fileOne.seekp(pos);
					fileOne.write((char*)&st, sizeof(st));
					
					st.custQty(qty);
					list.push_back(st);
					
					cout<<endl<<"\nItem added to cart.."<<endl;
					tag++;
					break;
				}
				else
				{	
					tag = 2;
					break;
				}
			}
		}
		
		if (tag == 0)
		{
			cout<<"\nProduct not found. Please re-enter the details"<<endl;
			getch();
			fileOne.close();
			goto buypr_top;	
		}
		
		if (tag == 2)
		{
			cout<<"\nInsufficient Stock. Please re-enter valid details."<<endl;
			getch();
			fileOne.close();
			goto buypr_top;
		}
		
		else
		{
			cout<<"Press any key to continue"<<endl;
			getch();
			fileOne.close();
		}
		
	}
	
	void genBill()
	{
		// create a getStoreName() and setStoreName() independent function [user-defined name]	{access only to admin}
		// replace the line as:
		// string name = getStoreName()
		// code capable of resizing text to align by itself.
		string name = "Departmental Store";
		
		system("cls");
		string date = getDate();
		string time = getTime();
		
		for (int i=0;i<74;i++) cout<<"=";
		cout<<endl<<endl;
		
		cout<<setw(37 + (name.length())/2)<<name<<endl<<endl;
		
		for (int i=0;i<74;i++) cout<<"=";
		cout<<endl;
		cout<<setw(40)<<"INVOICE"<<endl;
		for (int i=0;i<74;i++) cout<<"=";
		cout<<endl;
		cout<<"Date: "<<date<<setw(72 - 14 - time.length())<<"Time: "<<time<<endl;
		for (int i=0;i<74;i++) cout<<"=";
		cout<<endl<<endl;
		
		cout<<"ProductName"<<setw(25)<<"ID"<<setw(14)<<"Price"<<setw(12)<<"Qty"<<setw(12)<<"Net"<<endl;
		
		// reference..
		
		float total;
		
		for (auto i=list.begin(); i<list.end(); i++)
		{
			(*i).showBilling();
			total += (*i).totalPrice();
		}
		cout<<endl<<endl;
		
		for (int i=0;i<74;i++) cout<<"=";
		cout<<endl;
		
		cout<<setw(37 + 2 + 24)<<"Total:"<<setw(35 - 24)<<total<<endl;
	
		for (int i=0;i<74;i++) cout<<"=";
		cout<<endl;
		
		cout<<setw(37 + 13)<<"## Thank You Visit Again ##"<<endl;
		
		for (int i=0;i<74;i++) cout<<"=";
		cout<<endl;
	}
};

// ***************************************************main function***************************************************
int main()
{
	/*
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
	}*/
	
	Dealer d;
	//d.addEmp();
	//d.newProd();
	//d.refill();
	//dispStock();
	Customer c;
	
	char choice;
	
	while (tolower(choice) != 'n')
	{
		c.buyProd();
		cout<<"\nDo you want to continue shopping? (Y/N): ";
		cin>>choice;
	}
	
	c.genBill();
	
	return 0;
}