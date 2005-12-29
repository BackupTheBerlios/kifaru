#include "tools.h"
#include "effect.h"


using namespace std;

namespace ephidrena {

int str2int(const char* digit) 
{
	int result = 0;

	while (*digit >= '0' && *digit <='9')
	{
		result = (result * 10) + (*digit - '0');
		digit++;
   	}
	
	if (*digit != 0)
		return false;

	return result;
}

float str2float(const char* digit)
{
	float result = 0;
	float divider = 1;

	while (*digit >= '0' && *digit <= '9')
	{
		result = (result * 10) + (*digit - '0');
		digit++;
	}
   
	if (*digit == '.') 
	{
		digit++;
		while (*digit >= '0' && *digit <= '9')
		{
			result = (result * 10) + (*digit - '0');
			divider *=10 ;
			digit++;
		}	   
		result /= divider;
	}   

	if (*digit != 0)
		return false;
	
	return result;
}

int Rnd(int min,int max)
{	
	static unsigned seed;
	
	seed += unsigned(time(0));
	srand(seed);

	return (min + rand() ) % max; 
}


static int partition(int a[], int first, int last)
{
	int pivot = a[first];
	int lastS1 = first;
	int firstUnknown = first + 1;
	
	while (firstUnknown <= last)
	{
		if (a[firstUnknown] < pivot)
		{
			lastS1++;
			std::swap(a[firstUnknown], a[lastS1]);
		}
		firstUnknown++;
	}
	std::swap(a[first], a[lastS1]);
	return lastS1;
}

static void quicksort(int a[], int first, int last)
{
	if (first < last)
	{
		int pivotIndex = partition(a, first, last);
		quicksort(a, first, pivotIndex - 1);
		quicksort(a, pivotIndex + 1, last);
	}
}

static void quicksort(int a[], int aSize)
{
	quicksort(a, 0, aSize - 1);
}

};
