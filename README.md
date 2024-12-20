# TesserCrypt
 A Tesseract geometry based file encryption solution.

## Background

## Basic Theory
The Basic concept is to use matrix transforms to manipulate a Tesseract coordinate matrix.  Initially only single axis rotation and uniform scale transformations will be used. 

The end goal is to be able to scale arbitrarily, perform multi-axis rotation and inverting transformations as additional transforms.

These matrix transformations are used to scramble a file that is split across all 24 faces of the tesseract and encode the transformations to the end of the file.  After all transformations are completed the data split across the faces is then conventionally encrypted and then interlaced and flattened into an image file.
 
 
## 4D spacial coordinates
The mathematical convention is to use W for the 4th dimensional axis.

 
 
 
