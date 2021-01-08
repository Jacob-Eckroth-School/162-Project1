/************************
 * Program:implementation.cpp
 * Author: Jacob Eckroth
 * Date: 1/14/2020
 * Description: The implementation file for the budget_buddy app.
 * Input: Inputs taken from driver file, including user filename, transaction filename and sort selection.
 * Output: Transactions sorted in the order chosen by the user, either written to a file or to the screen.
 * **********************/
#include "./implementation.h"
#include<cmath>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;


/**********************
 * Function Name: getfiles
 * Args: int argc, char **argv, string &transactionfile, string &userfile
 * Output: No return, changes data in transactionfile, and userfile.
 * Description: This function error handles the command line, and gets the input for the userfile, and transactionfile if they are not valid already.
 * ********************/
void getfiles(int argc,char **argv,string & transactionfile,string &userfile){
	if(argc == 3){
		userfile =argv[1];
		transactionfile = argv[2];

	}else{
		cout<<"Invalid amount of arguments. Please re-enter."<<endl;
		cout<<"Enter the name of the user file:";
		getline(cin,userfile);	
		cout<<"Enter the name of the transaction file:";
		getline(cin,transactionfile);
	}

	testfiles(userfile,transactionfile);

}

/**********************
 * Function Name: testfiles 
 * Args: string & userfile, string& transactionfile
 * Output: No return, changes data in transactionfile, and userfile.
 * Description: Tests if the files exists, if they do, great, if not, prompt the user until they enter a file that exists.
 * ********************/
void testfiles(string &userfile,string &transactionfile){
	bool userfilestatus = false;
	bool transactionfilestatus = false;
	fstream Filestream; 

	do{		
		Filestream.open(userfile); //testing if we can open the budgetfile from the current directory
		if(Filestream.is_open()){
			userfilestatus = true;
		}else{
			cout<<"Invalid user file name. Please re-enter a valid user file:";
			getline(cin, userfile);
		}
	}while(!userfilestatus);
	Filestream.close();//This might not need to be here but everything breaks if it isn't
	do{
		Filestream.open(transactionfile); //tetsing if we can open the transactionfile from the current directory
		if(Filestream.is_open()){
			transactionfilestatus = true;
		}else{
			cout<<"Invalid transaction file name. Please re-enter a valid transaction file:";
			getline(cin,transactionfile);
		}
	}while(!transactionfilestatus);
	Filestream.close();

}

/**********************
 * Function Name: createuserarray 
 * Args: string filename, int &amountofusers
 * Output: Array filled with user objects and info from the filename. Also updates amountofusers to contain amount of users
 * Description: Creates an array filled with info collected from the filename that contains the userfile. Also updates amountofusers to contain the actual amount of users.
 * * ********************/

user* createuserarray(string filename,int &amountofusers){

	fstream Filestream;
	Filestream.open(filename);
	string tempstr = "";
	getline(Filestream,tempstr,'\n');//The first number in the file will be the amount of users, so we get it here	
	amountofusers = stoi(tempstr);
	user* userarray = new user[amountofusers];
	for(int i = 0; i < amountofusers; i++){//because we know the format of the user file, we can get all the information here sequentially for each user
		getline(Filestream,tempstr,' ');
		userarray[i].name = tempstr;
		getline(Filestream,tempstr,' ');	
		userarray[i].id = stoi(tempstr);
		getline(Filestream,tempstr,'\n');
		userarray[i].password = tempstr;
	}

	Filestream.close();
	return userarray;

}


/**********************
 * Function Name: Login 
 * Args: int &userid, int amountofusers, user* arr
 * Output: no return. Updates userid to contain the correct userid after logging in.
 * Description: Gets user input into the userid, and tests to make sure that that user exists.
 * * ********************/
void login(int &userid,int amountofusers, user*arr){
	bool validinput = true;
	bool idexists = true;
	cout<<"Login Page"<<endl;
	string userinput = "";
	do{
		if(!validinput){
			cout<<"Invalid input, user id must be a series of integers."<<endl;
		}else if(!idexists){
			cout<<"Invalid input, user id does not exist."<<endl;
		}
		cout<<"Enter your user id:";
		getline(cin,userinput);
		validinput = testuserid(userinput);
		if(validinput){
			idexists = userexists(userinput,amountofusers,arr);
		}

	}while(!validinput || !idexists);
	userid = stoi(userinput);



}


/**********************
 * Function Name: userexists 
 * Args: string userinput, int amountofusers, user* arr
 * Output: Returns true if the userinput exists somewhere in the list of IDs in the user array, returns false if it doesn't.
 * Description: tests whether string userinput exists in the id of one of the users in the array arr.
 * * ********************/
bool userexists(string userinput,int amountofusers, user* arr){
	for(int i = 0; i < amountofusers; i++){
		if(arr[i].id == stoi(userinput)){
			return true;
		}
	}
	return false;


}
/**********************
 * Function Name: testuserid 
 * Args: string str
 * Output: returns true if the string is entirely integers, returns false if it isn't.
 * Description: tests whether the userinput into the string for their id is entirely integers or not.
 * * ********************/
bool testuserid(string str){
	if(str == ""){
		return false;
	}

	for(int i = 0; i < str.length(); i++){
		if(!(str[i] >= '0' && str[i] <= '9')){//if it's an integer via ASCII value
			return false; //it's not valid
		}
	}
	return true;	

}



/**********************
 * Function Name: createbudgets 
 * Args: string budgetfile, int &amountofbudgets
 * Output:Returns an array of budgets filled with information, and updates amountofbudgets to contain the right amount of budgets.
 * Description: Opens the file, budgetfile, and creates a array of budgets based on the file, and the amount of budgets listed in teh budget file.
 * * ********************/
budget* createbudgets(string budgetfile, int &amountofbudgets){
	ifstream Fstream;
	string tempstring = "";
	Fstream.open(budgetfile);
	getline(Fstream,tempstring,'\n');//first number in budgetfile will always be amount of budgets
	amountofbudgets = stoi(tempstring);

	budget* budgetarray = create_budgets(amountofbudgets);
	get_budget_data(budgetarray,amountofbudgets,Fstream);
	Fstream.close();
	return budgetarray;
}

/**********************
 * Function Name: create_budgets 
 * Args: int amount
 * Output: returns an array of budgets with amount, amount
 * Description: Creates an empty array of budgets with amount, amount, and returns the budget array.
 ********************/
budget* create_budgets(int amount){
	budget* arr = new budget[amount];
	return arr;

}
/**********************
 * Function Name: get_budget_data 
 * Args: budget* arr, int amount, ifstream &budgetfile
 * Output: No return. Updates the budget array to contain all the information from the budget file.
 * Description: fills the budget* array with info taken from the ifstream object budgetfile, assuming that it is formatted correctly in the file.
 ********************/
void get_budget_data(budget* arr,int amount, ifstream &budgetfile){
	string tempstr = "";
	for(int i = 0; i < amount; i++){
		getline(budgetfile,tempstr,' ');
		arr[i].id = stoi(tempstr);
		getline(budgetfile,tempstr,' ');
		arr[i].balance = stof(tempstr);
		getline(budgetfile,tempstr,'\n');
		arr[i].num_transactions = stoi(tempstr);
		arr[i].t = create_transactions(arr[i].num_transactions); //fills the transaction array in the budget array. Arrayception
		get_transaction_data(arr[i].t,arr[i].num_transactions,budgetfile);//fills the transaction array in the budget array with the info from the file.
	}	
}


/**********************
 * Function Name: create_transactions 
 * Args: int amount
 * Output: returns an array of transactions of amount, amount
 * Description: creates an array of empty transactions and returns it.
 ********************/
transaction* create_transactions(int amount){
	transaction *arr = new transaction[amount];
	return arr;

}

/**********************
 * Function Name: get_transaction_data 
 * Args: transaction* arr, int amount, ifstream &file
 * Output: No return. Updates the transaction array to contain all the transaction info from the ifstream file.
 * Description: Fills an array of transactions with info taken from the ifstream file, assuming that it is formatted correctly
 ********************/
void get_transaction_data(transaction* arr,int amount, ifstream &file){
	string tempstr = "";
	for(int i = 0; i < amount; i++){
		getline(file,tempstr,' ');

		arr[i].date = tempstr;
		getline(file,tempstr,' ');
		arr[i].amount = stof(tempstr);
		getline(file,tempstr,' ');
		arr[i].description = tempstr;
		getline(file,tempstr,'\n');
		arr[i].category = tempstr;

	}
}

/**********************
 * Function Name: printuserinfo 
 * Args: int amountofusers, int amountofbudgets, int userid, user* userarray, budget* budgetarray
 * Output: Prints the user name, id, and account balance
 * Description: Prints the username, ID, and account balance, based on info in the user array, and budgetarray
 ********************/
void printuserinfo(int amountofusers,int amountofbudgets, int userid, user* userarray,budget* budgetarray){	
	int usernumber;
	int budgetnumber;
	for(int i = 0; i < amountofusers; i++){
		if(userarray[i].id == userid){
			usernumber = i;
		}
	}

	for(int i = 0; i < amountofbudgets; i++){

		if(budgetarray[i].id == userid){
			budgetnumber = i;
		}
	}

	cout<<"\nName:"<<userarray[usernumber].name<<endl;
	cout<<"ID:"<<userarray[usernumber].id<<endl;
	cout<<"Account Balance:$"<<budgetarray[budgetnumber].balance<<endl;


}

/**********************
 * Function Name: getuserinput 
 * Args: int amountofusers, int amountofbudgets, int userid, user* userarray, budget*b budgetarray
 * Output: returns an int based on what option the user chooses.
 * Description: gets the input for what option between int 1-4 the user wants to choose.
 ********************/
int getuserinput(int amountofusers,int amountofbudgets, int userid, user* userarray, budget* budgetarray){
	printuserinfo(amountofusers,amountofbudgets,userid,userarray,budgetarray);//Prints the user id, name, balance above the options.
	string userinput = "";
	bool validinput = true;
	cout<<"Sort transactions by category(1)"<<endl;
	cout<<"Sort transactions by date(2)"<<endl;
	cout<<"Sort transactions by dollar amount(3)"<<endl;
	cout<<"Quit(4)"<<endl;
	cout<<"Choose your option:";
	do{
		if(!validinput){
			cout<<"Invalid input. Please enter a number between 1 and 4:";
		}
		getline(cin,userinput);
		if(userinput[0] >= '0' && userinput[0] <= '4'){
			validinput = true;
		}else{
			validinput = false;
		}
	}while(!validinput);
	return(userinput[0]-'0');//because apparently I don't know about the stoi function
}

/**********************
 * Function Name: useinput 
 * Args: int userinput, int userid, int amountofusers, int amountofbudgets, int userid, user* userarray, budget*b budgetarray
 * Output: no return. Deals with the option chosen by the user, and prints info to screen.
 * Description: Using an int input, chooses what sort the user wants to do, and does that sort. Updates running to be false, if the user wants to quit.
 ********************/

void useinput(int userinput, int userid, int amountofusers, int amountofbudgets, bool &running, user* userarray, budget* budgetarray){
	bool tofile = false;
	switch(userinput){
		case(1): //sort by category	
			tofile = functiontofile(); //do you want to input to a file or to the screen?
			categorysort(tofile,userid, amountofusers, amountofbudgets, userarray, budgetarray);
			break;
		case(2): //sort by date
			tofile = functiontofile(); 
			datesort(tofile,userid, amountofusers, amountofbudgets, userarray, budgetarray);
			break;
		case(3): //sort by dollar amount
			tofile = functiontofile();
			dollarsort(tofile,userid, amountofusers, amountofbudgets, userarray, budgetarray);
			break;
		case(4)://quit
			running = false;
			break;
		default://this shouldn't exist
			cout<<"Shit this should never happen"<<endl;
			break;
	}

}

/**********************
 * Function Name: categorysort 
 * Args: bool tofile, int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray
 * Output: Prints, or writes to a file the transactions in the budgetarray sorted by category.
 * Description: Sorts the transactions in a file by category, in order from top to bottom: Housing, Food, Entertainment, Personal_Care, Miscellaneous.
 ********************/
void categorysort(bool tofile, int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray){
	int userbudget = findbudgetposition(amountofusers,userid,budgetarray);
	int amountoftransactionsinarray = 0;
	string filename = "";
	transaction temp;
	bool sorted = false;
	if(tofile){
		filename = getfilename();
	}
	transaction* transarray = new transaction[budgetarray[userbudget].num_transactions];//new array where we put the items in the right order
	for(int i = 0; i < budgetarray[userbudget].num_transactions;i++){
		transarray[i] = budgetarray[userbudget].t[i];
	}
	while(!sorted){
		for(int i = 0; i < budgetarray[userbudget].num_transactions; i++){
			if(i != 0){
				//whoo boy ok, so this is testing every item in the array, to see if the item before it falls before it in the order that categories should be started in the list: Housing, Food, Entertainment, Personal_Care, Miscellaneous. It's a selection sort
				if(/*test1*/(transarray[i].category == "Housing" && transarray[i-1].category != "Housing")||/*test2*/ (transarray[i].category == "Food" && (transarray[i-1].category != "Housing" && transarray[i-1].category != "Food" )) ||/*test3*/ (transarray[i].category == "Entertainment" && (transarray[i-1].category == "Personal_Care" || transarray[i-1].category == "Miscellaneous")) ||/*test4*/ (transarray[i].category == "Personal_Care" && (transarray[i-1].category == "Miscellaneous"))){ //This is fucking disgusting
					swap(transarray,i,i-1);							
					break;//run through the array again
				}
			}
			if(i==budgetarray[userbudget].num_transactions - 1){//If we got through the for loop with everything in the right order
				sorted = true;
			}
		}
	}
	dealwithtransactions(tofile,filename,transarray,budgetarray[userbudget].num_transactions);//print or write to file transactions
	delete[] transarray;


}

/**********************
 * Function Name: datesort 
 * Args: bool tofile, int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray
 * Output: sorts an array of transactions based on date and prints the info to screen or writes to a file.
 * Description:Sorts a transaction by date using an insertion sort, and either prints to screen, or writes to file the sorted transactions.
 ********************/
void datesort(bool tofile, int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray){
	string filename = "";
	transaction temp;
	bool sorted = false;
	int userbudget = findbudgetposition(amountofusers,userid,budgetarray);
	if(tofile){
		filename = getfilename();
	}
	transaction* transarray = new transaction[budgetarray[userbudget].num_transactions];
	for(int i = 0; i < budgetarray[userbudget].num_transactions;i++){
		transarray[i] = budgetarray[userbudget].t[i];//fills the temporary array
	}

	while(!sorted){
		for(int i = 0; i < budgetarray[userbudget].num_transactions;i++){
			if(i!=0){
				//Brace yourself for this next line, because holy shit
				//It compares two spots in an array, and tests if the date of the 2nd spot in the array is earlier than the date in the second spot in the array
				//If it is, then switch places, if not, keep looping
				if(/*different year*/(stoi(transarray[i].date.substr(6,4)) > stoi(transarray[i-1].date.substr(6,4)))||/*same year different month*/((stoi(transarray[i].date.substr(6,4)) == stoi(transarray[i-1].date.substr(6,4))) && (stoi(transarray[i].date.substr(0,2)) > stoi(transarray[i-1].date.substr(0,2)))) ||/*same year, same month, different day*/ ((stoi(transarray[i].date.substr(6,4)) == stoi(transarray[i-1].date.substr(6,4))) && (stoi(transarray[i].date.substr(0,2)) == stoi(transarray[i-1].date.substr(0,2))) && (stoi(transarray[i].date.substr(3,2)) > stoi(transarray[i-1].date.substr(3,2))))){
					swap(transarray,i,i-1);
					break;//run through all the spots in the array again
				}
			}
			if(i==budgetarray[userbudget].num_transactions-1){//if we got through loop without breaking out
				sorted = true;
			}

		}
	}
	dealwithtransactions(tofile,filename,transarray,budgetarray[userbudget].num_transactions);//print out stuff
	delete[] transarray;
}

/**********************
 * Function Name: dollarsort 
 * Args: bool tofile, int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray
 * Output: sorts an array of transactions based on dollar amount and prints the info to screen or writes to a file.
 * Description:Sorts a transaction by dollar amount using an insertion sort, and either prints to screen, or writes to file the sorted transactions.
 ********************/
void dollarsort(bool tofile, int userid, int amountofusers, int amountofbudgets, user* userarray, budget* budgetarray){
	string filename = "";
	transaction temp;
	bool sorted = false;
	int userbudget = findbudgetposition(amountofusers,userid,budgetarray);
	if(tofile){
		filename = getfilename();
	}
	transaction* transarray = new transaction[budgetarray[userbudget].num_transactions];
	for(int i = 0; i < budgetarray[userbudget].num_transactions;i++){
		transarray[i] = budgetarray[userbudget].t[i];//fillls temporary array
	}
	while(!sorted){
		for(int i = 0; i < budgetarray[userbudget].num_transactions;i++){
			if(i!=0){
				if(transarray[i].amount > transarray[i-1].amount){ //If the amount of the current position is greater than the amount of the position above it.
					swap(transarray,i,i-1);
					break;
				}
			}
			if(i==budgetarray[userbudget].num_transactions-1){//if entire transaction array is in order.
				sorted = true;
			}

		}
	}

	dealwithtransactions(tofile,filename,transarray,budgetarray[userbudget].num_transactions);
	delete[] transarray;
}

/**********************
 * Function Name: swap
 * Args: transaction* transarray, int position1, int position2
 * Output: swaps the position of 2 transactions within an array
 * Description:swaps the position of 2 transactions within an array.
 ********************/
void swap(transaction* transarray, int position1,int position2){
	transaction temp = transarray[position1];
	transarray[position1] = transarray[position2];
	transarray[position2] = temp;
}

/**********************
 * Function Name: dealwithtransactions 
 * Args: bool tofile, string filename, transaction* transarray, int transactioncount
 * Output: Prints, or writes to screen info from the transarray
 * Description:Depending on whether the user wanted the transactions written to a file or not, the transactions are either written to a file which is created, or the information is printed to the screen.
 ********************/
void dealwithtransactions(bool tofile, string filename, transaction* transarray, int transactioncount){
	ofstream fout;
	if(!tofile){//If writing to console
		for(int i = 0; i < transactioncount; i++){
			cout<< transarray[i].date<<" $"<<transarray[i].amount<<" "<<transarray[i].description<<" "<<transarray[i].category<<endl;
		}
	}else{//write to file
		fout.open(filename,ios::out|ios::trunc);//open a file and delete everything that's in it.
		for(int i =0; i < transactioncount; i++){ 
			fout<<transarray[i].date<<" $"<<transarray[i].amount<<" "<<transarray[i].description<<" "<<transarray[i].category<<endl; //put each transaction on a new line
		}
		cout<<"Written to the file:"<<filename<<endl;	
	}
}

/**********************
 * Function Name: findbudgetposition 
 * Args: int amountofusers, int userid, budget* budgetarray
 * Output: an int that represents the array position of the user id in the budget array
 * Description: parses through a budgetarray to find the position that holds the user id, and returns that int.
 ********************/
int findbudgetposition(int amountofusers, int userid, budget* budgetarray){
	for(int i =0; i < amountofusers; i++){
		if(budgetarray[i].id == userid){
			return i;
		}
	}
}

/**********************
 * Function Name: getfilename 
 * Args: None
 * Output: Returns a string
 * Description:Get's user input for a filename into a string, and returns it.
 ********************/
string getfilename(){
	string str;
	cout<<"Please enter the file name you want the transactions written to:";
	getline(cin,str);
	return str;

}

/**********************
 * Function Name: functiontofile  
 * Args: None
 * Output: Returns true if the user wants the transactions written to a file, false otherwise
 * Description:Error handles, and tests if the user wants the information written to a file, or printed to the screen. Returns true if they want to write it to a file, false if they do not.
 ********************/
bool functiontofile(){
	bool validinput = true;
	string userinput = "";
	cout<<"Do you the information printed to the screen(0), or written to a file(1)?:";
	do{
		if(!validinput){
			cout<<"Invalid input, please enter either 0 or 1:";
		}
		getline(cin,userinput);
		if(userinput !="0" && userinput != "1"){
			validinput = false;
		}else{
			validinput = true;
		}
	}while(!validinput);
	return stoi(userinput); 
}

/**********************
 * Function Name: correctpassword  
 * Args: int userid, int amountofusers, string userfile, user* arr
 * Output: returns true if the correct password was entered in 3 attemps or less, false if it was not.
 * Description:Uses the user id to find the corerct corellating password. Then allows the user to enter a string up to 3 times. If they don't get the password in 3 tries, return false, else return true.
 ********************/
bool correctpassword(int userid,int amountofusers,string userfile,user* arr){
	string correctpassword = getcorrectpassword(userid,amountofusers,arr);
	bool correct = true;
	string userinput = "";
	cout<<"Password:";
	for(int i = 0; i < 3; i++){
		if(!correct){
			cout<<"Invalid password. You have "<<3-i<<" tries remaining"<<endl;
			cout<<"Password:";
		}


		getline(cin,userinput);
		if(userinput == correctpassword){
			correct = true;
			break;
		}else{
			correct = false;
		}
	}
	if(correct){
		return true;
	}
	return false;
}

/**********************
 * Function Name: getcorrectpassword  
 * Args: int userid, int amountofusers, string userfile, user* arr
 * Output: returns the password that correlates with the userid from the userfile.
 * Description:searches through the user array to find the id. Then takes the password attached to that user and returns it.
 ********************/
string getcorrectpassword(int userid, int amountofusers,user*arr){
	for(int i = 0; i < amountofusers; i++){

		if(userid == arr[i].id){
			return arr[i].password;
		}
	}	
}

/**********************
 * Function Name: delete_info  
 * Args: user*userarray, budget*budgetarray, int amountofbudgets
 * Output: deletes the space on the heap that is taken up by budgetarray, transactions within budgetarray, and userarray
 * Description:Deletes space taken by userarray, budgetarray, and the transactions inside each budget in the budgetarray
 ********************/
void delete_info(user*userarray,budget*budgetarray,int amountofbudgets){
	delete[] userarray;
	for(int i = 0; i < amountofbudgets; i++){
		delete[] budgetarray[i].t;
	}
	delete[] budgetarray;
}
