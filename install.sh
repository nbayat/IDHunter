#!/bin/bash

# check if .bin exists
if [ ! -d ~/.bin ]; then
    mkdir -p ~/.bin
fi

# Compile the executable file
if [ ! -d ./src ]; then
    git clone https://github.com/nbayat/IDHunter.git
    cd IDHunter
    gcc -o ~/.bin/IDHunter src/IDHunter.c
    cd ..
    rm -rf IDHunter
else
    gcc -o ~/.bin/IDHunter src/IDHunter.
fi

# Add the myapp directory to the PATH environment variable
echo 'export PATH="$HOME/.bin:$PATH"' >> ~/.zshrc

# Reload the .zshrc file
source ~/.zshrc

# Done message
echo "Done!"
echo "Run IDHunter -h for help"
