venv:
	poetry install

format:
	poetry run clang-format -i *.ino *.cpp *.h

format/check:
	poetry run clang-format -i *.ino *.cpp *.h --dry-run --Werror