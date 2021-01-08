
#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
struct user{
	string name;
	int id;
	string password;
};

struct budget{
	int id;
	float balance;
	int num_transactions;
	struct transaction *t;
};

struct transaction{
	float amount;
	string date;
	string category;
	string description;
};


void useinput(int,int,int,int,bool &,user*,budget*);
bool functiontofile();

int findbudgetposition(int,int,budget*);
void dealwithtransactions(bool,string,transaction*,int);
void swap(transaction* transarray, int i,int k);
void printuserinfo(int amountofusers, int,int userid, user* userarry,budget* budgetarray);
bool correctpassword(int id,int,string, user*);
string getcorrectpassword(int userid, int amountofusers,user*arr);
budget* createbudgets(string,int&);
user* createuserarray(string filename, int &);
void testfiles(string&, string&);
void login(int &userid,int,user*);
void getfiles(int,char**,string&,string&);
budget* create_budgets(int);
void get_budget_data(budget*,int,ifstream &);
transaction* create_transactions(int);
void get_transaction_data(transaction*,int,ifstream &);
void delete_info(user**, budget**, int);
bool testuserid(string str);
int stringtointeger(string str);
int getuserinput(int amountofusers, int,int userid, user* userarray, budget* budgetarray);
bool passwordinput(int userid);

bool userexists(string,int amountofusers, user* arr);

string getfilename();
void categorysort(bool tofile,int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray);
void datesort(bool tofile,int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray);
void dollarsort(bool tofile,int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray);

void delete_info(user*,budget*, int);


#endif
