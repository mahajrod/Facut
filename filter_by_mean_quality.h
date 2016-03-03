#ifndef FILTER_BY_MEAN_QUALITY_H_
#define FILTER_BY_MEAN_QUALITY_H_

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "kseq.h"
#include "stat.h"
#include "parse_options.h"

gzFile fp_forward, fp_reverse;
FILE *fp_forward_pe_out, *fp_forward_se_out, *fp_reverse_pe_out, *fp_reverse_se_out;
long long int total_score_forward = 0, total_score_reverse = 0;
long long int paired = 0, forward_se = 0, reverse_se = 0, discarded_pairs = 0;
double mean_score_forward = 0, mean_score_reverse = 0;
int len_forward, len_reverse;
int l_forward, l_reverse;

#endif // FILTER_BY_MEAN_QUALITY_H_
