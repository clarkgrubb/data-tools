# BASIC INSTALLATION

To install the necessary Ruby gems and Python packages:

    $ sudo make setup

To put the *data tools* and man pages in your path:

    $ make install

It must be run with permission to create files in the install directory as it creates symlinks to the *data tools* repository.

# INSTALLING ON DEBIAN/UBUNTU

You may find that the Ruby gems or Python packages fail to build because
of missing system packages.  On Debain or Ubuntu these packages can be installed with:

    $ sudo apt-get install ruby-dev python-pip

# INSTALLING ON MAC

Mac OS X comes with Ruby 1.8, which the current version of Nokogiri no longer supports.  A fix is to install an older version:

    $ sudo gem install nokogiri -v 1.5

# SET INSTALLATION DIRECTORY

You can override the choice of install directory (`~/Bin` or `/usr/local/bin`) by setting the `LOCAL_INSTALL_DIR` environment variable.

You can override the choice of man page directory (`~/Man` or `/usr/local/share/man`) by setting the `LOCAL_MAN_DIR` environment variable.

# INSTALL AS ROOT

To build as an unprivileged user but install as root:

     $ make build
     
     $ sudo make setup
     
     $ sudo make install

# PARTIAL INSTALLATION

Installing the compiled executables, scripts, and man pages separately.

    $ make install-build

    $ make install-script
    
    $ make install-man

If the build is failing, one can skip the first step and still install the scripts.

# VIRTUALENV AND RBENV

One could probably use ``virtualenv`` and ``rbenv`` to avoid running ``make setup`` as root.  One would need to be in both environments when running the data tools.

# WINDOWS: MINGW

There is no ``/usr/local/bin/`` directory.  Installation will likely fail unless the ``LOCAL_INSTALL_DIR`` and ``LOCAL_MAN_DIR``environment variables are set.  Optionally one can create the directories ``~/Bin`` and ``~/Man`` and add them to ``PATH`` and ``MANPATH``.

Ruby, RubyGems, Python, and Pip must be installed.

``hexedit`` is a curses application and won't compile under MinGW.

The recommended installation producure is:

    $ make setup
    
    $ make install-tawk
    
    $ make install-script
    
    $ make install-man

# WINDOWS: CYGWIN

``hexedit`` fails to compile under Cygwin for undiagnosed reasons.  It might be possible to compile ``tawk``, but it takes a long time.

Ruby, RubyGems, Python, and Pip must be installed.

The recommended installation procedure is:

    $ make setup
    
    $ make install-script
    
    $ make install-man

