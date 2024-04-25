#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/unistd.h>

#include "utilities.h"
#include "eeprom-board.h"

FILE* file;
char *file_path = "/tmp/eeprom";
struct stat buffer_data;

void EepromMcuInit()
{
    int fd;

    // Open the file with write-only mode, creating it if it doesn't exist
    fd = open(file_path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Close the file descriptor
    close(fd);

    printf("File created successfully: %s\n", file_path);

}



LmnStatus_t EepromMcuReadBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    int i = 0;
    if (stat(file_path,&buffer_data)==0)
    {
        //open file for reading
        file = fopen(file_path, "r");
        if (file == NULL)
        {
        printf("Error opening exisitng file!\n");
        return LMN_STATUS_ERROR;        
        }

        signed char c;

        while ((c= fgetc(file))!= EOF)
        {
           buffer[i] = c;
           i++;
        }

        buffer[i]='\0';  
        fclose(file);   
        return LMN_STATUS_OK;            
    }
}


LmnStatus_t EepromMcuWriteBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    
    if (stat(file_path,&buffer_data)==0){
        //open file for writing
        file = fopen(file_path, "w");
        if (file == NULL){
        printf("Error opening exisitng file!\n");
        return LMN_STATUS_ERROR;        
        }
    }
    else 
    {
        //open file for writing
        file = fopen(file_path, "w");
        if (file == NULL){
        printf("Error creating and opening file!\n");
        return LMN_STATUS_ERROR; 
        }
    }

    //Write file 
    fprintf(file, buffer);
    printf("Successful write file\n");

    //close file
    fclose(file);
    return LMN_STATUS_OK;
}

uint8_t EepromMcuFlush()
{
    if (unlink(file_path)==0){
        printf("File successfully deleted.\n");
        return 1;        
    }
    else 
    {
        printf("Error deleting file.\n");
    }
    return 0;          
    
}