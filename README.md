screen-message
==============

If you just want to display a word or a short, possibly multi-line, text as
large and as quickly as possible on your screen, then `screen-message` is the
right too for you. It has been used already twice at a Debian conference for
the Mugshots.

`screen-message` runs on Linux and Windows and there is an online version on http://sm.nomeata.de/.

Installation Linux
------------------

Get it from your distribution with

    apt install sm

or install it from this source repository, if you know how to do these things.


Installation Windows
--------------------

Get the latest windows installer
[from my webpage](http://www.joachim-breitner.de/en/projects#screen-message). The windows installer lags behind a few versions; let me know if you need a new version.


Usage
-----

Screen Message  will display a given multi-line message as large as possible, fullscreen
and black on white. You can specify the text either when launching sm, or edit it  while
the program is running.

After  a short timeout, the text entry and the quit button will disappear, leaving
nothing on the screen but the entered text. To continue entering text, just start typing
or (left-)click anywhere on the screen.

To clear the displayed text, press Escape.

To invert the colors of the text and the background, press Ctrl-I.

To quit the program, press Ctrl-Q, or Escape twice, or click the “Quit”-button.

Options
-------

 * `[ text | - ]`


   Text  to  display at start up. Defaults to ":-)". If "-" is passed to sm, it will
   read the text to display from the standard input, see REMOTE CONTROLLING SM.

 * `-f`, `--foreground=colordesc`

   Define a different color to use for the foreground of the text  to  display  than
   black.  The text string can be in any of the forms accepted by XParseColor; these
   include name for a color from rgb.txt, such as DarkSlateGray, or a hex
   specification such as #3050b2 or #35b.

 * `-b`, `--background=colordesc`

   Define  a  different  color to use for the background of the text to display than
   white. For possible values, see above.

 * `-i`, `--invert`

   Switch the roles for foreground and  background  colors.  Useful  if  you  prefer
   white-on-black.

 * `-n`, `--font=fontspec`

   Define  a  different font to use than the default sans-serif font of your system.
   The fontspec be the complete name for a truetype  font  (like  "DejaVu  Sans"  or
   "Bitstream  Vera  Serif")  or  just  a  short font family specification ("serif",
   "sans-serif").

 * `-r`, `--rotate=rotation`

   Rotates the display by *rotation * 90* degrees counter-clock-wise. So  `-r 1`  rotates
   the display to the left, and `-r 2` puts it upside down.

 * `-a`, `--align=alignment`

   Aligns the text centered (`-a 0`), left (`-a 1`) or right (`-a 2`).

 * `--` (Double  dash)

   End option parsing. This is used to be able to actually hand over
   text that starts of with an dash.

 * `-h`, `--help`

   This option will give you  a  short  usage  message  summarizing  the  recognized
   options and quits.

 * `-V` `--version`

   This prints the project name together with its version number quits.

Remote controlling `sm`
-----------------------

If  sm  is  called  with `-` as a command line argument, it will read the text to be shown
from the standard input. It will read the input until it reaches the end of the file, or
the  line  form character `\f`, and show the input read so far at once. Newline characters
at the beginning or the end are ignored. The input is assumed to be UTF-8  encoded.

This  can  be  used to create automatic displays of changing data or similar tricks. For
example, the following command will create a simple digital watch:

    (while sleep 1; do date +%T; printf '\f'; done) | sm -


Contact
-------

Use the [GitHub issue tracker] or write to Joachim Breitner <<mail@joachim-breitner.de>>.

[GitHub issue tracker]: (https://github.com/nomeata/screen-message/issues)
