/* 
 * cpr.h
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
#ifndef CPR__H
#define CPR__H

#define int_type unsigned int

struct message {
    int format;   // even (0) or odd (1)
    unsigned int yz; // encoded latitude
    unsigned int xz; // encoded longitude
};

struct recovered_position {
    double lat; // recovered latitude
    double lon; // recovered longitude
};

typedef double fp;

/* Core functions */
// Global decoding
fp g_rLatf_i_0 (int yz0, int yz1);
fp g_rLatf_i_1 (int yz0, int yz1);
fp g_rLonf_i_0 (int xz0, int xz1, int nl);
fp g_rLonf_i_1 (int xz0, int xz1, int nl);
fp g_rLonf_nl_1 (int xz);
// Local decoding
fp rLatf (int i, unsigned int awb_lats, int yz);
fp rLatf_g_2_30 (int i, unsigned int awb_lats, int yz);
fp rLonf_nl_1 (unsigned int awb_lons, int xz);
fp rLonf (int i, int nl, unsigned int awb_lons, int xz);

/* Precomputed NL table */
int nl_double(double lat);

/* Interface */

struct recovered_position local_dec(int i, unsigned int reference_lat, unsigned int reference_longitude, struct message msg);
struct recovered_position global_dec(int i, struct message msg0, struct message msg1);

#endif // CPR__H