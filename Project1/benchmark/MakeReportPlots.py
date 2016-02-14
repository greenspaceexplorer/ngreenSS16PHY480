# Macro for Report Plots
# Written by: Noah Green
# Date: 2/12/2016
# Last Modified: 2/12/2016

import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from math import log10

file_time_error = "TimeError.txt"
file_step_limit = "StepErrorLimit.txt"

# try to open file
try:
    file_in = open( file_time_error, "r" )
except FileNotFoundError:
    print("Error: file not found\n")
# split each line along whitespace and store in list 
file_line_lst = []
for line in file_in:
    file_line =  line.split()
    file_line_count = 0
    for item in file_line:
        file_line[file_line_count] = item.strip()
        file_line_count += 1
    file_line_lst.append(file_line)

file_in.close()

# select out relevant data from each line
method_lst = [] # LU vs Gaussian decomp
N_lst_tmp  = [] # number of grid points
time_lst   = [] # time for calculation
err_lst    = [] # log10 of relative error

for lst in file_line_lst:
    tmp = len(lst[0])-1
    method_lst.append(lst[0][:tmp])
    N_lst_tmp.append(int(lst[3]))
    time_lst.append(float(lst[8]))
    err_lst.append(float(lst[13]))

# sort data from different methods
N_lst = []
LU_time_lst = []
GE_time_lst = []
LU_err_lst  = []
GE_err_lst  = []

count = 0
for method in method_lst:
    if count == 0:
        pass
    if method == "LU":
        N_lst.append(N_lst_tmp[count])
        LU_time_lst.append(time_lst[count])
        LU_err_lst.append(err_lst[count])
    if method == "GDG":
        GE_time_lst.append(time_lst[count])
        GE_err_lst.append(err_lst[count]) 
    count += 1

# x axis limits
x_min = 0.9*min(N_lst)
x_max = 1.1*max(N_lst)

# calculate y-intercept for log plot expected FLOPS comparison
coeff_n3 = LU_time_lst[len(N_lst)-1]/N_lst[len(N_lst)-1]**3
coeff_n  = GE_time_lst[len(N_lst)-1]/N_lst[len(N_lst)-1]

# calculate arrays for log plot expected FLOPS comparison
x_graph = np.linspace(x_min,x_max)
y_n3    = coeff_n3*x_graph**3
y_n     = coeff_n*x_graph

# plot: time vs grid points
time_name = "TimeVsNPlot.png"
y_min = 0.
y_max = 1.1*max(LU_time_lst)
fig1, (ax1) = plt.subplots(1,1)
ax1.grid(True)
ax1.set_xscale("log")
ax1.set_yscale("log")
ax1.set_xlim(x_min,x_max)
ax1.set_ylim(y_min,y_max)
ax1.set_title("Computation Time vs Number of Grid Points")
ax1.set_xlabel("Number of Grid Points, N")
ax1.set_ylabel("Computation Time (s)")
ax1.plot(N_lst,LU_time_lst,"o",label = "LU Decomposition")
ax1.plot(N_lst,GE_time_lst,"o",label = "Gaussian Elimination")
ax1.plot(x_graph,y_n3, label = "~$N^3$")
ax1.plot(x_graph,y_n, label = "~$N$")
ax1.legend(loc = 0)
fig1.savefig(time_name)
plt.close(fig1)

print("Saved plot of computation time vs grid points to {}".format(time_name))

# plot: relative error vs grid points
#       demonstrate same error for both algorithms
error_name = "ErrorVsNPlotBoth.png"
y_min = 1.1*min(LU_err_lst)
y_max = 0.
fig2, (ax2) = plt.subplots(1,1)
ax2.grid(True)
ax2.set_xscale("log")
ax2.set_xlim(x_min,x_max)
ax2.set_ylim(y_min,y_max)
ax2.set_title("Log$_{10}$ Relative Error vs Number of Grid Points")
ax2.set_xlabel("Number of Grid Points, N")
ax2.set_ylabel(r'log$_{10}$ of Relative Error')
ax2.plot(N_lst,LU_err_lst,"o",label = "LU Decomposition" )
ax2.plot(N_lst,GE_err_lst,"^",label = "Gaussian Elimination")
ax2.legend(loc = 0)
fig2.savefig(error_name)
plt.close(fig2)

print("Saved first plot of relative error vs grid points to {}".format(error_name))


# plot: relative error vs grid points
#       demonstrate limit on step size
try:
    file_in = open(file_step_limit)
except FileNotFoundError:
    print("Error: file not found\n")

N_lst = []
err_lst = []
for line in file_in:
    tmp_lst = line.split()
    N_lst.append(int(tmp_lst[0]))
    err_lst.append(float(tmp_lst[1]))

y_min = 1.1*min(err_lst)
x_min = 0.9*min(N_lst)
x_max = 1.1*max(N_lst)


error1_name = "ErrorVsNPlotLimit.png"
y_min = 1.3*min(LU_err_lst)
y_max = -6.
fig3, (ax3) = plt.subplots(1,1)
ax3.grid(True)
#ax3.set_xscale("log")
ax3.set_xlim(x_min,x_max)
ax3.set_ylim(y_min,y_max)
ax3.set_title("Log$_{10}$ Relative Error vs Number of Grid Points" )
ax3.set_xlabel("Number of Grid Points, N")
ax3.set_ylabel(r'log$_{10}$ of Relative Error')
ax3.plot(N_lst,err_lst,"." )
fig3.savefig(error1_name)
plt.close(fig3)

print("Saved second plot of relative error vs grid points to {}".format(error1_name))
