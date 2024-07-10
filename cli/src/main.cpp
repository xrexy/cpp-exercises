#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include <stdexcept>

std::string execCommand(const std::string cmd, int &out_exitStatus)
{
    out_exitStatus = 0;
    auto pPipe = ::popen(cmd.c_str(), "r");
    if (pPipe == nullptr)
    {
        throw std::runtime_error("Cannot open pipe");
    }

    std::array<char, 256> buffer{};

    std::string result;

    while (not std::feof(pPipe))
    {
        auto bytes = std::fread(buffer.data(), 1, buffer.size(), pPipe);
        result.append(buffer.data(), bytes);
    }

    auto rc = ::pclose(pPipe);

    if (WIFEXITED(rc))
    {
        out_exitStatus = WEXITSTATUS(rc);
    }

    return result;
}

int main(int argc, char const *argv[])
{
    std::string path{};

    std::cout << "Template path('d' for default): ";
    std::cin >> path;

    if (path.empty() || path == "d")
    {
        path = "/home/desktop/Code/cpp/_template";
    }

    std::cin.clear();

    // check if absolute path
    if (path[0] != '/')
    {
        std::cout << "Path must be absolute" << std::endl;
        return 1;
    }

    std::string name{};
    std::cout << "Project name: ";
    std::cin >> name;

    std::cin.clear();

    if (name.empty())
    {
        std::cout << "Name cannot be empty" << std::endl;
        return 1;
    }

    std::string folderPath{};
    std::cout << "Project path: ";
    std::cin >> folderPath;

    std::cin.clear();

    if (folderPath[0] != '/')
    {
        std::cout << "Folder path must be absolute" << std::endl;
        return 1;
    }

    std::cout << "\n";

    int exitStatus{};
    auto cmd = "cp -r " + path + " " + folderPath;
    std::cout << cmd << "\n\n";

    auto result = execCommand(cmd, exitStatus);
    if (exitStatus != 0)
    {
        std::cout << result << std::endl;
        return 1;
    }

    std::cout << "[!] Copied template; Preparing project..." << "\n\n";

    cmd = "sed -i 's/MyProject/" + name + "/g' " + folderPath + "/premake5.lua";
    std::cout << cmd << std::endl;
    result = execCommand(cmd, exitStatus);
    if (exitStatus != 0)
    {
        std::cout << result << std::endl;
        return 1;
    }

    cmd = "sed -i '1 s/MyProject/" + name + "/g' " + folderPath + "/README.md";
    std::cout << cmd << "\n\n";
    result = execCommand(cmd, exitStatus);
    if (exitStatus != 0)
    {
        std::cout << result << std::endl;
        return 1;
    }

    std::cout << "\n [!] Complete! Make sure to run \"premake5 gmake\" to build your make files." << std::endl;
    return 0;
}
