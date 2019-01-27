# viirs_sdr_read

A collection of C code for reading NOAA VIIRS SDR (level-1b in NASA parlance) files in HDF5 format.# Compilation commands for the programs in this directory.

Below is an example set of `gcc` invocations to build static binaries for reading each of the VIIRS SDR file types. You might need to fiddle around with the `-l` switch order, `gcc` is a pain that way.
```
export HDF5_INC=/opt/HDF5_5-1.8.3-linux-x86_64-static/include
export HDF5_LIB=/opt/HDF5_5-1.8.3-linux-x86_64-static/lib
export ZLIB=/opt/zlib/lib
export SZIP_LIB=/opt/szip/lib

export INCLUDES='-I/usr/include -I$HDF5_INC'
export LIBS='-L$HDF5_LIB -L$SZIP_LIB -L$ZLIB -L/usr/lib64'
export LFLAGS_GEO='-lhdf5 -lz -lsz -lm -static'
export LFLAGS_SV='-lhdf5_hl -lhdf5 -lz -lsz -lm -static'

gcc -Wall -fPIC Read_VIIRS_GIMGO.c $INCLUDES $LIBS -o Read_VIIRS_GIMGO $LFLAGS_GEO
gcc -Wall -fPIC Read_VIIRS_GMODO.c $INCLUDES $LIBS -o Read_VIIRS_GMODO $LFLAGS_GEO
gcc -Wall -fPIC Read_VIIRS_SVI01.c $INCLUDES $LIBS -o Read_VIIRS_SVI01 $LFLAGS_SV
gcc -Wall -fPIC Read_VIIRS_SVM16.c $INCLUDES $LIBS -o Read_VIIRS_SVM16 $LFLAGS_SV
```
