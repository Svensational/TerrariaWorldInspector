#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class TWorld;

class MainWindow : public QMainWindow {

   Q_OBJECT

public:
   explicit MainWindow(QWidget * parent = 0);
   ~MainWindow();

private slots:
   void loadWorld();
   void saveWorldAs();

private:
   TWorld * world;
   QAction * saveAsAct;

   void initGUI();
   void createCentralWidget();
   void createMenu();
};

#endif // MAINWINDOW_H
