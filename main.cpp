/*
Author: Curtis Ackland
Description: Initializes the application and creates the window
Date: 2021-09-23
*/
#include "mainwindow.h"
 
int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.resize(400, 600); // resizing the window
	mainWindow.show();
	return app.exec();
}