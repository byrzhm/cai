#! /bin/bash

cd src/parse && flex -o yy_lexer.cc lexer.ll && cd ../..
cd include/parse && bison --header=yy_parser.tab.hh -o ../../src/parse/yy_parser.cc ../../src/parse/parser.yy
mv ../../src/parse/location.hh .