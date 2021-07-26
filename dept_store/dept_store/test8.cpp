#include<iostream>
#include<iomanip>
#include<ctime>
#include "E:/delme.cpp"
using namespace std;

// make setStoreName() to let user enter their store name [max length 20 char]	{experimental}

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

void bill(string name)
{
	string date = getDate();
	string time = getTime();
	
	char prodName[30] = "Dettol_Handwash";
	int prodNumber = 10213;
	float Price = 200;
	int Quantity = 2;
	float net = Price * Quantity; 
	
	int total = 2000;
	
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
	
	cout<<"\n"<<prodName<<setw(36 - strlen(prodName))<<prodNumber<<setw(14)<<Price<<setw(12)<<Quantity<<setw(12)<<net;
	
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

int main()
{
	/*string storeName;
	cout<<"Enter your store name: ";
	getline(cin, storeName);
	
	cout<<storeName<<endl;*/
	
	bill("Departmental Store Management System");
	
	DelMe();
	return 0;
}
