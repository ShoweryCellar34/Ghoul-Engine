//#include <Pentagram.hpp>
//
//int main(int argc, char *argv[])
//{
//    return 0;
//}
//
// C++ Program to implement Date and Time parsing using
// <ctime>
// C++ Program to implement Date and Time Parsing using
// chrono
#include <iostream>
#include <ctime>

int main() {
    // Get the current time
    time_t currentTime = time(0);

    // Create a buffer to store the formatted time
    char buffer[80];

    // Format the current time
    strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", localtime(&currentTime));

    std::cout << "The current time in the specified format is: " << buffer << std::endl;

    return 0;
}
