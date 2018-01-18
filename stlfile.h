#ifndef STLFILE_H
#define STLFILE_H

#include <vector>
#include <QFile>

#include "triangle.h"


class STLFile
{
public:
    STLFile(const QString &name);

    std::vector<Triangle> decode(qint32 &n);
    bool encode(QString h, std::vector<Triangle> &t);

    QString getHeader();

    float getMinY();
    float getMaxY();
    float getMinZ();
    float getMaxZ();

    float getMaxXLength();
    float getMaxYLength();
    float getMaxZLength();

private:
    bool open(bool read);
    bool save();

    QString _name;

    QFile *_file;

    QString _header;

    float _min[3];
    float _max[3];


};

#endif // STLFILE_H
