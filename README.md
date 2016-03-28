# interview

This is an answer application to an interview question. It purposes to highlight C++ coding experience and comfort, as well as overall thinking and patterns in the domain of software design and architecture. 

Omitted from this sample application, in the least at this time, are such things such as threads, sockets, events / signals, windows-linux specific implementations, logging and other such topics that could be added so as to demonstrate capacity and understanding of these topics. It is hoped that through what is herein written, the authors' capacity for such can be inferred. 

C++11 has been used, and the only platform on which the compilation has been tested is OS X g++, version output below

> Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
> 
> Apple LLVM version 7.0.0 (clang-700.1.76)
> 
> Target: x86_64-apple-darwin15.4.0
> 
> Thread model: posix

and the boost libraries, version 1.59.
A simple modification to the Makefile, detailing the location of the boost libraries and includes should be all that is required for the compilation of the code. 

I would suggest one begin by taking a look and reading through, the overview diagram in the diagrams folder, it should not take much time, and will well help a measure of the code.
