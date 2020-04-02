# Contents

This PVS development includes several verification artifacts of the
ADS-B's Compact Position Reporting (CPR) algorithm.

The theories in the `CPR_fp` folder provide a formalization of  the airborne message
type, i.e., NB=17. This formalization includes:
* Counterexamples for the real-valued version of CPR assuming the hypothesis stated in the
  original version of the standard
* Counterexamples for  a straightforward
  implementation of CPR in single-precision floating-point numbers 
* Correctness proof of CPR under a modified hypothesis proposed
in [1]
* Correctness proof of of numerical simplifications proposed in [1]
* Equivalence proof between the functions defined here and the ACSL logic descriptions used in the verification of the floating-point C implementation presented in [2]
* A NL-table generator 

The theories in the `CPR` folder include a formalization of CPR in
  real arithmetic (`cpr_real.pvs`) and in 32-bit fixed-point
  arithmetic (`cpr_int.pvs`). Both formalizations provide support for all the possible
  message types defined in the standard: coarse (NB=12), intent (14),
  airborne (17), and surface (19). This formalization includes:
  
* Correctness proofs of the real-valued version under the hypothesis stated in [1]. 
* Equivalence proofs between the real-valued specification and the integer-valued specification. 
* Equivalence proofs between the integer-valued specification and the
ACSL logic description used in the verification of the unsigned
integer C implementation for every possible value of NB, found in the
folders `vc_nb_12` (coarse), `vc_nb_14` (intent), `vc_nb_17`
(airborne),  and `vc_nb_19` (surface). The folder `vc_shared` contains
the PVS theories shared by all of them.
* The PVS  definitions used by the Frama-C/WP plugin, which are found
  in the `framac_wp` folder.

# Re-running the PVS Proofs

[PVS version 7.1](http://pvs.csl.sri.com) and the development version
of the [NASA PVS Library](https://github.com/nasa/pvslib) are required
to type-check and prove these formalizations. 

To re-prove the CPR development, type the following command in a Unix
shell in the directory containing the folder `CPR-fp`, `CPR`, `framac_wp`,
and `vc_nb_xx`.

```
$ provethem --addpath 
```

The output of that command is

```
Processing all-theories. Output in ./all-theories.grandtotals
CPR_fp                   [OK: 281 proofs]
CPR                      [OK: 290 proofs]
framac_wp                [OK: 10 proofs]
vc_nb_12                 [OK: 80 proofs]
vc_nb_14                 [OK: 80 proofs]
vc_nb_17                 [OK: 80 proofs]
vc_nb_19                 [OK: 80 proofs]

*** Grand Totals: 901 proofs / 901 formulas. Missed: 0 formulas.
*** Number of libraries: 7
```

# Bibliography

[1] A. Dutle, M. Moscato, L. Titolo, and C. Munoz. A formal analysis
of the compact position reporting algorithm. 9th Working Conference on
Verified Software: Theories, Tools, and Experiments, VSTTE 2017,
Revised Selected Papers, 10712:19–34, 2017.

[2] L. Titolo, M. Moscato, C. A. Munoz, A. Dutle, and F. Bobot. A
formally verified floating-point implementation of the compact
position reporting algorithm. In Klaus Havelund, Jan Peleska, Bill
Roscoe, and Erik de Vink, editors, Formal Methods, pages 364-381,
Cham, 2018. Springer International Publishing.
