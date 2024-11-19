
 -- /!\ Stream2.c is not finished yet. The results should not be right. --

STREAM and STREAM2 benchmark

The STREAM benchmark is a simple synthetic benchmark program that 
	measures sustainable memory bandwidth (in MB/s) and the corresponding 
	computation rate for simple vector kernels.

The STREAM2 is an attempt to extend the functionality of the STREAM benchmark 
	in two important ways: measuring sustained bandwidth at all levels of 
	the cache hierarchy, and more clearly exposing the performance differences 
	between reads and writes 
  
You can find more information about the both versions on :
	https://www.cs.virginia.edu/stream/

	
For compilation you can use make. There are 3 makefiles. Each ones build STREAM and STREAM2
from fortran code (-f) and C code (-c) :

 --	" Makefile " is for x86 architecture (-x86), you can call it 
	with the default commande : make 
	The result from this compilation should be :
	stream-x86-c, stream-x86-f, stream2-x86-c and stream2-x86-f 

 --	" Makefile.arm " is for arm 32 bits architecture (-arm), you can call
	with the commande : make -f Makefile.arm 
	The result from this compilation should be :
	stream-arm-c, stream-arm-f, stream2-arm-c and stream2-arm-f 

 --	" Makefile.aarch64 " is for arm 32 bits architecture (-aarch64), you can call
	with the commande : make -f Makefile.aarch64
	The result from this compilation should be :
	stream-aarch64-c, stream-aarch64-f, stream2-aarch64-c and stream2-aarch64-f

 --	You can find a "clean" target for make. You can call it with : make clean

About dependencies : 

 -- 	for C code and the makefiles you need cross compiler for the 3 architectures,
	and build-essentia. You can use this commands for the installation :

	sudo apt-get install build-essential
	sudo apt-get install gcc-aarch64-linux-gnu 
	sudo apt-get install gcc-arm-linux-gnueabi
		   
	
 --	for fortran77 compilation on x86 architecture, you need gfortran. 
	You can install it with : 

	sudo apt-get install gfortran

 -- 	for fortran77 on arm architecture 32 and 64 bits, you need : gfortran-8
	for both arm architecture. You can install it with : 
	
	sudo apt-get install gfortran-8-aarch64-linux-gnu
	sudo apt-get install gfortran-8-arm-linux-gnueabi


	
 

