#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
   
void shuffleArray(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
		for (i = 0; i < n - 1; i++) 
		{
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
    }
}

void fullPrintArray(int *myArrayPtr, size_t arrayLength)
{
	int i;
	for(i = 0; i < arrayLength; i++)
	{
		printf("Array Value at element %d is: %d\n", i, myArrayPtr[i]);
	}
}

int * generateArray(size_t arraySize)
{
	size_t n = arraySize;
	int *myArray = (int *)malloc(n * sizeof(int*));
	size_t i;
	for(i = 0; i < n; i++)
	{
		myArray[i] = i;
	}
	return myArray;
}

int * concatenate(int *lowerArray, int pivotValue, int *higherArray, size_t totalArraySize, size_t lowerArraySize, size_t higherArraySize)
{
	int *array = (int *)malloc(totalArraySize * sizeof(int*));
	int i;
	array[lowerArraySize] = pivotValue;
	for(i = 0; i < totalArraySize; i++)
	{
		if(i < lowerArraySize && lowerArraySize > 0)
		{
			array[i] = lowerArray[i];
		}
		if(i < higherArraySize && higherArraySize > 0)
		{
			array[i+lowerArraySize+1] = higherArray[i];
		}
	}
	free(lowerArray);
	free(higherArray);
	return array;
}

int * quickSort(int *array, size_t arraySize)
{
	//If single value
		//return
	//Else
		//Select Pivot
		//Assign > to list1
		//Assign < to list2
		//Quicksort lists
		//Concatenate results
	if(arraySize <= 1)
	{
		return array;
	}
	else
	{
		int middlePoint = arraySize/2;
		int pivotValue = array[middlePoint];
		while(pivotValue == 0)
		{
			middlePoint++;
			pivotValue = array[middlePoint];
			if(middlePoint == arraySize)
			{
				middlePoint = 0;
			}
			if(middlePoint == arraySize/2)
			{
				printf("Massive failure!\n");
				int *emptyArray = 0;
				return emptyArray;
			}
		}
		//Pivot value cannot be 0 (it just makes it all easier!)
		int i;
		int lowerArrayCounter = 0;
		int higherArrayCounter = 0;
		for(i = 0; i < arraySize; i++)
		{
			if(array[i] <= pivotValue)
			{
				lowerArrayCounter++;
			}
			else
			{
				higherArrayCounter++;
			}
		}
		lowerArrayCounter--;
		//Removes pivot value
		int *lowerArray = (int *)malloc(lowerArrayCounter * sizeof(int*));
		int *higherArray = (int *)malloc(higherArrayCounter * sizeof(int*));
		i = 0;
		int lowerArrayIndex = 0;
		int higherArrayIndex = 0;
		for(i = 0; i < arraySize; i++)
		{
			if(array[i] < pivotValue)
			{
				lowerArray[lowerArrayIndex] = array[i];
				lowerArrayIndex++;
			}
			else if(array[i] > pivotValue)
			{
				higherArray[higherArrayIndex] = array[i];
				higherArrayIndex++;
			}
		}
		return concatenate(quickSort(lowerArray, lowerArrayCounter), pivotValue, quickSort(higherArray, higherArrayCounter), arraySize, lowerArrayCounter, higherArrayCounter);
	}
}

int linearElementSearch(int *array, size_t arraySize, int seekValue)
{
	int i;
	for(i = 0; i < arraySize; i++)
	{
		if(array[i] == seekValue)
		{
			printf("SeekValue found at element %d\n", i);
			return array[i];
		}
	}
	return -1;
}

void getSystemTime(double *time)
{
	struct timeval  tv;
	gettimeofday(&tv, NULL);

	*time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
    // convert tv_sec & tv_usec to millisecond     
}

int main()
{
	double preSortTime = 0;
	double postSortTime = 0;
	size_t arraySize = 10000000;
	int *myArrayPtr = generateArray(arraySize);
	int seekValue = 45;
	//fullPrintArray(myArrayPtr, arraySize);
	printf("Array Generated\n\n");
	shuffleArray(myArrayPtr, arraySize);
	//fullPrintArray(myArrayPtr, arraySize);
	printf("Array Shuffled\n\n");
	getSystemTime(&preSortTime);
	int foundValue = linearElementSearch(myArrayPtr, arraySize, seekValue);
	//myArrayPtr = quickSort(myArrayPtr, arraySize);
	getSystemTime(&postSortTime);
	//fullPrintArray(myArrayPtr, arraySize);
	printf("Value %d found in %f milliseconds\n\n", foundValue, postSortTime - preSortTime);
	free(myArrayPtr);
	return 0;
}
