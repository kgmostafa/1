#include "utils.h"
#include "math.h"
Utils::Utils()
{

}

float Utils::distance(Vertex v1, Vertex v2)
{
    float dx = v1.getX() - v2.getX();
    float dy = v1.getY() - v2.getY();
    float dz = v1.getZ() - v2.getZ();

    float dist = sqrt(pow(dx, 2.0) + pow(dy, 2.0) + pow(dz, 2.0));

    return dist;
}
