#!/bin/bash

sudo modprobe nbd

sudo echo 4 > /sys/block/nbd0/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd1/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd2/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd3/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd4/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd5/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd6/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd7/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd8/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd9/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd10/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd11/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd12/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd13/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd14/queue/max_sectors_kb
sudo echo 4 > /sys/block/nbd15/queue/max_sectors_kb
