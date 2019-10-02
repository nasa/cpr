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

# Hypothesis 2       
{ (i in [0,1] /\ yz0 in [0,131071] /\ yz1 in [0,131071] ->
  (jaf - jar in [0,0]
  /\
  (floor(jaf) - floor(jar) in [0,0] -> jf - jr in [0,0]))) }


# complete the coq certificate with the proof of
# forall x,y: x = y -> floor(x) = floor(y) 


