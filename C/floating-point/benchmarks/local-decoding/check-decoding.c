/* 
 * check-decoding.c
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

#define INPUT_LINE_MAX_LENGTH 220

// dlat
#define __dlati__(i) (i==0?6.0:(360.0/59.0))

#define P2_18 262144.0

// P2_NB1 = 2^(17+1)
#define P2_NB1 P2_18

#define RESOLUTION 360.0/4294967296.0

double awb2lat(int_type awb_lat){
    if(awb_lat<=1073741824) // 2^30
        return awb_lat*RESOLUTION;
    else 
        return awb_lat*RESOLUTION - 360.0;
}

// simple in-line abs(X-Y)
#define __diffabs__(X,Y) (X>=Y?X-Y:Y-X)
// simple modulus operation (correct for X in [-359,(2*360-1)])
#define __mod360__(X) (X>=360?X-360:(X<0?360+X:X))
#define INV_RESOLUTION 4294967296.0/360.0

int_type lat2awb(double lat){
    return (int_type)floor(INV_RESOLUTION*__mod360__(lat)+0.5);
}

// This correction comes from the Theorem 7 in [FM2018].
#define FP_BOUND_CORRECTION 0.000022888

int main(int argc, char * argv[]){
    int result = 0; // OK
    int i;
    FILE *fp ;
    char line[INPUT_LINE_MAX_LENGTH] ;
    const char* token = NULL;
    int_type awb_ref_lat, awb_ref_lon;
    int_type awb_cur_lat, awb_cur_lon;
    double deg_rec_lat, deg_rec_lon;
    int_type encoded_lat, encoded_lon;
    int_type decoded_lat, decoded_lon;
    double deg_ref_lat, deg_ref_lon;
    double deg_cur_lat, deg_cur_lon;

    if(argc <= 1) {
        fprintf(stderr, "Error: Missing input file name.\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "Error: File %s not found.\n", argv[1]);
        return 1;
    }

    // Bound stated by the local_correcteness_theorem
    int_type awb_bound;
    double deg_bound;
    double deg_bound_i0 = __dlati__(0)/P2_NB1 + FP_BOUND_CORRECTION;
    double deg_bound_i1 = __dlati__(1)/P2_NB1 + FP_BOUND_CORRECTION;
    int_type awb_bound_i0 = lat2awb(deg_bound_i0);
    int_type awb_bound_i1 = lat2awb(deg_bound_i1);

    char* tmp = NULL;
    while( fgets ( line, INPUT_LINE_MAX_LENGTH, fp ) != NULL ) {
        tmp = strdup(line);
        token = strtok(tmp, ",");
        deg_ref_lat = atof(token);
        token = strtok(NULL, ",");
        deg_ref_lon = atof(token);
        token = strtok(NULL, ",");
        awb_ref_lat = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        awb_ref_lon = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        deg_cur_lat = atof(token);
        token = strtok(NULL, ",");
        deg_cur_lon = atof(token);
        token = strtok(NULL, ",");
        awb_cur_lat = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        awb_cur_lon = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        i = atoi(token);
        token = strtok(NULL, ",");
        encoded_lat = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        encoded_lon = (int_type) strtoul(token,NULL,16);
        token = strtok(NULL, ",");
        deg_rec_lat = atof(token);
        token = strtok(NULL, ",");
        deg_rec_lon = atof(token);
        free(tmp);

        awb_bound = (i==0?awb_bound_i0:awb_bound_i1);
        deg_bound = (i==0?deg_bound_i0:deg_bound_i1);

        double deg_dist = __diffabs__(deg_cur_lat,deg_rec_lat);
        if(deg_dist > awb_bound) {
            printf("recovered: %.20f and actual: %.20f at %.20f (vs. %.20f)\n",deg_rec_lat,deg_cur_lat,deg_dist,deg_bound);
            result = 1; // ERROR
        }
    }
    fclose(fp) ;
    return result;
}