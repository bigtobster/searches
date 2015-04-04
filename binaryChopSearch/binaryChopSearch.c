#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
   
void shuffleArray(int *array, int n)
{
    if (n > 1) 
    {
        int i;
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

int * generateArray(int arraySize)
{
	int n = arraySize;
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

int * quickSort(int *array, int arraySize)
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
		//printf("arraySize: %d\n", arraySize);
		//getchar();
		int middlePoint = arraySize/2;
		//int originalMiddlePoint = middlePoint;
		int pivotValue = array[middlePoint];
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

int * splitArray(int *array, int startPoint, int endPoint)
{
	int *splitArray = (int *)malloc(((endPoint-startPoint)+1) * sizeof(int*));
	int i;
	for(i = 0; i <= endPoint - startPoint; i++)
	{
		splitArray[i] = array[startPoint + i];
	}
	return splitArray;
}

int binaryChopSearch(int *array, int startIndex, int endIndex, int seekValue)
{
	//printf("Entering Binary Chop\n");
	//printf("seekValue: %d\n", seekValue);
	//printf("startIndex: %d\n", startIndex);
	//printf("middleIndex: %d\n", (startIndex + ((endIndex-startIndex)/2)));
	//printf("endIndex: %d\n", endIndex);
	//printf("array[(startIndex + (endIndex-startIndex)]: %d\n\n", array[(startIndex + ((endIndex-startIndex)/2))]);
	//getchar();
	if(seekValue == array[(startIndex + ((endIndex-startIndex)/2))])
	{
		return array[(startIndex + ((endIndex-startIndex)/2))];
	}
	else if(seekValue < array[(startIndex + ((endIndex-startIndex)/2))])
	{
		int foundValue = binaryChopSearch(array, startIndex, startIndex + ((endIndex-startIndex)/2), seekValue);
		return foundValue;
	}
	else
	{
		int foundValue = binaryChopSearch(array, (startIndex + ((endIndex-startIndex)/2))+1, endIndex, seekValue);
		return foundValue;
	}
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
	int arraySize = 10000000;
	int *myArrayPtr = generateArray(arraySize);
	int seekValue = 45;
	//fullPrintArray(myArrayPtr, arraySize);
	printf("Array Generated\n\n");
	//printf("MAIN arraySize: %d", arraySize);
	shuffleArray(myArrayPtr, arraySize);
	//fullPrintArray(myArrayPtr, arraySize);
	printf("Array Shuffled\n\n");
	getSystemTime(&preSortTime);
	int *mySortedArray = quickSort(myArrayPtr, arraySize);
	getSystemTime(&postSortTime);
	int foundValue = binaryChopSearch(mySortedArray, 0, arraySize-1, seekValue);
	//fullPrintArray(mySortedArray, arraySize);
	printf("Array Sorted\n");
	printf("Value %d found in %f milliseconds\n\n", foundValue, postSortTime - preSortTime);
	free(myArrayPtr);
	//free(mySortedArray);
	return 0;
}
