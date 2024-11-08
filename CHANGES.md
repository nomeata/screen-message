screen-message (0.29)

  - Add keywords to desktop file as requested as described in #693918

 -- Tiago Bortoletto Vaz <tiago@debian.org>  Wed, 06 Nov 2024 09:33:47 -0500

screen-message (0.27)

  - Move sm from /usr/games to /usr/bin. Thanks to Josh Triplet
  - Move manpage from section 6 to section 1. Thanks to Josh Triplett.

 -- Tiago Bortoletto Vaz <tiago@debian.org>  Wed, 16 Oct 2024 11:24:09 -0400

screen-message (0.26)

  * Fix memory leak (thanks to Santtu Lakkala)

 -- Joachim Breitner <nomeata@debian.org>  Fri, 26 Feb 2021 14:12:32 +0100

screen-message (0.25)

  * Support -i and Ctrl-I

 -- Joachim Breitner <nomeata@debian.org>  Tue, 09 May 2017 08:11:20 -0400

screen-message (0.24)

  * New upstream release

 -- Joachim Breitner <nomeata@debian.org>  Mon, 09 May 2016 12:50:10 +0200

screen-message (0.23) unstable; urgency=medium

  Disable temporary disabling of anti-aliasing

  It seems to have stopped working with recent versions of gtk3, and
  furthermore causes every second keypress to be ignored.

 -- Joachim Breitner <nomeata@debian.org>  Tue, 23 Dec 2014 19:41:09 +0100

screen-message (0.22.2)

  * New upstream release

 -- Joachim Breitner <nomeata@debian.org>  Tue, 30 Sep 2014 15:48:32 +0200

screen-message (0.22.1)

  * New minor upstream release (fixes sm.desktop), thanks to Sebastian Pipping
    for the patch.

 -- Joachim Breitner <nomeata@debian.org>  Fri, 30 May 2014 10:21:26 +0200

screen-message (0.22)

  * New minor upstream release

 -- Joachim Breitner <nomeata@debian.org>  Thu, 22 May 2014 23:54:38 +0200

screen-message (0.21)

  * use stock gtk fullscreen functionality

 -- Joachim Breitner <nomeata@debian.org>  Fri, 09 May 2014 09:45:46 +0200

screen-message (0.20) experimental; urgency=low

  * New upstream release

 -- Joachim Breitner <nomeata@debian.org>  Sat, 24 Nov 2012 20:28:14 +0100

screen-message (0.19) unstable; urgency=low

  * Fixes SIGSEGV by not using g_object_set

 -- Joachim Breitner <nomeata@debian.org>  Mon, 17 May 2010 18:13:34 +0200

screen-message (0.18)

  * Does not focus the hidden text input, avoiding unwanted pop-ups of
    a possible virtual keyboard.
  * Ship .desktop file

 -- Joachim Breitner <nomeata@debian.org>  Fri, 24 Jul 2009 12:46:27 +0200

screen-message (0.17)

  * Properly hide entry when no data is provided

 -- Joachim Breitner <nomeata@debian.org>  Mon, 20 Jul 2009 23:44:46 +0200

screen-message (0.16)

  * 3 second timeout, react on cursor movements, thanks to
    Paul Wise for the patch.
  * Avoid flicker when toggling the entry.

 -- Joachim Breitner <nomeata@debian.org>  Thu, 27 Nov 2008 14:37:00 +0100

screen-message (0.15)

  * Back to using a GtkDraw for the text, behaves better with matchbox
  * Show mouse pointer while entry is visible

 -- Joachim Breitner <nomeata@debian.org>  Sat, 23 Aug 2008 23:50:10 +0200

screen-message (0.14)

  * Only show entry from start on when nothing is provided
  * Redraw screen on screen configuration changes

 -- Joachim Breitner <nomeata@debian.org>  Sat, 16 Aug 2008 16:07:25 -0300

screen-message (0.13)

  * Floats and auto-hides text entry
  * Ignore trailing newlines on stdin, thanks to Chris Lamb for the patch.

 -- Joachim Breitner <nomeata@debian.org>  Tue, 12 Aug 2008 01:35:39 -0300

screen-message (0.12)

  * --foreground, --background, --font, thx to Rhonda
  * --rotate [0|1|2|3] for rotation

 -- Joachim Breitner <nomeata@debian.org>  Tue, 05 Aug 2008 19:39:46 -0300

screen-message (0.11)

  * Manpage in section 6

 -- Joachim Breitner <nomeata@debian.org>  Thu, 17 Apr 2008 23:39:57 +0200

screen-message (0.10) unstable; urgency=low

  * Includes an icon
  * Move binary to /usr/games

 -- Joachim Breitner <nomeata@debian.org>  Thu, 20 Mar 2008 14:15:49 +0100

screen-message (0.9)

  * Starts with text selected

 -- Joachim Breitner <nomeata@debian.org>  Wed, 24 Oct 2007 00:53:43 +0200

screen-message (0.8)

  * Make the initial text size the same as normal text
  * Pressing Esc when there is no text quits the program
    (Both changes thanks to Paul Wise)

 -- Joachim Breitner <nomeata@debian.org>  Mon, 22 Oct 2007 17:53:30 +0200

screen-message (0.7)

  * Fixes: only first argument is used as the text
    Thanks to Florian Ragwitz for the patch.
  * Sets the size to the size of the screen. This makes fullscren
    work with xmonad, please tell me if it causes problems with other
    WMs.

 -- Joachim Breitner <nomeata@debian.org>  Sun, 21 Oct 2007 21:19:41 +0200

screen-message (0.6)

  * Read from stdin if parameter is -
  * Middle-Clicking anywhere works
  * End program upon destroy
  * Fix colors to black/white independent of the theme

 -- Joachim Breitner <nomeata@debian.org>  Tue, 19 Jun 2007 13:19:51 +0100

screen-message (0.5)

  * rename to screen-message, as there ∃ sm in Debian

 -- Joachim Breitner <nomeata@debian.org>  Thu, 14 Jun 2007 20:21:20 +0100

sm (0.4)

  * automakized

 -- Joachim Breitner <nomeata@debian.org>  Thu, 14 Jun 2007 18:07:53 +0100

sm (0.3)

  * Get rid of a warning (thx to Jérémy Bobbio <lunar@debian.org>)
  * Automake the whole thing

 -- Joachim Breitner <nomeata@debian.org>  Thu, 14 Jun 2007 16:51:22 +0100

sm (0.2)

  * Version ready for release

 -- Joachim Breitner <nomeata@debian.org>  Thu, 14 Jun 2007 14:24:19 +0100

sm (0.1)

  * Initial release.

 -- Joachim Breitner <nomeata@debian.org>  Thu, 14 Jun 2007 13:33:54 +0100
