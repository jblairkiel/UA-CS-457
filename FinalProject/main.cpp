#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

/* Attributions:
	Dr. Lusth provided an options.c file, which I modified into this main.cpp file

	-Blair Kiel
*/

/* options */
int optionV = 0;
int optionD = 0;

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
		string conditionBooleanArr[100];
		string fieldsArr[100];
		int j = 0;
		int k = 0;
		int l = 0;
		int m = 0;
		string str;

		if (operationChoice == "find"){

			//parse conditionChoices
			i++;
			while(queryIn[i] != ')' & queryIn.length() != i){

				char ch = queryIn[i]; 

				//condition name
				if(queryIn[i] == '='){
	       				conditionNamesArr[j]= str;
					j++;
					str = "";
				}

				//check if boolean
				else if(str == "and" or str == "or"){
					conditionBooleanArr[k] = str;
					str = "";
					k++;
				}

				//condition value
				else if(queryIn[i] == ' '){
					conditionValuesArr[l] = str;
					l++;
					str = "";
				}

				//condition value end 
				else if (queryIn[i] == ')'){
					conditionValuesArr[l] = str;
					l++;
					str = "";	
					break;
				}

				else{
					str += ch;
				}
				i++;

			}
			conditionValuesArr[l] = str;
			l++;
			i++;
			str = "";

			//Parse Fields
			i++;
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
	       				conditionNamesArr[j] = str;
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

		/*
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
			cout << conditionValuesArr[j] << ' ';
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
	  	cout << '\n';	
		*/



		/*Read in values*/
		string line;
		string file = argv[1];
		ifstream dataFile (file);
	 	if (dataFile.is_open()){
	 		while ( getline (dataFile,line) ){
	 			//cout << line << '\n';
	 		}
	 		dataFile.close();
		}
	}
	return 0;

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
