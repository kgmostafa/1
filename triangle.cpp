#include "triangle.h"
#include <limits>

Triangle::Triangle() {
}


Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) {
    // TODO: add v1, v2 and v3 verifications
    // TODO: calculate normal vector
    this->_v[0] = v1;
    this->_v[1] = v2;
    this->_v[2] = v3;
}


Triangle::Triangle(Vertex normal, Vertex v1, Vertex v2, Vertex v3) {
    // TODO: add v1, v2 and v3 verifications
    // TODO: check if this normal is correct
    this->_normal = normal;
    this->_v[0] = v1;
    this->_v[1] = v2;
    this->_v[2] = v3;
}

QString Triangle::toString() {
    QString result;
    result += "{";
    for(int i = 0; i < 3; i++) {
        result += _v[i].toString();
        result += "\n";
    }
    result += "}";
    return result;
}

void Triangle::set(Vertex v1, Vertex v2, Vertex v3) {
    this->_v[0].set(v1.getX(), v1.getY(), v1.getZ());
    this->_v[1].set(v2.getX(), v2.getY(), v2.getZ());
    this->_v[2].set(v3.getX(), v3.getY(), v3.getZ());
}

Vertex Triangle::getNormal() {
    return this->_normal;
}

Vertex Triangle::getV1() {
    return this->_v[0];
}

Vertex Triangle::getV2() {
    return this->_v[1];
}


Vertex Triangle::getV3() {
    return this->_v[2];
}

float Triangle::getMinX() {
    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < 3; i++) {
        if(this->_v[i].getX() < min)
            min = this->_v[i].getX();
    }
    return min;
}

float Triangle::getMaxX() {
    float max = std::numeric_limits<float>::min();
    for(int i = 0; i < 3; i++) {
        if(this->_v[i].getX() > max)
            max = this->_v[i].getX();
    }
    return max;
}

float Triangle::getMinY() {
    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < 3; i++) {
        if(this->_v[i].getY() < min)
            min = this->_v[i].getY();
    }
    return min;
}

float Triangle::getMaxY() {
    float max = std::numeric_limits<float>::min();
    for(int i = 0; i < 3; i++) {
        if(this->_v[i].getY() > max)
            max = this->_v[i].getY();
    }
    return max;
}


float Triangle::getMinZ() {
    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < 3; i++) {
        if(this->_v[i].getZ() < min)
            min = this->_v[i].getZ();
    }
    return min;
}

float Triangle::getMaxZ() {
    float max = std::numeric_limits<float>::min();
    for(int i = 0; i < 3; i++) {
        if(this->_v[i].getZ() > max)
            max = this->_v[i].getZ();
    }
    return max;
}


