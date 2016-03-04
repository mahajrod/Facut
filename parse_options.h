/*
 * options.h
 *
 *  Created on: Mar 3, 2016
 *      Author: mahajrod
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char *short_options = "hsgq:f:r:p:t:n:";
char *forward_reads, *reverse_reads, *output_prefix;
long long int quality_threshold;
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
				printf("This is demo help. Try -h or --help.\n");	\
				printf("option_index = %d (\"%s\",%d,%c)\n",	\
						option_index,	\
						long_options[option_index].name,	\
						long_options[option_index].has_arg,	\
						long_options[option_index].val);	\
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
					printf("%i\n", quality_offset);	\
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
					printf("%s\n", optarg); \
					break;	\
					}	\
				if (strcmp(optarg,"illumina") == 0)	\
					{	\
					name_type = 1;	\
					break; \
					}	\
				}	\
			};	\
		};	\

#endif /* OPTIONS_H_ */
