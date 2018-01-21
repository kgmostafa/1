#include "cell.h"

Cell::Cell() :
    _initialized(false) {
}

std::vector<Triangle> Cell::getFacets() {
    return _facets;
}

void Cell::scale(float x, float y, float z) {
    // TODO: move to origin before scale
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->scale(x, y, z);
    }
}

void Cell::rotateX(float angle) {
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->rotateX(angle);
    }
}

void Cell::rotateY(float angle) {
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->rotateY(angle);
    }
}

void Cell::rotateZ(float angle) {
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->rotateZ(angle);
    }
}

void Cell::translate(float x, float y, float z) {
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->translate(x, y, z);
    }
}

void Cell::place(float x, float y, float z) {
    // TODO: translate cell to origin first
    for (std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->translate(x, y, z);
    }
}

bool Cell::isInitialized() {
    return _initialized;
}
