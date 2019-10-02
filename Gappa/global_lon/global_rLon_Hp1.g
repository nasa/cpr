# Hypotesis 1:
# rLon11f - rLon11r -> 0 is valid because of

@rnd = float<ieee_64,ne>;
@floor = int<dn>;
 
x   = floor(x_);   # x is an integer
y   = floor(y_);   # x is an integer

r = x/y;
f rnd= x/y;

{ ( x in [-60,59] /\ y in [1,59] -> floor(f) - floor(r) in [0,0] ) }
floor(f) - floor(r) $ x,y;






