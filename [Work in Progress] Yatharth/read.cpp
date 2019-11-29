#include<iostream>
#include<fstream>

using namespace std;

int main(){
	ifstream fileReader;
	string line;
	int countLines=0;
	fileReader.open("example.txt");
	if (fileReader.bad()||!fileReader){			//Prints Error message if file is empty or doesnt exist
		cout<<"Invalid file"<<endl;
	}
	else{
		while(getline(fileReader,line)){						//Loops till we reach end of file
			countLines++;
			cout<<line<<endl;
		}
	}
	cout<<"Number of Lines: "<<countLines<<endl;
	fileReader.close();
	return 0;
}