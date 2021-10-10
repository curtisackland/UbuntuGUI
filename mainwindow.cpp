/*
Author: Curtis Ackland
Description: Builds the CommandGUI window and all the GUI while handling user input
Date: 2021-09-23
*/
#include "mainwindow.h"

/*
Name: MainWindow
Description: Creates all the elements in the new GUI including labels, a button, textfields, and a user input box
Parameters: QWidget *parent is the point to the main parent
*/
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{

  // Create the execute button
  m_button = new QPushButton("Execute", this);
  // set size and location of the button
  m_button->setGeometry(QRect(QPoint(310, 10), QSize(80, 25)));
  // Connect button signal to appropriate slot
  connect(m_button, &QPushButton::released, this, &MainWindow::handleCommand);

  // Create user input text box
  m_commandInput = new QLineEdit(this);
  m_commandInput->setGeometry(QRect(QPoint(100, 10), QSize(200, 25)));
  connect(m_commandInput, SIGNAL(returnPressed()),this, SLOT(handleCommand()));


  // Labels
  m_commandText = new QLabel("Command: ", this);
  m_commandText->setGeometry(QRect(QPoint(20, 10), QSize(100, 25)));

  m_outputText = new QLabel("Output ", this);
  m_outputText->setGeometry(QRect(QPoint(20, 35), QSize(100, 25)));

  m_returnCode = new QLabel("Exit status: 0", this);
  m_returnCode->setGeometry(QRect(QPoint(20, 290), QSize(100, 25)));

  m_historyText = new QLabel("History", this);
  m_historyText->setGeometry(QRect(QPoint(20, 320), QSize(100, 25)));


  //Output text field
  m_output = new QTextEdit(this);
  m_output->setGeometry(QRect(QPoint(10, 60), QSize(380, 230)));
  m_output->setReadOnly(true);

  //History list box
  m_list = new QListWidget(this);
  m_list->setGeometry(QRect(QPoint(10, 350), QSize(380, 230)));
  connect(m_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleList(QListWidgetItem*)));

}

/*
Name: handleCommand
Description: when the execute button is pressed, or return is pressed, this executes 
the command that was given using the Command class. It outputs the result to the output text field and adds the command to the history list
*/
void MainWindow::handleCommand(){
  if(!m_commandInput->text().toStdString().empty()){
    command = new Command(m_commandInput->text().toStdString() + "\0");
    command->execute();
    m_output->setText(QString::fromStdString(command->getResult()));
    m_returnCode->setText(QString::fromStdString("Exit status: " + std::to_string(command->getReturnCode())));
    m_list->addItem(m_commandInput->text()+ " (" + QString::fromStdString(std::to_string(command->getReturnCode())) + ")"); // Add command to history list
    commandList.push_back(command);  // Pushing command object to the history vector
  }
}

/*
Name: handleList
Description: when a command in the history list is clicked this will find the index of that command. It will then use the index with the vector storing all the Command 
objects to repopulate the gui with the old commands output, returncode, and command
*/
void MainWindow::handleList(QListWidgetItem* item){ // When a command in the history list is clicked this will update the UI to display the output of that command
  int counter = 0;
  while(m_list->item(counter) != item){ // Finds command in list
    counter++;
  }
  m_commandInput->setText(QString::fromStdString(commandList[counter]->getCommand()));  //Repopulating GUI with clicked on command
  m_output->setText(QString::fromStdString(commandList[counter]->getResult()));
  m_returnCode->setText(QString::fromStdString("Exit status: " + std::to_string(commandList[counter]->getReturnCode())));

}
