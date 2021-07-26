#include<iostream>
#include<vector>
#include "E:/delme.cpp"
using namespace std;

class A
{
	int a;
	char c;
	public:
		void get()
		{
			cin>>a;
			cin>>c;
		}
		void show()
		{
			cout<<"int: "<<a<<endl;
			cout<<"char: "<<c<<endl;
		}
};

class B
{
	vector<A> list;
	public:	
};


int main()
{
	DelMe();
	return 0;
}
