//System.String:
#define SYSTEM_STRING_CONSOLE
#include "String.hpp"
using namespace System;
//file io:
#include <fstream>
//file system:
#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    std::string input_folder_path;
    std::string output_file_path;
    //not enough parameters:
    if (argc < 3)
    {
        //try to read config.txt:
        std::ifstream input;
        input.open("config.txt");
        if (!input.is_open())
        {
            Console::WriteLine(U8("Not enough parameters : gen <input_folder_path> <output_file_path>"));
            return -1;
        }
        int index = 0;
        std::string line;
        while (std::getline(input, line))
        {
            if (index == 0) input_folder_path = line;
            if (index == 1) output_file_path = line;
            index++;
        }
        input.close();
        if (index < 2)
        {
            Console::WriteLine(U8("Not enough lines in config.txt!"));
            return -1;
        }
    }
    //enough parameters:
    else
    {
        input_folder_path = argv[1];
        output_file_path = argv[2];
    }
    //iterate input files:
    for (const auto& item : fs::directory_iterator(input_folder_path))
    {
        Console::WriteLine(item.path().string());
    }
    return 0;
}