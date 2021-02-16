# include <iostream>
# include <string>
# include <ostream>
# include <vector>

#ifndef _INTEGERSET_H
#define _INTEGERSET_H

using namespace std;

class IntegerSet
{
private:
	int size;
	int * myArray;
public:
	IntegerSet(); // empty constructor                                                                  
	IntegerSet(int aSize); // constructor with array size                                              
	IntegerSet(const IntegerSet &); // deep copy constructor                                            
	IntegerSet operator+(int rhsInt); // add an int to a set                                          
	IntegerSet operator+(const IntegerSet & rhs) const; // add two sets to eachother                    
	IntegerSet operator*(const IntegerSet & rhs) const; // intersection                                 
	const IntegerSet & operator=(const IntegerSet & rhs); // assign	                                   
	const IntegerSet & operator+=(const IntegerSet & rhs); // add a set to another set                 
	bool operator<=(const IntegerSet & rhs); // subset of int                                          
	~IntegerSet(); // destructor                                                                        

	//getter:
	int sizeGetter() const;
	int * contentGetter() const;

	//sort
	void bubbleSort(int myArr[], int a);
};

ostream & operator<<(ostream & ,const IntegerSet &);                                              
bool operator!=(const IntegerSet &lhs, const IntegerSet & rhs); // bool, return true if not equal  
bool operator<=(const int & x ,const IntegerSet & rhs); // subset of a subset              

# endif