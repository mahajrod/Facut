#include "split_fastq.h"

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
	{
	//-------------------Parsing options---------------------
	PARSE_OPTIONS;
	//-------------------------------------------------------
	kseq_t *seq_input;

	fp_input = gzopen(input_file, "r");

	seq_input = kseq_init(fp_input);

	char forward_out_file[strlen(output_prefix) + 9];
	char reverse_out_file[strlen(output_prefix) + 9];

	strcpy(forward_out_file, output_prefix);
	strcat(forward_out_file, "_1.fq");
	strcpy(reverse_out_file, output_prefix);
	strcat(reverse_out_file, "_2.fq");

	fp_forward_out = fopen(forward_out_file, "w");
	fp_reverse_out = fopen(reverse_out_file, "w");


	while ((l_input = kseq_read(seq_input)) >= 0)
		{
		fprintf(fp_forward_out, "@%s\n%s\n+\n%s\n", seq_input->name.s, seq_input->seq.s, seq_input->qual.s);
		if ((l_input = kseq_read(seq_input)) >= 0)
			{
			fprintf(fp_reverse_out, "@%s\n%s\n+\n%s\n", seq_input->name.s, seq_input->seq.s, seq_input->qual.s);
			}
		else
			{
			printf("Truncated input file");
			exit(-1);
			}
		number_of_pairs++;
		}

	printf("Total pairs\t%i", number_of_pairs);

	kseq_destroy(seq_input);
	gzclose(fp_input);
	fclose(fp_forward_out);
	fclose(fp_reverse_out);

	return 0;
	}
