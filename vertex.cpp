#include "vertex.h"
#include "glm/ext.hpp"

Vertex::Vertex() :
    glm::vec3() {
    this->set(0.0, 0.0, 0.0);
}

Vertex::Vertex(glm::vec3 v) :
    glm::vec3(v) {
}

Vertex::Vertex(float x, float y, float z) :
    glm::vec3(x, y, z) {
}

void Vertex::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vertex::translate(float x, float y, float z) {
    this->x += x;
    this->y += y;
    this->z += z;
}

QString Vertex::toString() {
    QString result;
     result += "(";
     result += QString::number(x);
     result += ", ";
     result += QString::number(y);
     result += ", ";
     result += QString::number(z);
     result += ")";
     return result;
}

//bool Vertex::operator==(const Vertex &v) const {
//    return glm::all(glm::lessThan(glm::abs(*this-v), glm::vec3(std::numeric_limits<float>::epsilon())));
//}
