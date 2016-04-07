#include "Planet.h"
#include "SolarSystem.h"
#include "MultiPlot.h"


using namespace std;

int main(){

  //=======================================================================================
  // part c: Earth-Sun system
  //=======================================================================================

  // declare outside of scope for comparison in part f
  TGraph *ESJFRK4_plot_earth;
  TGraph *ESJFRK4_plot_jupiter;
  TGraph *ESJFVerlet_plot_earth;
  TGraph *ESJFVerlet_plot_jupiter;
  
  // put first 3 exercises in common scope for stationary sun and circular orbits
  {  
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
  

    //=======================================================================================
    // part e: Three body problem; Sun fixed
    //=======================================================================================

    //------Show how Jupiter affects Earth's orbit------
    // RK4
    Planet Jupiter("Jupiter",9.5e-4,5.46,0,0,0,2*M_PI/sqrt(5.46),0);
    double ESJ_time = 13.;
    int ESJ_iter = 13000;
    SolarSystem ESJFRK4_reg(ESJ_time,ESJ_iter);
    ESJFRK4_reg.AddPlanet(Sun);
    ESJFRK4_reg.AddPlanet(Earth);
    ESJFRK4_reg.AddPlanet(Jupiter);

    ESJFRK4_reg.RK4();

    ESJFRK4_plot_earth = ESJFRK4_reg.GetPlanet(1).PlotCoordinates2D();
    ESJFRK4_plot_jupiter = ESJFRK4_reg.GetPlanet(2).PlotCoordinates2D();

    MultiPlot ESJFRK4_reg_plot;
    ESJFRK4_reg_plot.Add(ESJFRK4_reg.GetPlanet(1).PlotCoordinates2D(), ESJFRK4_reg.GetPlanet(1).Name(),4);
    ESJFRK4_reg_plot.Add(ESJFRK4_reg.GetPlanet(2).PlotCoordinates2D(), ESJFRK4_reg.GetPlanet(2).Name(),2);
    ESJFRK4_reg_plot._squareplot = true;
    ESJFRK4_reg_plot._title = "3BS:Stationary Sun";
    ESJFRK4_reg_plot.Save("ESJFRK4_reg");

    Planet Jupiter10("Jupiter#times 10",9.5e-3,5.46,0,0,0,2*M_PI/sqrt(5.46),0);
    SolarSystem ESJFRK4_x10(ESJ_time,ESJ_iter);
    ESJFRK4_x10.AddPlanet(Sun);
    ESJFRK4_x10.AddPlanet(Earth);
    ESJFRK4_x10.AddPlanet(Jupiter10);

    ESJFRK4_x10.RK4();
  
    MultiPlot ESJFRK4_x10_plot;
    ESJFRK4_x10_plot.Add(ESJFRK4_x10.GetPlanet(1).PlotCoordinates2D(), ESJFRK4_x10.GetPlanet(1).Name(),4);
    ESJFRK4_x10_plot.Add(ESJFRK4_x10.GetPlanet(2).PlotCoordinates2D(), ESJFRK4_x10.GetPlanet(2).Name(),2);
    ESJFRK4_x10_plot._squareplot = true;
    ESJFRK4_x10_plot._title = "3BS:Stationary Sun";
    ESJFRK4_x10_plot.Save("ESJFRK4_x10");

    Planet Jupiter1000("Jupiter#times 1000",9.5e-1,5.46,0,0,0,2*M_PI/sqrt(5.46),0);
    SolarSystem ESJFRK4_x1000(4.8,ESJ_iter);
    ESJFRK4_x1000.AddPlanet(Sun);
    ESJFRK4_x1000.AddPlanet(Earth);
    ESJFRK4_x1000.AddPlanet(Jupiter1000);

    ESJFRK4_x1000.RK4();
  
    MultiPlot ESJFRK4_x1000_plot;
    ESJFRK4_x1000_plot.Add(ESJFRK4_x1000.GetPlanet(1).PlotCoordinates2D(), ESJFRK4_x1000.GetPlanet(1).Name(),4);
    ESJFRK4_x1000_plot.Add(ESJFRK4_x1000.GetPlanet(2).PlotCoordinates2D(), ESJFRK4_x1000.GetPlanet(2).Name(),2);
    ESJFRK4_x1000_plot._squareplot = true;
    ESJFRK4_x1000_plot._title = "3BS:Stationary Sun";
    ESJFRK4_x1000_plot.Save("ESJFRK4_x1000");

    TGraph *BoldEarth = ESJFRK4_reg.GetPlanet(1).PlotCoordinates2D();
    BoldEarth->SetLineWidth(2);

    MultiPlot ESJFRK4_Earths_plot;
    ESJFRK4_Earths_plot._squareplot = true;
    ESJFRK4_Earths_plot._title = "Earth Orbit with Different Jupiter Masses";
    ESJFRK4_Earths_plot.Add(ESJFRK4_x1000.GetPlanet(1).PlotCoordinates2D(), "Jupiter#times1000",4);
    ESJFRK4_Earths_plot.Add(ESJFRK4_x10.GetPlanet(1).PlotCoordinates2D(), "Jupiter#times10",3);
    ESJFRK4_Earths_plot.Add(BoldEarth, "Jupiter",2);
    ESJFRK4_Earths_plot.Save("ESJFRK4_Earths");

    // Verlet
    SolarSystem ESJFVerlet_reg(ESJ_time,ESJ_iter);
    ESJFVerlet_reg.AddPlanet(Sun);
    ESJFVerlet_reg.AddPlanet(Earth);
    ESJFVerlet_reg.AddPlanet(Jupiter);

    ESJFVerlet_reg.Verlet();
  
    ESJFVerlet_plot_earth = ESJFVerlet_reg.GetPlanet(1).PlotCoordinates2D();
    ESJFVerlet_plot_jupiter = ESJFVerlet_reg.GetPlanet(2).PlotCoordinates2D();

    MultiPlot ESJFVerlet_reg_plot;
    ESJFVerlet_reg_plot.Add(ESJFVerlet_reg.GetPlanet(1).PlotCoordinates2D(), ESJFVerlet_reg.GetPlanet(1).Name(),4);
    ESJFVerlet_reg_plot.Add(ESJFVerlet_reg.GetPlanet(2).PlotCoordinates2D(), ESJFVerlet_reg.GetPlanet(2).Name(),2);
    ESJFVerlet_reg_plot._squareplot = true;
    ESJFVerlet_reg_plot._title = "3BS:Stationary Sun";
    ESJFVerlet_reg_plot.Save("ESJFVerlet_reg");

    SolarSystem ESJFVerlet_x10(ESJ_time,ESJ_iter);
    ESJFVerlet_x10.AddPlanet(Sun);
    ESJFVerlet_x10.AddPlanet(Earth);
    ESJFVerlet_x10.AddPlanet(Jupiter10);

    ESJFVerlet_x10.Verlet();
  
    MultiPlot ESJFVerlet_x10_plot;
    ESJFVerlet_x10_plot.Add(ESJFVerlet_x10.GetPlanet(1).PlotCoordinates2D(), ESJFVerlet_x10.GetPlanet(1).Name(),4);
    ESJFVerlet_x10_plot.Add(ESJFVerlet_x10.GetPlanet(2).PlotCoordinates2D(), ESJFVerlet_x10.GetPlanet(2).Name(),2);
    ESJFVerlet_x10_plot._squareplot = true;
    ESJFVerlet_x10_plot._title = "3BS:Stationary Sun";
    ESJFVerlet_x10_plot.Save("ESJFVerlet_x10");

    SolarSystem ESJFVerlet_x1000(4.8,ESJ_iter);
    ESJFVerlet_x1000.AddPlanet(Sun);
    ESJFVerlet_x1000.AddPlanet(Earth);
    ESJFVerlet_x1000.AddPlanet(Jupiter1000);

    ESJFVerlet_x1000.Verlet();
  
    MultiPlot ESJFVerlet_x1000_plot;
    ESJFVerlet_x1000_plot.Add(ESJFVerlet_x1000.GetPlanet(1).PlotCoordinates2D(), ESJFVerlet_x1000.GetPlanet(1).Name(),4);
    ESJFVerlet_x1000_plot.Add(ESJFVerlet_x1000.GetPlanet(2).PlotCoordinates2D(), ESJFVerlet_x1000.GetPlanet(2).Name(),2);
    ESJFVerlet_x1000_plot._squareplot = true;
    ESJFVerlet_x1000_plot._title = "3BS:Stationary Sun";
    ESJFVerlet_x1000_plot.Save("ESJFVerlet_x1000");

    TGraph *BoldEarth2 = ESJFVerlet_reg.GetPlanet(1).PlotCoordinates2D();
    BoldEarth->SetLineWidth(2);

    MultiPlot ESJFVerlet_Earths_plot;
    ESJFVerlet_Earths_plot._squareplot = true;
    ESJFVerlet_Earths_plot._title = "Earth Orbit with Different Jupiter Masses";
    ESJFVerlet_Earths_plot.Add(ESJFVerlet_x1000.GetPlanet(1).PlotCoordinates2D(), "Jupiter#times1000",4);
    ESJFVerlet_Earths_plot.Add(ESJFVerlet_x10.GetPlanet(1).PlotCoordinates2D(), "Jupiter#times10",3);
    ESJFVerlet_Earths_plot.Add(BoldEarth2, "Jupiter",2);
    ESJFVerlet_Earths_plot.Save("ESJFVerlet_Earths");



    // put jupiters in array for iteration 
    Planet Jupiter_a[] = {Jupiter,Jupiter10,Jupiter1000};

    //------Show how number iterations affects orbit with Verlet vs RK4------
    // initialize solar system for each solver and add planets  
    double esj_time = 2.;
    TString esj_names[] = {"1000 intervals","100 intervals","10 intervals"};
    int esj_colors[] = {2,3,4};

    MultiPlot ESJRK4_plot_reg;
    MultiPlot ESJRK4_plot_x10;
    MultiPlot ESJRK4_plot_x1000;
    MultiPlot ESJRK4_plot[] = {ESJRK4_plot_reg,ESJRK4_plot_x10,ESJRK4_plot_x1000};
    string ESJRK4_names[] = {"ESJRK4_plot_reg","ESJRK4_plot_x10","ESJRK4_plot_x1000"};

    MultiPlot ESJVerlet_plot_reg;
    MultiPlot ESJVerlet_plot_x10;
    MultiPlot ESJVerlet_plot_x1000;
    MultiPlot ESJVerlet_plot[] = {ESJVerlet_plot_reg,ESJVerlet_plot_x10,ESJVerlet_plot_x1000};
    string ESJVerlet_names[] = {"ESJVerlet_plot_reg","ESJVerlet_plot_x10","ESJVerlet_plot_x1000"};

    // iterate over jupiters
    for( int iPlot = 0; iPlot < 3; iPlot++ ){
    
      SolarSystem ESJRK4_1000(esj_time,1000);
      SolarSystem ESJVerlet_1000(esj_time,1000 );
      SolarSystem ESJRK4_100(esj_time,100);
      SolarSystem ESJVerlet_100(esj_time,100);
      SolarSystem ESJRK4_10(esj_time,10);
      SolarSystem ESJVerlet_10(esj_time,10);

      SolarSystem ESJRK4[] = {ESJRK4_1000,ESJRK4_100,ESJRK4_10};
      SolarSystem ESJVerlet[] = {ESJVerlet_1000,ESJVerlet_100,ESJVerlet_10};

      // iterate over number of time steps
      for( int i = 0; i < 3; i++ ){
	ESJRK4[i].AddPlanet(Sun);
	ESJRK4[i].AddPlanet(Earth);
	ESJRK4[i].AddPlanet(Jupiter_a[iPlot]);

	ESJVerlet[i].AddPlanet(Sun);
	ESJVerlet[i].AddPlanet(Earth);
	ESJVerlet[i].AddPlanet(Jupiter_a[iPlot]);
    
	// solve using RK4 and Verlet algorithms
	ESJRK4[i].RK4();
	ESJVerlet[i].Verlet();

	// add results to multiplots
	ESJRK4_plot[iPlot].Add(ESJRK4[i].GetPlanet(1).PlotCoordinates2D(),esj_names[i],esj_colors[i]);
	ESJVerlet_plot[iPlot].Add(ESJVerlet[i].GetPlanet(1).PlotCoordinates2D(),esj_names[i],esj_colors[i]);
      }

      ESJRK4_plot[iPlot]._squareplot = true;
      ESJRK4_plot[iPlot]._title = "ESJ Circular Orbits: RK4";
 
      ESJVerlet_plot[iPlot]._squareplot = true;
      ESJVerlet_plot[iPlot]._title = "ESJ Circular Orbits: Verlet";

      ESJRK4_plot[iPlot].Save(ESJRK4_names[iPlot]);

      ESJVerlet_plot[iPlot].Save(ESJVerlet_names[iPlot]);
    }
  }
  
  //=======================================================================================
  // part f: Dynamic Sun
  //=======================================================================================

  {
    //------3 body system------

    Planet Earth("Earth",3.0e-6,1,0,0, 0,2.*M_PI, 0);  
    Planet Jupiter("Jupiter",9.5e-4,5.46,0,0,0,2*M_PI/sqrt(5.46),0);
    double SunM = 1.1;
    double SunX0 = (-Earth.M()*Earth.X(0)-Jupiter.M()*Jupiter.X(0))/SunM;
    double SunVy0 = (-Earth.M()*Earth.Vy(0)-Jupiter.M()*Jupiter.Vy(0))/SunM;
    Planet Sun("Sun",SunM,SunX0,0,0,0,SunVy0,0);
    Planet ThreeBS[] = {Sun,Earth,Jupiter};

    double esjd_time = 13.;
    double esjd_iter = 13000;
    SolarSystem ESJDRK4(esjd_time,esjd_iter);
    SolarSystem ESJDVerlet(esjd_time,esjd_iter);
    
    for( int i = 0; i < 3; i++ ){
      ESJDRK4.AddPlanet(ThreeBS[i]);
      ESJDVerlet.AddPlanet(ThreeBS[i]);
    }
    
    ESJDRK4.RK4();
    ESJDVerlet.Verlet();

    MultiPlot ESJDRK4_plot;
    MultiPlot ESJDVerlet_plot;

    ESJFRK4_plot_earth->SetLineStyle(3);
    ESJFRK4_plot_jupiter->SetLineStyle(3);
    ESJFVerlet_plot_earth->SetLineStyle(3);
    ESJFVerlet_plot_jupiter->SetLineStyle(3);

    ESJDRK4_plot.Add(ESJDRK4.GetPlanet(1).PlotCoordinates2D(),"Dynamic Sun: Earth",2);
    ESJDRK4_plot.Add(ESJDRK4.GetPlanet(2).PlotCoordinates2D(),"Dynamic Sun: Jupiter",2);
    ESJDRK4_plot.Add(ESJFRK4_plot_earth,"Fixed Sun: Earth",4);
    ESJDRK4_plot.Add(ESJFRK4_plot_jupiter,"Fixed Sun: Jupiter",4);
    ESJDRK4_plot._title = "3BS - Dynamic vs Fixed Sun: RK4";
    ESJDRK4_plot._squareplot = true;

    ESJDVerlet_plot.Add(ESJDVerlet.GetPlanet(1).PlotCoordinates2D(),"Dynamic Sun: Earth",2);
    ESJDVerlet_plot.Add(ESJDVerlet.GetPlanet(2).PlotCoordinates2D(),"Dynamic Sun: Jupiter",2);
    ESJDVerlet_plot.Add(ESJFVerlet_plot_earth,"Fixed Sun: Earth",4);
    ESJDVerlet_plot.Add(ESJFVerlet_plot_jupiter,"Fixed Sun: Jupiter",4);
    ESJDVerlet_plot._title = "3BS - Dynamic vs Fixed Sun: Verlet";
    ESJDVerlet_plot._squareplot = true;    

    ESJDRK4_plot.Save("ESJD_vs_ESJF_RK4");
    ESJDVerlet_plot.Save("ESJD_vs_ESJF_Verlet");
  }
  {
    //------All Major Bodies------
    
    int colors[] = {2,3,4,5,6,7,8,9,1};

    string name[] = {"Sun","Mercury",
		     "Venus","Earth",
		     "Mars","Jupiter",
		     "Saturn","Uranus",
		     "Neptune","Pluto"};

    // Data from JPL HORIZONS system for March 31, 2016

    double mass[] = {1.988544E30,3.302E23,
		     48.685E23,5.97219E24,
		     6.4185E23,1898.13E24,
		     5.68319E26,86.8103E24,
		     102.41E24,1.307E22};

    double x[] = {3.771214804599960E-03,2.392995312379659E-01,
		  6.200080951465198E-01,-9.785498627322475E-01,
		  -1.291291380295386E+00,-5.340537616430271E+00,
		  -3.267596099340765E+00,1.875050199109291E+01,
		  2.805307738816995E+01,8.813542799667879E+00};

    double y[] = {2.029137249606372E-03,2.149377287906326E-01,
		  -3.834322496073330E-01,-1.797802315515018E-01,
		  -9.142624877468940E-01,9.640539204125582E-01,
		  -9.466161305745835E+00,6.871711168043479E+00,
		  -1.051025318965087E+01,-3.186086878390841E+01};

    double z[] = {-1.627041292968787E-04,-4.373669448731976E-03,
		  -4.100838270136119E-02,-1.542552118280727E-04,
		  1.241997175310343E-02,1.154277983360122E-01,
		  2.946376648237891E-01,-2.173952906637191E-01,
		  -4.300726059227100E-01,8.599235865533303E-01};

    double vx[] = {-8.522377770069941E-08,-2.441502198304051E-02,
		   1.060444244667140E-02,2.844142182850449E-03,
		   8.605879257227663E-03,-1.428821446090004E-03,
		   4.967932738054810E-03,-1.382108942896100E-03,
		   1.080903856006663E-03,3.099595772509775E-03};

    double vy[] = {6.979633120052890E-06,2.207511116564336E-02,
		   1.707276942379964E-02,-1.697531631024390E-02,
		   -1.021981613245090E-02,-7.070884170411123E-03,
		   -1.836733609206427E-03,3.509588176414278E-03,
		   2.958348897133972E-03,1.954292088148089E-04};

    double vz[] = {-7.708745975336407E-09,4.043081073902325E-03,
		   -3.779681873547074E-04,7.672476189903642E-07,
		   -4.255309731514439E-04,6.130732872842216E-05,
		   -1.660975644462740E-04,3.103939420070382E-05,
		   -8.607100616149453E-05,-9.220205082807938E-04};
    

    // Make planets
    Planet MajorBodies[10];
    double kg_per_sm = mass[0];
    double days_per_year = 365.25636;

    for( int i = 0; i < 10; i++ ){
      // unit conversion kg->Solar Masses and AU/day->AU/year
      mass[i] = mass[i]/kg_per_sm;
      vx[i] = vx[i]*days_per_year;
      vy[i] = vy[i]*days_per_year;
      vz[i] = vz[i]*days_per_year;
      Planet APlanet(name[i],mass[i],x[i],y[i],z[i],vx[i],vy[i],vz[i]);
      MajorBodies[i] = APlanet;
    }

    // Do inner and outer solar system separately since they have orbits of different timescales
    // ---inner solar system---
    double time_inner = 5;
    double iter_inner = 5000;
    SolarSystem MajorBodies_inner_RK4(time_inner,iter_inner);
    SolarSystem MajorBodies_inner_Verlet(time_inner,iter_inner);
    for( int i = 0; i < 10; i++ ){
      MajorBodies_inner_RK4.AddPlanet(MajorBodies[i]);
      MajorBodies_inner_Verlet.AddPlanet(MajorBodies[i]);  
    }
    MajorBodies_inner_RK4.RK4();
    MajorBodies_inner_Verlet.Verlet();

    // ---outer solar system---
    double time_outer = 250;
    double iter_outer = 25000;
    SolarSystem MajorBodies_outer_RK4(time_outer,iter_outer);
    SolarSystem MajorBodies_outer_Verlet(time_outer,iter_outer);
    // assume inner planets have a negligible effect on outer planet orbits
    //  -justifiable since they have relatively small masses and are far from the outer planets
    MajorBodies_outer_RK4.AddPlanet(MajorBodies[0]);
    MajorBodies_outer_Verlet.AddPlanet(MajorBodies[0]);
    for( int i = 5; i < 10; i++ ){
      MajorBodies_outer_RK4.AddPlanet(MajorBodies[i]);
      MajorBodies_outer_Verlet.AddPlanet(MajorBodies[i]);
    }
    MajorBodies_outer_RK4.RK4();
    MajorBodies_outer_Verlet.Verlet();

    // Do entire solar system at once to demonstrate problem
    SolarSystem MajorBodies_all_RK4(time_outer,iter_outer);
    SolarSystem MajorBodies_all_Verlet(time_outer,iter_outer);
    for( int i = 0; i < 10; i++ ){
      MajorBodies_all_RK4.AddPlanet(MajorBodies[i]);
      MajorBodies_all_Verlet.AddPlanet(MajorBodies[i]);
    }
    MajorBodies_all_RK4.RK4();
    MajorBodies_all_Verlet.Verlet();

    MultiPlot all_bodies_inner_outer_sep_RK4;
    MultiPlot all_bodies_same_time_RK4;
    MultiPlot inner_only_RK4;
    MultiPlot outer_only_RK4;
    
    all_bodies_inner_outer_sep_RK4._squareplot = true;
    all_bodies_same_time_RK4._squareplot = true;
    inner_only_RK4._squareplot = true;
    outer_only_RK4._squareplot = true;
    all_bodies_inner_outer_sep_RK4._title = "Solar System: Inner and Outer Planets Different Timescales";
    all_bodies_same_time_RK4._title = "Solar System: All Planet Same Timescale";
    inner_only_RK4._title = "Solar System: Inner Planets Only";
    outer_only_RK4._title = "Solar System: Outer Planets Only";

    for( int i = 1; i < 10; i++ ){
      all_bodies_same_time_RK4.Add(MajorBodies_all_RK4.GetPlanet(i).PlotCoordinates2D(),
				   MajorBodies_all_RK4.GetPlanet(i).Name(),colors[i]);	       
    }
    for( int i = 1; i < 5; i++ ){
      all_bodies_inner_outer_sep_RK4.Add(MajorBodies_inner_RK4.GetPlanet(i).PlotCoordinates2D(),
				   MajorBodies_inner_RK4.GetPlanet(i).Name(),colors[i]);
      inner_only_RK4.Add(MajorBodies_inner_RK4.GetPlanet(i).PlotCoordinates2D(),
			 MajorBodies_inner_RK4.GetPlanet(i).Name(),colors[i]);
    }
    for( int i = 1; i < MajorBodies_outer_RK4.GetN(); i++ ){
      all_bodies_inner_outer_sep_RK4.Add(MajorBodies_outer_RK4.GetPlanet(i).PlotCoordinates2D(),
					 MajorBodies_outer_RK4.GetPlanet(i).Name(),colors[9-i]);
      outer_only_RK4.Add(MajorBodies_outer_RK4.GetPlanet(i).PlotCoordinates2D(),
					 MajorBodies_outer_RK4.GetPlanet(i).Name(),colors[9-i]);
    }
    all_bodies_inner_outer_sep_RK4.Save("all_bodies_inner_outer_sep_RK4");
    all_bodies_same_time_RK4.Save("all_bodies_same_time_RK4");
    inner_only_RK4.Save("inner_only_RK4");
    outer_only_RK4.Save("outer_only_RK4");

    MultiPlot all_bodies_inner_outer_sep_Verlet;
    MultiPlot all_bodies_same_time_Verlet;
    MultiPlot inner_only_Verlet;
    MultiPlot outer_only_Verlet;
    
    all_bodies_inner_outer_sep_Verlet._squareplot = true;
    all_bodies_same_time_Verlet._squareplot = true;
    inner_only_Verlet._squareplot = true;
    outer_only_Verlet._squareplot = true;
    all_bodies_inner_outer_sep_Verlet._title = "Solar System: Inner and Outer Planets Different Timescales";
    all_bodies_same_time_Verlet._title = "Solar System: All Planet Same Timescale";
    inner_only_Verlet._title = "Solar System: Inner Planets Only";
    outer_only_Verlet._title = "Solar System: Outer Planets Only";

    for( int i = 1; i < 10; i++ ){
      all_bodies_same_time_Verlet.Add(MajorBodies_all_Verlet.GetPlanet(i).PlotCoordinates2D(),
				   MajorBodies_all_Verlet.GetPlanet(i).Name(),colors[i]);	       
    }
    for( int i = 1; i < 5; i++ ){
      all_bodies_inner_outer_sep_Verlet.Add(MajorBodies_inner_Verlet.GetPlanet(i).PlotCoordinates2D(),
				   MajorBodies_inner_Verlet.GetPlanet(i).Name(),colors[i]);
      inner_only_Verlet.Add(MajorBodies_inner_Verlet.GetPlanet(i).PlotCoordinates2D(),
			 MajorBodies_inner_Verlet.GetPlanet(i).Name(),colors[i]);
    }
    for( int i = 1; i < MajorBodies_outer_Verlet.GetN(); i++ ){
      all_bodies_inner_outer_sep_Verlet.Add(MajorBodies_outer_Verlet.GetPlanet(i).PlotCoordinates2D(),
					 MajorBodies_outer_Verlet.GetPlanet(i).Name(),colors[9-i]);
      outer_only_Verlet.Add(MajorBodies_outer_Verlet.GetPlanet(i).PlotCoordinates2D(),
					 MajorBodies_outer_Verlet.GetPlanet(i).Name(),colors[9-i]);
    }
    all_bodies_inner_outer_sep_Verlet.Save("all_bodies_inner_outer_sep_Verlet");
    all_bodies_same_time_Verlet.Save("all_bodies_same_time_Verlet");
    inner_only_Verlet.Save("inner_only_Verlet");
    outer_only_Verlet.Save("outer_only_Verlet");

  }
  

}
