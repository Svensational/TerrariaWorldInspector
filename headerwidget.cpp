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
   QFrame * line;
   QFormLayout * layout = new QFormLayout();

   QHBoxLayout * generalLayout = new QHBoxLayout();
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    generalLayout->addWidget(line);
    generalLayout->addWidget(new QLabel("<b>General</b>"));
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    generalLayout->addWidget(line);
   layout->addRow(generalLayout);

   version = new QLabel();
   layout->addRow("Version", version);

   worldName = new QLineEdit();
   layout->addRow("Name", worldName);

   QHBoxLayout * worldIDLayout = new QHBoxLayout();
    worldID = new QSpinBox();
     // QSpinBox can only hold signed integer values,
     // but I'm not shure whether world ID is unsigned or not :/
     worldID->setRange(0, INT_MAX);
    worldIDLayout->addWidget(worldID);
    QToolButton * worldIDBtn = new QToolButton();
     worldIDBtn->setIcon(QIcon(":/actions/refresh"));
     connect(worldIDBtn, &QToolButton::clicked, this, &HeaderWidget::randomizeWorldID);
    worldIDLayout->addWidget(worldIDBtn);
   layout->addRow("ID", worldIDLayout);

   worldSize = new QLabel();
   layout->addRow("Size", worldSize);


   QHBoxLayout * TimeWeatherLayout = new QHBoxLayout();
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    TimeWeatherLayout->addWidget(line);
    TimeWeatherLayout->addWidget(new QLabel("<b>Time & Weather</b>"));
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    TimeWeatherLayout->addWidget(line);
   layout->addRow(TimeWeatherLayout);

   time = new QTimeEdit();
   layout->addRow("Time", time);

   moonType = new QSpinBox();
   ///@todo determine amount of moon types
   layout->addRow("Moon type", moonType);

   moonPhase = new QSpinBox();
   ///@todo determine amount of moon phases
   layout->addRow("Moon phase", moonPhase);

   isBloodMoon = new QCheckBox();
   layout->addRow("Blood moon", isBloodMoon);

   isEclipse = new QCheckBox();
   layout->addRow("Eclipse", isEclipse);

   isRaining = new QCheckBox;
   layout->addRow("Raining", isRaining);

   rainTime = new QSpinBox();
   ///@todo determin range
   layout->addRow("Rain time", rainTime);

   maxRain = new QDoubleSpinBox();
   ///@todo determin range
   layout->addRow("Max rain", maxRain);

   cloudsActive = new QSpinBox();
   ///@todo determin range
   cloudsActive->setRange(0, INT_MAX);
   layout->addRow("Clouds active", cloudsActive);

   numClouds = new QSpinBox();
   ///@todo determin range
   numClouds->setRange(0, INT_MAX);
   layout->addRow("Number of clouds", numClouds);

   windSpeed = new QDoubleSpinBox();
   ///@todo determin range
   windSpeed->setRange(-1.0, 1.0);
   windSpeed->setDecimals(5);
   layout->addRow("Wind speed", windSpeed);


   QHBoxLayout * stylesLayout = new QHBoxLayout();
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    stylesLayout->addWidget(line);
    stylesLayout->addWidget(new QLabel("<b>Styles</b>"));
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    stylesLayout->addWidget(line);
   layout->addRow(stylesLayout);

   treeStyle = new QLabel();
   layout->addRow("Tree style", treeStyle);

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

   //std::array<quint8, 8> styles;
   BgTree = new QSpinBox();
   BgTree->setRange(0, 255);
   layout->addRow("BgTree", BgTree);

   BgCorruption = new QSpinBox();
   BgCorruption->setRange(0, 255);
   layout->addRow("BgCorruption", BgCorruption);

   BgJungle = new QSpinBox();
   BgJungle->setRange(0, 255);
   layout->addRow("BgJungle", BgJungle);

   BgSnow = new QSpinBox();
   BgSnow->setRange(0, 255);
   layout->addRow("BgSnow", BgSnow);

   BgHallow = new QSpinBox();
   BgHallow->setRange(0, 255);
   layout->addRow("BgHallow", BgHallow);

   BgCrimson = new QSpinBox();
   BgCrimson->setRange(0, 255);
   layout->addRow("BgCrimson", BgCrimson);

   BgDesert = new QSpinBox();
   BgDesert->setRange(0, 255);
   layout->addRow("BgDesert", BgDesert);

   BgOcean = new QSpinBox();
   BgOcean->setRange(0, 255);
   layout->addRow("BgOcean", BgOcean);


   QHBoxLayout * flagsLayout = new QHBoxLayout();
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    flagsLayout->addWidget(line);
    flagsLayout->addWidget(new QLabel("<b>Flags & Counts</b>"));
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    flagsLayout->addWidget(line);
   layout->addRow(flagsLayout);

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


   QHBoxLayout * invasionLayout = new QHBoxLayout();
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    invasionLayout->addWidget(line);
    invasionLayout->addWidget(new QLabel("<b>Invasion</b>"));
    line = new QFrame();
     line->setFrameStyle(QFrame::HLine | QFrame::Plain);
     line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    invasionLayout->addWidget(line);
   layout->addRow(invasionLayout);

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
   invasionX->setRange(0.0, 8400.0);
   layout->addRow("Invasion X", invasionX);

   setLayout(layout);
}

void HeaderWidget::randomizeWorldID() {
   // still smaller than INT_MAX
   worldID->setValue(rand()*rand());
}

void HeaderWidget::update() {
   TWorld::Header const & header = world->getHeader();

   version->setText(QString("%1").arg(header.version));
   worldName->setText(header.worldName);
   worldID->setValue(header.worldID);
   worldSize->setText(QString("%1x%2 blocks").arg(header.worldSize.width())
                                             .arg(header.worldSize.height()));
   moonType->setValue(header.moonType);
   treeStyle->setText(QString("%1, %2, %3, %4").arg(header.treeStyle[0])
                                               .arg(header.treeStyle[1])
                                               .arg(header.treeStyle[2])
                                               .arg(header.treeStyle[3]));
   caveBackStyle->setText(QString("%1, %2, %3, %4").arg(header.caveBackStyle[0])
                                                   .arg(header.caveBackStyle[1])
                                                   .arg(header.caveBackStyle[2])
                                                   .arg(header.caveBackStyle[3]));
   iceBackStyle->setValue(header.iceBackStyle);
   jungleBackStyle->setValue(header.jungleBackStyle);
   hellBackStyle->setValue(header.hellBackStyle);
   BgTree->setValue(header.styles[0]);
   BgCorruption->setValue(header.styles[1]);
   BgJungle->setValue(header.styles[2]);
   BgSnow->setValue(header.styles[3]);
   BgHallow->setValue(header.styles[4]);
   BgCrimson->setValue(header.styles[5]);
   BgDesert->setValue(header.styles[6]);
   BgOcean->setValue(header.styles[7]);


   if (header.isDayTime) {
      time->setTime(QTime(4, 30).addSecs(header.time));
   }
   else {
      time->setTime(QTime(19, 30).addSecs(header.time));
   }

   moonPhase->setValue(header.moonPhase);
   isBloodMoon->setChecked(header.isBloodMoon);
   isEclipse->setChecked(header.isEclipse);
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
   cloudsActive->setValue(header.cloudsActive);
   numClouds->setValue(header.numClouds);
   windSpeed->setValue(header.windSpeed);
}
