#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <cmath>
//Time inclusion to evaluate efficiency of the programme
#include <chrono>
#include <ctime>

using namespace std;

class vettore 
 {
public:
//Variabili
 vector<double> componenti;
 double modulo;

//Costruttori
 vettore(){}
 vettore(vector<double> a): componenti(a)
  {
   double modulo_quadro = 0;
   for (int i=0; i<a.size();++i) modulo_quadro+= (a[i]*a[i]);
   modulo = sqrt(modulo_quadro);
  }
  

 vettore(double x, double y)
  {
   componenti.resize(2);
   componenti[0] = x;
   componenti[1] = y;
   double modulo_quadro = 0;
   for (int i=0; i<componenti.size();++i) modulo_quadro+=(componenti[i]*componenti[i]);
   modulo = sqrt(modulo_quadro);
  }
  

 vettore(double x, double y , double z)
  {
   componenti.resize(3);
   componenti[0] = x;
   componenti[1] = y;
   componenti[2] = z;
   double modulo_quadro = 0;
   for (int i=0; i<componenti.size();++i) modulo_quadro+= (componenti[i]*componenti[i]);
   modulo = sqrt(modulo_quadro);
  }
  

  vettore(const vettore &X)
  {
    componenti.resize(X.componenti.size());
    for(int i=0; i<componenti.size(); i++)
    {
      componenti[i]=X.componenti[i];
    }
    modulo=X.modulo;
  }

 vettore operator+(vettore b) 
  {
   vector<double> x;
   x.resize(componenti.size());
   for(int i=0; i<componenti.size() ; ++i) x[i] = (componenti[i] + b.componenti[i]);
   vettore somma (x);
   return somma;
  }

 vettore operator-(vettore b) 
  {
   vector<double> x;
   x.resize(componenti.size());
   for(int i=0; i<componenti.size() ; ++i) x[i] = (componenti[i] - b.componenti[i]);
   vettore somma (x);
   return somma;
  }
	

 double operator*(vettore b)
  {
   double x = 0;
  
   for (int i=0; i<componenti.size(); ++i ) x += componenti[i] * b.componenti[i];
    //cout<<x<<endl;
   return (x);  
  }


  vettore get_versor() 
  {
   return (1/modulo)*(*this);  
  }

   vettore get_normal() 
  {
   if (componenti.size()==2)
   {
   vettore X (-componenti[1], componenti[0]);
   
   return (1/X.modulo)*X;  
   }
   else 
     {
      cout<<"Unavailable in more than two dimensions!\n";
      return *this;
     }
  }   

  friend vettore operator* (double ,vettore );
  friend ostream& operator<< (ostream& o, vettore A);	
};


vettore operator* (double a, vettore v) 
 {
  vector<double> x;
  x.resize(v.componenti.size());
  for (int i=0; i<x.size();++i) x[i] = a*v.componenti[i];
  vettore X(x);
  return X;
 } 


ostream& operator<< (ostream& o, vettore v) 
{
 cout<<"(";
for (int i=0; i<v.componenti.size(); ++i) 
 {
  cout<<v.componenti[i];
  if(i != v.componenti.size() -1 ) cout<<" , ";
 }
 cout<<")";
 return o;
}