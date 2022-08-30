#!/bin/bash

IN_FILE=$1
OUT_FILE=$2
MODEL_PATH=`pwd`/../data/s

if [ "$UCVM_INSTALL_PATH" ]; then
  MODEL_PATH=$UCVM_INSTALL_PATH/model/cvms/data/s
fi

#echo "Using ${MODEL_PATH} to run >" ${0##*/} 

./cvms_txt ${MODEL_PATH} < ${IN_FILE} > ${OUT_FILE}

##./cvms_txt < ${IN_FILE} > ${OUT_FILE}

if [ $? -ne 0 ]; then
    exit 1
fi

exit 0
