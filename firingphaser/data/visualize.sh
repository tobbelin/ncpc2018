cd $(dirname $0)

g++ -O2 -std=gnu++14 -o sol ../submissions/accepted/per.cc
for f in {sample,secret}/*.in; do
    if [ -f ${f%.in}.png ]; then continue; fi
    echo $f
    time ./sol verbose < $f > sol.out
    if [ $? == 0 ]; then
	cat sol.out | asy visualize.asy -o ${f%.in}.png
    fi
done

