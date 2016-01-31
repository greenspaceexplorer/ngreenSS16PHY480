//Vector class for PHY 480 project 1 and beyond
//Written by: Noah Green
//Date: 1/29/2016
//Last Modified: 1/31/2016

#ifndef VECTOR_CLS_HPP
#define VECTOR_CLS_HPP
#include <iostream>
#include <stdlib.h>

using namespace std;

//-----------------------------------------------------------------------------
// Class Declaration
//-----------------------------------------------------------------------------

template<typename element>
class vec{
  
 public:
  //default constructor
  vec( unsigned int length, element fill ); 
  //copy constructor
  vec( const vec& other ); 
  //destructor
  ~vec(); 
  //returns length of vector
  int length(); 
  //sets value of vector at index
  void set( unsigned int index, element value ); 
  //returns value of vector at index
  element get( unsigned int index) const; 
  //returns pointer to element at index
  element* operator[]( int index ); 

 private:
  element *_vec;
  unsigned int _len;

};

//-----------------------------------------------------------------------------
// Class Definitions
//-----------------------------------------------------------------------------

template< typename element >
vec< element >::vec( unsigned int length, element fill ){
  if( length == 0 ){
    cout << "Error: vec must have a length" << endl;
    exit(1);
  }
  _len = length;
  _vec = new element[_len];
  for( unsigned int i = 0; i < _len; i++ ){
    _vec[i] = fill;
  }
}

//-----------------------------------------------------------------------------

template< typename element >
vec< element >::vec( const vec& other ){
  _len = other.length();
  _vec = new element[_len];
  for( unsigned int i = 0; i < _len; i++ ){
    _vec[i] = other.get(i);
  }
}

//-----------------------------------------------------------------------------

template< typename element >
vec< element >::~vec(){
  if( _vec != 0 ){ delete [] _vec; }
}

//-----------------------------------------------------------------------------

template< typename element >
int vec< element >::length(){ return _len; }

//-----------------------------------------------------------------------------

template< typename element >
void vec< element >::set( unsigned int index, element value ){
  if( index >= _len ){
    cout << "Error: invalid index" << endl;
    exit(1);
  }
  _vec[index] = value;
  return;
}

//-----------------------------------------------------------------------------

template< typename element >
element vec< element >::get( int index ) const { 
  if( index >= _len || index < 0 ){
    cout << "Error: invalid index" << endl;
    exit(1);
  }
  return _vec[index];
}

//-----------------------------------------------------------------------------

template< typename element >
element* vec< element >::operator[]( int index ){
  if( index >= _len || index < 0 ){
    cout << "Error: invalid index" << endl;
    exit(1);
  }
  return &_vec[index];

}

//-----------------------------------------------------------------------------

#endif
