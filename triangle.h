#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/vec3.hpp>

#include <QString>

#include "vertex.h"

class Triangle
{
public:
    Triangle();
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    Triangle(Vertex v1, Vertex v2, Vertex v3);
    Triangle(Vertex normal, Vertex v1, Vertex v2, Vertex v3);

    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void rotate(float angle, glm::vec3 normal);

    void set(Vertex v1, Vertex v2, Vertex v3);

    glm::vec3 getNormal();
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
    glm::vec3 _normal;
    glm::vec3 _vec[3];

    bool _normalSet;
};

#endif // TRIANGLE_H
