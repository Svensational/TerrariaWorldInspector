#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "tworld.h"

class MainWindow : public QMainWindow {

   Q_OBJECT

public:
   explicit MainWindow(QWidget * parent = 0);
   ~MainWindow();

private slots:
   void loadMap();
   void saveMapAs();

private:
   TWorld world;
   QAction * saveAsAct;

   void initGUI();
};

#endif // MAINWINDOW_H