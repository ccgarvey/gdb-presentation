all: serial parallel

serial: elementwise_product.o file_io.o
	g++ elementwise_product.o file_io.o -o serial_elementwise_product

elementwise_product.o: elementwise_product.cpp file_io.hpp
	g++ elementwise_product.cpp -c

parallel: mpi_elementwise_product.o file_io.o
	mpic++ mpi_elementwise_product.o file_io.o -o mpi_elementwise_product

mpi_elementwise_product.o: mpi_elementwise_product.cpp file_io.hpp
	mpic++ mpi_elementwise_product.cpp -c

file_io.o: file_io.cpp file_io.hpp
	g++ file_io.cpp -c

clean:
	rm -f elementwise_product.o file_io.o serial_elementwise_product mpi_elemenetwise_product.o mpi_elementwise_product
