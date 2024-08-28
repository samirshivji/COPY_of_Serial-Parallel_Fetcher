#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::string inputBuffer;
    std::vector<std::string> commandArguments;
    pid_t processID, waitResult;
    int status;

    while(true) {
        std::cout << "cmd> ";
        std::getline(std::cin, inputBuffer);

        if(inputBuffer == "exit") {
            std::cout << "Bye.\n";
            break;
        }

        // Tokenized the input
        size_t pos = 0;
        std::string token;
        while((pos = inputBuffer.find(' ')) != std::string::npos) {
            token = inputBuffer.substr(0, pos);
            commandArguments.push_back(token);
            inputBuffer.erase(0, pos + 1);
        }
        commandArguments.push_back(inputBuffer); // Last argument gets pushed back

        std::vector<char*> argv;
        for (const auto& arg : commandArguments) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr); // Null-terminates the argument list

        processID = fork();

        if(processID == 0) { // Child process starts here
            execvp(argv[0], argv.data());
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (processID > 0) { // Parent process starts here
            do {
                waitResult = waitpid(processID, &status, 0);
            } while (waitResult == -1 && errno == EINTR); // Repeats if waitpid was interrupted

            if (waitResult == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status)) {
                std::cout << "User command " << argv[0] << " execution is finished with exit status " << WEXITSTATUS(status) << ".\n";
            } else if (WIFSIGNALED(status)) {
                std::cout << "User command " << argv[0] << " terminated by signal " << WTERMSIG(status) << ".\n";
            }
        } else {
            perror("fork"); 
            exit(EXIT_FAILURE);
        }

        commandArguments.clear(); // Clear the arguments for the next command
    }

    return 0;
}
