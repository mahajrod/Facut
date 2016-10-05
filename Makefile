all: src/filter_by_mean_quality.c src/stat.c src/split_fastq.c src/trim_and_filter_by_mean_quality.c src/subsample_fastq.c src/split_fastq_by_lane.c
		@echo "Compiling filter_by_mean_quality ...\n"

		$(CC) -g -O2 src/stat.c src/filter_by_mean_quality.c -o bin/filter_by_mean_quality -lz -std=c99
		
		@echo "\nCompiling trim_and_filter_by_mean_quality ...\n"

		$(CC) -g -O2 src/stat.c src/trim_and_filter_by_mean_quality.c -o bin/trim_and_filter_by_mean_quality -lz -std=c99

		@echo "\nCompiling split_fastq ...\n"

		$(CC) -g -O2 src/split_fastq.c -o bin/split_fastq -lz -std=c99

		@echo "\nCompiling subsample_fastq ...\n"

		$(CC) -g -O2 src/subsample_fastq.c -o bin/subsample_fastq -lz -std=c99

		@echo "\nCompiling split_fastq_by_lane ...\n"

		$(CC) -g -O2 src/stat.c src/split_fastq_by_lane.c -o bin/split_fastq_by_lane -lz -std=c99

clean:
		rm -f *.o filter_by_mean_quality