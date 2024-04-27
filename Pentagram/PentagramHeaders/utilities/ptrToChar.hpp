#pragma once

#include <includes.hpp>

namespace PNT
{
    // Resizes and fills the char array with the const char *.
    void ptrToChar(char *&array, const char* source)
    {
        unsigned int sourceSize = strlen(source); // Get string length
        unsigned int newSize = sourceSize + 1; // New size (source size + null terminator)
        char* newArray = new char[newSize]; // Allocate memory for the new array
        strncpy(newArray, source, sourceSize); // Copy the contents of the source string into the new array
        newArray[sourceSize] = '\0'; // Ensure null-termination
        delete[] array; // Deallocate memory of the original array
        array = newArray; // Update the original array pointer
    }
}
