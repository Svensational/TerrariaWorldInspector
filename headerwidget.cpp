#include "headerwidget.h"
#include <QtWidgets>
#include "tworld.h"

HeaderWidget::HeaderWidget(TWorld * world, QWidget * parent) :
   QWidget(parent), world(world)
{
   initGUI();
   connect(world, &TWorld::loaded, this, &HeaderWidget::update);
}

void HeaderWidget::initGUI() {
   QFormLayout * layout = new QFormLayout();

   version = new QLabel();
   layout->addRow("Version", version);

   worldName = new QLineEdit();
   layout->addRow("Name", worldName);

   worldID = new QLabel();
   layout->addRow("ID", worldID);

   worldBounds = new QLabel();
   layout->addRow("Bounds", worldBounds);

   worldSize = new QLabel();
   layout->addRow("Size", worldSize);

   moonType = new QSpinBox();
   ///@todo determine amount of moon types
   layout->addRow("Moon type", moonType);

   treeX = new QLabel();
   layout->addRow("TreeX", treeX);

   treeStyle = new QLabel();
   layout->addRow("Tree style", treeStyle);

   caveBackX = new QLabel();
   layout->addRow("Cave Back X", caveBackX);

   caveBackStyle = new QLabel();
   layout->addRow("Cave Back Style", caveBackStyle);

   iceBackStyle = new QSpinBox();
   ///@todo determine amount of back styles
   layout->addRow("Ice back style", iceBackStyle);

   jungleBackStyle = new QSpinBox();
   ///@todo determine amount of back styles
   layout->addRow("Jungle back style", jungleBackStyle);

   hellBackStyle = new QSpinBox();
   ///@todo determine amount of back styles
   layout->addRow("Hell back style", hellBackStyle);

   spawnPoint = new QLabel(); //quint32
   layout->addRow("Spawn point", spawnPoint);

   groundLevel = new QDoubleSpinBox();
   groundLevel->setRange(0.0, 2400.0);
   layout->addRow("Ground level", groundLevel);

   rockLevel = new QDoubleSpinBox();
   rockLevel->setRange(0.0, 2400.0);
   layout->addRow("Rock level", rockLevel);

   time = new QTimeEdit();
   layout->addRow("Time", time);

   moonPhase = new QSpinBox();
   ///@todo determine amount of moon phases
   layout->addRow("Moon phase", moonPhase);

   isBloodMoon = new QCheckBox();
   layout->addRow("Blood moon", isBloodMoon);

   isEclipse = new QCheckBox();
   layout->addRow("Eclipse", isEclipse);

   dungeonPoint = new QLabel();
   layout->addRow("Dungeon point", dungeonPoint);

   isCrimson = new QCheckBox();
   layout->addRow("Crimson", isCrimson);

   //std::array<bool, 14> isDefeated;
   //std::array<bool, 3> isSaved;

   isShadowOrbSmashed = new QCheckBox();
   layout->addRow("Shadow Orb destroyed", isShadowOrbSmashed);

   isMeteorSpawned = new QCheckBox();
   layout->addRow("Meteor spawned", isMeteorSpawned);

   numShadowOrbs = new QSpinBox();
   numShadowOrbs->setRange(0, 50);
   layout->addRow("Shadow Orbs destroyed", numShadowOrbs);

   altarCount = new QSpinBox();
   altarCount->setRange(0, 50);
   layout->addRow("Altars destroyed", altarCount);

   isHardMode = new QCheckBox();
   layout->addRow("Hard mode", isHardMode);

   invasionDelay = new QSpinBox();
   ///@todo determin range
   layout->addRow("Invasion delay", invasionDelay);

   invasionSize = new QSpinBox();
   ///@todo determin range
   layout->addRow("Invasion size", invasionSize);

   invasionType = new QSpinBox();
   ///@todo determin range
   layout->addRow("Invasion type", invasionType);

   invasionX = new QDoubleSpinBox;
   invasionX->setRange(0, 8400);
   layout->addRow("Invasion X", invasionX);

   isRaining = new QCheckBox;
   layout->addRow("Raining", isRaining);

   rainTime = new QSpinBox();
   ///@todo determin range
   layout->addRow("Rain time", rainTime);

   maxRain = new QDoubleSpinBox();
   ///@todo determin range
   layout->addRow("Max rain", maxRain);

   oreTier1 = new QSpinBox();
   ///@todo determin range
   layout->addRow("Ore tier 1", oreTier1);

   oreTier2 = new QSpinBox();
   ///@todo determin range
   layout->addRow("Ore tier 2", oreTier2);

   oreTier3 = new QSpinBox();
   ///@todo determin range
   layout->addRow("Ore tier 3", oreTier3);

   //std::array<quint8, 8> styles;

   cloudsActive = new QSpinBox();
   ///@todo determin range
   layout->addRow("Clouds active", cloudsActive);

   numClouds = new QSpinBox();
   ///@todo determin range
   layout->addRow("Number of clouds", numClouds);

   windSpeed = new QDoubleSpinBox();
   ///@todo determin range
   windSpeed->setRange(-1.0, 1.0);
   windSpeed->setDecimals(5);
   layout->addRow("Wind speed", windSpeed);

   setLayout(layout);
}

void HeaderWidget::update() {
   TWorld::Header const & header = world->getHeader();

   version->setText(QString("%1").arg(header.version));
   worldName->setText(header.worldName);
   worldID->setText(QString("%1").arg(header.worldID));
   worldBounds->setText(QString("[%1..%2]x[%3..%4]").arg(header.worldBounds.left())
                                                    .arg(header.worldBounds.right())
                                                    .arg(header.worldBounds.top())
                                                    .arg(header.worldBounds.bottom()));
   worldSize->setText(QString("%1x%2").arg(header.worldSize.width())
                                      .arg(header.worldSize.height()));
   moonType->setValue(header.moonType);
   treeX->setText(QString("%1, %2, %3").arg(header.treeX[0])
                                       .arg(header.treeX[1])
                                       .arg(header.treeX[2]));
   treeStyle->setText(QString("%1, %2, %3, %4").arg(header.treeStyle[0])
                                               .arg(header.treeStyle[1])
                                               .arg(header.treeStyle[2])
                                               .arg(header.treeStyle[3]));
   caveBackX->setText(QString("%1, %2, %3").arg(header.caveBackX[0])
                                           .arg(header.caveBackX[1])
                                           .arg(header.caveBackX[2]));
   caveBackStyle->setText(QString("%1, %2, %3, %4").arg(header.caveBackStyle[0])
                                                   .arg(header.caveBackStyle[1])
                                                   .arg(header.caveBackStyle[2])
                                                   .arg(header.caveBackStyle[3]));
   iceBackStyle->setValue(header.iceBackStyle);
   jungleBackStyle->setValue(header.jungleBackStyle);
   hellBackStyle->setValue(header.hellBackStyle);
   spawnPoint->setText(QString("(%1 / %2)").arg(header.spawnPoint.x())
                                           .arg(header.spawnPoint.y()));
   groundLevel->setValue(header.groundLevel);
   rockLevel->setValue(header.rockLevel);

   if (header.isDayTime) {
      time->setTime(QTime(4, 30).addSecs(header.time));
   }
   else {
      time->setTime(QTime(19, 30).addSecs(header.time));
   }

   moonPhase->setValue(header.moonPhase);
   isBloodMoon->setChecked(header.isBloodMoon);
   isEclipse->setChecked(header.isEclipse);
   dungeonPoint->setText(QString("(%1 / %2)").arg(header.dungeonPoint.x())
                                             .arg(header.dungeonPoint.y()));
   isCrimson->setChecked(header.isCrimson);
   isShadowOrbSmashed->setChecked(header.isShadowOrbSmashed);
   isMeteorSpawned->setChecked(header.isMeteorSpawned);
   numShadowOrbs->setValue(header.numShadowOrbs);
   altarCount->setValue(header.altarCount);
   isHardMode->setChecked(header.isHardMode);
   invasionDelay->setValue(header.invasionDelay);
   invasionSize->setValue(header.invasionSize);
   invasionType->setValue(header.invasionType);
   invasionX->setValue(header.invasionX);
   isRaining->setChecked(header.isRaining);
   rainTime->setValue(header.rainTime);
   maxRain->setValue(header.maxRain);
   oreTier1->setValue(header.oreTier[0]);
   oreTier2->setValue(header.oreTier[1]);
   oreTier3->setValue(header.oreTier[2]);
   cloudsActive->setValue(header.cloudsActive);
   numClouds->setValue(header.numClouds);
   windSpeed->setValue(header.windSpeed);
}
