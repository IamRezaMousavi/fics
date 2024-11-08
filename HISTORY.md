# HISTORY

Versions up to 1.2.16 and between 1.2.23 and 1.3.2 are approximate.
Information on changes may not be exact or complete.

1.6.2    News bug fixed (Marsalis), caused crash and corrupted index file.
         ECO brought back (Sparky), bug fixed for use with scratch games
         (uninitialized moveList caused crash).  Examine can now
         be used to load board positions (Sparky).  Works with
         scratch games also.

1.6.1    News rewritten (Marsalis), Much faster code.  Some crash
         protection code (writing player files after every 'set'
         command for example) has been supressed for speed.
         Bug in new playerfile code fixed (sanity checks added to
         avoid crashes).

1.6      Playerfile formats completely recoded (DAV)  new and old
         formats recognized.  New format is written always.  The
         new format has expanded functionallity, more compact form,
         and much faster processing.

1.5.2    Ghosts hopefully killed; no more timeseal sitting;
         Oldmoves implementation changes; game structure shrunk.
         fics_hostname now takes it's contents from SERVER_NAME,
         which should nwo be a DNS resolvable hostname.
         fics_addplayer new account message modernized to include
         brief instructions on how to connect to the server and
         and warn about the use of anauthorzied duplicate accounts.
  both adminproc.c and fics_addplayer modified.

1.5.1    Fixes in journal commands, some bughouse bugs.

1.5.0    Journals allowed.  Some fixes for NULL v. NULL games.

1.4.0    Initial bughouse version.

1.3.3    clearing and showing individual messages.

1.3.2    fixes to open file bugs;
         clearing and showing messages from a particular player.

1.3.1    kibitz level; tell/whisper bugs and similar fixed;
         noplay and gnotify lists.

1.3.0    new admin structure for coordination, responding to suggestions, etc;
         got rid of annoyingly large version numbers :-).

1.2.23-1.2.24 ???

1.2.22   Examining of history games supported.

1.2.21   Language variable; can't refresh private games;
         Got rid of "You are not observing" message when you are observing.
         New news interface; cnewsi, cnewsf, and news show on startup.
         Percent of life stats.

1.2.20   New help interface; index command.

1.2.19   Examine mode (without history game support)
         ECO and NIC codes now supported for history games and for
         interactive reporting on games in process.
         PGN format now supported for email of game scores.
         Direct sendmail support provided with the SENDMAILPROG
         definition in config.h, which overrides any MAILPROGRAM
         definition.  Provides for more reliable and efficient operatio under heavy load.

1.2.18   variable mailmess: mails messages to you.
         messages give the user feedback on what was sent.
         simul commands simallabort, simadjourn, simalladjourn
         (aliases saa sadj saadj)
         simabort given alias sa
         cshout and it prompts fixed
         it gives better feedback
         can restart simuls (or untimed games in simul form) with simmatch
         game format reduced in size
1.2.17   asetpasswd now sends mail to the player telling him the new
         password.
         extra info in up for admins
         annunreg seen by all admins
         hostinfo and lock removed as was fics_delplayer, fics_mailproc
  and mail_proc.
         see messages from one person, clear messages from a person
         More simul bug fixes.
         simprev (alias sp), goboard (alias go, goto), gonum commands.
         allow admin to reset RD; ratings may be set with 0 games played.
1.2.16   Many simul bugs fixed, one fatal bug corrected which caused
         a crash during a simul.
         unobserve command.
         MAILPROGRAM replaced by "sendmail -t" and appropriate "To:"
         and subject headers.  This should help with blank mail
         message problem.  mailhelp and mailsource still depend on MAILPROGRAM
         stuff added for SUN5 compilation
         best info shown in who
1.2.15   Simul bug fixed - losing connection led to a crash
         adjudicate written (forcedraw, forcewin, forceres commands removed)
         hostinfo removed from addplayer
1.2.14   Simul code made operational.
         games list ordered.
         tally code disabled
1.2.13   forcedraw, forcewin, forceres commands
         asetv command replaces pose
1.2.12   bug fixes.
         pose weakened.
1.2.11   First stable version of FICS.  unnotify and unalias had big problems
  that led to crashes and corrupt player files.
         siteinfo removed - caused infinite lag
         mailmess
1.2.10   bug fixes, max length enforced in alias to stop a crash.
1.2.9    autoboot out code added.
1.2.8    aliases fixed, @ added, can alias system commands
         flagging without material claims a draw, not a win.
1.2.7    filter list operational.
         multicol.c used to drop 2048 bytes
1.2.6    rank and best, makerank
         time for next shout shown.
         bug fix to timelog
         login/logouts logged
         addcomment and showcomment
1.2.5    Summon written.
         ban list
  (TD) in who
         board styles fixed
         shout quotas, it and shout modified
         admin command to toggle (*)
         fixes to up
         admins can observe anything
1.2.4    td list
         qtell, getpi, commands for TD
         asetblitz, asetstd
         news,anews
  wild chess made rated, best shows wild, new file
  asetwild
  next
         SGI compilation possible.
1.2.3    lists
         (FM) (GM) (IM) (C) shown in who
         raisedead given a second argument to rename a player
         ahelp, info written
         help files split into help and info
         shutdown fixed
1.2.2    internal version
1.2.1    bug fixes.
         admin gods can only use pose.
         siteinfo shown
1.2      notifiedby flag
         remplayer, asethandle, raisedead written
         nuke improved
         query disabled
1.1      who bug fixed - caused a crash if more than 10 players on.
         ++++ shown in who for unreg players
         early version of nuke.
  (*) shown if level 10 admin
         level 60 given title Assistant superuser.
         who A, who l, who U, who R
         Look of announce and other stuff improved.
1.0  Original Nash code
-----------------------------------------------------------------------------

Here is a more stable, hopefully more portable release of the
FICS source code with many features added.

People who have helped improve this from previous releases
(March 1st 1995 onward) include (FICS names):
DAV, foxbat, grimm, Hawk, hersco, loon, mann, Shane, Sparky, vek
SORRY if you feel you should have been on this list but were forgotten.

And Most thanks to red (Richard Nash) for the original code!
 And Micheal Moore for the original idea of an ICS.

-- Uploaded by Shane Hudson (Shane on FICS).
Thanks to everyone for their support of FICS.
