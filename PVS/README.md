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
(airborne),  and `vc_nb_19` (surface). 
* The PVS  definitions used by the Frama-C/WP plugin, which are found
  in the `framac_wp` folder.

# Re-running the PVS Proofs

[PVS version 8.1.3](https://github.com/SRI-CSL/PVS/releases/tag/pvs8.1.3) and
[NASALib](https://github.com/nasa/pvslib) are required to type-check and prove the CPR
development in PVS. Install NASALib as its README says.

## Checked versions

All 910 formulas are proved with these versions:

| Tool | Version |
|---|---|
| PVS | 8.1.3, the release of 2026-10-28 (tag [`pvs8.1.3`](https://github.com/SRI-CSL/PVS/releases/tag/pvs8.1.3), commit `50a70e713`) |
| NASALib | `master` at commit [`d70ebfc8`](https://github.com/nasa/pvslib/commit/d70ebfc8fcd562699aea4bcccbaf3d2c4d66796f) (2026-10-28) |

## Check the formalization

Run this command in the local directory `PVS`:

```
$ provethem --proveit-option 'add-path .' all-libraries
```

The option `add-path .` adds the directory `PVS` to the library path for this run. Thus the
libraries `vc_nb_12`, `vc_nb_14`, `vc_nb_17` and `vc_nb_19` find the libraries `CPR` and
`framac_wp`, and no other setting is necessary. The file `all-libraries` lists the libraries in
the order in which they are checked.

The output of that command should be

```
CPR_fp      Proving... [OK: 282 proofs]
CPR         Proving... [OK: 295 proofs]
framac_wp   Proving... [OK: 10 proofs]
vc_nb_12    Proving... [OK: 81 proofs]
vc_nb_14    Proving... [OK: 81 proofs]
vc_nb_17    Proving... [OK: 81 proofs]
vc_nb_19    Proving... [OK: 80 proofs]

*** Grand Totals: 910 proofs / 910 formulas. Missed: 0 formulas
*** Number of libraries: 7
```

On a MacBook with Apple silicon, the command took 38 minutes. The library `CPR` takes the
longest, about 16 minutes.

To type-check without proving, add the option `-T`:

```
$ provethem -T --proveit-option 'add-path .' all-libraries
```

## Complete and incomplete proofs

The directory `summaries` holds the summary of each library from the run above. Every formula is
proved: no formula is `unfinished`, `untried` or `unchecked`. PVS lists each proved formula in one
of two ways:

- `proved - complete`: the proof succeeds, and every formula that the proof uses is also proved in
  this installation. These are the lemmas, TCCs and judgements that the proof uses, and the
  formulas that their proofs use, through the whole chain.
- `proved - incomplete`: the proof succeeds, but its chain contains a formula that is not proved in
  this installation, for example a NASALib lemma, TCC or judgement.

NASALib is fully proved, but its proofs take several hours, so the check above does not run them.
Thus `proved - incomplete` does not mean that a proof failed or is missing. After NASALib is proved
in the same installation, for example with its script `prove-all`, the check lists these formulas
as `proved - complete`.

## Use CPR as a library in another development

To import CPR in another PVS development, PVS must find the directory `PVS` of this repository
in the Unix environment variable `PVS_LIBRARY_PATH`, together with NASALib.

1. Clone this repository. In the commands below, replace `<cprdir>` with the absolute path of the
   local clone, and `<nasalibdir>` with the absolute path of the local directory where NASALib was
   cloned.

2. Add both directories to `PVS_LIBRARY_PATH`.

   In Bourne shell (bash or sh) or zsh:

   ~~~
   export PVS_LIBRARY_PATH="<nasalibdir>:<cprdir>/PVS:$PVS_LIBRARY_PATH"
   ~~~

   In C shell (csh or tcsh):

   ~~~
   setenv PVS_LIBRARY_PATH "<nasalibdir>:<cprdir>/PVS:$PVS_LIBRARY_PATH"
   ~~~

   If `PVS_LIBRARY_PATH` already contains NASALib, add only `<cprdir>/PVS`. To keep the setting,
   add the line to your shell startup file (for example `~/.bashrc`, `~/.zshrc` or `~/.cshrc`).
   Start PVS after you set the variable.

3. Import the theories with the library name as a prefix. To import all of CPR, import its `top`
   theory:

   ~~~
   IMPORTING CPR@top
   ~~~

   You can also import one theory, for example `IMPORTING CPR@cpr_int`. The library `CPR_fp` is
   imported in the same way, for example `IMPORTING CPR_fp@top`.

4. Type-check your development once with the command `M-x typecheck` in PVS, or with
   `proveit -T <your theory file>`, to make sure that PVS finds CPR.

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
