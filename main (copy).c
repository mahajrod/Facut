#include <zlib.h>
#include <stdio.h>
#include <argp.h>

#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

const char *argp_program_version = "FaCut v0.1";
const char *argp_program_bug_address = "<mahajrod@gmail.com>";
static char doc[] = "Tool for quality trimming or filtration of Illumina data";
static char args_doc[] = "[FILENAME]...";
static struct argp_option options[] = {
    { "quality_encoding", 'q', "QUALITY_ENCODING", 0, "Quality encoding. Default: phred64"},
    { "forward", 'f', "FORWARD", 0, "File with forward reads"},
    { "reverse", 'r', "REVERSE", 0, "File with reverse reads"},
    { "output_prefix", 'p', "OUTPUT_PREFIX", 0, "Output prefix"},
    { 0 } };

struct arguments
{
  //char *args[2];
  char *quality_encoding;
  char *forward;
  char *reverse;
  char *output_prefix;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'q':
      arguments->quality_encoding = arg;
      break;
    case 'f':
      arguments->forward = arg;
      break;
    case 'r':
      arguments->reverse = arg;
      break;
    case 'p':
      arguments->output_prefix = arg;
      break;
    /*case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
	{
	  argp_usage(state);
	}
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 2)
	{
	  argp_usage (state);
      printf("aaaa");
      break;
	}
      break;*/
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}
static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char *argv[])
{
	//----------------Parsing arguments----------------------
	//struct arguments arguments;
	//argp_parse (&argp, argc, argv, 0, 0, &arguments);
	//-------------------------------------------------------

	gzFile fp_forward, fp_reverse;
	kseq_t *seq_forward, *seq_reverse;
	long long int total_score_forward = 0, total_score_reverse = 0;
	double mean_score_forward = 0, mean_score_reverse = 0;
	int len_forward, len_reverse;
	int quality_offset = 0;
	int l_forward, l_reverse;
	if (argc == 1) {
		fprintf(stderr, "Usage: %s <in.seq>\n", argv[0]);
		return 1;
	}

	/*
	if (arguments.quality_encoding == "phred33")
	{
		quality_offset = 33;
	} else quality_offset = 64;
	*/
	quality_offset = 64;
	printf("%i\n", quality_offset);
	//printf("%s\n", arguments.forward);
	//printf("%s\n", arguments.reverse);
	printf("%s\n", argv[4]);
	printf("%s\n", argv[6]);
	fp_forward = gzopen(argv[4], "r");
	fp_reverse = gzopen(argv[6], "r");
	seq_forward = kseq_init(fp_forward);
	seq_reverse = kseq_init(fp_reverse);
	printf("cccc\n");
	while ((l_forward = kseq_read(seq_forward)) >= 0) {
		l_reverse = kseq_read(seq_reverse);
		printf("dddd\n");
		mean_score_forward = 0;
		mean_score_reverse = 0;

		printf("forward\n");
		printf("name: %s\n", seq_forward->name.s);
		// if (seq->comment.l) printf("comment: %s\n", seq->comment.s);
		printf("seq: %s\n", seq_forward->seq.s);
		if (seq_forward->qual.l) printf("qual: %s\n", seq_forward->qual.s);

		printf("reverse\n");
		printf("name: %s\n", seq_reverse->name.s);
		// if (seq->comment.l) printf("comment: %s\n", seq->comment.s);
		printf("seq: %s\n", seq_reverse->seq.s);
		if (seq_reverse->qual.l) printf("qual: %s\n", seq_reverse->qual.s);


		// printf("%i\n", strlen(seq_reverse->qual.s));
		len_forward = strlen(seq_forward->qual.s);
		len_reverse = strlen(seq_reverse->qual.s);
		for (int i =0; i < len_forward; i++)
			{
			mean_score_forward += seq_reverse->qual.s[i];
			}
		printf("%f\n", mean_score_forward);
		mean_score_forward /= len_forward;
		mean_score_forward -= quality_offset;

		printf("%f\n", mean_score_forward);
	}

	printf("return value: %d\n", l_forward);
	kseq_destroy(seq_forward);
	kseq_destroy(seq_reverse);
	gzclose(fp_forward);
	gzclose(fp_reverse);
	return 0;
}
