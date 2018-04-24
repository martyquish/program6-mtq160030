// Author: Martin Quish
// Class: CS 3377.502
// Email: mtq160030@utdallas.edu
#include <fstream>
#include <cstddef>
#include "classes.h"
#include "program6.h"


using namespace std;

bool is_initialized = false;

// These two variables are used to ensure we don't read past the last record in the file.
// 'numRecords' will be initialized when readHeader() is called.
int numRecords;
int currentRecord=0;

// The binary ifstream to be used during all read operations.
// Is initialized in binio_init()
ifstream* binfile;

// Opens 'cs3377.bin' for reading in binary
void binio_init(){
  binfile = new ifstream("cs3377.bin",ios::in|ios::binary);
  is_initialized=true;
}

// Reads one record out of the binary file and returns the BinaryFileRecord object produced
BinaryFileRecord* readRecord(){
  // If a stream has not been initialized yet, initialize one
  if(!is_initialized)
    binio_init();

  // If we have reached the end of the file, return a blank record.
  if(numRecords==currentRecord)
    return NULL;

  // Create a new record to store the read information in
  BinaryFileRecord* record = new BinaryFileRecord();

  // Read one BinaryFileRecord worth of bytes from the binary file into the record
  binfile->read((char*)record, sizeof(BinaryFileRecord));
  
  // Moving to next record
  currentRecord++;

  // Return the filled record
  return record;
}

// Reads a header from the file and returns it
BinaryFileHeader* readHeader(){
  // If a stream has not been initialized yet, initialize one
  if(!is_initialized)
    binio_init();
  
  // Create a new header object to store read information in
  BinaryFileHeader* header = new BinaryFileHeader();
  
  // Read one header worth of data from the binary file
  binfile->read((char*)header,sizeof(BinaryFileHeader));

  // Save the number of records in the file
  numRecords = header->numRecords; 

  // Return the header, which is now filled with bytes from the file.
  return header;
}
