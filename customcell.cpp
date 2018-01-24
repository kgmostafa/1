#include "customcell.h"

CustomCell::CustomCell(QString fn) :
    Cell(), _stl(fn) {
    _initialized = init();
}

bool CustomCell::init() {
    // Decode the STL file
    qint32 n = 0;
    _facets = _stl.decode(n);
    if(n < 0)
        return false; // Return if input file is invalid

    // Load variables
    _maxXLength = _stl.getMaxXLength();
    _maxYLength = _stl.getMaxYLength();
    _maxZLength = _stl.getMaxZLength();
    _maxLength = _stl.getMaxLength();

    return true;
}
