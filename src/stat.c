#include "../header/stat.h"

struct read_name parse_read_name(char *name_copy, int mode)
	{
	//1: full read  name template @<instrument>:<run number>:<flowcell ID>:<lane>:<tile>:<x-pos>:<y-pos> <read>:<is filtered>:<control number>:<index sequence>
	//2: short read name template <flowcell ID>:<lane>:<tile>:<x-pos>:<y-pos>#index/read
	struct read_name parsed_name;
	char *parsed[5];
	int tile_numbers[3];
	char *token = strtok(name_copy, ": #");
	for (int i =0; i < 5; i++)
	   {
	   parsed[i] = token;
	   token = strtok(NULL, ":");
	   }

	switch(mode)
		{
		case 1:
			{
			parsed_name.instrument_id = parsed[0];
			parsed_name.run_number = atoi(parsed[1]);
			parsed_name.flowcell_id = parsed[2];
			parsed_name.lane_number = atoi(parsed[3]);
			PARSE_TILE_NUMBER(parsed[4],tile_numbers);
			break;
			}
		case 2:
			{
			parsed_name.instrument_id = ".";
			parsed_name.run_number = 0;
			parsed_name.flowcell_id = parsed[0];
			parsed_name.lane_number = atoi(parsed[1]);
			PARSE_TILE_NUMBER(parsed[2], tile_numbers);
			break;
			}
		}
	parsed_name.side = tile_numbers[0];
	parsed_name.swatch = tile_numbers[1];
	parsed_name.tile = tile_numbers[2];
	//printf("%s\n", parsed_name.flowcell_id);
	return parsed_name;
	}

int compare_read_name_with_stat_struct(struct illumina_lane_stat stat_struct, struct read_name name)
	{
	if ((strcmp(stat_struct.instrument_id,name.instrument_id) != 0) || (stat_struct.run_number != name.run_number) || \
		(strcmp(stat_struct.flowcell_id,name.flowcell_id) != 0) || (stat_struct.lane_number != name.lane_number))
		{
		return 0;
		}
	return 1;
	}

int find_lane(struct illumina_lane_stat lane_stats[], struct read_name name, int number_of_lanes, int previous_lane)
	{
	//printf("aaaa");
	if (previous_lane == -1) return -1;
	//returns -1 if read is from new lane

	if (compare_read_name_with_stat_struct(lane_stats[previous_lane], name) == 1)
		{
		return previous_lane;
		}

	for (int i = 0; i < number_of_lanes; i++)
		{
		if (compare_read_name_with_stat_struct(lane_stats[i], name) == 1)
			{
			return i;
			}
		}
	return -1;
	}

