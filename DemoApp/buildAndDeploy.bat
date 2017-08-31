@echo off
echo Start Build...
mingw32-make
echo Done
python deploy.py
