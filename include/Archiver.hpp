#pragma once
#include <fstream>
#include <iostream>
#include <zstd.h>
#include <string>
#include <atomic>


void archive(const std::string& inputFile, const std::string& archiveFile, std::atomic<bool>& stopFlag);
void unzip(const std::string& archiveFile, const std::string& outputFile, std::atomic<bool>& stopFlag);