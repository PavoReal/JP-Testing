#! /bin/bash

CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJDUMP=arm-none-eabi-objdump
OBJCOPY=arm-none-eabi-objcopy

ASM_FLAGS="--warn --fatal-warnings -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard"
CC_FLAGS="-Wall -Wextra -Werror -O2 -nostdlib -nostartfiles -ffreestanding -c -mcpu=arm1176jzf-s -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -I../newlib/include"
LD_FLAGS="-L../newlib/arm-none-eabi/newlib -lc -lg -lm -lgcc"

mkdir -p build/

pushd build/ > /dev/null

for i in ../src/*.s; do
    [ -f "$i" ] || break

    echo "$AS $ASM_FLAGS $i -o $(basename $i).o"
    $AS $ASM_FLAGS $i -o $(basename $i).o
done

for i in ../src/*.c; do
    [ -f "$i" ] || break

    echo "$CC $CC_FLAGS $i -o $(basename $i).o"
    $CC $CC_FLAGS $i -o $(basename $i).o
done

# cp ../src/memmap ./

echo "$LD $LD_FLAGS *.o -o main.elf"
$LD $LD_FLAGS *.o -o main.elf
# $OBJDUMP -D main.elf > main.list
# $OBJCOPY --srec-forceS3 main.elf -O srec main.srec
echo "$OBJCOPY main.elf -O binary kernel.img"
$OBJCOPY main.elf -O binary kernel.img

popd > /dev/null
echo "Done..."