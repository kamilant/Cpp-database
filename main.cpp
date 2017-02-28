
#include "dependencies.h"
#include "DMethods.h"
#include "prototypes.h"
#include "helpers.cpp" //helper functions
using namespace std;
//GLOBALS
vector<DMethods> myMethods; // Objects from database are loaded into this vector string
vector<string> methods, dFeature, iType, physical;

void loadObjectsIntoMemory(bool reloadObjects) {
		if (reloadObjects) {
			methods.clear();
			dFeature.clear();
			iType.clear();
			physical.clear();
			myMethods.clear();
			remove("tmp.txt");
			try {
				system("clear");
			} catch(...) {
				system("clr");
			}
			clog << "\033[31m---------------RE-LOADING OBJECTS INTO MEMORY-----------\033[m\n";
		}
		if (!reloadObjects){

			clog << "\033[34m---------------LOADING OBJECTS INTO MEMORY-----------\033[m\n";
			ofstream temp;
		}
		vector<string> data;
		int counter = 0;
		ifstream database("database.txt");
		ofstream mNames("./properties/methods.txt");
		ofstream pPhenomenas("./properties/phenomenas.txt");
		ofstream dFeatures("./properties/features.txt");
		ofstream iTypes("./properties/imagetypes.txt");
		bool startExtraction = false;
		string line, strBuild, word;

		while (getline(database, line)) {
			data.push_back(line);
		}

		for (size_t i = 0; i < data.size(); i++) {
	 		if (data[i][0] == '-' && data[i][sizeof(data)-1] != '\n') {
	 			counter++;
	 		}
	 		if (data[i][0] == '=') {
	 			counter = 0;
	 		}
	 		if (counter == 1) {
	 			istringstream iss(data[i]);
	 			while (iss >> word) {
	 						if (word == "[") {
	 							startExtraction = !startExtraction;
	 						}

	 						if (startExtraction == true) {
	 							if (word != "[" && word != "]") {
	 								strBuild.append(word + " ");
	 							}
	 						}

	 					if (word == "]") {
	 						startExtraction = !startExtraction;
	 						methods.push_back(strBuild);
	 						mNames << strBuild  << endl << "==="<<endl;
	 						strBuild = "";
	 					}
	 			}
	 		}

	 		if (counter == 2) {
	 			istringstream iss(data[i]);
	 			while (iss >> word) {
	 					if (word == "[") {
	 						startExtraction = !startExtraction;
	 					}

	 					if (startExtraction) {
	 						if (word != "[" && word != "]" && word != "_") {
	 							strBuild.append(word + " ");
	 						}
	 					}
	 					if (word == "]") {
	 						startExtraction = !startExtraction;
	 						physical.push_back(strBuild);
	 						pPhenomenas << strBuild<< endl<< "==="<<endl;
	 						strBuild = "";
	 					}
	 			}
	 		}
	 		if (counter == 3) {
	 			istringstream iss(data[i]);
	 			while (iss >> word) {
	 				if (word == "[") {
	 					startExtraction = !startExtraction;
	 				}
	 				if (startExtraction == true) {
	 					if (word != "[" && word != "]") {
	 						strBuild.append(word + " ");
	 					}
	 				}

	 				if (word == "]") {
	 					startExtraction = !startExtraction;
	 					dFeature.push_back(strBuild);
	 					dFeatures << strBuild  << endl<< "==="<<endl;
	 					strBuild = "";
	 				}
	 			}
	 		}
	 		if (counter == 4) {
	 			istringstream iss(data[i]);
	 			while (iss >> word) {
	 				if (word == "[") {
	 					startExtraction = !startExtraction;
	 				}
	 				if (startExtraction == true) {
	 					if (word != "[" && word != "]") {
	 						strBuild.append(word + " ");
	 					}
	 				}

	 				if (word == "]") {
	 					startExtraction = !startExtraction;
	 					iType.push_back(strBuild);
	 					iTypes << strBuild << endl << "==="<<endl;
	 					strBuild = "";
	 				}
	 			}
	 		}
	 	}

		for (size_t i = 0; i < methods.size(); i++) {
			DMethods* p;
			DMethods method(methods[i], physical[i], dFeature[i], iType[i]);
			p = &method;
			myMethods.push_back(*p);
		}
		database.close();
		mNames.close();
		dFeatures.close();
		iTypes.close();
		pPhenomenas.close();
	}
void saveObject(DMethods *method){
    ofstream database;
    database.open("database.txt", ofstream::out | ofstream::app);

    for(int i = 0; i < 4; i++){
			database << method -> getProperties()[i] << endl;
    }

		myMethods.push_back(*method);
		database << "======================================= " << endl;
    database.close();
}
void dumpData() {
	ifstream database("database.txt");
	ofstream temp("dumpTemp.txt");
	for (size_t i = 0; i < myMethods.size(); i++) {
		temp << myMethods[i].getMethodName() <<endl;
		temp << myMethods[i].getPhysicalPhenomena() <<endl;
		temp << myMethods[i].getDepictedFeature() <<endl;
		temp << myMethods[i].getImageType() <<endl;
		temp << "======================================" <<endl;
	}
	temp.close();
	database.close();
	remove("database.txt");
	rename("dumpTemp.txt", "database.txt");
}
void asserto() {
	for (int i = 0; i <= 5; i++) {
		string iter = to_string(i);
		DMethods* p;
		DMethods method("method"+iter+" ", "physicalP"+iter+" ", "depictedFeature"+iter+" ", "imageType"+iter+" ");
		p = &method;
		saveObject(p);
	}
	system("clear");
	cout << "\033[34m Successfully added to DB\033[m";
	init(false);
}
void removeMethod() {
	unsigned int methodId;
	unsigned int myMethodSizeBefore;
	string saveRemovedMethod;
	ifstream database;
	ofstream temp;

	temp.open("tempDatabaseRemove.txt", ofstream::out);
	database.open("database.txt");

	if (!database.is_open()) {
		cout << "Failed to open input file\n Close file first...";
		init(false);
	}
	if (myMethods.size() == 0) {
		clear();
		cout << "\033[33m-----Nothing to remove. Your\033[m \033[32m D A T A B A S E\033[m is \033[32mE M P T Y.\033[m \033[33mTry adding something first-----\033[m\033[m" << endl;
		cin.ignore();
		cout << "Press \033[34m E N T E R \033[m to continue\n";
		getchar();
		clear();
		init(false);
	}
	cin.ignore();
	clear();
	cout << "Choose what to remove: \n";
	for (size_t i = 0; i < myMethods.size(); i++) {
		clog <<"ID: [ \033[35m"<< i << "\033[m ] " << myMethods[i].getMethodName() <<endl ;
		clog << "======================================" <<endl;
	}
	cin >> methodId;
	myMethodSizeBefore = myMethods.size();
	saveRemovedMethod = myMethods[methodId].getMethodName();
	myMethods.erase(myMethods.begin() + methodId);
	clear();
	cout << "-- Method removed. --" << endl << endl;
	for (size_t i = 0; i < myMethods.size(); i++) {
		temp << myMethods[i].getMethodName() <<endl;
		temp << myMethods[i].getPhysicalPhenomena() <<endl;
		temp << myMethods[i].getDepictedFeature() <<endl;
		temp << myMethods[i].getImageType() <<endl;
		temp << "======================================" <<endl;

		if (i == methodId) {
			clog <<"\n->	\033[44m- R E M O V E D - ID: "<< i << " "<< saveRemovedMethod <<"\n\033[m"<<endl;

		}
		if (i >= myMethods.size()-1 && i == methodId - 1) {
			clog <<"\n->	\033[44m- R E M O V E D - ID: "<< i + 1 << " "<< saveRemovedMethod <<"\n\033[m"<<endl;
		}
		clog <<"ID: [ \033[35m"<< i << "\033[m ] " << myMethods[i].getMethodName() <<endl;
		clog << "======================================" <<endl;
	}
	cout << "Press \033[34m E N T E R \033[m to continue\n";
	cin.ignore();
	cin.clear();
	getchar();
	temp.close();
	database.close();
	remove("database.txt");
	rename("tempDatabaseRemove.txt", "database.txt");
	clear();
	init(false);
}
void addMethod(){
		int id;
    string methodName,
				   physicalP,
				   depictedFeature,
				   imageType;
    char s;
    string result;
    DMethods *p; //pointer to the created object
    cout << "Provide method name: ";
    getline(cin >> ws, methodName);

    cout << "Describe Physical Phenomena "<<endl;
    getline(cin >> ws,  physicalP, '|');

    cout << "Depicted feature: "<< endl;
    getline(cin >> ws,  depictedFeature, '|');

    cout << "Image Type: " << endl;
    getline(cin >> ws, imageType);

    DMethods method(methodName, physicalP, depictedFeature, imageType);
    p = &method; // create reference for created object
    saveObject(p); // pass created object to save their properties
		clear();
		cout << "\033[36m -- Method Added. --\033[m" << endl;
		cout << "Press \033[34m E N T E R \033[m to continue\n";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.clear();
		clear();
    init(false);
}
void findMethod(){
	ifstream database;
	unsigned int curLine = 0;
	string line;
	string methodName;
	bool found = false,
			 zeroFlag = false;

	database.open("database.txt");
	clear();
	cout << "Provide method name to find: -> ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin >> ws, methodName);
	clear();
	while(getline(database, line)) {
	    curLine++;
	    if (line.find(methodName) != string::npos) {
					found = true;
	        cout << "\033[31mfound: \033[m" << methodName << " in line: "<< curLine << endl << endl;
	    }
			if (found == true) {
				zeroFlag = true;
				cout << line << endl;
				if (line[0] == '=') {
					found = false;
				}
			}
	}
	if (zeroFlag == false) {
		clear();
		cout << "\033[31mNothing found. Try changing your query.\033[m\n";
	}
	database.close();
	cout << "Press \033[34m E N T E R \033[m to continue\n";
	getchar();
	clear();
	init(false);
}
void editMethod() {
	ifstream database("database.txt");
	ofstream editTempDatabase("editTempDatabase.txt");
	string editedContent,
				 line;
	int answer = 0;

	if (myMethods.size() == 0) {
		clear();
		cout << "\033[33m-----Nothing to edit. Your\033[m \033[32m D A T A B A S E\033[m is \033[32mE M P T Y.\033[m \033[33mTry adding something first-----\033[m\033[m" << endl;
		cin.ignore();
		cout << "Press \033[34m E N T E R \033[m to continue\n";
		getchar();
		clear();
		init(false);
	}

	cin.clear();
	clear();
	string headerText = "\033[36mChoose what property do you want to edit: \033[m";
	string text = " \n 1. Methods"
					"\n 2. Physical Phenomenas"
					"\n 3. Depicted Feature"
					"\n 4. Image Feature\n";
					do {
						cout << headerText;
						cout << text;
						cin.clear();
						while (!(cin >> answer) || ((answer <= 0) || (answer >= 5)) ) {
							clear();
							cout << headerText << "\n\n\033[31mWrong input. Please choose one of avaliable properties.\n\033[m";
							cout << text;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
					} while(((answer <= 0) || (answer >= 5)));
	clear();
	switch (answer) {
		case 1:
			for (size_t i = 0; i < myMethods.size(); i++) {
				clog << "ID: [\033[33m"<< i << "\033[m]" << myMethods[i].getMethodName()<< endl;
				clog << "-------" << endl;
			}
			answer = 0;
			cout << "\033[31m What do you want to edit?\033[m" << endl;
			cin >> answer;
			cout<< " -> "<< answer << endl;
			cout << "\033[31m Rewrite now and hit ENTER to change: \033[m ";
			getline(cin >> ws, editedContent);
			myMethods[answer].setMethodName(editedContent);
			dumpData();
			clear();
			init(false);
		break;

		case 2:
			for (size_t i = 0; i < myMethods.size(); i++) {
				clog << "ID: [\033[33m"<< i << "\033[m]" << myMethods[i].getPhysicalPhenomena()<< endl;
				clog << "-------" << endl;
			}
			answer = 0;
			cout << "\033[31m What do you want to edit?\033[m" << endl;
			cin >> answer;
			cout<< " -> "<< answer << endl;
			cout << "\033[31m Rewrite now and hit ENTER to change: \033[m ";
			getline(cin >> ws, editedContent, '|');
			myMethods[answer].setPhysicalPhenomena(editedContent);
			dumpData();
			clear();
			init(false);
		break;

		case 3:
			for (size_t i = 0; i < myMethods.size(); i++) {
				clog << "ID: [\033[33m"<< i << "\033[m]" << myMethods[i].getDepictedFeature() << endl;
				clog << "-------" << endl;
			}
			answer = 0;
			cout << "\033[31m What do you want to edit?\033[m" << endl;
			cin >> answer;

			cout<< " -> "<< answer << endl;
			cout << "\033[31m Rewrite now and hit ENTER to change: \033[m ";
			getline(cin >> ws, editedContent, '|');
			myMethods[answer].setDepictedFeature(editedContent);
			dumpData();
			clear();
			init(false);
		break;

		case 4:
			for (size_t i = 0; i < myMethods.size(); i++) {
				clog << "ID: [\033[33m"<< i << "\033[m]" << myMethods[i].getImageType() << endl;
				clog << "-------" << endl;
			}
			answer = 0;
			cout << "\033[31m What do you want to edit?\033[m" << endl;
			cin >> answer;
			cout<< " -> "<< answer << endl;

			cout << "\033[31m Rewrite now and hit E N T E R to change: \033[m ";
			getline(cin >> ws, editedContent);
			myMethods[answer].setImageType(editedContent);
			dumpData();
			clear();
			init(false);
		break;
	}
}
void listAllObjects() {
	clear();
	for (size_t i = 0; i < myMethods.size(); i++) {
		clog << myMethods[i].getMethodName() <<endl ;
		clog << myMethods[i].getPhysicalPhenomena() <<endl ;
		clog << myMethods[i].getDepictedFeature() <<endl ;
		clog << myMethods[i].getImageType() <<endl ;
		clog << "======================================" <<endl;
	}
	clog << "=="<<endl;
	cin.ignore();
	cin.clear();
	getchar();
	clear();
	init(false);
}
void init(bool initialInit) {
		if (initialInit) {
			/* code */
			system("clear");
	    cout << "===============================================================================\n";
	    cout << "*******************************************************************************\n";
	    cout << "****                                                                      *****\n";
	    cout << "**** Program do pobierania danych na temat technik obrazowania medycznego *****\n";
	    cout << "****                                                                      *****\n";
	    cout << "*******************************************************************************\n\n";
	    cout << "================================================================================\n";
			loadObjectsIntoMemory(false);
		}
    cout << "\n\n\n\033[34m What do you want to do?\n\n\n\033[m";

		int number;

  string text =
	    "1. Add new method name\n"
			"2. Find method\n"
			"3. Edit method\n"
			"4. Remove method\n"
	    "5. assert db\n"
			"6. list objects\n";
	do {
		cout << text;
		cin.clear();
		while (!(cin >> number) || ((number <= 0) || (number >= 7)) ) {
			clear();
			cout << "\033[31m Please provide number from \033[m\033[37m\033[40m 1 to 6 \033[m\033[31m to get started.\033[m\n\n";
			cout << text;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while(((number <= 0) || (number >= 7)));

	    switch(number){
	    case 1:
					addMethod();
			break;
	    case 2:
					findMethod();
			break;
	    case 3:
					editMethod();
			break;
			case 4:
					removeMethod();
			break;
			case 5:
					asserto();
			break;
			case 6:
					listAllObjects();
			break;
	    }
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
init(true);
return 0;
};
