/* 
 * nl.c
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
#include <math.h>

// Precalculated NL Table.
int nl_double(double lat) {
 double abslat = fabs(lat);
 return abslat > 86.99999999999998578914? 1 :
        abslat > 86.53536997512100015228? 2 :
        abslat > 85.75541620944417786631? 3 :
        abslat > 84.89166190702084691110? 4 :
        abslat > 83.99173562980563190194? 5 :
        abslat > 83.07199444719813641313? 6 :
        abslat > 82.13956980510604921619? 7 :
        abslat > 81.19801349271948254227? 8 :
        abslat > 80.24923213280511902212? 9 :
        abslat > 79.29428225456925360958? 10:
        abslat > 78.33374082922746595158? 11:
        abslat > 77.36789461328187655908? 12:
        abslat > 76.39684390794467105934? 13:
        abslat > 75.42056256653356172137? 14:
        abslat > 74.43893415725136719629? 15:
        abslat > 73.45177441667863149632? 16:
        abslat > 72.45884544728943410518? 17:
        abslat > 71.45986473028982288724? 18:
        abslat > 70.45451074987599326959? 19:
        abslat > 69.44242631144021515865? 20:
        abslat > 68.42322022083330068653? 21:
        abslat > 67.39646774084663150006? 22:
        abslat > 66.36171008382616776088? 23:
        abslat > 65.31845309682088895897? 24:
        abslat > 64.26616522567439915292? 25:
        abslat > 63.20427479381928037582? 26:
        abslat > 62.13216659210329595453? 27:
        abslat > 61.04917774246351314104? 28:
        abslat > 59.95459276694029426835? 29:
        abslat > 58.84763776148457026238? 30:
        abslat > 57.72747353866113684262? 31:
        abslat > 56.59318756205917821944? 32:
        abslat > 55.44378444495043112283? 33:
        abslat > 54.27817472272899834706? 34:
        abslat > 53.09516152796003041203? 35:
        abslat > 51.89342469168767735254? 36:
        abslat > 50.67150165553834995080? 37:
        abslat > 49.42776439255686682372? 38:
        abslat > 48.16039128096621624308? 39:
        abslat > 46.86733252498745372349? 40:
        abslat > 45.54626722660234605655? 41:
        abslat > 44.19454951419274379986? 42:
        abslat > 42.80914012243555077930? 43:
        abslat > 41.38651832260239160632? 44:
        abslat > 39.92256684333861471714? 45:
        abslat > 38.41241892412256220268? 46:
        abslat > 36.85025107593526172422? 47:
        abslat > 35.22899597796384796311? 48:
        abslat > 33.53993436298484454027? 49:
        abslat > 31.77209707681076977792? 50:
        abslat > 29.91135685731808990794? 51:
        abslat > 27.93898710121904471748? 52:
        abslat > 25.82924707058775481982? 53:
        abslat > 23.54504486557070563890? 54:
        abslat > 21.02939492602846627278? 55:
        abslat > 18.18626357071335419846? 56:
        abslat > 14.82817436868679372707? 57:
        abslat > 10.47047129996848013888? 58: 59;
}