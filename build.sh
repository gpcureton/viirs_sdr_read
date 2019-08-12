#!/bin/bash
# Commands to build a series of binaries to test the reading of various 
# NOAA VIIRS SDR files, and a VIIRS LWM file, all in HDF5 format.

# gitlab.ssec.wisc.edu:5555/cspp/buildbucket/buildbucket_gcc64:latest
curdir=$PWD
#cd src
echo $(which gcc)
echo "Current directory is :"$curdir
export HDF4_DIR=/opt/hdf4
export HDF5_DIR=/opt/hdf5
export NETCDF_DIR=/opt/netcdf

make -f Makefile_static clean
#make -f Makefile_static Read_VIIRS_GMODO
#make -f Makefile_static Read_VIIRS_GMTCO
#make -f Makefile_static Read_VIIRS_GIMGO
#make -f Makefile_static Read_VIIRS_GITCO
make -f Makefile_static Read_VIIRS_SVI01
make -f Makefile_static Read_VIIRS_SVM16
#make -f Makefile_static Read_VIIRS_LWM

#for target in Read_VIIRS_GIMGO Read_VIIRS_GITCO; \
#for target in Read_VIIRS_GMODO Read_VIIRS_GMTCO Read_VIIRS_GIMGO Read_VIIRS_GITCO Read_VIIRS_SVI01 Read_VIIRS_SVM16 Read_VIIRS_LWM; \
#do \
    ##make -n -f Makefile_static $target; \
    #make -f Makefile_static $target; \
#done

cd $curdir
#find ./ -name "Read_VIIRS_SVI01" -print
