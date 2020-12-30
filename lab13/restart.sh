g++ -c main.cpp -I C:\\'Program Files'\\MySQL\\'MySQL Server 8.0'\\include 
g++ -c ticket.cpp -I C:\\'Program Files'\\MySQL\\'MySQL Server 8.0'\\include 
g++ main.o ticket.o -o a -L C:\\'Program Files'\\MySQL\\'MySQL Server 8.0'\\lib -l mysql -std=c++11