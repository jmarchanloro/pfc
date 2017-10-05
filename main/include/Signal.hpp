#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <fstream>

class Signal{
public:
  
  /**
   * @brief Read a signal from a dir. The signal can be divided between files.
   * @param Directory name where signal files are
   * @return Signal vector. If there are several files the vector contains all
   *         values:
   *         VECTOR:
   *         value_1_1  from file 1
   *         value_2_1  from file 1
   *         value_n_1  from file 1
   *            ...
   *         value_n_1  from file n
   *         value_n_n  from file n
   */
  std::vector< double > read_signal_from_dir(std::string dir_data);
   

private:
  
  /**
   * @brief read a signalfrom a file. The format of the file must be one value per line
   * @param path file
   * @return Signal vector
   */
  std::vector< double > read_signal_from_file(std::string file_path);

  /**
   * @brief adjust_values Adjust the values read. The reason is train and predict the system
   *        with same voltage values order
   * @param signal Signal read previously
   */
  void adjust_values(std::vector< double> &signal);
  
    
  
};

#endif /*SIGNAL_H_*/
