#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char * argv[]) {

   QApplication a(argc, argv);
   MainWindow w;
   w.show();

   srand(time(nullptr));

   return a.exec();
}
