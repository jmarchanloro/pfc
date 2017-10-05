//=============================
// Author = Javier MarchAn Loro
// Date   = March 26 2014
//=============================

#include <Python.h>

#include <iostream>

#include "include/FeatureVector.hpp"
#include "include/Signal.hpp"

using namespace std;

FeatureVector::FeatureVector::FeatureVector(int level, string filter)
{
  this->level  = level;
  this->filter = filter;
}

vector< vector<double> > FeatureVector::calculate_dwt(const std::vector< double>& s)
{
  
    vector<double> signal = s;
    vector< vector< double > > coeffs;
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    
    /* Initialize the Python interpreter*/
    Py_Initialize();
    
    /***************************************************************/
    /***¿¿¿¿POR QUE COJONES ESTAS LINEAS NO ESTAN EN LA DOCUMENTACION OFICIAL?????***/
    /* SIN ESTO NO ENCUENTRA EL SCRIPT*/
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");
    /***************************************************************/
    /* load the script*/
    pName = PyString_FromString("dwtpy");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule != NULL) {

        /* Prepare the function called doDWT()*/
        pFunc = PyObject_GetAttrString(pModule, "doDWT");
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            //Prepare args to the doDWT function	    
            pArgs  = PyTuple_New(3);
            pValue = vector_to_list(signal);
            if (!pValue) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                cout << "Cannot convert argument" << endl;
            }
            PyTuple_SetItem(pArgs, 0, pValue);
            pValue = PyString_FromString(filter.c_str());
            PyTuple_SetItem(pArgs, 1, pValue);
            pValue = PyInt_FromLong(level);
            PyTuple_SetItem(pArgs, 2, pValue);
	    
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                PyObject *c;
                vector<double> v_c;

                //get coeffcients
                // CA_n CD_n CD_n-1 .. CD_1
                for(int i=0; i<PySequence_Size(pValue); i++){
                    c = PySequence_GetItem(pValue, i);
                    v_c  = convert_to_vector(c);
                    coeffs.insert(coeffs.end(), v_c);
                    //Py_DECREF(pValue); // Do not work!
                }
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                cout << "Call failed" << endl;
            }

        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();


            cout << "Cannot find function" << endl;
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        cout << "Failed to load script" << endl;
    }

//     Py_Finalize();
    
    return coeffs;

}

std::vector< double > FeatureVector::get_feature_vector(const std::vector< double >& s)
{
  
    vector<double> feature_vector;
    vector< vector<double> > coeffs = calculate_dwt(s);    
    feature_vector = calculate_statistical_values(coeffs);
    return feature_vector;

}

std::vector< double > FeatureVector::calculate_statistical_values(const std::vector< vector<double> > &coeffs){

    double max, min, mean, variance, stddev;
    vector<double> max_values;
    vector<double> min_values;
    vector<double> mean_values;
    vector<double> stddev_values;

    vector<double> feature_vector;

    for(unsigned int i=0; i<coeffs.size(); i++){
        max = *std::max_element(coeffs.at(i).begin(), coeffs.at(i).end());
        max_values.push_back(max);
        min = *std::min_element(coeffs.at(i).begin(), coeffs.at(i).end());
        min_values.push_back(min);
        mean = std::accumulate(coeffs.at(i).begin(), coeffs.at(i).end(), 0.0) / (double)(coeffs.at(i).size());
        mean_values.push_back(mean);
        variance = (std::inner_product(coeffs.at(i).begin(), coeffs.at(i).end(), coeffs.at(i).begin(), 0.0) / coeffs.at(i).size()) - mean*mean;
        stddev= sqrt(variance);
        stddev_values.push_back(stddev);
    }

    feature_vector.insert(feature_vector.end(),
                          max_values.begin(), max_values.end());

    feature_vector.insert(feature_vector.end(),
                          min_values.begin(), min_values.end());

    feature_vector.insert(feature_vector.end(),
                          mean_values.begin(), mean_values.end());

    feature_vector.insert(feature_vector.end(),
                          stddev_values.begin(), stddev_values.end());

    return feature_vector;

}

std::vector< double > FeatureVector::convert_to_vector(PyObject *pValue)
{
  vector<double> v;
  
  PyObject *seq, *value;
  double dvalue;
  seq = PySequence_Fast(pValue, "expected a sequence");
  int len = PySequence_Size(pValue);
//   cout << "len:" << len << endl;
  for (int i=0; i < len; i++){
    value = PySequence_Fast_GET_ITEM(seq, i);
    dvalue = PyFloat_AS_DOUBLE(value);
    v.push_back(dvalue);
  }
   
  return v;

}

PyObject* FeatureVector::vector_to_list(const std::vector< double >& data)
{
  PyObject* listObj = PyList_New( data.size() );
  
  for (unsigned int i = 0; i < data.size(); i++) {
    PyObject *num = PyFloat_FromDouble( (double) data[i]);
    if (!num) {
      Py_DECREF(listObj);
//       throw logic_error("Unable to allocate memory for Python list");
    }
    PyList_SET_ITEM(listObj, i, num);
  }
  return listObj;

}

void FeatureVector::myprintsimple(std::vector< double >& v)
{
   int j=0;
   for (auto &i : v){
       std::cout << i << "|";
       j++;
   }

    std::cout << endl << endl << j << endl;

}


