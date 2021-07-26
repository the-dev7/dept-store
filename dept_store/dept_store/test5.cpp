#include<iostream>
#include<iomanip>
#include<fstream>
//#include<windows.h>
#include "E:/delme.cpp"
#include "dept_store.cpp"
using namespace std;

int centerX()
{
	CONSOLE_SCREEN_BUFFER_INFO scr;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &scr);
	int cnt_x = (scr.srWindow.Right - scr.srWindow.Left) / 2;
	return cnt_x; 
}

void show()
{
	int mid_x = centerX();
	
	for (int i=0;i<74;i++) cout<<"=";
	cout<<endl<<endl;
	//cout << "\n=================================================================="<<endl;
	cout<<setw(49)<<"THE STOCK ITEMS ARE"<<endl<<endl;
	
	for (int i=0;i<74;i++) cout<<"=";
	cout<<endl<<endl;
	
	cout<<"Name"<<setw(30)<<"Product No."<<setw(20)<<"Price"<<setw(20)<<"Quantity";
	
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
	
}

int main()
{
	show();
	DelMe();
	return 0;
}
