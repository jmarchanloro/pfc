#ifndef ENGINE_H
#define ENGINE_H

#include "IEngine.hpp"

//#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Engine: public IEngine{
public:
    Engine();
    std::vector < double > adquisition();
private:
    void create_files();
    std::string get_data_time();

    std::ofstream files[22];
    std::vector< double > signal;
    std::vector< std::vector<double> > channels;

};


#endif // ENGINE_H
