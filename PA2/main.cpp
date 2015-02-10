//Tyler Longbons
//Assignment: PA2


#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "image.h"	



	int main(int argc, char* argv[]){
		if(argc != 3)
		{
		return -1;	
		}
		

		if(strcmp(argv[1],argv[2]) == 0)
		{
			//std::cout<< "Args are the same"<<std::endl;
			return -1;
		}

		std::ifstream inFile(argv[1]);


		if(readFile(inFile) == -1)
		{
			//std::cout<< "Read File Failed"<<std::endl;
			return -1;
		}
		if(processFileData() == -1)
		{
			//std::cout<< "Process file failed"<<std::endl;
			return -1;
		}

		if(processHeaderData() == -1)
		{
		//std::cout << "Process Header Failed" << std::endl;
		return -1;
		}
		if(validatePixels() == -1)
		{
			//std::cout << "Bad Pixels" << std::endl;
			return -1;
		}
		findMin();
		findAverage();
		findMax();
		
		if(rescale() == -1)
		{
			//std::cout << "Failed to rescale" << std::endl;
			return -1;
		}
		

		std::ofstream outFile(argv[2]);
		if(writeFile(outFile) == -1)
		{
			//std::cout<<"outFile failed" <<std::endl;
			return -1;
		}




		
		
	return 0;


	}