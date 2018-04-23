#ifndef _PROGRAM_6_CLASSES_
#define _PROGRAM_6_CLASSES_

// For system types
#include <stdint.h>

// The class definition for binary file headers
class BinaryFileHeader{
 public:  
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

/*
 * Each record buffer is a fixed length.
 * This length is set to the value of
 * maxRecordStringLength
 */
static const int maxRecordStringLength = 25;

// The class definition for a binary file record
class BinaryFileRecord{
 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};


#endif
