/***************************
 * Program:driver.cpp
 * Author:Jacob Eckroth
 * Date:1/14/2020
 * Description:This program takes in two files with users and budgets, allows a user to log in, see their budget, and sort their transactions in multiple ways. Either the transaction gets written to a file, or printed to the screen edepending on what the user chooses.
 * Input:In the command line, 2 file names. The user also needs to login and choose how they want to sort their transaction and whether they want it to be in a file or not.
 * Output:The transactions sorted, either in a file, or printed to the screen. Also, tells the user if they failed to login.
 * ***********************/
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
#include "./implementation.h" //header file with prototypes and user,budget, and transaction struct


int main(int argc, char**argv){ //argument 1 and 2 should be name of user file, and name of budget file.
	string transactionfile; 
	string userfile; 
	bool running = true;
	int userinput = 0;
	int userid = 0;
	int amountofusers = 0;
	int amountofbudgets = 0;	
	getfiles(argc, argv, transactionfile,userfile);	
	user* userarray = createuserarray(userfile,amountofusers);
	budget* budgetarray = createbudgets(transactionfile, amountofbudgets);
	login(userid,amountofusers,userarray);
	if(!correctpassword(userid,amountofusers,userfile,userarray)){ //if the password is tried 3 times and failed.
		delete_info( userarray, budgetarray,amountofbudgets);
		cout<<"You have failed. Bye!"<<endl;
		return 0;
	}

	do{

		userinput = getuserinput(amountofusers,amountofbudgets,userid, userarray,budgetarray);
		useinput(userinput, userid, amountofusers, amountofbudgets, running, userarray, budgetarray);	



	}while(running);
	cout<<"Bye!"<<endl;
	delete_info( userarray, budgetarray,amountofbudgets);

	return 0;
}
