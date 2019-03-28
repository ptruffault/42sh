#!/bin/sh
TEST_FILES=$(find cmd -name '*.cmd')
COUNT=1

for FILE in $TEST_FILES
do
	< $FILE radamsa > cmd/generated/${COUNT}.cmd
	COUNT=`expr $COUNT + 1`
done
