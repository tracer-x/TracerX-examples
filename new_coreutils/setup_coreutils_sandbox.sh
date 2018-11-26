#!/bin/bash
echo "===================="
echo "| SET UP COREUTILS |"
echo "===================="

if [ ! -d "coreutils-6.10" ]; then
	wget -O - https://ftp.gnu.org/gnu/coreutils/coreutils-6.10.tar.gz | tar xzf -
fi
export LLVM_COMPILER=clang
cd coreutils-6.10
mkdir obj-llvm;
cd obj-llvm
CC=wllvm ../configure --disable-nls CFLAGS="-g"
CC=wllvm make
CC=wllvm make -C src arch hostname
cd src
find . -executable -type f | xargs -I '{}' extract-bc '{}'
cd ../../..


if [ ! -d "coreutils-6.11" ]; then
	wget -O - https://ftp.gnu.org/gnu/coreutils/coreutils-6.11.tar.gz | tar xzf -
fi
cd coreutils-6.11
mkdir obj-llvm;
cd obj-llvm
CC=wllvm ../configure --disable-nls CFLAGS="-g"
CC=wllvm make
CC=wllvm make -C src arch hostname
cd src
find . -executable -type f | xargs -I '{}' extract-bc '{}'
cd ../../..

echo "===================="
echo "|  SET UP SANDBOX  |"
echo "===================="

wget https://www.doc.ic.ac.uk/~cristic/klee/testing-env.sh
env -i /bin/bash -c '(source testing-env.sh; env >test.env)'
wget -O - https://www.doc.ic.ac.uk/~cristic/klee/sandbox.tgz | tar -xvzf - -C /tmp

echo "===================="
echo "|     FINISH       |"
echo "===================="