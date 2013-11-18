#include "tworld.h"
#ifdef Q_OS_WIN
   #include <shlobj.h>
#endif
#include <QtCore/QDataStream>
#include <QtCore/QFile>
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
      file.close();
      return (valid = false);
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
   QPoint point;
   point.setX(readFloat(in));
   point.setY(readFloat(in));
   return point;
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

   // write header
   write(header, out);

   // write tiles
   foreach(Tile const & tile, tiles) {
      write(tile, out);
   }

   // write chests
   foreach(Chest const & chest, chests) {
      write(chest, out);
   }
   for (int i=chests.size(); i<1000; ++i) {
      write(false, out);
   }

   // write signs
   foreach(Sign const & sign, signs) {
      write(sign, out);
   }
   for (int i=signs.size(); i<1000; ++i) {
      write(false, out);
   }

   // write NPCs
   foreach(NPC const & npc, npcs) {
      write(npc, out);
   }
   write(false, out);
   foreach(QString const & name, npcNames) {
      write(name, out);
   }

   // write file ending
   write(true, out);
   write(header.worldName, out);
   write(header.worldID, out);

   file.close();
   return true;
}

void TWorld::write(bool b, QDataStream & out) const {
   out << b;
}

void TWorld::write(Chest const & chest, QDataStream & out) const {
   write(chest.isValid, out);
   if (chest.isValid) {
      write(chest.position, out);
      foreach (Chest::Item const & item, chest.items) {
         write(item.amount, out);
         if (item.amount) {
            write(item.id, out);
            write(item.modifierID, out);
         }
      }
   }
}

void TWorld::write(double fp, QDataStream & out) const {
   out.setFloatingPointPrecision(QDataStream::DoublePrecision);
   out << fp;
}

void TWorld::write(float fp, QDataStream & out) const {
   // fu you, Qt>=4.6, fu you hard!
   out.setFloatingPointPrecision(QDataStream::SinglePrecision);
   out << fp;
}

void TWorld::write(Header const & header, QDataStream & out) const {
   write(header.version, out);
   write(header.worldName, out);
   write(header.worldID, out);
   write(header.worldBounds, out);
   write(header.worldSize, out);
   write(header.moonType, out);
   for (int i=0; i<3; ++i)
      write(header.treeX[i], out);
   for (int i=0; i<4; ++i)
      write(header.treeStyle[i], out);
   for (int i=0; i<3; ++i)
      write(header.caveBackX[i], out);
   for (int i=0; i<4; ++i)
      write(header.caveBackStyle[i], out);
   write(header.iceBackStyle, out);
   write(header.jungleBackStyle, out);
   write(header.hellBackStyle, out);
   write(header.spawnPoint, out);
   write(header.groundLevel, out);
   write(header.rockLevel, out);
   write(header.time, out);
   write(header.isDayTime, out);
   write(header.moonPhase, out);
   write(header.isBloodMoon, out);
   write(header.isEclipse, out);
   write(header.dungeonPoint, out);
   write(header.isCrimson, out);
   for (int i=0; i<10; ++i)
      write(header.isDefeated[i], out);
   for (int i=0; i<3; ++i)
      write(header.isSaved[i], out);
   for (int i=10; i<14; ++i)
      write(header.isDefeated[i], out);
   write(header.isShadowOrbSmashed, out);
   write(header.isMeteorSpawned, out);
   write(header.numShadowOrbs, out);
   write(header.altarCount, out);
   write(header.isHardMode, out);
   write(header.invasionDelay, out);
   write(header.invasionSize, out);
   write(header.invasionType, out);
   write(header.invasionX, out);
   write(header.isRaining, out);
   write(header.rainTime, out);
   write(header.maxRain, out);
   for (int i=0; i<3; ++i)
      write(header.oreTier[i], out);
   for (int i=0; i<8; ++i)
      write(header.styles[i], out);
   write(header.cloudsActive, out);
   write(header.numClouds, out);
   write(header.windSpeed, out);
}

void TWorld::write(NPC const & npc, QDataStream & out) const {
   write(npc.isValid, out);
   if (npc.isValid) {
      write(npc.job, out);
      write(npc.position, out);
      write(npc.isHomeless, out);
      write(npc.homePos, out);
   }
}

void TWorld::write(QPoint const & point, QDataStream & out) const {
   out << point.x();
   out << point.y();
}

void TWorld::write(QPointF const & point, QDataStream & out) const {
   out.setFloatingPointPrecision(QDataStream::SinglePrecision);
   out << point.x();
   out << point.y();
}

void TWorld::write(QRect const & rect, QDataStream & out) const {
   out << rect.left();
   out << rect.right();
   out << rect.top();
   out << rect.bottom();
}

void TWorld::write(Sign const & sign, QDataStream & out) const {
   write(sign.isValid, out);
   if (sign.isValid) {
      write(sign.text, out);
      write(sign.position, out);
   }
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

void TWorld::write(Tile const & tile, QDataStream & out) const {
   write(tile.isActive, out);
   if (tile.isActive) {
      write(tile.tileType, out);
      if (tileLUT(tile.tileType).hasTexCoords) {
         write(tile.texU, out);
         write(tile.texV, out);
      }
      write(tile.hasColor, out);
      if (tile.hasColor) {
         write(tile.color, out);
      }
   }
   write(tile.hasWall, out);
   if (tile.hasWall) {
      write(tile.wallType, out);
      write(tile.hasWallColor, out);
      if (tile.hasWallColor) {
         write(tile.wallColor, out);
      }
   }
   write(tile.hasLiquid, out);
   if (tile.hasLiquid) {
      write(tile.liquidAmount, out);
      write(tile.liquidIsLava, out);
      write(tile.liquidIsHoney, out);
   }
   write(tile.hasWire1, out);
   write(tile.hasWire2, out);
   write(tile.hasWire3, out);
   write(tile.isHalfBrick, out);
   write(tile.slope, out);
   write(tile.actuator, out);
   write(tile.inActive, out);
   write(tile.rle, out);
}

void TWorld::write(quint8 i, QDataStream & out) const {
   out << i;
}

void TWorld::write(quint16 i, QDataStream & out) const {
   out << i;
}

void TWorld::write(quint32 i, QDataStream & out) const {
   out << i;
}
