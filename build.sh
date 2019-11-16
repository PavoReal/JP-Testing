#! /bin/bash

if ! [ -x "$(command -v arm-none-eabi-gcc)" ]; then
	export PATH="$PATH:/opt/cross-compiler/bin"
	echo "Trying /opt/cross-compiler/bin"
fi

CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJDUMP=arm-none-eabi-objdump
OBJCOPY=arm-none-eabi-objcopy

ASM_FLAGS="--warn --fatal-warnings -mcpu=arm1176jzf-s -mfpu=vfpv2"
CC_FLAGS="-Wall -Wextra -Werror -O2 -nostartfiles -ffreestanding -mcpu=arm1176jzf-s -mtune=arm1176jzf-s  -I../newlib/libc/include"
LD_FLAGS="-lc -lm -T memmap"

shopt -s nullglob

mkdir -p build/

pushd build/ > /dev/null

rm -rf *.o

for i in ../src/*.s; do
    [ -f "$i" ] || break

    echo "ASM $(basename $i)"
    $AS $ASM_FLAGS $i -o $(basename $i).o
done

for i in ../src/*.c; do
    [ -f "$i" ] || break

    echo "CC $(basename $i)"
    $CC -c $CC_FLAGS $i -o $(basename $i).o
done

cp ../src/memmap ./

list=(*.o)

echo "CC ${list[@]} --> main.elf"
$CC $CC_FLAGS $LD_FLAGS *.o -o main.elf

$OBJDUMP -D main.elf > main.list
$OBJCOPY --srec-forceS3 main.elf -O srec main.srec

echo "OBJCOPY main.elf --> kernel.img"
$OBJCOPY main.elf -O binary kernel.img

popd > /dev/null
echo "Done..."