/* 
 * local_rLat.c
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
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef double fp;

/*@
axiomatic real_function {
  logic real rLatr (int i, int awb_lats, int yz) =
    \let dLatr  = 360. / (60. - i);
    \let j1r    = ((awb_lats * (60 - i) - (yz - 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
    \let jr     = \floor(j1r);
    dLatr * (yz*0x1.0p-17 + jr);
}
@*/

/*@
  requires 0 <= i <= 1;
  requires 0 <= awb_lats <= 1073741824;
  requires 0 <= yz <= 131071;
  requires \floor(awb_lats) == awb_lats;
  requires \floor(yz) == yz;
  requires \floor(i) == i;
  ensures \abs(\result - rLatr(i,awb_lats,yz)) <= 0.000022888;
  @*/
fp rLatf (int i, unsigned int awb_lats, int yz) {
  fp dLatf  = 360.0 / (60.0 - i);
  fp j1f = ((awb_lats * (60.0 - i) - (yz - 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
  fp jf = floor(j1f);
  /*@ assert j1f:
      j1f == ((awb_lats * (60 - i) - (yz - 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32; @*/
  return dLatf * (yz*0x1.0p-17 + jf);
} 