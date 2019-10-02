/* 
 * global_rLonNL1.c
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
  logic real rLonr (int xz) = 360 * (xz/0x1.0p+17);
}
@*/

/*@
  requires 0 <= xz <= 131071;
  ensures \abs(\result - rLonr(xz)) <= 0.000022888;
  @*/
fp g_rLonf_nl_1 (int xz) {
  return 360 * (xz/0x1.0p+17);
}