/*
 * Copyright (c) 2019 2020 2021 2022
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
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#ifdef OpenBSD
#include <err.h>
#endif
#ifdef __FreeBSD_version
#include <err.h>
#endif
#ifdef __NetBSD_Version__
#include <err.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>

#include "jls.h"

/*
 * show_file_info()
 */
long int show_file_info(struct s_work *w, char *f)
{
  static int show_hdr = TRUE;
  char *emsg = (char *) NULL;
  struct stat s;
  struct tm *t;

  if ( j2_f_exist(f) )
    {
      switch(j2_file_typ(f))
	{
	  case J2_BLOCK_SPECIAL:
	    emsg = LIT_BYP_BLOCK_SPECIAL;
	    break;
	  case J2_CANT_GET:
	    emsg = LIT_BYP_ABORTED;
	    break;
	  case J2_CHAR_SPECIAL:
	    emsg = LIT_BYP_CHAR_SPEC;
	    break;
	  case J2_DIRECTORY:
	    emsg = LIT_BYP_DIRECTORY;
	    break;
	  case J2_FIFO:
	    emsg = LIT_BYP_FIFO;
	    break;
	  case J2_PIPE:
	    emsg = LIT_BYP_PIPE;
	    break;
	  case J2_REGULAR:
	    if (stat(f, &s)  != 0)
	      emsg = LIT_BYP_NO_INFO;
	    break;
	  case J2_SOCKET:
	    emsg = LIT_BYP_SOCKET;
	    break;
	  case J2_SYMB_LINK:
	    emsg = LIT_BYP_SYMB_LINK;
	    break;
	  case J2_UNKNOWN:
	    emsg = LIT_BYP_UNKNOWN;
	    break;
	  default:
	    emsg = LIT_BYP_UNDEFINED;
	    break;
	}
    }
  else
    emsg = LIT_BYP_MISSING;

  if (emsg != (char *) NULL)
    {
      if (w->verbose > 1)
	fprintf(w->err.fp, "%s : %s\n", emsg, f);
      return(0L);
    }

  if ((w->verbose > 0) && (show_hdr == TRUE))
    {
      show_hdr = FALSE;
      if (w->smod)
	fprintf(w->out.fp, "%19s ", LIT_MOD_DT);
      if (w->sacc)
	fprintf(w->out.fp, "%19s ", LIT_ACC_DT);
      if (w->schg)
	fprintf(w->out.fp, "%19s ", LIT_STA_DT);
      if (w->ssiz)
	fprintf(w->out.fp, "%15s ", LIT_FILE_SIZE);
      fprintf(w->out.fp, "%s\n", LIT_FILE_NAME);
    }

  /* now show file data */
  if (w->smod)
    {
      t = localtime(&(s.st_mtime));
      fprintf(w->out.fp, "%04d-%02d-%02d %02d:%02d:%02d ",
	      (t->tm_year + 1900), (t->tm_mon + 1), t->tm_mday,
	      t->tm_hour,          t->tm_min,       t->tm_sec);
    }
  if (w->sacc)
    {
      t = localtime(&(s.st_atime));
      fprintf(w->out.fp, "%04d-%02d-%02d %02d:%02d:%02d ",
	      (t->tm_year + 1900), (t->tm_mon + 1), t->tm_mday,
	      t->tm_hour,          t->tm_min,       t->tm_sec);
    }
  if (w->schg)
    {
      t = localtime(&(s.st_ctime));
      fprintf(w->out.fp, "%04d-%02d-%02d %02d:%02d:%02d ",
	      (t->tm_year + 1900), (t->tm_mon + 1), t->tm_mday,
	      t->tm_hour,          t->tm_min,       t->tm_sec);
    }
  if (w->ssiz)
    fprintf(w->out.fp, "%15lld ", (long long) s.st_size);

  fprintf(w->out.fp, "%s\n", f);

  return(1L);

} /* show_file_info() */

/*
 * process_a_file()
 */
void process_a_file(struct s_work *w, char *fname, char **buf, size_t *bsize)

{

  char *fmt_in  = (char *) NULL;
  char *fmt_out = (char *) NULL;
  ssize_t cbytes = (ssize_t) 0;
  ssize_t tbytes = (ssize_t) 0;
  long int lines_read = 0L;
  long int lines_write = 0L;
  FILE *fp;
  
  if ( ! open_in(&fp, fname, w->err.fp) )
    return;

  /*** process data ***/
  if (w->file_list == (char *) NULL)
    show_file_info(w, fname);
  else
    {
      while ((cbytes = j2_getline(buf, bsize, fp)) > (ssize_t) -1)
	{
	  lines_read++;
	  tbytes += cbytes;
	  j2_rtw((*buf));
	  lines_write += show_file_info(w, (*buf));
	}
    }
  
  /*** complete ***/
  if ((w->verbose > 2) && (w->file_list != (char *) NULL))
    {
      if (fname != (char *) NULL)
	{
	  if (strcmp(fname, FILE_NAME_STDIN) != 0)
	    fmt_in = fname;
	}
      if (w->out.fname != (char *) NULL)
	{
	  if (strcmp(w->out.fname, FILE_NAME_STDIN) != 0)
	    fmt_out = w->out.fname;
	}
      fprintf(w->err.fp, "\n");
      fprintf(w->err.fp, MSG_INFO_I096, (long int) tbytes,
              (fmt_in == (char *) NULL ? LIT_STDIN  : fmt_in));
      fprintf(w->err.fp, MSG_INFO_I072, lines_read,
              (fmt_in == (char *) NULL ? LIT_STDIN  : fmt_in));
      fprintf(w->err.fp, MSG_INFO_I080, lines_write, 
              (fmt_out == (char *) NULL ? LIT_STDOUT : fmt_out));
    }
  
  close_in(&fp, fname);

} /* process_a_file() */

/*
 * process_all() -- Process all files
 */
void process_all(int argc, char **argv, struct s_work *w)

{
  int i;
  char *buf = (char *) NULL;
  size_t bsiz = (size_t) 200;
  
  /* allocate initial read buffer memory (optional) */
  buf = (char *) calloc(bsiz, sizeof(char));
  if (buf == (char *) NULL)
    {
      fprintf(w->err.fp, MSG_ERR_E080, strerror(errno));
      return;
    }

  /* process files */
  if (w->file_list == (char *) NULL)
    {
      for (i = optind; i < argc; i++)
	process_a_file(w, argv[i], &buf, &bsiz);
      if (i == optind)
	process_a_file(w, FILE_NAME_STDIN, &buf, &bsiz);
    }
  else
    process_a_file(w, w->file_list, &buf, &bsiz);


#ifdef OpenBSD
  freezero(buf, bsiz);
#else
  if (buf != (char *) NULL)
    free(buf);
#endif

}  /* process_all() */

/*
 * main()
 */
int main(int argc, char **argv)

{
  struct s_work w;

#ifdef OpenBSD
  if(pledge("stdio rpath wpath cpath",NULL) == -1)
    err(1,"pledge\n");
#endif

  init(argc, argv, &w);
  
  process_all(argc, argv, &w);
  
  close_out(&(w.out));
  close_out(&(w.err));
  exit(EXIT_SUCCESS);

}  /* main() */
