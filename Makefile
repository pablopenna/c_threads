thread_exe: thread_car.c
	gcc -Wall thread_car.c -o thread_exe -lpthread
clean:
	rm thread_exe
	clear
