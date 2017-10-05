#include "include/Signal.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>

using namespace std;  
    
    std::vector< double > Signal::read_signal_from_dir(string dir_data)
    {
      
      std::vector< double> signal;
      std::vector< double > aux;

      DIR *dir;
      dirent *pdir;
      std::vector<string> files;
      
      dir = opendir(dir_data.c_str());
  
      while ((pdir = readdir(dir))){
	if ( (strcmp(pdir->d_name, ".")) != 0 && (strcmp(pdir->d_name,"..")) != 0){
	  files.push_back(pdir->d_name);
	}
      }
      std::sort(files.begin(), files.end());
      closedir(dir);
  
  
      for (unsigned int i=0; i<files.size(); i++){
	string file_path = dir_data;
	file_path.append(files[i]);
	aux = read_signal_from_file(file_path.c_str());
	signal.insert(signal.end(), aux.begin(), aux.end());
      }
  
      return signal;
    }

    
    std::vector< double > Signal::read_signal_from_file(string file_path){
      std::vector< double > signal;  
      ifstream data;
      double value;
    
      data.open(file_path);
       //std::cout << "opened " << file_path << std::endl;
      while(data >> value){
	signal.push_back(value);
      }

      data.close();
      
      adjust_values(signal);
      
//       for (auto i : signal)
//    cout << i << endl;


      return signal;
    }
    
//     std::vector< double > Signal::get_signal()
//     {
//       return signal;
//     }

 void Signal::adjust_values(std::vector< double> &signal){
   
   std::vector<double>::iterator max;
   max = std::max_element(signal.begin(), signal.end());

   if( std::abs(*max) < 2){
     std::transform(signal.begin(), signal.end(), signal.begin(),
               std::bind1st(std::multiplies<double>(),1000));
   }

   if( std::abs(*max) > 3000){
     std::transform(signal.begin(), signal.end(), signal.begin(),
               std::bind1st(std::multiplies<double>(),1.0/100.0));
   }
    
   
 }
  
