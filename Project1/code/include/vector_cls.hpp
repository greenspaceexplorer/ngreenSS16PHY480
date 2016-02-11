//Vector class for PHY 480 project 1 and beyond
//Written by: Noah Green
//Date: 1/29/2016
//Last Modified: 2/6/2016

#ifndef VECTOR_CLS_HPP
#define VECTOR_CLS_HPP
#include <iostream>
#include <stdlib.h>

using namespace std;

//-----------------------------------------------------------------------------
// Class Declaration
//-----------------------------------------------------------------------------

template<typename element>
class vect{
  
public:
  //default constructor
  vect( int length, element fill ); 
  //copy constructor
  vect( const vect& other );
  //function constructor: fill vect with discretized function values
  vect( int length, element interval, element (*function)(element x) );
  //destructor
  ~vect(); 
  //returns length of vector
  int length() const; 
  //sets value of vector at index
  void set( int index, element value ); 
  //returns value of vector at index
  element get( int index) const; 
  //returns pointer to element at index
  element* operator[]( int index ); 

private:
  element *_vect;
  element _step;
  element _interval;
  int _len;

};


//-----------------------------------------------------------------------------
// Class Definitions
//-----------------------------------------------------------------------------

template< typename element >
vect< element >::vect( int length, element fill ){
  if( length == 0 ){
    cout << "Error: vect must have a length" << endl;
    exit(1);
  }
  if( length < 0 ){
    cout << "Error: vect cannot have negative length" << endl;
    exit(1);
  }
  _len = length;
  _vect = new element[_len];
  for( int i = 0; i < _len; i++ ){
    _vect[i] = fill;
  }
}

//-----------------------------------------------------------------------------

template< typename element >
vect< element >::vect( const vect& other ){
  _len = other.length();
  _vect = new element[_len];
  for( int i = 0; i < _len; i++ ){
    _vect[i] = other.get(i);
  }
}

//-----------------------------------------------------------------------------
template< typename element >
vect< element >::vect( int length, element interval
		       , element (*function)(element x) ){
   if( length == 0 ){
    cout << "Error: vect must have a length" << endl;
    exit(1);
  }
  if( length < 0 ){
    cout << "Error: vect cannot have negative length" << endl;
    exit(1);
  }
  // length of vector
  _len = length;
  // interval over which function is defined
  _interval = interval;
  // calculate step size
  _step = _interval/(_len-1);
  _vect = new element[_len];
  for( int i = 0; i < _len; i++ ){
    _vect[i] = function(i*_step);    
  }

}


//-----------------------------------------------------------------------------

template< typename element >
vect< element >::~vect(){
  if( _vect != 0 ){ delete [] _vect; }
}

//-----------------------------------------------------------------------------

template< typename element >
int vect< element >::length() const { return _len; }

//-----------------------------------------------------------------------------

template< typename element >
void vect< element >::set( int index, element value ){
  if( index >= _len || index < 0 ){
    cout << "Error: invalid index" << endl;
    exit(1);
  }
  _vect[index] = value;
  return;
}

//-----------------------------------------------------------------------------

template< typename element >
element vect< element >::get( int index ) const { 
  if( index >= _len || index < 0 ){
    cout << "Error: invalid index" << endl;
    exit(1);
  }
  return _vect[index];
}

//-----------------------------------------------------------------------------

template< typename element >
element* vect< element >::operator[]( int index ){
  if( index >= _len || index < 0 ){
    cout << "Error: invalid index" << endl;
    exit(1);
  }
  return &_vect[index];

}

//-----------------------------------------------------------------------------

#endif
