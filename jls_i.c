/*
 * Copyright (c) 2019 ... 2023 2024
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _MSDOS
#include <sys/param.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef HAVE_JLIB
#include <j_lib2.h>
#include <j_lib2m.h>
#endif

#include "jls.h"

#define SCKARG 80

/*
 * init_w() -- initialize work area
 */
void init_w(struct s_work *w, char *a)

{
  init_finfo(&(w->out));
  init_finfo(&(w->err));
  w->err.fp    = stderr;
  w->out.fp    = stdout;

  w->prog_name        = j2_get_prgname(a, PROG_NAME);
  w->file_list        = (char *) NULL;
  w->num_files        = 0;
  w->verbose          = 0;
  w->force            = FALSE;
  w->smod             = FALSE;
  w->sacc             = FALSE;
  w->schg             = FALSE;
  w->ssiz             = FALSE;

}  /* init_w() */

/*
 * save_fname() -- Check and Save File Name
 */
void save_fname(struct s_file_info *f, char *afname, char *pname, char arg_val)
{
  if (f->fname == (char *) NULL)
    f->fname = strdup(afname);
  else
    {
      fprintf(stderr, MSG_ERR_E074, SWITCH_CHAR, arg_val);
      fprintf(stderr, MSG_ERR_E000, pname, SWITCH_CHAR, ARG_HELP);
      exit(EXIT_FAILURE);
    }

} /* save_fname() */

/*
 * process_arg() -- process arguments
 */
void process_arg(int argc, char **argv, struct s_work *w)

{
  char ckarg[SCKARG];
  int opt;
  int i;

  snprintf(ckarg, SCKARG, "%c%c%c%c%c%c%c%c%c:%c:%c:", 
	  ARG_FORCE,    ARG_HELP,     ARG_VERBOSE,  ARG_VERSION,
          ARG_MOD_DATE, ARG_ACC_DATE, ARG_CHG_DATE, ARG_FILE_SIZE,
	  ARG_INPUT,    ARG_ERR,      ARG_OUT);

  while ((opt = getopt(argc, argv, ckarg)) != -1)
    {
      switch (opt)
	{
	case ARG_FORCE:
	  w->force = TRUE;
	  break;
	case ARG_ACC_DATE:
	  w->sacc = TRUE;
	  break;
	case ARG_CHG_DATE:
	  w->schg = TRUE;
	  break;
	case ARG_FILE_SIZE:
	  w->ssiz = TRUE;
	  break;
	case ARG_MOD_DATE:
	  w->smod = TRUE;
	  break;
	case ARG_HELP:
	  show_brief_help(stderr, w->prog_name);
	  break;
	case ARG_VERBOSE:
	  w->verbose++;
	  break;
	case ARG_VERSION:
	  show_rev(stderr, w->prog_name);
	  break;
	case ARG_INPUT:
	  if (w->file_list == (char *) NULL)
	    w->file_list = strdup(optarg);
	  else
	    {
	      fprintf(w->err.fp,MSG_ERR_E028);
	      fprintf(w->err.fp, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
	      exit(EXIT_FAILURE);
	    }
	  break;
	case ARG_ERR:
	  save_fname(&(w->err), optarg, w->prog_name, ARG_ERR);
	  break;
	case ARG_OUT:
	  save_fname(&(w->out), optarg, w->prog_name, ARG_ERR);
	  break;
	default:
	  fprintf(w->err.fp, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
	  exit(EXIT_FAILURE);
	  break;
	}
    }

  /*** open 'out' files ***/
  if ( ! open_out(stderr, &(w->err), w->prog_name, w->force))
    w->err.fp = stderr;
  if ( ! open_out(w->err.fp, &(w->out), w->prog_name, w->force) )
    w->out.fp = stdout;

  /*** Count number of files to process */
  for (i = optind; i < argc; i++)
    (w->num_files)++;
  if ((w->num_files == 0) && (w->file_list == (char *) NULL))
    {
      w->file_list = strdup(FILE_NAME_STDIN);
      (w->num_files)++;  /* stdin when no files */
    }
  else
    {
      if ((w->num_files > 0) && (w->file_list != (char *) NULL))
	{
	  fprintf(w->err.fp, "Cannot specify -i and files at the same time\n");
	  fprintf(w->err.fp, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
	  exit(EXIT_FAILURE);
	}
    }

  /*** set defaults ***/
  if ( (w->smod == FALSE) && (w->sacc == FALSE) && (w->schg == FALSE) && (w->ssiz == FALSE) )
    w->smod = TRUE;

} /* process_arg() */

/*
 * init() -- initialize
 */
void init(int argc, char **argv, struct s_work *w)

{

  init_w(w, argv[0]);

  process_arg(argc, argv, w);

}  /* init() */
