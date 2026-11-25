/* 
 * check-encoding.c
 *
 * Contact: Cesar Munoz
 * Organization: NASA/Langley Research Center
 *
 * This software may be used, reproduced, and provided to others only as 
 * permitted under the terms of the agreement under which it was acquired from
 * the U.S. Government. Neither title to, nor ownership of, the software is 
 * hereby transferred. This notice shall remain on all copies of the software.
 * 
 * Copyright 2019 United States Government as represented by the Administrator
 * of the National Aeronautics and Space Administration. All Rights Reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../cpr.h"

#define INPUT_LINE_MAX_LENGTH 270

/* Reads the encoded latitude and longitude (fields 4 and 5) of a CSV line.
 * Returns 0 if the line has fewer than 5 fields, and 1 otherwise. */
static int read_encoding(const char* line, int_type* encoded_lat, int_type* encoded_lon) {
    int found = 0;
    char* tmp = strdup(line);
    const char* token = strtok(tmp, ",");      // format
    if (token != NULL) token = strtok(NULL, ","); // awb_lat
    if (token != NULL) token = strtok(NULL, ","); // awb_lon
    if (token != NULL) token = strtok(NULL, ","); // encoded latitude
    if (token != NULL) {
        *encoded_lat = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");                 // encoded longitude
        if (token != NULL) {
            *encoded_lon = (int_type) strtoul(token,NULL,16);
            found = 1;
        }
    }
    free(tmp);
    return found;
}

int main(int argc, char * argv[]){
    int result = 0; // OK
    unsigned int line_number = 0;
    FILE *original_data_file ;
    FILE *result_data_file ;
    char original_line[INPUT_LINE_MAX_LENGTH] ;
    char result_line[INPUT_LINE_MAX_LENGTH] ;
    int_type expected_encoded_lat, expected_encoded_lon;
    int_type result_encoded_lat, result_encoded_lon;

    if(argc <= 2) {
        fprintf(stderr, "Error: Missing input file names.\n");
        fprintf(stderr, "USAGE: %s <input CSV file> <result CSV file>\n", argv[0]);
        return 1;
    }

    original_data_file = fopen(argv[1], "r");
    if(original_data_file == NULL) {
        fprintf(stderr, "Error: File %s not found.\n", argv[1]);
        return 1;
    }

    result_data_file = fopen(argv[2], "r");
    if(result_data_file == NULL) {
        fprintf(stderr, "Error: File %s not found.\n", argv[2]);
        fclose(original_data_file);
        return 1;
    }

    while( fgets ( original_line, INPUT_LINE_MAX_LENGTH, original_data_file ) != NULL ) {
        line_number++;

        if ( fgets ( result_line, INPUT_LINE_MAX_LENGTH, result_data_file ) == NULL ) {
            printf("File %s has more rows than %s.\n",argv[1],argv[2]);
            result = 1; // ERROR
            break;
        }

        if ( !read_encoding(original_line, &expected_encoded_lat, &expected_encoded_lon) ) {
            printf("Error in line %d of %s: fewer than 5 fields.\n",line_number,argv[1]);
            result = 1; // ERROR
            continue;
        }

        if ( !read_encoding(result_line, &result_encoded_lat, &result_encoded_lon) ) {
            printf("Error in line %d of %s: fewer than 5 fields.\n",line_number,argv[2]);
            result = 1; // ERROR
            continue;
        }

        if(expected_encoded_lat != result_encoded_lat) {
            printf("Error in line %d: expected latitude in %s is %X but computed latitude in %s is %X.\n",line_number,argv[1],expected_encoded_lat,argv[2],result_encoded_lat);
            result=1; // ERROR
        }

        if(expected_encoded_lon != result_encoded_lon) {
            printf("Error in line %d: expected longitude in %s is %X but computed longitude in %s is %X.\n",line_number,argv[1],expected_encoded_lon,argv[2],result_encoded_lon);
            result=1; // ERROR
        }
    }

    if ( result == 0 && fgets ( result_line, INPUT_LINE_MAX_LENGTH, result_data_file ) != NULL ) {
        printf("File %s has more rows than %s.\n",argv[2],argv[1]);
        result = 1; // ERROR
    }

    fclose(original_data_file) ;
    fclose(result_data_file) ;
    return result;
}
