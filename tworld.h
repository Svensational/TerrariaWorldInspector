#ifndef TWORLD_H
#define TWORLD_H

#include <array>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QRect>
#include <QtCore/QString>

class TWorld : public QObject {

   Q_OBJECT

public:
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
      quint32 rainTime;
      float maxRain;
      std::array<quint32, 3> oreTier;
      std::array<quint8, 8> styles;
      quint32 cloudsActive;
      quint16 numClouds;
      float windSpeed;
   };

   struct Tile {
      bool isActive;
       quint8 tileType;
        quint16 texU;
        quint16 texV;
       bool hasColor;
        quint8 color;
      bool hasWall;
       quint8 wallType;
       bool hasWallColor;
        quint8 wallColor;
      bool hasLiquid;
       quint8 liquidAmount;
       bool liquidIsLava;
       bool liquidIsHoney;
      bool hasWire1;
      bool hasWire2;
      bool hasWire3;
      bool isHalfBrick;
      quint8 slope; //???
      bool actuator;
      bool inActive;
      quint16 rle;
   };

   TWorld();
   bool isValid() const;
   bool load(QString const & filename);
   bool save(QString const & filename);
   QString getName() const;

   static QString getFolderName();
   Header const & getHeader() const;

signals:
   void loaded();

private:
   bool valid;
   Header header;
   QList<Tile> tiles;


   inline void read(float & fp, QDataStream & in) const;
   inline void read(double & fp, QDataStream & in) const;
   inline void read(QPoint & point, QDataStream & in) const;
   inline void read(QRect & rect, QDataStream & in) const;
   inline void read(QSize & size, QDataStream & in) const;
   inline void read(QString & string, QDataStream & in) const;
   Header readHeader(QDataStream & in) const;
   Tile readTile(QDataStream & in) const;

   inline void write(float const & fp, QDataStream & out) const;
   inline void write(double const & fp, QDataStream & out) const;
   inline void write(QPoint const & point, QDataStream & out) const;
   inline void write(QRect const & rect, QDataStream & out) const;
   inline void write(QSize const & size, QDataStream & out) const;
   inline void write(QString const & string, QDataStream & out) const;
   void writeHeader(Header const & header, QDataStream & out) const;

   void debugOutput() const;
};

#endif // TWORLD_H
