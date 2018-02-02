#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <vector>

#include "cell.h"
#include "triangle.h"
#include "vertex.h"

struct Facet {
    glm::vec3 normal;
    int vertex[3];
};

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
    static bool intersectRayTriangle(glm::vec3 v1, glm::vec3 v2, Triangle t);
    static bool checkTriangleBoxOverlap(Triangle t, glm::vec3 v1, glm::vec3 v2);

    static std::vector<Triangle> slice(std::vector<Triangle> t, float z, float thickness);
    static std::vector<Triangle> getTrianglesFromBox(std::vector<Triangle> t, float x, float y, float z, float thickness);

    static std::vector<Vertex> getVertexList(std::vector<Triangle> &t, std::vector<Facet> &f);


    static void offsetVertices(std::vector<Vertex> &v, std::vector<Facet> &f, float d);
private:
    static bool planeBoxOverlap(glm::vec3 normal, glm::vec3 vert, glm::vec3 maxbox);
};

/*======================== X-tests ========================*/

#define AXISTEST_X01(a, b, fa, fb) \
    p0 = a*v0.y - b*v0.z; \
    p2 = a*v2.y - b*v2.z; \
    if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * boxhalfsize.y + fb * boxhalfsize.z;   \
    if(min>rad || max<-rad) return false;

#define AXISTEST_X2(a, b, fa, fb)			   \
    p0 = a*v0.y - b*v0.z;			           \
    p1 = a*v1.y - b*v1.z;			       	   \
    if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize.y + fb * boxhalfsize.z;   \
    if(min>rad || max<-rad) return false;

/*======================== Y-tests ========================*/

#define AXISTEST_Y02(a, b, fa, fb)			   \
    p0 = -a*v0.x + b*v0.z;		      	   \
    p2 = -a*v2.x + b*v2.z;	       	       	   \
    if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * boxhalfsize.x + fb * boxhalfsize.z;   \
    if(min>rad || max<-rad) return false;

#define AXISTEST_Y1(a, b, fa, fb)			   \
    p0 = -a*v0.x + b*v0.z;		      	   \
    p1 = -a*v1.x + b*v1.z;	     	       	   \
    if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize.x + fb * boxhalfsize.z;   \
    if(min>rad || max<-rad) return false;

/*======================== Z-tests ========================*/
#define AXISTEST_Z12(a, b, fa, fb)			   \
    p1 = a*v1.x - b*v1.y;			           \
    p2 = a*v2.x - b*v2.y;			       	   \
    if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;} \
    rad = fa * boxhalfsize.x + fb * boxhalfsize.y;   \
    if(min>rad || max<-rad) return false;

#define AXISTEST_Z0(a, b, fa, fb)			   \
    p0 = a*v0.x - b*v0.y;				   \
    p1 = a*v1.x - b*v1.y;			           \
    if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize.x + fb * boxhalfsize.y;   \
    if(min>rad || max<-rad) return false;

#endif // UTILS_H
