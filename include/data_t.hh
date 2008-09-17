//
// data_t.hh
//
//  DJK, June 2007
//  This is a class that defines the data_t object that is 
//  used to store the g4numi output in a root tree.
//------------------
#ifndef DATA_T_HH
#define DATA_T_HH

#include "TROOT.h"          // Top level (or root) structure for all classes
#include "TObject.h"

class data_t 
{
  
 public:
  // a constructor and a destructor
  data_t();
  virtual ~data_t();
  
  
  // the following variables are placed in the root tree
  Int_t run;            // Run number
  Int_t evtno;          // Particle ID
  Int_t box_index;          // Scintillator box index
  Int_t ptype;          // Particle type
  Double_t x_trk_pos, y_trk_pos, z_trk_pos;       // Hit location in Scintillator
  Double_t x_p, y_p, z_p;       // Momentum(s) at hit
  Double_t penergy;     // Particle energy at hit position
  
 private:
  ClassDef(data_t ,1) // data_t
    
    };

#endif 

