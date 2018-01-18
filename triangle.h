#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"
#include <QString>

class Triangle
{
public:
    Triangle();
    Triangle(Vertex v1, Vertex v2, Vertex v3);
    Triangle(Vertex normal, Vertex v1, Vertex v2, Vertex v3);

    QString toString();

    void set(Vertex v1, Vertex v2, Vertex v3);

    Vertex getNormal();
    Vertex getV1();
    Vertex getV2();
    Vertex getV3();

    float getMinX();
    float getMaxX();
    float getMinY();
    float getMaxY();
    float getMinZ();
    float getMaxZ();
private:
    Vertex _normal;
    Vertex _v[3];
};

#endif // TRIANGLE_H
