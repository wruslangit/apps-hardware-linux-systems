#!/bin/bash
echo "Bismillah WRY. Execute run-makeglossaries-texindy.sh \n"
echo

makeglossaries Draft-39-PhD-Proposal-WRY.tex
pdflatex       Draft-39-PhD-Proposal-WRY.tex

makeindex      Draft-39-PhD-Proposal-WRY.idx

makeindex -s   Draft-39-PhD-Proposal-WRY.ist -t Draft-39-PhD-Proposal-WRY.glg -o Draft-39-PhD-Proposal-WRY.gls Draft-39-PhD-Proposal-WRY.glo

makeindex -s   Draft-39-PhD-Proposal-WRY.ist -t Draft-39-PhD-Proposal-WRY.glg -o Draft-39-PhD-Proposal-WRY.acr Draft-39PhD-Proposal-WRY.acn

makeindex -s   Draft-39-PhD-Proposal-WRY.ist -t Draft-39-PhD-Proposal-WRY.glg -o Draft-39-PhD-Proposal-WRY.gls Draft-39-PhD-Proposal-WRY.glo

makeindex -s   Draft-39-PhD-Proposal-WRY.ist -t Draft-39-PhD-Proposal-WRY.glg -o Draft-39-PhD-Proposal-WRY.nls Draft-39-PhD-Proposal-WRY.nlo

texindy		   Draft-39-PhD-Proposal-WRY.tex
pdflatex       Draft-39-PhD-Proposal-WRY.tex
pdflatex       Draft-39-PhD-Proposal-WRY.tex


echo
echo "SUCCESS. Alhamdulillah 3 times WRY."
echo