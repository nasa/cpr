# Longitude Local Decoding (NL>1)

@rnd = float<ieee_64,ne>;
@floor = int<dn>;

i = floor(i_); # i is an integer
xz = floor(xz_); # i is an integer
nl = floor(nl_); # nl is an integer
awb_lons = floor(awb_lons_); # awb_lons is an integer

dLonr      = 360 / (nl - i);
dLonf rnd  = 360 / (nl - i);
m1r     = ((awb_lons * (nl - i) - (xz + 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
m1f rnd = ((awb_lons * (nl - i) - (xz + 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
rLonr     = dLonr * (floor (m1r) + xz*0x1.0p-17);
rLonf rnd = dLonf * (floor (m1f) + xz*0x1.0p-17);

# Main property
{ (i in [0,1] /\ nl in [2,59] /\ xz in [0,131072] /\ awb_lons in [0,4294967295] -> 
	(m1f - m1r in [0,0]
	/\
	(floor(m1f) - floor(m1r) in [0,0] -> rLonf - rLonr in [-0.000046,0.000046])))} 

# complete the coq certificate with the proof of
# forall x,y: x = y -> floor(x) = floor(y) 
