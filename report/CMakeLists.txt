PROJECT(final_report NONE)
cmake_minimum_required(VERSION 3.4)
INCLUDE(../UseLATEX/UseLATEX.cmake)
add_latex_document(
        final_report.tex
        INPUTS metodologia-i-algorytm.tex realizacja.tex wstep.tex analiza-danych.tex
        BIBFILES bibliography.bib
        IMAGE_DIRS images
        INCLUDE_DIRECTORIES images
        FORCE_PDF
        USE_BIBLATEX
)