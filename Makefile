all: filter_by_mean_quality.c stat.c split_fastq.c trim_and_filter_by_mean_quality.c
		@echo "Compiling filter_by_mean_quality ...\n"

		$(CC) -g -O2 stat.c filter_by_mean_quality.c -o filter_by_mean_quality -lz -std=c99
		
		@echo "\nCompiling trim_and_filter_by_mean_quality ...\n"

		$(CC) -g -O2 stat.c trim_and_filter_by_mean_quality.c -o trim_and_filter_by_mean_quality -lz -std=c99

		@echo "\nCompiling split_fastq ...\n"

		$(CC) -g -O2 split_fastq.c -o split_fastq -lz -std=c99
clean:
		rm -f *.o filter_by_mean_quality