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

#define SIDE_NUMBER 2+1
#define SWATCH_PER_SIDE_NUMBER  3+1
#define TILE_PER_SWATCH_NUMBER  64+1

#define HISEQ_SIDE_NUMBER 2+1
#define HISEQ_SWATCH_PER_SIDE_NUMBER  3+1
#define HISEQ_TILE_PER_SWATCH_NUMBER  16+1

#define X_SIDE_NUMBER 2+1
#define X_SWATCH_PER_SIDE_NUMBER  2+1
#define X_TILE_PER_SWATCH_NUMBER  24+1

#define MISEQ_SIDE_NUMBER 2+1
#define MISEQ_GROUP_NUMBER 3+1
#define MISEQ_SWATCH_PER_SIDE_NUMBER  3+1
#define MISEQ_TILE_PER_SWATCH_NUMBER  12+1


#define	NUMBER_OF_STATISTICS	4

#define BOTH_RETAINED	0
#define FORWARD_ONLY	1
#define REVERSE_ONLY	2
#define	BOTH_DISCARDED	3

struct illumina_lane_stat
	{
	char *instrument_id;
	unsigned long long int run_number;
	char *flowcell_id;
	unsigned int lane_number;
	unsigned long long int tile_stats[SIDE_NUMBER][SWATCH_PER_SIDE_NUMBER][TILE_PER_SWATCH_NUMBER][NUMBER_OF_STATISTICS];
	};

struct illumina_miseq_lane_stat
	{
	char *instrument_id;
	unsigned long long int run_number;
	char *flowcell_id;
	unsigned int lane_number;
	unsigned long long int tile_stats[MISEQ_SIDE_NUMBER][MISEQ_GROUP_NUMBER][MISEQ_SWATCH_PER_SIDE_NUMBER][MISEQ_TILE_PER_SWATCH_NUMBER][NUMBER_OF_STATISTICS];
	};

struct read_name
	{
	char *instrument_id;
	unsigned long long int run_number;
	char *flowcell_id;
	unsigned int lane_number;
	short unsigned int side;
	unsigned int group;
	short unsigned int swatch;
	short int tile;
	};

#define PARSE_TILE_NUMBER(tile_str, tile_numbers)	\
	tile_numbers[0] = tile_str[0] - '0';	\
	tile_numbers[1] = tile_str[1] - '0';	\
	tile_numbers[2] = atoi(tile_str+2);

#define PARSE_MISEQ_TILE_NUMBER(tile_str, tile_numbers)	\
	tile_numbers[0] = tile_str[0] - '0';	\
	tile_numbers[1] = tile_str[1] - '0';	\
	tile_numbers[2] = tile_str[2] - '0';	\
	tile_numbers[3] = atoi(tile_str+3);

#define INIT_LANE_STAT_BY_READ_NAME(lane_stat, read_name) \
	memset(lane_stat.tile_stats, 0, sizeof lane_stat.tile_stats); /*init array with zeroes*/ \
	lane_stat.instrument_id = read_name.instrument_id; \
	lane_stat.run_number = read_name.run_number; \
	lane_stat.flowcell_id = read_name.flowcell_id; \
	lane_stat.lane_number = read_name.lane_number;

struct read_name parse_read_name(char *name, int mode);

int compare_read_name_with_stat_struct(struct illumina_lane_stat stat_struct, struct read_name name);
int find_lane(struct illumina_lane_stat lane_stats[], struct read_name name, int number_of_lanes, int previous_lane);

#endif /* STAT_H_ */
