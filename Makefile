all: filter_by_mean_quality.c
		# LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/lib/x86_64-linux-gnu/
		$(CC) -g -O2 filter_by_mean_quality.c -o filter_by_mean_quality -lz -std=c99

clean:
		rm -f *.o kseq_test