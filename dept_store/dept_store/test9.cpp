#include<iostream>
#include<fstream>
#include "E:/delme.cpp"
using namespace std;

class Test
{
	int a;
	string s;
	double d;
	
	public:
		void get()
		{
			fflush(stdin);
			getline(cin, s);
			cin>>a;
			cin>>d;
			
			fstream f;
			f.open("hello.dat", ios::binary | ios::out);
			f.write((char*)this, sizeof(*this));
			f.close();
		}
		
		void show()
		{
			cout<<s<<" "<<a<<" "<<d<<endl;
		}
};

int main()
{
	
	Test a, obj;
	a.get();
	fstream fil;
	fil.open("hello.dat", ios::binary | ios::in);
	fil.read((char*)&obj, sizeof(obj));
	fil.close();
	
	obj.show();
	
	DelMe();
	return 0;
}
