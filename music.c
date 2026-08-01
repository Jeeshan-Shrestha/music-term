#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <search query>\n", argv[0]);
    return 1;
  }

  char search[512] = "";

  for (int i = 1; i < argc; i++) {
    strcat(search, argv[i]);
    if (i != argc - 1)
      strcat(search, " ");
  }

  char ytcmd[1024];
  snprintf(ytcmd, sizeof(ytcmd),
           "yt-dlp --js-runtimes node "
           "\"ytsearch5:%s\" "
           "--print \"%%(title)s|%%(webpage_url)s\"",
           search);

  FILE *fp = popen(ytcmd, "r");
  if (fp == NULL) {
    perror("popen");
    return 1;
  }

  char line[2048];
  char titles[5][1024];
  char urls[5][512];
  int count = 0;

  while (fgets(line, sizeof(line), fp) && count < 5) {
    line[strcspn(line, "\n")] = '\0';

    char *sep = strchr(line, '|');
    if (sep == NULL)
      continue;

    *sep = '\0';

    strcpy(titles[count], line);
    strcpy(urls[count], sep + 1);

    printf("%d. %s\n", count + 1, titles[count]);

    count++;
  }

  pclose(fp);

  if (count == 0) {
    printf("No results found.\n");
    return 1;
  }

  int choice;

  printf("Choose a video (1-%d): ", count);
  scanf("%d", &choice);

  if (choice < 1 || choice > count) {
    printf("Invalid choice.\n");
    return 1;
  }

  printf("\nDownloading:\n%s\n\n", titles[choice - 1]);

  char command[2048];

  snprintf(command, sizeof(command),
           "yt-dlp --js-runtimes node "
           "-o \"$HOME/Music/%%(title)s.%%(ext)s\" "
           "-x --audio-format mp3 "
           "\"%s\"",
           urls[choice - 1]);

  system(command);

  return 0;
}
