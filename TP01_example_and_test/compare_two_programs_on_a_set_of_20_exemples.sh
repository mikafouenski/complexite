#!/bin/sh

NUMBERS=""
mark=0

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

function testProg() #args: programCorrection programTested N
{
    local programCorrection=$1
    local programTested=$2
    local N=$3

    echo "################ tabular of size $N"
    NUMBERS="$(generateNRandomNumbers $N -100 100)"
    echo $NUMBERS
    CORRECTANSWER=$($programCorrection $NUMBERS)
    echo "CorrectProgram ($programCorrection): $CORRECTANSWER"
    TESTEDANSWER=$($programTested $NUMBERS)
    echo "TestedProgram ($programTested): $TESTEDANSWER"
    if [ "$CORRECTANSWER" = "$TESTEDANSWER" ]
    then
      echo "+1 (tested answer is correct)"
      let mark=mark+1
    else
      echo "0 (tested answer is not correct)"
    fi
}

numberOfTests=20
# first serie of tests for sizes 100 to 109
for n in $(seq 100 109)
do
  testProg "$1" "$2" $n
done
# second serie of tests for sizes 1000 to 1009
for n in $(seq 1000 1009)
do
  testProg "$1" "$2" $n
done
# give mark
echo ""
echo "################"
echo "The comparison of \"$1\" and \"$2\" passed $mark tests over ${numberOfTests}."

