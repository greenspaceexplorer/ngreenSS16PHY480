//
//  linearTools.hpp
//  project1
//
//  Created by Curtis Rau on 1/28/16.
//  Copyright © 2016 Curtis Rau. All rights reserved.
//

#ifndef linearTools_hpp
#define linearTools_hpp

#include <stdio.h>



// Declare the public class "linTools" which will have functions for solving linear equations
class linTools {

    // Declare public functions
    public:
        // A function which takes a matrix "A", decomposes it into a lower and upper matrix, and returns pointers to L and U.
        void luDecomp (double A, double** L, double** U);
};

#endif /* linearTools_hpp */
