#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "kseq.h"
#include "stat.h"
#include "parse_options.h"

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
	{
	//-------------------Parsing options---------------------
	PARSE_OPTIONS;

	gzFile fp_forward, fp_reverse;
	FILE *fp_forward_pe_out, *fp_forward_se_out, *fp_reverse_pe_out, *fp_reverse_se_out;
	kseq_t *seq_forward, *seq_reverse;
	long long int total_score_forward = 0, total_score_reverse = 0;
	long long int paired = 0, forward_se = 0, reverse_se = 0, discarded_pairs = 0;
	double mean_score_forward = 0, mean_score_reverse = 0;
	int len_forward, len_reverse;

	int l_forward, l_reverse;

	fp_forward = gzopen(forward_reads, "r");
	fp_reverse = gzopen(reverse_reads, "r");

	seq_forward = kseq_init(fp_forward);
	seq_reverse = kseq_init(fp_reverse);

	char forward_pe_out_file[strlen(output_prefix) + 9];
	char forward_se_out_file[strlen(output_prefix) + 9];
	char reverse_pe_out_file[strlen(output_prefix) + 9];
	char reverse_se_out_file[strlen(output_prefix) + 9];
	strcpy(forward_pe_out_file, output_prefix);
	strcat(forward_pe_out_file, "_1.pe.fq");

	strcpy(forward_se_out_file, output_prefix);
	strcat(forward_se_out_file, "_1.se.fq");
	strcpy(reverse_pe_out_file, output_prefix);
	strcat(reverse_pe_out_file, "_2.pe.fq");
	strcpy(reverse_se_out_file, output_prefix);
	strcat(reverse_se_out_file, "_2.se.fq");

	fp_forward_pe_out = fopen(forward_pe_out_file, "w");
	fp_forward_se_out = fopen(forward_se_out_file, "w");
	fp_reverse_pe_out = fopen(reverse_pe_out_file, "w");
	fp_reverse_se_out = fopen(reverse_se_out_file, "w");

	char *parsed[5];

	while ((l_forward = kseq_read(seq_forward)) >= 0)
		{
		l_reverse = kseq_read(seq_reverse);

		mean_score_forward = 0;

		parse_read_name(seq_forward->name.s, parsed);

		for (int i = 0; i < 5; i++)
			{
			printf("%s\n", parsed[i]);
			}

		len_forward = strlen(seq_forward->qual.s);
		for (int i =0; i < len_forward; i++)
			{
			mean_score_forward += seq_forward->qual.s[i];
			}
		mean_score_forward /= len_forward;
		mean_score_forward -= quality_offset;

		mean_score_reverse = 0;
		len_reverse = strlen(seq_reverse->qual.s);
		for (int i =0; i < len_reverse; i++)
			{
			mean_score_reverse += seq_reverse->qual.s[i];
			}
		mean_score_reverse /= len_reverse;
		mean_score_reverse -= quality_offset;

		/*
		printf("forward\n");
		printf("name: %s\n", seq_forward->name.s);
		if (seq->comment.l) printf("comment: %s\n", seq->comment.s);
		printf("seq: %s\n", seq_forward->seq.s);
		if (seq_forward->qual.l) printf("qual: %s\n", seq_forward->qual.s);
		printf("%f\n", mean_score_forward);

		printf("reverse\n");
		printf("name: %s\n", seq_reverse->name.s);
		if (seq->comment.l) printf("comment: %s\n", seq->comment.s);
		printf("seq: %s\n", seq_reverse->seq.s);
		if (seq_reverse->qual.l) printf("qual: %s\n", seq_reverse->qual.s);
		printf("%f\n", mean_score_reverse);
		*/
		//printf("%f\t%f\n", mean_score_forward, mean_score_reverse);
		if ((mean_score_forward >= quality_threshold) && (mean_score_reverse >= quality_threshold))
			{
			fprintf(fp_forward_pe_out, "@%s\n%s\n+\n%s\n", seq_forward->name.s, seq_forward->seq.s, seq_forward->qual.s);
			fprintf(fp_reverse_pe_out, "@%s\n%s\n+\n%s\n", seq_reverse->name.s, seq_reverse->seq.s, seq_reverse->qual.s);
			paired += 1;
			} else
			{
			if ((mean_score_forward >= quality_threshold) && (mean_score_reverse < quality_threshold))
				{
				fprintf(fp_forward_se_out, "@%s\n%s\n+\n%s\n", seq_forward->name.s, seq_forward->seq.s, seq_forward->qual.s);
				forward_se += 1;
				} else
				{
				if ((mean_score_forward < quality_threshold) && (mean_score_reverse >= quality_threshold))
					{
					fprintf(fp_reverse_se_out, "@%s\n%s\n+\n%s\n", seq_reverse->name.s, seq_reverse->seq.s, seq_reverse->qual.s);
					reverse_se += 1;
					} else discarded_pairs += 1;
				}
			}

		}

	//printf("return value: %d\n", l_forward);
	kseq_destroy(seq_forward);
	kseq_destroy(seq_reverse);
	gzclose(fp_forward);
	gzclose(fp_reverse);
	fclose(fp_forward_pe_out);
	fclose(fp_forward_se_out);
	fclose(fp_reverse_pe_out);
	fclose(fp_reverse_se_out);

	printf("Paires retained:\t%i\nForward only retained:\t%i\nReverse only retained:\t%i\nPairs discarded:\t%i\n", paired, forward_se, reverse_se, discarded_pairs);
	return 0;

	}
