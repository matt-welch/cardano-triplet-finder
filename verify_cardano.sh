#!/bin/bash
# verify parallel vs. serial
# verify_cardano.sh

for i in {1..100}
do
    ./cardano 1000 > res_ser
    ./cardano_parallel 1000 > res_par
    diff res_ser res_par > diff$i
done
