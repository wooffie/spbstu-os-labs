SHELL=/bin/bash

all:
	for a in $$(find -type d -name "src*" ); do \
		echo "processing $$a"; \
		$(MAKE) -C $$a; \
	done;
	@echo "Done!"

clean:
	for a in $$(find -type d -name "src*" ); do \
		echo "cleaning $$a"; \
		$(MAKE) clean -C $$a; \
	done;
	@echo "Done!"
