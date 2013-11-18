#include "tworld.h"
#ifdef Q_OS_WIN
   #include <shlobj.h>
#endif
#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QDebug>
#include <QImage>
#include "luts.h"

TWorld::Chest::Item::Item() :
   amount(0), id(0), modifierID(0)
{
}

TWorld::Chest::Chest() :
   isValid(false)
{
}

TWorld::Sign::Sign() :
   isValid(false)
{
}

TWorld::TWorld() :
   valid(false)
{
}

void TWorld::debugOutput() const {
   int i = 0;
   QImage image(header.worldSize, QImage::Format_ARGB32);
   image.fill(qRgb(0, 255, 0));
   foreach(Tile const & tile, tiles) {
      int max = i+tile.rle+1;
      for (; i<max; ++i) {
         if (tile.isActive) {
            image.setPixel(i/header.worldSize.height(), i%header.worldSize.height(), qRgb(255, 255, 255));
         }
         else {
            image.setPixel(i/header.worldSize.height(), i%header.worldSize.height(), qRgb(0, 0, 0));
         }
      }
   }
   image.save("debug.png");
}

QString TWorld::getFolderName() {
   QString folder;

#ifdef Q_OS_WIN
   WCHAR my_documents[MAX_PATH];
   if (SHGetFolderPathW(NULL, CSIDL_PERSONAL, NULL, 0, my_documents) == S_OK) {
      folder = QString::fromUtf16((const unsigned short *) my_documents) + "\\My Games\\Terraria\\Worlds";
   }
#endif

   return folder;
}

TWorld::Header const & TWorld::getHeader() const {
   return header;
}

QString TWorld::getName() const {
   if (isValid()) {
      return header.worldName;
   }
   else {
      return QString();
   }
}

bool TWorld::isValid() const {
   return valid;
}

bool TWorld::load(QString const & filename) {
   QFile file(filename);
   if (!file.open(QIODevice::ReadOnly)) {
      return false;
   }
   QDataStream in(&file);
   in.setByteOrder(QDataStream::LittleEndian);

   // load header
   header = readHeader(in);

   // load tiles
   tiles.clear();
   int i = 0;
   Tile tile;
   while (i < header.worldSize.width() * header.worldSize.height()) {
      tile = readTile(in);
      tiles << tile;
      i += tile.rle+1;
   }

   // load chests
   Chest chest;
   chests.clear();
   for (i=0; i<1000; ++i) {
      chest = readChest(in);
      if (chest.isValid) {
         chests << chest;
      }
   }

   // load signs
   Sign sign;
   signs.clear();
   for (i=0; i<1000; ++i) {
      sign = readSign(in);
      if (sign.isValid) {
         signs << sign;
      }
   }

   // load NPCs
   NPC npc = readNPC(in);
   npcs.clear();
   while (npc.isValid) {
      npcs << npc;
      npc = readNPC(in);
   }
   npcNames.clear();
   for (i=0; i<18; ++i) {
      npcNames << readString(in);
   }

   // validate
   if (!readBool(in) || readString(in)!=header.worldName || readUInt32(in)!=header.worldID) {
      qDebug() << "Failed!";
      //debugOutput();
   }

   file.close();
   emit loaded();
   return (valid = true);
}

bool TWorld::readBool(QDataStream & in) const {
   bool b;
   in >> b;
   return b;
}

TWorld::Chest TWorld::readChest(QDataStream & in) const {
   Chest chest;

   if ((chest.isValid = readBool(in))) {
      chest.position = readPoint(in);
      chest.items.resize(40);
      for (int i=0; i<40; ++i) {
         if ((chest.items[i].amount = readUInt16(in))) {
            chest.items[i].id = readUInt32(in);
            chest.items[i].modifierID = readUInt8(in);
         }
      }
   }

   return chest;
}

double TWorld::readDouble(QDataStream & in) const {
   float fp;
   // fu you, Qt>=4.6, fu you hard!
   in.setFloatingPointPrecision(QDataStream::DoublePrecision);
   in >> fp;
   return fp;
}

float TWorld::readFloat(QDataStream & in) const {
   float fp;
   // fu you, Qt>=4.6, fu you hard!
   in.setFloatingPointPrecision(QDataStream::SinglePrecision);
   in >> fp;
   return fp;
}

TWorld::Header TWorld::readHeader(QDataStream & in) const {
   Header header;

   header.version = readUInt32(in);
   header.worldName = readString(in);
   header.worldID = readUInt32(in);
   header.worldBounds = readRect(in);
   header.worldSize = readSize(in);
   header.moonType = readUInt8(in);
   for (int i=0; i<3; ++i)
      header.treeX[i] = readUInt32(in);
   for (int i=0; i<4; ++i)
      header.treeStyle[i] = readUInt32(in);
   for (int i=0; i<3; ++i)
      header.caveBackX[i] = readUInt32(in);
   for (int i=0; i<4; ++i)
      header.caveBackStyle[i] = readUInt32(in);
   header.iceBackStyle = readUInt32(in);
   header.jungleBackStyle = readUInt32(in);
   header.hellBackStyle = readUInt32(in);
   header.spawnPoint = readPoint(in);
   header.groundLevel = readDouble(in);
   header.rockLevel = readDouble(in);
   header.time = readDouble(in);
   header.isDayTime = readBool(in);
   header.moonPhase = readUInt32(in);
   header.isBloodMoon = readBool(in);
   header.isEclipse = readBool(in);
   header.dungeonPoint = readPoint(in);
   header.isCrimson = readBool(in);
   for (int i=0; i<10; ++i)
      header.isDefeated[i] = readBool(in);
   for (int i=0; i<3; ++i)
      header.isSaved[i] = readBool(in);
   for (int i=10; i<14; ++i)
      header.isDefeated[i] = readBool(in);
   header.isShadowOrbSmashed = readBool(in);
   header.isMeteorSpawned = readBool(in);
   header.numShadowOrbs = readUInt8(in);
   header.altarCount = readUInt32(in);
   header.isHardMode = readBool(in);
   header.invasionDelay = readUInt32(in);
   header.invasionSize = readUInt32(in);
   header.invasionType = readUInt32(in);
   header.invasionX = readDouble(in);
   header.isRaining = readBool(in);
   header.rainTime = readUInt32(in);
   header.maxRain = readFloat(in);
   for (int i=0; i<3; ++i)
      header.oreTier[i] = readUInt32(in);
   for (int i=0; i<8; ++i)
      header.styles[i] = readUInt8(in);
   header.cloudsActive = readUInt32(in);
   header.numClouds = readUInt16(in);
   header.windSpeed = readFloat(in);

   return header;
}

TWorld::NPC TWorld::readNPC(QDataStream & in) const {
   NPC npc;

   if ((npc.isValid = readBool(in))) {
      npc.job = readString(in);
      npc.position = readPointF(in);
      npc.isHomeless = readBool(in);
      npc.homePos = readPoint(in);
   }

   return npc;
}

QPoint TWorld::readPoint(QDataStream & in) const {
   int x, y;
   in >> x;
   in >> y;
   return QPoint(x, y);
}

QPointF TWorld::readPointF(QDataStream & in) const {
   return QPoint(readFloat(in), readFloat(in));
}

QRect TWorld::readRect(QDataStream & in) const {
   QRect rect;
   rect.setLeft(readUInt32(in));
   rect.setRight(readUInt32(in));
   rect.setTop(readUInt32(in));
   rect.setBottom(readUInt32(in));
   return rect;
}

TWorld::Sign TWorld::readSign(QDataStream & in) const {
   Sign sign;

   if ((sign.isValid = readBool(in))) {
      sign.text = readString(in);
      sign.position = readPoint(in);
   }

   return sign;
}

QSize TWorld::readSize(QDataStream & in) const {
   int width, height;
   // strange, but correct
   in >> height;
   in >> width;
   return QSize(width, height);
}

QString TWorld::readString(QDataStream & in) const {
   QString string("");
   const quint8 length = readUInt8(in);
   for(quint8 i=0; i<length; ++i) {
      string.append(QChar(readUInt8(in)));
   }
   return string;
}

TWorld::Tile TWorld::readTile(QDataStream & in) const {
   Tile tile;

   if ((tile.isActive = readBool(in))) {
      tile.tileType = readUInt8(in);
      if (tileLUT(tile.tileType).hasTexCoords) {
         tile.texU = readUInt16(in);
         tile.texV = readUInt16(in);
      }
      if ((tile.hasColor = readBool(in))) {
         tile.color = readUInt8(in);
      }
   }
   if ((tile.hasWall = readBool(in))) {
      tile.wallType = readUInt8(in);
      if ((tile.hasWallColor = readBool(in))) {
         tile.wallColor = readUInt8(in);
      }
   }
   if ((tile.hasLiquid = readBool(in))) {
      tile.liquidAmount = readUInt8(in);
      tile.liquidIsLava = readBool(in);
      tile.liquidIsHoney = readBool(in);
   }
   tile.hasWire1 = readBool(in);
   tile.hasWire2 = readBool(in);
   tile.hasWire3 = readBool(in);
   tile.isHalfBrick = readBool(in);
   tile.slope = readUInt8(in);
   tile.actuator = readBool(in);
   tile.inActive = readBool(in);
   tile.rle = readUInt16(in);

   return tile;
}

quint8 TWorld::readUInt8(QDataStream & in) const {
   quint8 i;
   in >> i;
   return i;
}

quint16 TWorld::readUInt16(QDataStream & in) const {
   quint16 i;
   in >> i;
   return i;
}

quint32 TWorld::readUInt32(QDataStream & in) const {
   quint32 i;
   in >> i;
   return i;
}

bool TWorld::save(QString const & filename) {
   QFile file(filename);
   if (!file.open(QIODevice::WriteOnly)) {
      return false;
   }
   QDataStream out(&file);
   out.setByteOrder(QDataStream::LittleEndian);

   // save stuff
   writeHeader(header, out);

   file.close();
   return true;
}

void TWorld::write(float const & fp, QDataStream & out) const {
   // fu you, Qt>=4.6, fu you hard!
   out.setFloatingPointPrecision(QDataStream::SinglePrecision);
   out << fp;
}

void TWorld::write(double const & fp, QDataStream & out) const {
   out.setFloatingPointPrecision(QDataStream::DoublePrecision);
   out << fp;
}

void TWorld::write(QPoint const & point, QDataStream & out) const {
   out << point.x();
   out << point.y();
}

void TWorld::write(QRect const & rect, QDataStream & out) const {
   out << rect.left();
   out << rect.right();
   out << rect.top();
   out << rect.bottom();
}

void TWorld::write(QSize const & size, QDataStream & out) const {
   out << size.height();
   out << size.width();
}

void TWorld::write(QString const & string, QDataStream & out) const {
   out << (quint8) string.length();
   for (int i=0; i<string.length(); ++i) {
      out << (quint8) string[i].unicode();
   }
}

void TWorld::writeHeader(Header const & header, QDataStream & out) const {
   out << header.version;
   write(header.worldName, out);
   out << header.worldID;
   write(header.worldBounds, out);
   write(header.worldSize, out);
   out << header.moonType;
   for (int i=0; i<3; ++i)
      out << header.treeX[i];
   for (int i=0; i<4; ++i)
      out << header.treeStyle[i];
   for (int i=0; i<3; ++i)
      out << header.caveBackX[i];
   for (int i=0; i<4; ++i)
      out << header.caveBackStyle[i];
   out << header.iceBackStyle;
   out << header.jungleBackStyle;
   out << header.hellBackStyle;
   write(header.spawnPoint, out);
   out << header.groundLevel;
   out << header.rockLevel;
   out << header.time;
   out << header.isDayTime;
   out << header.moonPhase;
   out << header.isBloodMoon;
   out << header.isEclipse;
   write(header.dungeonPoint, out);
   out << header.isCrimson;
   for (int i=0; i<10; ++i)
      out << header.isDefeated[i];
   for (int i=0; i<3; ++i)
      out << header.isSaved[i];
   for (int i=10; i<14; ++i)
      out << header.isDefeated[i];
   out << header.isShadowOrbSmashed;
   out << header.isMeteorSpawned;
   out << header.numShadowOrbs;
   out << header.altarCount;
   out << header.isHardMode;
   out << header.invasionDelay;
   out << header.invasionSize;
   out << header.invasionType;
   out << header.invasionX;
   out << header.isRaining;
   out << header.rainTime;
   out << header.maxRain;
   for (int i=0; i<3; ++i)
      out << header.oreTier[i];
   for (int i=0; i<8; ++i)
      out << header.styles[i];
   out << header.cloudsActive;
   out << header.numClouds;
   out << header.windSpeed;
}
