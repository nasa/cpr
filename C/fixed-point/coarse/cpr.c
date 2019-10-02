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
#include "cpr_int.h"
#include "cpr.h"

/* ======================================================== */
/* ================== Encoding ============================ */
/* ======================================================== */

struct message encode(int i, int_type awb_lat, int_type awb_lon) {
    int_type nz = max(nl_awb(rlat_int(i,awb_lat))-i, 1);
    struct message result =  { i , encoding(60-i, awb_lat) , encoding(nz, awb_lon) };
    return result;
}
/* ======================================================== */
/* ==================== Local Decoding ==================== */
/* ======================================================== */

struct recovered_position local_dec(int i, int_type reference_lat, int_type reference_longitude, struct message msg){
    int_type r_lat = local_decode(60-i, reference_lat, msg.yz);
    int_type r_lon = local_decode(max(nl_awb(r_lat)-i, 1), reference_longitude, msg.xz);
    struct recovered_position result = { r_lat, r_lon};
    return result;
}

/* ======================================================== */
/* =================== Global Decoding ==================== */
/* ======================================================== */

struct recovered_position global_dec(int i, struct message msg0, struct message msg1){
    int_type r_lat = global_decode(60, msg0.yz, msg1.yz, i);
    int_type nl0 = nl_awb(global_decode(60, msg0.yz, msg1.yz, 0));
    int_type r_lon = global_decode(nl0, msg0.xz, msg1.xz, i);
    struct recovered_position result = { r_lat, r_lon};
    return result;
}