#include <unistd.h>
#include <limits.h>
#include <string>
#include <iostream>

void setWorkingDirectoryToProjectRoot()
{
    char path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len != -1)
    {
        path[len] = '\0';
        std::string fullPath(path);
        std::string::size_type pos = fullPath.find("/build/");
        if (pos != std::string::npos)
        {
            std::string rootDir = fullPath.substr(0, pos);
            if (chdir(rootDir.c_str()) == 0)
            {
                // std::cout << "Diretório de trabalho ajustado para: " << rootDir << std::endl;
            }
            else
            {
                std::cerr << "Failed to set working directory." << std::endl;
                exit(EXIT_FAILURE); // Exit the program if adjustment fails
            }
        }
    }
}
