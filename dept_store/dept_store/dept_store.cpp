/*
Features of our project:
	Dealer(or Admin)
						***Password  protected***
		newProd() -> To add new products with product name, price and quantity.
		refill() -> Refill or restock current products.
		initRun() -> sets default login password for first execution.
		enterPassword() -> gets the password input from user and checks it.
		modifyPassword() -> function to change admin login password manually.
		addNewEmp() -> to add new Employee record
		viewAllEmp() -> to view all records of Employees
		
	Employee 
		newProd() -> To add new products with product name, price and quantity.
		refill() -> Refill or restock current products.
			// supplementary functions to Dealer class
			addEmp()
			viewEmp()
		
	Customer
		buyProd() -> Displays all the products, its quantity available and its price and 
					 asks the user to enter the name and quantity of the product to be purchased.
		genBill() -> Generates the bill for the products bought by the customer.
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
#include<stdio.h>

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
			cout<<ename<<setw(29 - ename.length())<<eid<<setw(21)<<salary<<endl;	
		}
		
}emp;

//****************************************************Individual Functions***************************************************
void dispStock()
{
	int i = 1;
	
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
		//cout << "\n\n\t\t\t!!Empty record room!!";
		cout<<setw(37 + 11)<<"!! Empty record room !!";
	}
	
	cout<<endl<<endl;
	for (int i=0;i<74;i++) cout<<"=";
	cout<<endl;
	
	fin.close();
}

string PasswordHide()
{
	char pass[30];
	int i = 0;
	char a;
	while (1)
	{
		a = getch();
		if ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') || (a >= '0' && a <= '9'))
		{
			pass[i] = a;
			i++;
			cout<<"*";
		}
		if (a == '\b' && i>0)
		{
			cout<<"\b \b";
			i--;
		}
		if (a == '\r')
		{
			pass[i] = '\0';
			break;
		}
	}
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

// checks if program has been executed before
int checkIfInit()
{
	int n;
	ifstream r("init.txt");
	if (r.is_open())
	{
		r >> n;
		n++;
	}
	r.close();
	
	ofstream o("init.txt");
	o << n;
	o.close();
	return n;	
}

//******************************************************* Dealer Class ********************************************************

fstream empRec;

// function to create designer lines
// function created to fix issue while using setw() in viewAllEmp() function.
void prettyPrintEmp()
{
	for(int i=0;i<50;i++) cout<<"=";
	cout<<endl;
}

class Dealer : public Employee
{
	//string storeName;
	string accessPwd;
	public:
		
		void initRun()
		{
			//this->storeName = "Departmental_Store";
			this->accessPwd = "admin";
			
			fstream fil;
			fil.open("Dealer.dat", ios::binary | ios::out);
			fil.write((char*)this, sizeof(*(this)));
			fil.close();
		}
		
		int enterPassword()
		{
			string l;
			
			cout<<"NOTE: Max Password length is 30"<<endl;
			cout<<"Password can contain only the following:\na - z, A - Z, 0 - 9"<<endl<<endl;
			cout<<"Enter password: ";
			l = PasswordHide();
			
			fstream f;
			f.open("Dealer.dat", ios::binary | ios::in);
			f.read((char*)this, sizeof(*(this)));
			f.close();
			
			if (l == this->accessPwd)
				return 1;
			else
				return 0;
		}
		
		void modifyPassword()
		{
			string h;
			cout<<"Enter new password: ";
			h = PasswordHide();
			
			fstream f;
			f.open("Dealer.dat", ios::binary | ios::in);
			f.read((char*)this, sizeof(*(this)));
			f.close();
			
			this->accessPwd = h;
			
			fstream f1;
			f1.open("Dealer.dat", ios::binary | ios::out);
			f1.write((char*)this, sizeof(*(this)));
			f1.close();
			
		}
		
		void addNewEmp()
		{
			emp.addEmp();				
			empRec.open("empData.dat", ios::binary | ios::app);
			empRec.write((char*)&emp, sizeof(emp));
			empRec.close();		
		}
		
		void viewAllEmp()
		{
			prettyPrintEmp();	
			cout<<"EMP_NAME"<<setw(21)<<"EID"<<setw(21)<<"SALARY"<<endl;
			prettyPrintEmp();	
			int isData = 0;
			empRec.open("empData.dat", ios::binary | ios::in);
			while(!empRec.eof())
			{
				empRec.read((char*)&emp, sizeof(emp));
				if (!empRec.eof())
				{
					if (empRec.tellg() < 0)
					{
						isData = 0; break;
					}
					emp.viewEmp();
					isData = 1;
				}	
			}
			
			empRec.close();
			
			if (isData == 0)
			{
				//cout << "\n\n\t\t!!Empty record room!!";
				cout<<"\t     !! Empty record room !!"<<endl;
			}
			
			prettyPrintEmp();
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
		//cout<<setw(37 + (len)/2)<<name<<endl<<endl;
		
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

	Dealer b;
	int run = checkIfInit();
	if (run == 0)
	{
		b.initRun();
	} 
	
	int c0;
	do
	{
		system("cls");
		
		for(int i=0;i<70;i++) cout<<"=";
		cout<<endl;
		cout<<setw(70 - 17)<<"Departmental Store Management System"<<endl;
		for(int i=0;i<70;i++) cout<<"=";
		cout<<endl;
		cout<<setw(40)<<"Main Menu"<<endl;
		for(int i=0;i<70;i++) cout<<"=";
		cout<<endl<<endl;
		
		cout<<setw(10)<<"	Select an option:\n\n	1.Admin/Dealer login\n	2.Employee\n	3.Customer\n	4.Exit"<<endl<<endl;
		cout<<"	Enter your choice: ";
		cin>>c0;
		
		if (c0 == 1)
		{
		 	a:
			// password check
			system("cls");
			int chk = b.enterPassword();
			if (chk == 0)
			{
				goto a;	
			}
			int c1;
			do
			{
				system("cls");
				
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl;
				cout<<setw(70 - 17)<<"Departmental Store Management System"<<endl;
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl;
				cout<<setw(41)<<"Admin Menu"<<endl;
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl<<endl;
				
				cout<<"	Select an option:\n\n	1. Change login password\n	2. Add New Product\n	3. Refill Stock\n	4. Check Stock\n	5. Add New Employee\n	6. View All Employee\n	7. Exit to main menu"<<endl<<endl;
				cout<<"	Enter your choice: ";
				cin>>c1;
				
				if (c1 == 1)
				{
					system("cls");
					b.modifyPassword();
					getch();
				}
				if (c1 == 2)
				{
					b.newProd();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
				if (c1 == 3)
				{
					b.refill();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
				if (c1 == 4)
				{
					system("cls");
					dispStock();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
				
				if (c1 == 5)
				{
					system("cls");
					b.addNewEmp();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
				
				if (c1 == 6)
				{
					system("cls");
					b.viewAllEmp();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
				
			}while(c1 != 7);
		}
		
		if (c0 == 2)
		{
			int c2;
			Employee e;
			do{
				system("cls");
		
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl;
				cout<<setw(70 - 17)<<"Departmental Store Management System"<<endl;
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl;
				cout<<setw(41)<<"Employee Menu"<<endl;
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl<<endl;
				
				cout<<"	Select an option:\n\n	1. Add New Product\n	2. Refill Stock\n	3. Check Stock\n	4. Exit to main menu"<<endl<<endl;
				cout<<"	Enter your choice: ";
				cin>>c2;
				
				if (c2 == 1)
				{
					e.newProd();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
				if (c2 == 2)
				{
					e.refill();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
				if (c2 == 3)
				{
					system("cls");
					dispStock();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
			}while(c2 != 4);
		}
		
		if (c0 == 3)
		{
			int c3;
			Customer c;
			do
			{
				system("cls");
				
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl;
				cout<<setw(70 - 17)<<"Departmental Store Management System"<<endl;
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl;
				cout<<setw(41)<<"Customer Menu"<<endl;
				for(int i=0;i<70;i++) cout<<"=";
				cout<<endl<<endl;
				
				cout<<"	Select an option\n\n	1. View Product list\n	2. Purchase\n	3. Exit to main menu"<<endl<<endl;
				cout<<"	Enter your choice: ";
				cin>>c3;
				
				if (c3 == 1)
				{
					system("cls");
					dispStock();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
				}
				
				if (c3 == 2)
				{
					char choice;
	
					while (tolower(choice) != 'n')
					{
						c.buyProd();
						cout<<"\nDo you want to continue shopping? (Y/N): ";
						cin>>choice;
					}
					c.genBill();
					cout<<"\n\nPress any key to continue"<<endl;
					getch();
					// print bill to storage
					fstream file;
					string fn = "Bills/file" + to_string(run) + ".txt";
					file.open(fn, ios::out);
					streambuf* stream_buffer_cout = cout.rdbuf();
   					streambuf* stream_buffer_cin = cin.rdbuf();
   					streambuf* stream_buffer_file = file.rdbuf();
   					cout.rdbuf(stream_buffer_file);
   					c.genBill();
   					cout.rdbuf(stream_buffer_cout);
				}
				
			}while(c3 != 3);
		}
		
	}while(c0 != 4);	
	return 0;
}