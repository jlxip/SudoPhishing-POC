# SudoPhishing-POC

## Description
This is a Proof of Concept to show that [SudoPhishing](https://github.com/jlxip/SudoPhishing) can be used to perform privilege escalation. Run it, wait a few seconds, and a file called `evidence.txt` will appear in `/tmp`, which will be owned by root.

## Method
This program is quite simple.

When it runs, it unpacks to `/tmp` SudoPhishing and autosudo, which is a tiny program whose only purpose is to enter the stored password when asked by sudo. It will read it from `~/.config/._`, try it, and then delete that entry, so in case the password was wrong, it will try the next one.

Once the binaries are dropped, it will run SudoPhishing, and wait for `~/.config/._` to be created. Then, it will locally set `SUDO_ASKPASS` to autosudo, and execute itself. If the program detects it's running as root, it creates `/tmp/evidence.txt`, and ends. Most of the changes will be undone, such as the unpacked files and those created by SudoPhishing, but the shell profile will not be reversed, as creating a backup would have required some more code and the purpose was to keep this simple.

## Compilation
In the same way as SudoPhishing, compilation requires both `TCC` and `python2`. Just run `make` and the file `poc` will appear.

## Copyleft
Copyright (C) 2019 jlxip

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.
