/* 
 * decode.c
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
#include "../../cpr.h"

#define INPUT_LINE_MAX_LENGTH 170

#define __usage_str__ \
  "USAGE: this program expect as argument the name of an CSV file.\n"\
  "       Each line of the file must start with the following fields:\n"\
  "        1) even latitude in degrees (double),\n"\
  "        2) even longitude in degrees (double),\n"\
  "        3) even latitude as AWB (unsigned int, hexadecimal),\n"\
  "        4) even longitude as AWB (unsigned int, hexadecimal),\n"\
  "        5) encoded even latitude [YZ] (unsigned int, hexadecimal),\n"\
  "        6) encoded even longitude [XZ] (unsigned int, hexadecimal),\n"\
  "        7) odd latitude in degrees (double),\n"\
  "        8) odd longitude in degrees (double),\n"\
  "        9) odd latitude as AWB (unsigned int, hexadecimal),\n"\
  "       10) odd longitude as AWB (unsigned int, hexadecimal),\n"\
  "       11) encoded odd latitude [YZ] (unsigned int, hexadecimal),\n"\
  "       12) encoded odd longitude [XZ] (unsigned int, hexadecimal),\n\n"\
  "       For each line, it prints in the standard output the following information:\n"\
  "        1) even latitude in degrees (double),\n"\
  "        2) even longitude in degrees (double),\n"\
  "        3) even latitude as AWB (unsigned int, hexadecimal),\n"\
  "        4) even longitude as AWB (unsigned int, hexadecimal),\n"\
  "        5) encoded even latitude [YZ] (unsigned int, hexadecimal),\n"\
  "        6) encoded even longitude [XZ] (unsigned int, hexadecimal),\n"\
  "        7) recovered latitude in degrees (double) decoded with i=0,\n"\
  "        8) recovered longitude in degrees (double) decoded with i=0,\n"\
  "        9) odd latitude in degrees (double),\n"\
  "       10) odd longitude in degrees (double),\n"\
  "       11) odd latitude as AWB (unsigned int, hexadecimal),\n"\
  "       12) odd longitude as AWB (unsigned int, hexadecimal),\n"\
  "       13) encoded odd latitude [YZ] (unsigned int, hexadecimal),\n"\
  "       14) encoded odd longitude [XZ] (unsigned int, hexadecimal),\n"\
  "       15) recovered latitude in degrees (double) decoded with i=1,\n"\
  "       16) recovered longitude in degrees (double) decoded with i=1,\n"

int main(int argc, char * argv[]){
    int i;
    FILE *fp ;
    char line[INPUT_LINE_MAX_LENGTH] ;
    const char* token = NULL;
    int_type awb_evn_lat, awb_evn_lon;
    int_type awb_odd_lat, awb_odd_lon;
    int_type enc_evn_lat, enc_evn_lon;
    int_type enc_odd_lat, enc_odd_lon;
    double deg_evn_lat, deg_evn_lon;
    double deg_odd_lat, deg_odd_lon;

    if(argc <= 1) {
        fprintf(stderr, "Error: Missing input file name.\n");
        fprintf(stderr, __usage_str__);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "Error: File %s not found.\n", argv[1]);
        return 1;
    }

    char* tmp = NULL;
    while( fgets ( line, INPUT_LINE_MAX_LENGTH, fp ) != NULL ) {
        tmp = strdup(line);

        token = strtok(tmp, ",");
        deg_evn_lat = atof(token);
        token = strtok(NULL, ",");
        deg_evn_lon = atof(token);
        token = strtok(NULL, ",");
        awb_evn_lat = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        awb_evn_lon = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        enc_evn_lat = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        enc_evn_lon = (int_type) strtoul(token,NULL,16);

        token = strtok(NULL, ",");
        deg_odd_lat = atof(token);
        token = strtok(NULL, ",");
        deg_odd_lon = atof(token);
        token = strtok(NULL, ",");
        awb_odd_lat = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        awb_odd_lon = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        enc_odd_lat = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        enc_odd_lon = (int_type) strtoul(token,NULL,16);

        free(tmp);

        struct message msg0 = { 0 , enc_evn_lat, enc_evn_lon };
        struct message msg1 = { 1 , enc_odd_lat, enc_odd_lon };

        struct recovered_position rpos0 = global_dec(0, msg0, msg1);
        struct recovered_position rpos1 = global_dec(1, msg0, msg1);

        printf("%.20f,%.20f,%X,%X,%X,%X,%.20f,%.20f,%.20f,%.20f,%X,%X,%X,%X,%.20f,%.20f\n",
                deg_evn_lat,deg_evn_lon,awb_evn_lat,awb_evn_lon,enc_evn_lat,enc_evn_lon,rpos0.lat,rpos0.lon,
                deg_odd_lat,deg_odd_lon,awb_odd_lat,awb_odd_lon,enc_odd_lat,enc_odd_lon,rpos1.lat,rpos1.lon);
    }
    fclose(fp) ;
    return 0;
}