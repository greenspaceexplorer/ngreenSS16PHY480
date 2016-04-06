#include "Planet.h"
#include "SolarSystem.h"
#include "MultiPlot.h"


using namespace std;

int main(){

  //=======================================================================================
  // part c: Earth-Sun system
  //=======================================================================================

  /*
  // set initial values for Earth to have circular orbit around the Sun
  Planet Sun("Sun",1,0,0,0,0,0,0);
  Planet Earth("Earth",3.0e-6,1,0,0, 0,2.*M_PI, 0);  

  // fix the Sun in place
  Sun.SetFixed( true );

  // initialize solar system for each solver and add planets  
  double es_time = 1.9;

  SolarSystem ESRK4_1000(es_time,1000);
  SolarSystem ESVerlet_1000(es_time,1000 );
  SolarSystem ESRK4_500(es_time,500 );
  SolarSystem ESVerlet_500(es_time,500 );
  SolarSystem ESRK4_100(es_time,100);
  SolarSystem ESVerlet_100(es_time,100);
  SolarSystem ESRK4_50(es_time,50);
  SolarSystem ESVerlet_50(es_time,50);
  SolarSystem ESRK4_25(es_time,25);
  SolarSystem ESVerlet_25(es_time,25);   
  SolarSystem ESRK4_10(es_time,10);
  SolarSystem ESVerlet_10(es_time,10);

  SolarSystem ESRK4[] = {ESRK4_1000,ESRK4_500,ESRK4_100,ESRK4_50,ESRK4_25,ESRK4_10};
  SolarSystem ESVerlet[] = {ESVerlet_1000,ESVerlet_500,ESVerlet_100,ESVerlet_50,ESVerlet_25,ESVerlet_10};
  TString a_names[] = {"1000 intervals","500 intervals"
		       ,"100 intervals","50 intervals"
		       ,"25 intervals","10 intervals"};
  int a_colors[] = {1,3,4,8,46,2};

  MultiPlot ESRK4_plot;
  MultiPlot ESRK4_pe;
  MultiPlot ESRK4_ke;
  MultiPlot ESRK4_l;

  MultiPlot ESVerlet_plot;
  MultiPlot ESVerlet_pe;
  MultiPlot ESVerlet_ke;
  MultiPlot ESVerlet_l;
  

  for( int i = 0; i < 6; i++ ){
    ESRK4[i].AddPlanet(Sun);
    ESRK4[i].AddPlanet(Earth);
    ESVerlet[i].AddPlanet(Sun);
    ESVerlet[i].AddPlanet(Earth);
    
    // solve using RK4 and Verlet algorithms
    ESRK4[i].RK4();
    ESVerlet[i].Verlet();

    // add results to multiplots
    ESRK4_plot.Add(ESRK4[i].GetPlanet(1).PlotCoordinates2D(),a_names[i],a_colors[i]);
    ESRK4_pe.Add(ESRK4[i].PlotPEvsT(),a_names[i],a_colors[i]);
    ESRK4_ke.Add(ESRK4[i].PlotKEvsT(),a_names[i],a_colors[i]);
    ESRK4_l.Add(ESRK4[i].PlotLvsT(),a_names[i],a_colors[i]);

    ESVerlet_plot.Add(ESVerlet[i].GetPlanet(1).PlotCoordinates2D(),a_names[i],a_colors[i]);
    ESVerlet_pe.Add(ESVerlet[i].PlotPEvsT(),a_names[i],a_colors[i]);
    ESVerlet_ke.Add(ESVerlet[i].PlotKEvsT(),a_names[i],a_colors[i]);
    ESVerlet_l.Add(ESVerlet[i].PlotLvsT(),a_names[i],a_colors[i]);
  }

  ESRK4_plot._squareplot = true;
  ESRK4_plot._title = "Earth-Sun System, Circular Orbit: RK4";
  ESRK4_pe._title   = "Earth-Sun System, Potential Energy: RK4";
  ESRK4_pe._xlabel  = "Time (Y)";
  ESRK4_pe._ylabel  = "Potential Energy ( M_{#odot}#times AU^{2}/Y^{2} )";
  ESRK4_pe._xmin    = 0.;
  ESRK4_pe._xmax    = es_time;
  ESRK4_pe._ymin    = -2.0e-4;
  ESRK4_ke._title   = "Earth-Sun System, Kinetic Energy: RK4";
  ESRK4_ke._xlabel  = "Time (Y)";
  ESRK4_ke._ylabel  = "Kinetic Energy ( M_{#odot}#times AU^{2}/Y^{2} )";
  ESRK4_ke._xmin    = 0.;
  ESRK4_ke._xmax    = es_time;
  ESRK4_ke._ymax    = 2.0e-4;
  ESRK4_l._title    = "Earth-Sun System, Angular Momentum: RK4";
  ESRK4_l._xlabel   = "Time (Y)";
  ESRK4_l._ylabel   = "Angular Momentum ( M_{#odot}#times AU^{2}/Y )";
  ESRK4_l._xmin     = 0.;
  ESRK4_l._xmax     = es_time;
  ESRK4_l._ymax     = 2.0e-5;

  ESVerlet_plot._squareplot = true;
  ESVerlet_plot._title = "Earth-Sun System, Circular Orbit: Verlet";
  ESVerlet_pe._title   = "Earth-Sun System, Potential Energy: Verlet";
  ESVerlet_pe._xlabel  = "Time (Y)";
  ESVerlet_pe._ylabel  = "Potential Energy ( M_{#odot}#times AU^{2}/Y^{2} )";
  ESVerlet_pe._xmin    = 0.;
  ESVerlet_pe._xmax    = es_time;
  ESVerlet_pe._ymin    = -0.2e-3;
  ESVerlet_ke._title   = "Earth-Sun System, Kinetic Energy: Verlet";
  ESVerlet_ke._xlabel  = "Time (Y)";
  ESVerlet_ke._ylabel  = "Kinetic Energy ( M_{#odot}#times AU^{2}/Y^{2} )";
  ESVerlet_ke._xmin    = 0.;
  ESVerlet_ke._xmax    = es_time;
  ESVerlet_ke._ymax    = 0.07e-3;
  ESVerlet_l._title    = "Earth-Sun System, Angular Momentum: Verlet";
  ESVerlet_l._xlabel   = "Time (Y)";
  ESVerlet_l._ylabel   = "Angular Momentum ( M_{#odot}#times AU^{2}/Y )";
  ESVerlet_l._xmin     = 0.;
  ESVerlet_l._xmax     = es_time;
  ESVerlet_l._ymin     = 18.5e-6;
  ESVerlet_l._ymax     = 19.e-6;

  ESRK4_plot.Save("ESRK4_position");
  ESRK4_pe.Save("ESRK4_pe");
  ESRK4_ke.Save("ESRK4_ke");
  ESRK4_l.Save("ESRK4_l");

  ESVerlet_plot.Save("ESVerlet_position");
  ESVerlet_pe.Save("ESVerlet_pe");
  ESVerlet_ke.Save("ESVerlet_ke");
  ESVerlet_l.Save("ESVerlet_l");

  

  //=======================================================================================
  // part d: Escape from the solar system
  //=======================================================================================
  
  Planet Sun("Sun",1,0,0,0,0,0,0);
  Sun.SetFixed( true );
  
  double Escape_time = 126;
  int Escape_iter = 20000;

  Planet EPlanet("Escape",3.0e-6,1,0,0, 0,sqrt(8)*M_PI*1.01, 0);  
  Planet NPlanet("No Escape",3.0e-6,1,0,0, 0,sqrt(8)*M_PI*0.99, 0);  
  SolarSystem Escape(Escape_time, Escape_iter);
  SolarSystem NoEscape(Escape_time, Escape_iter);
  Escape.AddPlanet(Sun);
  Escape.AddPlanet(EPlanet);
  NoEscape.AddPlanet(Sun);
  NoEscape.AddPlanet(NPlanet);

  Escape.RK4();
  NoEscape.RK4();

  MultiPlot Escape_plot;
  Escape_plot._squareplot = true;
  Escape_plot._title = "Orbit of Planets Below and Above Escape Velocity";

  Escape_plot.Add(Escape.GetPlanet(1).PlotCoordinates2D()
		  ,"V_{0} = 1.01 #times #sqrt{#frac{2GM_{#odot}}{1 AU}}",2);
  Escape_plot.Add(NoEscape.GetPlanet(1).PlotCoordinates2D()
		    ,"V_{0} = 0.99 #times #sqrt{#frac{2GM_{#odot}}{1 AU}}",4);
  Escape_plot.Save("Escape_plot");
  */

  //=======================================================================================
  // part e: Three body problem; Sun fixed
  //=======================================================================================
  

}
