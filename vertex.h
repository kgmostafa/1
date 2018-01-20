#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <QString>

class Vertex
{
public:
    Vertex();
    Vertex(float x, float y, float z);


    void set(float x, float y, float z);
    void translate(float x, float y, float z);

    float getX();
    float getY();
    float getZ();

    QString toString();

    Vertex(glm::vec3& v){
              _x = v.x;
              _y = v.y;
              _z = v.z;
     }

     Vertex& operator= (glm::vec3& v){
              _x = v.x;
              _y = v.y;
              _z = v.z;
              return *this;
     }

private:
    float _x, _y, _z;
};

#endif // VERTEX_H
