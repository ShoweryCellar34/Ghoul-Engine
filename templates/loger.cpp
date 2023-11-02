#include <iostream>
#include <string>
#include <fstream>

class Logger
{
    private:
        std::ofstream logFile;
        std::string tempBuffer;
        void log(std::string prefix, std::string message)
        {
            if(!save)
            {
                tempBuffer.append("[NOT SAVED]");
            }
            tempBuffer.append(prefix);
            tempBuffer.append(message);
            tempBuffer.append("\n");
            if(save)
            {
                logFile.open(logFilePath, std::ios::app);
                logFile << tempBuffer;
                logFile.close();
            }
            if(print)
            {
                std::cout << tempBuffer;
            }
            tempBuffer.clear();
        }
    public:
        std::string logFilePath = "log.txt";
        bool print = true;
        bool save = true;
        void Note(std::string message)
        {
            log("[NOTE] ", message);
        }
        void Warn(std::string message)
        {
            log("[WARN] ", message);
        }
        void Error(std::string message)
        {
            log("[ERROR] ", message);
        }
        void FatalError(std::string message)
        {
            log("[FATAL ERROR] ", message);
        }
        Logger()
        {
            logFile.open(logFilePath);
            logFile.clear();
            logFile.close();
        }
        Logger(bool print, bool save)
        {
            logFile.open(logFilePath);
            logFile.clear();
            logFile.close();
            this -> print = print;
            this -> save = save;
        }
        Logger(bool print, bool save, std::string logFilePath)
        {
            logFile.open(logFilePath);
            logFile.clear();
            logFile.close();
            this -> print = print;
            this -> save = save;
            this -> logFilePath = logFilePath;
        }
};

int main()
{
    Logger log;
    log.Note("12345");
    log.save = false;
    log.Warn("12345");
    log.save = true;
    log.Error("12345");
    return 0;
}
