## jls - simple file list

jls is a simple utility I created because I
cannot remember ls(1) options between various
[Unix](https://en.wikipedia.org/wiki/Unix)
Systems.
I also wanted a default of printing only Last
Modification Date/Time and File Name.

It also avoids command line size by reading
the files to process from stdin or a Text File.
Some
[Unix](https://en.wikipedia.org/wiki/Unix)
Systems have a rather short Command Line Buffer.

This requires [j\_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* Set "DESTDIR" for where you want this to install.  Examples:
  * setenv DESTDIR /usr/local
  * export DESTDIR=/usr/local
* this assumes [j\_lib2](https://github.com/jmcunx/j_lib2)
  is also installed under "DESTDIR".
* Edit Makefile, uncomment areas associated to the OS
  you want to compile on.
  OS Sections:
  * Linux 64 bit (default)
  * Linux 32 bit
  * BSD 64 bit
  * BSD 32 bit
  * AIX

_To uninstall_, execute
"make uninstall"
from the source directory
