# IDHunter
OSX Installed Apps bundle id extractor CLi

This is a simple C program that takes an application name as input and returns the bundle identifier of the installed application on a Mac OS system.

# Install

```console
~$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/nbayat/IDHunter/main/install.sh)"
```

### Or manually

```console
~$ ./install.sh
```

# Usage

```console
~$ IDHunter code
Bundle ID for Visual Studio Code.app: com.microsoft.VSCode
```

OR

```console
~$ IDHunter "Prime Video"
Bundle ID for Prime Video.app: com.amazon.aiv.AIVApp
```




## Author

Written by [Nima Bayat](https://github.com/nbayat)

## License

This program is released under the [MIT License]
