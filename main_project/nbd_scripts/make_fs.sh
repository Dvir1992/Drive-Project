#!/bin/bash

sudo mkfs.ext2 /dev/nbd5
sudo mount /dev/nbd5 /home/dvir-hazut/git/main_project/user_dir
