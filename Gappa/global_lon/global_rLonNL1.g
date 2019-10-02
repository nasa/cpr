# Longitude Global Decoding (when NL=1)

@rnd = float<ieee_64,ne>;
@floor = int<dn>;

xz = floor(xz_); # i is an integer

rLonr     = 360 * (xz/0x1.0p+17);
rLonf rnd = 360 * (xz/0x1.0p+17);

{ (xz in [0,131072] ->  rLonf - rLonr in [-0.000046,0.000046])} 

rLonf - rLonr $ xz; 
