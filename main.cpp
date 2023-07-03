#include "acc.h"
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<map>
#include<vector>

using namespace std;

class InsufficientFunds
{
    public:
        InsufficientFunds()
        {
            cout<<"  Insufficient funds  ";
        }
};

long Account::getAccNo()
{
    return accountNumber;
}
string Account:: getFirstName()
{
    return firstName;
}
string Account:: getLastName()
{    
    return lastName;    
}
float Account::getBalance()
{
    return balance;
}
void Account::Deposit(float amount)
{
    balance+=amount;
}
void Account:: Withdraw(float amount)
{
     if( balance-amount < 500 ) //considering mininmum balance is 500
    throw InsufficientFunds();
    balance-=amount;
 }
long Account::NextAccountNumber=0;

Account::Account(string fname,string lname,float balance)
{
    NextAccountNumber++;
    accountNumber = NextAccountNumber;
    firstName = fname;
    lastName = lname;
    this->balance = balance;
}

void Account::setLastAccountNumber(long accountNumber)
{
    NextAccountNumber = accountNumber;
}
long Account::getLastAccountNumber()
{
    return NextAccountNumber;
}

class Bank
{
    private:
            map<long,Account> accounts;
    public:
        Bank();
        Account OpenAcc(string fname,string lname,float balance);
        Account BalanceEnquiry(long accountNumber);
        Account Deposit(long accountNumber,float amount);
        Account Withdraw(long accountNumber,float amount);
        void CloseAcc(long accountNumber);
        void ShowAllAccounts();
        ~Bank();
};

Bank::Bank()    //constructor
{
    Account account;
    ifstream infile;
    infile.open("Bank.data");
    //all the accounts data is stored in a file named Bank.data
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    while(!infile.eof())
    {
        infile>>account;
        accounts.insert(pair<long,Account>(account.getAccNo(),account));
    }
    Account::setLastAccountNumber(account.getAccNo());
    
    infile.close();
}

Account Bank::OpenAcc(string fname,string lname,float balance)
{
    ofstream outfile;
    Account acc(fname,lname,balance);
    accounts.insert(pair<long,Account>(acc.getAccNo(),acc));
    
    outfile.open("Bank.data", ios::trunc);
    
    map<long,Account>::iterator itr;
    for(itr=accounts.begin() ; itr!=accounts.end() ; itr++)
    {
        outfile<<itr->second;
    }
    outfile.close();
    return acc;
}
Account Bank::BalanceEnquiry(long accountNumber)
{
    map<long,Account>::iterator itr = accounts.find(accountNumber);
    return itr->second;
}
Account Bank::Deposit(long accountNumber,float amount)
{
    map<long,Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}
Account Bank::Withdraw(long accountNumber,float amount)
{
    map<long,Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}
void Bank::CloseAcc(long accountNumber)
{
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    cout<<"Account Deleted"<<itr->second;
    accounts.erase(accountNumber);
}
void Bank::ShowAllAccounts()
{
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
        cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
    }
}

int main()
{
    Bank b;
    Account acc;
    int choice;
    string fname,lname;
    long acc_no;
    float balance;
    float amount;

    cout<<"\n\t\t*** Banking System ***"<<endl;
    
    do
    {
        cout<<"\n\tSelect one option below "<<endl;
        cout<<"\t1 Open an Account"<<endl;
        cout<<"\t2 Balance Enquiry"<<endl;
        cout<<"\t3 Deposit"<<endl;
        cout<<"\t4 Withdrawal"<<endl;
        cout<<"\t5 Close an Account"<<endl;
        cout<<"\t6 Show All Accounts"<<endl;
        cout<<"\t7 Quit\n"<<endl;

        cout<<"\tEnter your choice: ";
        cin>>choice;

        if(choice==1)
            { 
                cout<<"Enter First Name: ";
                cin>>fname;
                cout<<"Enter Last Name: ";
                cin>>lname;
                cout<<"Enter initil Balance: ";
                cin>>balance;

                acc=b.OpenAcc(fname,lname,balance);
                cout<<endl<<"Congratulations!! Account is Created\n"<<endl;
                cout<<acc;
            }   

             else if (choice==2)
            { 
                cout<<"Enter Account Number:";
                cin>>acc_no;
                acc=b.BalanceEnquiry(acc_no);
                cout<<endl<<"Your Account Details"<<endl;
                cout<<acc;
            }

          else if (choice==3)
            {
                cout<<"Enter Account Number:";
                cin>>acc_no;
                cout<<"Enter Balance(to deposit):";
                cin>>amount;
                acc=b.Deposit(acc_no, amount);
                cout<<endl<<"Amount is Deposited\n"<<endl;
                cout<<acc;
            }         

            else if (choice==4)
            {
                cout<<"Enter Account Number:";
                cin>>acc_no;
                cout<<"Enter Balance(to withdraw):";
                cin>>amount;
                acc=b.Withdraw(acc_no, amount);
                cout<<endl<<"Amount Withdrawn"<<endl;
                cout<<acc;
            }      

          else if (choice==5)
            {
                cout<<"Enter Account Number:";
                cin>>acc_no;
                b.CloseAcc(acc_no);
                cout<<endl<<"Account is Closed"<<endl;
                cout<<acc;
            } 
            else if(choice==6)
            {
                b.ShowAllAccounts();
            }
        else if (choice==7)
                break;      
        else
            cout<<"\nEnter corret choice";
            exit(0);
        
    }
        while(choice!=7);
    return 0;
}

ofstream & operator<<(ofstream &fos,Account &acc)
{
    fos<<acc.accountNumber<<endl;
    fos<<acc.firstName<<endl;
    fos<<acc.lastName<<endl;
    fos<<acc.balance<<endl;
    return fos;
}
ifstream & operator>>(ifstream &fis,Account &acc)
{
    fis>>acc.accountNumber;
    fis>>acc.firstName;
    fis>>acc.lastName;
    fis>>acc.balance;
    return fis;
}
ostream & operator<<(ostream &os,Account &acc)
{
    os<<"\tFirst Name:"<<acc.getFirstName()<<endl;
    os<<"\tLast Name:"<<acc.getLastName()<<endl;
    os<<"\tAccount Number:"<<acc.getAccNo()<<endl;
    os<<"\tBalance:"<<acc.getBalance()<<endl<<endl;
    return os;
}

Bank::~Bank()   //destructor 
{
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);
    
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
        outfile<<itr->second;

    outfile.close();
}
