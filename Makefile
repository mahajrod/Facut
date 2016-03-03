all: filter_by_mean_quality.c stat.c
		$(CC) -g -O2 stat.c filter_by_mean_quality.c -o filter_by_mean_quality -lz -std=c99

clean:
		rm -f *.o filter_by_mean_quality