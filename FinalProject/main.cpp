#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

/* Concept:
 * 	Create NoSQL DBMS that processes query using as little memory as possible
 *
 * Attributions:
	Dr. Lusth provided an options.c file, which I modified into this main.cpp file

	Applied a modified trim function similiar to python's trim function

	-Blair Kiel
*/

template <std::ctype_base::mask mask>
class IsNot
{
	std::locale myLocale;       // To ensure lifetime of facet...
        std::ctype<char> const* myCType;
public:
	IsNot( std::locale const& l = std::locale() )
		: myLocale( l )
		, myCType( &std::use_facet<std::ctype<char> >( l ) )
		{
		}
	bool operator()( char ch ) const{
		return ! myCType->is( mask, ch );
	}
};

typedef IsNot<std::ctype_base::space> IsNotSpace;


/* options */
int optionV = 0;
int optionD = 0;

string trim( string const& original );
bool onlyDigits(string s);
vector<string> evalBoolean(string *data, string conditionName1, string conditionValue1, string conditionOperator1, string conditionName2, string conditionValue2, string conditionOperator2, string boolean);
int retreiveAvgValue(string line, string field);
void printSelectedFields(string line,string *fieldsArr);
bool conditionMatches(string line, string conditionName, string conditionOperator, string conditionValue);
int arrayLen(string *arr);
void processQuery(string file, string operation, string *conditionNamesArr, string *conditionOperatorsArr, string *conditionValuesArr, string *conditionBooleanArr, string *fieldsArr, queue<string> conditionQueue);
int ProcessOptions(int, char const **);
void Fatal(char const *, ...);

int main(int argc, char const **argv)
{
	/* argument handler*/
	int argIndex;

	//if (argc == 1) Fatal("%d arguments!\n", argc - 1);

	argIndex = ProcessOptions(argc, argv);

	cout << "argv[1] is: " << argv[1]<<'\n';

	/*
	if (argIndex == argc){
		printf("No arguments\n");
	else
	{
		
		printf("Remaining arguments:%d\n", argc);
		int i;
		for (i = argIndex; i < argc; ++i){
			printf("argc is %d\n",argc);
			printf("argIndex is %d\n",argIndex);
			printf("i is %d\n",i);
			printf("argv[i] is %s\n",argv[i]);
			printf("    %s\n", argv[i-1]);
			printf("made it here");
		}
		
		
	}
	*/

	/* Main Program */

	int continueQueries = 1;	
	int i = 0;
	string queryIn;
	string dbChoice;
	string collectionChoice;
	string operationChoice; 
	string conditionsChoice;
	string fieldsChoice;
	while(continueQueries){

		dbChoice = "";
		collectionChoice = "";
		operationChoice = "";
		conditionsChoice = "";
		fieldsChoice = "";

		/*Parse Query*/
		cout << "Please Enter a Query:\n";
		getline(cin, queryIn);

		//parse dbChoice
		i = 0;
		while(queryIn[i] != '.' & queryIn.length() != i){
			char ch = queryIn[i]; 
			dbChoice += ch;
			i++;
		}
		i++;

		//parse collectionChoice
		while(queryIn[i] != '.' & queryIn.length() != i){
			char ch = queryIn[i]; 
			collectionChoice += ch;
			i++;
		}
		i++;

		//parse operationChoice
		while(queryIn[i] != '(' & queryIn.length() != i){
			char ch = queryIn[i]; 
			operationChoice += ch;
			i++;
		}
		i++;

		cout << "dbChoice: "<< dbChoice << " | collectionChoice: " << collectionChoice << " | operationChoice: " << operationChoice << "\nQuery: "<< queryIn << "\n";

		/*Evaluate Operation's Arguments' Conditions and Fields*/
		

		string conditionNamesArr[100];
		string conditionValuesArr[100];
		string conditionOperatorsArr[100];
		string conditionBooleanArr[100];
		string fieldsArr[100];
		queue<string> conditionQueue;
		int j = 0;
		int k = 0;
		int l = 0;
		int m = 0;
		int n = 0;
		string str;
		string queueStr;

		if (operationChoice == "find"){

			//parse conditionChoices
			i++;
			while(queryIn[i] != ',' & queryIn.length() != i){

				char ch = queryIn[i]; 

				//condition name and Operators
				if(queryIn[i] == '='){
	       				conditionNamesArr[j]= str;
					conditionOperatorsArr[n] = '=';
					n++;
					j++;
					str = "";
					queueStr += ch;
				}

				else if(queryIn[i] == '<'){
					conditionNamesArr[j]=str;
					j++;
					str = "";
					queueStr += ch;
					if(queryIn[i+1] == '>'){
						conditionOperatorsArr[n] = "<>";
						i++;
						n++;
					}
					else{
						conditionOperatorsArr[n] = '<';
						n++;
					}
				}
				else if (queryIn[i] == '>'){
					conditionNamesArr[j] = str;
					conditionOperatorsArr[n] = '>';
					n++;
					j++;	
					queueStr += ch;
					str = "";
				}

				//check if boolean
				else if(str == "and" or str == "or"){
					conditionBooleanArr[k] = str;
					//cout << "queryIn[i+1] is: " << queryIn[i+1] << "\n";
					/*
					if (queryIn[i+1] == '('){
						conditionQueue.push(str);
					}
					*/
					str = "";
					k++;
				}

				//condition value
				else if(queryIn[i] == ' ' and queryIn[i+1] == '('){
					cout << "Ch is : " << ch << "\n";
					queueStr += ch;	
				}

				else if(queryIn[i] == ' ' and queryIn[i+1] != 'a' and queryIn[i+1] != 'o'){
					cout << "Ch is : " << ch << "\n";
					cout << "Made it here: '" << str << "'\n";
					queueStr += ch;
					conditionValuesArr[l] = str;
					l++;
					str = "";
				}

				else if(queryIn[i] == ' '){
					queueStr += ch;
				}

				

				else if(queryIn[i] == ' ' and queryIn[i-1] != ')'){
					conditionValuesArr[l] = str;
					queueStr += ch;
					l++;
					str = "";
				}


				//else if (queryIn[i] == ' ' and (queryIn[i+1] == 'a' or queryIn[i+1] == 'o')){
				else if (queryIn[i] == ' ' and queryIn[i-1] == ')'){
					str = "";
				}

				else if(queryIn[i] == '('){
					queueStr = "";
					queueStr += ch;
				}

				//condition value end 
				else if (queryIn[i] == ')' and queryIn[i+1] != ','){
					queueStr += ch;
					conditionValuesArr[l] = str;
					l++;
					conditionQueue.push(queueStr);
					queueStr = "";
					str = "";	
				}
				else if (queryIn[i] == ')' and queryIn[i+1] == ','){
					//queueStr += ch;
					conditionValuesArr[l] = str;
					l++;
					conditionQueue.push(queueStr);
					queueStr = "";
					str = "";	

				}

				else{
					str += ch;
					queueStr += ch;
				}
				i++;

			}
			//conditionValuesArr[l] = str;
			l++;
			i++;
			str = "";

			//Parse Fields
			i++;
			i++;
			while(queryIn[i] != ']' & queryIn.length() != i){

				char ch = queryIn[i]; 

				//condition name
				if(queryIn[i] == ','){
	       				fieldsArr[m] = str;
					m++;
					i++;
					str = "";
				}
				else{
					str += ch;
				}
				i++;
			}
			if (str != ""){
				fieldsArr[m] = str;
				m++;
				i++;
			}
		}
		else if (operationChoice == "avg"){

			
			while(queryIn.length() != i){

				char ch = queryIn[i]; 

				//field name
				if(queryIn[i] == ')'){
	       				fieldsArr[j] = str;
					j++;
					str = "";
					break;
				}
				else{
					str += ch;
				}
				i++;

			}
			l++;
			i++;

		}
		else{
			cout << "Error: Please enter a valid query ('find' or 'avg');";
		}

		//Print conditionNames
		cout << "Condition Names:\n";
		j = 0;
		while(conditionNamesArr[j] != ""){
			cout << conditionNamesArr[j] << ' ';
			j++;
		}
	  	cout << '\n';	

		//Print conditionValues
		cout << "Condition Values:\n";
		j = 0;
		while(conditionValuesArr[j] != ""){
			cout << conditionValuesArr[j] << " | ";
			j++;
		}
	  	cout << '\n';	
		

		//Print conditionValues
		cout << "Condition Values:\n";
		j = 0;
		while(conditionOperatorsArr[j] != ""){
			cout << conditionOperatorsArr[j] << ' ';
			j++;
		}
	  	cout << '\n';	

		//Print conditionBooleans
		cout << "Condition Booleans:\n";
		j = 0;
		while(conditionBooleanArr[j] != ""){
			cout << conditionBooleanArr[j] << ' ';
			j++;
		}
	  	cout << '\n';	


		//Print fields 
		cout << "Fields:\n";
		j = 0;
		while(fieldsArr[j] != ""){
			cout << fieldsArr[j] << ' ';
			j++;
		}
		//cout << "fieldsArr is: len() = " << j;


		//Print conditionQueue
		cout << "ConditionQueue:\n";
		queue<string> tempQueue;
		while(!conditionQueue.empty()){
			cout << conditionQueue.front() << '|';
			tempQueue.push(conditionQueue.front());
			conditionQueue.pop();
		}

		while(!tempQueue.empty()){
			conditionQueue.push(tempQueue.front());
			tempQueue.pop();
		}
	  	cout << '\n' << '\n';	


		processQuery(argv[1],operationChoice, conditionNamesArr, conditionOperatorsArr, conditionValuesArr, conditionBooleanArr, fieldsArr, conditionQueue);


	}
	return 0;
}



void processQuery(string file,string operation, string *conditionNamesArr, string *conditionOperatorsArr, string *conditionValuesArr, string *conditionBooleanArr,string *fieldsArr, queue<string> conditionQueue){

	/*Read in values*/
	string line;
	ifstream dataFile (file);
	string data[500];
	string matchesArr[500];
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	int count = 1;
	if (dataFile.is_open()){

		long id = 0;
		//process operation
		if(operation == "find"){

			string helperArr[500];
			string tempArr[500];

			line = trim(line);
			//process booleans
			if(arrayLen(conditionBooleanArr) > 0){
				while ( getline (dataFile,line) ){
					data[k] = line;
					k++;
					//process condition
					//cout << "Line is: '" << line << "'\n";
					//cout << "conditionName is: '" << conditionNamesArr[0] << "'\n";
					//cout << "conditionValue is: '" << conditionValuesArr[0] << "'\n";
					//cout << "\n";

				}

				//while booleans are still
				//
				string nConQueue = "";
				cout << "conditionQueue.size(): " << conditionQueue.size() << "\n";
				while(conditionQueue.size() != 0){
				
					nConQueue = conditionQueue.front();
					vector<string> tempVect = evalBoolean(data, conditionNamesArr[m], conditionValuesArr[m], conditionOperatorsArr[m], conditionNamesArr[m+1], conditionValuesArr[m+1], conditionOperatorsArr[m+1], nConQueue);
					while(tempVect.size() != 0){
						helperArr[l] = tempVect.back();
						tempVect.pop_back();
						l++;
					}
					conditionQueue.pop();
					m++;
					m++;
				}

			}
			else{
				while ( getline (dataFile,line) ){
					//cout << "Made it here";	
					line = trim(line);
					//process condition
					//ID is 0 needs to be 1
					//cout << "Line is: '" << line << "'\n";
					//cout << "conditionName is: '" << conditionNamesArr[0] << "'\n";
					//cout << "conditionValue is: '" << conditionValuesArr[0] << "'\n";
					//cout << "\n";
					if(conditionMatches(line, conditionNamesArr[0], conditionOperatorsArr[0], conditionValuesArr[0])){
						matchesArr[i] = "ID: " + to_string(count) + " " + line;
						//cout << "ID: " + to_string(count) + " " + line + "\n";
						i++;
					}	
					//cout << "Count is: " << count << "\n";
					count++;	
				}
				dataFile.close();
			}

			//print the selected values
			//cout << "Counting arraylen(matchesArr): \n";
			if(arrayLen(matchesArr) > 0){
				//cout << "Counting arraylen(fieldsArr): \n";
				if(arrayLen(fieldsArr) > 0){
					//cout << "made it here\n";
					while(matchesArr[j] != ""){
						printSelectedFields(matchesArr[j], fieldsArr);
						j++;
						//cout << "J is: " << j << "\n";
					}
					//cout << "realCount is: " << realCount << "\n";
				}
				else{
					while(matchesArr[j] != ""){
						cout << matchesArr[j] << '\n';
						j++;
					}	
				}
			}

		}
		else if(operation == "avg"){
			int retAvg = 0;
			float sumAvg = 0;
			int countAvg = 0;
			if (fieldsArr[0] == ""){

				//handle nothing case
				cout << "\nPlease enter a field into the avg query. Ex: db.final.avg(Salary)\n";
			}
			else{

				while ( getline (dataFile,line) ){
						
					line = trim(line);
					//process condition
					//ID is 0 needs to be 1
					//cout << "Line is: '" << line << "'\n";
					//cout << "conditionName is: '" << conditionNamesArr[0] << "'\n";
					//cout << "conditionValue is: '" << conditionValuesArr[0] << "'\n";
					//cout << "\n";
					retAvg = retreiveAvgValue(line, fieldsArr[0]);
					if(retAvg != 0){
						sumAvg += retAvg;
						//cout << "	sumAvg: "<< sumAvg<< "\n";
						countAvg++;
					}	
					//cout << count++ << "\n";
					retAvg = 0;
				}
				//cout << "sumAvg: " << sumAvg << "\n";
				//cout << "countAvg: " << countAvg << "\n";
				cout << "avg_" << fieldsArr[0] << ": " << (sumAvg/countAvg) << "\n";
				dataFile.close();
			}
		}
		else{
			cout << "Incorrect Operation";
		}
		
		//cout << line << '\n';

	}
	return;
}

/* Function that trims a string similiar to python's "strip()"
 *
 */
string trim( string const& original ){

	string::const_iterator right = find_if( original.rbegin(), original.rend(), IsNotSpace() ).base();
	string::const_iterator left = find_if(original.begin(), right, IsNotSpace() );
	return string( left, right );
}

/* Function that ensures a string consists of only digits
 *
 */
bool onlyDigits(string s){

	for (size_t i = 0; i < s.length(); i++){
		if (!isdigit(s[i])){
			return false;
	    	}
	}
	return true;
}

/* Evaluator used for booleans
 *
 */
vector<string> evalBoolean(string *data, string conditionName1, string conditionValue1, string conditionOperator1, string conditionName2, string conditionValue2, string conditionOperator2, string boolean){

	int i = 0;
	int j = 0;
	int k = 0;
	string arr1[500];
	string arr2[500];
	vector<string> arr3;
	vector<string>::iterator it;

	cout << "\nconditionName1: "<< conditionName1 << "\nconditionValue1: " << conditionValue1 << "\nconditionOperator1: "<< conditionOperator1 << "\n";
	cout << "\nconditionName2: "<< conditionName2 << "\nconditionValue2: " << conditionValue2 << "\nconditionOperator2: " << conditionOperator2 << "\n";
	cout << "\nBoolean: " << boolean << "\n";

	if (boolean.find(" and ") != std::string::npos or boolean.find(" or ") != std::string::npos) {
		    std::cout << "found!" << '\n';
	}

	//process arr1
	while(data[i] != ""){
		if(conditionMatches(data[i], conditionName1, conditionOperator1, conditionValue1)){
			arr1[j] = data[i];
			j++;
		}
		i++;
	}

	//process arr2
	i = 0;
	while(data[i] != ""){
		if(conditionMatches(data[i], conditionName2, conditionOperator2, conditionValue2)){
			arr2[k] = data[i];
			k++;
		}
		i++;
	}

	i = 0;
	j = 0;
	k = 0;
	//process boolean
	it = arr3.begin();
	if (boolean == "and"){
		while(arr1[i] != ""){
			while(arr2[j] != ""){
				if(arr1[i] == arr2[j]){
					it = arr3.insert ( it , arr1[i] );
					it = arr3.begin();
				}
				j++;
			}
			i++;
			j=0;
		}	
	}
	else if(boolean == "or"){

	}
	else{
		cout << "Error: spell 'or' or 'and' correctly\n";
	}

	return arr3;
}


/* Function that returns the fieldvalue of a document record if it contains the correct field 
 *
 */
int retreiveAvgValue(string line, string field){

	int i = 0;
	char ch;
	string cName = "";
	string cValue = "";
	int aValue;
	//cout << "\nLine is " << line << '\n';
	while(line.length() != i){

		ch = line[i];

		//find conditionName
		while(line[i] != ':'){
			/*
			if (line.length() == i){
				return 0;
			}
			*/
			ch = line[i];
			cName += ch;
			i++;
		}
		i++;
		i++;

		//find conditionValue
		while(line[i] != ' ' and i < line.length()){
			//cout << "i is: " << to_string(i) << '\n';
			//cout << "line.length() is: "<< to_string(line.length()) << '\n';
			ch = line[i];
			//cout << ch << "\n";
			cValue += ch;
			i++;
		}

		//cout << "	Line is: " << line << "\n";
		//cout << "	cName,cValue | " << cName <<","<<cValue<< " Checking for: " << field << '\n';
		cName = trim(cName);
		//cout << "'" << cValue << "' ";
		//cout << "Comparing: '" << cName << "' and '" << field << "'\n ";
		if((cName.compare(field) == 0) and onlyDigits(cValue)){
				//if(cName == field){
				//cout << "Is a digit\n";
				aValue = stoi(cValue);

				if(i <= line.length()){
					//cout << "	cName,cValue | " << cName <<","<<cValue<< " Checking for: " << field << '\n';
					//cout << cName << ": " << cValue << "\n";
					return aValue;
					//cout << "cName,cValue | '" << cName << "','" << cValue << "'\n";
				}
				/*
				else{
					return 0;
				}
				*/
				//cout << cName << ": " << cValue << "\n";
		}
		cName = "";
		cValue = "";
		
	}
	return 0;
}

/* Function that prints the correct fields of a document record
 *
 */
void printSelectedFields(string line, string *fieldsArr){

	int i = 0;
	int j;
	char ch;
	string fName;
	string fValue;
	bool foundField = false;
	//cout << "line is: "<< line<<"\n";
	if (arrayLen(fieldsArr) == 0){
		cout << " "<<line << "\n";
		return;
	}
	else{
		while(line.length() >= i){
			ch = line[i];

			//find conditionName
			//cout << "conditionName: \n";
			while(line[i] != ':'){
				ch = line[i];
				//cout << ch << "\n";
				fName += ch;
				i++;
			}
			i++;
			i++;

			//find conditionValue
			while(line[i] != ' ' and i < line.length()){
				ch = line[i];
				//cout << ch << "\n";
				fValue += ch;
				i++;
			}
			//cout << "\n";


			j = 0;
			//iterate through fields
			while(fieldsArr[j] != ""){

				//if field is selected
				if(fName == fieldsArr[j]){
					cout << " " << fName << ": " << fValue;
					foundField = true;
				}
				j++;
			}
			i++;

			//print newline if field is found

			/*
			j = 0;
			//iterate through fields 
			while(j < arrayLen(fieldsArr)){
				//if field is selected
				//cout << "fName is: " << fName << "\n";
				//cout << "fieldsArr[" << j << "] is: " << fieldsArr[j] << "\n";
				if(fName == fieldsArr[j]){
					cout << " " << fName << ": " << fValue;
					foundField = true;
				}
				j++;
			}
			*/
			fName = "";
			fValue = "";
		}

		//print newline if field is found
		if (foundField){
			cout << "\n";
		}

		return;
	}
}

/* Function that determines whether a document record contains the correct condition
 *
 */
bool conditionMatches(string line, string conditionName, string conditionOperator, string conditionValue){

	int i = 0;
	char ch;
	string cName = "";
	string cValue = "";
	int iValue;
	int icValue;
	line = trim(line);
	cout << "Line is '" << line << "'\n";
	if(conditionName == ""){
		return true;
	}
	while(line.length() >= i){
		ch = line[i];

		//find conditionName
		while(line[i] != ':'){
			if (line.length() == i){
				return false;
			}
			ch = line[i];
			cName += ch;
			i++;
		}
		i++;
		i++;

		//find conditionValue
		while(line[i] != ' ' and i < line.length()){
			//cout << "i is: " << to_string(i) << '\n';
			//cout << "line.length() is: "<< to_string(line.length()) << '\n';
			ch = line[i];
			//cout << ch << "\n";
			cValue += ch;
			i++;
		}

		cout << "	Line is: " << line << "\n";
		cout << "	cName,cValue | " << cName <<","<<cValue<< " Checking for: " << conditionName << "=" << conditionValue << '\n';
		cName = trim(cName);
		iValue = stoi(cValue);
		icValue = stoi(conditionValue);

		if(i <= line.length()){
			/*
			ch = line[i];
			cValue += ch;
			i++;
			*/
			//cout << "cName,cValue | '" << cName << "','" << cValue << "'\n";
			
			//operators
			//equal
			//cout << "	cName,cValue | " << cName <<","<<cValue<< " Checking for: " << conditionName << "=" << conditionValue << '\n';
			if(conditionOperator == "="){

				if(cName == conditionName and ((iValue) == (icValue))){
					//cout << "	MATCH: cName,cValue | " << cName <<","<<cValue<< " Checking for: " << conditionName << "=" << conditionValue << '\n';
					//cout << "matches";
					return true;
				}
				else if(cName == conditionName and ((iValue) != (icValue))){
					//cout << "Did not find\n";
					return false;
				}
				/*
				else{
					//cout << "Did not find here\n";
					return false;
				}
				*/
			}
			//not equal
			else if(conditionOperator == "<>"){

				if(cName == conditionName and ((cValue) != (conditionValue))){
					//cout << "	MATCH: cName,cValue | " << cName <<","<<cValue<< " Checking for: " << conditionName << "=" << conditionValue << '\n';
					//cout << "matches";
					return true;
				}
				else if(cName == conditionName and ((cValue) == (conditionValue))){
					//cout << "Did not find\n";
					return false;
				}
				/*
				else{
					//cout << "Did not find here\n";
					return false;
				}
				*/
			}
			//less than
			else if(conditionOperator == "<"){
				//cout << "In the right loop\n";
				if(cName == conditionName and ((iValue) < (icValue))){
					//cout << "	MATCH: cName,cValue | " << cName <<","<<cValue<< " Checking for: " << conditionName << "=" << conditionValue << '\n';
					//cout << "matches";
					return true;
				}
				else if(cName == conditionName and ((iValue) > (icValue))){
					//cout << "Did not find\n";
					return false;
				}
				/*
				else{
					//cout << "Did not find here\n";
					return false;
				}
				*/

			}
			//greater than
			else if (conditionOperator == ">"){
				if(cName == conditionName and ((iValue) > (icValue))){
					//cout << "	MATCH: cName,cValue | " << cName <<","<<cValue<< " Checking for: " << conditionName << "=" << conditionValue << '\n';
					//cout << "matches";
					return true;
				}
				else if(cName == conditionName and ((iValue) < (icValue))){
					//cout << "Did not find\n";
					return false;
				}
				/*
				else{
					//cout << "Did not find here\n";
					return false;
				}
				*/
			}
		}

		//cout << "cName,cValue | '" << cName << "','" << cValue << "'\n";
		//if match
		if(cName == conditionName and cValue == conditionValue){
			//cout << "	MATCH: cName,cValue | " << cName <<","<<cValue<< " Checking for: " << conditionName << "=" << conditionValue << '\n';
			//cout << "matches";
			return true;
		}
		else if(cName == conditionName and cValue != conditionValue){
			//cout << "Did not find here either\n";
			return false;
		}
		cName = "";
		cValue = "";
		i++;
		//cout << i << "\n";
		//cout << "Made it here without finding";
	}
	return false;
	//if match
	/*
	cout << "cName,cValue | '" << cName << "','" << cValue << "'\n";
	if(cName == conditionName and cValue == conditionValue){
		//cout << "	MATCH: cName,cValue | " << cName <<","<<cValue<< " Checking for: " << conditionName << "=" << conditionValue << '\n';
		//cout << "matches";
		return true;
	}
	else if(cName == conditionName and cValue != conditionValue){
		//cout << "Did not find\n";
		return false;
	}
	else{
		//cout << "Did not find here\n";
		return false;
	}
	*/
}

/* Counts and returns the Length of An Array
 *
 */
int arrayLen(string *arr){

	int i = 0;
	int count = 0;
	//cout << "Counting: \n";
	if(arr[i] == ""){
		return 0;
	}
	else{
		i++;
	}	

	while(arr[i] != ""){
		//cout << arr[i] << "\n";
		//cout << i << "\n";
		i++;
	}
	//cout << "ArrayLen Is: " << to_string(i) << '\n';
	return i++;
}

void Fatal(char const *fmt, ...)
{
	va_list ap;

	fprintf(stderr, "An error occured: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	exit(-1);
}

/* only -oXXX  or -o XXX options */

int ProcessOptions(int argc, char const **argv)
{
	int argIndex;
	int argUsed;
	int separateArg;
	char const *arg;

	argIndex = 1;

	while (argIndex < argc && *argv[argIndex] == '-')
	{
		/* check if stdin, represented by "-" is an argument */
		/* if so, the end of options has been reached */
		if (argv[argIndex][1] == '\0') return argIndex;

		separateArg = 0;
		argUsed = 0;

		if (argv[argIndex][2] == '\0')
		{
			arg = argv[argIndex + 1];
			separateArg = 1;
		}
		else
			arg = argv[argIndex] + 2;

		switch (argv[argIndex][1])
		{
			/*
			* when option has an argument, do this
			*
			*     examples are -m4096 or -m 4096
			*
			*     case 'm':
			*         MemorySize = atol(arg);
			*         argUsed = 1;
			*         break;
			*
			*
			* when option does not have an argument, do this
			*
			*     example is -a
			*
			*     case 'a':
			*         PrintActions = 1;
			*         break;
			*/

		case 'v': /* give the author's name and explanation on how the implementation performs the sorting in 0(n log n) time
				  -also give some empirical evidence (such as a table of input sizes versus time) that indicates your sort runs in 0(n log n) time - then immediatley exit */
			optionV = 1;
			break;
		case 'd': /* sort in decreasing order (default is increasing order) */
			optionD = 1;
			break;
		default:

			Fatal("option %s not understood\n", argv[argIndex]);
		}

		if (separateArg && argUsed)
			++argIndex;

		++argIndex;
	}

	return argIndex;
}
