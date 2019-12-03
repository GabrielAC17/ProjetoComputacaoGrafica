/*-----------------------------------------------------------------------------
   ERROR.H - Error Management (Header file)

Created:  26-March-2001
-----------------------------------------------------------------------------*/
#ifndef _ERROR_H
#define _ERROR_H 1

#include <stdio.h>
#include <string.h>
#include "types.h"


/*-----------------------------------------------------------------------------
                               Constants
-----------------------------------------------------------------------------*/
// Generic values
#define MAX_ERRORINFO          32
#define MAX_WARNINGINFO        32
#define MAX_SRCFILE            32
#define MAX_MSGLEN            128


// macros for setting errors and warnings
#define errorSet(X,Y)     error.error(__FILE__,__LINE__,X,Y)
#define warningSet(X,Y)   error.warning(__FILE__,__LINE__,X,Y)
 

/*-----------------------------------------------------------------------------
                             Data Structures
-----------------------------------------------------------------------------*/
// error information 
typedef struct {
   char  msg[MAX_MSGLEN];              // error message
   char  srcFile[MAX_SRCFILE];         // source file name
   dword srcLine;                      // error line in source file
   dword codeAux;                      // auxiliar error code
   dword count;                        // number of occurences of this error
   } tErrorInfo;


/*-----------------------------------------------------------------------------
                                 cError
-----------------------------------------------------------------------------*/
// Class for handle errors 
class cError {
private:
   tErrorInfo err[MAX_ERRORINFO];      // last error codes
   tErrorInfo warn[MAX_WARNINGINFO];   // last warning codes
   char str[MAX_MSGLEN<<1];            // buffer to build output messages
   char fileName[512];                 // log file name
   int  numErr;                        // number of elements in err[]
   int  numWarn;                       // number of elements in warn[]
   int  numErrOverflow;                // number of errors discarded
   int  numWarnOverflow;               // number of warnings discarded
   int  isInit;                        // class is initialized
   
public:
        cError(void);
   void init(char *parmFileName);
   int  error(const char *srcFile, dword srcLine, const char *msg, dword codeAux);
   int  warning(const char *srcFile, dword srcLine, const char *msg, dword codeAux);
   void close(void);
        ~cError();

private:
   int  saveLog(void);
   char *strFileFromPath(char *fileName);
   };

/*-----------------------------------------------------------------------------
                            Global Variables
-----------------------------------------------------------------------------*/
extern cError error;                   // Object to handle errors


#endif
