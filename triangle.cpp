#include <iostream>
#include <limits>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>

#include "triangle.h"

Triangle::Triangle() :
    _normalSet(false) {
    calculateMinMax();
}

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) :
    _normalSet(false) {
    // TODO: add v1, v2 and v3 verifications
    // TODO: calculate normal vector
    this->_vec[0] = v1;
    this->_vec[1] = v2;
    this->_vec[2] = v3;
    calculateMinMax();
}

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) :
    _normalSet(false) {
    this->_vec[0] = glm::vec3(v1.getX(), v1.getY(), v1.getZ());
    this->_vec[1] = glm::vec3(v2.getX(), v2.getY(), v2.getZ());
    this->_vec[2] = glm::vec3(v3.getX(), v3.getY(), v3.getZ());
    calculateMinMax();
}

Triangle::Triangle(Vertex normal, Vertex v1, Vertex v2, Vertex v3) :
    _normalSet(true) {
    // TODO: add v1, v2 and v3 verifications
    // TODO: check if this normal is correct
    this->_normal = glm::vec3(normal.getX(), normal.getY(), normal.getZ());;
    this->_vec[0] = glm::vec3(v1.getX(), v1.getY(), v1.getZ());
    this->_vec[1] = glm::vec3(v2.getX(), v2.getY(), v2.getZ());
    this->_vec[2] = glm::vec3(v3.getX(), v3.getY(), v3.getZ());
    calculateMinMax();
}

void Triangle::scale(float x, float y, float z) {
    for(int i = 0; i < 3; i++) {
        _vec[i].x *= x;
        _vec[i].y *= y;
        _vec[i].z *= z;
    }
    calculateMinMax();
}

void Triangle::translate(float x, float y, float z) {
    for(int i = 0; i < 3; i++) {
        _vec[i].x += x;
        _vec[i].y += y;
        _vec[i].z += z;
    }
    calculateMinMax();
}

void Triangle::rotateX(float angle) {
    rotate(angle, glm::vec3(1.0, 0.0, 0.0));
}

void Triangle::rotateY(float angle) {
    rotate(angle, glm::vec3(0.0, 1.0, 0.0));
}

void Triangle::rotateZ(float angle) {
    rotate(angle, glm::vec3(0.0, 0.0, 1.0));
}

void Triangle::rotate(float angle, glm::vec3 normal) {
    // translate to origin?
    glm::mat4 rotMatrix(1.0);
    rotMatrix = glm::rotate(rotMatrix, angle, normal);

    for(int i = 0; i < 3; i++) {
        glm::vec4 vec(_vec[i], 1.0);

        vec = rotMatrix * vec;

        _vec[i].x = vec.x;
        _vec[i].y = vec.y;
        _vec[i].z = vec.z;
    }
    // translate back to position?

    calculateMinMax();
}

void Triangle::calculateMinMax() {
    glm::vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
    glm::vec3 max(FLT_MIN, FLT_MIN, FLT_MIN);
    for(int i = 0; i < 3; i++) {
        // Check if is lower
        if(_vec[i].x < min.x) {
            min.x = _vec[i].x;
        }
        if(_vec[i].y < min.y) {
            min.y = _vec[i].y;
        }
        if(_vec[i].z < min.z) {
            min.z = _vec[i].z;
        }
        // Check if is higher
        if(_vec[i].x > max.x) {
            max.x = _vec[i].x;
        }
        if(_vec[i].y > max.y) {
            max.y = _vec[i].y;
        }
        if(_vec[i].z > max.z) {
            max.z = _vec[i].z;
        }
    }
    _min = min;
    _max = max;
}

void Triangle::set(Vertex v1, Vertex v2, Vertex v3) {
    _vec[0] = glm::vec3(v1.getX(), v1.getY(), v1.getZ());
    _vec[1] = glm::vec3(v2.getX(), v2.getY(), v2.getZ());
    _vec[2] = glm::vec3(v3.getX(), v3.getY(), v3.getZ());
    calculateMinMax();
}

glm::vec3 Triangle::getNormal() {
    if(_normalSet == false) {
        std::cout << "normalSet == false\n";
        _normal = glm::normalize(glm::cross(_vec[1]-_vec[0], _vec[2]-_vec[0]));
        _normalSet = true;
    }
    return _normal;
}

glm::vec3 Triangle::getV1() {
    return _vec[0];
}

glm::vec3 Triangle::getV2() {
    return _vec[1];
}

glm::vec3 Triangle::getV3() {
    return _vec[2];
}

glm::vec3 Triangle::getMin() {
    return _min;
}

glm::vec3 Triangle::getMax() {
    return _max;
}

float Triangle::getMinX() {
    return _min.x;
}

float Triangle::getMaxX() {
    return _max.x;
}

float Triangle::getMinY() {
    return _min.y;
}

float Triangle::getMaxY() {
    return _max.y;
}

float Triangle::getMinZ() {
    return _min.z;
}

float Triangle::getMaxZ() {
    return _max.z;
}

QString Triangle::toString() {
    QString result;
    result += "{";
    for(int i = 0; i < 3; i++) {
        result += QString::fromStdString(glm::to_string(_vec[i]));//.toString();
        result += "\n";
    }
    result += "}";
    return result;
}

