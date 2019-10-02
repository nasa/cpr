CC := gcc
CFLAGS := -Wall

airborne: cpr.o nl.o global_rLat_i0.o global_rLat_i1.o global_rLon_i0.o global_rLon_i1.o global_rLonNL1.o local_rLat-greater-2-30.o local_rLat.o local_rLon.o local_rLonNL1.o
	ar -cr libairborne.a cpr.o nl.o global_rLat_i0.o global_rLat_i1.o global_rLon_i0.o global_rLon_i1.o global_rLonNL1.o local_rLat-greater-2-30.o local_rLat.o local_rLon.o local_rLonNL1.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) *.o *.a