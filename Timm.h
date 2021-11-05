#ifndef _Timmh_
#define _Timmh_

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define EMPTY_FILE -5
#define INVALID_FORMAT_FILE -6
#define NULL_CODE -7
 
int imm_open_file(char argv[]);
int imm_convert(char *file, char *bin);
int imm_segment(char *file, char *bin, int thr);
int imm_cc(char *file1, char *file2);
int imm_lab(char *file1, char *file2);

#endif