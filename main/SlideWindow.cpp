//==========================
// Author = Javier MarchAn Loro
// Date   = 7 Jan 2014
//==========================


#include "include/SlideWindow.h"
#include <iostream>
#include <vector>
#include <math.h>

SlideWindow::SlideWindow(const std::vector<double>& v, int size_ww, int ovl, double frequency){
	
	freq = frequency;
	size_window = size_ww;
	overlap = ovl;
	origin  = v;
	period = 1.0 / freq;
	nwindows_bug = ((v.size()*period)) / size_window;
	nwindows = 0;
	window_inferior_limit = 0;
    window_superior_limit = size_window*floor(frequency) + 1;
	current_window = 1;
	
}

std::vector<double> SlideWindow::get_next_window(){
	
	if (window_superior_limit <= origin.size()){
		std::vector<double> window(&origin[window_inferior_limit], &origin[window_superior_limit]);		
		window_inferior_limit += size_window*floor(freq) - overlap*floor(freq);
		window_superior_limit += size_window*floor(freq) - overlap*floor(freq);
		
		current_window++;
		return window;
	}
	else{
	        nwindows = current_window;
		std::vector<double> window;
		return window;
	}
	
}

int SlideWindow::get_current_window(){
	return current_window - 1;
}


int SlideWindow::get_nwindows()
{
	return nwindows;
}

/*old funciton with bug*/
int SlideWindow::get_nwindows_bug()
{
	return nwindows_bug;
}


SlideWindow::~SlideWindow()
{
}

