#-----------------------------------------------------------------------------
# Project Makefile
# Daniel J. Greenhoe
#-----------------------------------------------------------------------------
#--------------------------------------
# TARGET
#--------------------------------------
TARGET = jj

#--------------------------------------
# Files
#--------------------------------------
FILES_OBJ = main.o blackjack.o numberGame.o codeBreaker.o videoGame.o
FILES_H   = main.h

#--------------------------------------
# Programs
#--------------------------------------
PRG_COMPILE = g++
PRG_LINK    = g++

#--------------------------------------
# master build control
#--------------------------------------
$(TARGET).exe: $(FILES_OBJ) $(FILES_H) makefile
  time /T
  $(PRG_LINK)  -o $(TARGET).exe $(FILES_OBJ)
  dir $(TARGET).exe
#  @echo Done ... sto/graphics pdfs are ready!

#--------------------------------------
# implicit build control
#--------------------------------------
.cpp.o:
	$(PRG_COMPILE) -c $&.cpp

#--------------------------------------
# commands
#--------------------------------------
clean:
  del *.o

scrub:
  make clean
  del *.exe

new:
  del *.obj
  make

zip:
  zip -o -9 -r $(TARGET).zip * -x *.obj *.tds *.exe *.dat *.sty *.zip *.bat *.pdf tmp\*
  unzip -l $(TARGET).zip
  dir *.zip
