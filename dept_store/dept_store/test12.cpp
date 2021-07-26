#include<iostream>
#include<fstream>
#include "E:/delme.cpp"
using namespace std;

class A
{
	string a;
	string b;
	public:
		void get()
		{
			fflush(stdin);
			getline(cin, a);
			getline(cin, b);
			
			fstream f;
			f.open("testbin.dat", ios::binary | ios::out);
			f.write((char*)this, sizeof(*(this)));
			f.close();
		}
		
		void modify_a()
		{
			fstream f, f1;
			f.open("testbin.dat", ios::binary | ios::in);
			f.read((char*)this, sizeof(*(this)));
			f.close();
			fflush(stdin);
			getline(cin, a);
			f.open("testbin.dat", ios::binary | ios::out);
			f.write((char*)this, sizeof(*(this)));
			f.close();			
		}
		
		void show()
		{
			cout<<a<<" "<<b<<endl;
		}
		
};

int main()
{
	A a;
	a.modify_a();
	
	A b;
	fstream f1;
	f1.open("testbin.dat", ios::binary | ios::in);
	f1.read((char*)&b, sizeof(b));
	f1.close();
	b.show();
	DelMe();
	return 0;
}
