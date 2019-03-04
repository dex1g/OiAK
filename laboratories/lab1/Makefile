all: app

app: app.o
	ld app.o -o app

app.o: changLetterSize.s
	as changLetterSize.s -o app.o

clean:
	rm -f app.o app
