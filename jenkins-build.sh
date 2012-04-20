autoreconf -i && \
rm -rf build && \
rm -rf installation && \
mkdir build && \
mkdir installation && \
cd build && \
CXX="ccache g++" CC="ccache gcc" ../configure --prefix=$WORKSPACE/installation && \
make && \
make check && \
cd tests/ && \
make check-valgrind && \
make my-check