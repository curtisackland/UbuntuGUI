/*
Author: Curtis Ackland
Description: Header for the MainWindow class
Date: 2021-09-23
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <vector>
#include <QListWidget>
#include "command.h"

namespace Ui {
	  class MainWindow;
}
 
class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		    explicit MainWindow(QWidget *parent = nullptr);
		    private slots:
			      void handleCommand();
				  void handleList(QListWidgetItem*);
	private: 
			  Command *command; // command object handles executing and getting output for command
			  std::vector<Command*> commandList; // stores all executed commands
			  QPushButton *m_button;
			  QLineEdit *m_commandInput;
			  QLabel *m_commandText;
			  QLabel *m_outputText;
			  QLabel *m_returnCode;
			  QLabel *m_historyText;
			  QTextEdit *m_output;
			  QListWidget *m_list;
};
#endif // MAINWINDOW_H