#!/bin/bash

g++ boardDriver.cpp include/*.cpp AIs/*.cpp -lncurses -lboost_regex -o 2048
