# Latitude encoding function

@rnd = float<ieee_64,ne>;
@floor = int<dn>;

n = floor(n_); # n is an integer
i = floor(i_); # i is an integer

dlr       = 60 - i;
dlf   rnd = 60 - i;
tmp1r     = (n * dlr + 0x1.0p+14)*0x1.0p-15;
tmp1f rnd = (n * dlf + 0x1.0p+14)*0x1.0p-15;  
tmp2r     = (n * dlr)*0x1.0p-32;
tmp2f rnd = (n * dlf)*0x1.0p-32;
yzr1       = floor(tmp1r) - 0x1.0p+17 * floor(tmp2r) ;
yzf1   rnd = floor(tmp1f) - 0x1.0p+17 * floor(tmp2f) ;
yzr17     = yzr1 * 0x1.0p-17;
yzf17 rnd = yzf1 * 0x1.0p-17;

# Hypothesis 2
{ (i in [0,1] /\ n in [0,4294967296] -> yzf17 - yzr17 in [0,0]) }
yzf1 - yzr1 -> 0; # Hypotesis 1
