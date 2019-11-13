import os
import sys
import subprocess
import glob

testFiles=list(glob.glob("*.cpp"))

print("Test Files:", testFiles)

print("\n########### NO PARALLEL ###########\n")
for file in testFiles:
    print("\n----- "+file+" -----\n")
    if(subprocess.call(["g++", file, "-o", "test", "-ggdb3", "-std=c++11", "-Wno-literal-suffix"])): exit(1)  
    print("\n\n")
    if(subprocess.call(["valgrind", "--leak-check=full", "--show-leak-kinds=all", "--error-exitcode=1", "./test"])): exit(1)

print("\n########### PARALLEL ###########\n")
for file in testFiles:
    print("\n----- "+file+" -----\n")
    if(subprocess.call(["g++", file, "-o", "test", "-ggdb3", "-std=c++11", "-Wno-literal-suffix", "-fopenmp", "-D", "DM4thParallel"])): exit(1)  
    print("\n\n")
    if(subprocess.call(["./test"])): exit(1)