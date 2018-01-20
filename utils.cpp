#include "utils.h"
#include "math.h"

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

float Utils::distance(Vertex v1, Vertex v2)
{
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
