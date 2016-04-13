/*

clang -g -emit-llvm -c tr_small.c -o tr_small.bc
 ~/git/tracerx/klee/Release+Asserts/bin/klee -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls -search=dfs tr_small.bc --sym-arg 1 --sym-arg 1 --sym-arg 1 --sym-files 2 2000 --max-fail 1 

clang -g -emit-llvm -c tr_small.c -o tr_small.bc
 ~/git/original/klee/Release+Asserts/bin/klee -libc=uclibc --posix-runtime -only-output-states-covering-new -search=dfs tr_small.bc --sym-arg 1 --sym-arg 1 --sym-arg 1 --sym-files 2 2000 --max-fail 1 

RUN WITH THIS CONFIG CAUSE RUN TIME ERROR
clang -emit-llvm -c -g tr_small.c -o tr_small.bc
time ~/git/tracerx/klee/Release+Asserts/bin/klee -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls ./tr_small.bc --sym-arg 1 --sym-arg 1 --sym-arg 1 --sym-files 2 2000 --max-fail 1 

clang -emit-llvm -c -g tr_small.c -o tr_small.bc
time ~/git/original/klee/Release+Asserts/bin/klee -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls ./tr_small.bc --sym-arg 1 --sym-arg 1 --sym-arg 1 --sym-files 2 2000 --max-fail 1 
 
*/ 

 #include <stdio.h>

#define BUFFER_SIZE     1024
 #define ASCII           0377
 
 typedef char BOOL;
 #define TRUE    1
 #define FALSE   0
 
 #define NIL_PTR         ((char *) 0)
 
 BOOL com_fl, del_fl, sq_fl;
 
 unsigned char output[BUFFER_SIZE], input[BUFFER_SIZE];
 unsigned char vector[ASCII + 1];
 BOOL invec[ASCII + 1], outvec[ASCII + 1];
 
 short in_index, out_index;
 
 #include <sys/types.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 
/*
 _PROTOTYPE(int main, (int argc, char **argv));
 _PROTOTYPE(void convert, (void));
 _PROTOTYPE(void map, (unsigned char *string1, unsigned char *string2));
 _PROTOTYPE(void expand, (char *arg, unsigned char *buffer));
 _PROTOTYPE(void complement, (unsigned char *buffer));*/

int main (int argc, char **argv);
int mystrlen(const char * input);
void convert(void);
void map(unsigned char *string1, unsigned char *string2);
void expand(char *arg, unsigned char *buffer);
void complement(unsigned char *buffer);
 
int main(argc, argv)
int argc;
char *argv[];
//int main()
 { 
   //int SIZE = 3;
   //int argc;
   //char *argv[SIZE];
   //klee_make_symbolic(argv, sizeof argv, "argv");
   //argc = SIZE;
 
   register unsigned char *ptr;
   int index = 1;
   short i;
 
   if (argc > 1 && argv[index][0] == '-') {
         for (ptr = (unsigned char *) &argv[index][1]; *ptr; ptr++) {
                 switch (*ptr) {
                     case 'c':   com_fl = TRUE;  break;
                     case 'd':   del_fl = TRUE;  break;
                     case 's':   sq_fl = TRUE;   break;
                     default:
                         //write(2,"Usage: tr [-cds] [string1 [string2]].\n", 38);
                         exit(1);
                 }
         }
         index++;
   }
   for (i = 0; i <= ASCII; i++) {
         vector[i] = i;
         invec[i] = outvec[i] = FALSE;
   }
 
   if (argv[index] != NIL_PTR) {
         expand(argv[index++], input);
         //if (com_fl) complement(input);
         if (argv[index] != NIL_PTR) expand(argv[index], output);
         //if (argv[index] != NIL_PTR) map(input, output);
         //for (ptr = input; *ptr; ptr++) invec[*ptr] = TRUE;
         //for (ptr = output; *ptr; ptr++) outvec[*ptr] = TRUE;
   }
   //convert();
   return(0);
 }
 
 static int starts_with(const char *s1, const char *s2)
 {
         while (*s1 && *s1 == *s2)
         {
                 s1++;
                 s2++;
         }
         return *s1 == 0;
 }
 
 /* 
  * character classes from 
  * http://www.opengroup.org/onlinepubs/009695399/utilities/tr.html
  * missing: blank, punct, cntrl, graph, print, space 
  */
 static struct
 {
         const char *keyword;
         char first;
         char last;
 } expand_keywords[] = {
         { "[:alnum:]", 'A', 'Z' },
         { "[:alnum:]", 'a', 'z' },
         { "[:alnum:]", '0', '9' },
         { "[:alpha:]", 'A', 'Z' },
         { "[:alpha:]", 'a', 'z' },
         { "[:digit:]", '0', '9' },
         { "[:lower:]", 'a', 'z' },
         { "[:upper:]", 'A', 'Z' },
         { "[:xdigit:]", '0', '9' },             
         { "[:xdigit:]", 'A', 'F' },
         { "[:xdigit:]", 'a', 'f' }
 };
 
 #define LENGTH(a) ((sizeof((a))) / (sizeof((a)[0])))
 
 void expand(arg, buffer)
 register char *arg;
 register unsigned char *buffer;
 {
   int i, ac, keyword_index;
 
   while (*arg) {
         if (*arg == '\\') {
                 arg++;
                 i = ac = 0;
                 if (*arg >= '0' && *arg <= '7') {
                         do {
                                 ac = (ac << 3) + *arg++ - '0';
                                 i++;
                         } while (i < 4 && *arg >= '0' && *arg <= '7');
                         *buffer++ = ac;
                 } else if (*arg != '\0')
                         *buffer++ = *arg++;
         } else if (*arg == '[') {
                 /* does one of the keywords match? */
                 keyword_index = -1;
                 for (i = 0; i < LENGTH(expand_keywords); i++)
                         if (starts_with(expand_keywords[i].keyword, arg))
                         {
                                 /* we have a match, remember and expand */
                                 keyword_index = i;
                                 ac = expand_keywords[i].first;
                                 while (ac <= expand_keywords[i].last)
                                         *buffer++ = ac++;
                         }
 
                 /* skip keyword if found, otherwise expand range */
                 if (keyword_index >= 0){
	 		arg += mystrlen(expand_keywords[keyword_index].keyword);
                        //arg += strlen(expand_keywords[keyword_index].keyword);
		}
                 else
                 {
                         /* expand range */
                         arg++;
                         i = *arg++;
                         if (*arg++ != '-') {
                                 *buffer++ = '[';
                                 arg -= 2;
                                 continue;
                         }
                         ac = *arg++;
                         while (i <= ac) *buffer++ = i++;
                         arg++;          /* Skip ']' */
                 }
         } else
                 *buffer++ = *arg++;
   }
 }
 
 int mystrlen(const char * input){
   int length = 0;
   while(input[length]!='\0'){
    length++;
   }
   return length;
 }
 
