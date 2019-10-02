# Hypothesis 1: floor(j_60_i_f) - floor(j_60_i_r) -> 0;
#
# The argument is that j_60_i_f = j_60_i_r, which can be stated as valid since:

@rnd = float<ieee_64,ne>; 
@floor = int<dn>;

x = floor(x_);   # x is an integer
y = floor(y_);   # y is an integer

r     = x/y;
f rnd = x/y;

{ ( x in [-60,59] /\ y in [59,60] -> floor(f) - floor(r) in [0,0] ) }
floor(f) - floor(r) $ y,x;
