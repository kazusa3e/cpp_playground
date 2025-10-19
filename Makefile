SOURCES := $(shell fd -E build '\.(h|hpp|cc)$$')

.PHONY: build
build:
	cmake --build build -j$(shell nproc)

.PHONY: test
test: build
	./build/tests/all_tests

.PHONY: clang-tidy-check
clang-tidy-check:
	clang-tidy -p build --warnings-as-errors='*' $(SOURCES)

.PHONY: clang-format-check
clang-format-check:
	clang-format --Werror --dry-run --ferror-limit=0 $(SOURCES)

.PHONY: lint
lint: clang-format-check
	@echo "Lint checks passed."

.PHONY: clean
clean:
	cmake --build build --target clean
