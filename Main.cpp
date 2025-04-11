#include <iostream>
#include <csignal>
#include "include/Archiver.hpp"


std::atomic<bool> stopFlag = false;

void signalHandler(int signal) 
{
    if (signal == SIGINT) {
        std::cerr << "\nOperation interrupted by user." << std::endl;
        stopFlag = true;
    }
}

int main(int argc, char* argv[]) {
    std::signal(SIGINT, signalHandler);

    if (argc != 4) {
        std::cerr << "Archiver a <input file> <archive file>\nArchiver u <archive file> <output file>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    try {
        if (mode == "a") {
            archive(inputFile, outputFile, stopFlag);
        }
        else if (mode == "u") {
            unzip(inputFile, outputFile, stopFlag);
        }
        else {
            std::cerr << "Unknown mode: " << mode << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}