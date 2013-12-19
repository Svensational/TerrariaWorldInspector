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
   // positions
   QLabel *  spawnPoint; //quint32
   QDoubleSpinBox * groundLevel;
   QDoubleSpinBox * rockLevel;
   QLabel *  treeX;
   QLabel *  caveBackX;
   QLabel * dungeonPoint;
   // styles
   QLabel *  treeStyle;
   QLabel *  caveBackStyle;
   QSpinBox * iceBackStyle;
   QSpinBox * jungleBackStyle;
   QSpinBox * hellBackStyle;
   //std::array<quint8, 8> styles;
   // stuff
   QCheckBox * isCrimson;
   //std::array<bool, 14> isDefeated;
   //std::array<bool, 3> isSaved;
   QCheckBox * isShadowOrbSmashed;
   QCheckBox * isMeteorSpawned;
   QSpinBox * numShadowOrbs;
   QSpinBox * altarCount;
   QCheckBox * isHardMode;
   QSpinBox * invasionDelay;
   QSpinBox * invasionSize;
   QSpinBox * invasionType;
   QDoubleSpinBox * invasionX;
   QSpinBox * oreTier1;
   QSpinBox * oreTier2;
   QSpinBox * oreTier3;

   void initGUI();

private slots:
   void update();
   void randomizeWorldID();
};

#endif // HEADERWIDGET_H
