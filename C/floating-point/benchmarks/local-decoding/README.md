Example of use of the decoding functionality of CPR.

The program in `decode.c` reads the information needed to (locally) decode a CPR message and prints the recovered position.
It is expected for the information to be provided in a CSV file in which every line starts with the following fields:
```
<message format>, <awb reference latitude>, <awb reference longitude>, <message latitude>, <message longitude>
````
where _<message format>_ can take the value 0 (even message) or 1 (odd message), _<awb reference latitude>_ and _<awb reference longitude>_ represent the reference position (given as a pair of AWB integers representing latitude and longitude resp.), and the last two fields represents the encoded latitude and longitude transmitted in a CPR message.
The program expects as argument the name of the input CSV file. 
It prints on the standard output the input data followed by the recovered position (latitude and longitude, in that order).
```
<message format>, <awb reference latitude>, <awb reference longitude>, <message latitude>, <message longitude>, <recovered latitude>, <recovered longitude>
````
For convenience, a `Makefile` is provided to build the program.
```shell
$ make
gcc -o decode decode.c -L../.. -lairborne 
```

This program uses the airborne library (`libairborne.a`). 
To build the library, the user may invoke `make` in the [`airborne`](`../../`) directory (see [`airborne/README.md`](`../../README.md`) for details).

A bash script ([`run.sh`](run.sh)) aimed to automate the execution of the program on multiple files is also provided. 
It assumes that the CSV file contains not only the required input data (in the order explained above) but also the expected result of the decoding.
The script iterates over all the CSV files in the directory and executes `decode` on them.
Every result is stored in an `.out` file and compared with the input.
The standard output is used to report discrepancies of the results w.r.t. the given input.
