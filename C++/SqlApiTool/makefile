server:
	g++ server.cpp -o server
db:testmain.cpp database.cpp
	g++ -o dbtest testmain.cpp database.cpp `mysql_config --cflags --libs` 
	
clean:
	rm -r -f server *.o dbtest
