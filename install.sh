#!/bin/bash

# check if .bin exists
if [ ! -d ~/.bin ]; then
    mkdir -p ~/.bin
fi

# Compile the executable file
if [ ! -d ./src ]; then
    curl -o IDHunter.c https://raw.githubusercontent.com/nbayat/IDHunter/main/src/IDHunter.c &
    wait pid=$!
    gcc -o ~/.bin/IDHunter ./IDHunter.c
else
    gcc -o ~/.bin/IDHunter src/IDHunter.c
fi

rm ./IDHunter.c

# Add the myapp directory to the PATH environment variable
echo 'export PATH="$HOME/.bin:$PATH"' >> ~/.zshrc

# Reload the .zshrc file
source ~/.zshrc

# Done message
echo "Done!"
echo "Run IDHunter -h for help"
