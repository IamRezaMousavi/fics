/* utils.c
 *
 */

/*
    fics - An internet chess server.
    Copyright (C) 1993  Richard V. Nash

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

/* Revision history:
   name		email		yy/mm/dd	Change
   Richard Nash	              	93/10/22	Created
*/

#include "stdinclude.h"

#include "common.h"
#include "config.h"
#include "network.h"
#include "playerdb.h"
#include "rmalloc.h"
#include "utils.h"

PUBLIC int count_lines(FILE *fp)
{
  int c, nl = 0;

  while ((c = fgetc(fp)) != EOF)
	if (c == '\n')
		++nl;

  return nl;
}

PUBLIC int iswhitespace(int c)
{
  if ((c < ' ') || (c == '\b') || (c == '\n') ||
      (c == '\t') || (c == ' ')) {	/* white */
    return 1;
  } else {
    return 0;
  }
}

PUBLIC char *getword(char *str)
{
  int i;
  static char word[MAX_WORD_SIZE];

  i = 0;
  while (*str && !iswhitespace(*str)) {
    word[i] = *str;
    str++;
    i++;
    if (i == MAX_WORD_SIZE) {
      i = i - 1;
      break;
    }
  }
  word[i] = '\0';
  return word;
}

PUBLIC char *eatword(char *str)
{
  while (*str && !iswhitespace(*str))
    str++;
  return str;
}

PUBLIC char *eatwhite(char *str)
{
  while (*str && iswhitespace(*str))
    str++;
  return str;
}

PUBLIC char *eattailwhite(char *str)
{
  int len;
  if (str == NULL)
    return NULL;

  len = strlen(str);
  while (len > 0 && iswhitespace(str[len - 1]))
    len--;
  str[len] = '\0';
  return (str);
}

PUBLIC char *nextword(char *str)
{
  return eatwhite(eatword(str));
}

/* check_the_email_address function: */
/*
PUBLIC int check_emailaddr(char *email)
{
  int qbuflen;
  char qabuf[5120];

  if ((email = strchr(email, '@')) == NULL)
    return 2;
  email++;

  res_init();
  _res.options = (RES_INIT | RES_RECURSE);
  if ((qbuflen = res_mkquery(QUERY, email, C_IN, T_ANY, NULL, 0, NULL, qabuf, sizeof(qabuf))) == -1)
    return 1;

  if (res_send(qabuf, qbuflen, qabuf, sizeof(qabuf)) == -1)
    return 1;

  return (_getshort(qabuf + 6) ? 0 : 2);
}
*/

PUBLIC int mail_string_to_address(char *addr, char *subj, char *str)
{
  char com[1000];
  FILE *fp;

#ifdef SENDMAILPROG
  sprintf(com, "%s\n", SENDMAILPROG);
#else
  sprintf(com, "%s -s \"%s\" %s", MAILPROGRAM, subj, addr);
#endif
  fp = popen(com, "w");
  if (!fp)
    return -1;
#ifdef SENDMAILPROG
  fprintf(fp, "To: %s\nSubject: %s\n%s", addr, subj, str);
#else
  fprintf(fp, "%s", str);
#endif
  pclose(fp);
  return 0;
}

PUBLIC int mail_string_to_user(int p, char *subj, char *str)
{

  if (parray[p].emailAddress &&
      parray[p].emailAddress[0] &&
      safestring(parray[p].emailAddress)) {
    return mail_string_to_address(parray[p].emailAddress, subj, str);
  } else {
    return -1;
  }
}

PUBLIC int mail_file_to_address(char *addr, char *subj, char *fname)
{
  char com[1000];
  char tmp[MAX_LINE_SIZE];
  FILE *fp;
  FILE *file_fp;

#ifdef SENDMAILPROG
  sprintf(com, "%s\n", SENDMAILPROG);
#else
  sprintf(com, "%s -s \"%s\" %s < %s&", MAILPROGRAM, subj, addr, fname);
#endif
  fp = popen(com, "w");
  if (!fp)
    return -1;
#ifdef SENDMAILPROG
  fprintf(fp, "To: %s\nSubject: %s\n", addr, subj);
  file_fp = fopen(fname, "r");
  if (!file_fp)
    return -1;
  while (!feof(file_fp)) {
    fgets(tmp, MAX_LINE_SIZE - 1, file_fp);
    if (!feof(file_fp)) {
      fputs(tmp, fp);
    }
  }
  fclose(file_fp);

#endif
  pclose(fp);
  return 0;
}

PUBLIC int mail_file_to_user(int p, char *subj, char *fname)
{

  if (parray[p].emailAddress &&
      parray[p].emailAddress[0] &&
      safestring(parray[p].emailAddress)) {
    return mail_file_to_address(parray[p].emailAddress, subj, fname);
  } else {
    return -1;
  }
}


/* Process a command for a user */
PUBLIC int pcommand(int p, char *comstr,...)
{
  char tmp[MAX_LINE_SIZE];
  int retval;
  int current_socket = parray[p].socket;
  va_list ap;
  va_start(ap, comstr);

  vsprintf(tmp, comstr, ap);
  retval = process_input(current_socket, tmp);
  if (retval == COM_LOGOUT) {
    process_disconnection(current_socket);
    net_close_connection(current_socket);
  }
  va_end(ap);
  return retval;
}

PUBLIC int pprintf(int p, char *format,...)
{
  char tmp[10 * MAX_LINE_SIZE];	/* Make sure you can handle 10 lines worth of
				   stuff */
  int retval;
  va_list ap;
  va_start(ap, format);

  retval = vsprintf(tmp, format, ap);
  if (strlen(tmp) > 10 * MAX_LINE_SIZE) {
    fprintf(stderr, "FICS: pprintf buffer overflow\n");
  }
  net_send_string(parray[p].socket, tmp, 1);
  va_end(ap);
  return retval;
}

PUBLIC void pprintf_dohightlight(int p)
{
  if (parray[p].highlight & 0x01)
    pprintf(p, "\033[7m");
  if (parray[p].highlight & 0x02)
    pprintf(p, "\033[1m");
  if (parray[p].highlight & 0x04)
    pprintf(p, "\033[4m");
  if (parray[p].highlight & 0x08)
    pprintf(p, "\033[2m");
}

PUBLIC int pprintf_highlight(int p, char *format,...)
{
  char tmp[10 * MAX_LINE_SIZE];
  int retval;
  va_list ap;

  va_start(ap, format);
  pprintf_dohightlight(p);
  retval = vsprintf(tmp, format, ap);
  if (strlen(tmp) > 10 * MAX_LINE_SIZE) {
    fprintf(stderr, "FICS: pprintf buffer overflow\n");
  }
  net_send_string(parray[p].socket, tmp, 1);
  va_end(ap);
  if (parray[p].highlight)
    pprintf(p, "\033[0m");
  return retval;
}

PUBLIC void sprintf_dohightlight(int p, char *s)
{

  if (parray[p].highlight & 0x01)
    strcat(s, "\033[7m");
  if (parray[p].highlight & 0x02)
    strcat(s, "\033[1m");
  if (parray[p].highlight & 0x04)
    strcat(s, "\033[4m");
  if (parray[p].highlight & 0x08)
    strcat(s, "\033[2m");
}

PUBLIC int psprintf_highlight(int p, char *s, char *format,...)
{
  int retval;
  va_list ap;

  va_start(ap, format);
  if (parray[p].highlight) {
    sprintf_dohightlight(p, s);
    retval = vsprintf(s + strlen(s), format, ap);
    strcat(s, "\033[0m");
  } else {
    retval = vsprintf(s, format, ap);
  }
  va_end(ap);
  return retval;
}

PUBLIC int pprintf_prompt(int p, char *format,...)
{
  char tmp[10 * MAX_LINE_SIZE];	/* Make sure you can handle 10 lines worth of
				   stuff */
  int retval;
  va_list ap;

  va_start(ap, format);

  retval = vsprintf(tmp, format, ap);
  if (strlen(tmp) > 10 * MAX_LINE_SIZE) {
    fprintf(stderr, "FICS: pprintf_prompt buffer overflow\n");
  }
  net_send_string(parray[p].socket, tmp, 1);
  net_send_string(parray[p].socket, parray[p].prompt, 1);
  va_end(ap);
  return retval;
}

PUBLIC int pprintf_noformat(int p, char *format,...)
{
  char tmp[10 * MAX_LINE_SIZE];	/* Make sure you can handle 10 lines worth of
				   stuff */
  int retval;
  va_list ap;

  va_start(ap, format);

  retval = vsprintf(tmp, format, ap);
  if (strlen(tmp) > 10 * MAX_LINE_SIZE) {
    fprintf(stderr, "FICS: pprintf_noformat buffer overflow\n");
  }
  net_send_string(parray[p].socket, tmp, 0);
  va_end(ap);
  return retval;
}


/*******************       grimm          *************/
/*******************    added below       *************/
PUBLIC int psend_raw_file(int p, char *dir, char *file)
{
  FILE *fp;
  char tmp[MAX_LINE_SIZE];
  char fname[MAX_FILENAME_SIZE];
  int num;

  if (dir)
    sprintf(fname, "%s/%s", dir, file);
  else
    strcpy(fname, file);
  fp = fopen(fname, "r");
  if (!fp)
    return -1;
  while ((num = fread(tmp, sizeof(char), MAX_LINE_SIZE - 1, fp)) > 0) {
    tmp[num] = '\0';
    net_send_string(parray[p].socket, tmp, 1);
  }
  fclose(fp);
  return 0;
}

PUBLIC int psend_file(int p, char *dir, char *file)
{
  FILE *fp;
  char tmp[MAX_LINE_SIZE];
  char fname[MAX_FILENAME_SIZE];
  int lcount = parray[p].d_height - 1;

  if (parray[p].last_file)
    rfree(parray[p].last_file);
  parray[p].last_file = NULL;
  parray[p].last_file_byte = 0L;

  if (dir)
    sprintf(fname, "%s/%s", dir, file);
  else
    strcpy(fname, file);
  fp = fopen(fname, "r");
  if (!fp)
    return -1;
  while (!feof(fp) && (--lcount > 0)) {
    fgets(tmp, MAX_LINE_SIZE - 1, fp);
    if (!feof(fp)) {
      net_send_string(parray[p].socket, tmp, 1);
    }
  }
  if (!feof(fp)) {
    parray[p].last_file = xstrdup(fname);
    parray[p].last_file_byte = ftell(fp);
    pprintf(p, "Type [next] to see next page.\n");
  }
  fclose(fp);
  return 0;
}

/*
 * Marsalis added on 8/27/95 so that [next] does not
 * appear in the logout process for those that have
 * a short screen height.  (Fixed due to complaint
 * in Bug's messages).
 */
PUBLIC int psend_logoutfile(int p, char *dir, char *file)
{
  FILE *fp;
  char tmp[MAX_LINE_SIZE];
  char fname[MAX_FILENAME_SIZE];

  if (parray[p].last_file)
    rfree(parray[p].last_file);
  parray[p].last_file = NULL;
  parray[p].last_file_byte = 0L;

  if (dir)
    sprintf(fname, "%s/%s", dir, file);
  else
    strcpy(fname, file);
  fp = fopen(fname, "r");
  if (!fp)
    return -1;
  while (!feof(fp)) {
    fgets(tmp, MAX_LINE_SIZE - 1, fp);
    if (!feof(fp)) {
	net_send_string(parray[p].socket, tmp, 1);
    }
  }

  fclose(fp);
  return 0;
}

PUBLIC int pmore_file(int p)
{
  FILE *fp;
  char tmp[MAX_LINE_SIZE];
  int lcount = parray[p].d_height - 1;

  if (!parray[p].last_file) {
    pprintf(p, "There is no more.\n");
    return -1;
  }
  fp = fopen(parray[p].last_file, "r");
  if (!fp) {
    pprintf(p, "File not found!\n");
    return -1;
  }
  fseek(fp, parray[p].last_file_byte, SEEK_SET);

  while (!feof(fp) && (--lcount > 0)) {
    fgets(tmp, MAX_LINE_SIZE, fp);
    if (!feof(fp)) {
	net_send_string(parray[p].socket, tmp, 1);
    }
  }
  if (!feof(fp)) {
    parray[p].last_file_byte = ftell(fp);
    pprintf(p, "Type [next] to see next page.\n");
  } else {
    rfree(parray[p].last_file);
    parray[p].last_file = NULL;
    parray[p].last_file_byte = 0L;
  }
  fclose(fp);
  return 0;
}

PUBLIC int psend_command(int p, char *command, char *input)
{
  FILE *fp;
  char tmp[MAX_LINE_SIZE];
  int num;

  if (input)
    fp = popen(command, "w");
  else
    fp = popen(command, "r");
  if (!fp)
    return -1;
  if (input) {
    fwrite(input, sizeof(char), strlen(input), fp);
  } else {
    while (!feof(fp)) {
      num = fread(tmp, sizeof(char), MAX_LINE_SIZE - 1, fp);
      tmp[num] = '\0';
      net_send_string(parray[p].socket, tmp, 1);
    }
  }
  pclose(fp);
  return 0;
}

PUBLIC char *stolower(char *str)
{
  int i;

  if (!str)
    return NULL;
  for (i = 0; str[i]; i++) {
    if (isupper(str[i])) {
      str[i] = tolower(str[i]);
    }
  }
  return str;
}

PUBLIC int safechar(int c)
{
  if ((c == '>') || (c == '!') || (c == '&') || (c == '*') || (c == '?') ||
      (c == '/') || (c == '<') || (c == '|') || (c == '`') || (c == '$'))
    return 0;
  return 1;
}

PUBLIC int safestring(char *str)
{
  int i;

  if (!str)
    return 1;
  for (i = 0; str[i]; i++) {
    if (!safechar(str[i]))
      return 0;
  }
  return 1;
}

PUBLIC int alphastring(char *str)
{
  int i;

  if (!str)
    return 1;
  for (i = 0; str[i]; i++) {
    if (!isalpha(str[i])) {
      return 0;
    }
  }
  return 1;
}

PUBLIC int printablestring(char *str)
{
  int i;

  if (!str)
    return 1;
  for (i = 0; str[i]; i++) {
    if ((!isprint(str[i])) && (str[i] != '\t') && (str[i] != '\n'))
      return 0;
  }
  return 1;
}

PUBLIC char *xstrdup(const char *str)
{
  char *tmp;

  if (!str)
    return NULL;
  tmp = rmalloc(strlen(str) + 1);
  strcpy(tmp, str);
  return tmp;
}

PUBLIC char *hms_desc(int t)
{
static char tstr[80];
int days, hours, mins, secs;

    days  = (t / (60*60*24));
    hours = ((t % (60*60*24)) / (60*60));
    mins  = (((t % (60*60*24)) % (60*60)) / 60);
    secs  = (((t % (60*60*24)) % (60*60)) % 60);
    if ((days==0) && (hours==0) && (mins==0)) {
      sprintf(tstr, "%d sec%s",
                 secs, (secs==1) ? "" : "s");
    } else if ((days==0) && (hours==0)) {
/*      sprintf(tstr, "%d min%s, %d sec%s",
                 mins, (mins==1) ? "" : "s",
                 secs, (secs==1) ? "" : "s");  */
      sprintf(tstr, "%d min%s",
                 mins, (mins==1) ? "" : "s");
    } else if (days==0) {
      sprintf(tstr, "%d hr%s, %d min%s, %d "
                 "sec%s",
                 hours, (hours==1) ? "" : "s",
                 mins, (mins==1) ? "" : "s",
                 secs, (secs==1) ? "" : "s");
    } else {
      sprintf(tstr, "%d day%s, %d hour%s, %d minute%s "
                 "and %d second%s",
                 days, (days==1) ? "" : "s",
                 hours, (hours==1) ? "" : "s",
                 mins, (mins==1) ? "" : "s",
                 secs, (secs==1) ? "" : "s");
    }
    return tstr;
}

PUBLIC char *hms(int t, int showhour, int showseconds, int spaces)
{
  static char tstr[20];
  char tmp[10];
  int h, m, s;

  h = t / 3600;
  t = t % 3600;
  m = t / 60;
  s = t % 60;
  if (h || showhour) {
    if (spaces)
      sprintf(tstr, "%d : %02d", h, m);
    else
      sprintf(tstr, "%d:%02d", h, m);
  } else {
    sprintf(tstr, "%d", m);
  }
  if (showseconds) {
    if (spaces)
      sprintf(tmp, " : %02d", s);
    else
      sprintf(tmp, ":%02d", s);
    strcat(tstr, tmp);
  }
  return tstr;
}

PRIVATE char *strtime(struct tm * stm)
{
  static char tstr[100];

#if defined (SGI)
  strftime(tstr, sizeof(tstr), "%a %b %e, %H:%M %Z", stm);
#else
  strftime(tstr, sizeof(tstr), "%a %b %e, %k:%M %Z", stm);
#endif
  return (tstr);
}

PUBLIC char *fix_time(char *old_time) {

  char day[5];
  char month[5];
  char date[5];
  char new_time[20];
  char i;

  sscanf(old_time, "%s %s %s", day, month, date);

  if (date[2] != ',') {
    i = date[0];
    date[0] = '0';
    date[1] = i;
  }
  date[2] = '\0';

  sprintf (new_time, "%s, %s %s", day, month, date);

  return new_time;
}

PUBLIC char *strltime(time_t *clock)
{
  struct tm *stm = localtime(clock);
  return strtime(stm);
}

PUBLIC char *strgtime(time_t *clock)
{
  struct tm *stm = gmtime(clock);
  return strtime(stm);
}

/* This is used only for relative timeing since it reports seconds since
 * about 5:00pm on Feb 16, 1994
 */
PUBLIC unsigned tenth_secs(void)
{
  struct timeval tp;
  struct timezone tzp;

  gettimeofday(&tp, &tzp);
/* .1 seconds since 1970 almost fills a 32 bit int! So lets subtract off
 * the time right now */
  return ((tp.tv_sec - 331939277) * 10L) + (tp.tv_usec / 100000);
}

/* This is to translate tenths-secs time back into 1/1/70 time in full
 * seconds, because vek didn't read utils.c when he programmed new ratings.
   1 sec since 1970 fits into a 32 bit int OK.
*/
PUBLIC int untenths(unsigned tenths)
{
  return (tenths / 10 + 331939277 + 0xffffffff / 10 + 1);
}

PUBLIC char *tenth_str(unsigned t, int spaces)
{
  return hms((t + 5) / 10, 0, 1, spaces);	/* Round it */
}

#define MAX_TRUNC_SIZE 100

/* Warning, if lines in the file are greater than 1024 bytes in length, this
   won't work! */
/* nasty bug fixed by mann, 3-12-95 */
PUBLIC int truncate_file(char *file, int lines)
{
  FILE *fp;
  int bptr = 0, trunc = 0, i;
  char tBuf[MAX_TRUNC_SIZE][MAX_LINE_SIZE];

  if (lines > MAX_TRUNC_SIZE)
    lines = MAX_TRUNC_SIZE;
  fp = fopen(file, "r");
  if (!fp)
    return 1;
  while (!feof(fp)) {
    fgets(tBuf[bptr], MAX_LINE_SIZE, fp);
    if (feof(fp))
      break;
    if (tBuf[bptr][strlen(tBuf[bptr]) - 1] != '\n') {	/* Line too long */
      fclose(fp);
      return -1;
    }
    bptr++;
    if (bptr == lines) {
      trunc = 1;
      bptr = 0;
    }
  }
  fclose(fp);
  if (trunc) {
    fp = fopen(file, "w");
    for (i = 0; i < lines; i++) {
      fputs(tBuf[bptr], fp);
      bptr++;
      if (bptr == lines) {
	bptr = 0;
      }
    }
    fclose(fp);
  }
  return 0;
}

/* Warning, if lines in the file are greater than 1024 bytes in length, this
   won't work! */
PUBLIC int lines_file(char *file)
{
  FILE *fp;
  int lcount = 0;
  char tmp[MAX_LINE_SIZE];

  fp = fopen(file, "r");
  if (!fp)
    return 0;
  while (!feof(fp)) {
    if (fgets(tmp, MAX_LINE_SIZE, fp))
      lcount++;
  }
  fclose(fp);
  return lcount;
}

PUBLIC int file_has_pname(char *fname, char *plogin)
{
  if (!strcmp(file_wplayer(fname), plogin))
    return 1;
  if (!strcmp(file_bplayer(fname), plogin))
    return 1;
  return 0;
}

PUBLIC char *file_wplayer(char *fname)
{
  static char tmp[MAX_FILENAME_SIZE];
  char *ptr;
  strcpy(tmp, fname);
  ptr = rindex(tmp, '-');
  if (!ptr)
    return "";
  *ptr = '\0';
  return tmp;
}

PUBLIC char *file_bplayer(char *fname)
{
  char *ptr;

  ptr = rindex(fname, '-');
  if (!ptr)
    return "";
  return ptr + 1;
}


/* Hey, leave this code alone.  "a" is always in network byte order,
   which is big-endian, even on a little-endian machine.  I fixed this
   code to handle that correctly a while ago, and someone
   gratuitiously changed it so that it would work correctly only on a
   big-endian machine (like a Sun).  I have now changed it back. --mann
*/
PUBLIC char *dotQuad(unsigned int a)
{
  static char tmp[20];
  unsigned char *aa = (unsigned char *) &a;

  sprintf(tmp, "%d.%d.%d.%d", aa[0], aa[1], aa[2], aa[3]);
  return tmp;
}

PUBLIC int available_space(void)
{
#if defined(SYSTEM_NEXT)
  struct statfs buf;

  statfs(player_dir, &buf);
  return ((buf.f_bsize * buf.f_bavail));
#elif defined(SYSTEM_ULTRIX)
  struct fs_data buf;

  statfs(player_dir, &buf);
  return ((1024 * buf.bfreen));
#elif defined(SYSTEM_SUN4)
/*
  struct statfs buf;

  statfs(player_dir, buf);
  return (1024 * buf.f_bfree); */
  return 100000000;		/* Infinite space */
#else
   return 100000000;		/* Infinite space */
#endif
}

PUBLIC int file_exists(char *fname)
{
  FILE *fp;

  fp = fopen(fname, "r");
  if (!fp)
    return 0;
  fclose(fp);
  return 1;
}

PUBLIC char *ratstr(int rat)
{
  static int on = 0;
  static char tmp[20][10];

  if (on == 20)
    on = 0;
  if (rat) {
    sprintf(tmp[on], "%4d", rat);
  } else {
    sprintf(tmp[on], "----");

  }
  on++;
  return tmp[on - 1];
}

PUBLIC char *ratstrii(int rat, int reg)
{
  static int on = 0;
  static char tmp[20][10];

  if (on == 20)
    on = 0;
  if (rat) {
    sprintf(tmp[on], "%4d", rat);
  } else {
    if (reg) {
      sprintf(tmp[on], "----");
    } else {
      sprintf(tmp[on], "++++");
    }
  }
  on++;
  return tmp[on - 1];
}

struct t_tree {
  struct t_tree *left, *right;
  char name;			/* Not just 1 char - space for whole name */
};				/* is allocated.  Maybe a little cheesy? */

struct t_dirs {
  struct t_dirs *left, *right;
  time_t mtime;			/* dir's modification time */
  struct t_tree *files;
  char name;			/* ditto */
};

PRIVATE char **t_buffer = NULL; /* pointer to next space in return buffer */
PRIVATE int t_buffersize = 0;	/* size of return buffer */

/* fill t_buffer with anything matching "want*" in file tree t_tree */
PRIVATE void t_sft(char *want, struct t_tree *t)
{
  if (t) {
    int cmp = strncmp(want, &t->name, strlen(want));
    if (cmp <= 0)		/* if want <= this one, look left */
      t_sft(want, t->left);
    if (t_buffersize && (cmp == 0)) {	/* if a match, add it to buffer */
      t_buffersize--;
      *t_buffer++ = &(t->name);
    }
    if (cmp >= 0)		/* if want >= this one, look right */
      t_sft(want, t->right);
  }
}

/* delete file tree t_tree */
PRIVATE void t_cft(struct t_tree **t)
{
  if (*t) {
    t_cft(&(*t)->left);
    t_cft(&(*t)->right);
    rfree(*t);
    *t = NULL;
  }
}

/* make file tree for dir d */
PRIVATE void t_mft(struct t_dirs *d)
{
  DIR *dirp;
#ifdef USE_DIRENT
  struct dirent *dp;
#else
  struct direct *dp;
#endif
  struct t_tree **t;

  if ((dirp = opendir(&(d->name))) == NULL) {
    fprintf(stderr, "FICS:mft() couldn't opendir.\n");
  } else {
    while ((dp = readdir(dirp))) {
      t = &d->files;
      if (dp->d_name[0] != '.') {	/* skip anything starting with . */
	while (*t) {
	  if (strcmp(dp->d_name, &(*t)->name) < 0) {
	    t = &(*t)->left;
	  } else {
	    t = &(*t)->right;
	  }
	}
	*t = rmalloc(sizeof(struct t_tree) + strlen(dp->d_name));
	(*t)->right = (*t)->left = NULL;
	strcpy(&(*t)->name, dp->d_name);
      }
    }
    closedir(dirp);
  }
}

PUBLIC int search_directory(char *dir, char *filter, char **buffer, int buffersize)
{
/* dir = directory to search
   filter = what to search for
   buffer = where to store pointers to matches
   buffersize = how many pointers will fit inside buffer */

  static struct t_dirs *ramdirs = NULL;
  struct t_dirs **i;
  int cmp;
  static char nullify = '\0';
  struct stat statbuf;

  t_buffer = buffer;
  t_buffersize = buffersize;

  if (!stat(dir, &statbuf)) {
    if (filter == NULL)		/* NULL becomes pointer to null string */
      filter = &nullify;
    i = &ramdirs;
    while (*i) {			/* find dir in dir tree */
      cmp = strcmp(dir, &(*i)->name);
      if (cmp == 0)
	break;
      else if (cmp < 0)
	i = &(*i)->left;
      else
	i = &(*i)->right;
    }
    if (!*i) {				/* if dir isn't in dir tree, add him */
      *i = rmalloc(sizeof(struct t_dirs) + strlen(dir));
      (*i)->left = (*i)->right = NULL;
      (*i)->files = NULL;
      strcpy(&(*i)->name, dir);
    }
    if ((*i)->files) {			/* delete any obsolete file tree */
      if ((*i)->mtime != statbuf.st_mtime) {
	t_cft(&(*i)->files);
      }
    }
    if ((*i)->files == NULL) {		/* if no file tree for him, make one */
      (*i)->mtime = statbuf.st_mtime;
      t_mft(*i);
    }
    t_sft(filter, (*i)->files);		/* finally, search for matches */
  }
  return (buffersize - t_buffersize);
}

PUBLIC int display_directory(int p, char **buffer, int count)
/* buffer contains 'count' string pointers */
{
  int i;
  multicol *m = multicol_start(count);

  for (i = 0; (i < count); i++)
    multicol_store(m, *buffer++);
  multicol_pprint(m, p, 78, 1);
  multicol_end(m);
  return (i);
}
