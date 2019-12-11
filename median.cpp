/**************************
** TDDD56 Lab 3
***************************
** Author:
** August Ernstsson
**************************/

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <iterator>

#include <skepu2.hpp>

#include "support.h"

unsigned char median_kernel(int ox, int oy, size_t stride, const unsigned char *image, size_t elemPerPx)
{
	int pixelNum = (2*ox+1)*(2*oy+1);
    int leftNum = 0;
    int old_leftNum = 0; 
    int j = 0;
    int start = 0;
    int end = pixelNum - 1;
    int left, right;
    
    unsigned char array[10000];
    unsigned char temp, median,tmp;
	
	unsigned char tmp1, tmp2; 
	
	int p;
	
    for (int y = -oy; y <= oy; ++y)
		for (int x = -ox; x <= ox; x += elemPerPx)
			array[j++] = image[y*(int)stride+x]; 
	
	
	// START QUICKSORT
	
	// source: https://www.geeksforgeeks.org/iterative-quick-sort/
	
	
		// Create an auxiliary stack 
		int l=0, h=pixelNum;
		
		int stack[10000]; 
	  
		// initialize top of stack 
		int top = -1; 
	  
		// push initial values of l and h to stack 
		stack[++top] = l; 
		stack[++top] = h; 
	  
		// Keep popping from stack while is not empty 
		while (top >= 0) { 
			// Pop h and l 
			h = stack[top--]; 
			l = stack[top--]; 
	  
			// Set pivot element at its correct position 
			// in sorted array 

			int x = array[h]; 
			int i = (l - 1); 
		  
			for (int jpart = l; jpart <= h - 1; jpart++) { 
				if (array[jpart] <= x) { 
					i++; 
					tmp1 = array[i]; 
					array[i] = array[jpart]; 
					array[jpart] = tmp1; 
				} 
			} 
				
			tmp2 = array[i + 1]; 
			array[i + 1] = array[h]; 
			array[h] = tmp2; 
			
			p = (i + 1); 
			
			// If there are elements on left side of pivot, 
			// then push left side to stack 
			if (p - 1 > l) { 
				stack[++top] = l; 
				stack[++top] = p - 1; 
			} 
	  
			// If there are elements on right side of pivot, 
			// then push right side to stack 
			if (p + 1 < h) { 
				stack[++top] = p + 1; 
				stack[++top] = h; 
			} 
		}
				
	// END QUICKSORT

    if(pixelNum%2==0)
        return((array[pixelNum/2] + array[pixelNum/2 - 1]) / 2.0);
    else
        return array[pixelNum/2];

}


int main(int argc, char* argv[])
{
	LodePNGColorType colorType = LCT_RGB;
	
	if (argc < 5)
	{
		std::cout << "Usage: " << argv[0] << "input output radius [backend]\n";
		exit(1);
	}
	
	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];
	const int radius = atoi(argv[3]);
	auto spec = skepu2::BackendSpec{skepu2::Backend::typeFromString(argv[4])};
	
	// Create the full path for writing the image.
	std::stringstream ss;
	ss << (2 * radius + 1) << "x" << (2 * radius + 1);
	std::string outputFileNamePad = outputFileName + ss.str() + "-median.png";
		
	// Read the padded image into a matrix. Create the output matrix without padding.
	ImageInfo imageInfo; 
	skepu2::Matrix<unsigned char> inputMatrix = ReadAndPadPngFileToMatrix(inputFileName, radius, colorType, imageInfo);
	skepu2::Matrix<unsigned char> outputMatrix(imageInfo.height, imageInfo.width * imageInfo.elementsPerPixel, 120);
	
	// Skeleton instance
	auto calculateMedian = skepu2::MapOverlap(median_kernel);
	calculateMedian.setBackend(spec);
	calculateMedian.setOverlap(radius, radius  * imageInfo.elementsPerPixel);
	
	auto timeTaken = skepu2::benchmark::measureExecTime([&]
	{
		calculateMedian(outputMatrix, inputMatrix, imageInfo.elementsPerPixel);
	});
	
	WritePngFileMatrix(outputMatrix, outputFileNamePad, colorType, imageInfo);
	
	std::cout << "Time: " << (timeTaken.count() / 10E6) << "\n";
	
	return 0;
}


