/*
 * split_fastq_options.h
 *
 *  Created on: Mar 3, 2016
 *      Author: mahajrod
 */

#ifndef SUBSAMPLE_FASTQ_OPTIONS_H_
#define SUBSAMPLE_FASTQ_OPTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char *short_options = "hf:r:p:a:";
char *reverse_reads, *forward_reads, *output_prefix;
int fraction = 0;

static struct option long_options[] =
		        {
		          {"help",               no_argument,       NULL, 'h'},
		          {"forward_reads",  	 required_argument, NULL, 'f'},
		          {"reverse_reads",  	 required_argument, NULL, 'r'},
		          {"output_prefix",  	 required_argument, NULL, 'p'},
		          {"fraction",  	     required_argument, NULL, 'a'},
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
				printf("Usage:\n\tsplit_fastq -i INPUT_FILE -o OUTPUT_PREFIX\n");\
				printf("Options:\n");	\
				printf("    -f/--forward_reads        STR    File with forward reads\n"); \
				printf("    -r/--reverse_reads        STR    File with reverse reads\n"); \
				printf("    -p/--output_prefix        STR          Prefix of output files\n"); \
				printf("    -a/--fraction             INT\\FLOAT    Approximate fraction(in fact probability to retain) of read pairs to retain.\n"); \
				printf("                                           Can be set both as fraction or percent, i.e 20 or 0.2.\n"); \
				printf("                                           Also this number is rounded to hundredth.\n"); \
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
			case 'p':	\
				{	\
				output_prefix = optarg;	\
				break;	\
				};	\
			case 'a':	\
				{	\
				fraction = atof(optarg) > 1 ? (int) (atof(optarg) + 0.5) : (int) ((atof(optarg) * 100) + 0.5) ;	\
				if (fraction > 100) \
					{	\
					printf("ERROR: fraction can't be greater than 100");	\
					exit(-1);	\
					}	\
				break;	\
				};	\
			};	\
		};	\

#endif /* SUBSAMPLE_FASTQ_OPTIONS_H_ */
