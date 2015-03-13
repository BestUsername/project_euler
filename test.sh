#!/bin/bash
NUM_PASS=0;
NUM_FAIL=0;
FILES=`find . -maxdepth 1 -type f -executable -not -name "*.sh" -print | sort`
for FILE in $FILES
do
    eval $FILE
    TEMP=$?
    if [ "0" -eq "$TEMP" ]; then
        NUM_PASS=$(( $NUM_PASS + 1 ))
    else
        NUM_FAIL=$(( $NUM_FAIL + 1 ))
    fi
done
TOTAL=$(( $NUM_PASS + $NUM_FAIL ))
echo "Passed ($NUM_PASS / $TOTAL)"
