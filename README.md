[![Build Status](https://travis-ci.org/amichaeltm/BDSup2SubPlusPlus.svg?branch=master)](https://travis-ci.org/amichaeltm/BDSup2SubPlusPlus)

BDSup2Sub++
===========

BDSup2Sub++ (c) 2012 is a port of the original BDSup2Sub (c) 2009 by 0xdeadbeef and incorporating enhancements from  Miklos Juhasz. It is a subtitle conversion tool for image based stream formats with scaling capabilities and some other nice features.

Current maintainer is paradoxic4l.

# libbdsup2sub++

This fork adds a meson.build that will create a library. Which basically has all the code except `main.cpp`.

The reasoning behind this is because I wanted to write a c++ application that requires bdsup2sub, but I didn't want
to have to require java to run said application.  I figured out that all the `main.cpp` code does is create a
BDSup2Sub object, and then if command options exist it just passes the command line options to the object.

This allows my program to avoid spawning a seperate process.
