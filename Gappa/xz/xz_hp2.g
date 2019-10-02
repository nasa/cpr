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


# Hypothesis 2
{ (i in [0,1] /\ n in [0,4294967296] /\ nl in [1,59]  -> xzf1*0x1.0p-17 - xzr1*0x1.0p-17 in [0,0])}
xzf1 - xzr1 -> 0; # Hypotesis 1
