#include "stat.h"

struct read_name parse_read_name(char *name, int mode)
	{
	//1: full read  name template @<instrument>:<run number>:<flowcell ID>:<lane>:<tile>:<x-pos>:<y-pos> <read>:<is filtered>:<control number>:<index sequence>
	//2: short read name template <flowcell ID>:<lane>:<tile>:<x-pos>:<y-pos>#index/read
	struct read_name parsed_name;
	char *parsed[5];
	int tile_numbers[3];
	char *token = strtok(name, ": #");
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
	return parsed_name;
	}

int compare_read_name_with_stat_struct(struct illumina_tile_stat stat_struct, struct read_name name)
	{
	//if ((illumina_tile_stat.run_number != read_name) or () or ())
	//	{
	//	return 0;
	//	}
	return 1;
	}

