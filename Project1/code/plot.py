import matplotlib.pyplot as plt
import matplotlib.lines as line

def get_coords(filename):
    """
    Gets coordinates from file.

    Receive: string
    Return: tuple of list of coordinates (x, y_act, y_calc)
    """

    # Open file with coordinates
    try:
        coord_file = open( filename, "r" )
    except FileNotFoundError:
        print("Error: file not found\n")

    # Store each line from file in a list
    coord_list = []
    for line in coord_file:
        coord_list.append(line)
    
    coord_file.close()
    
    # Split line into coordinates and store in lists
    x = []
    y_act = []
    y_calc = []
    for coord_string in coord_list:
        tmp_list = coord_string.split(",")
        x.append(      float( tmp_list[0] ) )
        y_act.append(  float( tmp_list[1] ) )
        y_calc.append( float( tmp_list[2] ) )
    
    return ( x, y_act, y_calc )

def main():
    filename = "sltn_dbl.txt"
    
    # Get coordinates from file
    coords_tuple = get_coords( filename )

    # Get plot boundaries
    x_min = min( coords_tuple[0] )
    y_min = min( ( min(coords_tuple[1]), min(coords_tuple[2]) ) )
    x_max = max( coords_tuple[0] )
    y_max = max( ( max(coords_tuple[1]), max(coords_tuple[2]) ) )

    # Make plot
    plt.plot( coords_tuple[0], coords_tuple[1], label = "Actual" )
    plt.plot( coords_tuple[0], coords_tuple[2], label = "Calculated" )
    plt.axis( [x_min, x_max, y_min, y_max] )
    plt.legend( loc = 7 )
    plt.xlabel( 'x' )
    plt.ylabel( 'y' )
    plt.title( 'Exact and Calculated Solutions to Poisson Equation' )
    plt.show()
    

main()
