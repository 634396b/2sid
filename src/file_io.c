#include "file_io.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>  

void readMemoryIn(uint8_t* memory){
    FILE * fp;
    int i = 0;
    char c1, c2;
    uint8_t c1_[2] = {c1, '\0'};
    uint8_t c2_[2] = {c2, '\0'};
    fp = fopen("mem_in.txt", "rt");
    printf("Reading memory in file\n");
    if(fp){
        while((c1 = fgetc(fp)) != EOF){
            if(c1 != '\n'){
                c2 = fgetc(fp);
                c1_[0] = c1;
                c2_[0] = c2;
                uint8_t f1 = ((uint8_t) strtol(c1_, NULL, 16));
                uint8_t f2 = ((uint8_t) strtol(c2_, NULL, 16));
                memory[i] = f1<<4 | f2;
                // Remove space after 2 chars
                fgetc(fp); 
                i++;
            }
        }
        fclose(fp);
    } else {
        printf("Unable to read file\n");
    }
    printf("Finished reading memory in file\n");
}

void writeMemoryOut(uint8_t* memory){
    FILE * fp;
    int i = 0;
    fp = fopen("mem_out_result.txt", "w");
    printf("Writing memory in file\n");
    if(fp){
        while (i < 2<<15){
            if(i%16 == 0 && i != 0){
                fputc('\n', fp);
                fprintf(fp,"%02x ", memory[i]);
            } else {
                fprintf(fp,"%02x ", memory[i]);
            }
            i++;
        }
        fclose(fp);
    } else {
        printf("Unable to write to file\n");
    }
    printf("Finished writing memory in file\n");
}