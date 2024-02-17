#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <unistd.h>  
#include <sys/wait.h>

int exitWithError()
{
    std:: cout << "An Error Occured";
    exit(0);
    return -1;
}

int main()
{
    pid_t pid;
    int status, MODE;
    (isatty(STDIN_FILENO)) ? MODE = 1 : MODE = 0;
    //std::cin.ignore();
    std::ifstream fin("commands.txt");
    while(true){
        pid = fork();
        if (pid == 0) 
            {
                std::vector<char*> argv;
                std::cout << "\n>> ";
                std::string args,token;
                MODE ? std::getline(std::cin, args) : std::getline(fin, args);
                std::stringstream ss(args);
                while (ss >> token)
                { 
                    token.length() > 256 ? exitWithError() : 0; 
                    if(token[token.length()-1] == 'c' && token[token.length()-2] == '.' )
                        argv.push_back(strdup("g++"));
                    argv.push_back(strdup(token.c_str())); 
                }
                argv.push_back(nullptr); 
                (execvp(argv[0],argv.data()) == -1) ? exitWithError() : 0;
            }
            
        else 
            wait(&status);
    }
    return 0;
}
