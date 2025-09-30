# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
SRCDIR = src
SOURCES = $(SRCDIR)/matrix.cpp
MAIN_SOURCE = $(SRCDIR)/main.cpp
TEST_SOURCE = $(SRCDIR)/test.cpp
MAIN_APP = matrix_app
TEST_APP = test_app
DOCSDIR = docs
CSV_FILES = *.csv

.PHONY: all main test docs clean run-test run-demo memcheck all-check docker-build docker-run docker-test docker-demo ci-test csv-test help

all: main test

main: $(SOURCES) $(MAIN_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(MAIN_APP) $(SOURCES) $(MAIN_SOURCE)

test: $(SOURCES) $(TEST_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TEST_APP) $(SOURCES) $(TEST_SOURCE)

docs:
	doxygen Doxyfile

clean:
	rm -f $(MAIN_APP) $(TEST_APP) $(CSV_FILES)
	rm -rf $(DOCSDIR)/html/ $(DOCSDIR)/latex/

run-test: test
	./$(TEST_APP)

run-demo: main
	./$(MAIN_APP)

memcheck: test
	valgrind --leak-check=full ./$(TEST_APP)

all-check: test
	./$(TEST_APP)
	valgrind --leak-check=full ./$(TEST_APP)

docker-build:
	docker build -t matrix-calculator .

docker-run: docker-build
	docker run matrix-calculator

docker-test: docker-build
	docker run matrix-calculator ./$(TEST_APP)

docker-demo: docker-build
	docker run matrix-calculator ./$(MAIN_APP)

ci-test: test
	./$(TEST_APP)
	valgrind --leak-check=full --error-exitcode=1 ./$(TEST_APP)

csv-test: test
	./$(TEST_APP)
	@echo "Checking for CSV files..."
	@if ls *.csv 1> /dev/null 2>&1; then \
		echo "CSV files found:"; \
		ls *.csv; \
	else \
		echo "No CSV files found"; \
	fi

help:
	@echo "Available targets:"
	@echo "  all        - Build main app and tests"
	@echo "  main       - Build only main application"
	@echo "  test       - Build and run tests"
	@echo "  run-test   - Run tests"
	@echo "  run-demo   - Run demo application"
	@echo "  memcheck   - Run tests with Valgrind"
	@echo "  docs       - Generate documentation"
	@echo "  clean      - Clean build artifacts"
	@echo "  docker-build - Build Docker image"
	@echo "  docker-run   - Run Docker container with tests"
	@echo "  docker-test  - Run tests in Docker"
	@echo "  docker-demo  - Run demo in Docker"
	@echo "  ci-test    - Run tests for CI/CD"
	@echo "  csv-test   - Run tests and check CSV files"