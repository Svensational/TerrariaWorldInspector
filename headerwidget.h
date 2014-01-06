#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QtWidgets/QWidget>

class QCheckBox;
class QDoubleSpinBox;
class QLabel;
class QLineEdit;
class QSpinBox;
class QTimeEdit;
class TWorld;

class HeaderWidget : public QWidget {

   Q_OBJECT

public:
   explicit HeaderWidget(TWorld * world, QWidget * parent = 0);

private:
   TWorld * world;
   // general information
   QLabel * version;
   QLineEdit * worldName;
   QSpinBox * worldID;
   QLabel * worldSize;
   // wheather and time
   QTimeEdit * time;
   QSpinBox * moonType;
   QSpinBox * moonPhase;
   QCheckBox * isBloodMoon;
   QCheckBox * isEclipse;
   QCheckBox * isRaining;
   QSpinBox * rainTime;
   QDoubleSpinBox * maxRain;
   QSpinBox * cloudsActive;
   QSpinBox * numClouds;
   QDoubleSpinBox * windSpeed;
   // styles
   QLabel *  treeStyle;
   QLabel *  caveBackStyle;
   QSpinBox * iceBackStyle;
   QSpinBox * jungleBackStyle;
   QSpinBox * hellBackStyle;
   QSpinBox * BgTree;
   QSpinBox * BgCorruption;
   QSpinBox * BgJungle;
   QSpinBox * BgSnow;
   QSpinBox * BgHallow;
   QSpinBox * BgCrimson;
   QSpinBox * BgDesert;
   QSpinBox * BgOcean;
   // flags and counts
   //std::array<bool, 14> isDefeated;
   //std::array<bool, 3> isSaved;
   QCheckBox * isShadowOrbSmashed;
   QCheckBox * isMeteorSpawned;
   QSpinBox * numShadowOrbs;
   QSpinBox * altarCount;
   QCheckBox * isHardMode;
   // invasion
   QSpinBox * invasionDelay;
   QSpinBox * invasionSize;
   QSpinBox * invasionType;
   QDoubleSpinBox * invasionX;

   void initGUI();

private slots:
   void update();
   void randomizeWorldID();
};

#endif // HEADERWIDGET_H
