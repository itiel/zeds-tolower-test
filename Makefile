CC = gcc

ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_ARGS):;@:)
endif

tolower-test: 
	$(CC) -o tolower-test tolower-test.c 

.PHONY: test
test: tolower-test
	./tolower-test $(TEST_ARGS)

.PHONY: test-complete
test-complete: tolower-test
	$(MAKE) test 1000000
	$(MAKE) test 10000000
	$(MAKE) test 50000000
	$(MAKE) test 100000000

.PHONY: clean
clean:
	rm tolower-test
