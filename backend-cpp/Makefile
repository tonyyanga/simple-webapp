server: server.c httphandler.c
	gcc -levent `mysql_config --cflags` -g -o server httphandler.c server.c `mysql_config --libs`
