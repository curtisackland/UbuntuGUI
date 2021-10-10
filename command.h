/*
Author: Curtis Ackland
Description: Header for Command class
Date: 2021-09-23
*/
#ifndef COMMAND_H
#define COMMAND_H
#include <string.h>
#include <iostream>
#include <boost/process.hpp>

class Command {
    private:
        std::string command;
        std::string result;
        int returnCode;
    public:
        Command(std::string);
        ~Command();
        void execute();
        std::string getCommand();
        std::string getResult();
        int getReturnCode();
};

#endif