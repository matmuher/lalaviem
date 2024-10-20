#!/bin/bash
	clang++ IR_generator.cpp sim.c log.c sim.h -lSDL2 $(llvm-config --cppflags --ldflags --libs)