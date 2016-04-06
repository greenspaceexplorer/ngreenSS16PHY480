#include <Planet.h>

using namespace std;

//======================================================================================
// Member Function Definitions
//======================================================================================

Planet::Planet(TString Plabel, double M, double X, double Y, double Z
	       , double Vx, double Vy, double Vz){
  _name = Plabel;
  SetM(M);
  AddCoordinates(0.,X,Y,Z,Vx,Vy,Vz);
  _fixed = false;
}

//--------------------------------------------------------------------------------------

Planet::~Planet(){}

//--------------------------------------------------------------------------------------

TString Planet::Name(){ return _name; }
double Planet::M(){ return _M; }

double Planet::T( unsigned int n ){ Check(n); return _C.t.at(n); }
double Planet::X( unsigned int n ){ Check(n); return _C.x.at(n); }
double Planet::Y( unsigned int n ){ Check(n); return _C.y.at(n); }
double Planet::Z( unsigned int n ){ Check(n); return _C.z.at(n); }

double Planet::Vx( unsigned int n ){ Check(n); return _C.vx.at(n); }
double Planet::Vy( unsigned int n ){ Check(n); return _C.vy.at(n); }
double Planet::Vz( unsigned int n ){ Check(n); return _C.vz.at(n); }

//--------------------------------------------------------------------------------------

unsigned int Planet::N(){
  Check();
  return _C.t.size();
}

//--------------------------------------------------------------------------------------

double Planet::X( Planet &other, unsigned int n ){
  Check(n); 
  return other.X(n) - X(n);
}
double Planet::Y( Planet &other, unsigned int n ){
  Check(n); 
  return other.Y(n) - Y(n);
}
double Planet::Z( Planet &other, unsigned int n ){
  Check(n); 
  return other.Z(n) - Z(n);
}
double Planet::Vx( Planet &other, unsigned int n ){
  Check(n); 
  return other.Vx(n) - Vx(n);
}
double Planet::Vy( Planet &other, unsigned int n ){
  Check(n); 
  return other.Vy(n) - Vy(n);
}
double Planet::Vz( Planet &other, unsigned int n ){
  Check(n); 
  return other.Vz(n) - Vz(n);
} 

//--------------------------------------------------------------------------------------

void Planet::SetM( double Mval ){ _M = Mval; }

void Planet::AddT( double Tval ){ _C.t.push_back(Tval); }
void Planet::AddX( double Xval ){ _C.x.push_back(Xval); }
void Planet::AddY( double Yval ){ _C.y.push_back(Yval); }
void Planet::AddZ( double Zval ){ _C.z.push_back(Zval); }

void Planet::AddVx( double VxVal ){ _C.vx.push_back(VxVal); }
void Planet::AddVy( double VyVal ){ _C.vy.push_back(VyVal); }
void Planet::AddVz( double VzVal ){ _C.vz.push_back(VzVal); }

void Planet::SetT( double Tval, unsigned int n ){ 
  _C.t.at(n) = Tval;
}
void Planet::SetX( double Xval, unsigned int n ){ 
  _C.x.at(n) = Xval;
}
void Planet::SetY( double Yval, unsigned int n ){
  _C.y.at(n) = Yval;
}
void Planet::SetZ( double Zval, unsigned int n ){
  _C.z.at(n) = Zval;
}

void Planet::SetVx( double VxVal, unsigned int n ){
  _C.vx.at(n) = VxVal;
}
void Planet::SetVy( double VyVal, unsigned int n ){
  _C.vy.at(n) = VyVal;
}
void Planet::SetVz( double VzVal, unsigned int n ){
  _C.vz.at(n) = VzVal;
}

void Planet::AddCoordinates( double Tval, double Xval, double Yval, double Zval
		     , double VxVal, double VyVal, double VzVal ){
  AddT(Tval);
  AddX(Xval);
  AddY(Yval);
  AddZ(Zval);
  AddVx(VxVal);
  AddVy(VyVal);
  AddVz(VzVal);
  Check();

}

void Planet::SetCoordinates( unsigned int n, double Tval, double Xval, double Yval, double Zval
		     , double VxVal, double VyVal, double VzVal ){
  SetT(Tval,n);
  SetX(Xval,n);
  SetY(Yval,n);
  SetZ(Zval,n);
  SetVx(VxVal,n);
  SetVy(VyVal,n);
  SetVz(VzVal,n);
  Check(n);
}

//--------------------------------------------------------------------------------------

void Planet::SetFixed( bool isFixed ){ _fixed = isFixed; }
bool Planet::Fixed(){ return _fixed; }

//--------------------------------------------------------------------------------------

double Planet::R( unsigned int n ){
  Check(n); 
  return sqrt(X(n)*X(n) + Y(n)*Y(n) + Z(n)*Z(n));
}

double Planet::R( Planet &other, unsigned int n ){

  Check(n); 
  return sqrt( (X(n)-other.X(n))*(X(n)-other.X(n)) + (Y(n)-other.Y(n))*(Y(n)-other.Y(n))
	       + (Z(n)-other.Z(n))*(Z(n)-other.Z(n)) );
}

//--------------------------------------------------------------------------------------

double Planet::V( unsigned int n ){
  Check(n); 
  return sqrt(Vx(n)*Vx(n) + Vy(n)*Vy(n) + Vz(n)*Vz(n));
}

//--------------------------------------------------------------------------------------

double Planet::F( Planet &other, unsigned int n ){
  if( R(other,n) == 0. ){
    cout << "Error: cannot get force b/w planet and itself." << endl;
    exit(1);
  }  
  return G*M()*other.M()/(R(other,n)*R(other,n));
}

double Planet::Fx( Planet &other, unsigned int n ){ 
  return F(other,n)*X(other,n)/R(other,n);
}

double Planet::Fy( Planet &other, unsigned int n ){
  return F(other,n)*Y(other,n)/R(other,n);
}

double Planet::Fz( Planet &other, unsigned int n ){
  return F(other,n)*Z(other,n)/R(other,n);
}

//--------------------------------------------------------------------------------------

double Planet::KE( unsigned int n ){
  Check(n);
  return (0.5)*M()*V(n)*V(n);
}

//--------------------------------------------------------------------------------------

double Planet::PE( Planet &other, unsigned int n ){
  Check(n);
  if( Name() == other.Name() ){ return 0.; }
  return -G*M()*other.M()/R(other,n);
}

//--------------------------------------------------------------------------------------

void Planet::Lv( double &lx, double &ly, double &lz, unsigned int n ){
  Check(n);
  lx = M()*(Y(n)*Vz(n)-Z(n)*Vy(n));
  ly = M()*(Z(n)*Vx(n)-X(n)*Vz(n));
  lz = M()*(X(n)*Vy(n)-Y(n)*Vx(n));
}

//--------------------------------------------------------------------------------------

double Planet::L( unsigned int n ){
  double lx,ly,lz;
  Lv(lx,ly,lz,n);
  return sqrt(lx*lx+ly*ly+lz*lz);
}

//--------------------------------------------------------------------------------------

void Planet::Check(){

  bool bx,by,bz,bvx,bvy,bvz;
  bx =  _C.t.size() == _C.x.size();
  by =  _C.t.size() == _C.y.size();
  bz =  _C.t.size() == _C.z.size();
  bvx =  _C.t.size() == _C.vx.size();
  bvy =  _C.t.size() == _C.vy.size();
  bvz =  _C.t.size() == _C.vz.size();
  if(!( bx && by && bz && bvx && bvy && bvz )){
    cout << "Error: missing coordinates" << endl;
    exit(1);

  }

}

//--------------------------------------------------------------------------------------

void Planet::Check( unsigned int n ){
  Check();
  if( n > _C.t.size()-1 ){
    cout << "n = " << n << endl;
    cout << "_C.t.size() - 1 = " << _C.t.size() - 1 << endl;
    cout << "Error: time index out of range" << endl;
    exit(1);

  }
}

//--------------------------------------------------------------------------------------

void Planet::PrintCoordinates( unsigned int n ){
  Check(n);
  cout << setprecision(3) 
       << "T = " << _C.t.at(n) << setw(10)
       << "X = " << _C.x.at(n) << setw(10)
       << "Y = " << _C.y.at(n) << setw(10)
       << "Z = " << _C.z.at(n) << setw(10)
       << "Vx = " << _C.vx.at(n) << setw(10)
       << "Vy = " << _C.vy.at(n) << setw(10)
       << "Vz = " << _C.vz.at(n) << endl;
}

//--------------------------------------------------------------------------------------

void Planet::SaveCoordinates( string filename ){
  Check();
  string file;
  file = filename + ".csv";
  ofstream CFile(file.c_str());
  if( !CFile ){
    cout << "Error: file could not be opened";
    exit(1);      
  }
  for( unsigned int i = 0; i < _C.t.size(); i++ ){
    CFile << _C.t.at(i) << ","
	  << _C.x.at(i) << ","
	  << _C.y.at(i) << ","
	  << _C.z.at(i) << ","
	  << _C.vx.at(i) << ","
	  << _C.vy.at(i) << ","
	  << _C.vz.at(i) << endl;
  }
  CFile.close();
}

//--------------------------------------------------------------------------------------

TGraph *Planet::PlotCoordinates2D(){
  Check();
  int n = _C.t.size();
  Double_t *x = _C.x.data();
  Double_t *y = _C.y.data();
  TGraph* Plot2d = new TGraph(n,x,y);
  return Plot2d;
}

//--------------------------------------------------------------------------------------

TGraph *Planet::PlotKEvsT(){
  Check();
  double ke;
  TGraph* PlotKE = new TGraph();
  for( unsigned int i = 0; i < _C.t.size(); i++ ){
    ke = KE(i);
    PlotKE->SetPoint(i,_C.t.at(i),ke);
  }
  return PlotKE;
}

//--------------------------------------------------------------------------------------

TGraph *Planet::PlotPEvsT( Planet &other ){
  Check();
  other.Check();
  if( N() != other.N() ){
    cout << "Error: Cannot compute potential energy - mismatch coordinates" << endl;
    exit(1);
  }
  double pe;
  TGraph* PlotPE = new TGraph();
  for( unsigned int i = 0; i < _C.t.size(); i++ ){
    pe = PE(other, i);
    PlotPE->SetPoint(i,_C.t.at(i),pe);
  }
  return PlotPE;
}

//--------------------------------------------------------------------------------------
