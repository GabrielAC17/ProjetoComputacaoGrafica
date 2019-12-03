/*-----------------------------------------------------------------------------
   ERROR.CPP - Continuum 3D Engine - Error Management

Compiler: Visual C++ 6.0 with Source Control
Created:  26-March-2001
-----------------------------------------------------------------------------*/
#include "error.h"

/*-----------------------------------------------------------------------------
                              cError::cError()
-----------------------------------------------------------------------------*/
cError::cError(void)
{
// initialize variables
memset(&fileName, 0, sizeof(fileName));
memset(err, 0, sizeof(err));
memset(warn, 0, sizeof(warn));
numErr          = 0;
numWarn         = 0;
numErrOverflow  = 0;
numWarnOverflow = 0;
isInit          = 0;
}
/*-----------------------------------------------------------------------------
                               cError::init()
-----------------------------------------------------------------------------*/
void cError::init(char *parmFileName)
{
// save file name
strcpy(fileName, parmFileName);
isInit = 1;
}
/*-----------------------------------------------------------------------------
                               cError::error()
-----------------------------------------------------------------------------*/
int cError::error(const char *srcFile, dword srcLine, const char *msg, dword codeAux)
{
int i;

// extract path from source file name
if( srcFile == NULL )
   srcFile = "Unknown";
else
   srcFile = this->strFileFromPath((char*)srcFile);

// check if already on list
for(i=0; i < numErr; i++)
   {
   // check if the same file and line
   if( (srcLine == err[i].srcLine) && (strcmp(srcFile, err[i].srcFile) == 0) )
      break;
   }
if( i < numErr )
   {
   // increment error counter
   err[i].count++;
   }
else if( numErr < MAX_ERRORINFO )
   {
   // insert error info in a new slot
   if( msg == NULL )
      msg = "";
   strncpy(err[numErr].srcFile, srcFile, sizeof(err[numErr].srcFile)-1);
   strncpy(err[numErr].msg, msg, sizeof(err[numErr].msg)-1);
   err[numErr].srcLine = srcLine;
   err[numErr].codeAux = codeAux;
   err[numErr].count   = 1;
   numErr++;
   }
else // an error must be discarded
   numErrOverflow++;

return 0;
}
/*-----------------------------------------------------------------------------
                              cError::warning()
-----------------------------------------------------------------------------*/
int cError::warning(const char *srcFile, dword srcLine, const char *msg, dword codeAux)
{
int i;

// extract path from source file name
if( srcFile == NULL )
   srcFile = "Unknown";
else
   srcFile = this->strFileFromPath((char*)srcFile);

// check if already on list
for(i=0; i < numWarn; i++)
   {
   // check if the same file and line
   if( (srcLine == warn[i].srcLine) && (strcmp(srcFile, warn[i].srcFile) == 0) )
      break;
   }
if( i < numWarn )
   {
   // increment warning counter
   warn[i].count++;
   }
else if( numWarn < MAX_WARNINGINFO )
   {
   // insert warning info in a new slot
   if( msg == NULL )
      msg = "";
   strncpy(warn[numWarn].srcFile, srcFile, sizeof(warn[numWarn].srcFile)-1);
   strncpy(warn[numWarn].msg, msg, sizeof(warn[numWarn].msg)-1);
   warn[numWarn].srcLine = srcLine;
   warn[numWarn].codeAux = codeAux;
   warn[numWarn].count   = 1;
   numWarn++;
   }
else // a warning must be discarded
   numWarnOverflow++;

return 0;
}
/*-----------------------------------------------------------------------------
                               cError::close()
-----------------------------------------------------------------------------*/
void cError::close(void)
{
// if not initialized, return
if( !isInit )
   return;
   
// save log if necessary
if( (numErr > 0) || (numWarn > 0) )
   {
   // write log file
   this->saveLog();
   }
isInit = 0;
}
/*-----------------------------------------------------------------------------
                              cError::~cError()
-----------------------------------------------------------------------------*/
cError::~cError()
{
this->close();
}
/*-----------------------------------------------------------------------------
                              cError::saveLog()
-----------------------------------------------------------------------------*/
int cError::saveLog(void)
{
FILE *hFile;
int  i;

// create log file
if( (hFile=fopen(fileName,"wt")) == NULL )
   return 0;

// write header
fprintf(hFile, "----------------------------------------------------------------------\n");
fprintf(hFile, "                   Application Error and/or Warning Log\n");
fprintf(hFile, "----------------------------------------------------------------------\n");
fprintf(hFile, "Number of Errors:   %d\n",numErr);
fprintf(hFile, "Number of Warnings: %d\n",numWarn);
fprintf(hFile, "Number of Discarded Errors:   %d\n",numErrOverflow);
fprintf(hFile, "Number of Discarded Warnings: %d\n\n\n",numWarnOverflow);

// write errors
if( numErr > 0 )
   {
   fprintf(hFile, "----------------------------------------------------------------------\n");
   fprintf(hFile, "                               Errors\n");
   fprintf(hFile, "----------------------------------------------------------------------\n");
   for(i=0; i<numErr; i++)
      {
      if( err[i].count == 1 )
         fprintf(hFile, "File %s, Line %d\n   %s (code=%d)\n\n", err[i].srcFile, err[i].srcLine, err[i].msg, err[i].codeAux);
      else
         fprintf(hFile, "File %s, Line %d (%d occurrences)\n   %s (code=%d)\n\n", err[i].srcFile, err[i].srcLine, err[i].count, err[i].msg, err[i].codeAux);
      }
   }

// write warnings
if( numWarn > 0 )
   {
   fprintf(hFile, "----------------------------------------------------------------------\n");
   fprintf(hFile, "                              Warnings\n");
   fprintf(hFile, "----------------------------------------------------------------------\n");
   for(i=0; i<numWarn; i++)
      {
      if( warn[i].count == 1 )
         fprintf(hFile, "File %s, Line %d\n   %s (code=%d)\n\n", warn[i].srcFile, warn[i].srcLine, warn[i].msg, warn[i].codeAux);
      else
         fprintf(hFile, "File %s, Line %d (%d occurrences)\n   %s (code=%d)\n\n", warn[i].srcFile, warn[i].srcLine, warn[i].count, warn[i].msg, warn[i].codeAux);
      }
   }

// close file
fclose(hFile);

return 1;
}
/*-----------------------------------------------------------------------------
                         cError::strFileFromPath()
-----------------------------------------------------------------------------*/
char *cError::strFileFromPath(char *fileName)
{
int i;

// search for a path separator, and return
for(i=strlen(fileName)-1; i > 0; i--)
   {
   if( (fileName[i] == '/') || (fileName[i] == '\\') || (fileName[i] == ':') )
      {
      i++;
      break;
      }
   }

return &fileName[i];
}

