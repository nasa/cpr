# Longitude Local Decoding (NL=1)

@rnd = float<ieee_64,ne>;
@floor = int<dn>;

xz = floor(xz_); # i is an integer
awb_lons = floor(awb_lons_); # awb_lons is an integer
i = floor(i_);

m1r     = ((awb_lons - (xz + 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
m1f rnd = ((awb_lons - (xz + 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
rLonr     = 360 * (floor (m1r) + xz*0x1.0p-17);
rLonf rnd = 360 * (floor (m1f) + xz*0x1.0p-17);

# Main property
{ (i in [0,1] /\ xz in [0,131072] /\ awb_lons in [0,4294967295] ->
  (m1f - m1r in [0,0]
   /\
   (floor(m1f) - floor(m1r) in [0,0] -> rLonf - rLonr in [-0.000046,0.000046])))} 

# complete the coq certificate with the proof of
# forall x,y: x = y -> floor(x) = floor(y) 
