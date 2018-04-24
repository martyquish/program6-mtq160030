// Author: Martin Quish
// Class: CS 3377.502
// Email: mtq160030@utdallas.edu

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstddef>

#include "cdk.h"
#include "program6.h"
#include "classes.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

// Functions for writing binary file data to the CDK matrix
int writeHeaderToMatrix(CDKMATRIX*); // Writes the header info to the first row and returns the number of records
void writeRecordsToMatrix(CDKMATRIX*, int); // Writes the given number of records to the matrix

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  // Write the header info to the matrix and get the number of records from the header
  int numRecords = writeHeaderToMatrix(myMatrix);
  // Write the records to the matrix
  writeRecordsToMatrix(myMatrix, numRecords);
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}

/*
 * This function writes the header file to the first row of the CDK matrix.
 * After doing this, it returns the number of records in the binary file (this number is found in the parsed header file)
 */
int writeHeaderToMatrix(CDKMATRIX* matrix){
  BinaryFileHeader* header = readHeader();
  
  // Create a blank stringstream to be used for formatting text.
  stringstream stream;
  
  // Convert the magic number to its hexadecimal representation in string form.
  stream << "Magic: 0x" << hex << header->magicNumber;

  // Sets cell 1,1 to the char* version of the above stream
  setCDKMatrixCell(matrix, 1, 1, stream.str().c_str());
  
  // Clear the stream for reuse
  stream.str("");
  
  // Convert the version to a readable string
  stream << "Version: " << header->versionNumber;
  // Set cell 1,2 to the version
  setCDKMatrixCell(matrix, 1, 2, stream.str().c_str());
  
  // Again, clear stream for reuse
  stream.str("");

  // Convert the number of records to a readable string
  stream << "Number of Records: " << header->numRecords;
  // Set cell 1,3 to the number of records
  setCDKMatrixCell(matrix, 1, 3, stream.str().c_str());
  return (int)header->numRecords;
}

// Writes numRecords records to the CDK matrix.
void writeRecordsToMatrix(CDKMATRIX* matrix, int numRecords){
  // Attempt to read the first record in the file
  BinaryFileRecord* currentRecord = readRecord();
  // Begin with row 2 (row 1 contains header info)
  int row=2;
  
  // Create empty stringstream for string conversion
  stringstream stream;
  
  // Iterate through the number of records
  for(int i=0; i<numRecords; i++){
    // If the current record read returned null, there was a read error. Exit the loop and don't display any more information on CDK matrix
    // We should only read a maximum of 4 records, so break if the current record is past the 4th record
    if(currentRecord==NULL || i>3) break;


    // Get the length of the record's string in printable string format using stringstream
    stream << "StrLength: "  << (int)currentRecord->strLength;
    // Put the string length in the first column
    setCDKMatrixCell(matrix, row, 1, stream.str().c_str());
    // Reset the stream for the next entry
    stream.str("");
    
    // Set the second column of the current row to the value of the record
    setCDKMatrixCell(matrix, row, 2, currentRecord->stringBuffer);
    
    // Move on to the next row
    row++;

    // Read the next record
    currentRecord=readRecord();
  }
  
}
