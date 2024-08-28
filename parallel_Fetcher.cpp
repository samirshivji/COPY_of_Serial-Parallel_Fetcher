#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    std::vector<pid_t> children;

    int count = 0; // Keeps track of the order of child processes
    // File gets read line by line
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        double lat, lon;
        if (!(iss >> lat >> lon)) { break; } // Error

        // Fork a new process
        pid_t pid = fork();
        if (pid == 0) {
            // Child process, which executes curl and redirects output to a file
            std::string outputFileName = "output" + std::to_string(++count) + ".txt";
            std::string jsonFileName = "file" + std::to_string(count) + ".json";
            std::string url = "https://api.open-meteo.com/v1/forecast?latitude=" 
                              + std::to_string(lat) + "&longitude=" 
                              + std::to_string(lon) + "&current_weather=True";

            // Opens a file to redirect curl output
            int outputFileDescriptor = open(outputFileName.c_str(), O_WRONLY|O_CREAT|O_TRUNC, 0644);
            if (outputFileDescriptor < 0) {
                perror("open");
                exit(1);
            }
            // Redirects standard output and standard error to the file
            dup2(outputFileDescriptor, STDOUT_FILENO);
            dup2(outputFileDescriptor, STDERR_FILENO);
            close(outputFileDescriptor); // Close the file descriptor as it's no longer needed

            execlp("/usr/bin/curl", "curl", "-o", jsonFileName.c_str(), url.c_str(), (char*) NULL);
            perror("execlp"); // If execlp returns, it's an error
            exit(1);
        } else if (pid > 0) {
            // Parent process which adds child to vector
            children.push_back(pid);
        } else {
            std::cerr << "Failed to fork." << std::endl;
            return 1;
        }
    }

    // Wait for all child processes to finish
    for (pid_t k : children) {
        waitpid(k, NULL, 0);
    }

    // After all children have finished, prints the contents of the output files
    for (int i = 1; i <= count; ++i) {
        std::string outputFileName = "output" + std::to_string(i) + ".txt";
        std::ifstream outputFile(outputFileName);
        std::cout << outputFile.rdbuf();
        std::cout << std::endl;
    }

    return 0;
}
