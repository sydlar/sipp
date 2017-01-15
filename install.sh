#!/bin/bash

PWD=$(pwd)
SIPPDIR=$HOME/.sipp
BINDIR=$HOME/bin


chmod u+x runSippFile.sh

ln -s $PWD $SIPPDIR
[ -d $BINDIR ] || mkdir $BINDIR
ln -s $PWD/runSippFile.sh $BINDIR/runSpp


