#include <string>
#include <iostream>
using namespace std;
class Account
{
    private:
        long accountNumber;
        string firstName;
        string lastName;
        float balance;
        static long NextAccountNumber;
    public:
        //constructors
        Account(){}
        Account(string fname,string lname,float balance);

        //accessors
        long getAccNo();
        string getFirstName();
        string getLastName();
        float getBalance();
        static void setLastAccountNumber(long accountNumber);
        static long getLastAccountNumber();

        void Deposit(float amount);
        void Withdraw(float amount);
        
        friend ofstream & operator<<(ofstream &fos,Account &acc);
        friend ifstream & operator>>(ifstream &fis,Account &acc);
        friend ostream & operator<<(ostream &os,Account &acc);
};