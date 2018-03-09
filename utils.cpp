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
#include <igl/copyleft/cork/from_cork_mesh.h>
#include <igl/copyleft/cork/to_cork_mesh.h>
#include <igl/copyleft/cgal/mesh_boolean.h>
#include <igl/copyleft/cork/mesh_boolean.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>

Utils::Utils() {

}

// http://mathworld.wolfram.com/WedgeProduct.html
float Utils::wedge(glm::vec2 a, glm::vec2 b)
{
    return a.x*b.y - a.y*b.x;
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

    Vertex v0(0.0f, 0.0f, 0.0f);
    Vertex v1(edgeLength, 0.0f, 0.0f);
    Vertex v2(0.0f, edgeLength, 0.0f);
    Vertex v3(edgeLength, edgeLength, 0.0f);

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
    float minFloat = std::numeric_limits<float>::lowest();
    float maxFloat = std::numeric_limits<float>::max();
    std::array<float, 2> minimum = {maxFloat, maxFloat};
    std::array<float, 2> maximum = {minFloat, minFloat};
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

int Utils::intersectLines(std::pair<glm::vec3, glm::vec3> s1, std::pair<glm::vec3, glm::vec3> s2, glm::vec3 &intersectionPoint)
{
    glm::vec3 v1 = s1.second - s1.first;
    glm::vec3 v2 = s2.first  - s1.first;
    glm::vec3 v3 = s2.second - s1.first;

    glm::vec3 u = s1.second - s1.first;
    glm::vec3 v = s2.second - s2.first;
    glm::vec3 w = s2.first  - s1.first;

    // Check if the lines are not coplanar
    if (fabsf(glm::dot(v1, glm::cross(v2, v3))) > std::numeric_limits<float>::epsilon()) {
        return 0;   // The lines do not intersect
    }

    // Check if the lines are parallel
    glm::vec3 paral = glm::cross(u, v);
    if(fabsf(paral.x) < std::numeric_limits<float>::epsilon() &&
       fabsf(paral.y) < std::numeric_limits<float>::epsilon() &&
       fabsf(paral.z) < std::numeric_limits<float>::epsilon()) {
        // Check if the lines are disjoint
        glm::vec3 disj = glm::cross(u, v);
        if(fabsf(disj.x) > std::numeric_limits<float>::epsilon() ||
           fabsf(disj.y) > std::numeric_limits<float>::epsilon() ||
           fabsf(disj.z) > std::numeric_limits<float>::epsilon()) {
            return 0;   // The lines do not intersect
        } else {
            intersectionPoint = glm::vec3(0.0);
            return 1;   // The lines are coincident
        }
    }

    // Get the intersection point
    float s = glm::dot(glm::cross(w, v), glm::cross(u, v)) / glm::dot(glm::cross(u, v), glm::cross(u, v));
    intersectionPoint = s1.first + (u * s);
    return 2;
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

// Möller–Trumbore intersection algorithm
bool Utils::intersectRayTriangle(glm::vec3 origin, glm::vec3 dir, Triangle t, float &distance)
{
    const float TOLERANCE = 0.0000001f;
    glm::vec3 vertex0 = t.getV1();
    glm::vec3 vertex1 = t.getV2();
    glm::vec3 vertex2 = t.getV3();
    glm::vec3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = glm::cross(dir, edge2);
    a = glm::dot(edge1, h);
    if (a > -TOLERANCE && a < TOLERANCE) {
        return false;
    }
    f = 1/a;
    s = origin - vertex0;
    u = f * (glm::dot(s, h));
    if (u < 0.0 || u > 1.0) {
        return false;
    }
    q = glm::cross(s, edge1);
    v = f * glm::dot(dir, q);
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    // At this stage we can compute t to find out where the intersection point is on the line.
    float dist = f * glm::dot(edge2, q);
    if (dist > TOLERANCE) { // ray intersection
        distance = dist;
        return true;
    } else { // This means that there is a line intersection but not a ray intersection.
        return false;
    }
}

float Utils::distanceFromPlane(glm::vec3 point, glm::vec3 planePoint, glm::vec3 planeNormal)
{
    planeNormal = glm::normalize(planeNormal);
    return glm::dot(planeNormal, point - planePoint);
}

bool Utils::intersectSegmentPlane(glm::vec3 s1, glm::vec3 s2, glm::vec3 planePoint, glm::vec3 planeNormal, glm::vec3 &intersectionPoint)
{
    float d1 = distanceFromPlane(s1, planePoint, planeNormal);
    float d2 = distanceFromPlane(s2, planePoint, planeNormal);

    // Check if s1 is in the plane
    if(fabsf(d1) < std::numeric_limits<float>::epsilon()) {
        intersectionPoint = s1;
        return true;
    }

    // Check if s2 is in the plane
    if(fabsf(d2) < std::numeric_limits<float>::epsilon()) {
        intersectionPoint = s2;
        return true;
    }

    // Check if points lie on the same side of plane
    if (d1*d2 > std::numeric_limits<float>::epsilon()) {
        return false;
    }

    // Get intersection point
    float t = d1 / (d1 - d2);
    intersectionPoint = s1 + (t * (s2 - s1));
    return true;
}

// NOTE: This function don't check if the triangle isn't intersecting the plane (it just return the segment).
// The result must be a pair of points that defines a segment, if both points are the same, it's just a point.
std::pair<glm::vec3, glm::vec3> Utils::intersectTrianglePlane(Triangle triangle, glm::vec3 planeP, glm::vec3 planeN)
{
    std::pair<glm::vec3, glm::vec3> segment;
    glm::vec3 intersection;
    // Check if V1 is on the plane
    if(fabsf(glm::dot(planeN, triangle.getV1()-planeP)) < EPSILON) {
        intersectSegmentPlane(triangle.getV1(), triangle.getV2(), planeP, planeN, intersection);
        segment.first = intersection;
        intersectSegmentPlane(triangle.getV2(), triangle.getV3(), planeP, planeN, intersection);
        segment.second = intersection;
        return segment;
    }

    // Check if V2 is on the plane
    if(fabsf(glm::dot(planeN, triangle.getV2()-planeP)) < EPSILON) {
        intersectSegmentPlane(triangle.getV2(), triangle.getV1(), planeP, planeN, intersection);
        segment.first = intersection;
        intersectSegmentPlane(triangle.getV1(), triangle.getV3(), planeP, planeN, intersection);
        segment.second = intersection;
        return segment;
    }

    // Check if V3 is on the plane
    if(fabsf(glm::dot(planeN, triangle.getV3()-planeP)) < EPSILON) {
        std::cout << "V3 is over the plane\n";
        intersectSegmentPlane(triangle.getV3(), triangle.getV1(), planeP, planeN, intersection);
        segment.first = intersection;
        intersectSegmentPlane(triangle.getV1(), triangle.getV2(), planeP, planeN, intersection);
        segment.second = intersection;
        return segment;
    }

    // None of the triangle vertex are on the plane: get the segment by trial and error
    bool second = false;
    if(intersectSegmentPlane(triangle.getV1(), triangle.getV2(), planeP, planeN, intersection)) {
        segment.first = intersection;
        second = true;
    }

    if(intersectSegmentPlane(triangle.getV2(), triangle.getV3(), planeP, planeN, intersection)) {
        if(second) {
            segment.second = intersection;
            return segment;
        } else {
            segment.first = intersection;
            second = true;
        }
    }

    if(intersectSegmentPlane(triangle.getV3(), triangle.getV1(), planeP, planeN, intersection)) {
        segment.second = intersection;
    }

    assert(second == true);
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

/* Check if two segments intersect.
 * Return:  0 - the segments do not intersect
 *          1 - the segments are collinear and overlapping (multiple intersection points)
 *          2 - the segments have a single point of intersection
 * Based on: https://www.codeproject.com/Tips/862988/Find-the-Intersection-Point-of-Two-Line-Segments
 */
int Utils::intersectSegments2D(std::pair<glm::vec2, glm::vec2> segment1, std::pair<glm::vec2, glm::vec2> segment2, glm::vec2 &intersectionPoint)
{
    glm::vec2 r = segment1.second - segment1.first;
    glm::vec2 s = segment2.second - segment2.first;
    glm::vec2 t = segment2.first  - segment1.first;
    float rs = wedge(r, s);
    float tr = wedge(t, r);

    // If r^s = 0 and (s21 - s11)^r = 0, then the two lines are collinear.
    if(fabsf(rs) < EPSILON && fabsf(tr) < EPSILON) {
        // 1. If either  0 <= (s21 - s11).r <= r.r or 0 <= (s11 - s21).s <= s.s
        // then the two lines are overlapping,
        if ((0 <= glm::dot(segment2.first - segment1.first, r) && glm::dot(segment2.first - segment1.first, r) <= glm::dot(r, r)) ||
            (0 <= glm::dot(segment1.first - segment2.first, s) && glm::dot(segment1.first - segment2.first, s) <= glm::dot(s, s))) {
            return 1;
        }

        // 2. If neither 0 <= (s21 - s11).r ≤ r.r nor 0 <= (s11 - s21).s <= s.s
        // then the two lines are collinear but disjoint.
        // No need to implement this expression, as it follows from the expression above.
        return 0;
    }

    // 3. If r^s = 0 and (s21 - s11).r != 0, then the two lines are parallel and non-intersecting.
    if (fabsf(rs) < EPSILON && fabsf(tr) >= EPSILON) {
        return 0;
    }

    // u = (s21 - s11)^s / (r^s)
    float u = wedge(segment2.first - segment1.first, s) / rs;
    // v = (s21 - s11)^r / (r^s)
    float v = wedge(segment2.first - segment1.first, r) / rs;

    // 4. If r^s != 0 and 0 <= u <= 1 and 0 <= v <= 1
    // the two line segments meet at the point s11 + u*r = s21 + v*s.
    if (fabsf(rs) >= EPSILON && (0 <= u && u <= 1) && (0 <= v && v <= 1)) {
        // We can calculate the intersection point using either u or v.
        intersectionPoint = segment1.first + u * r;

        // An intersection was found.
        return 2;
    }

    // 5. Otherwise, the two line segments are not parallel but do not intersect.
    return 0;
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
int Utils::intersectSegments3D(std::pair<glm::vec3, glm::vec3> segment1, std::pair<glm::vec3, glm::vec3> segment2) {
    // intersect2D_2Segments(): find the 2D intersection of 2 finite segments
    //    Input:  two finite segments S1 and S2
    //    Output: *I0 = intersect point (when it exists)
    //            *I1 =  endpoint of intersect segment [I0,I1] (when it exists)
    //    Return: 0=disjoint (no intersect)
    //            1=intersect  in unique point I0
    //            2=overlap  in segment from I0 to I1
    glm::vec3 u = segment1.second - segment1.first;
    glm::vec3 v = segment2.second - segment2.first;
    glm::vec3 w = segment1.first - segment2.first;
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
            if (segment1.first !=  segment2.first)         // they are distinct  points
                 return 0;
            return 1;
        }
        if (du==0) {                     // S1 is a single point
            if (inSegment(segment1.first, segment2) == false)  // but is not in S2
                 return 0;
            return 1;
        }
        if (dv==0) {                     // S2 a single point
            if  (inSegment(segment2.first, segment1) == false)  // but is not in S1
                 return 0;
            return 1;
        }
        // they are collinear segments - get  overlap (or not)
        float t0, t1;                    // endpoints of S1 in eqn for S2
        glm::vec3 w2 = segment1.second - segment2.first;
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

std::vector<Triangle> Utils::getTrianglesFromBox(std::vector<Triangle> t, glm::vec3 pos, glm::vec3 size) {
    t.erase(std::remove_if(t.begin(),
                           t.end(),
                           [pos, size](Triangle aux) {
                               return !(checkTriangleBoxOverlap(aux, pos, pos+size));
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
            f_aux.vertex[0] = (int)v.size() - 1;
        } else {
            f_aux.vertex[0] = v_it - v.begin();
        }

        v_it =  std::find(v.begin(), v.end(), it->getV2());
        if(v_it  == v.end()) {
            v.push_back(it->getV2());
            f_aux.vertex[1] = (int)v.size() - 1;
        } else {
            f_aux.vertex[1] = v_it - v.begin();
        }

        v_it =  std::find(v.begin(), v.end(), it->getV3());
        if(v_it  == v.end()) {
            v.push_back(it->getV3());
            f_aux.vertex[2] = (int)v.size() - 1;
        } else {
            f_aux.vertex[2] = v_it - v.begin();
        }

        f.push_back(f_aux);
    }
    return v;
}

// Bahattin  Koc, Yuan-Shin Lee (2002): Non-uniform offsettting and hollowing objects by using biarcs fitting for rapid protoyping processes
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
    float max = std::numeric_limits<float>::lowest();
    for(std::vector<Vertex>::iterator it = v.begin() ; it != v.end(); ++it) {
        if(it->z > max) {
            max = it->z;
        }
    }
    return max;
}

CorkTriMesh Utils::meshToCorkTriMesh(std::vector<Triangle> &t)
{
    CorkTriMesh cork;
    std::vector<Facet> facets;
    std::vector<Vertex> vertices;
    vertices = getVertexList(t, facets);
    cork.n_vertices = vertices.size();
    cork.n_triangles = facets.size();
    cork.triangles = new uint[(cork.n_triangles) * 3];
    cork.vertices  = new float[(cork.n_vertices) * 3];
    int i = 0;
    for(std::vector<Facet>::iterator it = facets.begin(); it != facets.end(); ++it) {
        cork.triangles[i*3] = it->vertex[0];
        cork.triangles[i*3 + 1] = it->vertex[1];
        cork.triangles[i*3 + 2] = it->vertex[2];
        i++;
    }

    i = 0;
    for(std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        cork.vertices[i*3] = it->x;
        cork.vertices[i*3 + 1] = it->y;
        cork.vertices[i*3 + 2] = it->z;
        i++;
    }

    return cork;
}

std::vector<Triangle> Utils::corkTriMeshToMesh(CorkTriMesh &c)
{
    std::vector<Facet> facets;
    std::vector<Vertex> vertices;

    int i;
    for(i = 0; i < c.n_vertices; i++) {
        float x = c.vertices[i*3];
        float y = c.vertices[i*3 + 1];
        float z = c.vertices[i*3 + 2];
        Vertex v(x, y, z);
        vertices.push_back(v);
    }

    for(i = 0; i < c.n_triangles; i++) {
        Facet f;
        f.vertex[0] = c.triangles[i*3];
        f.vertex[1] = c.triangles[i*3 + 1];
        f.vertex[2] = c.triangles[i*3 + 2];
        facets.push_back(f);
    }

    return getTriangleList(vertices, facets);
}

// TODO: handle and return errors
int Utils::meshBooleanIntersect(std::vector<Triangle> &inA, std::vector<Triangle> &inB, std::vector<Triangle> &out)
{
    Eigen::MatrixXd vInputA;
    Eigen::MatrixXi fInputA;
    Eigen::MatrixXd vInputB;
    Eigen::MatrixXi fInputB;
    Eigen::MatrixXd vOutput;
    Eigen::MatrixXi fOutput;

    CorkTriMesh corkA = Utils::meshToCorkTriMesh(inA);
    CorkTriMesh corkB = Utils::meshToCorkTriMesh(inB);
    CorkTriMesh corkOut;

    igl::copyleft::cork::from_cork_mesh(corkA, vInputA, fInputA);
    igl::copyleft::cork::from_cork_mesh(corkB, vInputB, fInputB);
    igl::copyleft::cgal::mesh_boolean(vInputA, fInputA, vInputB, fInputB, igl::MESH_BOOLEAN_TYPE_INTERSECT, vOutput, fOutput);
    igl::copyleft::cork::to_cork_mesh(vOutput, fOutput, corkOut);

    out = Utils::corkTriMeshToMesh(corkOut);

    return 0;
}

// TODO: Check this function result
std::vector<std::pair<glm::vec3, glm::vec3>> Utils::getIntersectionSegments(std::vector<Triangle> &t, float z) {
    std::vector<std::pair<glm::vec3, glm::vec3>> result;
    for(std::vector<Triangle>::iterator it = t.begin(); it != t.end(); ++it) {
        if(it->getMinZ() <= z + EPSILON && it->getMaxZ() >= z - EPSILON) {
            std::pair<glm::vec3, glm::vec3> tmp;
            tmp = intersectTrianglePlane(*it, glm::vec3(0.0, 0.0, z), glm::vec3(0.0, 0.0, 1.0));

            // Add only segments
            if((fabsf(tmp.first.x - tmp.second.x) < std::numeric_limits<float>::epsilon() &&
               fabsf(tmp.first.y - tmp.second.y) < std::numeric_limits<float>::epsilon() &&
               fabsf(tmp.first.z - tmp.second.z) < std::numeric_limits<float>::epsilon()) == false) {
                // Check if can be a duplicate
                bool checkDuplicate = false;
                if(fabsf(it->getV1().z - z) <= EPSILON) {
                    if(fabsf(it->getV2().z - z) <= EPSILON) {
                        checkDuplicate = true;
                    } else if(fabsf(it->getV3().z - z) <= EPSILON) {
                        checkDuplicate = true;
                    }
                } else if(fabsf(it->getV2().z - z) <= EPSILON) {
                    if(fabsf(it->getV3().z - z) <= EPSILON) {
                        checkDuplicate = true;
                    }
                }

                if(checkDuplicate) {
                    if(std::find_if(result.begin(), result.end(),
                       [tmp](std::pair<glm::vec3, glm::vec3> seg) {
                        if(fabsf(tmp.first.x - seg.first.x) <= EPSILON &&
                           fabsf(tmp.first.y - seg.first.y) <= EPSILON &&
                           fabsf(tmp.first.z - seg.first.z) <= EPSILON) {
                            if(fabsf(tmp.second.x - seg.second.x) <= EPSILON &&
                               fabsf(tmp.second.y - seg.second.y) <= EPSILON &&
                               fabsf(tmp.second.z - seg.second.z) <= EPSILON) {
                            return true;
                            }
                        } else if(fabsf(tmp.first.x - seg.second.x) <= EPSILON &&
                                  fabsf(tmp.first.y - seg.second.y) <= EPSILON &&
                                  fabsf(tmp.first.z - seg.second.z) <= EPSILON) {
                            if(fabsf(tmp.second.x - seg.first.x) <= EPSILON &&
                               fabsf(tmp.second.y - seg.first.y) <= EPSILON &&
                               fabsf(tmp.second.z - seg.first.z) <= EPSILON) {
                            return true;
                            }
                        }
                        return false;
                    }) == result.end()) {
                        result.push_back(tmp);
                    }
                } else {
                    result.push_back(tmp);
                }
            }
        }
    }
    return result;
}

// Unknown behavior: when the function tries to connect a contour that have an loop and
// the vertex is intersecting at the loop (4 segments sharing the same vertex, instead of 2)
std::vector<std::vector<glm::vec3>> Utils::connect(std::vector<std::pair<glm::vec3, glm::vec3>> &v) {
    std::vector<std::vector<glm::vec3>> result;

    std::vector<std::pair<glm::vec3, glm::vec3>> aux = v;

    int i = 0;
    bool exist = false;
    glm::vec3 dir;
    while(i < aux.size()) {
        std::cout << i << std::endl;
        // Check if point is alright on countours result vector
        for(std::vector<std::vector<glm::vec3>>::iterator it2 = result.begin(); it2 != result.end(); ++it2) {
            std::cout << "it2\n";
//            std::cout << "distance 1: " << glm::distance(it2->back(), aux[i].first) << std::endl <<
//                         "distance 2: " << glm::distance(it2->back(), aux[i].second) << std::endl;
            if(glm::distance(it2->back(), aux[i].first) < 0.001) {  // Exists
                std::cout << "exists\n";
//                if(glm::length(glm::cross(dir, aux[i].second - it2->back())) < 0.00001) {
//                    std::cout << "trying to pop_back\n";
//                    it2->pop_back();
//                }
//                dir = aux[i].second - it2->back();
                it2->push_back(aux[i].second);
                exist = true;
                break;
            } else if(glm::distance(it2->back(), aux[i].second) < 0.001) {  // Exists
                std::cout << "exists\n";
//                if(glm::length(glm::cross(dir, aux[i].first - it2->back())) < 0.00001) {
//                    std::cout << "trying to pop_back\n";
//                    it2->pop_back();
//                }
//                dir = aux[i].first - it2->back();
                it2->push_back(aux[i].first);
                exist = true;
                break;
            }
        }
        if(exist) {

            std::cout << "trying to erase\n";
            aux.erase(aux.begin() + i);
            i = 0;
            exist = false;
        } else {
            i++;

            std::cout << "i++\n";
            if(i == aux.size() && aux.size() != 1) {
                std::cout << "auxsize\n";
                std::vector<glm::vec3> tmp;
                tmp.push_back(aux[0].first);
                dir = aux[0].second - aux[0].first;
                result.push_back(tmp);
                aux.erase(aux.begin());
                i = 0;
            }
        }
    }

    std::cout << "post-processing\n";

    std::cout << "result.size(): " << result.size() << "\n";

    std::cout << "v.size(): " << v.size() << "\n";
    // Remove remaining duplicates
    // TODO: improve the legibility of this piece of code
    for(std::vector<std::vector<glm::vec3>>::iterator it1 = result.begin(); it1 != result.end(); ++it1) {

        std::cout << "it1.size:" << it1->size() << "\n";
    }
//        glm::vec3 v0 = it1->at(0);
//        glm::vec3 v1 = it1->at(1);
//        glm::vec3 vb0 = it1->back();
//        glm::vec3 vb1 = *(it1->end()-2);
//        if(glm::length(glm::cross(v1-v0, v0-vb0)) < 0.00001) {
//            it1->erase(it1->begin());
//        } else if(glm::length(glm::cross(v0-vb0, vb0-vb1)) < 0.00001) {
//            it1->erase(it1->end());
//        }
//    }

    return result;
}

std::vector<std::vector<glm::vec3> > Utils::getContours(std::vector<std::pair<glm::vec3, glm::vec3> > &segments, float tolerance)
{
    std::vector<std::vector<glm::vec3>> contours;
    std::vector<bool> segmentsCheck;
    for(int i = 0; i < segments.size(); i++) {
        segmentsCheck.push_back(false);
    }

    for(int i = 0; i < segments.size(); i++) {
        if(segmentsCheck[i] == true) {
            continue;
        }
        std::vector<glm::vec3> contour;
        contour.push_back(segments[i].first);
        contour.push_back(segments[i].second);
        segmentsCheck[i] = true;
        contour = getContour(segments, segmentsCheck, contour, tolerance);
        contours.push_back(contour);
    }
    return contours;
}

// Unknown behavior: when the function tries to connect a contour that have an loop and
// the vertex is intersecting at the loop (4 segments sharing the same vertex, instead of 2)
std::vector<glm::vec3> Utils::getContour(std::vector<std::pair<glm::vec3, glm::vec3> > &segments, std::vector<bool> &segmentsCheck, std::vector<glm::vec3> contour, float tolerance)
{
    // Find the next segment
    int nearestIndex = getNearestSegment(segments, segmentsCheck, contour.back(), tolerance);
    std::pair<glm::vec3, glm::vec3> nearest = segments[nearestIndex];
    segmentsCheck[nearestIndex] = true;
    if(glm::length(nearest.first - contour.back()) < glm::length(nearest.second - contour.back())) {    // The first is the redudant vertex
        contour.push_back(nearest.second);
    } else {    // The second is the redudant vertex
        contour.push_back(nearest.first);
    }

    // Check if the contour is closed
    if(fabsf(contour[0].x - contour.back().x) < tolerance &&
       fabsf(contour[0].y - contour.back().y) < tolerance &&
       fabsf(contour[0].z - contour.back().z) < tolerance) {
        contour.pop_back();
        return contour;
    } else {
        return getContour(segments, segmentsCheck, contour, tolerance);
    }
}

int Utils::getNearestSegment(std::vector<std::pair<glm::vec3, glm::vec3> > &segments, std::vector<bool> &segmentsCheck, glm::vec3 point, float tolerance)
{
    for(int i = 0; i < segments.size(); i++) {
        if(segmentsCheck[i] == false) {
            std::pair<glm::vec3, glm::vec3> s = segments[i];
            if(fabsf(s.first.x - point.x) < tolerance &&
               fabsf(s.first.y - point.y) < tolerance &&
               fabsf(s.first.z - point.z) < tolerance) {
                return i;
            }
            if(fabsf(s.second.x - point.x) < tolerance &&
               fabsf(s.second.y - point.y) < tolerance &&
               fabsf(s.second.z - point.z) < tolerance) {
                return i;
            }
        }
    }
    std::cout << "ERROR: Can't find the nearest segment\n";
    return -1;
}

// Author: Momesso
std::vector<std::vector<glm::vec2> > Utils::convertContourTo2D(std::vector<std::vector<glm::vec3> > &contours)
{
    std::vector<std::vector<glm::vec2> > result;
    for(std::vector<std::vector<glm::vec3> >::iterator it1 = contours.begin(); it1 != contours.end(); ++it1) {
        std::vector<glm::vec2> aux;
        for(std::vector<glm::vec3>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
            aux.push_back(glm::vec3(*it2));
        }
        result.push_back(aux);
    }
    return result;
}

// Author: Momesso
std::vector<std::vector<glm::vec2> > Utils::splitLoopsFromContours2D(std::vector<std::vector<glm::vec2>> &contours) {
    std::vector<std::vector<glm::vec2> > result;
    for(std::vector<std::vector<glm::vec2>>::iterator itContour = contours.begin(); itContour != contours.end(); ++itContour) {
        std::vector<std::vector<glm::vec2> > aux;
        aux = splitLoopsFromContour2D(*itContour);
        result.insert(result.begin(), aux.begin(), aux.end());
    }
    return result;
}

// Author: Momesso
std::vector<std::vector<glm::vec2> > Utils::splitLoopsFromContour2D(std::vector<glm::vec2> &contour)
{
    std::vector<std::vector<glm::vec2> > result;
    for(std::vector<glm::vec2>::iterator it1 = contour.begin(); it1 != contour.end()-3; ++it1) {
        for(std::vector<glm::vec2>::iterator it2 = it1+2; it2 != contour.end()-1; ++it2) {
            std::pair<glm::vec2, glm::vec2> s1(*(it1), *(it1+1));
            std::pair<glm::vec2, glm::vec2> s2(*(it2), *(it2+1));
            glm::vec2 intersection;
            if(Utils::intersectSegments2D(s1, s2, intersection) == 2) {
                std::vector<glm::vec2> c1;
                std::vector<glm::vec2> c2;
                c1.push_back(intersection);
                c1.insert(c1.end(), it1+1, it2);
                c2.push_back(intersection);
                c2.insert(c2.end(), it2+1, contour.end());
                c2.insert(c2.end(), contour.begin(), it1);
                std::vector<std::vector<glm::vec2> > aux;
                aux = splitLoopsFromContour2D(c1);
                result.insert(result.end(), aux.begin(), aux.end());
                aux = splitLoopsFromContour2D(c2);
                result.insert(result.end(), aux.begin(), aux.end());
                return result;
            }
        }
    }
    result.push_back(contour);
    return result;
}

void Utils::removeLoops2D(std::vector<Triangle> &t, float z, std::vector<std::vector<glm::vec2> > &contoursBase, std::vector<std::vector<glm::vec2> > &contoursOffset, float offset, float tolerance)
{
    offset = fabsf(offset);
    // 1. Detect loop contours
    for(std::vector<std::vector<glm::vec2>>::iterator it1 = contoursBase.begin(); it1 != contoursBase.end(); ++it1) {
        for(std::vector<glm::vec2>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
            glm::vec2 pBase = *it2;
            for(std::vector<std::vector<glm::vec2>>::iterator it3 = contoursOffset.begin(); it3 != contoursOffset.end(); ++it3) {
                for(std::vector<glm::vec2>::iterator it4 = it3->begin(); it4 != it3->end(); ++it4) {
                    glm::vec2 pOffset = *it4;
                    // Maybe the minimum distance between the pBase and the segments of the contour is more robust
                    if(glm::distance(pBase, pOffset) < offset) {
                        std::cout << "loop contour found!\n";
                    }
                }
            }
        }
    }

    // 2. Remove all intersecting triangles from loop contours

    // 3. Repair mesh
}

// NOTE: This function just check for loops on the same contour
bool Utils::checkLoops(std::vector<std::vector<glm::vec3>> &contour) {
    int k = 0;
    std::cout << "contour size: " << contour.size() << std::endl;
    for(std::vector<std::vector<glm::vec3>>::iterator itContour = contour.begin(); itContour != contour.end(); ++itContour) {
        int i = 0;
        while(i < itContour->size()-1) {
            for(int j = i+2; j < itContour->size()-1; j++) {
                std::pair<glm::vec2, glm::vec2> s1(itContour->at(i), itContour->at(i+1));
                std::pair<glm::vec2, glm::vec2> s2(itContour->at(j), itContour->at(j+1));
                glm::vec2 intersection;
                if(Utils::intersectSegments2D(s1, s2, intersection) == 2) {

                    std::cout << k << std::endl <<
                                 glm::to_string(s1.first) << ", " << glm::to_string(s1.second) << std::endl <<
                                 glm::to_string(s2.first) << ", " << glm::to_string(s2.second) << std::endl;
//                    return true;
                }
            }
            i++;
        }
        k++;
    }
    return false;
}

// Author: Momesso
// slice: true if the triangle mesh is just a slice (on z-axis) of a bigger mesh
// POSSIBLE KNOWN PROBLEM: when this function call intersectRayTriangle, if the ray crosses the triangles in their edges, the function return false
//      expected behavior: get the intersection and take the normals average or just one normal
bool Utils::isInsideMesh(std::vector<Triangle> &t, glm::vec3 cellP, bool slice)
{
    bool inside = false;
    glm::vec3 dir;
    if(slice) {
        dir = glm::vec3(1.0, 1.0, 0.0);
    } else {
        dir = glm::vec3(1.0, 1.0, 1.0);
    }

    float distance = std::numeric_limits<float>::max();
    for(std::vector<Triangle>::iterator it = t.begin(); it != t.end(); ++it) {
        float aux = distance;
        if(intersectRayTriangle(cellP, dir, *it, aux)) {
            if(distance > aux) {
                distance = aux;
                if(glm::dot(it->getNormal(), dir) >= 0) {
                    inside = true;
                } else {
                    inside = false;
                }
            }
        }
    }

    return inside;
}

// Centroid of a Polygon
// G Bashein, PR Detmer - GRAPHICS GEMS, 1994
int Utils::getCentroid(std::vector<glm::vec2> &contour, glm::vec2 &centroid)
{
    float area = 0;
    glm::vec2 aux(0.0, 0.0);

    if(contour.size() < 3) {
        return 1;
    }

    for(std::vector<glm::vec2>::iterator p1 = contour.end()-1, p2 = contour.begin(); p2 != contour.end(); p1 = p2, ++p2) {
        float a = (p1->x * p2->y) - (p2->x * p1->y);
        area += a;
        aux.x += (p1->x + p2->x) * a;
        aux.y += (p1->y + p2->y) * a;
    }

    if(fabsf(area) < EPSILON) {
        return 2;
    }

    centroid = aux / (3.0 * area);
    return 0;
}

// http://wwwf.imperial.ac.uk/~rn/centroid.pdf
int Utils::getCentroid(std::vector<Triangle> &t, glm::vec3 &centroid, float &volume)
{
    float volumeAux = 0.0;
    glm::vec3 centroidAux(0.0, 0.0, 0.0);

    if(t.size() < 4) {
        return 1;
    }

    for(std::vector<Triangle>::iterator it = t.begin(); it != t.end(); ++it) {
        volumeAux += glm::dot(it->getV1(), it->getNormal());
        centroidAux.x += (1.0/24.0) * glm::dot(it->getNormal(), glm::vec3(1.0, 0.0, 0.0)) * (pow(glm::dot(it->getV1()+it->getV2(), glm::vec3(1.0, 0.0, 0.0)), 2.0) + pow(glm::dot(it->getV2()+it->getV3(), glm::vec3(1.0,0.0,0.0)), 2.0) + pow(glm::dot(it->getV3()+it->getV1(), glm::vec3(1.0,0.0,0.0)), 2.0));
        centroidAux.y += (1.0/24.0) * glm::dot(it->getNormal(), glm::vec3(0.0, 1.0, 0.0)) * (pow(glm::dot(it->getV1()+it->getV2(), glm::vec3(0.0, 1.0, 0.0)), 2.0) + pow(glm::dot(it->getV2()+it->getV3(), glm::vec3(0.0,1.0,0.0)), 2.0) + pow(glm::dot(it->getV3()+it->getV1(), glm::vec3(0.0,1.0,0.0)), 2.0));
        centroidAux.z += (1.0/24.0) * glm::dot(it->getNormal(), glm::vec3(0.0, 0.0, 1.0)) * (pow(glm::dot(it->getV1()+it->getV2(), glm::vec3(0.0, 0.0, 1.0)), 2.0) + pow(glm::dot(it->getV2()+it->getV3(), glm::vec3(0.0,0.0,1.0)), 2.0) + pow(glm::dot(it->getV3()+it->getV1(), glm::vec3(0.0,0.0,1.0)), 2.0));
    }

    if(fabsf(volumeAux) < EPSILON) {
        return 2;
    }

    volume = volumeAux / 6.0;
    centroid = centroidAux / (2.0 * volume);
    return 0;
}

// Author: Momesso
//void Utils::split(std::vector<Triangle> &mesh, std::vector<Triangle> &cuttingSurface) {
//    // Get intersection points
//    std::vector<glm::vec3> intersectionPoints;
//    for(std::vector<Triangle>::iterator itCut = cuttingSurface.begin(); itCut != cuttingSurface.end(); ++itCut) {
//        for(std::vector<Triangle>::iterator itMesh = mesh.begin(); itMesh != mesh.end(); ++itMesh) {
//            bool intersect = false;
//            // TODO: must be intersect segment triangle
//            if(Utils::intersectRayTriangle(itMesh->getV1(), itMesh->getV2(), *itCut)) {
//                std::cout << std::endl << "intersect:" << glm::to_string(itMesh->getV1()) << std::endl << glm::to_string(itMesh->getV2()) << std::endl << itCut->toString().toStdString() << std::endl;
//                intersect = true;
//            }
//            if(Utils::intersectRayTriangle(itMesh->getV2(), itMesh->getV3(), *itCut)) {
//                intersect = true;
//            }
//            if(Utils::intersectRayTriangle(itMesh->getV3(), itMesh->getV1(), *itCut)) {
//                intersect = true;
//            }
//            if(intersect)
//                std::cout << "intersect\n";
//        }
//    }

//    // Discard outside triangles

//    // Reconstruct surface
//}
