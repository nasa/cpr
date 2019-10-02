# Latitude Local Decoding (NL>1)

@rnd = float<ieee_64,ne>;
@floor = int<dn>;

i = floor(i_); # i is an integer
yz = floor(yz_); # i is an integer
awb_lats = floor(awb_lats_); # awb_lats is an integer

dLatr      = 360 / (60 - i);
dLatf rnd  = 360 / (60 - i);
j1r     = ((awb_lats * (60 - i) - (yz + 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
j1f rnd = ((awb_lats * (60 - i) - (yz + 0x1.0p+16)*0x1.0p+15)) * 0x1.0p-32;
jr     = floor(j1r);
jf rnd = floor(j1f);
rLatr     = dLatr * (jr + yz*0x1.0p-17);
rLatf rnd = dLatf * (jf + yz*0x1.0p-17);

{ (i in [0,1] /\ yz in [0,131072] /\ awb_lats in [0,4294967295] ->
    (j1f - j1r in [0,0] /\
    (floor(j1f) - floor(j1r) in [0,0] -> rLatf - rLatr in [-0.000046,0.000046])))
}

# complete the coq certificate with the proof of
# forall x,y: x = y -> floor(x) = floor(y) 