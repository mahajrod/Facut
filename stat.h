/*
 * stat.h
 *
 *  Created on: Mar 3, 2016
 *      Author: mahajrod
 */

#ifndef STAT_H_
#define STAT_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//this structure supports lanes with 96 tiles only
#define SIDE_NUMBER 2
#define SWATCH_PER_SIDE_NUMBER  3
#define TILE_PER_SWATCH_NUMBER  16


struct illumina_tile_stat
	{

	char *instrument_id;
	unsigned long long int run_number;
	char *flowcell_id;
	unsigned int lane_number;
	unsigned long long int tile_stats[SIDE_NUMBER][SWATCH_PER_SIDE_NUMBER][TILE_PER_SWATCH_NUMBER];
	};

struct read_name
	{
	char *instrument_id;
	unsigned long long int run_number;
	char *flowcell_id;
	unsigned int lane_number;
	short unsigned int side;
	short unsigned int swatch;
	short int tile;
	};

#define PARSE_TILE_NUMBER(tile_str, tile_numbers)	\
	tile_numbers[0] = tile_str[0] - '0';	\
	tile_numbers[1] = tile_str[1] - '0';	\
	tile_numbers[2] = atoi(tile_str+2);	\

struct read_name parse_read_name(char *name, int mode);

int compare_read_name_with_stat_struct(struct illumina_tile_stat stat_struct, struct read_name name);

#endif /* STAT_H_ */
