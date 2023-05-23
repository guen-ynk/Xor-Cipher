#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define BUFFER_SIZE 8192  // Adjust the buffer size based on system performance

int main(int argc, char const **argv)
{
    clock_t begin = clock();

    FILE *infile = fopen(argv[1], "rb");
    FILE *keyfile = fopen(argv[2], "rb");

    if (infile == NULL || keyfile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fseek(infile, 0, SEEK_END);
    long infilelen = ftell(infile);
    rewind(infile);

    fseek(keyfile, 0, SEEK_END);
    long filelen = ftell(keyfile);
    rewind(keyfile);

    char *inbuffer = (char *)malloc(infilelen);
    char *buffer = (char *)malloc(filelen);

    fread(inbuffer, sizeof(char), infilelen, infile);
    fread(buffer, sizeof(char), filelen, keyfile);

    fclose(infile);
    fclose(keyfile);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elapsed for reading files: %f seconds\n", time_spent);

    FILE *fout = fopen(argv[3], "wb");

    if (fout == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // Parallelize the XOR operation using OpenMP
    #pragma omp parallel for
    for (long i = 0; i < infilelen; i += BUFFER_SIZE)
    {
        long chunkSize = (i + BUFFER_SIZE > infilelen) ? (infilelen - i) : BUFFER_SIZE;
        for (long j = 0; j < chunkSize; ++j)
        {
            inbuffer[i + j] ^= buffer[(i + j) % filelen];
        }
    }

    fwrite(inbuffer, sizeof(char), infilelen, fout);
    fclose(fout);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    long fileMB = infilelen / (1024 * 1024);
    printf("Time elapsed: %f seconds. %ld MB written.\n", time_spent, fileMB);

    free(inbuffer);
    free(buffer);

    return 0;
}
