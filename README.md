# TerminalTennis

A terminal based tennis game built using the ncurses library. 

Download and extract NCURSES(supports only linux based devices and WSL) from the following link: https://invisible-island.net/datafiles/release/ncurses.tar.gz

Run these following commands in terminal to install the library:

tar zxvf ncurses-6.3.tar.gz  # unzip and untar the archive
cd ncurses-6.3               # cd to the directory
./configure                             # configure the build according to your 
                                            # environment
make                                    # make it
sudo make install                            # install it



Compiling and executing can be done after navigating into the folder containing TT.c file:

gcc TT.c -ogame.out -lncurses

./game.out



