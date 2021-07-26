//#include<bits/stdc++.h> // for competitive programming
//#include<cstdio> // c lang stdio func
//#include<stdlib>  // std library
//#include<unistd>
#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
#include "E:/delme.cpp"
using namespace std;

class Products
{
	char prodName[30];
	int prodNumber;
	int Price;
	int Quantity;
	
	public:

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
	
};

class Customer : protected Products
{
	public:
		void genBill(vector<Products> list)
		{
			for (auto i=list.begin(); i<list.end(); i++)
			{
				(*i).show();
			}
		}
};

int main()
{
	Products p;
	vector<Products> list;
	
	char choice;
	
	while (tolower(choice) != 'n')
	{
		p.get();
		list.push_back(p);
		cout<<"\nDo you want to continue shopping? (Y/N): ";
		cin>>choice;
	}
	
	Customer c;
	c.genBill(list);
	
	DelMe();
	return 0;
}
