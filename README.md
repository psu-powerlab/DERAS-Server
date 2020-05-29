# DERAS-Server
Distributed Energy Resource Aggregation System

## Dependencies

After building the following sources, I moved their respective "include" and "lib" files into the project repository so that at the very lease what I used would be clear. 

### OpenSSL

https://www.digitalocean.com/community/tutorials/openssl-essentials-working-with-ssl-certificates-private-keys-and-csrs

Specifically the Generate a Self-Signed Certificate section to be used by server for now. Also you will need to generate a dh.pem file which can be achieved using the following terminal command.

``` bash
openssl dhparam -out dh.pem 2048
```

### Xerces-C++

http://xerces.apache.org/xerces-c/build-3.html

### Boost Libraries

https://www.boost.org/doc/libs/1_73_0/more/getting_started/unix-variants.html

Specifically the source must be build from some programs. Refere to Section 5 "Prepare to Use a Boost Library Binary".

### IEEE 2030.5 Models

https://standards.ieee.org/standard/2030_5-2018.html

I used the ".eap" file to generate all of the resouce classes in their respective source and header files. The program has a 30 day free trial so if you need to get access to the base files I would suggest doing that.

I also used Visual Studios to view the "sep.xsd" file and generate example xml for each resource to test the xerces validation agains the schema. I am unsure if there is an easier way to generate all the sample xml, but that is what I did.

### MySQL Community Server 8.0.20

https://dev.mysql.com/downloads/mysql/

### MySQL Workbench

https://dev.mysql.com/downloads/workbench/

### MySQL Connector/C++

https://dev.mysql.com/downloads/connector/cpp/

### CodeBlocks

http://www.codeblocks.org/downloads/26#linux

#### setup
1. Project -> Build Options... -> Compiler Settings -> Compiler Flags (-std=c++11, -static-libstdc++)
1. Project -> Build Options... -> Linker Settings -> Link libraries: -> Add -> "include all files in project lib folder"
1. Project -> Build Options... -> Linker Settings -> Other linker options: -> (-lmysqlcppconn8, -lxerces-c
, -lxerces-c-3.2, -lpthread, -lssl, -lcrypto)
1. Project -> Build Options... -> Search directories -> Compiler -> Add -> (include)
1. Project -> Build Options... -> Search directories -> Linker -> Add -> (lib)


## Resources

https://en.cppreference.com/w/cpp

https://google.github.io/styleguide/cppguide.html

https://refactoring.guru/

https://gameprogrammingpatterns.com/

## Practice

https://edabit.com/

https://www.hackerrank.com/
