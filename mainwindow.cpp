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

void MainWindow::createMenu() {
   QMenu * worldMenu = menuBar()->addMenu(tr("&World"));

   QAction * openAct = new QAction(QIcon(":/actions/open"), tr("&Open"), this);
   openAct->setShortcut(Qt::CTRL + Qt::Key_O);
   connect(openAct, &QAction::triggered, this, &MainWindow::loadWorld);
   worldMenu->addAction(openAct);

   saveAsAct = new QAction(QIcon(":/actions/saveas"), tr("&Save as..."), this);
   saveAsAct->setShortcut(Qt::CTRL + Qt::Key_S);
   saveAsAct->setDisabled(true);
   connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveWorldAs);
   worldMenu->addAction(saveAsAct);

   worldMenu->addSeparator();

   QAction * quitAct = new QAction(tr("&Quit"), this);
   quitAct->setShortcut(Qt::CTRL + Qt::Key_Q);
   connect(quitAct, &QAction::triggered, this, &MainWindow::close);
   worldMenu->addAction(quitAct);


   QMenu * mapMenu = menuBar()->addMenu(tr("&Map"));

   mapMenu->addSeparator();
}

void MainWindow::initGUI() {
   createCentralWidget();
   createMenu();

   setWindowTitle("Terraria World Inspector v0.9");
   //setWindowIcon(QIcon(":/items/48"));
}

void MainWindow::loadWorld() {
   QString filename = QFileDialog::getOpenFileName(this, tr("Open world"), TWorld::getFolderName(), tr("Terraria worlds (*.wld);;Terraria world backups (*.wld.bak)"));
   if (filename.isNull()) {
      return;
   }
   if (world->load(filename)) {
      setWindowTitle(world->getName() + " - TWI v0.9");
      saveAsAct->setEnabled(true);
   }
}

void MainWindow::saveWorldAs() {
   QString filename = QFileDialog::getSaveFileName(this, tr("Save world as..."), TWorld::getFolderName(), tr("Terraria worlds (*.wld)"));
   if (filename.isNull()) {
      return;
   }

   world->save(filename);
}
