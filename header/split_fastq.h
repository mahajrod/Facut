#ifndef SPLIT_FASTQ_H_
#define SPLIT_FASTQ_H_

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <malloc.h>

#include "kseq.h"
#include "split_fastq_options.h"

gzFile fp_input;
FILE *fp_forward_out, *fp_reverse_out;
int l_input;
long long int number_of_pairs = 0;

#endif // SPLIT_FASTQ_H_
