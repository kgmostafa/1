#ifndef CUSTOMCELL_H
#define CUSTOMCELL_H

#include "cell.h"
#include "stlfile.h"

class CustomCell : public Cell {
public:
    CustomCell(QString fn);
    CustomCell(std::vector<Triangle> facets);

private:
    bool init();

    STLFile _stl;
};

#endif // CUSTOMCELL_H
