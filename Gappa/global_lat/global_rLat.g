# Latitude Global Decoding

@rnd = float<ieee_64,ne>;
@floor = int<dn>;

i   = floor(i_);   # i is an integer
yz0 = floor(yz0_); # yz0 is an integer
yz1 = floor(yz1_); # yz1 is an integer

dLatr     = 360 / (60 - i);
dLatf rnd = 360 / (60 - i);

jar     = (59 * yz0 - 60 * yz1 + 0x1.0p+16) *0x1.0p-17;
jaf rnd = (59 * yz0 - 60 * yz1 + 0x1.0p+16) *0x1.0p-17;
jr      = floor(jar);
jf rnd  = floor(jaf);

j_60_i_r     = jr/(60 - i);
j_60_i_f rnd = jf/(60 - i);

rLatr     = dLatr * ((jr - (60 - i)*(floor (j_60_i_r))) + yz0*0x1.0p-17);
rLatf rnd = dLatf * ((jf - (60 - i)*(floor (j_60_i_f))) + yz0*0x1.0p-17);

# Main property
{ (i in [0,1] /\ yz0 in [0,131071] /\ yz1 in [0,131071] -> rLatf - rLatr in [-0.000046,0.000046])}
floor(j_60_i_f) - floor(j_60_i_r) -> 0; # Hypothesis 1
jf - jr -> 0;                           # Hypothesis 2
