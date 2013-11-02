#ifndef TWORLD_H
#define TWORLD_H

#include <array>
#include <QtCore/QList>
#include <QtCore/QRect>
#include <QtCore/QString>

class TWorld {

   struct Header {
      quint32 version;
      QString worldName;
      quint32 worldID;
      QRect worldBounds; //quint32
      QSize worldSize; //quint32
      quint8 moonType;
      std::array<quint32, 3> treeX;
      std::array<quint32, 4> treeStyle;
      std::array<quint32, 3> caveBackX;
      std::array<quint32, 4> caveBackStyle;
      quint32 iceBackStyle;
      quint32 jungleBackStyle;
      quint32 hellBackStyle;
      QPoint spawnPoint; //quint32
      double groundLevel;
      double rockLevel;
      double time;
      bool isDayTime;
      quint32 moonPhase;
      bool isBloodMoon;
      bool isEclipse;
      QPoint dungeonPoint; //quint32
      bool isCrimson;
      std::array<bool, 14> isDefeated;
      std::array<bool, 3> isSaved;
      bool isShadowOrbSmashed;
      bool isMeteorSpawned;
      quint8 numShadowOrbs;
      quint32 altarCount;
      bool isHardMode;
      quint32 invasionDelay;
      quint32 invasionSize;
      quint32 invasionType;
      double invasionX;
      bool isRaining;
      bool rainTime;
      float maxRain;
      std::array<quint32, 3> oreTier;
      std::array<quint8, 8> styles;
      quint32 cloudsActive;
      quint16 numClouds;
      float windSpeed;
   };

public:
   TWorld();
   bool isValid() const;
   bool load(QString const & filename);
   bool save(QString const & filename);
   QString getName() const;

   static QString getFolderName();

private:
   bool valid;
   Header header;

   inline void read(QPoint & point, QDataStream & in) const;
   inline void read(QRect & rect, QDataStream & in) const;
   inline void read(QSize & size, QDataStream & in) const;
   inline void read(QString & string, QDataStream & in) const;
   Header readHeader(QDataStream & in) const;

   inline void write(QPoint const & point, QDataStream & out) const;
   inline void write(QRect const & rect, QDataStream & out) const;
   inline void write(QSize const & size, QDataStream & out) const;
   inline void write(QString const & string, QDataStream & out) const;
   void writeHeader(Header const & header, QDataStream & out) const;
};

#endif // TWORLD_H
