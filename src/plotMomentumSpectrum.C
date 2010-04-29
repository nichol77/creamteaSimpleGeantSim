#include "TMath.h"
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TRandom.h"
#include <iostream>


int getNiceColour(int index)
{
    Int_t niceColours[16]={kBlue-3,kRed-3,kGreen-3,
			   kMagenta-3,kCyan-3,kOrange-3,
			   kViolet-3,kTeal-3,
			   kBlue+1,kRed-3,kGreen+1,
			   kMagenta+1,kCyan+1,kOrange+1,
			   kViolet+1,kTeal+1};
    if(index<16) return niceColours[index];
    
    Int_t offset=index/16;
    Int_t colourInd=index%16;
    
    return (niceColours[colourInd]+offset);
			  
}


double funcCosThetaStar(double cosTheta)
{
  Double_t P1=0.102573;
  Double_t P2=-0.068287;
  Double_t P3=0.958633;
  Double_t P4=0.0407253;
  Double_t P5=0.817285;

  Double_t top=cosTheta*cosTheta+P1*P1+P2*TMath::Power(cosTheta,P3)+P4*TMath::Power(cosTheta,P5);
  Double_t bottom=1+P1*P1+P2+P4;
  return TMath::Sqrt(top/bottom);
}

double guanMuonflux(double energy, double theta)
{
  //Energy in GeV
  //theta in radians

  Double_t cosTheta=TMath::Cos(theta);
  Double_t cosThetaStar=funcCosThetaStar(cosTheta);

  Double_t piTerm= 1 + (1.1 * energy *cosThetaStar)/115.;
  Double_t kTerm=1+ (1.1*energy*cosThetaStar)/850.;
  Double_t bracket=(1/piTerm) + (0.054/kTerm);
  Double_t lowEPart=1 + 3.64/(energy*TMath::Power(cosThetaStar,1.29));
  Double_t full=0.14*TMath::Power(energy*lowEPart,-2.7)*bracket;

  return full;
}

double funcGuanMomentum(double *x, double *par)
{

  return guanMuonflux(x[0],par[0]);

}

TF1 *guamFuncs[90];
double intVals[90];
double cutVals[90];

void getMomentumAndAngle(double pMin, double pMax, double &energy, double &angle) {
  static int doneInit=0;
  if(!doneInit) {
    std::cout << "Starting init\n";
    char graphName[20];
    Double_t totalInt=0;
    for(int deg=0;deg<90;deg++) {
      sprintf(graphName,"guamFunc%d",deg);
      guamFuncs[deg]= new TF1(graphName,funcGuanMomentum,pMin,pMax,1);
      guamFuncs[deg]->SetParameter(0,deg*TMath::DegToRad());
      guamFuncs[deg]->SetNpx(1000);
      intVals[deg]=guamFuncs[deg]->Integral(pMin,pMax);
      totalInt+=intVals[deg];
      //      std::cout << deg << "\t" << intVals[deg] << "\t" << totalInt << "\n";
    } 
    
    Double_t runningTotal=0;
    for(int deg=0;deg<90;deg++) {      
      runningTotal+=intVals[deg];
      cutVals[deg]=runningTotal/totalInt;
      //      std::cout << deg << "\t"  << cutVals[deg] << "\n";
    }
    std::cout << "Done init\n";
    doneInit=1;
  }
  
  Double_t rand=gRandom->Rndm();
  int thisDeg=0;
  double minCut=0;
  for(int deg=0;deg<90;deg++) {
    if(rand<cutVals[deg]) {
      thisDeg=deg;
      if(deg>0) {
	minCut=cutVals[deg-1];
      }
      break;
    }
  }
  angle=TMath::DegToRad()*(((rand-minCut)/(cutVals[thisDeg]-minCut))+thisDeg);
  energy=guamFuncs[thisDeg]->GetRandom();

}


double getMomentum(double pMin, double pMax) {
  //  double pMin=0.1;
  //  double pMax=1e3;

  double maxp1=pow(pMax,-1.7);
  double minp1=pow(pMin,-1.7);
  double y=gRandom->Rndm();
  double momentum=TMath::Power((maxp1-minp1)*y + minp1,-1./1.7);
  return momentum;
}


double getMomentum2(double pMin, double pMaximum) {
  //Takes and returns GeV???
  double pt = 3;
  double y = gRandom->Rndm();  
  double maxp1=TMath::Power(pMaximum,-1.7);
  double minpt=TMath::Power(pt,-1.7);
  
  double a = 5;

  double threshold = 1./(1 + (a/-1.7) * (maxp1 - minpt));
  
  double momentum1 = ((y*(1+((a/-1.7)*(maxp1-minpt))))*(pt-pMin)) + pMin;
  double momentum2 = TMath::Power((((-1.7/a)*(y*(1+(a/-1.7)*(maxp1-minpt))-1)) + minpt),-
			 1./1.7);
  
  if(y<threshold) {  
    //    std::cout << "Momentum1 = " << momentum1 << "\n";
    return momentum1;
  } else { 
    //    std::cout << "Momentum2 = " << momentum2 << "\n";
    return momentum2;
  }
}


double cosThetaWeird(double theta)
{
  return TMath::Power(cos(theta),2.15);
}

double getTheta() {
  //    cout << drand48() << endl;
    while(1) {
      double angle=(gRandom->Rndm()*TMath::Pi())-TMath::PiOver2();
      double value=cosThetaWeird(angle);
      if(value>gRandom->Rndm())
	return angle;      
    }
}



void plotMomentumSpectrum()
{
  TCanvas *can = new TCanvas("can","can");
  can->SetLogy();
  can->SetLogx();
  TF1 *funcy = new TF1("funcy",funcGuanMomentum,0.1,10000,1);
  funcy->SetNpx(10000);
  funcy->SetParameter(0,0);
  funcy->DrawClone("");
  for(int deg=10;deg<90;deg+=10) {
    funcy->SetParameter(0,deg*TMath::DegToRad());
    funcy->SetLineColor(getNiceColour(deg/10));
    funcy->DrawClone("same");
  }


  TH1F *histEnergy = new TH1F("histEnergy","histEnergy",1000,0.1,1000);
  TH1F *histAngle = new TH1F("histAngle","histAngle",90,0,90);
  Double_t energy,angle;
  for(int i=0;i<1000;i++) {
    getMomentumAndAngle(0.1,10000,energy,angle);
    histEnergy->Fill(energy);
    //    std::cout << energy << "\t" << angle << "\n";
    histAngle->Fill(angle*TMath::RadToDeg());
  }
  TCanvas *can2 = new TCanvas("can2","can2");
  can2->Divide(1,2);
  can2->cd(1);
  histEnergy->Draw();
  can2->cd(2);
  histAngle->Draw();
      


}
