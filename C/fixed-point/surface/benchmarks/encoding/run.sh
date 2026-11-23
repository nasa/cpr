#!/bin/bash

for csvfile in *.csv
do
   # MOPS-table-2-140.csv is the input of verify-lat-trans-points, not of encode.
   if [ "$csvfile" = "MOPS-table-2-140.csv" ]; then
      continue
   fi

   if [ -e "$csvfile" ]; then
      ./encode $csvfile > $csvfile.out

      ./check-encoding $csvfile $csvfile.out

      retVal=$?
      if [ $retVal -eq 0 ]; then
         echo "$csvfile encoded as expected."
      fi
   else 
      echo 'Warning: No *.csv file found in the current directory.'
   fi
done