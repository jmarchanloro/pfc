#ifndef IENGINE_H
#define IENGINE_H

#include <vector>

class IEngine{
public:
    std::vector< double > virtual adquisition() =0;

};


#endif // IENGINE_H
