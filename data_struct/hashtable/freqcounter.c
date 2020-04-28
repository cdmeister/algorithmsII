//#include "symbol_table.h"
//#include "symbol_table_bs.h"
//#include "symbol_table_bst.h"
//#include "red_black_bst.h"
#include "hash_table.h"


// This ST client counts the frequecy of occurence of the strings in standard
// input, then prints out that occurs with highest frequency. The command-line,
// argument specifies a lower bound on the length of keys considered.

int main(int argc, char ** argv){
  printf("argc: %d\n",argc);
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
      int word_length =(int) strlen(pch);
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
  printf("Final Size: %d now printing tree\n",size(st));

  //printST(st);
  printf("done printing tree\n");

  free(line);
  char ** key_it = keys(st);
  printf("Key_it address: %p\n",key_it);
  int i;
  printf("Drifto King %s\n",key_it[0]);
  char * max = (char *) malloc(MAX_NUM_CHAR*sizeof(char));
  strcpy(max,key_it[0]);
  printf("Max Orido %s\n",max);
  for(i = 0; i< size(st);i++){
    if(*get(st,key_it[i]) > *get(st,max)){
      strcpy(max,key_it[i]);
    }
  }
  cleanup_keys(st,key_it);
  printf("%s %d\n",max, *get(st,max));
  return EXIT_SUCCESS;

}
