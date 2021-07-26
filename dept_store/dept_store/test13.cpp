#include<iostream>
#include<iomanip>
#include "E:/delme.cpp"
using namespace std;

int main()
{
	cout<<setw(25 + 11)<<"!! Empty record room !!"<<endl;
	cout<<"\t     !! Empty record room !!";
	
	cout<<endl<<endl;
	for(int i=0;i<50;i++) cout<<"=";
	cout<<endl;
	
	DelMe();
	return 0;
}
