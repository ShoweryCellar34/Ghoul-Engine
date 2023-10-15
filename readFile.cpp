#include <fstream>
#include <iostream>
#include <filesystem>

int main()
{
    std::ifstream inputSource("LICENSE");
    std::string lineSource, outputString;
    if(inputSource.is_open()) {
        while(inputSource) {
        std::getline(inputSource, lineSource);
        lineSource.append("\n");
        outputString.append(lineSource);
        }
        inputSource.close();
    }
    std::cout << outputString << std::endl;

    return 0;
}
