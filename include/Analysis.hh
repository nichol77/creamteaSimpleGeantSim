//
// Analysis.hh
//
// Modified Jul 2005 by A. MArino to make data_t and hadmmtuple_t classes

#ifndef NUMIANALYSIS_HH
#define NUMIANALYSIS_HH

//Root files
#include "TROOT.h"          // Top level (or root) structure for all classes
#include "TApplication.h"   // ROOT head file for GUI application singleton
#include <TH1.h>            // ROOT head file for 1 dimension histograms
#include <TH2.h>            // ROOT head file for 2 dimension histograms
#include <TSystem.h>        // ROOT head file for a generic interface to the OS
#include <TStopwatch.h>     // ROOT head file for stopwatch for real and cpu time
#include <TStyle.h>         // ROOT head file for all graphics attributes
#include <TFile.h>          
#include <TText.h>
#include <TTree.h>
#include <TF1.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPostScript.h>
#include <TGraph.h>

#include "DataInput.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4TrajectoryContainer.hh"
#include "ScintillatorHit.hh"

class TClonesArray;

class Analysis
{
public:

  Analysis();
  ~Analysis();

  void book();
  void finish();
  void FillTree(const ScintillatorHitsCollection *hitCol);

  static Analysis* getInstance();

private:
  static Analysis* instance;


  char NtupleFileName[50];

 public:
  DataInput* Data;

  TFile* fScintFile; 
  TTree* fScintTree;
  Int_t fRun;
  Int_t fEvent;

  TClonesArray *fScintHitArray;

  #include "DetectorParams.hh"

};

#endif 
