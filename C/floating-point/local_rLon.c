/* 
 * local_rLon.c
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
  logic real rLonr (int i, int nl, int awb_lons, int xz) =
     \let dLonr = 360.0 / (nl - i);
     \let m1r   = ((awb_lons * (nl - i) - (xz - 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
     \let mr    = \floor (m1r);
     dLonr * (mr + xz*0x1.0p-17);
}
@*/

/*@
  requires 0 <= i <= 1;
  requires 0 <= awb_lons <= 4294967295;
  requires 0 <= xz <= 131072;
  requires 2 <= nl <= 59;
  requires \floor(awb_lons) == awb_lons;
  requires \floor(xz) == xz;
  requires \floor(nl) == nl;
  requires \floor(i) == i;
  ensures \abs(\result - rLonr(i,nl,awb_lons,xz)) <= 0.000022888;
  @*/
fp rLonf (int i, int nl, unsigned int awb_lons, int xz) {
  fp dLonf  = 360.0 / ((fp) nl - (fp) i);
  fp m1f = ((awb_lons * ((fp) nl - (fp) i) - (xz - 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
  /*@ assert m1f:
    m1f == ((awb_lons * (nl - i) - (xz - 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32; @*/
  fp mf = floor(m1f);
  return dLonf * (mf + xz*0x1.0p-17);
}