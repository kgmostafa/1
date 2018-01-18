#ifndef VERTEX_H
#define VERTEX_H

#include <QString>

class Vertex
{
public:
    Vertex();
    Vertex(float x, float y, float z);

    void set(float x, float y, float z);

    float getX();
    float getY();
    float getZ();

    QString toString();
private:
    float _x, _y, _z;
};

#endif // VERTEX_H
