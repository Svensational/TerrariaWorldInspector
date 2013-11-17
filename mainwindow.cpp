#include "mainwindow.h"
#include <QtWidgets>
#include "tworld.h"
#include "headerwidget.h"

MainWindow::MainWindow(QWidget * parent) :
   QMainWindow(parent)
{
   world = new TWorld();
   initGUI();
}

MainWindow::~MainWindow() {
   delete world;
}

void MainWindow::createCentralWidget() {
   QTabWidget * tabWidget = new QTabWidget();
   tabWidget->setIconSize(QSize(32, 32));

   QScrollArea * headerScroll = new QScrollArea();
   HeaderWidget * headerWidget = new HeaderWidget(world);
   headerScroll->setWidget(headerWidget);
   tabWidget->addTab(headerScroll, QIcon(":/icons/tree"), "Header");

   QWidget * tilesWidget = new QWidget();
   tabWidget->addTab(tilesWidget, QIcon(":/icons/tile"), "Tiles");

   QWidget * chestsWidget = new QWidget();
   tabWidget->addTab(chestsWidget, QIcon(":/icons/chest"), "Chests");

   setCentralWidget(tabWidget);
}

void MainWindow::initGUI() {
   createCentralWidget();

   QToolBar * toolbar = addToolBar(tr("Toolbar"));
   QAction * openAct = new QAction(tr("&Open map"), this);
   connect(openAct, &QAction::triggered, this, &MainWindow::loadMap);
   toolbar->addAction(openAct);

   saveAsAct = new QAction(tr("&Save map as"), this);
   saveAsAct->setDisabled(true);
   connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveMapAs);
   toolbar->addAction(saveAsAct);

   toolbar->addSeparator();

   setWindowTitle("Terraria World Inspector v0.9");
   //setWindowIcon(QIcon(":/items/48"));
}

void MainWindow::loadMap() {
   QString filename = QFileDialog::getOpenFileName(this, tr("Open map"), TWorld::getFolderName(), tr("Terraria worlds (*.wld);;Terraria world backups (*.wld.bak)"));
   if (filename.isNull()) {
      return;
   }
   if (world->load(filename)) {
      setWindowTitle(world->getName() + " - TWI v0.9");
      saveAsAct->setEnabled(true);
   }
}

void MainWindow::saveMapAs() {
   QString filename = QFileDialog::getSaveFileName(this, tr("Save map as..."), TWorld::getFolderName(), tr("Terraria worlds (*.wld)"));
   if (filename.isNull()) {
      return;
   }

   world->save(filename);
}
