# Plotting program for PHY 480 project 2
# Written by: Noah Green
# Date: 1/29/2016
# Last Modified: 3/4/2016

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.lines as line
import numpy as np

#--------------------------------------------------------------------------

def PlotNtest():
    """
    Plots chi squared function as a function of grid points

    Requires file: SeHoNtestGSL.csv
    """
    try:
        ntest_file = open( "SeHoNtestGSL.csv", "r" )
    except FileNotFoundError:
        print("Error: file not found\n")

    Ntest     = []
    Nlist     = []
    E1list    = []
    E2list    = []
    E3list    = []
    ChiSqList = []

    for line in ntest_file:     
        line_list = line.split(",")
        for item in line_list:
            Nlist.append    ( float( line_list[0] ) )
            E1list.append   ( float( line_list[1] ) )
            E2list.append   ( float( line_list[2] ) )
            E3list.append   ( float( line_list[3] ) )
            ChiSqList.append( float( line_list[4] ) )

    Ntest.append( Nlist     )
    Ntest.append( E1list    )
    Ntest.append( E2list    )
    Ntest.append( E3list    )
    Ntest.append( ChiSqList )

    

    # Get plot boundaries 
    x_min = min( Ntest[0] )
    x_max = max( Ntest[0] )
    y_min = min( Ntest[4] ) - .1*abs(min( Ntest[4] ))
    y_max = max( Ntest[4] ) + .1*abs(max( Ntest[4] ))


    Ntest_name = "SeHoNtest.png" 
   
    # plot points
    NtestFig, (ax1) = plt.subplots(1,1)
    ax1.set_xlim(x_min,x_max)
    ax1.set_ylim(y_min,y_max)
    ax1.set_xlabel( 'Number of grid points, N' )
    ax1.set_ylabel( '$\chi^{2}$ ' )
    ax1.set_title('$\chi^{2}$ vs Number of Grid Points')
    ax1.plot( Ntest[0], Ntest[4] )
    NtestFig.savefig(Ntest_name)
    plt.close(NtestFig)

#--------------------------------------------------------------------------

def PlotRtest():
    """
    Plots chi squared function as a function of range

    Requires file: SeHoRtestGSL.csv
    """
    try:
        ntest_file = open( "SeHoRtestGSL.csv", "r" )
    except FileNotFoundError:
        print("Error: file not found\n")

    Rtest     = []
    Rlist     = []
    E1list    = []
    E2list    = []
    E3list    = []
    ChiSqList = []

    for line in ntest_file:     
        line_list = line.split(",")
        for item in line_list:
            Rlist.append    ( float( line_list[0] ) )
            E1list.append   ( float( line_list[1] ) )
            E2list.append   ( float( line_list[2] ) )
            E3list.append   ( float( line_list[3] ) )
            ChiSqList.append( float( line_list[4] ) )

    Rtest.append( Rlist     )
    Rtest.append( E1list    )
    Rtest.append( E2list    )
    Rtest.append( E3list    )
    Rtest.append( ChiSqList )

    

    # Get plot boundaries 
    x_min = 4.4 #min( Rtest[0] )
    x_max = max( Rtest[0] )
    y_min = 0.0 #min( Rtest[4] ) - .1*abs(min( Rtest[4] ))
    y_max = 3.0 #max( Rtest[4] ) + .1*abs(max( Rtest[4] ))

    Rtest_name = "SeHoRtest.png" 
   
    # plot points
    RtestFig, (ax1) = plt.subplots(1,1)
    ax1.set_xlim(x_min,x_max)
    ax1.set_ylim(y_min,y_max)
    ax1.set_xlabel( 'Range ( unitless )' )
    ax1.set_ylabel( '$\chi^{2}$ ' )
    ax1.set_title('$\chi^{2}$ vs Range')
    ax1.plot( Rtest[0], Rtest[4] )
    RtestFig.savefig(Rtest_name)
    plt.close(RtestFig)
        
#--------------------------------------------------------------------------

def PlotIterTimeTest():
    """
    Plots iterations and time to compute as a function of number of grid points

    Requires file: SeHoIterTimeTest.csv
    """
    try:
        ntest_file = open( "SeHoIterTimeTest.csv", "r" )
    except FileNotFoundError:
        print("Error: file not found\n")

    Ttest     = []
    Nlist     = []
    Rlist     = []
    TJlist    = []
    TGlist    = []

    for line in ntest_file:     
        line_list = line.split(",")
        for item in line_list:
            Nlist.append    ( float( line_list[0] ) )
            Rlist.append    ( float( line_list[1] ) )
            TJlist.append   ( float( line_list[2] ) )
            TGlist.append   ( float( line_list[3] ) )

    Ttest.append( Nlist     )
    Ttest.append( Rlist     )
    Ttest.append( TJlist    )
    Ttest.append( TGlist    )


    # iterations plot

    # Get plot boundaries 
    x_min = min( Ttest[0] )
    x_max = max( Ttest[0] )
    y_min = min( Ttest[1] )
    y_max = max( Ttest[1] )

    # Make 2 point quadratic fit
    ItA2 = (Ttest[1][0] - Ttest[1][len(Rlist)-1])\
          /(Ttest[0][0]**2 - Ttest[0][len(Nlist)-1]**2)
    ItB2 = Ttest[1][0] - ItA2*Ttest[0][0]**2
    ItX = np.linspace(x_min,x_max)
    ItY2 = ItA2*ItX**2 + ItB2

    IterTest_name = "SeHoIterTest.png" 
   
    IterTestFig, (ax1) = plt.subplots(1,1)
    ax1.set_xlim(x_min,x_max)
    ax1.set_ylim(y_min,y_max)
    ax1.set_xlabel( 'Number of grid points' )
    ax1.set_ylabel( 'Number of rotations' )
    ax1.set_title('Number of Rotations vs Number of Grid Points')
    #ax1.set_yscale("log")
    ax1.plot( Ttest[0], Ttest[1], "o", label = "Number of Rotations" )
    ax1.plot( ItX, ItY2, label = "$Ax^2+B$" )
    ax1.legend(loc = 0)
    IterTestFig.savefig(IterTest_name)
    plt.close(IterTestFig)

    # time plot
    y_min = min( min(Ttest[2]), min(Ttest[3]) )
    y_max = max( max(Ttest[2]), max(Ttest[3]) )

    TJA4 = (Ttest[2][0] - Ttest[2][len(Rlist)-1])\
          /(Ttest[0][0]**4 - Ttest[0][len(Nlist)-1]**4)
    TJB4 = Ttest[2][0] - TJA4*Ttest[0][0]**4 


    TGA2 = (Ttest[3][0] - Ttest[3][len(Rlist)-1])\
          /(Ttest[0][0]**2 - Ttest[0][len(Nlist)-1]**2)
    TGB2 = Ttest[3][0] - TGA2*Ttest[0][0]**2 
    TGA3 = (Ttest[3][0] - Ttest[3][len(Rlist)-1])\
          /(Ttest[0][0]**3 - Ttest[0][len(Nlist)-1]**3)
    TGB3 = Ttest[3][0] - TGA3*Ttest[0][0]**3 

    TJY4 = TJA4*ItX**4 + TJB4
    TGY2 = TGA2*ItX**2 + TGB2
    TGY3 = TGA3*ItX**3 + TGB3

    Ttest_name = "SeHoTimeTest.png"
    
    TimeTestFig, (ax2) = plt.subplots(1,1)
    ax2.set_xlim(x_min,x_max)
    ax2.set_ylim(y_min,y_max)
    ax2.set_xlabel( 'Number of grid points' )
    ax2.set_ylabel( 'Solution Time (s)' )
    ax2.set_title('Solution Time vs Number of Grid Points')
    ax2.set_yscale("log")
    ax2.plot( Ttest[0], Ttest[2], "o", label = "Jacobi Algorithm" )
    ax2.plot( Ttest[0], Ttest[3], "^", label = "QR Algorithm" )
    ax2.plot( ItX, TJY4, label = "$Ax^4+B$" )
    ax2.plot( ItX, TGY2, label = "$Ax^2+B$" )
    ax2.plot( ItX, TGY3, label = "$Ax^3+B$" )
    ax2.legend(loc = 4, prop = {'size':10})
    TimeTestFig.savefig(Ttest_name)
    plt.close(TimeTestFig)
 
#--------------------------------------------------------------------------

def PlotSeHoWf():
    """
    Plots non-interacting electron wavefunction

    Requires file: SeHoEvec.csv
    """
    try:
        ntest_file = open( "SeHoEvec.csv", "r" )
    except FileNotFoundError:
        print("Error: file not found\n")
    
    XV      = []
    EV1     = []
    EV2     = []
    EV3     = []
    EVlist  = [XV, EV1, EV2, EV3]
    WrList  = []
    WrVal   = [0.01, 0.5, 1.0, 5.0]
    WrName  = ["001","05","1","5"]

    for line in ntest_file:     
        if "Wr" not in line:
            line_list = line.split(",")
            for item in line_list:
                EVlist[0].append   ( float( line_list[0] ) )
                EVlist[1].append   ( float( line_list[1] ) )
                EVlist[2].append   ( float( line_list[2] ) )
                EVlist[3].append   ( float( line_list[3] ) )

        elif "Wr" in line and len(EVlist[0]) == 0:
            continue
        else:
            WrList.append(EVlist)
            XV     = []
            EV1    = []
            EV2    = []
            EV3    = []
            EVlist = [XV, EV1, EV2, EV3]
    WrList.append(EVlist)

    for i in range(len(WrList)):
        CoordList = WrList[i]
        # Get plot boundaries 
        x_min = min(CoordList[0])
        x_max = max(CoordList[0])
        y_min = min(min(CoordList[1]),min(CoordList[2]),min(CoordList[3]))
        y_max = max(max(CoordList[1]),max(CoordList[2]),max(CoordList[3]))

        WfName = "SeHoWfWr"+WrName[i]+".png"

        # plot points
        WfFig, (ax1) = plt.subplots(1,1)
        ax1.set_xlim(x_min,x_max)
        ax1.set_ylim(y_min,y_max)
        ax1.set_xlabel( r'$\rho$ ( unitless )' )
        ax1.set_ylabel( r'$\psi (\rho) $ ' )
        ax1.set_title(r'Double Noninteracting Electron Wavefunctions for $\omega_r$ = ' + str(WrVal[i]))
        ax1.plot( CoordList[0],CoordList[1], label = r'$1^{st}$')
        ax1.plot( CoordList[0],CoordList[2], label = r'$2^{nd}$')
        ax1.plot( CoordList[0],CoordList[3], label = r'$3^{rd}$')
        ax1.legend(loc = 0, title = 'Energy Level' )
        WfFig.savefig(WfName)
        plt.close(WfFig)
        
#--------------------------------------------------------------------------

def PlotDeHoWf():
    """
    Plots double electron wavefunction

    Requires file: DeHoEvec.csv
    """
    try:
        ntest_file = open( "DeHoEvec.csv", "r" )
    except FileNotFoundError:
        print("Error: file not found\n")
    
    XV      = []
    EV1     = []
    EV2     = []
    EV3     = []
    EVlist  = [XV, EV1, EV2, EV3]
    WrList  = []
    WrVal   = [0.01, 0.5, 1.0, 5.0]
    WrName  = ["001","05","1","5"]

    for line in ntest_file:     
        if "Wr" not in line:
            line_list = line.split(",")
            for item in line_list:
                EVlist[0].append   ( float( line_list[0] ) )
                EVlist[1].append   ( float( line_list[1] ) )
                EVlist[2].append   ( float( line_list[2] ) )
                EVlist[3].append   ( float( line_list[3] ) )

        elif "Wr" in line and len(EVlist[0]) == 0:
            continue
        else:
            WrList.append(EVlist)
            XV     = []
            EV1    = []
            EV2    = []
            EV3    = []
            EVlist = [XV, EV1, EV2, EV3]
    WrList.append(EVlist)

    for i in range(len(WrList)):
        CoordList = WrList[i]
        # Get plot boundaries 
        x_min = min(CoordList[0])
        x_max = max(CoordList[0])
        y_min = min(min(CoordList[1]),min(CoordList[2]),min(CoordList[3]))
        y_max = max(max(CoordList[1]),max(CoordList[2]),max(CoordList[3]))

        WfName = "DeHoWfWr"+WrName[i]+".png"

        # plot points
        WfFig, (ax1) = plt.subplots(1,1)
        ax1.set_xlim(x_min,x_max)
        ax1.set_ylim(y_min,y_max)
        ax1.set_xlabel( r'$\rho$ ( unitless )' )
        ax1.set_ylabel( r'$\psi (\rho) $ ' )
        ax1.set_title(r'Double Electron Wavefunctions for $\omega_r$ = ' + str(WrVal[i]))
        ax1.plot( CoordList[0],CoordList[1], label = r'$1^{st}$')
        ax1.plot( CoordList[0],CoordList[2], label = r'$2^{nd}$')
        ax1.plot( CoordList[0],CoordList[3], label = r'$3^{rd}$')
        ax1.legend(loc = 0, title = 'Energy Level' )
        WfFig.savefig(WfName)
        plt.close(WfFig)


PlotNtest()
PlotRtest()
PlotIterTimeTest()
PlotSeHoWf()
PlotDeHoWf()
