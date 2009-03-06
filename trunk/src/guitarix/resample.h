// ***** resample.h *****
/******************************************************************************
part of guitarix, 
for guitarix by hermann meyer
******************************************************************************/
#include <sndfile.hh>

#ifndef ResampleH
#define ResampleH

class Resample
{
private:


public:

 Resample();
  ~Resample();

virtual void fileread(GtkWidget *widget, gpointer data );
};
#endif


