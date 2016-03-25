#ifndef SUBSAMPLE_FASTQ_H_
#define SUBSAMPLE_FASTQ_H_

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <malloc.h>

#include "kseq.h"
#include "subsample_fastq_options.h"

gzFile fp_forward, fp_reverse;
FILE *fp_forward_out, *fp_reverse_out;
int l_forward, l_reverse;
int random_number;
long long int total_number_of_pairs = 0, number_of_retained_pairs = 0;

#endif // SUBSAMPLE_FASTQ_H_
