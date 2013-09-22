% HEXEDIT(1)
% Pascal Rigaux
% February 2013


# NAME

hexedit - view and edit files in hexadecimal or in ASCII

# SYNOPSIS

hexedit [-s | --sector] [-m | --maximize] [-h | --help] [filename]

# DESCRIPTION

hexedit shows a file both in ASCII and in hexadecimal. The file can be a device as the file is read a piece at a time. You can modify the file and search through it.

# OPTIONS

"-s, --sector" Format the display to have entire sectors.

"-m, --maximize" Try to maximize the display.

"-h, --help" Show the usage.

# COMMANDS (quickly)

*Moving*

    <, > :  go to start/end of the file
    Right:  next character
    Left:   previous character
    Down:   next line
    Up:     previous line
    Home:   beginning of line
    End:    end of line
    PUp:    page forward
    PDown:  page backward
    Miscellaneous

    F2:     save
    F3:     load file
    F1:     help
    Ctrl-L: redraw
    Ctrl-Z: suspend
    Ctrl-X: save and exit
    Ctrl-C: exit without saving

    Tab:    toggle hex/ascii
    Return: go to
    Backspace: undo previous character
    Ctrl-U: undo all
    Ctrl-S: search forward
    Ctrl-R: search backward
    Cut&Paste

    Ctrl-Space: set mark
    Esc-W:  copy
    Ctrl-Y: paste
    Esc-Y:  paste into a file
    Esc-I:  fill

# COMMANDS (full and detailed)

    o Right-Arrow, Left-Arrow, Down-Arrow, Up-Arrow - move the cursor. 
    o Ctrl+F, Ctrl+B, Ctrl+N, Ctrl+P - move the cursor. 
    o Ctrl+Right-Arrow, Ctrl+Left-Arrow, Ctrl+Down-Arrow, Ctrl+Up-Arrow - move n times the cursor. 
    o Esc+Right-Arrow, Esc+Left-Arrow, Esc+Down-Arrow, Esc+Up-Arrow - move n times the cursor. 
    o Esc+F, Esc+B, Esc+N, Esc+P - move n times the cursor. 
    o Home, Ctrl+A - go the beginning of the line. 
    o End, Ctrl+E - go to the end of the line. 
    o Page up, Esc+V, F5 - go up in the file by one page. 
    o Page down, Ctrl+V, F6 - go down in the file by one page. 
    o <, Esc+<, Esc+Home - go to the beginning of the file. 
    o >, Esc+>, Esc+End - go to the end of the file (for regular files that have a size). 
    o Ctrl+Z - suspend hexedit. 
    o Ctrl+U, Ctrl+_, Ctrl+/ - undo all (forget the modifications). 
    o Ctrl+Q - read next input character and insert it (this is useful for inserting control characters and bound keys). 
    o Tab, Ctrl+T - toggle between ASCII and hexadecimal. 
    o /, Ctrl+S - search forward (in ASCII or in hexadecimal, use TAB to change). 
    o Ctrl+R - search backward. 
    o Ctrl+G, F4 - go to a position in the file. 
    o Return - go to a sector in the file if --sector is used, otherwise go to a position in the file. 
    o Esc+L - display the page starting at the current cursor position. 
    o F2, Ctrl+W - save the modifications. 
    o F1, Esc+H - help (show the man page). 
    o Ctrl+O, F3 - open another file 
    o Ctrl+L - redisplay (refresh) the display (usefull when your terminal screws up). 
    o Backspace, Ctrl+H - undo the modifications made on the previous byte. 
    o Esc+Ctrl+H - undo the modifications made on the previous bytes. 
    o Ctrl+Space, F9 - set mark where cursor is. 
    o Esc+W, Delete, F7 - copy selected region. 
    o Ctrl+Y, Insert, F8 - paste (yank) previously copied region. 
    o Esc+Y, F11 - save previously copied region to a file. 
    o Esc+I, F12 - fill the selection with a string 
    o Esc+T - truncate the file at the current location 
    o Ctrl+C - unconditional quit (without saving). 
    o F10, Ctrl+X - quit.

For the Esc commands, it sometimes works to use Alt instead of Esc. Funny things here (especially for froggies :) egrave = Alt+H , ccedilla = Alt+G, Alt+Y = ugrave. 

*Modeline*

At the bottom of the display you have the modeline (copied from emacs). As in emacs, you have the indications --, ** and %% meaning unmodified, modified and read-only. Then you have the name of the file you're currently editing. Next to it is the current position of the cursor in the file followed by the total file size. The total file size isn't quite correct for devices. 
While in --sector mode, it shows the sector the cursor is in.

*Editing*

You can edit in ASCII or in hexadecimal. You can switch between the two with Tab. When the file is read-only, you can't edit it. When trying to edit a read-only file, a message (``File is read-only'') tells you it is non-writable. 
The modifications are shown in bold until they are saved. The modeline indicates whether you have modified the file or not. 
When editing in hexadecimal, only 0,1,...,9, a,b,...,f, A,B,...F are legal. Other keys are unbound. The first time you hit an unbound key, the help pops up. It won't pop again unless you call the help directly (with F1). 
When editing in ascii, you can find it difficult to enter characters like / which are bound to a function. The solution is to use the quoted insert function Ctrl+Q, the key after the quoted insert function is not processed by hexedit (like emacs' quoted-insert, or like the \\ character in C).
Searching

You can search for a string in ASCII or in hexadecimal. You can switch between the two with Tab. If the string is found, the cursor is moved to the beginning of the matching location. If the search failed, a message (``not found'') tells you so. You can cancel the search by pressing a key. 
The search in hexadecimal is a bit confusing. You must give a hexadecimal string with an even number of characters. The search can then be done byte by byte. If you want to search a long number (eg: a 32 bit number), you must know the internal representation of that number (little/big endian problem) and give it the way it is in memory. For example, on an Intel processor (little endian), you must swap every bytes: 0x12345678 is written 0x78563412 in memory and that's the string you must give to the search engine. 
Before searching you are asked if you want to save the changes, if the file is edited.

For more sophisticated search, see Volker Schatz's patch at http://www.volkerschatz.com/unix/homebrew.html#hexedit.

*Selecting, copying, pasting, filling*

First, select the part of the buffer you want to copy: start setting the mark where you want. Then go to the end of the area you want to copy (you can use the go to function and the search functions). Then copy it. You can then paste the copied area in the current file or in another file.

You can also fill the selected area with a string or a character: start choosing the block you want to fill in (set mark then move to the end of the block), and call the fill function (F12). hexedit ask you the string you want to fill the block with. 
The code is not tuned for huge filling as it keeps the modifications in memory until you save them. That's why hexedit will warn you if you try to fill in a big block.

When the mark is set, the selection is shown in reverse mode. 
Be aware that the copied area contains the modifications done at the time of the copy. But if you undo the modifications, it does not change the content of the copy buffer. It seems obvious but it's worth saying.

*Scrolling*

The scrolling is different whether you are in --sector mode or not. In normal mode, the scrolling is line by line. In sector mode, the scrolling is sector by sector. In both modes, you can force the display to start at a given position using Esc+L.

# SEE ALSO

`od`(1), `hdump`(1), `hexdump`(1), `bpe`(1), `hexed`(1), `beav`(1).

# AUTHOR

Pixel (Pascal Rigaux) <pixel@rigaux.org>, 
Home page is http://rigaux.org/.

# UNRESTRICTIONS

hexedit is Open Source; anyone may redistribute copies of hexedit to anyone under the terms stated in the GNU General Public License.
You can find hexedit at 
http://rigaux.org/hexedit-1.2.13.src.tgz and 
http://rigaux.org/hexedit-1.2.13.bin.i386.dynamic.tgz.

# TODO

Anything you think could be nice...

# LIMITATIONS

There are problems with the curses library given with Redhat 5.0 that make hexedit think the terminal is huge. The result is that hexedit is not usable.
The shortcuts work on some machines, and not on others. That's why there are many shortcuts for each function. The Ctrl+Arrows and the Alt+. do not work work as they should most of the time. On SUNs, you must do Ctrl+V-Ctrl+V instead of Ctrl+V (!); and the Alt key is the diamond one.

While searching, it could be interesting to know which position the search has reached. It's always nice to see something moving to help waiting.

The hexadecimal search could be able to search modulo 4 bits instead of 8 bits. Another feature could be to complete padd odd length hexadecimal searches with zeros.

# BUGS

I have an example where the display is completly screwed up. It seems to be a bug in ncurses (or maybe in xterm and rxvt)?? Don't know if it's me using ncurses badly or not... It seems to happen when hexedit leaves only one space at the end of the lines... If anyone has a (or the) solution, please tell me!
If you have any problem with the program (even a small one), please do report it to me. Remarks of any kind are also welcome.


