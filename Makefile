# Standard flags


PROJECTS := x_game

.PHONY: all clean help $(PROJECTS)

all: ${PROJECTS}

x_game:
	@echo "==== Building x_game ===="
	@${MAKE} --no-print-directory -C . -f HelicopterGame.make
	@echo "==== Finished x_game ===="


run: 
	@echo "==== Running x_game ===="
	@${MAKE} --no-print-directory -C . -f HelicopterGame.make run

clean:
	@${MAKE} --no-print-directory -C . -f HelicopterGame.make clean
