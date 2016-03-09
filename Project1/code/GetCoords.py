# Interface with coordinate files
# Written by: Noah Green
# Date: 2/11/2016
# Last Modified: 2/11/2016

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
    y = []
    for coord_string in coord_list:
        tmp_list = coord_string.split(",")
        x.append( float( tmp_list[0] ) )
        y.append( float( tmp_list[1] ) )
    
    return ( x, y_act, y_calc, y_error )
