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

#ifndef JLS_H

#define JLS_H "INCLUDED"

#define PROG_NAME  "jls"

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_INT_NULL   ((int) '\0')
#define JLIB2_CHAR_NULL  ((char) '\0')
#define JLIB2_UCHAR_NULL ((unsigned char) '\0' )
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
#endif

/*** values returned by file_type() ***/
#ifdef NO_JLIB
#define J2_CANT_GET      0
#define J2_UNKNOWN       1
#define J2_DIRECTORY     2  /* S_IFDIR  */
#define J2_REGULAR       3  /* S_IFREG  */
#define J2_CHAR_SPECIAL  4  /* S_IFCHR  */
#define J2_BLOCK_SPECIAL 5  /* S_IFBLK  */
#define J2_PIPE          6  /* S_IFPIP  */
#define J2_SOCKET        7  /* S_IFSOCK */
#define J2_SYMB_LINK     8  /* S_IFLNK  */
#define J2_FIFO          9  /* S_IFIFO  */
#endif /* NO_JLIB */

/*** structures ***/
struct s_file_info
{
  FILE *fp;
  char *fname;
} ;

struct s_work
{
  struct s_file_info out;         /* default stdout               */
  struct s_file_info err;         /* default stderr               */
  char *prog_name;                /* real program name            */
  char *file_list;                /* list of files to process     */
  int num_files;                  /* # of files to process        */
  int verbose;                    /* TRUE or FALSE                */
  int force;                      /* TRUE or FALSE                */
  int smod;                       /* show Mod Time                */
  int sacc;                       /* show Access Time             */
  int schg;                       /* show Last Stat Change Time   */
  int ssiz;                       /* show File Size               */
} ;

/*** messages ***/
#ifdef NO_JLIB
#define ARG_ACC_DATE      'a'  /* Last Access Date/Time              */
#define ARG_CHG_DATE      'c'  /* Last Status Change Date/Time       */
#define ARG_ERR           'e'  /* Output Error File                  */
#define ARG_FILE_SIZE     's'  /* File Size                          */
#define ARG_FORCE         'f'  /* force create files                 */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_INPUT         'i'  /* Input File                         */
#define ARG_MOD_DATE      'm'  /* Modification Date/Time             */
#define ARG_OUT           'o'  /* Output File                        */
#define ARG_VERBOSE       'v'  /* Verbose                            */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define FILE_NAME_STDIN   "-"
#define FILE_NAME_STDOUT  "-"
#define LIT_ACC_DT            "Access Date/Time"
#define LIT_BYP_ABORTED       "Bypassed Call Aborted"
#define LIT_BYP_BLOCK_SPECIAL "Bypassed Block Special"
#define LIT_BYP_CHAR_SPEC     "Bypassed Character Special"
#define LIT_BYP_DIRECTORY     "Bypassed Directory"
#define LIT_BYP_FIFO          "Bypassed FIFO"
#define LIT_BYP_MISSING       "Bypassed File Missing"
#define LIT_BYP_NO_INFO       "Bypassed cannot get info"
#define LIT_BYP_PIPE          "Bypassed Pipe"
#define LIT_BYP_SOCKET        "Bypassed Socket"
#define LIT_BYP_SYMB_LINK     "Symbol Link"
#define LIT_BYP_UNDEFINED     "Bypassed Undefined issue"
#define LIT_BYP_UNKNOWN       "Bypassed Unknown Type"
#define LIT_FILE_NAME         "File Name"
#define LIT_FILE_SIZE         "File Size"
#define LIT_INFO_01           "\tBuild: %s %s\n"
#define LIT_MOD_DT            "Mod Date/Time"
#define LIT_REV               "Revision"
#define LIT_STA_DT            "Stat Chg Date/Time"
#define LIT_STDIN             "(standard input)"
#define LIT_STDOUT            "(standard output)"
#define MSG_ERR_E000          "Try '%s %c%c' for more information\n"
#define MSG_ERR_E002          "ERROR E002: Cannot open '%s' for write, processing aborted\n"
#define MSG_ERR_E025          "ERROR E025: File %s cannot be created, already exists\n"
#define MSG_ERR_E028          "ERROR E028: too many files specified\n"
#define MSG_ERR_E074          "ERROR E074: 'Too many Arguments specified for %c%c\n"
#define MSG_ERR_E080          "ERROR E080: cannot allocate initial memory : %s\n"
#define MSG_INFO_I072         "I072:    Lines Reads:  %9ld - File %s\n"
#define MSG_INFO_I080         "I080:   Lines Writes:  %9ld - File %s\n"
#define MSG_INFO_I096         "I096:     Read Bytes:  %9ld - File %s\n"
#define MSG_WARN_W002         "W002: Open Error Bypass File '%s' : %s\n"
#define SWITCH_CHAR           '-'
#define USG_MSG_ARG_ACC_DATE   "\t%c%c\t\t: Show Last Access Date/Time\n"
#define USG_MSG_ARG_CHG_DATE   "\t%c%c\t\t: Show Last Status Change Date/Time\n"
#define USG_MSG_ARG_ERR        "\t%c%c file\t\t: Write errors to file 'file', default stderr\n"
#define USG_MSG_ARG_FILE_SIZE  "\t%c%c\t\t: Show File Size in Bytes\n"
#define USG_MSG_ARG_FORCE      "\t%c%c\t\t: force create of files when found\n"
#define USG_MSG_ARG_HELP       "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_MOD_DATE   "\t%c%c\t\t: Show Last Modify Date/Time\n"
#define USG_MSG_ARG_OUT        "\t%c%c file\t\t: Write output to file 'file', default stdout\n"
#define USG_MSG_ARG_VERBOSE_8  "\t%c%c\t\t: verbose level, each time specified level increases\n"
#define USG_MSG_ARG_VERSION    "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_OPTIONS        "Options\n"
#define USG_MSG_USAGE          "usage:\t%s [OPTIONS] [FILES ...]\n"
#endif /* NO_JLIB */

/*** prototypes ***/
void init(int, char **, struct s_work *);
void init_finfo(struct s_file_info *);
void show_brief_help(FILE *, char *);
void show_rev(FILE *, char *);
void process_arg(int, char **, struct s_work *);
int  open_out(FILE *, struct s_file_info *, char *, int);
void close_out(struct s_file_info *);
int  open_in(FILE **, char *, FILE *);
void close_in(FILE **, char *);

#ifdef NO_JLIB
SSIZE_T j2_getline(char **buf, size_t *n, FILE *fp);
char *j2_get_prgname(char *argv_0, char *default_name);
int j2_f_exist(char *file_name);
int j2_file_typ(char *file_name);
long int j2_clr_str(char *s, char c, int size);
long int j2_rtw(char *buffer);
#endif /* NO_JLIB */

#endif /*  JLS_H  */
