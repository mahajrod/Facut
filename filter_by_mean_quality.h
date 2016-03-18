#ifndef FILTER_BY_MEAN_QUALITY_H_
#define FILTER_BY_MEAN_QUALITY_H_

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <malloc.h>

#include "kseq.h"
#include "stat.h"
#include "filter_by_mean_quality_options.h"

#define MAX_NUMBER_OF_LANES 50	//At moment lane stat array is static - just to simplify
gzFile fp_forward, fp_reverse;
FILE *fp_forward_pe_out, *fp_forward_se_out, *fp_reverse_pe_out, *fp_reverse_se_out;
long long int total_score_forward = 0, total_score_reverse = 0;
long long int paired = 0, forward_se = 0, reverse_se = 0, discarded_pairs = 0;
double mean_score_forward = 0, mean_score_reverse = 0;
int l_forward, l_reverse;

struct read_name parsed_forward_name;
struct illumina_lane_stat lane_filter_stat_array[MAX_NUMBER_OF_LANES];
int number_of_lanes = 0, previous_lane_number = -1, lane_index = -1;

char *read_name_copy;
#endif // FILTER_BY_MEAN_QUALITY_H_
