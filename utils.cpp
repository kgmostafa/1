#include "utils.h"
#include <algorithm>
#include <limits>
#include <array>
#include <iostream>
#include <cassert>
#include "math.h"
#include "glm/ext.hpp"

#include "cell.h"
#include "triangle.h"

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
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;

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

// WARNING: this function must be tested before being used again
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

bool Utils::intersectRayTriangle(glm::vec3 v1, glm::vec3 v2, Triangle t) {
    const float EPSILON = 0.0000001;
    glm::vec3 vertex0 = t.getV1();
    glm::vec3 vertex1 = t.getV2();
    glm::vec3 vertex2 = t.getV3();
    glm::vec3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = glm::cross((v2-v1), edge2);
    a = glm::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON) {
        return false;
    }
    f = 1/a;
    s = v1 - vertex0;
    u = f * (glm::dot(s, h));
    if (u < 0.0 || u > 1.0) {
        return false;
    }
    q = glm::cross(s, edge1);
    v = f * glm::dot((v2-v1), q);
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    // At this stage we can compute t to find out where the intersection point is on the line.
    float k = f * glm::dot(edge2, q);
    if (k > EPSILON) { // ray intersection
        return true;
    } else { // This means that there is a line intersection but not a ray intersection.
        return false;
    }
}

bool Utils::checkTriangleBoxOverlap(Triangle t, glm::vec3 b1, glm::vec3 b2) {
    /*    use separating axis theorem to test overlap between triangle and box */
    /*    need to test for overlap in these directions: */
    /*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */
    /*       we do not even need to test these) */
    /*    2) normal of the triangle */
    /*    3) crossproduct(edge from tri, {x,y,z}-directin) */
    /*       this gives 3x3=9 more tests */
    glm::vec3 v0, v1, v2;

    float min,max,p0,p1,p2,rad,fex,fey,fez;

    glm::vec3 normal, e0, e1, e2;

    /* This is the fastest branch on Sun */

    /* move everything so that the boxcenter is in (0,0,0) */
    glm::vec3 boxcenter = (b2 + b1) * 0.5;
    glm::vec3 boxhalfsize = (b2 - b1) * 0.5;

    v0 = t.getV1() - boxcenter;
    v1 = t.getV2() - boxcenter;
    v2 = t.getV3() - boxcenter;

    /* compute triangle edges */
    e0 = v1 - v0;
    e1 = v2 - v1;
    e2 = v0 - v2;

    /* Bullet 3:  */
    /*  test the 9 tests first (this was faster) */
    fex = fabsf(e0.x);
    fey = fabsf(e0.y);
    fez = fabsf(e0.z);
    AXISTEST_X01(e0.z, e0.y, fez, fey);
    AXISTEST_Y02(e0.z, e0.x, fez, fex);
    AXISTEST_Z12(e0.y, e0.x, fey, fex);

    fex = fabsf(e1.x);
    fey = fabsf(e1.y);
    fez = fabsf(e1.z);
    AXISTEST_X01(e1.z, e1.y, fez, fey);
    AXISTEST_Y02(e1.z, e1.x, fez, fex);
    AXISTEST_Z0(e1.y, e1.x, fey, fex);

    fex = fabsf(e2.x);
    fey = fabsf(e2.y);
    fez = fabsf(e2.z);
    AXISTEST_X2(e2.z, e2.y, fez, fey);
    AXISTEST_Y1(e2.z, e2.x, fez, fex);
    AXISTEST_Z12(e2.y, e2.x, fey, fex);

    /* Bullet 1: */
    /*  first test overlap in the {x,y,z}-directions */
    /*  find min, max of the triangle each direction, and test for overlap in */
    /*  that direction -- this is equivalent to testing a minimal AABB around */
    /*  the triangle against the AABB */

    /* test in X-direction */
    min = max = v0.x;
    if(v1.x<min) min=v1.x;
    if(v1.x>max) max=v1.x;
    if(v2.x<min) min=v2.x;
    if(v2.x>max) max=v2.x;
    if(min>boxhalfsize.x || max<-boxhalfsize.x) return false;

    /* test in Y-direction */
    min = max = v0.y;
    if(v1.y<min) min=v1.y;
    if(v1.y>max) max=v1.y;
    if(v2.y<min) min=v2.y;
    if(v2.y>max) max=v2.y;
    if(min>boxhalfsize.y || max<-boxhalfsize.y) return false;

    /* test in Z-direction */
    min = max = v0.z;
    if(v1.z<min) min=v1.z;
    if(v1.z>max) max=v1.z;
    if(v2.z<min) min=v2.z;
    if(v2.z>max) max=v2.z;
    if(min>boxhalfsize.z || max<-boxhalfsize.z) return false;

    /* Bullet 2: */
    /*  test if the box intersects the plane of the triangle */
    /*  compute plane equation of triangle: normal*x+d=0 */
    normal = glm::cross(e0, e1);

    // -NJMP- (line removed here)
    if(!planeBoxOverlap(normal,v0,boxhalfsize)) return false;	// -NJMP-

    return true;   /* box and triangle overlaps */
}

bool Utils::planeBoxOverlap(glm::vec3 normal, glm::vec3 vert, glm::vec3 maxbox) { // -NJMP-
    int q;
    glm::vec3 vmin,vmax;
    float v;
    for(q=0;q<=2;q++) {
        v=vert[q];					// -NJMP-
        if(normal[q]>0.0f) {
            vmin[q]=-maxbox[q] - v;	// -NJMP-
            vmax[q]= maxbox[q] - v;	// -NJMP-
        } else {
            vmin[q]= maxbox[q] - v;	// -NJMP-
            vmax[q]=-maxbox[q] - v;	// -NJMP-
        }
    }
    if(glm::dot(normal,vmin)>0.0f) return false;	// -NJMP-
    if(glm::dot(normal,vmax)>=0.0f) return true;	// -NJMP-
    return false;
}


// Return a list of Triangles that intersects the plane on z or z+thickness
std::vector<Triangle> Utils::slice(std::vector<Triangle> t, float z, float thickness) {
    t.erase(std::remove_if(t.begin(),
                           t.end(),
                           [z, thickness](Triangle aux) {
                               return !((aux.getMinZ() <= z &&
                                         aux.getMaxZ() >= z) ||
                                        (aux.getMinZ() >= z &&
                                         aux.getMaxZ() <= z+thickness) ||
                                        (aux.getMinZ() <= z+thickness &&
                                         aux.getMaxZ() >= z+thickness));
                           }),
            t.end());
    return t;
}

std::vector<Triangle> Utils::getTrianglesFromBox(std::vector<Triangle> t, float x, float y, float z, float thickness) {
    t.erase(std::remove_if(t.begin(),
                           t.end(),
                           [x, y, z, thickness](Triangle aux) {
                               return !(checkTriangleBoxOverlap(aux, glm::vec3(x, y, z), glm::vec3(x+thickness, y+thickness, z+thickness)));
                           }),
            t.end());
    return t;
}

std::vector<Vertex> Utils::getVertexList(std::vector<Triangle> &t, std::vector<Facet> &f) {
    std::vector<Vertex> v;
    Facet f_aux;

    for(std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        f_aux.normal = it->getNormal();

        std::vector<Vertex>::iterator v_it =  std::find(v.begin(), v.end(), it->getV1());
        if(v_it  == v.end()) {
            v.push_back(it->getV1());
            f_aux.vertex[0] = v.size() - 1;
        } else {
            f_aux.vertex[0] = v_it - v.begin();
        }
        std::cout << "f_aux.vertex[0] = " << f_aux.vertex[0] << std::endl;

        v_it =  std::find(v.begin(), v.end(), it->getV2());
        if(v_it  == v.end()) {
            v.push_back(it->getV2());
            f_aux.vertex[1] = v.size() - 1;
        } else {
            f_aux.vertex[1] = v_it - v.begin();
        }
        std::cout << "f_aux.vertex[1] = " << f_aux.vertex[1] << std::endl;

        v_it =  std::find(v.begin(), v.end(), it->getV3());
        if(v_it  == v.end()) {
            v.push_back(it->getV3());
            f_aux.vertex[2] = v.size() - 1;
        } else {
            f_aux.vertex[2] = v_it - v.begin();
        }
        std::cout << "f_aux.vertex[2] = " << f_aux.vertex[2] << std::endl;

        f.push_back(f_aux);
    }
    return v;
}


