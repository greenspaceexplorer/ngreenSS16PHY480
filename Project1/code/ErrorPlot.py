# Plotting program for PHY 480 project 1
# Plots calculated and actual solutions of poisson equation
# Written by: Noah Green
# Date: 1/29/2016
# Last Modified: 2/12/2016

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.lines as line
import GetCoords

def main():
    # Open file with filenames
    try:
        file_file = open( "CoordFiles.txt", "r" )
    except FileNotFoundError:
        print("Error: file not found\n")
    filename_list = []
    for line in file_file:
        filename_list.append(line.strip())
    
    count = 0
    for filename in filename_list:
        # Get coordinates from file
        coords_tuple = GetCoords.get_coords( filename )
        
        # do not plot error for endpoints
        error_coord_len = len(coords_tuple[3])
        coords_tuple[0].pop(error_coord_len-1)
        coords_tuple[3].pop(error_coord_len-1)
        coords_tuple[0].pop(0)
        coords_tuple[3].pop(0)

       # make plot name
        name_lst = filename.split(".")
        subname_lst = name_lst[0].split("_")
        plot_name = "Error_" + subname_lst[1]+ "_" + subname_lst[2] + ".png"

        # make plot title
        n_str = subname_lst[2][1:]
        title_str = 'Log Plot of Poisson Equation Solver Relative Error: N =  '\
                    + n_str

        # Get plot boundaries ( 10% beyond max/min of graphs )
        x_min = min( coords_tuple[0] ) - .1*abs(min( coords_tuple[0] ))
        y_min = min( coords_tuple[3] ) - .1*abs(min( coords_tuple[3] ))
        x_max = max( coords_tuple[0] ) + .1*abs(max( coords_tuple[0] ))
        y_max = max( coords_tuple[3] ) + .1*abs(max( coords_tuple[3] ))

        # Make plot
        plt.plot( coords_tuple[0], coords_tuple[3], label = "Relative Error" )
        plt.axis( [x_min, x_max, y_min, y_max] )
        plt.legend( loc = 9 )
        plt.xlabel( 'Independent Variable $x\in(0,1)$' )
        plt.ylabel( 'Log$_{10}$ of Relative Error' )
        plt.title(title_str)
        plt.savefig(plot_name)
        plt.clf()
    
    

main()
