// Info450SaveMore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> 

using namespace std;

class account
{
public:
	int day;
	const char *accountNum = new char[50];
	double interest = 0;
	double bal = 0;

	void display();
	virtual int deposit(double d);
	virtual int withdraw(double w);
};


void account::display()
{

	cout << endl;

	cout << "Account Number: " << accountNum << endl;
	cout << "Account Interest: " << interest << '%' << endl;
	cout << "Account Balance: " << bal << endl;

}
int account::deposit(double d)
{
	if (d < 0)
	{
		cout << "That is not allowed" << endl;
		return (-1);
	}
	else
	{
		bal += d;
		return (0);
	}
}

int account::withdraw(double w)
{
	if (bal - w < 0)
	{
		cout << "Insufficient Funds" << endl;
		return(-1);
	}
	else
	{
		bal -= w;
		return(0);
	}
}


class savings : public account
{
public:
	savings()
	{
	
	}
	void checkaccount()
	{
		if (bal >= 10000)
		{
			interest = 2;
		}
		else
		{
			interest = 1;
		}
	}
	void compound(int day)
	{
		if (day == 1)
		{
			bal = bal * (interest / 100);
			checkaccount();
		}
	}
	int deposit(double d)
	{
		account::deposit(d);
		checkaccount();
		return (0);
	}
	int withdraw(double w)
	{
		account::withdraw(w);
		checkaccount();
		return (0);
	}
};

class checking : public account
{
public:
	checking()
	{	
		interest = 0;
	}
	void checkaccount()
	{
		if (bal < 500)
		{
			bal = bal - 5;
		}
	}
	void orderChecks()
	{
		bal = bal - 15;
	}
	int deposit(double d)
	{
		account::deposit(d);
		checkaccount();
		return (0);
	}
	int withdraw(double w)
	{
		account::withdraw(w);
		checkaccount();
		return (0);
	}
};


class cd : public account
{
public:
	int t;
	void checkterm(int term)
	{
		if (term >= 5)
			interest = 10;
		else
			interest = 5;
	}
	cd(int term)
	{		
		checkterm(term);
		t = term;

	}
	void compound(int day)
	{
		if (day == 1)
		{
			bal = bal + (bal * (interest / 100));
		}
	}
	void penalty(int i)	
	{
		if (i == 1)
		{
			bal = (bal - (bal *(interest / 100)));
		}
	}
	int deposit(double d)
	{
		account::deposit(d);
		checkterm(t);
		return (0);

	}
	int withdraw(double w, int i)
	{
		if (i == 1)
		{
			bal = (bal - (bal *(interest / 100)));
		}
		account::withdraw(w);
		checkterm(t);
		return (0);
	}
};

int main()
{
	savings save;
	save.accountNum = "Saving";
	save.deposit(10000);
	checking check;
	check.accountNum = "Checking";
	check.deposit(600);
	cd cd(3);
	cd.deposit(10000);
	cd.accountNum = "Certificate of Deposit";
	save.display();
	check.display();
	cd.display();
	save.compound(1);
	cd.compound(1);
	save.display();
	cd.display();
	check.orderChecks();
	check.withdraw(200);
	save.withdraw(1000);
	cd.withdraw(2000, 1);
	save.display();
	check.display();
	cd.display();
}
