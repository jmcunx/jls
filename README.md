## jls - simple file list

**Note:** Starting October 12 2023, Microsoft GitHub is forcing
me to use my 2FA access to my repositories via my Cell Phone
or some proprietary application.  So updates to this project
will no longer occur on GitHub.  Updates can be downloaded
from my gemini capsule:

* gemini://gem.sdf.org/jmccue/computer/repository.gmi
* gemini://sdf.org/jmccue/computer/repository.gmi (mirror)

[See gemini wikipedia](https://en.wikipedia.org/wiki/Gemini_(protocol)#Software) for clients.

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

[j\_lib2](https://github.com/jmcunx/j_lib2) is an **optional** dependency.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* If "DESTDIR" is not set, will install under /usr/local
* Execute ./build.sh to create a Makefile
* Works on Linux, BSD and AIX

_To uninstall_, execute
"make uninstall"
from the source directory
