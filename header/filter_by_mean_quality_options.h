/*
 * filter_by_mean_quality_options.h
 *
 *  Created on: Mar 3, 2016
 *      Author: mahajrod
 */

#ifndef FILTER_BY_MEAN_QUALITY_OPTIONS_H_
#define FILTER_BY_MEAN_QUALITY_OPTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char *short_options = "hmsgq:f:r:p:t:n:u";
char *forward_reads, *reverse_reads, *output_prefix;
long long int quality_threshold;
short int per_tile_stat = 0;
short int miseq = 0;


int quality_offset = 0;
int name_type = 0;
int unpaired = 0;
//int single;
static struct option long_options[] =
		        {
		          {"help",               no_argument,       NULL, 'h'},
		          {"quality_score",  	 required_argument, NULL, 'q'},
		          {"forward_reads",  	 required_argument, NULL, 'f'},
		          {"reverse_reads",  	 required_argument, NULL, 'r'},
		          {"output_prefix",  	 required_argument, NULL, 'p'},
		          {"quality_threshold",  required_argument, NULL, 't'},
		          {"per_tile_stat",      no_argument,       NULL, 's'},
		          {"name_type",      	 required_argument, NULL, 'n'},
                  {"unpaired",      	 no_argument,       NULL, 'u'},
		          {0, 0, 0, 0}
		        };

int rez;
int option_index;

#define PARSE_OPTIONS	\
	while ((rez=getopt_long(argc,argv,short_options, long_options,&option_index))!=-1)	\
		{	\
		switch(rez)	\
			{	\
			case 'h':	\
				{	\
				printf("Usage:\n\tfilter_by_mean_quality -t QUALITY_THRESHOLD -q QUALITY_SCORE -n READ_NAME_TYPE  -f FORWARD_READS -r REVERSE_READS -p OUTPUT_PREFIX\n");\
				printf("Options:\n");	\
				printf("    -t/--quality_threshold    INT    Threshold for minimum mean quality of reads\n"); \
				printf("    -q/--quality_score        STR    Type of quality score. Possible variants: phred33, phred64. Default: phred64\n"); \
				printf("    -n/--name_type            STR    Name type of reads in file. Possible variants: short, illumina, miseq\n"); \
				printf("    -f/--forward_reads        STR    File with forward reads\n"); \
				printf("    -r/--reverse_reads        STR    File with reverse reads. Argument is ignored if -u/--unpaired option is set\n"); \
				printf("    -p/--output_prefix        STR    Prefix of output files\n"); \
                printf("    -u/--unpaired                    Reads are unpaired(single-end)\n"); \
				exit(0); \
				break;	\
				};	\
            case 'u':	\
				{	\
                unpaired = 1; \
				break;	\
				};	\
			case 'f':	\
				{	\
				forward_reads = optarg;	\
				break;	\
				};	\
			case 'r':	\
				{	\
				reverse_reads = optarg;	\
				break;	\
				};	\
			case 'q':	\
				{	\
				if (strcmp(optarg,"phred33") == 0)	\
					{	\
					quality_offset = 33;	\
					} else quality_offset = 64; \
				break;	\
				};	\
			case 'p':	\
				{	\
				output_prefix = optarg;	\
				break;	\
				};	\
			case 't':	\
				{	\
				quality_threshold = atoi(optarg);	\
				break;	\
				};	\
			case 's': \
				{	\
				per_tile_stat = 1;	\
				break;	\
				}	\
			case 'n':	\
				{	\
				if (strcmp(optarg,"short") == 0)	\
					{	\
					name_type = 2;	\
					break;	\
					}	\
				if (strcmp(optarg,"illumina") == 0)	\
					{	\
					name_type = 1;	\
					break; \
					}	\
				if (strcmp(optarg,"miseq") == 0)	\
					{	\
					name_type = 3;	\
					break; \
					}	\
				}	\
			};	\
		};	\

#endif /* FILTER_BY_MEAN_QUALITY_OPTIONS_H_ */
