//=============================
// Author = Javier MarchAn Loro
// Date   = March 26 2014
//=============================

#ifndef DWT_H_
#define DWT_H_

#include <Python.h>

#include <vector>
#include <string>

/* 
 * This class
 */


class FeatureVector
{
public:
  FeatureVector(int level, std::string filter);
  std::vector< std::vector<double> > calculate_dwt(const std::vector<double>& s);
  std::vector< double > get_feature_vector(const std::vector<double>& s);
  
private:
  std::vector< double > calculate_statistical_values(const std::vector< std::vector<double> > &coeffs);
  std::vector< double > convert_to_vector(PyObject *pValue);
  PyObject* vector_to_list(const std::vector< double >& v);
  
  void myprintsimple(std::vector< double >& v);

  int level;
  std::string filter;
  
};

#endif /*DWT_H_*/
