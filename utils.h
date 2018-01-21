#ifndef UTILS_H
#define UTILS_H

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

    static float distance(Vertex v1, Vertex v2);

    static std::vector<Triangle> createSquare(float el);
};

#endif // UTILS_H
