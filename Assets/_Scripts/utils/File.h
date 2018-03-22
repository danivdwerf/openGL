#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace Utilities
{
    class File
    {
        public: static std::string getFileContent(const char* path)
        {
            std::ifstream file;
            std::stringstream ss;
            file.exceptions(std::fstream::failbit|std::fstream::badbit);
            try
            {   
                file.open(path);
                ss << file.rdbuf();
                std::string tmp = ss.str();
                file.close();
                ss.clear();
                return tmp;
            }
            catch(std::fstream::failure e)
            {
                std::cout << "File.h: FAILED TO GET FILE CONTENT:\n" << e.what() << '\n';
                return "";
            }
        }
    };
};
#endif