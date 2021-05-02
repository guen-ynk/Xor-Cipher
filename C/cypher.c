#include <stdio.h>
#include<stdlib.h>
#include <time.h>

int main(int argc, char const **argv)
{
    
    double time_spent = 0.0;
    clock_t begin = clock();

    FILE *infile = fopen(argv[1], "rb");
    FILE *keyfile = fopen(argv[2], "rb");

    char *buffer;
	long filelen;
    char *inbuffer;
	long infilelen;

	fseek(infile, 0, SEEK_END);                                     // Jump to the end of the file
	infilelen = ftell(infile);                                      // Get the current byte offset in the file
	rewind(infile); 

	fseek(keyfile, 0, SEEK_END);                                    // Jump to the end of the file
	filelen = ftell(keyfile);                                       // Get the current byte offset in the file
	rewind(keyfile); 


	inbuffer = (char *)malloc(infilelen * sizeof(char));            // Enough memory for the file
	fread(inbuffer, infilelen, 1, infile);                          // Read in the entire file
	fclose(infile);                                                 // Close the file
                     
	buffer = (char *)malloc(filelen * sizeof(char));                // Enough memory for the file
	fread(buffer, filelen, 1, keyfile);                             // Read in the entire file
	fclose(keyfile);                                                // Close the file

    time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
    printf("Time elpased is %f seconds\n", time_spent);

    
    FILE *fout = fopen(argv[3],"wb");     

    for (int i = 0; i < infilelen; ++i)
    {
    	putc(inbuffer[i] ^ buffer[i % filelen], fout);
    }
   
 
    time_spent = (double)(clock() - time_spent) / CLOCKS_PER_SEC;
    printf("Time elpased is %f seconds. %ld MB written", time_spent, ((infilelen/1024)/1024));
  
    return 0;
}

