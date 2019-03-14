#include "shell.hh"
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(){
string input;
while(true){
    cout << "Geef aan wat u wilt: ";
    getline(cin, input);        	   // Lees een regel
    if (input == "new_file") new_file();   // Kies de functie
    else if (input == "ls") list();        //   op basis van
    else if (input == "src") src();        //   de invoer
    else if (input == "find") find();
    else if (input == "python") python();
    else if (input == "exit") return 0;
    else if (input == "quit") return 0;
    else if (input == "error") return 1;

    if (cin.eof()) return 0; } }

void new_file(){
	string newfileinput;
	string tekstregel;
 	cout << "Geef bestandsnaam en locatie: " << endl;
 	getline(cin, newfileinput);

	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const char *pathname = newfileinput.c_str();
	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);

	while(true){
		cout << "Geef tekstregel: " << endl;
		getline(cin, tekstregel);
		if(tekstregel == "<EOF>"){
			break;}
		tekstregel += '\n';
		const char *buffer = tekstregel.c_str();
		write(fd, buffer, tekstregel.size());}
}

void list(){
	int pid = fork();
	if(pid == 0){
		char *args[] = {"/bin/ls", "-la", (char *) 0};
		execv("/bin/ls", args);
	}else{
		int exit_status;
		wait(&exit_status);
	}
}

void find(){
	int pid;
	int pip[2];
	int status;
	string search;

	cout << "Wat wilt u zoeken: ";
	getline(cin, search);
	const char * searching = search.c_str();

	pipe(pip);
	pid = fork();

	if(pid == 0){
		dup2(pip[1], 1);
		close(pip[0]);
		close(pip[1]);
		execlp("find", "find", ".", NULL);
	}else{
		wait(NULL);
	}

	pid = fork();
	if(pid == 0){
		dup2(pip[0], 0);
		close(pip[0]);
		close(pip[1]);
		execlp("grep", "grep", search, NULL);
	}
	close(pip[0]);
	close(pip[1]);
	wait(NULL);
}

void python(){
	int status3;
	char *args[2];

	args[0] = "/usr/bin/python";
	args[1] = NULL;

	if(fork() == 0)
		execv(args[0], args);
	else
		wait(&status3);
}

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
std::cout << byte; } //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
