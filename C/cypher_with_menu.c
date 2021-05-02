#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<string.h>

int main(int argc, char const **argv)
{
    int mode = -1;
    char INPUT[255];
    char INPUT2[255];
    char ext[25];

    printf("MODE SELECTION\n");
    printf("Encryptionmode: 0 | Decryptionmode: 1\n");
    printf("Enter mode: \n");
    scanf("%d", &mode);

    while(mode != 1 && mode != 0){
        printf("Enter mode again 0 or 1: ");
        scanf("%d", &mode);
    }
    
    FILE *infile;
    FILE *keyfile; 

  if(mode==1){
     printf("\n--------------------------------------------\nDecryption-mode\n");
     printf("Enter the File you used to encrypt e.g. book.pdf\n");
     scanf("%s", &INPUT);
     keyfile = fopen(INPUT, "rb");

     while(keyfile == NULL){
     printf("Err .. Enter the File you used to encrypt e.g. book.pdf\n");
     scanf("%s", &INPUT);
     keyfile = fopen(INPUT, "rb");
     }

     printf("Enter the originalfilename.key e.g. image.png.key\n");
     scanf("%s", &INPUT2);
     infile = fopen(INPUT2, "rb");

     while(infile == NULL){
     printf("Err .. Enter the originalfilename.key e.g. image.png.key\n");
     scanf("%s", &INPUT2);
     infile = fopen(INPUT2, "rb");

     }
     int ext_index = strlen(INPUT2)-4;
     memcpy(ext, &INPUT2[0], ext_index);
     ext[ext_index] = '\0';
     printf("\noriginal file: %s", ext);

    }
     if(mode==0){

     printf("\n--------------------------------------------\nEncryption-mode\n");
     printf("Enter the File you want to encrypt e.g. image.png\n");
     scanf("%s", &INPUT);
     infile = fopen(INPUT, "rb");

     while(infile == NULL){
     printf("Err .. Enter the File you want to encrypt e.g. image.png\n");
     scanf("%s", &INPUT);
     infile = fopen(INPUT, "rb");
     }

     printf("Enter the File you to transform the 1. into  e.g. book.pdf\n");
     scanf("%s", &INPUT2);
    keyfile = fopen(INPUT2, "rb");

     while(keyfile == NULL){
     printf("Err .. Enter the File you to transform the 1. into  e.g. book.pdf\n");
     scanf("%s", &INPUT2);
     keyfile = fopen(INPUT2, "rb");

     }
     snprintf(ext, sizeof(ext), "%s.key", INPUT);
     printf("\nkey file: %s\n", ext);

    }


    double time_spent = 0.0;
    clock_t begin = clock();

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

    
    FILE *fout = fopen(ext,"wb");     

    for (int i = 0; i < infilelen; ++i)
    {
    	putc(inbuffer[i] ^ buffer[i % filelen], fout);
    }
   
 
    time_spent = (double)(clock() - time_spent) / CLOCKS_PER_SEC;
    printf("Time elpased is %f seconds. %ld MB written", time_spent, ((infilelen/1024)/1024));
  
    return 0;
}

