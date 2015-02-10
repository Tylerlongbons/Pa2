#ifndef IMAGE_H
#define IMAGE_H
//Tyler Longbons


int readFile(std::istream& inFile);
int findMax();
int findMin();
int findAverage();
int writeFile(std::ostream& outFile);
void resize();
void printOrigFinalData();
void printPixels();
bool isTokenNumber(std::string token);
bool isTokenComment(std::string token);
int processHeaderData();
int processFileData();
int validateHeader(std::string line);
int getMaxPixelVal();
int getWidth();
int getHeight();
int validatePixels();
int rescale();
void printNewPixels();




#endif