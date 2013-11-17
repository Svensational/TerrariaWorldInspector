#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QtWidgets/QWidget>

class QCheckBox;
class QDoubleSpinBox;
class QLabel;
class QLineEdit;
class QSpinBox;
class TWorld;

class HeaderWidget : public QWidget {

   Q_OBJECT

public:
   explicit HeaderWidget(TWorld * world, QWidget * parent = 0);

private:
   TWorld * world;

   QLabel * version;
   QLineEdit * worldName;
   QLabel * worldID;
   QLabel * worldBounds;
   QLabel * worldSize;
   QSpinBox * moonType;
   QLabel *  treeX;
   QLabel *  treeStyle;
   QLabel *  caveBackX;
   QLabel *  caveBackStyle;
   QSpinBox * iceBackStyle;
   QSpinBox * jungleBackStyle;
   QSpinBox * hellBackStyle;
   QLabel *  spawnPoint; //quint32
   QDoubleSpinBox * groundLevel;
   QDoubleSpinBox * rockLevel;
   QDoubleSpinBox * time;
   QCheckBox * isDayTime;
   QSpinBox * moonPhase;
   QCheckBox * isBloodMoon;
   QCheckBox * isEclipse;
   QLabel * dungeonPoint;
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
   QCheckBox * isRaining;
   QSpinBox * rainTime;
   QDoubleSpinBox * maxRain;
   QSpinBox * oreTier1;
   QSpinBox * oreTier2;
   QSpinBox * oreTier3;
   //std::array<quint8, 8> styles;
   QSpinBox * cloudsActive;
   QSpinBox * numClouds;
   QDoubleSpinBox * windSpeed;

   void initGUI();

private slots:
   void update();
};

#endif // HEADERWIDGET_H
