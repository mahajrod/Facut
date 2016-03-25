#include "../header/split_fastq.h"

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
	{
	//-------------------Parsing options---------------------
	PARSE_OPTIONS;
	//-------------------------------------------------------
	kseq_t *seq_input;

	char * comment;
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

		KSEQ_WRITE(fp_forward_out, seq_input);

		if ((l_input = kseq_read(seq_input)) >= 0)
			{

			KSEQ_WRITE(fp_reverse_out, seq_input);

			}
		else
			{
			printf("Truncated input file\n");
			exit(-1);
			}
		number_of_pairs++;
		}

	printf("Total pairs\t%i\n", number_of_pairs);

	kseq_destroy(seq_input);
	gzclose(fp_input);
	fclose(fp_forward_out);
	fclose(fp_reverse_out);

	return 0;
	}
