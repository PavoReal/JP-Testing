#! /bin/bash

echo "This will take some time..."
read -p "Shall we start (y or n)? " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
	set -x # Echo commands

	export TARGET=arm-none-eabi
	export PREFIX=/opt/cross-compiler
	export JOBS='8' # If compilation fails, set this to 1

	# Remove existing archives
	rm -rf binutils-*
	rm -rf gcc-*

	# Download the compiler and linker
	curl -O https://ftp.gnu.org/gnu/gcc/gcc-9.2.0/gcc-9.2.0.tar.xz
	curl -O https://ftp.gnu.org/gnu/binutils/binutils-2.33.1.tar.xz

	# Extract them
	tar xf binutils-2.33.1.tar.xz
	tar xf gcc-9.2.0.tar.xz

	pushd binutils-2.33.1
	mkdir build

	pushd build

	# Build binutils
	../configure --target=$TARGET --prefix=$PREFIX
	make -j $JOBS
	sudo make install

	popd
	popd

	pushd gcc-9.2.0
	./contrib/download_prerequisites
	mkdir build
	pushd build
	../configure --target=$TARGET --prefix=$PREFIX --without-headers --with-newlib  --with-gnu-as --with-gnu-ld --enable-languages=c,c++ --enable-frame-pointer=no
	make -j $JOBS
	sudo make install

	popd
	popd

	echo "Done..."
	read -p "Shall I clean up (y or n)? " -n 1 -r
	echo    # (optional) move to a new line
	if [[ $REPLY =~ ^[Yy]$ ]]
	then
		rm -rf binutils-*
		rm -rf gcc-*
	fi
fi
