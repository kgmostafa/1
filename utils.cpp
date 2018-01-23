#include "utils.h"
#include <limits>
#include <array>
#include "math.h"

#include "cell.h"

Utils::Utils() {

}

void Utils::rotateX(std::vector<Triangle> &t, float angle) {
    for (std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        it->rotateX(angle);
    }
}

void Utils::rotateY(std::vector<Triangle> &t, float angle) {
    for (std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        it->rotateY(angle);
    }
}

void Utils::rotateZ(std::vector<Triangle> &t, float angle) {
    for (std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        it->rotateZ(angle);
    }
}

void Utils::translate(std::vector<Triangle> &t, float x, float y, float z) {
    for (std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        it->translate(x, y, z);
    }
}

void Utils::place(Cell &c, float x, float y, float z) {
    // TODO: translate cell to origin first
    std::vector<Triangle> t = c.getFacets();
    for (std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        it->translate(x, y, z);
    }
}

float Utils::distance(Vertex v1, Vertex v2) {
    float dx = v1.getX() - v2.getX();
    float dy = v1.getY() - v2.getY();
    float dz = v1.getZ() - v2.getZ();

    float dist = sqrt(pow(dx, 2.0) + pow(dy, 2.0) + pow(dz, 2.0));

    return dist;
}

std::vector<Triangle> Utils::createSquare(float edgeLength) {
    std::vector<Triangle> t;

    Vertex v0(0.0, 0.0, 0.0);
    Vertex v1(edgeLength, 0.0, 0.0);
    Vertex v2(0.0, edgeLength, 0.0);
    Vertex v3(edgeLength, edgeLength, 0.0);

    Triangle f0(v0, v2, v1);
    Triangle f1(v1, v2, v3);

    t.push_back(f0);
    t.push_back(f1);

    return t;
}

// TODO: add reference to website that gives this pseudocode
bool Utils::insideTriangle(glm::vec3 p, Triangle t) {
    glm::vec3 A = t.getV1();
    glm::vec3 B = t.getV2();
    glm::vec3 C = t.getV3();

    // Compute vectors
    glm::vec3 v0 = C - A;
    glm::vec3 v1 = B - A;
    glm::vec3 v2 = p - A;

    // Compute dot products

    float dot00 = glm::dot(v0, v0);
    float dot01 = glm::dot(v0, v1);
    float dot02 = glm::dot(v0, v2);
    float dot11 = glm::dot(v1, v1);
    float dot12 = glm::dot(v1, v2);

    // Compute barycentric coordinates
    float invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in triangle
    return (u >= 0) && (v >= 0) && (u + v < 1);
}

std::pair<std::array<float, 2>, std::array<float, 2>> Utils::getBoundaries(std::vector<Triangle> &t, float z) {
    std::array<float, 2> min = {FLT_MAX, FLT_MAX};
    std::array<float, 2> max = {FLT_MIN, FLT_MIN};
    for (std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        if(it->getMinZ() <= z && it->getMaxZ() >= z) {
            if(it->getMinX() < min[0]) {
                min[0] = it->getMinX();
            }
            if(it->getMinY() < min[1]) {
                min[1] = it->getMinY();
            }
            if(it->getMaxX() > max[0]) {
                max[0] = it->getMaxX();
            }
            if(it->getMaxY() > max[1]) {
                max[1] = it->getMaxY();
            }
        }
    }
    return std::pair<std::array<float, 2>, std::array<float, 2>>(min, max);
}
