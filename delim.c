
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include "csv.c/csv.h"

int chosenCol = 0;
static struct option const longopts[] =
{
  {"output-delimiter", required_argument, NULL, 'o'},
  {"input-delimiter", required_argument, NULL, 'd'},
  {"help", no_argument, NULL, 'h'},
  {NULL, 0, NULL, 0}
};

void usage (int status) {
  fputs ("Usage: csv-delim [OPTIONS] < IN.csv > OUT.tsv\n", stdout);
  fputs ("Deliminate a csv file.\n\n", stdout);

  fputs ("OPTIONS\n\n", stdout);

  fputs ("  -i, --input-delimiter=CHAR     select the input delimiter, defaults to ','\n", stdout);
  fputs ("  -d, --output-delimiter=CHAR    select the output delimiter, defaults to '\\t'\n", stdout);

  exit (status);
};

static char delim = '\t';

void field_cb(void* data, size_t len, void* outfile, int is_last) {
  fwrite(data, len, 1, (FILE*)outfile);
  if (!is_last)
    fputc(delim, (FILE*)outfile);
}

void row_cb(int c, void *outfile) {
  fputc('\n', (FILE *)outfile);
}

int main(int argc, const char *argv[]) {
  char c;
  char buffer[65535];
  ssize_t nread;
  struct csv_parser parser;

  csv_init(&parser, 0);

  while ((c = getopt_long (argc, argv, "d:i:h", longopts, NULL)) != -1) {
    switch (c) {
    case 'i': {
      csv_set_delim(&parser, optarg[0]);
      break;
    }
    case 'd': {
      delim = optarg[0];
      break;
    }
    case 'h': {
      usage(EXIT_SUCCESS);
      break;
    }
    case '?': {
      if (c == 'd') {
        // use , input delimination by default
        delim = ',';
      }
      break;
    }
    default: {
      printf("csv exiting because of %d\n", c);
      usage (EXIT_FAILURE);
    }
    }
  }
  
  while ((nread = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
    csv_parse(&parser, buffer, nread, field_cb, row_cb, stdout);
  }

  csv_fini(&parser, field_cb, row_cb, stdout);
  csv_free(&parser);

  return 0;
}
