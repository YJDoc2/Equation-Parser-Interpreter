#include<iostream>
#include<fstream>

using namespace std;

int main(){
	ifstream fileReader;
	string line;
	fileReader.open("example.txt");
	while(!fileReader.eof()){						//Loops till we reach end of file
		getline(fileReader,line);
		cout<<line<<endl;
	}
	fileReader.close();
	return 0;
}