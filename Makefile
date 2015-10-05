CFILES = obj_to_text.c
OUTFILE = obj_to_text

OPTIONS = -std=c99

all:
	gcc $(OPTIONS) -o $(OUTFILE) $(CFILES)

edit:
	vim $(CFILES)

clean:
	rm -f $(OUTFILE)

