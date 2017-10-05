//=============================
// Author = Javier MarchAn Loro
// Date   = 7 Jan 2014
//=============================


#ifndef SLIDEWINDOW_H_
#define SLIDEWINDOW_H_

#include <vector>
#include <iostream>

/*
 * This class implements an slide window with the parameters given. 
 * The general use is:
 * 
 * 		vector<T> window;
 * 		sw = SlideWindow sw(data, size_of_the_window, overlap, frequency);
 * 		while (!(window=sw.get_next_window()).empty()){
 * 				//Do something with the window
		}	
 *
 * Each call to the get_next_window function returns a window. For example, given a file with 100 numbers, sampled
 * 10 hz frequency (=10 seconds recorded), 5 seconds of size window and 0 overlap, the object will 
 * return two windows. If x numbers ar added, with 0 <= x < 50, they are not consideraded.
 * 
 * The object's useful life end up when get_next_window function returns an empty vector.
 * */


class SlideWindow
{
public:
	SlideWindow();
	
	/*Constructor
	 * v  data
	 * size_window  size of the slide window
	 * overlap  overlap between a window and the next
	 * freq  data is sampled to freq Hz*/
	SlideWindow(const std::vector<double>& v, int size_window, int overlap, double freq);
	
	/* The main function in the class. Return a vector whith the next window*/
	std::vector<double> get_next_window();
	
	/*Number of the last window gotten. When an object is created, this method returns 0
	 * After the first call to get_next_window, this function will return 1, etc*/
	int get_current_window();
	
	/**
	 *Temp
	 * Only enabled when all windows have been get
	 */
	int get_nwindows();
	int get_nwindows_bug();
	virtual ~SlideWindow();
	
private:
	std::vector<double> origin;
	double period;
	double freq;
	unsigned int size_window;
	unsigned int nwindows;
	unsigned int nwindows_bug;
	unsigned int current_window;
	unsigned int window_inferior_limit;
	unsigned int window_superior_limit;
	int overlap;
};

#endif /*SLIDEWINDOW_H_*/
