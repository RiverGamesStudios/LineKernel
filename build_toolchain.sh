#!/bin/bash
set -euo pipefail

# Update and install dependencies
sudo apt update || true  # Ignore repo errors
sudo apt install -y build-essential bison flex libgmp-dev libmpc-dev libmpfr-dev texinfo libisl-dev

# Set variables
export PREFIX="${PREFIX:-$HOME/opt/cross}"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# Create directories
mkdir -p $HOME/src
cd $HOME/src

# Download sources (using latest versions as of 2024)
wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
wget https://ftp.gnu.org/gnu/gcc/gcc-14.2.0/gcc-14.2.0.tar.xz

# Extract
tar xf binutils-2.42.tar.xz
tar xf gcc-14.2.0.tar.xz

# Build binutils
mkdir build-binutils
cd build-binutils
../binutils-2.42/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install
cd ..

# Build GCC
cd gcc-14.2.0
contrib/download_prerequisites
cd ..
mkdir build-gcc
cd build-gcc
../gcc-14.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)
make install-gcc
make install-target-libgcc

# Add to PATH
echo 'export PATH="$HOME/opt/cross/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc

echo "Cross-compiler installed. Run 'i686-elf-gcc --version' to verify."