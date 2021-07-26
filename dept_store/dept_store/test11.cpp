#include<iostream>
#include<iomanip>
#include "E:/delme.cpp"
using namespace std;

int main()
{
	for(int i=0;i<70;i++) cout<<"=";
	cout<<endl;
	cout<<setw(70 - 17)<<"Departmental Store Management System"<<endl;
	for(int i=0;i<70;i++) cout<<"=";
	cout<<endl;
	cout<<setw(40)<<"Main Menu"<<endl;
	for(int i=0;i<70;i++) cout<<"=";
	cout<<endl<<endl;
	
	cout<<setw(10)<<"	Select an option:\n\n	1.Admin/Dealer login\n	2.Employee\n	3.Customer"<<endl<<endl;
	cout<<"	Enter your choice: "<<endl<<endl;
	
	for(int i=0;i<70;i++) cout<<"=";
	cout<<endl;
	for(int i=0;i<70;i++) cout<<"=";
	cout<<endl;
	
	DelMe();
	return 0;
}
