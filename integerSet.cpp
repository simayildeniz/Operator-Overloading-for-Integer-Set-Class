# include "integerSet.h"
# include <iostream>
# include <algorithm>
# include <vector>
# include <ostream>

using namespace std;

// default constructor
IntegerSet::IntegerSet()
{
	size = 0;
	myArray = NULL;
}

// constructor with size
IntegerSet::IntegerSet(int aSize)
{
	size = aSize;
	myArray = new int[aSize];
	//vector <int> empty;
	/*for (int i = 0; i < aSize; i++)
	{
		empty[i] = i;
	}
	for (int i = 0; i < empty.size(); i++)
	{
		(*this).myArray[i] = empty[i];
	}*/
	for (int i = 0; i < size; i++)
	{
		myArray[i] = i;
	}
}

// destructor
IntegerSet::~IntegerSet()
{
	size = 0;
	delete [] myArray;
}

// deep copy constructor
IntegerSet::IntegerSet(const IntegerSet & copy)
{
	size = copy.size;
	myArray = new int[size];
	for (int i = 0; i < size; i++)
	{
		myArray[i] = copy.myArray[i];
	}
}

//assignment operation
const IntegerSet & IntegerSet::operator=(const IntegerSet & rhs)
{
	if (this != &rhs)
	{
		size = 0;
		delete[] myArray;

		size = rhs.size;
		myArray = new int[size];

		for (int i = 0; i < size; i++)
		{
			myArray[i] = rhs.myArray[i];
		}

	}
	return *this;
}

//+ for integer
IntegerSet IntegerSet::operator+(int rhsInt)
{
	bool isInArray = false;

	for (int i = 0; i < (*this).size; i++)
	{
		if (rhsInt == (*this).myArray[i])
		{
			isInArray = true;
		}
	}

	if (isInArray == false)
	{
		IntegerSet result(size+1);
		//result.myArray[(*this).size] = rhsInt;
		for (int j = 0; j < size; j++)
		{
			result.myArray[j] = (*this).myArray[j];
		}
		result.myArray[size] = rhsInt;
		return result;
	}
	else
	{
		IntegerSet result(*this);
		return result;
	}
}

//+ for 2 sets   UNION
IntegerSet IntegerSet::operator+(const IntegerSet & rhs) const                               
{
	IntegerSet result(*this); 

	for (int i = 0; i < rhs.size; i++)
	{
		bool isFound = false;

		for (int j = 0; j < result.size; j++)
		{
			if (result.myArray[j] == rhs.myArray[i])
			{
				isFound = true;
				break;
			}
		}
		if (isFound == false)
		{
			int * temp = new int[result.size+1];
			for (int k = 0; k < result.size; k++)
			{
				temp[k] = result.myArray[k];
			}
			//last element empty 
			result.size += 1;
			temp[result.size - 1] = rhs.myArray[i];
			delete [] result.myArray;
			result.myArray = temp;
		}
	}

	return result;
}

//intersection  *
IntegerSet IntegerSet::operator*(const IntegerSet & rhs) const  
{
	vector <int> resultVector;

	for (int i = 0; i < (*this).size; i++)
	{
		bool isFound = false;
		for (int j = 0; j < rhs.size; j++)
		{
			if ((*this).myArray[i] == rhs.myArray[j])
			{
				isFound = true;
			}
		}
		if (isFound == true)
		{
			resultVector.push_back((*this).myArray[i]);
		}
	}

	IntegerSet result(resultVector.size());
	for (int i = 0; i < resultVector.size(); i++)
	{
		result.myArray[i] = resultVector[i];
	}
	return result;
}

//+= 2  for 2 integer sets
const IntegerSet & IntegerSet::operator+=(const IntegerSet & rhs)                       
{
	*this = *this + rhs;
	return *this;
}


// is subset   for 2 subsets
bool IntegerSet::operator<=(const IntegerSet & rhs)  // is lhs -which is an int- a subset of rhs       
{
	if ((*this).size > rhs.size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < (*this).size; i++)
		{
			bool isFound = false;
			for (int j = 0; j < rhs.size; j++)
			{
				if ((*this).myArray[i] == rhs.myArray[j])
				{
					isFound = true;
					break;
				}
			}
			if (isFound == false)
			{
				return false;
			}
		}
		return true;
	}
}


//////////Getters In Class:
// size getter
int IntegerSet::sizeGetter() const
{
	return size;
}

//content of the array -getter-
int * IntegerSet::contentGetter() const
{
	int * tempArray = new int[size];

	for (int i = 0; i < size; i++)
	{
		tempArray[i] = myArray[i];
	}

	return tempArray;
}

////////////////FREE FUNCTIONS:
ostream & operator<<(ostream & os,const IntegerSet & intSet)
{
	//int sizeSet = intSet.sizeGetter;
	int x = intSet.sizeGetter();
	int * temp = intSet.contentGetter(); 
	cout << "{" ;
	for (int i = 0; i < intSet.sizeGetter(); i++)
	{
		if (temp[i] != temp[x-1])
		{
			os << temp[i] << ",";
		}
		else
		{
			os << temp[i];
		}

	}
	//os << temp[x] ;
	cout << "}";
	return os;
}

// bool, return true if not equal
bool operator!=(const IntegerSet &lhs, const IntegerSet & rhs)          
{
	int size1 = lhs.sizeGetter();
	int size2 = rhs.sizeGetter();

	int * arr1 = lhs.contentGetter();
	int * arr2 = rhs.contentGetter();

	if (size1 != size2)
	{
		return true;
	}
	else // if their size is equal
	{
		for (int i = 0; i < size1; i++)
		{
			bool isFound = false;
			for (int j = 0; j < size2; j++)
			{
				if (arr1[i] == arr2[j])
				{
					isFound = true;
					break;
				}
			}
			if (isFound == false)
			{
				delete [] arr1;
				delete [] arr2;
				return true;
			}
		}
		delete [] arr1;
		delete [] arr2;
		return false;
	}
}

bool operator<=(const int & x, const IntegerSet & rhs) // is subset?        
{
	int rhslen = rhs.sizeGetter();
	int * rhsArr = rhs.contentGetter();

	bool isFound = false;

	for (int i = 0; i < rhslen; i++)
	{
		if (rhsArr[i] == x)
		{
			isFound = true;
			break;
		}
	}
	if (isFound == true)
	{
		delete [] rhsArr;
		return true;
	}
	delete [] rhsArr;
	return false;
}