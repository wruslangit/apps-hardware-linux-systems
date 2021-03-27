#!/bin/bash
echo "Bismillah WRY. Execute run-makeglossaries-texindy.sh \n"
echo

FILENAME=Draft-46-PhD-Proposal-WRY

makeglossaries $FILENAME 
pdflatex       $FILENAME  
xindy	       $FILENAME  

makeindex      $FILENAME.idx -t zLog-01-$FILENAME.log 
makeindex -s   $FILENAME.ist -t zLog-02-$FILENAME.log -o $FILENAME.gls $FILENAME.glo
makeindex -s   $FILENAME.ist -t zLog-03-$FILENAME.log -o $FILENAME.acr $FILENAME.acn
makeindex -s   $FILENAME.ist -t zLog-04-$FILENAME.log -o $FILENAME.nls $FILENAME.nlo

xindy	       $FILENAME -t zLog-05-$FILENAME.log
makeglossaries $FILENAME -t zLog-06-$FILENAME.log
pdflatex       $FILENAME -t zLog-07-$FILENAME.log
pdflatex       $FILENAME -t zLog-08-$FILENAME.log

## CHECK REPLACEABLE PARAMETERS
echo 
echo $FILENAME.tex
echo
echo "SUCCESS. Alhamdulillah 3 times WRY."
echo

evince $FILENAME.pdf


