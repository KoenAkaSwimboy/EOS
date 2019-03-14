#include <iostream>
#include <string>
using namespace std;

string translate(string input, string variable){
	string resultaat = "";
	for(int i=0; i<variable.size(); i++){
		if(variable[i] >= 'a'){
			resultaat += variable[i] + ('A'-'a');}
		else{
			resultaat += variable[i] - ('A' - 'a');}}
	return resultaat;}

int main(int argc, char *argv[]){
	string s;
	if(argc != 2){
		cerr << "Deze functie heeft excact 1 argument nodig\n";
		return -1;}

	while(true){
		cin >> s;
		if(cin.eof()){
			return 0 ;}
		cerr << translate(argv[1], s) << endl;}
}
