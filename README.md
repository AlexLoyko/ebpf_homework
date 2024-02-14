# ebpf_homework
Homework for EECS 6891

## Background
My homework implementation is likely not tradinitional.
I've started with libbpf and implementing both parts in C, but realized that there were 
a series of parts that had nothing to do with eBPF, though had to be implemented (histogram handling is only possible through an array and custom parsing and printing). Given that the homework instructions didn't apply restrictions on the technology of use, I've decided to utilize BCC, which, in my honest opinion, is a much better tool for the job due to its conciseness.

## Installation
To get the necessary dependencies, run
```
echo deb http://cloudfront.debian.net/debian sid main >> /etc/apt/sources.list
sudo apt-get install -y bpfcc-tools libbpfcc libbpfcc-dev linux-headers-$(uname -r)
```

## Running
There is a Makefile (although dummy), which simply adds executable priviledges to the `iolatency` file.
This was meant to be consistent with the spec. So, just running the following is sufficient:
```
make
./iolatency 5
```

## Sample printouts
```
oleloy@debian:~/ebpf_homework$ make
oleloy@debian:~/ebpf_homework$ sudo ./iolatency 5
Tracing... Hit Ctrl-C to end.
-----------------------------------------------------------------------------
     usecs               : count     distribution
         0 -> 1          : 0        |                                        |
         2 -> 3          : 0        |                                        |
         4 -> 7          : 0        |                                        |
         8 -> 15         : 0        |                                        |
        16 -> 31         : 0        |                                        |
        32 -> 63         : 0        |                                        |
        64 -> 127        : 1        |****************************************|
       128 -> 255        : 0        |                                        |
       256 -> 511        : 0        |                                        |
       512 -> 1023       : 1        |****************************************|
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
     usecs               : count     distribution
         0 -> 1          : 0        |                                        |
         2 -> 3          : 0        |                                        |
         4 -> 7          : 0        |                                        |
         8 -> 15         : 0        |                                        |
        16 -> 31         : 0        |                                        |
        32 -> 63         : 0        |                                        |
        64 -> 127        : 0        |                                        |
       128 -> 255        : 0        |                                        |
       256 -> 511        : 1        |****************************************|
       512 -> 1023       : 0        |                                        |
      1024 -> 2047       : 1        |****************************************|
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
     usecs               : count     distribution
         0 -> 1          : 0        |                                        |
         2 -> 3          : 0        |                                        |
         4 -> 7          : 0        |                                        |
         8 -> 15         : 0        |                                        |
        16 -> 31         : 0        |                                        |
        32 -> 63         : 0        |                                        |
        64 -> 127        : 0        |                                        |
       128 -> 255        : 1        |****************************************|
       256 -> 511        : 1        |****************************************|
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
     usecs               : count     distribution
         0 -> 1          : 0        |                                        |
         2 -> 3          : 0        |                                        |
         4 -> 7          : 0        |                                        |
         8 -> 15         : 0        |                                        |
        16 -> 31         : 0        |                                        |
        32 -> 63         : 8        |******                                  |
        64 -> 127        : 6        |****                                    |
       128 -> 255        : 22       |****************                        |
       256 -> 511        : 29       |**********************                  |
       512 -> 1023       : 52       |****************************************|
      1024 -> 2047       : 46       |***********************************     |
      2048 -> 4095       : 36       |***************************             |
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
     usecs               : count     distribution
         0 -> 1          : 0        |                                        |
         2 -> 3          : 0        |                                        |
         4 -> 7          : 0        |                                        |
         8 -> 15         : 0        |                                        |
        16 -> 31         : 0        |                                        |
        32 -> 63         : 0        |                                        |
        64 -> 127        : 1        |****************************************|
       128 -> 255        : 0        |                                        |
       256 -> 511        : 0        |                                        |
       512 -> 1023       : 0        |                                        |
      1024 -> 2047       : 1        |****************************************|
-----------------------------------------------------------------------------
```
