#ifndef ICOSPHERE_H
#define ICOSPHERE_H

#include "cell.h"

class Icosphere : public Cell {
public:
    Icosphere();
    Icosphere(float r);
    Icosphere(float r, quint8 rl);

    float getRadius();

protected:
    bool init();

    float _radius;
    quint8 _recursionLevel;

private:
    glm::vec3 getMiddlePoint(glm::vec3 v1, glm::vec3 v2);
    glm::vec3 putOverUnitSphere(glm::vec3 v);
};

#endif // ICOSPHERE_H
