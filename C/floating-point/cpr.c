/* 
 * cpr.c
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
#include "cpr.h"

/* ======================================================== */
/* ==================== Local Decoding ==================== */
/* ======================================================== */

// This functions assumes that the reference position and the position encoded
// in msg fulfill the hypothosis of the Local Decoding Correctness theorem
// (Th. 1 in [1]).
struct recovered_position local_dec(int i, unsigned int reference_lat, unsigned int reference_longitude, struct message msg){
    double r_lat = (reference_lat<=1073741824? rLatf(i,reference_lat,msg.yz):rLatf_g_2_30(i,reference_lat,msg.yz));
    int nl = nl_double(r_lat);
    double r_lon = (nl==1?rLonf_nl_1(reference_longitude,msg.xz):rLonf(i,nl,reference_longitude,msg.xz));
    struct recovered_position result = { r_lat, r_lon};
    return result;
}

/* ======================================================== */
/* =================== Global Decoding ==================== */
/* ======================================================== */

#define __mod360__(X) (X>=360?X-360:X)

// This function assumes that
// - msg0 represents an even message (msg0.format == 0)
// - msg1 represents an odd message  (msg1.format == 1)
// - NL on the recovered latitude for both messages return the same number
// - the hyphotesis of the Global Decoding Correctness theorem (Th. 2 in [1]) hold
//   for the positions encoded by msg0 and msg1.
struct recovered_position global_dec(int i, struct message msg0, struct message msg1){
    double r_lat_before_shift = (i==0?g_rLatf_i_0(msg0.yz, msg1.yz):g_rLatf_i_1(msg0.yz, msg1.yz));
    double r_lat = __mod360__(r_lat_before_shift+180.0) - 180.0;
    int nl = nl_double(r_lat);
    double r_lon = (nl==1?g_rLonf_nl_1(msg0.xz):(i==0?g_rLonf_i_0(msg0.xz,msg1.xz,nl):g_rLonf_i_1(msg0.xz,msg1.xz,nl)));
    struct recovered_position result = { r_lat, r_lon };
    return result;
}


// [1] L. Titolo, M. Moscato, C. A. Munoz, A. Dutle, and F. Bobot. A
// formally verified floating-point implementation of the compact
// position reporting algorithm. In Klaus Havelund, Jan Peleska, Bill
// Roscoe, and Erik de Vink, editors, Formal Methods, pages 364-381,
// Cham, 2018. Springer International Publishing.