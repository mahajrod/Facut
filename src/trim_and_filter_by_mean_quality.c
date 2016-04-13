#include "../header/trim_and_filter_by_mean_quality.h"

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
	{
	//-------------------Parsing options---------------------
	PARSE_OPTIONS;
	//-------------------------------------------------------
	kseq_t *seq_forward, *seq_reverse;

	fp_forward = gzopen(forward_reads, "r");
	fp_reverse = gzopen(reverse_reads, "r");

	seq_forward = kseq_init(fp_forward);
	seq_reverse = kseq_init(fp_reverse);

	char forward_pe_out_file[strlen(output_prefix) + 9];
	char forward_se_out_file[strlen(output_prefix) + 9];
	char reverse_pe_out_file[strlen(output_prefix) + 9];
	char reverse_se_out_file[strlen(output_prefix) + 9];

	//printf("%i", strlen(forward_se_out_file));
	strcpy(forward_pe_out_file, output_prefix);
	strcat(forward_pe_out_file, "_1.pe.fq");

	strcpy(forward_se_out_file, output_prefix);
	strcat(forward_se_out_file, "_1.se.fq");
	strcpy(reverse_pe_out_file, output_prefix);
	strcat(reverse_pe_out_file, "_2.pe.fq");
	strcpy(reverse_se_out_file, output_prefix);
	strcat(reverse_se_out_file, "_2.se.fq");

	//printf("%i", strlen(forward_se_out_file));

	fp_forward_pe_out = fopen(forward_pe_out_file, "w");
	fp_forward_se_out = fopen(forward_se_out_file, "w");
	fp_reverse_pe_out = fopen(reverse_pe_out_file, "w");
	fp_reverse_se_out = fopen(reverse_se_out_file, "w");

	while ((l_forward = kseq_read(seq_forward)) >= 0)
		{
		l_reverse = kseq_read(seq_reverse);

		//checking lane
		read_name_copy = (char *) malloc(seq_forward->name.l + 1);
		strcpy(read_name_copy, seq_forward->name.s); // copy read  name to retain original name intact because of strtok (it modifies string when split)
		parsed_forward_name = parse_read_name(read_name_copy, name_type);

		//free(read_name_copy);
		//INIT_LANE_STAT_BY_READ_NAME(lane_filter_stat_array[0], parsed_forward_name);
		//printf()
		//printf("%s\n", parsed_forward_name.flowcell_id);

		lane_index = find_lane(lane_filter_stat_array, parsed_forward_name, number_of_lanes, previous_lane_number);

		if (lane_index == -1)
			{
			//printf("aaaa\n");
			current_lane_index++;
			INIT_LANE_STAT_BY_READ_NAME(lane_filter_stat_array[current_lane_index], parsed_forward_name);
			previous_lane_number = current_lane_index;
			number_of_lanes++;
			} else
				{
				free(read_name_copy);
				current_lane_index = lane_index;
				} // retain copied name in memory only for name of first read in lane;
		//printf("%s\t%s\n", parsed_forward_name.instrument_id, parsed_forward_name.flowcell_id);
		//printf("%i\t%i\t%i\n", forward_name.side, forward_name.swatch, forward_name.tile);

		//----------------------trimming--------------------------
		//retain_forward = 1;
		//retain_reverse = 1;

		if (0 < forward_end < seq_forward->seq.l)
			{
			seq_forward->seq.l = forward_end;
			seq_forward->qual.l = forward_end;
			seq_forward->seq.s[forward_end] = 0;
			seq_forward->qual.s[forward_end] = 0;
			}
		if (0 < reverse_end < seq_reverse->seq.l)
			{
			seq_reverse->seq.l = reverse_end;
			seq_reverse->qual.l = reverse_end;
			seq_reverse->seq.s[reverse_end] = 0;
			seq_reverse->qual.s[reverse_end] = 0;
			}
		/*
		if (forward_start <= seq_forward->seq.l)
			{
			seq_forward->seq.l = seq_forward->seq.l -forward_start;
			seq_forward->qual.l = seq_forward->qual.l - forward_start;
			seq_forward->seq.s = &seq_forward->seq.s[forward_start - 1];
			seq_forward->qual.s = &seq_forward->qual.s[forward_start - 1];
			} else retain_forward = -1;
		if (min_read_length > 0 && seq_forward->seq.l < min_read_length) retain_forward = -1;

		if (reverse_start <= seq_reverse->seq.l)
			{
			seq_reverse->seq.l -= reverse_start;
			seq_reverse->qual.l -= reverse_start;
			seq_reverse->seq.s += reverse_start - 1;
			seq_reverse->qual.s += reverse_start - 1;
			} else retain_reverse = -1;
		if (min_read_length > 0 && seq_reverse->seq.l < min_read_length) retain_reverse = -1;
		*/
		//--------------------------------------------------------


		mean_score_forward = 0;
		for (int i =0; i < seq_forward->qual.l; i++)
			{
			mean_score_forward += seq_forward->qual.s[i];
			}
		mean_score_forward /= seq_forward->qual.l;
		mean_score_forward -= quality_offset;

		mean_score_reverse = 0;
		for (int i =0; i < seq_reverse->qual.l; i++)
			{
			mean_score_reverse += seq_reverse->qual.s[i];
			}
		mean_score_reverse /= seq_reverse->qual.l;
		mean_score_reverse -= quality_offset;

		if ((mean_score_forward >= quality_threshold) && (mean_score_reverse >= quality_threshold))// && (retain_forward == 1) && (retain_reverse == 1))
			{
			KSEQ_WRITE(fp_forward_pe_out, seq_forward);
			KSEQ_WRITE(fp_reverse_pe_out, seq_reverse);
			/*
			fprintf(fp_forward_pe_out, "@%s\n%s\n+\n%s\n", seq_forward->name.s, seq_forward->seq.s, seq_forward->qual.s);
			fprintf(fp_reverse_pe_out, "@%s\n%s\n+\n%s\n", seq_reverse->name.s, seq_reverse->seq.s, seq_reverse->qual.s);
			*/
			lane_filter_stat_array[current_lane_index].tile_stats[parsed_forward_name.side][parsed_forward_name.swatch][parsed_forward_name.tile][BOTH_RETAINED]++;
			paired += 1;
			} else
			{
			if ((mean_score_forward >= quality_threshold) && (mean_score_reverse < quality_threshold))// && (retain_forward == 1))
				{
				KSEQ_WRITE(fp_forward_se_out, seq_forward);
				//fprintf(fp_forward_se_out, "@%s\n%s\n+\n%s\n", seq_forward->name.s, seq_forward->seq.s, seq_forward->qual.s);
				lane_filter_stat_array[current_lane_index].tile_stats[parsed_forward_name.side][parsed_forward_name.swatch][parsed_forward_name.tile][FORWARD_ONLY]++;
				forward_se += 1;
				} else
				{
				if ((mean_score_forward < quality_threshold) && (mean_score_reverse >= quality_threshold))// && (retain_reverse == 1))
					{
					KSEQ_WRITE(fp_reverse_se_out, seq_reverse);
					//fprintf(fp_reverse_se_out, "@%s\n%s\n+\n%s\n", seq_reverse->name.s, seq_reverse->seq.s, seq_reverse->qual.s);
					lane_filter_stat_array[current_lane_index].tile_stats[parsed_forward_name.side][parsed_forward_name.swatch][parsed_forward_name.tile][REVERSE_ONLY]++;
					reverse_se += 1;
					} else
						{
						lane_filter_stat_array[current_lane_index].tile_stats[parsed_forward_name.side][parsed_forward_name.swatch][parsed_forward_name.tile][BOTH_DISCARDED]++;
						discarded_pairs += 1;
						}
				}
			}
		}

	printf("Paires retained:\t%i\nForward only retained:\t%i\nReverse only retained:\t%i\nPairs discarded:\t%i\n", paired, forward_se, reverse_se, discarded_pairs);
	printf("\n");
	printf("instrument_id\trun_number\tflowcell_id\tlane_number\ttile\tboth_retained\tforward_only\treverse_only\tboth_discarded\n");

	//printf("%i", number_of_lanes);

	for (int i = 0; i < number_of_lanes; i++)
		{
		//printf("%s\n", lane_filter_stat_array[i].instrument_id);
		//printf("%i\n", lane_filter_stat_array[i].run_number);
		//printf("%s\n", lane_filter_stat_array[i].flowcell_id);
		//printf("%i\n", lane_filter_stat_array[i].lane_number);

		for (int s = 1; s < SIDE_NUMBER; s++)
			{
			for (int w = 1; w < SWATCH_PER_SIDE_NUMBER; w++)
				{
				for (int t = 1; t < TILE_PER_SWATCH_NUMBER; t++)
					{
					if (lane_filter_stat_array[i].tile_stats[s][w][t][BOTH_RETAINED] +
						lane_filter_stat_array[i].tile_stats[s][w][t][FORWARD_ONLY] +
					    lane_filter_stat_array[i].tile_stats[s][w][t][REVERSE_ONLY] +
						lane_filter_stat_array[i].tile_stats[s][w][t][BOTH_DISCARDED] == 0) continue;
					//printf("%i\t%i\t%i\n", s, w, t);
					printf("%s\t%i\t%s\t%i\t%i%i%02i\t%i\t%i\t%i\t%i\n",
						   lane_filter_stat_array[i].instrument_id,
						   lane_filter_stat_array[i].run_number,
						   lane_filter_stat_array[i].flowcell_id,
						   lane_filter_stat_array[i].lane_number,
						   s, w, t,
						   lane_filter_stat_array[i].tile_stats[s][w][t][BOTH_RETAINED],
						   lane_filter_stat_array[i].tile_stats[s][w][t][FORWARD_ONLY],
						   lane_filter_stat_array[i].tile_stats[s][w][t][REVERSE_ONLY],
						   lane_filter_stat_array[i].tile_stats[s][w][t][BOTH_DISCARDED]);

					}
				}
			}
		}
	//printf("%i\t%i\n", name_type, quality_offset);

	kseq_destroy(seq_forward);
	kseq_destroy(seq_reverse);
	gzclose(fp_forward);
	gzclose(fp_reverse);
	fclose(fp_forward_pe_out);
	fclose(fp_forward_se_out);
	fclose(fp_reverse_pe_out);
	fclose(fp_reverse_se_out);


	return 0;
	}
