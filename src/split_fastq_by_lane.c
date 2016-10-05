#include "../header/split_fastq_by_lane.h"

KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
	{
	//-------------------Parsing options---------------------

	PARSE_OPTIONS;
	//-------------------------------------------------------
	kseq_t *seq_forward, *seq_reverse;


	if (unpaired == 0)
		{
		fp_forward = gzopen(forward_reads, "r");
		fp_reverse = gzopen(reverse_reads, "r");

		seq_forward = kseq_init(fp_forward);
		seq_reverse = kseq_init(fp_reverse);
		} else
			{
			fp_forward = gzopen(forward_reads, "r");
			seq_forward = kseq_init(fp_forward);
			}


	while ((l_forward = kseq_read(seq_forward)) >= 0)
		{
        if (unpaired == 0) {
            l_reverse = kseq_read(seq_reverse);
            }
		//checking lane
		read_name_copy = (char *) malloc(seq_forward->name.l + 1);
		strcpy(read_name_copy,
			   seq_forward->name.s); // copy read  name to retain original name intact because of strtok (it modifies string when split)
		parsed_forward_name = parse_read_name(read_name_copy, name_type);

		lane_index = find_lane(lane_filter_stat_array, parsed_forward_name, number_of_lanes, previous_lane_number);


		if (lane_index == -1)
			{
			//printf("aaaa\n");
			current_lane_index++;
			INIT_LANE_STAT_BY_READ_NAME(lane_filter_stat_array[current_lane_index], parsed_forward_name);
			previous_lane_number = current_lane_index;
			number_of_lanes++;

			if (unpaired == 0)
				{
					char forward_pe_out_file[strlen(output_prefix) + 9];
					char reverse_pe_out_file[strlen(output_prefix) + 9];

					char forward_suffix[9], reverse_suffix[9];

					sprintf(forward_suffix, "_L%i_1.fq", lane_filter_stat_array[current_lane_index].lane_number);
					strcpy(forward_pe_out_file, output_prefix);
					strcat(forward_pe_out_file,forward_suffix); //

					sprintf(reverse_suffix, "_L%i_2.fq", lane_filter_stat_array[current_lane_index].lane_number);
					strcpy(reverse_pe_out_file, output_prefix);
					strcat(reverse_pe_out_file, reverse_suffix);//

					lane_filter_stat_array[current_lane_index].forward_reads_fd = fopen(forward_pe_out_file, "w");
					lane_filter_stat_array[current_lane_index].reverse_reads_fd = fopen(reverse_pe_out_file, "w");
				} else
				{

					char forward_pe_out_file[strlen(output_prefix) + 7];
					char forward_suffix[7];
					sprintf(forward_suffix, "_L%i.fq", lane_filter_stat_array[current_lane_index].lane_number);
					strcpy(forward_pe_out_file, output_prefix);
					strcat(forward_pe_out_file, forward_suffix);

					lane_filter_stat_array[current_lane_index].forward_reads_fd = fopen(forward_pe_out_file, "w");
				}

			} else
				{
				free(read_name_copy);
				current_lane_index = lane_index;
				}

		if (unpaired == 0)
			{    //paired end case

			KSEQ_WRITE(lane_filter_stat_array[current_lane_index].forward_reads_fd, seq_forward);
			KSEQ_WRITE(lane_filter_stat_array[current_lane_index].reverse_reads_fd, seq_reverse);

			} else
				{
				KSEQ_WRITE(lane_filter_stat_array[current_lane_index].forward_reads_fd, seq_forward);
				}
		}


	if (unpaired == 0) {

		kseq_destroy(seq_forward);
		kseq_destroy(seq_reverse);
		gzclose(fp_forward);
		gzclose(fp_reverse);

		for(int i = 0; i < number_of_lanes; i++)
			{
			fclose(lane_filter_stat_array[i].forward_reads_fd);
			fclose(lane_filter_stat_array[i].reverse_reads_fd);
			}

	} else { //single-end case

		kseq_destroy(seq_forward);
		gzclose(fp_forward);

		for(int i = 0; i < number_of_lanes; i++)
			{
			fclose(lane_filter_stat_array[i].forward_reads_fd);
			}
	    }


	return 0;
	}
