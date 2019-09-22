#include "symbol_table.h"

// This ST client counts the frequecy of occurence of the strings in standard
// input, then prints out that occurs with highest frequency. The command-line,
// argument specifies a lower bound on the length of keys considered.

int main(int argc, char ** argv){

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int minlen = atoi(argv[1]);
  struct symbol_table * st = ST();
  while ((read = getline(&line, &len, stdin)) != EOF) {
    //printf("Retrieved line of length %zu :\n", read);
    char * pch;
    pch = strtok (line," \t\n");
    while (pch != NULL)
    {
      //printf ("%s\n",pch);
      size_t word_length = strlen(pch);
      if(word_length < minlen){
        pch = strtok (NULL, " \t\n");
        continue;
      }
      if(!contains(st,pch)) put(st,pch,1);
      else{
        put(st,pch,(*get(st,pch)+1));
      }
      //printf("The word %s is %lu characters long\n",pch,word_length);
      pch = strtok (NULL, " \t\n");
    }
  }
  //printLL(st);

  free(line);
  char ** key_it = keys(st);
  int i;
  char * max = (char *) malloc(MAX_NUM_CHAR*sizeof(char));
  strcpy(max,key_it[0]);
  for(i = 0; i< st->size;i++){
    if(*get(st,key_it[i]) > *get(st,max)){
      strcpy(max,key_it[i]);
    }
  }
  cleanup_keys(st,key_it);
  printf("%s %d\n",max, *get(st,max));
  return EXIT_SUCCESS;

}
