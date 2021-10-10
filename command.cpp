/*
Author: Curtis Ackland
Description: Hold all the information about the command the user inputted
Date: 2021-09-23
*/
#include <command.h>
using namespace boost::process;

/*
Name: Command
Description: initializes command attributes
Parameters: std::string input is the command the user has inputted
*/
Command::Command(std::string input)
{
    this->command = input;
    this->returnCode = 0;
    this->result = "";
}

/*
Name: ~Command
Description: Default destructor for Command class
*/
Command::~Command()
{
}

/*
Name: execute
Description: executes command and using pipe gets the result of the command and stores the result and return code. 
If the command errors it handles the error and puts the error message in result and sets returnCode to -1
*/
void Command::execute() // Executes the command and stores result, exit code, 
{
    this->result = "";
    this->returnCode = 0;
    ipstream pipe_stream;
    std::string line;
    child *c;
    try{
        c = new child(this->command, (std_out & std_err) > pipe_stream); //executes the given command
        c->wait();
        while (pipe_stream && std::getline(pipe_stream, line) && !line.empty()) //Collects all the output from the pipe and stores it in result
            result = result + line + "\n";
        this->returnCode = c->exit_code();
    } catch(process_error e){
        result = std::string(e.what());
        this->returnCode = -1;
    }
    
}

/*
Name: getCommand
Description: gets command that was inputted by user
Returns: command that was inputted
*/
std::string Command::getCommand()
{
    return this->command;
}

/*
Name: getResult
Description: gets result of the command inputted
Returns: result of the command that was executed
*/
std::string Command::getResult()
{
    return this->result;
}

/*
Name: getReturnCode
Description: gets returnCode of the command inputted
Returns: return code of the command that was executed
*/
int Command::getReturnCode()
{
    return this->returnCode;
}
