#if !defined(TRAVIS)
#define TRAVIS

#include <stdio.h>
#include <string.h>
#define DEFAULT_SIZE 1024

char project_name[100];

void init_project_name(char _project_name[])
{
    strcpy(project_name, _project_name);
}

void create_makefile()
{
    char makefile_content[DEFAULT_SIZE];
    sprintf(makefile_content, "CC=gcc\nCFLAGS = -I. -Wall -ftest-coverage -fprofile-arcs\nDEPS   = ./lib/%s.h\nOBJ    = ./test/%s.test.o\n\n%s: %s $(DEPS)\n	$(CC) -c -o $@ $< $(CFLAGS)\n\ntest-library.out: $(OBJ)\n	gcc -o $@ $^ $(CFLAGS) -lm -lncurses -Os\n\nclean :\n	rm  *.o  *.asm  *.lst *.sym *.rel *.s *.gc* -f *.info", project_name, project_name, "%.o", "%.c");
    FILE * makefile = fopen("makefile.txt", "w");
    fprintf(makefile, "%s", makefile_content);
    fclose(makefile);
}

void create_travis_file()
{
    char travis_file_content[DEFAULT_SIZE];
    sprintf(travis_file_content, "%s", "language: c\n\ninstall:\n- cd ${TRAVIS_BUILD_DIR}\n- wget http://ftp.de.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz\n- tar xf lcov_1.11.orig.tar.gz\n- sudo make -C lcov-1.11/ install\n- gem install coveralls-lcov\n- cd ${TRAVIS_BUILD_DIR}\n- lcov --directory . --zerocounters\n\ncompiler:\n  - clang\n  - gcc\n\nscript:\n   - cd ${TRAVIS_BUILD_DIR}\n  - make\n\nafter_success:\n- cd ${TRAVIS_BUILD_DIR}\n- lcov --directory . --capture --output-file coverage.info\n- lcov --remove coverage.info 'tests/*' '/usr/*' 'test-library*' --output-file coverage.info\n- lcov --list coverage.info\n- coveralls-lcov  coverage.info");
    FILE * travis_file = fopen(".travis.yml", "w");
    fprintf(travis_file, "%s", travis_file_content);
    fclose(travis_file);
}

void create_shell_script()
{
    char shell_script_content[DEFAULT_SIZE];
    sprintf(shell_script_content, "make cleanmake\n./test/%s.test.out\ngcov ./lib/%s.h\n", project_name, project_name);
    FILE * shell_script = fopen("run_coverage_test.sh", "w");
    fprintf(shell_script, "%s", shell_script_content);
    fclose(shell_script);
}

void configure_travis_project(char project_name[])
{
    init_project_name(project_name);
    create_makefile();
    create_travis_file();
    create_shell_script();
}

#endif // TRAVIS
