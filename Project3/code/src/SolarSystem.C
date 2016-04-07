#include "SolarSystem.h"

//======================================================================================
// Member Function Definitions
//======================================================================================

SolarSystem::SolarSystem( double time, int intervals ){
  _Time = time;
  _Ntime = intervals;
  _step = time/((double) intervals);
  _solved = false;
}

//--------------------------------------------------------------------------------------

SolarSystem::~SolarSystem(){}

//--------------------------------------------------------------------------------------

void SolarSystem::AddPlanet( Planet newPlanet ){
  _vPlanets.push_back(newPlanet);
}

//--------------------------------------------------------------------------------------

Planet SolarSystem::GetPlanet( unsigned int i ){

  if( i > _vPlanets.size() - 1 ){
    cout << "Error: cannot get planet " << i 
         << ". Current number of planets = " << _vPlanets.size() << endl;
    exit(1);
  }
  return _vPlanets.at(i);
}

//--------------------------------------------------------------------------------------

unsigned int SolarSystem::GetN(){ return _vPlanets.size(); }

//--------------------------------------------------------------------------------------

void SolarSystem::TotalForce( unsigned int iPlanet, unsigned int iTime, 
			    double &Fx, double &Fy, double &Fz ){
  Fx = 0.; Fy = 0.; Fz = 0.; 
  for( unsigned int i = 0; i < GetN(); i++ ){
    if( i != iPlanet ){
      Fx += _vPlanets.at(iPlanet).Fx(_vPlanets.at(i),iTime);
      Fy += _vPlanets.at(iPlanet).Fy(_vPlanets.at(i),iTime);
      Fz += _vPlanets.at(iPlanet).Fz(_vPlanets.at(i),iTime);      
    }
  }
}

//--------------------------------------------------------------------------------------

double SolarSystem::SystemKE( unsigned int iTime ){
  double TotalKE = 0.;
  for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++){
    TotalKE +=_vPlanets.at(iPlanet).KE(iTime);
  }
  return TotalKE;
}

//--------------------------------------------------------------------------------------

double SolarSystem::SystemPE( unsigned int iTime ){
  double TotalPE = 0.;
  for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++ ){
    for( unsigned int jPlanet = 0; jPlanet < GetN(); jPlanet++ ){
      TotalPE += _vPlanets.at(iPlanet).PE(_vPlanets.at(jPlanet),iTime);
    }
  }
  // divide by 2 to counteract double counting
  return TotalPE/2.;
}

//--------------------------------------------------------------------------------------

double SolarSystem::SystemL( unsigned int iTime ){
  double lx,ly,lz;
  double tlx,tly,tlz;
  tlx = tly = tlz = 0.;
  
  for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++ ){
    _vPlanets.at(iPlanet).Lv(lx,ly,lz,iTime);
    tlx += lx;
    tly += ly;
    tlz += lz;
  }
  return sqrt(tlx*tlx+tly*tly+tlz*tlz);
}

//--------------------------------------------------------------------------------------

void SolarSystem::RK4(){
  _solved = true;
  double Fx,Fy,Fz;

  for( int i = 1; i <= _Ntime; i++ ){
    vector< vector< double > > k1, k2, k3; 
    for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++ ){

      // Keep planet in same position if it is fixed
      if(_vPlanets.at(iPlanet).Fixed()){
	_vPlanets.at(iPlanet).AddCoordinates(i*_step,
					     _vPlanets.at(iPlanet).X(i-1),
					     _vPlanets.at(iPlanet).Y(i-1),
					     _vPlanets.at(iPlanet).Z(i-1),
					     _vPlanets.at(iPlanet).Vx(i-1),
					     _vPlanets.at(iPlanet).Vy(i-1),
					     _vPlanets.at(iPlanet).Vz(i-1));				    
	vector<double> placeholder;
	k1.push_back(placeholder);
      }
      else{

	// calculate k1
	vector<double> k1i;
	k1i.push_back( _step*_vPlanets.at(iPlanet).Vx(i-1) );
	k1i.push_back( _step*_vPlanets.at(iPlanet).Vy(i-1) );
	k1i.push_back( _step*_vPlanets.at(iPlanet).Vz(i-1) );

	TotalForce(iPlanet,i-1,Fx,Fy,Fz);
	k1i.push_back( _step*Fx/_vPlanets.at(iPlanet).M() );
	k1i.push_back( _step*Fy/_vPlanets.at(iPlanet).M() );
	k1i.push_back( _step*Fz/_vPlanets.at(iPlanet).M() );

	// Advance f(t_i,y_i)->f(t_i+h/2,y_i+k1/2)
	_vPlanets.at(iPlanet).AddCoordinates(i*_step,
					     _vPlanets.at(iPlanet).X(i-1)+k1i.at(0)/2.,
					     _vPlanets.at(iPlanet).Y(i-1)+k1i.at(1)/2.,
					     _vPlanets.at(iPlanet).Z(i-1)+k1i.at(2)/2.,
					     _vPlanets.at(iPlanet).Vx(i-1)+k1i.at(3)/2.,
					     _vPlanets.at(iPlanet).Vy(i-1)+k1i.at(4)/2.,
					     _vPlanets.at(iPlanet).Vz(i-1)+k1i.at(5)/2.);
	k1.push_back(k1i);
      }
    }
  

    
    for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++ ){
      if(_vPlanets.at(iPlanet).Fixed()){
	vector<double> placeholder;
	k2.push_back(placeholder);
      }
      else{
	// calculate k2
	vector<double> k2i;
	k2i.push_back( _step*_vPlanets.at(iPlanet).Vx(i));
	k2i.push_back( _step*_vPlanets.at(iPlanet).Vy(i));
	k2i.push_back( _step*_vPlanets.at(iPlanet).Vz(i));

	TotalForce(iPlanet,i,Fx,Fy,Fz);
	k2i.push_back( _step*Fx/_vPlanets.at(iPlanet).M() );
	k2i.push_back( _step*Fy/_vPlanets.at(iPlanet).M() );
	k2i.push_back( _step*Fz/_vPlanets.at(iPlanet).M() );

	// Advance f(t_i+h/2,y_i+k1/2)->f(t_i+h/2,y_i+k2/2)
	_vPlanets.at(iPlanet).SetX(_vPlanets.at(iPlanet).X(i-1)+k2i.at(0)/2.,i);
	_vPlanets.at(iPlanet).SetY(_vPlanets.at(iPlanet).Y(i-1)+k2i.at(1)/2.,i);
	_vPlanets.at(iPlanet).SetZ(_vPlanets.at(iPlanet).Z(i-1)+k2i.at(2)/2.,i);
	_vPlanets.at(iPlanet).SetVx(_vPlanets.at(iPlanet).Vx(i-1)+k2i.at(3)/2.,i);
	_vPlanets.at(iPlanet).SetVy(_vPlanets.at(iPlanet).Vy(i-1)+k2i.at(4)/2.,i);
	_vPlanets.at(iPlanet).SetVz(_vPlanets.at(iPlanet).Vz(i-1)+k2i.at(5)/2.,i);
	k2.push_back(k2i);
      }
    }
  
    
    for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++ ){
      if(_vPlanets.at(iPlanet).Fixed()){
	vector<double> placeholder;
	k3.push_back(placeholder);
      }
      else{
	// calculate k3
	vector<double> k3i;
	k3i.push_back( _step*_vPlanets.at(iPlanet).Vx(i));
	k3i.push_back( _step*_vPlanets.at(iPlanet).Vy(i));
	k3i.push_back( _step*_vPlanets.at(iPlanet).Vz(i));

	TotalForce(iPlanet,i,Fx,Fy,Fz);
	k3i.push_back( _step*Fx/_vPlanets.at(iPlanet).M() );
	k3i.push_back( _step*Fy/_vPlanets.at(iPlanet).M() );
	k3i.push_back( _step*Fz/_vPlanets.at(iPlanet).M() );

	// Advance f(t_i+h/2,y_i+k2/2)->f(t_i+h,y_i+k3)
	_vPlanets.at(iPlanet).SetX(_vPlanets.at(iPlanet).X(i-1)+k3i.at(0),i);
	_vPlanets.at(iPlanet).SetY(_vPlanets.at(iPlanet).Y(i-1)+k3i.at(1),i);
	_vPlanets.at(iPlanet).SetZ(_vPlanets.at(iPlanet).Z(i-1)+k3i.at(2),i);
	_vPlanets.at(iPlanet).SetVx(_vPlanets.at(iPlanet).Vx(i-1)+k3i.at(3),i);
	_vPlanets.at(iPlanet).SetVy(_vPlanets.at(iPlanet).Vy(i-1)+k3i.at(4),i);
	_vPlanets.at(iPlanet).SetVz(_vPlanets.at(iPlanet).Vz(i-1)+k3i.at(5),i);
	k3.push_back(k3i);
      }
    }

    for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++ ){
      if(!_vPlanets.at(iPlanet).Fixed()){
	// calculate k4
	vector<double> k4i;
	k4i.push_back( _step*_vPlanets.at(iPlanet).Vx(i));
	k4i.push_back( _step*_vPlanets.at(iPlanet).Vy(i));
	k4i.push_back( _step*_vPlanets.at(iPlanet).Vz(i));

	Fx = Fy = Fz = 0.;
	TotalForce(iPlanet,i,Fx,Fy,Fz);
	k4i.push_back( _step*Fx/_vPlanets.at(iPlanet).M() );
	k4i.push_back( _step*Fy/_vPlanets.at(iPlanet).M() );
	k4i.push_back( _step*Fz/_vPlanets.at(iPlanet).M() );

	// Advance y_(i+1) = y_i + (1/6)(k1+2k2+2k3+k4)
	_vPlanets.at(iPlanet).SetX(_vPlanets.at(iPlanet).X(i-1)
				   +(k1.at(iPlanet).at(0)
				   +2.*k2.at(iPlanet).at(0)
				   +2.*k3.at(iPlanet).at(0)
				     +k4i.at(0))/6.,i);
	_vPlanets.at(iPlanet).SetY(_vPlanets.at(iPlanet).Y(i-1)
				   +(k1.at(iPlanet).at(1)
				   +2.*k2.at(iPlanet).at(1)
				   +2.*k3.at(iPlanet).at(1)
				     +k4i.at(1))/6.,i);
	_vPlanets.at(iPlanet).SetZ(_vPlanets.at(iPlanet).Z(i-1)
				   +(k1.at(iPlanet).at(2)
				   +2.*k2.at(iPlanet).at(2)
				   +2.*k3.at(iPlanet).at(2)
				     +k4i.at(2))/6.,i);
	_vPlanets.at(iPlanet).SetVx(_vPlanets.at(iPlanet).Vx(i-1)
				    +(k1.at(iPlanet).at(3)
				    +2.*k2.at(iPlanet).at(3)
				    +2.*k3.at(iPlanet).at(3)
				      +k4i.at(3))/6.,i);
	_vPlanets.at(iPlanet).SetVy(_vPlanets.at(iPlanet).Vy(i-1)
				    +(k1.at(iPlanet).at(4)
				    +2.*k2.at(iPlanet).at(4)
				    +2.*k3.at(iPlanet).at(4)
				      +k4i.at(4))/6.,i);
	_vPlanets.at(iPlanet).SetVz(_vPlanets.at(iPlanet).Vz(i-1)
				    +(k1.at(iPlanet).at(5)
				    +2.*k2.at(iPlanet).at(5)
				    +2.*k3.at(iPlanet).at(5)
				      +k4i.at(5))/6.,i);
      }
    }
  }

}

//--------------------------------------------------------------------------------------

void SolarSystem::Verlet(){
  _solved = true;
  // make force variables in this scope so they persist through loops
  vector<double> Fx,Fy,Fz;
  vector<double> fx,fy,fz;
  double f_x,f_y,f_z;
  for( unsigned int fi = 0; fi < GetN(); fi++ ){
    TotalForce(fi,0,f_x,f_y,f_z);
    Fx.push_back(f_x);
    Fy.push_back(f_y);
    Fz.push_back(f_z);
    fx.push_back(f_x);
    fy.push_back(f_y);
    fz.push_back(f_z);
  }

  for( int i = 1; i <= _Ntime; i++){
    for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++ ){
      if(_vPlanets.at(iPlanet).Fixed()){
	_vPlanets.at(iPlanet).AddCoordinates(i*_step,
					     _vPlanets.at(iPlanet).X(i-1),
					     _vPlanets.at(iPlanet).Y(i-1),
					     _vPlanets.at(iPlanet).Z(i-1),
					     _vPlanets.at(iPlanet).Vx(i-1),
					     _vPlanets.at(iPlanet).Vy(i-1),
					     _vPlanets.at(iPlanet).Vz(i-1));  
      }
      else{
	// advance spatial coordinates by one time step
	// set velocity to zero for now
	fx.at(iPlanet) = Fx.at(iPlanet);
	fy.at(iPlanet) = Fy.at(iPlanet);
	fz.at(iPlanet) = Fz.at(iPlanet);
	_vPlanets.at(iPlanet).AddCoordinates(i*_step,
					     _vPlanets.at(iPlanet).X(i-1)+ 
					     _step*_vPlanets.at(iPlanet).Vx(i-1)+
					     _step*_step*fx.at(iPlanet)/(2.*_vPlanets.at(iPlanet).M()),
					     _vPlanets.at(iPlanet).Y(i-1)+
					     _step*_vPlanets.at(iPlanet).Vy(i-1)+
					     _step*_step*fy.at(iPlanet)/(2.*_vPlanets.at(iPlanet).M()),
					     _vPlanets.at(iPlanet).Z(i-1)+
					     _step*_vPlanets.at(iPlanet).Vz(i-1)+
					     _step*_step*fz.at(iPlanet)/(2.*_vPlanets.at(iPlanet).M()),
					     0.,0.,0.);
      }
    }
    for( unsigned int iPlanet = 0; iPlanet < GetN(); iPlanet++){
      if( !_vPlanets.at(iPlanet).Fixed() ){
	// calculate force using new position coordinates
	TotalForce(iPlanet,i,Fx.at(iPlanet),Fy.at(iPlanet),Fz.at(iPlanet));
	// advance velocity coordinates by one step
	_vPlanets.at(iPlanet).SetVx(_vPlanets.at(iPlanet).Vx(i-1)+
				    _step*(fx.at(iPlanet)+Fx.at(iPlanet))/(2.*_vPlanets.at(iPlanet).M()),i);
	_vPlanets.at(iPlanet).SetVy(_vPlanets.at(iPlanet).Vy(i-1)+
				    _step*(fy.at(iPlanet)+Fy.at(iPlanet))/(2.*_vPlanets.at(iPlanet).M()),i);
	_vPlanets.at(iPlanet).SetVz(_vPlanets.at(iPlanet).Vz(i-1)+
				    _step*(fz.at(iPlanet)+Fz.at(iPlanet))/(2.*_vPlanets.at(iPlanet).M()),i);
	
      }
    }
  }
}

//--------------------------------------------------------------------------------------

TGraph *SolarSystem::PlotKEvsT(){
  if(!_solved){
    cout << "Error: must solve SolarSystem before making plot" << endl;
    exit(1);
  }
  double ke;
  TGraph *PlotKE = new TGraph();
  for( unsigned int iTime = 0; iTime < _vPlanets.at(0).N(); iTime++ ){
    ke = SystemKE(iTime);
    PlotKE->SetPoint(iTime,_vPlanets.at(0).T(iTime),ke);    
  }
  return PlotKE;
}

//--------------------------------------------------------------------------------------

TGraph *SolarSystem::PlotPEvsT(){ 
  if(!_solved){
    cout << "Error: must solve SolarSystem before making plot" << endl;
    exit(1);
  }
  double pe;
  TGraph *PlotPE = new TGraph();
  for( unsigned int iTime = 0; iTime < _vPlanets.at(0).N(); iTime++ ){
    pe = SystemPE(iTime);
    PlotPE->SetPoint(iTime,_vPlanets.at(0).T(iTime),pe); 
  }
  return PlotPE;
}

//--------------------------------------------------------------------------------------

TGraph *SolarSystem::PlotLvsT(){ 
  if(!_solved){
    cout << "Error: must solve SolarSystem before making plot" << endl;
    exit(1);
  }
  double l;
  TGraph *PlotL = new TGraph();
  for( unsigned int iTime = 0; iTime < _vPlanets.at(0).N(); iTime++ ){
    l = SystemL(iTime);
    PlotL->SetPoint(iTime,_vPlanets.at(0).T(iTime),l);    
  }
  return PlotL;
}


//--------------------------------------------------------------------------------------
