#include "vertex.h"

Vertex::Vertex() {
    this->set(0.0, 0.0, 0.0);
}

Vertex::Vertex(float x, float y, float z) {
    this->set(x, y, z);
}

void Vertex::set(float x, float y, float z) {
    this->_x = x;
    this->_y = y;
    this->_z = z;
}

float Vertex::getX() {
    return this->_x;
}

float Vertex::getY() {
    return this->_y;
}

float Vertex::getZ() {
    return this->_z;
}

QString Vertex::toString() {
    QString result;
    result += "(";
    result += QString::number(_x);
    result += ", ";
    result += QString::number(_y);
    result += ", ";
    result += QString::number(_z);
    result += ")";
    return result;
}
