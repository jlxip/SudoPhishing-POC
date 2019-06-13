all:
	cd SP && make && cd .. && mv SP/sp sp
	tcc autosudo.c -o autosudo
	python2 packer.py
	rm sp
	rm autosudo
	tcc poc.c -o poc
	rm packs.h
