PROJECT(final_report NONE)
cmake_minimum_required(VERSION 3.4)
INCLUDE(../UseLATEX/UseLATEX.cmake)
add_latex_document(
        final_report.tex
        INPUTS metodologia-i-algorytm.tex wstep.tex analiza-danych.tex img_dist.tex img_diff_time.tex img_diff_dist_small.tex img_diff_dist.tex
        BIBFILES bibliography.bib
        IMAGE_DIRS images
        INCLUDE_DIRECTORIES images
        USE_BIBLATEX
)