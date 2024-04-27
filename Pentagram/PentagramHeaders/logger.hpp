#pragma once
#define LOGGER

#include <includes.hpp>
#include <utilities/time.hpp>

namespace PNT
{
    class logger
    {
    public:
        std::string source;

        // Logs a message with a level.
        void log(unsigned short level, const char *message)
        {
            calculateTime(&currentTime);
            buffer = ('[' + currentTime.hour + ':' + currentTime.minute + ':' + currentTime.second + "][" + numToStr(level) + (source.empty() ? "" : "][" + source) + "]: " + message);
            std::cout << std::endl << buffer;
            myfile << std::endl << buffer;
        }
        // Logs a message with a level.
        void log(unsigned short level, const char *message, const char *sender)
        {
            calculateTime(&currentTime);
            const char *newSender = "][" + *sender;;
            buffer = ('[' + currentTime.hour + ':' + currentTime.minute + ':' + currentTime.second + "][" + numToStr(level) + sender + "]: " + message);
            std::cout << std::endl << buffer;
            myfile << std::endl << buffer;
        }
        // Postfixes a message on to the end of the previous message.
        void postfix(const char *postfix)
        {
            buffer = postfix;
            std::cout << buffer;
            myfile << buffer;
        }

        logger()
        {
            calculateTime(&currentTime);
            myfile.open(currentTime.day + '-' + currentTime.month + '-' + currentTime.year + ".txt");
        }
    private:
        timeData currentTime;
        std::string buffer;
        std::ofstream myfile;

        std::string numToStr(unsigned short number)
        {
            switch(number)
            {
            case 0:
                return "NOTE";
                break;
            case 1:
                return "WARN";
                break;
            case 2:
                return "ERROR";
                break;
            case 3:
                return "FATAL";
                break;
            default:
                return "N/A";
            }
        }
    };
    logger log;
}
