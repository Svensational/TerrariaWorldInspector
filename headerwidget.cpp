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
   layout->addRow("Moon type", moonType);

   treeX = new QLabel();
   layout->addRow("TreeX", treeX);

   treeStyle = new QLabel;
   layout->addRow("Tree style", treeStyle);

   caveBackX = new QLabel;
   layout->addRow("Cave Back X", caveBackX);

   caveBackStyle = new QLabel;
   layout->addRow("Cave Back Style", caveBackStyle);

   iceBackStyle = new QSpinBox();
   layout->addRow("Ice back style", iceBackStyle);

   jungleBackStyle = new QSpinBox();
   layout->addRow("Jungle back style", jungleBackStyle);

   hellBackStyle = new QSpinBox();
   layout->addRow("Hell back style", hellBackStyle);

   spawnPoint = new QLabel; //quint32
   layout->addRow("Spawn point", spawnPoint);

   groundLevel = new QDoubleSpinBox;
   groundLevel->setRange(0.0, 2400.0);
   layout->addRow("Ground level", groundLevel);

   rockLevel = new QDoubleSpinBox;
   rockLevel->setRange(0.0, 2400.0);
   layout->addRow("Rock level", rockLevel);

   time = new QDoubleSpinBox;
   time->setRange(0.0, 90000.0);
   layout->addRow("Time", time);

   isDayTime = new QCheckBox;
   layout->addRow("Day time", isDayTime);

   moonPhase = new QSpinBox();
   layout->addRow("Moon phase", moonPhase);

   isBloodMoon = new QCheckBox;
   layout->addRow("Blood moon", isBloodMoon);

   isEclipse = new QCheckBox;
   layout->addRow("Eclipse", isEclipse);

   dungeonPoint = new QLabel;
   layout->addRow("Dungeon point", dungeonPoint);

   isCrimson = new QCheckBox;
   layout->addRow("Crimson", isCrimson);

   //std::array<bool, 14> isDefeated;
   //std::array<bool, 3> isSaved;

   isShadowOrbSmashed = new QCheckBox;
   layout->addRow("Shadow orb smashed", isShadowOrbSmashed);

   isMeteorSpawned = new QCheckBox;
   layout->addRow("Meteor spawned", isMeteorSpawned);

   numShadowOrbs = new QSpinBox();
   layout->addRow("Shadow orbs smashed", numShadowOrbs);

   altarCount = new QSpinBox();
   layout->addRow("Altars", altarCount);

   isHardMode = new QCheckBox;
   layout->addRow("Hard mode", isHardMode);

   invasionDelay = new QSpinBox();
   layout->addRow("Invasion delay", invasionDelay);

   invasionSize = new QSpinBox();
   layout->addRow("Invasion size", invasionSize);

   invasionType = new QSpinBox();
   layout->addRow("Invasion type", invasionType);

   invasionX = new QDoubleSpinBox;
   layout->addRow("Invasion X", invasionX);

   isRaining = new QCheckBox;
   layout->addRow("Raining", isRaining);

   rainTime = new QSpinBox();
   layout->addRow("Rain time", rainTime);

   maxRain = new QDoubleSpinBox;
   layout->addRow("Max rain", maxRain);

   oreTier1 = new QSpinBox();
   layout->addRow("Ore tier 1", oreTier1);

   oreTier2 = new QSpinBox();
   layout->addRow("Ore tier 2", oreTier2);

   oreTier3 = new QSpinBox();
   layout->addRow("Ore tier 3", oreTier3);

   //std::array<quint8, 8> styles;

   cloudsActive = new QSpinBox();
   layout->addRow("Clouds active", cloudsActive);

   numClouds = new QSpinBox();
   layout->addRow("Number of clouds", numClouds);

   windSpeed = new QDoubleSpinBox;
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
   time->setValue(header.time);
   isDayTime->setChecked(header.isDayTime);
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
