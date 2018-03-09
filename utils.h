#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <vector>

#include "cell.h"
#include "triangle.h"
#include "vertex.h"

extern "C"{
#include "3rd_party/cork/cork.h"
}

struct Facet {
    glm::vec3 normal;
    int vertex[3];
};

enum Unit { micrometre, millimetre, centimetre, metre, inch, foot };

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)
#define EPSILON std::numeric_limits<float>::epsilon()

class Utils
{
public:
    Utils();

    // General
    static float wedge(glm::vec2 a, glm::vec2 b);
    static float distance(Vertex v1, Vertex v2);
    static float distanceFromPlane(glm::vec3 point, glm::vec3 planePoint, glm::vec3 planeNormal);
    static bool isInsideMesh(std::vector<Triangle> &t, glm::vec3 cellP, bool slice);
    static int getCentroid(std::vector<glm::vec2> &contour, glm::vec2 &centroid);
    static int getCentroid(std::vector<Triangle> &t, glm::vec3 &centroid, float &volume);

    // Mesh manipulation
    static void rotateX(std::vector<Triangle> &t, float angle);
    static void rotateY(std::vector<Triangle> &t, float angle);
    static void rotateZ(std::vector<Triangle> &t, float angle);
    static void translate(std::vector<Triangle> &t, float x, float y, float z);

    // Cell manipulation
    static void place(Cell &c, float x, float y, float z);
    static void shrink(Cell &c, float thickness);

    // Intersection functions
    static int intersectLines(std::pair<glm::vec3, glm::vec3> s1, std::pair<glm::vec3, glm::vec3> s2, glm::vec3 &intersectionPoint);
    static int intersectRayPlane(glm::vec3 v1, glm::vec3 v2, glm::vec3 pPoint, glm::vec3 pNormal, glm::vec3 &intersect);
    static bool intersectRayTriangle(glm::vec3 origin, glm::vec3 dir, Triangle t, float &distance);
    static std::pair<glm::vec3, glm::vec3> intersectTrianglePlane(Triangle triangle, glm::vec3 planeP, glm::vec3 planeN);
    static bool checkTriangleBoxOverlap(Triangle t, glm::vec3 v1, glm::vec3 v2);
    static int intersectSegments2D(std::pair<glm::vec2, glm::vec2> segment1, std::pair<glm::vec2, glm::vec2> segment2, glm::vec2 &intersectionPoint);
    static int intersectSegments3D(std::pair<glm::vec3, glm::vec3> segment1, std::pair<glm::vec3, glm::vec3> segment2);
    static bool intersectSegmentPlane(glm::vec3 s1, glm::vec3 s2, glm::vec3 planePoint, glm::vec3 planeNormal, glm::vec3 &intersectionPoint);
    static bool insideTriangle(glm::vec3 p, Triangle t);
    static bool inSegment(glm::vec3 p, std::pair<glm::vec3, glm::vec3> s);

    // Slicing
    static std::vector<Triangle> slice(std::vector<Triangle> t, float z, float thickness);
    static std::vector<Triangle> getTrianglesFromBox(std::vector<Triangle> t, glm::vec3 pos, glm::vec3 size);
    static std::vector<std::pair<glm::vec3, glm::vec3>> getIntersectionSegments(std::vector<Triangle> &t, float z);

    // Offsetting
    static std::vector<Vertex> getVertexList(std::vector<Triangle> &t, std::vector<Facet> &f);
    static void offsetVertices(std::vector<Vertex> &v, std::vector<Facet> &f, float d);
    static std::vector<Triangle> getTriangleList(std::vector<Vertex> &v, std::vector<Facet> &f);
    static void switchNormal(std::vector<Triangle> &t);

    // Contour detection
    static std::vector<std::vector<glm::vec3>> connect(std::vector<std::pair<glm::vec3, glm::vec3>> &v);
    static void processContour(std::vector<std::pair<glm::vec3, glm::vec3>> &contour);
    static std::vector<std::vector<glm::vec3>> getContours(std::vector<std::pair<glm::vec3, glm::vec3> > &segments, float tolerance);
    static std::vector<glm::vec3> getContour(std::vector<std::pair<glm::vec3, glm::vec3> > &segments, std::vector<bool> &segmentsCheck, std::vector<glm::vec3> contour, float tolerance);
    static int getNearestSegment(std::vector<std::pair<glm::vec3, glm::vec3>> &segments, std::vector<bool> &segmentsCheck, glm::vec3 point, float tolerance);
    static std::vector<std::vector<glm::vec2>> convertContourTo2D(std::vector<std::vector<glm::vec3>> &contours);
    static std::vector<std::vector<glm::vec2>> splitLoopsFromContours2D(std::vector<std::vector<glm::vec2>> &contours);
    static std::vector<std::vector<glm::vec2>> splitLoopsFromContour2D(std::vector<glm::vec2> &contour);
    static std::pair<std::array<float, 2>, std::array<float, 2>> getBoundaries(std::vector<Triangle> &t, float z, float thickness);

    // Loops
    static void removeLoops2D(std::vector<Triangle> &t, float z, std::vector<std::vector<glm::vec2>> &contoursBase, std::vector<std::vector<glm::vec2>> &contoursOffset, float offset, float tolerance);
    static bool checkLoops(std::vector<std::vector<glm::vec3> > &contour);

    // Cutting/splitting methods
    // Split one mesh on the surface of another mesh
    static void split(std::vector<Triangle> &mesh, std::vector<Triangle> &cuttingSurface);

    // Others
    static std::vector<Triangle> createSquare(float el);
    static float getMinimumZ(std::vector<Vertex> &v);
    static float getMaximumZ(std::vector<Vertex> &v);

    static CorkTriMesh meshToCorkTriMesh(std::vector<Triangle> &t);
    static std::vector<Triangle> corkTriMeshToMesh(CorkTriMesh &c);

    // Boolean operations
    static int meshBooleanIntersect(std::vector<Triangle> &inA, std::vector<Triangle> &inB, std::vector<Triangle> &out);

private:
    static bool planeBoxOverlap(glm::vec3 normal, glm::vec3 vert, glm::vec3 maxbox);
};


#define PERP(u,v) u.x*v.y - u.y*v.x  // perp product  (2D)

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
