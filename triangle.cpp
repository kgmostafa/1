#include <limits>
#include <iostream>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>

#include "triangle.h"

Triangle::Triangle() {
}


Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
    // TODO: add v1, v2 and v3 verifications
    // TODO: calculate normal vector
    this->_vec[0] = v1;
    this->_vec[1] = v2;
    this->_vec[2] = v3;
}

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3) {
    this->_vec[0] = glm::vec3(v1.getX(), v1.getY(), v1.getZ());
    this->_vec[1] = glm::vec3(v2.getX(), v2.getY(), v2.getZ());
    this->_vec[2] = glm::vec3(v3.getX(), v3.getY(), v3.getZ());
}


Triangle::Triangle(Vertex normal, Vertex v1, Vertex v2, Vertex v3) {
    // TODO: add v1, v2 and v3 verifications
    // TODO: check if this normal is correct
    this->_normal = normal;
    this->_vec[0] = glm::vec3(v1.getX(), v1.getY(), v1.getZ());
    this->_vec[1] = glm::vec3(v2.getX(), v2.getY(), v2.getZ());
    this->_vec[2] = glm::vec3(v3.getX(), v3.getY(), v3.getZ());
}

void Triangle::scale(float x, float y, float z) {
    for(int i = 0; i < 3; i++) {
        _vec[i].x *= x;
        _vec[i].y *= y;
        _vec[i].z *= z;
    }
}

void Triangle::translate(float x, float y, float z) {
//    glm::mat4 traMatrix = glm::translate(glm::vec3(x, y, z));

//    glm::vec4 vec0(_vec[0], 1.0);
//    glm::vec4 vec1(_vec[0], 1.0);
//    glm::vec4 vec2(_vec[0], 1.0);

//    std::cout << glm::to_string(vec0) << std::endl;
//    vec0 = traMatrix*vec0;
//    vec1 = traMatrix*vec1;
//    vec2 = traMatrix*vec2;

//    _vec[0] = glm::vec3(vec0);
//    _vec[1] = glm::vec3(vec1);
//    _vec[2] = glm::vec3(vec2);

//    std::cout << glm::to_string(_vec[0]) << std::endl;
//    traMatrix =
    for(int i = 0; i < 3; i++) {
        _vec[i].x += x;
        _vec[i].y += y;
        _vec[i].z += z;

    }
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
//    std::cout << glm::to_string(rotMatrix) << std::endl;
    rotMatrix = glm::rotate(rotMatrix, angle, normal);

    for(int i = 0; i < 3; i++) {
        glm::vec4 vec(_vec[i], 1.0);

        vec = rotMatrix * vec;

        _vec[i].x = vec.x;
        _vec[i].y = vec.y;
        _vec[i].z = vec.z;
    }

    // translate back to position?
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

void Triangle::set(Vertex v1, Vertex v2, Vertex v3) {
    this->_vec[0] = glm::vec3(v1.getX(), v1.getY(), v1.getZ());
    this->_vec[1] = glm::vec3(v2.getX(), v2.getY(), v2.getZ());
    this->_vec[2] = glm::vec3(v3.getX(), v3.getY(), v3.getZ());
}

Vertex Triangle::getNormal() {
    return this->_normal;
}

glm::vec3 Triangle::getV1() {
    return this->_vec[0];
}

glm::vec3 Triangle::getV2() {
    return this->_vec[1];
}


glm::vec3 Triangle::getV3() {
    return this->_vec[2];
}

float Triangle::getMinX() {
    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < 3; i++) {
        if(this->_vec[i].x < min)
            min = this->_vec[i].x;
    }
    return min;
}

float Triangle::getMaxX() {
    float max = std::numeric_limits<float>::min();
    for(int i = 0; i < 3; i++) {
        if(this->_vec[i].x > max)
            max = this->_vec[i].x;
    }
    return max;
}

float Triangle::getMinY() {
    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < 3; i++) {
        if(this->_vec[i].y < min)
            min = this->_vec[i].y;
    }
    return min;
}

float Triangle::getMaxY() {
    float max = std::numeric_limits<float>::min();
    for(int i = 0; i < 3; i++) {
        if(this->_vec[i].y > max)
            max = this->_vec[i].y;
    }
    return max;
}


float Triangle::getMinZ() {
    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < 3; i++) {
        if(this->_vec[i].z < min)
            min = this->_vec[i].z;
    }
    return min;
}

float Triangle::getMaxZ() {
    float max = std::numeric_limits<float>::min();
    for(int i = 0; i < 3; i++) {
        if(this->_vec[i].z > max)
            max = this->_vec[i].z;
    }
    return max;
}


