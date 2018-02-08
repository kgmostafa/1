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

// NOTE: This function don't check if the triangle isn't intersecting the plane (it just return the segment).
// The result must be a pair of points that defines a segment, if both points are the same, it's just a point.
std::pair<glm::vec3, glm::vec3> Utils::intersectTrianglePlane(Triangle triangle, glm::vec3 planeP, glm::vec3 planeN) {
    glm::vec3 intersectionPoint;
    std::pair<glm::vec3, glm::vec3> segment;
    bool second = false;
    if(Utils::intersectRayPlane(triangle.getV1(), triangle.getV2(), planeP, planeN, intersectionPoint) == 0) {
        segment.first = intersectionPoint;
        second = true;
    }
    if(Utils::intersectRayPlane(triangle.getV2(), triangle.getV3(), planeP, planeN, intersectionPoint) == 0) {
        if(second) {
            segment.second = intersectionPoint;
        } else {
            segment.first = intersectionPoint;
        }
    }
    if(Utils::intersectRayPlane(triangle.getV3(), triangle.getV1(), planeP, planeN, intersectionPoint) == 0) {
        segment.second = intersectionPoint;
    }
    return segment;
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

// inSegment(): determine if a point is inside a segment
//    Input:  a point P, and a collinear segment S
//    Return: 1 = P is inside S
//            0 = P is  not inside S
bool Utils::inSegment(glm::vec3 p, std::pair<glm::vec3, glm::vec3> s) {
    if (s.first.x != s.second.x) {    // S is not  vertical
        if (s.first.x <= p.x && p.x <= s.second.x)
            return true;
        if (s.first.x >= p.x && p.x >= s.second.x)
            return true;
    }
    else {    // S is vertical, so test y  coordinate
        if (s.first.y <= p.y && p.y <= s.second.y)
            return true;
        if (s.first.y >= p.y && p.y >= s.second.y)
            return true;
    }
    return false;
}
//===================================================================
// http://geomalgorithms.com/a05-_intersect-1.html#intersect2D_2Segments()
// TODO: add intersect point and endpoint
int Utils::intersectSegments(std::pair<glm::vec3, glm::vec3> s1, std::pair<glm::vec3, glm::vec3> s2) {
    // intersect2D_2Segments(): find the 2D intersection of 2 finite segments
    //    Input:  two finite segments S1 and S2
    //    Output: *I0 = intersect point (when it exists)
    //            *I1 =  endpoint of intersect segment [I0,I1] (when it exists)
    //    Return: 0=disjoint (no intersect)
    //            1=intersect  in unique point I0
    //            2=overlap  in segment from I0 to I1
    glm::vec3 u = s1.second - s1.first;
    glm::vec3 v = s2.second - s2.first;
    glm::vec3 w = s1.first - s2.first;
    float D = PERP(u,v);

    // test if  they are parallel (includes either being a point)
    if (fabs(D) < std::numeric_limits<float>::epsilon()) {           // S1 and S2 are parallel
        if (PERP(u,w) != 0 || PERP(v,w) != 0)  {
            return 0;                    // they are NOT collinear
        }
        // they are collinear or degenerate
        // check if they are degenerate  points
        float du = glm::dot(u,u);
        float dv = glm::dot(v,v);
        if (du==0 && dv==0) {            // both segments are points
            if (s1.first !=  s2.first)         // they are distinct  points
                 return 0;
            return 1;
        }
        if (du==0) {                     // S1 is a single point
            if (inSegment(s1.first, s2) == false)  // but is not in S2
                 return 0;
            return 1;
        }
        if (dv==0) {                     // S2 a single point
            if  (inSegment(s2.first, s1) == false)  // but is not in S1
                 return 0;
            return 1;
        }
        // they are collinear segments - get  overlap (or not)
        float t0, t1;                    // endpoints of S1 in eqn for S2
        glm::vec3 w2 = s1.second - s2.first;
        if (v.x != 0) {
                 t0 = w.x / v.x;
                 t1 = w2.x / v.x;
        }
        else {
                 t0 = w.y / v.y;
                 t1 = w2.y / v.y;
        }
        if (t0 > t1) {                   // must have t0 smaller than t1
                 float t=t0; t0=t1; t1=t;    // swap if not
        }
        if (t0 > 1 || t1 < 0) {
            return 0;      // NO overlap
        }
        t0 = t0<0? 0 : t0;               // clip to min 0
        t1 = t1>1? 1 : t1;               // clip to max 1
        if (t0 == t1) {                  // intersect is a point
//            *I0 = s2.first +  t0 * v;
            return 1;
        }

        // they overlap in a valid subsegment
//        *I0 = s2.first + t0 * v;
//        *I1 = s2.first + t1 * v;
        return 2;
    }
    // the segments are skew and may intersect in a point
    // get the intersect parameter for S1
    float     sI = PERP(v,w) / D;
    if (sI < 0 || sI > 1)                // no intersect with S1
        return 0;

    // get the intersect parameter for S2
    float     tI = PERP(u,w) / D;
    if (tI < 0 || tI > 1)                // no intersect with S2
        return 0;

//    *I0 = s1.first + sI * u;                // compute S1 intersect point
    return 1;
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

        v_it =  std::find(v.begin(), v.end(), it->getV2());
        if(v_it  == v.end()) {
            v.push_back(it->getV2());
            f_aux.vertex[1] = v.size() - 1;
        } else {
            f_aux.vertex[1] = v_it - v.begin();
        }

        v_it =  std::find(v.begin(), v.end(), it->getV3());
        if(v_it  == v.end()) {
            v.push_back(it->getV3());
            f_aux.vertex[2] = v.size() - 1;
        } else {
            f_aux.vertex[2] = v_it - v.begin();
        }

        f.push_back(f_aux);
    }
    return v;
}

// Bahattin  Koc, Yuan-Shin Lee (2001): Non-uniform offsettting and hollowing objects by using biarcs fitting for rapid protoyping processes
void Utils::offsetVertices(std::vector<Vertex> &v, std::vector<Facet> &f, float d) {
    for(int i = 0; i < v.size(); i++) {
        glm::vec3 normal;
        bool facet_check = false;
        for(int j = 0; j < f.size(); j++) {
            if(f.at(j).vertex[0] == i ||
               f.at(j).vertex[1] == i ||
               f.at(j).vertex[2] == i) {
                if(facet_check == false) {
                    facet_check = true;
                    normal = f.at(j).normal;
                    continue;
                }
                bool normal_check = false;
                for(int k = j-1; k >= 0; k--) {
                    if(f.at(k).vertex[0] == i ||
                       f.at(k).vertex[1] == i ||
                       f.at(k).vertex[2] == i) {
                        if(fabsf(glm::dot(f.at(j).normal, f.at(k).normal) - 1.0) < std::numeric_limits<float>::epsilon()) {
                            normal_check = true;
                            break;
                        }
                    }
                }
                if(normal_check == false) {
                    normal += f.at(j).normal;
                }
            }
        }
        normal =  glm::normalize(normal);
        v.at(i) += d * normal;
    }
}

std::vector<Triangle> Utils::getTriangleList(std::vector<Vertex> &v, std::vector<Facet> &f) {
    std::vector<Triangle> t;

    for(std::vector<Facet>::iterator it = f.begin() ; it != f.end(); ++it) {
        t.push_back(Triangle(it->normal, v.at(it->vertex[0]), v.at(it->vertex[1]), v.at(it->vertex[2])));
    }

    return t;
}

void Utils::switchNormal(std::vector<Triangle> &t) {
    for(std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        it->switchNormal();
    }
}

float Utils::getMinimumZ(std::vector<Vertex> &v) {
    float min = std::numeric_limits<float>::max();
    for(std::vector<Vertex>::iterator it = v.begin() ; it != v.end(); ++it) {
        if(it->z < min) {
            min = it->z;
        }
    }
    return min;
}

float Utils::getMaximumZ(std::vector<Vertex> &v) {
    float max = std::numeric_limits<float>::min();
    for(std::vector<Vertex>::iterator it = v.begin() ; it != v.end(); ++it) {
        if(it->z > max) {
            max = it->z;
        }
    }
    return max;
}

std::vector<std::pair<glm::vec3, glm::vec3>> Utils::getContours(std::vector<Triangle> &t, float z) {
    std::vector<std::pair<glm::vec3, glm::vec3>> result;
    for(std::vector<Triangle>::iterator it = t.begin(); it != t.end(); ++it) {
        if(it->getMinZ() <= z && it->getMaxZ() > z) {
            std::pair<glm::vec3, glm::vec3> tmp;
            tmp = intersectTrianglePlane(*it, glm::vec3(0.0, 0.0, z), glm::vec3(0.0, 0.0, 1.0));
            result.push_back(tmp);
        }
    }
    // TODO: remove duplicates
    return result;
}

std::vector<std::vector<glm::vec3>> Utils::connect(std::vector<std::pair<glm::vec3, glm::vec3>> &v) {
    std::vector<std::vector<glm::vec3>> result;

    std::vector<std::pair<glm::vec3, glm::vec3>> aux = v;

    int i = 0;
    bool exist = false;
    glm::vec3 dir;
    while(i < aux.size()) {
        // Check if point is alright on countours result vector
        for(std::vector<std::vector<glm::vec3>>::iterator it2 = result.begin(); it2 != result.end(); ++it2) {
            if(glm::distance(it2->back(), aux[i].first) < 0.00001) {  // Exists
                if(glm::length(glm::cross(dir, aux[i].second - it2->back())) < 0.00001) {
                    it2->pop_back();
                }
                dir = aux[i].second - it2->back();
                it2->push_back(aux[i].second);
                exist = true;
                break;
            } else if(glm::distance(it2->back(), aux[i].second) < 0.00001) {  // Exists
                if(glm::length(glm::cross(dir, aux[i].first - it2->back())) < 0.00001) {
                    it2->pop_back();
                }
                dir = aux[i].first - it2->back();
                it2->push_back(aux[i].first);
                exist = true;
                break;
            }
        }
        if(exist) {
            aux.erase(aux.begin() + i);
            i = 0;
            exist = false;
        } else {
            i++;
            if(i == aux.size() && aux.size() != 1) {
                std::vector<glm::vec3> tmp;
                tmp.push_back(aux[0].first);
                dir = aux[0].second - aux[0].first;
                result.push_back(tmp);
                aux.erase(aux.begin());
                i = 0;
            }
        }
    }

    // Remove remaining duplicates
    // TODO: improve the legibility of this piece of code
    for(std::vector<std::vector<glm::vec3>>::iterator it1 = result.begin(); it1 != result.end(); ++it1) {
        glm::vec3 v0 = it1->at(0);
        glm::vec3 v1 = it1->at(1);
        glm::vec3 vb0 = it1->back();
        glm::vec3 vb1 = *(it1->end()-2);
        if(glm::length(glm::cross(v1-v0, v0-vb0)) < 0.00001) {
            it1->erase(it1->begin());
        } else if(glm::length(glm::cross(v0-vb0, vb0-vb1)) < 0.00001) {
            it1->erase(it1->end());
        }
    }

    return result;
}

void Utils::getCrossSectionalContours(std::vector<Vertex> &v, std::vector<Facet> &f, float thickness) {
}

//void Utils::processContour(std::vector<std::pair<glm::vec3, glm::vec3> > &contour) {
//    for(std::vector<std::pair<glm::vec3, glm::vec3>>::iterator it1 = s.begin(); it1 != s.end(); ++it1) {
//        for(std::vector<std::pair<glm::vec3, glm::vec3>>::iterator it2 = it1; it2 != s.end(); ++it2) {
//            if(Utils::intersectSegments(*it1, *it2) == 2) {
//                return true;
//            }
//        }
//    }
//}

bool Utils::checkLoops(std::vector<std::pair<glm::vec3, glm::vec3> > &s)
{
    for(std::vector<std::pair<glm::vec3, glm::vec3>>::iterator it1 = s.begin(); it1 != s.end(); ++it1) {
        for(std::vector<std::pair<glm::vec3, glm::vec3>>::iterator it2 = it1; it2 != s.end(); ++it2) {
            if(Utils::intersectSegments(*it1, *it2) == 2) {
                return true;
            }
        }
    }
    return false;
}
