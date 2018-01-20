#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/vec3.hpp>

#include <QString>

#include "vertex.h"

class Triangle
{
public:
    Triangle();
    Triangle(Vertex v1, Vertex v2, Vertex v3);
    Triangle(Vertex normal, Vertex v1, Vertex v2, Vertex v3);

    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void rotate(float angle, glm::vec3 normal);

    void set(Vertex v1, Vertex v2, Vertex v3);

    Vertex getNormal();
    glm::vec3 getV1();
    glm::vec3 getV2();
    glm::vec3 getV3();

    float getMinX();
    float getMaxX();
    float getMinY();
    float getMaxY();
    float getMinZ();
    float getMaxZ();


    QString toString();
private:
    Vertex _normal;
//    Vertex _v[3];
    glm::vec3 _vec[3];
};

#endif // TRIANGLE_H
