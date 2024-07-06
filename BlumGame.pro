TEMPLATE = subdirs

CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0

SUBDIRS = app tests

CONFIG += ordered

# Цель для генерации документации
docs.commands = doxygen Doxyfile
QMAKE_EXTRA_TARGETS += docs

# Включение целей по умолчанию
PRE_TARGETDEPS += $$QMAKE_EXTRA_TARGETS

# Цель для проверки утечек памяти с Valgrind
valgrind_check.commands = cd app ; valgrind --suppressions=suppressions.supp --leak-check=full ./app
valgrind_check.depends = all
QMAKE_EXTRA_TARGETS += valgrind_check

# Цель для удобного вызова valgrind_check
memorycheck.target = memorycheck
memorycheck.commands = $(MAKE) valgrind_check
QMAKE_EXTRA_TARGETS += memorycheck
