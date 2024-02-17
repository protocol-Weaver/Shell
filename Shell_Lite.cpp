#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <unistd.h>  
#include <sys/wait.h>
int main()
{
    pid_t pid;
    int status, MODE = 1;
    std::cout << "Enter Mode (Console 1 and Batch 2) \n";
    std::cin >> MODE;
    std::cin.ignore();
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
                    if(token.find(".c")!= std::string::npos)
                        argv.push_back(strdup("g++"));
                    argv.push_back(strdup(token.c_str())); 
                }
                argv.push_back(nullptr); 
                if(execvp(argv[0],argv.data()) == -1)
                { 
                    std:: cout << "An Error Occured";
                    return -1;
                }
            }
            
        else 
            wait(&status);
    }
    return 0;
}
