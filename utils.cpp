#include "utils.h"
#include <algorithm>
#include <limits>
#include <array>
#include <iostream>
#include <cassert>
#include "math.h"
#include "glm/ext.hpp"

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

std::pair<std::array<float, 2>, std::array<float, 2>> Utils::getBoundaries(std::vector<Triangle> &t, float z, float thickness) {
    std::array<float, 2> minimum = {FLT_MAX, FLT_MAX};
    std::array<float, 2> maximum = {FLT_MIN, FLT_MIN};
    float pZ;

    for(int i = 0; i < 2; i++) {
        pZ = z + i*thickness;
        for(std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
            if(it->getMinZ() <= pZ && it->getMaxZ() >= pZ) {
                glm::vec3 v1 = it->getV1();
                glm::vec3 v2 = it->getV2();
                glm::vec3 v3 = it->getV3();
                glm::vec3 intersect1(0.0, 0.0, 0.0);
                glm::vec3 intersect2(0.0, 0.0, 0.0);
                int res1 = -1;
                int res2 = -1;
                if(v1.z <= pZ) {
                    if(v2.z <= pZ) { // just V3 is above the plane or the triangle is parallel to the plane
                        res1 = intersectRayPlane(v1, v3, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect1);
                        res2 = intersectRayPlane(v2, v3, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect2);
                    } else if(v3.z <= pZ) {  // just V2 is above the plane
                        res1 = intersectRayPlane(v1, v2, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect1);
                        res2 = intersectRayPlane(v3, v2, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect2);
                    } else {    // just V1 is under the plane
                        res1 = intersectRayPlane(v2, v1, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect1);
                        res2 = intersectRayPlane(v3, v1, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect2);
                    }
                } else if(v2.z <= pZ) {
                    if(v3.z <= pZ) { // just V1 is above the plane
                        res1 = intersectRayPlane(v2, v1, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect1);
                        res2 = intersectRayPlane(v3, v1, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect2);
                    } else { // just V2 is under the plane
                        res1 = intersectRayPlane(v1, v2, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect1);
                        res2 = intersectRayPlane(v3, v2, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect2);
                    }
                } else { // just V3 is under the plane
                    res1 = intersectRayPlane(v1, v3, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect1);
                    res2 = intersectRayPlane(v2, v3, glm::vec3(0.0, 0.0, pZ), glm::vec3(0.0, 0.0, 1.0), intersect2);
                }

//                assert(res1 != -1);
//                assert(res2 != -1);
//                assert(res1 != -2);
//                assert(res2 != -2);
                // TODO: fix a bug where res == -2 even with if(it->getMinZ() <= pZ && it->getMaxZ() >= pZ)
                if(res1 == 0) {  // Intersect the plane
                    minimum[0] = std::min(minimum[0], intersect1.x);
                    minimum[1] = std::min(minimum[1], intersect1.y);
                    maximum[0] = std::max(maximum[0], intersect1.x);
                    maximum[1] = std::max(maximum[1], intersect1.y);
                }
                if(res2 == 0) {  // Intersect the plane
                    minimum[0] = std::min(minimum[0], intersect2.x);
                    minimum[1] = std::min(minimum[1], intersect2.y);
                    maximum[0] = std::max(maximum[0], intersect2.x);
                    maximum[1] = std::max(maximum[1], intersect2.y);
                }
                if(res1 == 1 || res2 == 1) {
                    std::cout << "pararelo ao plano!\n";
                    minimum[0] = std::min(minimum[0], v1.x);
                    minimum[1] = std::min(minimum[1], v1.y);
                    maximum[0] = std::max(maximum[0], v1.x);
                    maximum[1] = std::max(maximum[1], v1.y);
                    minimum[0] = std::min(minimum[0], v2.x);
                    minimum[1] = std::min(minimum[1], v2.y);
                    maximum[0] = std::max(maximum[0], v2.x);
                    maximum[1] = std::max(maximum[1], v2.y);
                    minimum[0] = std::min(minimum[0], v3.x);
                    minimum[1] = std::min(minimum[1], v3.y);
                    maximum[0] = std::max(maximum[0], v3.x);
                    maximum[1] = std::max(maximum[1], v3.y);
                }
            }
        }
    }
    return std::pair<std::array<float, 2>, std::array<float, 2>>(minimum, maximum);
}

// Based on: http://geomalgorithms.com/a05-_intersect-1.html
int Utils::intersectRayPlane(glm::vec3 v1, glm::vec3 v2, glm::vec3 pPoint, glm::vec3 pNormal, glm::vec3 &intersect) {
    glm::vec3 u = v2-v1;

    float p = glm::dot(u, pNormal);
    if(p == 0) {    // Segment parallel to plane
        if(glm::dot(pNormal, v1 - pPoint) == 0) {
            return 1;   // Segment lies totally in the plane
        }
        return -1;  // Segment is parallel to plane but doesn't lies in the plane
    }

    glm::vec3 w = v1 - pPoint;
    float s = glm::dot(-pNormal, w)/p;

    if(s > 1 || s < 0)
        return -2;  // Segment doesn't intersect the plane

    intersect = v1 + s*u;
    return 0; // Segment intersect the plane
}
