CUIKSUITE

Overview

  The CuikSuite is a set of applications to solve position analysis
  and path planning problems with applications mainly to robotics, but also
  to molecular biology.

Documentation
  
  The documentation can be generated executing
     cd build
     make doc
  After this, the main page is stored in
     CuikSuite/doc/html/index.html

  This documentation can also be browsed from
     http://www.iri.upc.edu/people/porta/Soft/CuikSuite-Doc/html/index.html

License

  CuikSuite is licensed under a GPLv3 License.

Pre-Requisites

  To compile the CuikSuite you need at least:
    - Cmake http://www.cmake.org
    - The Coin-OR library http://www.coin-or.org
    - The LAPACK library
    - Flex http://flex.sourceforge.net
    - Bison http://www.gnu.org/software/bison
    - Solid http://www.dtecta.com/files/solid-3.5.6.tgz
  In Linux most of those packages are available from standard repositories.
  Extra functionalities requiere additonal dependencies. The set of functionalities
  are compiled by default but they can be deactuvated setting the right variables
  when calling cmake (see the CMakeList.txt header).
  
Installation

  Download the most recent version of the package from
     http://www.iri.upc.edu/people/porta/Soft/CuikSuite.tar.gz

  Uncompress it
     tar xzf CuikSuite.tar.gz

  Change to the build directory
     cd CuikSuite/build

  Generate the makefiles
     cmake ..

  Compile
     make

  After this, the executables are localy available in CuikSuite/bin.
  You can install them into the system executing
     make install
