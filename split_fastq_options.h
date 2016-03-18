/*
 * split_fastq_options.h
 *
 *  Created on: Mar 3, 2016
 *      Author: mahajrod
 */

#ifndef SPLIT_FASTQ_OPTIONS_H_
#define SPLIT_FASTQ_OPTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char *short_options = "hi:p:";
char *input_file, *output_prefix;

static struct option long_options[] =
		        {
		          {"help",               no_argument,       NULL, 'h'},
		          {"input_file",  	     required_argument, NULL, 'i'},
		          {"output_prefix",  	 required_argument, NULL, 'p'},
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
				printf("    -i/--input_file           STR    File with paired reads\n"); \
				printf("    -o/--output_prefix        STR    Prefix of output files\n"); \
				exit(0); \
				break;	\
				};	\
			case 'i':	\
				{	\
				input_file = optarg;	\
				break;	\
				};	\
			case 'p':	\
				{	\
				output_prefix = optarg;	\
				break;	\
				};	\
			};	\
		};	\

#endif /* SPLIT_FASTQ_OPTIONS_H_ */
