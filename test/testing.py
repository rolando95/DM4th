import os
import sys
import subprocess
import glob

testFiles=glob.glob("**/*.cpp", recursive=True)

print("Test Files:", testFiles)

print("\n########### NO PARALLEL ###########\n")
for file in testFiles:
    print("\n----- "+file+" -----\n")
    if(subprocess.call(["g++", file, "-o", "test", "-ggdb3", "-std=c++11", "-D", "DM4thOnlyStandardLiterals"])): exit(1)  
    if(len(sys.argv)>1 and sys.argv[1]=="usevalgrind"):
        if(subprocess.call(["valgrind", "--leak-check=full", "--show-leak-kinds=all", "--error-exitcode=1", "./test"])): exit(1)
    else:
        if(subprocess.call(["./test"])): exit(1)

print("\n########### PARALLEL ###########\n")
for file in testFiles:
    print("\n----- "+file+" -----\n")
    if(subprocess.call(["g++", file, "-o", "test", "-ggdb3", "-std=c++11", "-Wno-literal-suffix", "-fopenmp", "-D", "DM4thParallel", "-D", "DM4thOnlyStandardLiterals", "-D", "DM4thMinOmpLoops=1"])): exit(1)  
    if(subprocess.call(["./test"])): exit(1)