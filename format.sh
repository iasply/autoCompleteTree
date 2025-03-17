#!/bin/sh

make format
chmod 777 -R ./src/
chmod 777 -R ./include/
ls -la ./src
ls -la ./include