//System.String:
#define SYSTEM_STRING_CONSOLE
#include "String.hpp"
using namespace System;
//std::vector:
#include <vector>
//std::map:
#include <map>
//file io:
#include <fstream>
//file system:
#include <filesystem>
namespace fs = std::filesystem;

#define INCLUDE_STRING "#include"

std::string get_include_file_name(const std::string& line)
{
    if (StringA::StartsWith(line, INCLUDE_STRING))
    {
        std::string name = StringA::Trim(StringA::Substring(line, std::string(INCLUDE_STRING).size()));
        return StringA::Replace(name, "\"", "");
    }
    return StringA::Empty();
}

void find(const std::string& path, int index)
{

}

int main(int argc, char** argv)
{
    //i/o path:
    std::string input_folder_path;
    std::string output_file_path;
    //read:
    std::map<std::string, std::string> headerFilesDict;
    std::map<std::string, std::string> sourceFilesDict;
    //write:
    std::vector<std::string> output_lines;
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
        int index = StringA::LastIndexOf(item.path(), "/");
        if (index == -1) throw "Exception";
        std::string fileName = StringA::Substring(item.path(), index + 1);
        int dotIndex = StringA::LastIndexOf(fileName, ".");
        if (dotIndex == -1) continue;
        std::string extension = StringA::Substring(fileName, dotIndex + 1);
        if (extension == "hpp" || extension == "h")
        {
            headerFilesDict[fileName] = item.path();
        }
        else if(extension == "cpp" || extension == "c")
        {
            sourceFilesDict[fileName] = item.path();
        }
    }
    //
    for (const auto& item : headerFilesDict)
    {
        Console::WriteLine(item.first);
        //item.second;
    }
    //
    for (const auto& item : sourceFilesDict)
    {
        Console::WriteLine(item.first);
    }
    return 0;
}