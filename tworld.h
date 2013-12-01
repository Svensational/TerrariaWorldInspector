#ifndef TWORLD_H
#define TWORLD_H

#include <array>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QRect>
#include <QtCore/QString>
#include <QtCore/QVector>

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
      bool hasBlock;
       quint8 blockType;
        quint16 texU;
        quint16 texV;
       bool hasBlockColor;
        quint8 blockColor;
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
      quint8 slope;
      bool actuator;
      bool inActive;
      quint16 rle;
   };

   struct Chest {
      struct Item {
         quint16 amount;
          quint32 id;
          quint8 modifierID;
         Item();
      };

      bool isValid;
       QPoint position;
       QVector<Item> items;
      Chest();
   };

   struct Sign {
      bool isValid;
       QString text;
       QPoint position;
      Sign();
   };

   struct NPC {
      bool isValid;
       QString job;
       QPointF position;
       bool isHomeless;
       QPoint homePos;
   };

   TWorld();
   bool isValid() const;
   bool load(QString const & filename);
   bool save(QString const & filename);
   QString getName() const;
   Header const & getHeader() const;
   void convertBlocks(quint8 find, quint8 replace);

   static QString getFolderName();

signals:
   void loaded();

private:
   bool valid;
   Header header;
   QList<Tile> tiles;
   QList<Chest> chests;
   QList<Sign> signs;
   QList<NPC> npcs;
   QList<QString> npcNames;

   inline bool readBool(QDataStream & in) const;
   inline quint8 readUInt8(QDataStream & in) const;
   inline quint16 readUInt16(QDataStream & in) const;
   inline quint32 readUInt32(QDataStream & in) const;
   inline float readFloat(QDataStream & in) const;
   inline double readDouble(QDataStream & in) const;
   inline QPoint readPoint(QDataStream & in) const;
   inline QPointF readPointF(QDataStream & in) const;
   inline QSize readSize(QDataStream & in) const;
   inline QRect readRect(QDataStream & in) const;
   inline QString readString(QDataStream & in) const;
   Header readHeader(QDataStream & in) const;
   Tile readTile(QDataStream & in) const;
   Chest readChest(QDataStream & in) const;
   Sign readSign(QDataStream & in) const;
   NPC readNPC(QDataStream & in) const;

   inline void write(bool b, QDataStream & out) const;
   inline void write(quint8 i, QDataStream & out) const;
   inline void write(quint16 i, QDataStream & out) const;
   inline void write(quint32 i, QDataStream & out) const;
   inline void write(float fp, QDataStream & out) const;
   inline void write(double fp, QDataStream & out) const;
   inline void write(QPoint const & point, QDataStream & out) const;
   inline void write(QPointF const & point, QDataStream & out) const;
   inline void write(QSize const & size, QDataStream & out) const;
   inline void write(QRect const & rect, QDataStream & out) const;
   inline void write(QString const & string, QDataStream & out) const;
   void write(Header const & header, QDataStream & out) const;
   void write(Tile const & tile, QDataStream & out) const;
   void write(Chest const & chest, QDataStream & out) const;
   void write(Sign const & sign, QDataStream & out) const;
   void write(NPC const & npc, QDataStream & out) const;

   void debugOutput() const;
};

#endif // TWORLD_H
