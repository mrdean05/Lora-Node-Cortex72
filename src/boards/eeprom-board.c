#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>
#include <sys/unistd.h>

#include "utilities.h"
#include "eeprom-board.h"

FILE* file;
char *file_path = "/home/pp/eeprom";
struct stat buffer_data;

void EepromMcuInit()
{

}



LmnStatus_t EepromMcuReadBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    int i = 0;
    printf("------------------------------------------------------------------\n");
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
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    
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
    return 1;          
    
}