#ifndef FILTER_BY_MEAN_QUALITY_H_
#define FILTER_BY_MEAN_QUALITY_H_

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

#endif // FILTER_BY_MEAN_QUALITY_H_
