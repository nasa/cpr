# Longitude encoding function

@rnd = float<ieee_64,ne>;
@floor = int<dn>;

n = floor(n_); # n is an integer
i = floor(i_); # i is an integer
nl = floor(nl_); # nl is an integer

nlir = nl - i;
nlif rnd = nl - i;
tmp1r     = (n * nlir + 0x1.0p+14)*0x1.0p-15;
tmp1f rnd = (n * nlif + 0x1.0p+14)*0x1.0p-15;  
tmp2r     = (n * nlir)*0x1.0p-32;
tmp2f rnd = (n * nlif)*0x1.0p-32;
xzr1     = floor(tmp1r) - 0x1.0p+17 * floor(tmp2r) ;
xzf1 rnd = floor(tmp1f) - 0x1.0p+17 * floor(tmp2f) ;

xzr2     = 0x1.0p+17 * floor(xzr1*0x1.0p-17);
xzf2 rnd = 0x1.0p+17 * floor(xzf1*0x1.0p-17);

xzr      = xzr1 - xzr2;
xzf  rnd = xzf1 - xzf2;


# Main Property
{ (i in [0,1] /\ n in [0,4294967296] /\ nl in [1,59] -> xzf - xzr in [0,0])}
xzf1 - xzr1 -> 0; # Hypothesis 1
floor(xzf1*0x1.0p-17) - floor(xzr1*0x1.0p-17) -> 0; # Hypothesis 2
xzf2 - xzr2 -> 0; # Hypothesis 3

# complete the coq certificate with the proof of
# forall x,y: x = y -> floor(x) = floor(y)
# xz_hp1 and xz_hp2
