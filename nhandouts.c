
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//// Spartrekus
//// GNU: nhandouts for Unimark / Unibeam universal documents
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}


char *fbasename(char *name)
{
  //char *name;
  char *base = name;
  while (*name)
    {
      if (*name++ == '/')
	{
	  base = name;
	}
    }
  return (base);
}




/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}





#include <time.h>
char *strtimestamp()
{
      long t;
      struct tm *ltime;
      time(&t);
      ltime=localtime(&t);
      char charo[50];  int fooi ; 
      fooi = snprintf( charo, 50 , "%04d%02d%02d%02d%02d%02d",
	1900 + ltime->tm_year, ltime->tm_mon +1 , ltime->tm_mday, 
	ltime->tm_hour, ltime->tm_min, ltime->tm_sec 
	);
    size_t siz = sizeof charo ; 
    char *r = malloc( sizeof charo );
    return r ? memcpy(r, charo, siz ) : NULL;
}








///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
char thelineout[PATH_MAX];
int  thelinepos = 1;
int  picpos = 1;
void naddtohandout(  char *thefile , char *theitem )  //thefile is not used.
{
    FILE *fpout;  
    int fooi; 
    char charo[PATH_MAX];

    if ( picpos == 1 )
    {
       strncpy( thelineout, theitem  , PATH_MAX );
       picpos = 2;
    }
    else if ( picpos == 2 )
    {
      printf( "!clr\n" );
      printf( "> Results\n" );
      printf( "!figab{%s}{%s}\n", fbasename( thelineout) , fbasename( theitem ) );
      printf( "!info{%s}{%s}\n", fbasename(  thelineout) , fbasename( theitem ) );
      printf( "\n");
      printf( "\n");
      strncpy( thelineout, "" , PATH_MAX );
      picpos = 1;
    }
}



/////////////////////////////////
int main( int argc, char *argv[])
{
    int i ;  
    strncpy( thelineout , "", PATH_MAX );

    if ( argc >= 2)
    {
        for( i = 1 ; i < argc ; i++) 
        {
           if ( fexist( argv[ i ] ) == 1 )
           {
	      //printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
              naddtohandout( "dirfig.lst" , argv[ i ] ) ;
           }
        }
       return 0;
    }

    printf( "-Unimark: nhandouts for beamer -\n" );
    printf( "  Usage: nhandouts file1.png file2.png (and so on) \n" );
    printf( "\n" );

    return 0;
}





