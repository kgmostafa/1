#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <vector>

#include "cell.h"
#include "triangle.h"
#include "vertex.h"

class Utils
{
public:
    Utils();

    static void rotateX(std::vector<Triangle> &t, float angle);
    static void rotateY(std::vector<Triangle> &t, float angle);
    static void rotateZ(std::vector<Triangle> &t, float angle);
    static void translate(std::vector<Triangle> &t, float x, float y, float z);

    static void place(Cell &c, float x, float y, float z);

    static void shrink(Cell &c, float thickness);

    static float distance(Vertex v1, Vertex v2);

    static std::vector<Triangle> createSquare(float el);

    static bool insideTriangle(glm::vec3 p, Triangle t);

    static std::pair<std::array<float, 2>, std::array<float, 2>> getBoundaries(std::vector<Triangle> &t, float z, float thickness);
    static int intersectRayPlane(glm::vec3 v1, glm::vec3 v2, glm::vec3 pPoint, glm::vec3 pNormal, glm::vec3 &intersect);
};

#endif // UTILS_H
