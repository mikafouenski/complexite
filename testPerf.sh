#!/bin/sh

# *** START OF EDITABLE AREA ***

SRC="./src"
TESTSRC="test"
ALGO1="algo1.c"
ALGO2="algo2.c"
ALGO3="algo3.c"
ALGO4="algo4.c"
NUM_TEST=(100 500 1000 5000 10000 50000 100000 500000 1000000)

# *** END OF EDITABLE AREA ***

TEST1="$TESTSRC/algo1"
TEST2="$TESTSRC/algo2"
TEST3="$TESTSRC/algo3"
TEST4="$TESTSRC/algo4"

if [ ! -d $TESTSRC ];then
	echo "create test directory"
	mkdir $TESTSRC
fi

echo "Compile all algo"
gcc -o $TEST1 $SRC/$ALGO1
gcc -o $TEST2 $SRC/$ALGO2
gcc -o $TEST3 $SRC/$ALGO3
gcc -o $TEST4 $SRC/$ALGO4

function randomNumber() #args : min max
{
    local min=$1;
    local max=$2;

    echo $(( RANDOM%(max-min)+min ));
}

function generateNRandomNumbers() #args : N min max
{
    local N=$1
    local min=$2
    local max=$3
    local NUMBERS=""

    for ((i=0; i<N; i++))
    do
	NUMBERS="$NUMBERS $(randomNumber $min $max)"
    done
    echo $NUMBERS;
}

function launchTest() #args : TEST NUMBERS
{
	start=$(date +%s.%N);
	r="$(./$1 $2)"
	t=$(echo "$(date +%s.%N) - $start" | bc)
  	echo "$t"
}

for n in ${NUM_TEST[@]}
do
	echo -n "Generated $n numbers"
	NUMBERS="$(generateNRandomNumbers $n -500 500)"

	echo -n " - Execute TEST1"
	t1="$(launchTest $TEST1 $NUMBERS)"

	echo -n "...TEST2"
	t2="$(launchTest $TEST2 $NUMBERS)"

	echo -n "...TEST3"
	t3="$(launchTest $TEST3 $NUMBERS)"
	
	echo "...TEST4"
	t4="$(launchTest $TEST4 $NUMBERS)"

	echo -e "tab $n : \t $t1 \t $t2 \t $t3 \t $t4"
done

echo "Remove test folder"
rm -R $TESTSRC