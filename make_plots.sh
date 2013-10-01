#!/bin/bash

scriptroot=$(dirname $0)
dataroot=$1
rows=$2
cols=$3

matrices=$(ls $dataroot/matrices/*.cm)

for m in $matrices
do
    echo "Extracting plot from $m"
    $scriptroot/extract_plot $m $rows $cols > \
        $dataroot/matrices/$(basename $m).plot
done
