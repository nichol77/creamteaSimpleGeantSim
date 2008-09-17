//
// data_t.cc
//
//  Koskinen, July 2007
//  This is a class that defines the data_t object that 
//  is used to store the JDet output
//  in a root tree.
//------------------

#include "data_t.hh"
ClassImp(data_t)
  
  data_t::data_t():
    run(-1),evtno(-1), ptype(0), box_index(-1)
{;}


//----------------------------------------------------------------------
data_t::~data_t()
{
  // data_t destructor
}

