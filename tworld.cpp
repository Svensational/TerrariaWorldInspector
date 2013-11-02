#include "tworld.h"
#ifdef Q_OS_WIN
   #include <shlobj.h>
#endif
#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QDebug>

TWorld::TWorld() :
   valid(false)
{
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

   // load stuff
   header = readHeader(in);

   file.close();
   valid = true;
   return true;
}

void TWorld::read(QPoint & point, QDataStream & in) const {
   in >> point.rx();
   in >> point.ry();
}

void TWorld::read(QRect & rect, QDataStream & in) const {
   quint32 temp;
   in >> temp;
   rect.setLeft(temp);
   in >> temp;
   rect.setRight(temp);
   in >> temp;
   rect.setTop(temp);
   in >> temp;
   rect.setBottom(temp);
}

void TWorld::read(QSize & size, QDataStream & in) const {
   in >> size.rheight();
   in >> size.rwidth();
}

void TWorld::read(QString & string, QDataStream & in) const {
   string = QString("");
   quint8 nameLength;
   in >> nameLength;
   quint8 tempChar;
   for(quint8 i=0; i<nameLength; ++i) {
      in >> tempChar;
      string.append(QChar(tempChar));
   }
}

TWorld::Header TWorld::readHeader(QDataStream & in) const {
   Header header;

   in >> header.version;
   read(header.worldName, in);
   in >> header.worldID;
   read(header.worldBounds, in);
   read(header.worldSize, in);
   in >> header.moonType;
   for (int i=0; i<3; ++i)
      in >> header.treeX[i];
   for (int i=0; i<4; ++i)
      in >> header.treeStyle[i];
   for (int i=0; i<3; ++i)
      in >> header.caveBackX[i];
   for (int i=0; i<4; ++i)
      in >> header.caveBackStyle[i];
   in >> header.iceBackStyle;
   in >> header.jungleBackStyle;
   in >> header.hellBackStyle;
   read(header.spawnPoint, in);
   in >> header.groundLevel;
   in >> header.rockLevel;
   in >> header.time;
   in >> header.isDayTime;
   in >> header.moonPhase;
   in >> header.isBloodMoon;
   in >> header.isEclipse;
   read(header.dungeonPoint, in);
   in >> header.isCrimson;
   for (int i=0; i<10; ++i)
      in >> header.isDefeated[i];
   for (int i=0; i<3; ++i)
      in >> header.isSaved[i];
   for (int i=10; i<14; ++i)
      in >> header.isDefeated[i];
   in >> header.isShadowOrbSmashed;
   in >> header.isMeteorSpawned;
   in >> header.numShadowOrbs;
   in >> header.altarCount;
   in >> header.isHardMode;
   in >> header.invasionDelay;
   in >> header.invasionSize;
   in >> header.invasionType;
   in >> header.invasionX;
   in >> header.isRaining;
   in >> header.rainTime;
   in >> header.maxRain;
   for (int i=0; i<3; ++i)
      in >> header.oreTier[i];
   for (int i=0; i<8; ++i)
      in >> header.styles[i];
   in >> header.cloudsActive;
   in >> header.numClouds;
   in >> header.windSpeed;

   return header;
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
