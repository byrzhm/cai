# cai - a toy compiler

## 简介

cai是一个玩具编译器, 生成的目标代码为riscv64, 生成的目标代码可以在spike上运行。该项目仅为学习编译原理而写, 不具有实用性。本项目主要参考了教程[Write-a-Compiler](https://norasandler.com/2017/11/29/Write-a-Compiler.html).

## 依赖 (建议安装riscv64-unknown-elf)

- [riscv-gnu-toolchain](https://github.com/riscv/riscv-gnu-toolchain)
- [riscv-pk](https://github.com/riscv-software-src/riscv-pk.git)
- [spike](https://github.com/riscv-software-src/riscv-isa-sim.git)

### 1. riscv-gnu-toolchain

安装依赖

``` bash
sudo apt-get install autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build git cmake libglib2.0-dev libboost-all-dev device-tree-compiler
```

#### 获取 riscv-gnu-toolchain 源码

``` bash
git clone https://github.com/riscv/riscv-gnu-toolchain
cd riscv-gnu-toolchain
git submodule update --init --recursive
```

#### riscv-gnu-toolchain 编译与安装

``` bash
./configure --prefix=/usr/local/riscv
sudo make -j$(nproc) # risv64-unknown-elf
# or sudo make linux -j$(nproc) # riscv64-unknown-linux-gnu
```

> 建议安装riscv64-unknown-elf, 即 `sudo make -j$(nproc)`

### 2. riscv-pk

#### 获取riscv-pk源码

``` bash
git clone https://github.com/riscv-software-src/riscv-pk.git
```

#### riscv-pk 编译与安装

``` bash
cd riscv-pk
mkdir build
cd build
../configure --prefix=/usr/local/riscv --host=riscv64-unknown-linux-gnu --with-arch=rv64gc_zifencei
# or ../configure --prefix=/usr/local/riscv --host=riscv64-unknown-elf --with-arch=rv64gc_zifencei
make -j$(nproc)
sudo make install
```

> 1. 如果编译失败(riscv64-unknown-linux-gnu), 并且失败的原因是缺失 `gnu/stubs-lp64.h`, 执行下面的命令, 然后重新编译安装riscv-pk
> 2. 如果是riscv64-unknown-elf, 一般不会出现这个问题

``` bash
cd /usr/local/riscv/sysroot/include/gnu/
sudo cp stubs-lp64d.h stubs-lp64.h
```

### 3. spike

#### 获取spike源码

``` bash
git clone https://github.com/riscv-software-src/riscv-isa-sim.git
```

#### spike 编译与安装

``` bash
cd riscv-isa-sim
mkdir build
cd build
../configure --prefix=/usr/local/riscv --with-target=riscv64-unknown-linux-gnu
# or ../configure --prefix=/usr/local/riscv # default is riscv64-unknown-elf
make -j$(nproc)
sudo make install
```

## Building Cai Compiler

``` bash
mkdir build
cd build
cmake ..
make
```

## Usage of Cai Compiler

``` bash
./cai example.cai -o example.s
riscv64-unknown-linux-gnu-gcc -static -o example example.s
# or riscv64-unknown-elf-gcc -o example example.s
spike pk example
```
