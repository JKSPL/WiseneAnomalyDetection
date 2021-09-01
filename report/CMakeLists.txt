PROJECT(final_report NONE)
cmake_minimum_required(VERSION 3.4)
#SET(LATEX_OUTPUT_PATH ../report_build)
INCLUDE(../UseLATEX/UseLATEX.cmake)
add_latex_document(
        final_report.tex
        BIBFILES bibliography.bib
        IMAGE_DIRS images
        INCLUDE_DIRECTORIES images
        FORCE_PDF
        USE_BIBLATEX
)