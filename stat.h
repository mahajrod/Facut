/*
 * stat.h
 *
 *  Created on: Mar 3, 2016
 *      Author: mahajrod
 */

#ifndef STAT_H_
#define STAT_H_

#include <string.h>

#define SIDE_NUMBER 2
#define SWATCH_PER_SIDE_NUMBER  3
#define TILE_PER_SWATCH_NUMBER  16


struct illumina_tile_stat
	{
	//this structure supports lanes with 96 tiles only
	char *instrument_number[25];
	long long int run_number;
	char *flowcell_id[25];
	int lane_number;
	long long unsigned int tile_stats[SIDE_NUMBER][SWATCH_PER_SIDE_NUMBER][TILE_PER_SWATCH_NUMBER];
	};

int parse_read_name(char *read_name, char *parsed[])
	{
	// read  name template @<instrument>:<run number>:<flowcell ID>:<lane>:<tile>:<x-pos>:<y-pos> <read>:<is filtered>:<control number>:<index sequence>
	char *first_name_part = strtok(read_name, " "); // at moment i am not interested in read_id and following info
	char *first_name_part_2 = strtok(first_name_part, "#");
	//printf("%s\n", first_name_part_2);

	char *token = strtok(first_name_part_2, ":");
	short unsigned int i = 0;
	while(i < 5)
	   {
	   //printf("%s\n", token );
	   parsed[i] = token;
	   token = strtok(NULL, ":");
	   i++;
	   }
	return 0;
	}

#endif /* STAT_H_ */
