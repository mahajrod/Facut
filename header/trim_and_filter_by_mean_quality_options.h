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

const char *short_options = "hsgq:f:r:p:t:n:a:b:y:z:l:";
char *forward_reads, *reverse_reads, *output_prefix;
long long int quality_threshold;
long long int forward_start = 1, forward_end = 0, reverse_start = 1, reverse_end = 0;
long long int min_read_length = 0;
short int per_tile_stat = 0;

int quality_offset = 0;
int name_type = 0;

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

		          {"min_read_length",       required_argument, NULL, 'l'},
		          {"forward_start",      required_argument, NULL, 'a'},
		          {"forward_end",      	 required_argument, NULL, 'b'},
		          {"reverse_start",      required_argument, NULL, 'y'},
		          {"reverse_end",      	 required_argument, NULL, 'z'},

		          {0, 0, 0, 0}
		        };

int rez;
int option_index;

/*
 * 				printf("    -a/--forward_start        INT    First base to retain in forward read. Default: 1\n"); \
 * 				printf("    -y/--reverse_start        INT    First base to retain in reverse read. Default: 1\n"); \
 * 				printf("    -l/--min_read_length      INT    Minimum length after trimming to retain read. Default: any\n"); \
 */
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
				printf("    -n/--name_type            STR    Name type of reads in file. Possible variants: short, illumina, iontorrent, sra\n"); \
				printf("    -f/--forward_reads        STR    File with forward reads\n"); \
				printf("    -r/--reverse_reads        STR    File with reverse reads\n"); \
				printf("    -p/--output_prefix        STR    Prefix of output files\n"); \
				printf("    -b/--forward_end          INT    Last base to retain in forward read. Default: last\n"); \
				printf("    -z/--reverse_end          INT    Last base to retain in reverse read. Default: last\n"); \
				exit(0); \
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
				if (strcmp(optarg,"iontorrent") == 0)	\
                    {    \
                    name_type = 4;    \
                    break; \
                    }	\
				if (strcmp(optarg,"sra") == 0)	\
                    {    \
                    name_type = 5;    \
                    break; \
                    }	\
				}	\
			case 'b': \
				{	\
				if (atoi(optarg) > 0)	\
					{	\
					forward_end = atoi(optarg);	\
					}	\
				break;	\
				}	\
			case 'z': \
				{	\
				if (atoi(optarg) > 0)	\
					{	\
					reverse_end = atoi(optarg);	\
					}	\
				break;	\
				}	\
			};	\
		};	\
/*
 *
 * 			case 'a': \
				{	\
				if (atoi(optarg) > 1)	\
					{	\
					forward_start = atoi(optarg);	\
					}	\
				break;	\
				}	\
			case 'y': \
				{	\
				if (atoi(optarg) > 1)	\
					{	\
					reverse_start = atoi(optarg);	\
					}	\
				break;	\
				}	\

			case 'l': \
				{	\
				if (atoi(optarg) > 0)	\
					{	\
					min_read_length = atoi(optarg);	\
					}	\
				break;	\
				}	\
 *
 *
 */


#endif /* FILTER_BY_MEAN_QUALITY_OPTIONS_H_ */
