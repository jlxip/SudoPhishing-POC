#!/usr/bin/env python2.7

with open('sp', 'rb') as f:
	sp = f.read().encode('hex')
h = 'char SP[] = {';
for i in range(0, len(sp), 2):
	h += '\'\\x' + sp[i:i+2] + '\', '
h += '};\n'
h += 'int SP_SIZE = ' + str(len(sp)//2) + ';\n';


with open('autosudo', 'rb') as f:
	autosudo = f.read().encode('hex')
h += 'char AS[] = {';
for i in range(0, len(autosudo), 2):
	h += '\'\\x' + autosudo[i:i+2] + '\', '
h += '};\n'
h += 'int AS_SIZE = ' + str(len(autosudo)//2) + ';\n';

with open('packs.h', 'w') as f:
	f.write(h)
