#include <iostream>
#include <string>
using namespace std;

class Investment
{
public:
	Investment(string name, int value) : mname(name), mvalue(value) {}
	string name() const {
		return mname;
	}
	int purchasePrice() const {
		return mvalue;
	}
	virtual bool fungible() const {
		return false;
	}
	virtual string description() const = 0;
	virtual ~Investment() {}
private:
	string mname;
	int mvalue;
};

class Painting : public Investment
{
public:
	Painting(string name, int value) : Investment(name, value) {}
	virtual string description() const {
		return("painting");
	}
	virtual ~Painting() {
		cout << "Destroying " << name() << ", a painting" << endl;
	}
};

class Stock : public Investment
{
public:
	Stock(string name, int value, string company) : Investment(name, value), mcompany(company) {}
	virtual string description() const { 
		return("stock trading as " + mcompany);
	}
	virtual bool fungible() const {
		return true;
	}
	virtual ~Stock() {
		cout << "Destroying " << name() << ", a stock holding" << endl;
	}
private:
	string mcompany;
};

class House : public Investment
{
public:
	House(string name, int value) : Investment(name, value) {}
	virtual string description() const {
		return("house");
	}
	virtual ~House() {
		cout << "Destroying the house " << name() << endl;
	}
};

void display(const Investment* inv)
{
	cout << inv->name();
	if (inv->fungible())
		cout << " (fungible)";
	cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int main()
{
	Investment* portfolio[4];
	portfolio[0] = new Painting("Salvator Mundi", 450300000);
	// Stock holdings have a name, value, and ticker symbol
	portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
	portfolio[2] = new Stock("Symantec", 50000, "SYMC");
	portfolio[3] = new House("4 Privet Drive", 660000);

	for (int k = 0; k < 4; k++)
		display(portfolio[k]);

	// Clean up the investments before exiting
	cout << "Cleaning up" << endl;
	for (int k = 0; k < 4; k++)
		delete portfolio[k];
}