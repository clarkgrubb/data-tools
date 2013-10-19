# BASIC INSTALLATION

To install the necessary Ruby gems and Python packages:

    $ sudo make setup

To put the *data tools* and man pages in your path:

    $ make install

It must be run with permission to create files in the install directory as it creates symlinks to the *data tools* repository.

# SET INSTALLATION DIRECTORY

You can override the choice of install directory (`/usr/local/bin`) by setting the `LOCAL_INSTALL_DIR` environment variable.

You can override the choice of man page directory (`/usr/local/share/man`) by setting the `LOCAL_MAN_DIR` environment variable.

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

*TODO*

# WINDOWS

*TODO*
