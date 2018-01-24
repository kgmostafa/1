#ifndef CUSTOMCELL_H
#define CUSTOMCELL_H

#include "cell.h"
#include "stlfile.h"

class CustomCell : public Cell {
public:
    CustomCell(QString fn);

private:
    bool init();

    STLFile _stl;
};

#endif // CUSTOMCELL_H
