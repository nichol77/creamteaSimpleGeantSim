#include <stdlib.h>


#define PI 3.14159265358979312
double cosThetaWeird(double theta);
double getTheta();
double getPhi();
double getMomentum(double pMin, double pMax);
void getPxPyPz(double pVec[3], double pMin=0.1, double pMax=1000);

void getPxPyPz(double pVec[3], double pMin, double pMax)
{
   //Momentum are in GeV
  double theta=getTheta();
  double phi=getPhi();
  double momentum=getMomentum(pMin,pMax);
  pVec[2]=-1*momentum*cos(theta); //pz
  pVec[0]=momentum*cos(phi)*sin(theta);//px
  pVec[1]=momentum*sin(phi)*sin(theta);//py
  
}

//Double_t thetaFunc(Double_t *x, Double_t *par) {
//  return TMath::Power(TMath::Cos(x[0]),2.15);
//}


double cosThetaWeird(double theta)
{
  return pow(cos(theta),2.15);
}

double getTheta() {
  //    cout << drand48() << endl;
    while(1) {
      double angle=drand48()*PI/2;
      double value=cosThetaWeird(angle);
      if(value>drand48())
	return angle;      
    }
}

double getPhi() {
  return PI*2*drand48();
}


double getMomentum(double pMin, double pMax) {
  //  double pMin=1;
  //  double pMax=1e3;

  double maxp1=pow(pMax,-1.7);
  double minp1=pow(pMin,-1.7);
  double y=drand48();
  double momentum=pow((maxp1-minp1)*y + minp1,-1./1.7);
  return momentum;
}
