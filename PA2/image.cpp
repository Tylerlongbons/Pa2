//Tyler Longbons

#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include "image.h"


int height;
int width;
int MAX_PIXEL_VAL;
int total_Num_Pixels;
int min;
int max;
double average;

//Where we are storing the file
std::vector < std::vector < std::string > > origFileData;
std::vector <std::string> pixels;
std::vector <int> scaledPixels;



int validateHeader(std::string line)
{
	for(unsigned int i = 0; i < 3; i++)
	{
		char c = line[i];
		if(i == 0)
		{
			if(c != 'P')
			{
				return -1;
			}
		}
		else if(i == 1)
		{
			if(c != '2')
			{
				return -1;
			}	
		}else
		{
			if(isspace(c) && c != '#')
			{
				return -1;
			}
		}
	}
		return 0;
}


//Use for Debugging
void printOrigFinalData()
{
		for(unsigned int i = 0; i < origFileData.size();i++)
		{
			std::cout<<"Line: " << i << std::endl;
				for(unsigned int j = 0; j < origFileData[i].size();j++)
				{

					std::cout<<"MyData: " << origFileData[i][j] <<std::endl;
				}
		}
}

//Use for debugging
void printPixels()
{
		for(unsigned int i = 0;i < pixels.size();i++)
		{
			std::cout<<"Pixels: " << pixels[i] << std::endl;
		}
}


int getWidth()
{
	width = atoi(pixels[0].c_str());
	if(width <= 0)
	{
		return -1;
	}
	return 0;
}

int getHeight()
{
	height = atoi(pixels[1].c_str());
	if(height <= 0)
	{
		return -1;
	}
	return 0;
}
int getMaxPixelVal()
{
	MAX_PIXEL_VAL = atoi(pixels[2].c_str());
	if(MAX_PIXEL_VAL < 0  || MAX_PIXEL_VAL > 256)
	{
		return -1;
	}
	return 0;
}

int processHeaderData()
{
	if(getWidth() == -1)
	{
		return -1;
	}
	if(getHeight() == -1)
	{
		return -1;
	}
	if(getMaxPixelVal() == -1)
	{
		return -1;
	}


	return 0;
}



bool isTokenNumber(std::string token)
{
	bool isNumber = true;
	unsigned int i         = 0;
	while(isNumber && i < token.length())
	{
		char c 	  = token[i];
		if(isdigit(c) == 0)
		{
			isNumber = false;
		}
		i++;
	}
	return isNumber;
}

bool isTokenComment(std::string token)
{
	int found = token.find("#");
	if(found == -1)
	{
		return false;
	}else
	{
		return true;
	}
}

std::string getCommentNumber(std::string token)
{
		int found                = token.find("#");
		std::string commentVal   = "-1";
		if (found != -1)
		{
			if(found > 0)
			{
				commentVal       = token.substr(0, found);
			}
		}
	return commentVal;
}


int processFileData()
{


	for(unsigned int i = 0; i < origFileData.size();i++)
		{
				for(unsigned int j = 0; j < origFileData[i].size();j++)
				{
					if(i == 0 && j == 0)
					{	
						if(isTokenComment(origFileData[i][j]) == true)
						{
							if(origFileData.size() == 1)
							{
								return -1;
							}
							break;
						}

					}else
					{
						if(isTokenNumber(origFileData[i][j]) == true)
						{
							pixels.push_back(origFileData[i][j]);
						}else if(isTokenComment(origFileData[i][j]) == true)
						{
							std::string commentVal = getCommentNumber(origFileData[i][j]);
								if(commentVal != "-1")
								{
									pixels.push_back(commentVal);
									break;
								}else
								{
									break;
								}
						}else
						{
							return -1;
						}
					}	
				}
		}


	return 0;
}


int readFile(std::istream& inFile)

{
	
	if(!inFile)
	{
		return -1;
	}
	int lineCount = 0;
	std::string line;
	//Read each line primarily to make parsing comments easier
	while(getline(inFile, line))
	{
		if(lineCount == 0)
		{
			if(validateHeader(line) == -1)
			{
				return -1;
			}

		}
		std::vector<std::string> row;
		//std::cout << "Line: "<< line << std::endl;

		std::istringstream lineStream(line);
		std::string token;

		//break line into tokens to make sure we are 
		//getting valid entries 
		while(lineStream >> token)
		{
			row.push_back(token);
		}
		
		origFileData.push_back(row);
		lineCount++;
	}
	

		return 0;
}



int validatePixels()
{
	total_Num_Pixels = width * height;
	int actualNumPixels = 0;
	if(MAX_PIXEL_VAL == 256)
	{
		MAX_PIXEL_VAL = 255;
	}

	for(unsigned int i = 3; i < pixels.size(); i++)
	{
		int pixel = atoi(pixels[i].c_str()); 
		if(pixel <= MAX_PIXEL_VAL && pixel >= 0)
		{
			actualNumPixels++;
		}else
		{
			return -1;
		}
	}

		if(total_Num_Pixels != actualNumPixels)
		{
			return -1;
		}

		return 0;
}



int findMax()
{
	max = 0;

	for(unsigned int i = 3; i < pixels.size(); i++)
	{
		int pixel = atoi(pixels[i].c_str()); 
		if(pixel > max)
		{
			max = pixel;
		}
	}
	return 0;
}



int findMin()
{
	min = 255;

	for(unsigned int i = 3; i < pixels.size(); i++)
	{
		int pixel = atoi(pixels[i].c_str()); 
		if(pixel < min)
		{
			min = pixel;
		}
	}
	return 0;

}


int findAverage()
{
	average = 0;

	for(unsigned int i = 3; i < pixels.size(); i++)
	{
		int pixel = atoi(pixels[i].c_str()); 
		average += pixel;
	}
	average /= (total_Num_Pixels);
	return 0;
}


//Used for Debugging;
void printNewPixels()
{
	for(unsigned int i = 0; i < scaledPixels.size();i++)
	{
		std::cout<< "Pixel: " << scaledPixels[i] <<std::endl;
	}
}

int rescale()
{

for(unsigned int i = 3; i < pixels.size(); i++)
{
	int pixel = atoi(pixels[i].c_str());
	double pix = pixel - min;
	double den = max   - min;
	if(den == 0)
	{
		return -1;
	}
	double newPix = (255.0 * pix) / den;
	int newPixel = round(newPix);
	
	scaledPixels.push_back(newPixel);
}

return 0;

}


int writeFile(std::ostream& outFile)
{
	if(!outFile)
	{
		return -1;
	}

	outFile << "P2" <<std::endl;
	outFile << width << " " << height <<std::endl;
	outFile << "255" << std::endl;
	
	int colCount = 0;
	for(unsigned int i = 0; i < scaledPixels.size(); i++)
	{
		if(colCount == 19)
		{
			colCount = 0;
			outFile << scaledPixels[i] << std::endl;
		}else
		{
			outFile << scaledPixels[i] << " " ;
			colCount++;
		}
		
	}
	
	return 0;
}