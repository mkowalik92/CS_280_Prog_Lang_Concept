/*
 *
 * srtheap.c file
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "srt.h"

void heapify(void *, size_t, size_t, int(*)(const void *, const void *));
void siftDown(void *, size_t, size_t, size_t, int(*)(const void *, const void *));
int iLeftChild(int);
int iParent(int);

void srtheap(void *base, size_t nelem, size_t size, int(*compar)(const void *, const void *))
{
  char *qb = base;
  int end;

  heapify(qb, nelem, size, compar);

  end = nelem - 1;

  while ( end > 0 )
    {
      swap(qb + size * end, qb, size);
      end = end - 1;
      siftDown(qb, 0, end, size, compar);
    }
}

// Builds the heap in array base so that largest value is at the root
void heapify(void *base, size_t nelem, size_t size, int(*compar)(const void *, const void *))
{
  char *qb = base;
  int start = iParent(nelem-1);
  while ( start >= 0 )
    {
      siftDown(qb, start, nelem - 1, size, compar);
      start = start - 1;
    }
}

void siftDown(void *base, size_t start, size_t end, size_t size, int(*compar)(const void *, const void *))
{
  int child, swaps, root = start;
  char *qb = base;
  //printf("Element 4 in index[3]= %f\n", *(TYPE *)(qb + size * 3));
  
  while ( iLeftChild(root) <= end ) //While the root has at least one child
    {
      child = iLeftChild(root); // Left child of root
      swaps = root;             // Keeps track of child to swap with
      
      if ( compar(qb + size * swaps, qb + size * child) < 0 )
	{
	  swaps = child;
	}
      if ( ((child + 1) <= end) && (compar(qb + size * swaps, qb + size * (child + 1)) < 0) )
	{
	  swaps = child + 1;
	}
      if ( swaps == root ) // The root holds the largest element
	{
	  return;
	}
      else
	{
	  swap(qb + size * root, qb + size * swaps, size);
	  root = swaps;
	}
    }
}

// Finds and returns the left child of the node passed to the function.
int iLeftChild(int node)
{
  int leftChild = (2 * node) + 1;
  return leftChild;
}

// Finds and returns the parent of the node passed to the function.
int iParent(int node)
{
  if ( node <= 0 )
    {
      printf("Error: no parent node exists\n");
      exit(0);
    }
  if ( (node == 1) || (node == 2) )
    {
      return 0;
    }
  float i = (node - 1.0) / 2.0;
  if ( i == (int)i )
    {
      return (int)i;
    }
  else
    {
      i = (node - 2.0) / 2.0;
      return (int)i;
    }
}
