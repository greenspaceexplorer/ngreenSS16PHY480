#!/bin/bash

if [ -f poisson_solve ]
then
   ./poisson_solve 5
    python SolutionPlot.py
    python ErrorPlot.py
    ./poisson_solve 10
    python SolutionPlot.py
    python ErrorPlot.py
   ./poisson_solve 50
    python SolutionPlot.py
    python ErrorPlot.py
    ./poisson_solve 100
    python SolutionPlot.py
    python ErrorPlot.py
   ./poisson_solve 500
    python SolutionPlot.py
    python ErrorPlot.py
    ./poisson_solve 1000
    python SolutionPlot.py
    python ErrorPlot.py
   ./poisson_solve 1500
    python SolutionPlot.py
    python ErrorPlot.py
   ./poisson_solve 2000
    python SolutionPlot.py
    python ErrorPlot.py
else
    make
   ./poisson_solve 5
    python SolutionPlot.py
    python ErrorPlot.py
    ./poisson_solve 10
    python SolutionPlot.py
    python ErrorPlot.py
   ./poisson_solve 50
    python SolutionPlot.py
    python ErrorPlot.py
    ./poisson_solve 100
    python SolutionPlot.py
    python ErrorPlot.py
   ./poisson_solve 500
    python SolutionPlot.py
    python ErrorPlot.py
    ./poisson_solve 1000
    python SolutionPlot.py
    python ErrorPlot.py
   ./poisson_solve 1500
    python SolutionPlot.py
    python ErrorPlot.py
   ./poisson_solve 2000
    python SolutionPlot.py
    python ErrorPlot.py
fi

