#include "../header/subsample_fastq.h"

KSEQ_INIT(gzFile, gzread);

int main(int argc, char *argv[])
	{
	//set seed for rand()
	srand(time(NULL));

	//-------------------Parsing options---------------------
	PARSE_OPTIONS;

	//-------------------------------------------------------
	kseq_t *seq_forward, *seq_reverse;

	char * comment;
	fp_forward = gzopen(forward_reads, "r");
	fp_reverse = gzopen(reverse_reads, "r");

	seq_forward = kseq_init(fp_forward);
	seq_reverse = kseq_init(fp_reverse);

	char forward_out_file[strlen(output_prefix) + 9];
	char reverse_out_file[strlen(output_prefix) + 9];

	strcpy(forward_out_file, output_prefix);
	strcat(forward_out_file, "_1.fq");
	strcpy(reverse_out_file, output_prefix);
	strcat(reverse_out_file, "_2.fq");

	fp_forward_out = fopen(forward_out_file, "w");
	fp_reverse_out = fopen(reverse_out_file, "w");



	while ((l_forward = kseq_read(seq_forward)) >= 0)
		{
		l_reverse = kseq_read(seq_reverse);
		random_number = rand() % 100;
		//random_number = arc4random_uniform(100);
		if ( random_number < fraction)
			{
			KSEQ_WRITE(fp_forward_out, seq_forward);
			KSEQ_WRITE(fp_reverse_out, seq_reverse);
			number_of_retained_pairs++;
			}
		total_number_of_pairs++;
		}

	printf("Total pairs\t%i\nRetained pairs\t%i\n", total_number_of_pairs, number_of_retained_pairs);

	kseq_destroy(seq_forward);
	kseq_destroy(seq_reverse);
	gzclose(fp_forward);
	gzclose(fp_reverse);
	fclose(fp_forward_out);
	fclose(fp_reverse_out);

	return 0;
	}
