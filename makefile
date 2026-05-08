.DEFAULT_GOAL := help
.PHONY: check fix help

help:
	@echo ""
	@echo "Available targets:"
	@echo "  check      Run clang-tidy + clang-format in dry-run mode"
	@echo "  fix        Run clang-format in fix mode"
	@echo ""

# (git ls-files "src/*.cpp" "src/*.h")
# (git ls-files "src/*.cpp")
FILES_CPP := $(shell git ls-files 'src/*.cpp')
FILES_H := $(shell git ls-files 'src/*.h')

check:
	clang-format --dry-run --Werror $(FILES_CPP) $(FILES_H)
	clang-tidy -p cmake-build-minsizerel-visual-studio2019 --use-color -extra-arg="--std=c++11" $(FILES_CPP)

fix:
	clang-format -i $(FILES_CPP) $(FILES_H)
	clang-tidy $(FILES_CPP) -p cmake-build-minsizerel-visual-studio2019 --use-color --fix --fix-errors
