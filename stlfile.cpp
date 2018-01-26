#include "stlfile.h"

STLFile::STLFile(const QString &name) :
    _min(), _max() {
    _name = name;
    _file = new QFile(name);
}

bool STLFile::open(bool read) {
    if (!_file->open(read?QIODevice::ReadOnly:QIODevice::WriteOnly)) {
       return false;
    }
    return true;
}

bool STLFile::save() {
    return false;
}

std::vector<Triangle> STLFile::decode(qint32 &n) {
    if(this->open(true) == false) {
        n = -1; // Failed to open the file
        return std::vector<Triangle>();
    }

    std::vector<Triangle> t;

//    TODO: Check if QDataStream is more fast than QFile
    char first[80];
//    QDataStream in(&_file);
//    in.setVersion(QDataStream::Qt_4_5);
    _file->read(first, 80);
//    in.readRawData(first, 80);
//    in.readRawData(nTriangles, 4);
    _header = QString(first);
    _file->read(reinterpret_cast<char *>(&n), sizeof(n));

    for(int i = 0; i < n; i++) {
        Vertex v[4];
        for(int j = 0; j < 4; j++) {
            float x,y,z;
            _file->read(reinterpret_cast<char *>(&x), sizeof(x));
            _file->read(reinterpret_cast<char *>(&y), sizeof(y));
            _file->read(reinterpret_cast<char *>(&z), sizeof(z));
            v[j].set(x, y, z);

            if(j != 0) {
                if(x > _max[0]) {
                    _max[0] = x;
                } else if(x < _min[0]) {
                    _min[0] = x;
                }
                if(y > _max[1]) {
                    _max[1] = y;
                } else if(y < _min[1]) {
                    _min[1] = y;
                }
                if(z > _max[2]) {
                    _max[2] = z;
                } else if(z < _min[2]) {
                    _min[2] = z;
                }
            }
        }
        t.push_back(Triangle(v[0], v[1], v[2], v[3]));
        quint16 att;
        _file->read(reinterpret_cast<char *>(&att), sizeof(att));
    }
    return t;
}

bool STLFile::encode(QString h, std::vector<Triangle> &t) {
    if(this->open(false) == false) {
        return false;
    }

    // Write header
    QByteArray header = h.toLocal8Bit();
    _file->write(header);
    if(header.size() < 80) {
        char *fillHeader = (char *)calloc(80-header.size(), sizeof(char));
        _file->write(fillHeader, 80-header.size());
    }

    quint32 nTriangles = t.size();
    _file->write(reinterpret_cast<char *>(&nTriangles), sizeof(nTriangles));

    // Iterate through all triangles
    for (std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        Triangle aux = *it;
        float x, y, z;

        // Normal
        x = aux.getNormal().x;
        y = aux.getNormal().y;
        z = aux.getNormal().z;
        _file->write(reinterpret_cast<char *>(&x), sizeof(x));
        _file->write(reinterpret_cast<char *>(&y), sizeof(y));
        _file->write(reinterpret_cast<char *>(&z), sizeof(z));

        // Vertex 1
        x = aux.getV1().x;
        y = aux.getV1().y;
        z = aux.getV1().z;
        _file->write(reinterpret_cast<char *>(&x), sizeof(x));
        _file->write(reinterpret_cast<char *>(&y), sizeof(y));
        _file->write(reinterpret_cast<char *>(&z), sizeof(z));

        // Vertex 2
        x = aux.getV2().x;
        y = aux.getV2().y;
        z = aux.getV2().z;
        _file->write(reinterpret_cast<char *>(&x), sizeof(x));
        _file->write(reinterpret_cast<char *>(&y), sizeof(y));
        _file->write(reinterpret_cast<char *>(&z), sizeof(z));

        // Vertex 3
        x = aux.getV3().x;
        y = aux.getV3().y;
        z = aux.getV3().z;
        _file->write(reinterpret_cast<char *>(&x), sizeof(x));
        _file->write(reinterpret_cast<char *>(&y), sizeof(y));
        _file->write(reinterpret_cast<char *>(&z), sizeof(z));

        // Fill the attribute byte count with zeros
        quint16 att = 0;
        _file->write(reinterpret_cast<char *>(&att), sizeof(att));
    }

    _file->close();

    return true;
}

QString STLFile::getHeader() {
    return _header;
}

float STLFile::getMinY() {
    return _min[1];
}

float STLFile::getMaxY() {
    return _max[1];
}

float STLFile::getMinZ() {
    return _min[2];
}

float STLFile::getMaxZ() {
    return _max[2];
}

float STLFile::getMaxXLength() {
    return _max[0] - _min[0];
}

float STLFile::getMaxYLength() {
    return _max[1] - _min[1];
}

float STLFile::getMaxZLength() {
    return _max[2] - _min[2];
}

float STLFile::getMaxLength() {
    float maxLength = getMaxXLength();
    if(getMaxYLength() > maxLength)
        maxLength = getMaxYLength();
    if(getMaxZLength() > maxLength)
        maxLength = getMaxZLength();
    return maxLength;
}
