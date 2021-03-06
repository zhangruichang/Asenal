#!/bin/sh

rm -rf ./rd_r_*
rm -rf ./rd_sd_*
for ((j = 40; j < 91; j=( $j + 10) ))
do
  for ((k = 0; k < 101; k=( $k + 2) ))
  do
    for ((delay = 0; delay < 11; delay=( $delay + 5) ))
    do
      rm -rf last_rd_r;
      rm -rf last_rd_sd;
      for ((i = 0; i < 100; i=( $i + 1) ))
      do
        ./mm $k 100 100 $j 1 $delay > ./run_tmp_rd;
        cat ./run_tmp_rd | grep -v 'sd' | tail -1 >> ./last_rd_r;
        cat ./run_tmp_rd | grep 'sd' >> ./last_rd_sd;
      done
      cat last_rd_r | awk -F '\t' 'BEGIN { sum = 0; n = 0; }; {sum += $2; n++;}; END {printf("%d \n", sum / n);}' >> rd_r_$j\_$delay;
      cat last_rd_sd | awk -F '\t' 'BEGIN { sum = 0; n = 0; }; {sum += $2; n++;}; END {printf("%d \n", sum / n);}' >> rd_sd_$j\_$delay;
    done
  done
done
